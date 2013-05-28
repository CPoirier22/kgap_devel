#include "../../../include/common/include/_stddef.h"
#include "../../../include/common/include/rtxdef.h"
#include "../../../include/common/include/print_status.h"

extern void *memset(void *dst, int c, unsigned long int length);

#define _DEBUG_HEAPCHECK_
static BYTE HeapInitialized = 0;
static WORD MallocCount;

#ifndef HEAP_SIZE
#error Must define HEAP_SIZE in build file
/* #define HEAP_SIZE 0x1200*/
#endif

#ifdef GCCCOMPILE
static BYTE Heap[HEAP_SIZE] __attribute__ ((section (".data")));
#else
#pragma dataseg=HEAPMEM
static __no_init BYTE Heap[HEAP_SIZE];
#pragma dataseg=default
#endif

#define ECT_DEBUG_HEAP

void InitHeap_(void);
static void *malloc_(unsigned int size);
static void free_(void *block);
#define MALLOC 1
#define FREE   0

/**/
/* Prototypes*/
/**/
#if RTNSIZE
extern WORD GetSpReturnAdr(void);
#endif
void trapInterruptVector(int vectorNumber, char *msg);

#define ALLOCATED      0x8000
#define DEALLOCATED    0x0000
#define EXTRA_SIZE sizeof(unsigned)

#ifndef RTNSIZE
#define RTNSIZE 0
#endif
#define ERROR_HEAP_OVERFLOW 0x10
#define ERROR_HEAP_ERROR    0x11

typedef struct HeapBlock
{
  unsigned Size; /* size of block, bit 15=0, free block*/
  /*                bit 15=1, allocated block*/
  BYTE Data[1];

} HeapBlockType;

/******************************************************************************
 * Name       : malloc                                                         *
 * Input      : Number of bytes to be allocated on the heap                    *
 * Output     : Pointer to the allocated area, NULL if no space available      *
 * Modifies   : -                                                              *
 *-----------------------------------------------------------------------------*
 * Description:                                                                *
 *   This function allocates some temporary memory on the heap.                *
 ******************************************************************************/
void *malloc_(unsigned int size)
{

  struct HeapBlock *p = (struct HeapBlock *) Heap, *p1;
  unsigned tmpsize = size + EXTRA_SIZE + RTNSIZE, tmp;
  /*  printf232("malloc(%d)=",size);*/

#if RTNSIZE
  size+=RTNSIZE;
#endif

  if (size)
  {
    if (!HeapInitialized)
      InitHeap_();

    while (p != NULL)
    {
      tmp = p->Size & 0x7FFF;
      if ((tmp >= size) && !(p->Size & ALLOCATED))
      {
        break;
      }
      else
      {
        p = (struct HeapBlock *) ((BYTE *) p + tmp + EXTRA_SIZE);
        /*--        if((unsigned)p-(unsigned)Heap>=HEAP_SIZE)*/
        if (((uint32) p - (uint32) Heap) >= HEAP_SIZE)
          p = NULL;
      }
    }

    if (p != NULL)
    {
      if (tmp >= tmpsize)
      {
        /* Size doesn't fit, make new (empty) block.*/
        p1 = (struct HeapBlock *) ((BYTE *) p + tmpsize);
        p1->Size = tmp - tmpsize;
//#ifdef _DEBUG_HEAPCHECK_
//        if (p1->Size>0)
//        memset(p1->Data,0xf1,p1->Size);
//#endif
        p->Size = size;
      }

      p->Size |= ALLOCATED;

      MallocCount++;
#if RTNSIZE
      *((WORD*)&p->Data[0])=GetSpReturnAdr();
#endif
      /*      printf232("%x\n",&(p->Data[RTNSIZE]));*/
      return (void *) &(p->Data[RTNSIZE]);
    }
  }
  return NULL; /* No blocks large enough !*/
}

/******************************************************************************
 * Name       : MergeBlock
 * Input      :
 *-----------------------------------------------------------------------------
 * Description:
 *              Merges two succeeding heap block's <first> and <last>
 ******************************************************************************/
void MergeBlock_(struct HeapBlock *first, struct HeapBlock *last)
{
  /* Merge with previous block*/
  first->Size += (last->Size + EXTRA_SIZE);
//#ifdef _DEBUG_HEAPCHECK_
//  if (first->Size>0)
//  memset(first->Data,0xf2,first->Size);
//#endif
}

extern void print_all_heap(void);
extern void uart_sendstring2(char *msg);
/******************************************************************************
 * Name       : free                                                           *
 * Input      : Pointer to the memory to be freed                              *
 * Output     : None                                                           *
 * Modifies   : -                                                              *
 *-----------------------------------------------------------------------------*
 * Description:                                                                *
 *   This function frees some previously allocated memory.                     *
 ******************************************************************************/
void free_(void *block)
{
  struct HeapBlock *p = (struct HeapBlock *) Heap, *p1 = NULL, *b = (struct HeapBlock *) ((BYTE *) block - EXTRA_SIZE - RTNSIZE);

  /*  printf232("free(%x)\n",(uint16)block);*/
  /* Debug stuff*/
#ifdef _DEBUG_HEAPSIZE_
#ifdef _DEBUG_HEAPTRACE_
  Hts.Cmd= FREE;
  Hts.Size= b->Size&~ALLOCATED;
  Hts.Pos= (WORD) block;
  LogDebugMail(3,(char)sizeof(Hts),(char *)&Hts);
#endif
  HeapUsed-=(b->Size&~ALLOCATED)+2;
  HeapCnt--;
#endif

  if (!HeapInitialized)
    InitHeap_();

  if ((b->Size & 0x8000) == 0)
  {
    unsigned char *debug_data;
    char* tmp;
    int f, i;
    debug_data = (unsigned char *)b;
    debug_data -= 0x30; // start by moving back 0x30 bytes on the heap
	  uart_sendstring2("free ERROR\n\r");
    tmp = StringPrint(StatusString, "free Data\n\r");
    for (i = 0; i < 4; i++)
    {
      tmp = StringPrint(tmp, "[");
	  for (f = 0; f < 0x10; f++)
	  {
	    tmp = StrPrintHexByte(tmp, debug_data[(0x10 * i) + f]); /* Print data */
	    if (f < 0x0F) tmp = StringPrint(tmp, ",");
	  }
	  tmp = StringPrint(tmp, "]\n\r");
    }
    uart_sendstring2(StatusString);

	  print_all_heap();
	  while(1) {;}

    trapInterruptVector(0x17, "free error");
  }
  else
  {
    while (p < b)
    {
      p1 = p;
      p = (struct HeapBlock *) ((BYTE *) p + (p->Size & 0x7FFF) + EXTRA_SIZE);
    }

    p->Size &= 0x7FFF;
//#ifdef _DEBUG_HEAPCHECK_
//    if (p->Size>0)
//      memset(p->Data,0xf3,p->Size);
//#endif

    if (p1 != NULL && !(p1->Size & ALLOCATED))
    {
      MergeBlock_(p1, p);
      p = p1;
    }
    p1 = (struct HeapBlock *) ((BYTE *) p + (p->Size) + EXTRA_SIZE);
    /* Check if merge with next block possible*/
    if ((uint32) p1 - (uint32) Heap < HEAP_SIZE && !(p1->Size & ALLOCATED))
      MergeBlock_(p, p1);
    MallocCount--;
  }
}

/******************************************************************************
 * Name       : InitHeap                                                       *
 * Input      : None                                                           *
 * Output     : None                                                           *
 *-----------------------------------------------------------------------------*
 * Description:                                                                *
 *   Prepares the heap area for use.                                           *
 ******************************************************************************/
void InitHeap_(void)
{
  /*  printf232("InitHeap\n");*/
  memset((BYTE *) &Heap, 0x00, sizeof(Heap)); /*KEH*/
  ((struct HeapBlock *) Heap)->Size = HEAP_SIZE - EXTRA_SIZE;
  HeapInitialized++;
#ifdef _DEBUG_HEAPCHECK_
  memset(((struct HeapBlock *)Heap)->Data,0xf4,HEAP_SIZE-EXTRA_SIZE);
#endif
}

static int allocated = 0;
static int stopAtOutOfMem = 1;

int getAllocatedMemory()
{
  return allocated;
}

int getHeapSize()
{
  return sizeof(Heap);
}

struct HeapBlock *hm_p = (struct HeapBlock *) Heap;
int heap_print_cnt=0;
void *hm_print_heap(unsigned char reset)
{
  char* tmp;
  if (reset)
  {
    hm_p = (struct HeapBlock *) Heap;
    return NULL;
  }
  tmp = StringPrint(StatusString, "heap memory[");

  while ((hm_p != NULL) && (heap_print_cnt++<10))
  {
    if (hm_p->Size & ALLOCATED)
    {
      tmp = StringPrint(StatusString, "0x");
      tmp = StrPrintHexByte(tmp, hm_p->Data[0]); /* Print the id */
      tmp = StringPrint(tmp, ",");
#ifdef ECT_DEBUG_HEAP
      tmp = StrPrintHexByte(tmp, hm_p->Data[4]); /* Print the allocated time */
      tmp = StrPrintHexByte(tmp, hm_p->Data[3]); /* Print the allocated time */
      tmp = StringPrint(tmp, ",");
      tmp = StrPrintHexByte(tmp, hm_p->Data[5]); /* Print the additional info */
      tmp = StrPrintHexByte(tmp, hm_p->Data[6]); /* Print the additional info */
      tmp = StrPrintHexByte(tmp, hm_p->Data[9]); /* Print the additional info */
      tmp = StrPrintHexByte(tmp, hm_p->Data[10]); /* Print the additional info */
      tmp = StringPrint(tmp, ",");
      tmp = StrPrintHexWord(tmp, hm_p->Size & 0x7FFF); /* Print the id*/
#endif
      tmp = StringPrint(tmp, "\n\r");
      uart_sendstring2(StatusString);
    }
    else
    {
      tmp = StringPrint(StatusString, "0x");
      tmp = StrPrintHexByte(tmp, hm_p->Data[0]); /* Print the id*/
      tmp = StringPrint(tmp, ",");
      tmp = StringPrint(tmp, ",");
      tmp = StringPrint(tmp, ",");
      tmp = StrPrintHexWord(tmp, hm_p->Size & 0x7FFF); /* Print the id*/
      tmp = StringPrint(tmp, ",free");
      tmp = StringPrint(tmp, "\n\r");
      uart_sendstring2(StatusString);
    }
    hm_p = (struct HeapBlock *) ((BYTE *) hm_p + (hm_p->Size & 0x7FFF) + EXTRA_SIZE);
    if (((uint32) hm_p - (uint32) Heap) >= HEAP_SIZE)
      hm_p = NULL;
  }

  heap_print_cnt=0;
  return hm_p;
}

void print_all_heap(void)
{
  hm_print_heap(1);
  while (hm_print_heap(0));
}


extern void uart_sendbyte(char data);

void* mem_malloc(unsigned int size, BYTE id)
{
#ifdef ECT_DEBUG_HEAP
  char* buffer = malloc_(size + 5);
#else
  char* buffer = malloc_(size);
#endif
  if (buffer == 0)
  {
	  uart_sendstring2("malloc ERROR\n\r");
	  print_all_heap();
	  while(1) {;}

    char* tmp;
    struct HeapBlock *p = (struct HeapBlock *) Heap;

    tmp = StringPrint(StatusString, "Out of memory at id = 0x");
    tmp = StrPrintHexByte(tmp, id);
    tmp = StringPrint(tmp, " req 0x");
    tmp = StrPrintHexWord(tmp, size);
    tmp = StringPrint(tmp, " tot 0x");
    tmp = StrPrintHexWord(tmp, allocated);
    tmp = StringPrint(tmp, " [");

    while (p != NULL)
    {
	  tmp = StrPrintHexByte(tmp, p->Data[0]);			/* Print the id */
	  tmp = StrPrintHexWord(tmp, p->Size & 0x7FFF);		/* Print the size */
	  if ((p->Size & ALLOCATED) != ALLOCATED)
		tmp = StringPrint(tmp, "free");
	  tmp = StringPrint(tmp, "-");
//      if (p->Size & ALLOCATED)
//      {
//        tmp = StrPrintHexByte(tmp, p->Data[0]); /* Print the id*/
//        tmp = StrPrintHexWord(tmp, p->Size & 0x7FFF); /* Print the id*/
//        tmp = StringPrint(tmp, "-");
//      }
      p = (struct HeapBlock *) ((BYTE *) p + (p->Size & 0x7FFF) + EXTRA_SIZE);
      if (((uint32) p - (uint32) Heap) >= HEAP_SIZE)
        p = NULL;
    }
    tmp = StringPrint(tmp, "]");
    trapInterruptVector(0x15, StatusString);
    while (stopAtOutOfMem)
    {
      ;
    }
    return 0;
  }
#ifdef ECT_DEBUG_HEAP
  extern uint16 FreeRunCounter;
  buffer[0] = id;
  buffer[1] = size & 0xff;
  buffer[2] = (size >> 8) & 0xff;
  buffer[3] = FreeRunCounter & 0xff;
  buffer[4] = (FreeRunCounter >> 8) & 0xff;

  allocated += (size+5);

  return &buffer[5];
#else
  return buffer;
#endif
}

void mem_free(void* block)
{
  char* buffer = (char*) block;
  WORD size;
#ifdef ECT_DEBUG_HEAP
  buffer--;
  buffer--;
  buffer--;
  buffer--;
  buffer--;
#endif

  /* id = buffer[0];*/
  size = buffer[1] & 0xFF;
  size |= (buffer[2] & 0xFF) << 8;

#ifdef ECT_DEBUG_HEAP
  allocated -= (size+5);
#else
  allocated -= size;
#endif

  free_((void*) buffer);
}

char* getMemoryStatus()
{
  char *ptr = StringPrint(StatusString, "allocated [");
  ptr = StrPrintHexWord(ptr, getAllocatedMemory());
  ptr = StringPrint(ptr, "] of [");
  ptr = StrPrintHexWord(ptr, getHeapSize());
  ptr = StringPrint(ptr, "]");
  return StatusString;
}

void continueAtOutOfMem()
{
  stopAtOutOfMem = 0;
}
