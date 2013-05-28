#ifndef _HEAP_H__
#define _HEAP_H__

#include "../../../common/include/bitsdef.h"

typedef enum
{
    SignalHeap = 0,
    MemHeap = 1
} HeapNoType;

/*#define NewBuffer(size,ptr) ((*(ptr))=malloc(size))*/
extern Boolean NewBuffer(int BufferLength, void **BufferPointer);
extern Boolean NewBuffer_(int BufferLength, void **BufferPointer, BYTE id);
/*extern Boolean NewBuffer(unsigned int BufferLength, void ** BufferPointer);*/
extern Boolean NewSignal(int BufferLength, void **BufferPointer);

extern void DeleteBuffer(void *BufferPointer);

#endif /* _HEAP_H__*/
