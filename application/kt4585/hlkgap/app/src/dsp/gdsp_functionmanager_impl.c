#include "gdsp_functionmanager_api.h"
#include "gdsp_registerdef.h"
#include "gdsp_functionmanager_impl.h"
#include "../../../../../../include/common/include/print_status.h"

FmContextAdmin_t FmContextAdmin[MAX_NO_FM_CONTEXTS];// __attribute__ ((section (".data")));				// size: 0x54
FmDspAdmin_t FmDspAdmin[MAX_NO_FM_DSP_CORES];// __attribute__ ((section (".data")));					// size: 0x18
Function_manager_admin_type FmAdmin[MAX_FM_ADMIN_BLOCKS];// __attribute__ ((section (".data")));		// size: 0xf4

unsigned char no_contexts;
    
#define DSP1_RUNNIG          0x1
#define DSP2_RUNNIG          0x1   

#define DSP_SAFE_POINT       0x1  // Must have this value, will not work with other values!
#define DSP_UNSAFE_POINT     0x0  // Must have this value, will not work with other values!

#define DSP_CONTEXT_DONT_RUN 0x0000  // Must have this value, will not work with other values!
#define DSP_CONTEXT_RUN      0x8000  // Must have this value, will not work with other values!

#define BS_FREE 1
#define BS_ALLOCATED (!BS_FREE)
#define MAX_CODE_BLOCK ((64)-1)

#define FM_DSP_NULL_PTR (FM_DSP_PTR_TYPE)0xFFFF
#define FM_DSP_HEAP_BLOCK_MAX   0x7FFF
#define FM_DSP_HEAP_BLOCK_FREE  0x8000
#define FM_DSP_HEAP_END         0x0000
#define FM_DSP_HEAP_ADM_SIZE    1

typedef struct
{
  unsigned char context_id;
  unsigned char max_context_blocks;
} MaxContextIndexConvertTableType;

const MaxContextIndexConvertTableType MaxContextIndexConvertTable[GDSP_DSP_MAX_CONTEXT] =
{
  {GDSP_DSP1_BACKGROUND_CONTEXT      ,MAX_DSP1_BACKGROUND_BLOCKS},
  {GDSP_DSP1_8KHZ_CONTEXT            ,MAX_DSP1_8KHZ_BLOCKS},
  {GDSP_DSP1_16KHZ_CONTEXT           ,MAX_DSP1_16KHZ_BLOCKS},
  {GDSP_DSP1_32KHZ_CONTEXT           ,MAX_DSP1_32KHZ_BLOCKS},
  {GDSP_DSP1_CR16INT_CONTEXT         ,MAX_DSP1_CR16INT_BLOCKS},
  {GDSP_DSP1_DIPINT_CONTEXT          ,MAX_DSP1_DIPINT_BLOCKS},
  {GDSP_DSP1_DSP2INT_CONTEXT         ,MAX_DSP1_DSP2INT_BLOCKS},
  {GDSP_DSP2_BACKGROUND_CONTEXT      ,MAX_DSP2_BACKGROUND_BLOCKS},
  {GDSP_DSP2_8KHZ_CONTEXT            ,MAX_DSP2_8KHZ_BLOCKS},
  {GDSP_DSP2_16KHZ_CONTEXT           ,MAX_DSP2_16KHZ_BLOCKS},
  {GDSP_DSP2_32KHZ_CONTEXT           ,MAX_DSP2_32KHZ_BLOCKS},
  {GDSP_DSP2_CR16INT_CONTEXT         ,MAX_DSP2_CR16INT_BLOCKS},
  {GDSP_DSP2_DIPINT_CONTEXT          ,MAX_DSP2_DIPINT_BLOCKS},
  {GDSP_DSP2_DSP1INT_CONTEXT		 ,MAX_DSP2_DSP1INT_BLOCKS}, };

/*============================= DSP PC start registers  ====================================*/                                                     
unsigned short *dsp1_pc_reg          = (unsigned short *)GDSP_FM_DSP1_PC_REG;
unsigned short *dsp1_pc_start_reg    = (unsigned short *)GDSP_FM_DSP1_PC_START_REG;
unsigned short *dsp2_pc_reg          = (unsigned short *)GDSP_FM_DSP2_PC_REG;
unsigned short *dsp2_pc_start_reg    = (unsigned short *)GDSP_FM_DSP2_PC_START_REG;
unsigned short *dsp_main_ctrl_reg    = (unsigned short *)GDSP_FM_DSP_MAIN_CTRL_REG;

/*===========================Local Function Prototypes=======================================*/  


unsigned short* GenDspDataAddress_to_Cr16(GdspCoreNumberType gDspCoreNr,  FM_DSP_PTR_TYPE addr );
FM_DSP_PTR_TYPE Cr16_to_GenDspDataAddress(GdspCoreNumberType gDspCoreNr,  unsigned short* addr );
FM_DSP_PTR_TYPE Cr16_to_GenDspCodeAddress(GdspCoreNumberType gDspCoreNr,  unsigned long* addr );


unsigned short LdoAddressToIndex(unsigned short* cr16_data_address, unsigned long** code_offset);
unsigned long FunctionIndexToCallInst(unsigned char jumptable_index);
GdspReturnCode GdspWait(CONTEXT_TYPE context_id);
unsigned short GdspDsp1Running(void);
unsigned short GdspDsp2Running(void);
unsigned short IndexToContext(unsigned short index);
GdspCoreNumberType IndexToDsp(unsigned short index);
unsigned char ContextIdToContext(CONTEXT_TYPE context_id);
GdspReturnCode InsertCode(unsigned short admin_index,const unsigned long* function_block_code,unsigned short codesize, unsigned short *datapointer, unsigned char context, unsigned char skip_relative_calc);
unsigned short FmGetDataSize(unsigned short *datapointer);
void FmFreeData(GdspCoreNumberType gDspCoreNr, unsigned short *datapointer);
unsigned short *FmAllocData(GdspCoreNumberType gDspCoreNr, unsigned short datasize);



/*==========================Implementation of Gdsp Function Manager API=======================================*/


GdspReturnCode GdspStart(unsigned short* ldo_address)
/****************************************************************************
* DESCRIPTION:  
****************************************************************************/
{
    unsigned short  admin_index;
    unsigned long*  code_ptr;
    admin_index = LdoAddressToIndex(ldo_address,&code_ptr);

    if(BS_FREE == FmAdmin[admin_index].block_free)
    {
        FM_ASSERT_ERROR(0);
        return GDSP_INVALID_PARAMETER;
    }

    if (MAX_FM_ADMIN_BLOCKS>admin_index)
    {
      if (0 < FmAdmin[admin_index].code_size) // If block has code
      {
          #if  (MAX_NO_FM_USER_FUNCTIONS > 0)
          if (FmAdmin[admin_index].function_index & 0x1)  // If uneven index jump to user function
          {
             unsigned short user_fn_nr;
             GdspCoreNumberType dsp_nr;

             dsp_nr = IndexToDsp(admin_index);

             user_fn_nr = (unsigned short)INDEX_TO_USER_FN(FmAdmin[admin_index].function_index); 
             *code_ptr = GDSP_32BITOPCODE(CALL_INSTR, Cr16_to_GenDspCodeAddress(dsp_nr,&FmDspAdmin[dsp_nr].user_jumptable[user_fn_nr]));
          }
          else
          #endif
          {
             // Write in one 32bit instruction
             *code_ptr = FunctionIndexToCallInst((unsigned char)FmAdmin[admin_index].function_index);
          }
      }
      return GDSP_SUCCESS;
    }
    else
    {
      FM_ASSERT_ERROR(0);
      return GDSP_INVALID_PARAMETER;
    }
}


void GdspConnect(unsigned short* destination_address, unsigned short* source_address)
/****************************************************************************
* DESCRIPTION:  
****************************************************************************/
{
  // assign destination address (in DSP mem space (shorts))  
  // check if destination is on DSP 1 or DSP 2, assume that 
  GdspCoreNumberType dsp_nr;
  
  if (destination_address <= (unsigned short*) GDSP_FM_SHARED_RAM1_END)
  {
    dsp_nr = GDSP_CORE1;
  }
  else
  {
    dsp_nr = GDSP_CORE2;
  }
  *destination_address = (unsigned short)(Cr16_to_GenDspDataAddress(dsp_nr,(unsigned short*)source_address)); 
}


GdspReturnCode GdspStop(unsigned short* ldo_address)
/****************************************************************************
* DESCRIPTION:  
****************************************************************************/
{
    unsigned short  admin_index,context;
    unsigned long*  code_ptr;
    admin_index = LdoAddressToIndex(ldo_address,&code_ptr);

    if(BS_FREE == FmAdmin[admin_index].block_free)
    {
        FM_ASSERT_ERROR(0);
        return GDSP_INVALID_PARAMETER;
    }

    if ((MAX_FM_ADMIN_BLOCKS>admin_index) && (0 < FmAdmin[admin_index].code_size))
    {
      // Write in one 32bit instruction
      *code_ptr = (((unsigned long )((unsigned long)NOP_INSTR<<16)&0xFFFF0000)|(JADR9_INSTR | ((FmAdmin[admin_index].code_size<<1)-1)));

      context = IndexToContext(admin_index);
      GdspWait(FmContextAdmin[context].context_id);
      return GDSP_SUCCESS;
    }
    else
    {
      FM_ASSERT_ERROR(0);
      return GDSP_INVALID_PARAMETER;
    }
}


GdspReturnCode RemoveCode(unsigned short admin_index,unsigned long* code_ptr, unsigned short context)
/****************************************************************************
* DESCRIPTION:  
****************************************************************************/
{
  unsigned short i,k,code_offset,saved_last_index;
  unsigned long  *ja_codepointer=0;

  if (admin_index == FmContextAdmin[context].last_active_index) // If this block is marked as the last active block insert a JA Start/Exit instead of bypass
  {
    saved_last_index = FmContextAdmin[context].last_active_index;

    FmContextAdmin[context].last_active_index = FmContextAdmin[context].start_index; // In case no active blocks were found, start index is the first
    if (admin_index>0)
    {
      i=admin_index;
      while(i > FmContextAdmin[context].start_index)
      {
        i--;
        if (BS_ALLOCATED == FmAdmin[i].block_free)
        {
          FmContextAdmin[context].last_active_index = i;  // The new last acive block      
          break;
        }
      }
    }
    if (FmContextAdmin[context].last_active_index < (FmContextAdmin[context].end_index-1))
    {
      code_offset = 0;
      for(i=FmContextAdmin[context].start_index; i<=FmContextAdmin[context].last_active_index; i++) // From the above we now that the "next" block is free
      {
        code_offset = code_offset + (unsigned short)FmAdmin[i].code_size;
      }
      ja_codepointer = (unsigned long*)(FmContextAdmin[context].code_start_address + code_offset);
      *ja_codepointer = FmContextAdmin[context].JaStartExitInst;         
    }
    // Remove the old JA Start, overwrite with JADR9
    if (saved_last_index < (FmContextAdmin[context].end_index-1))
    {
      for (k=(saved_last_index+1);k<(FmContextAdmin[context].end_index-1);k++)
      {
        if (0 < FmAdmin[k].code_size)
        {
          if (MAX_CODE_BLOCK != FmAdmin[k].code_size) // if next block is not allocated then overwrite Ja else leave JA in the code 
          {
            code_offset = 0;
            for(i=FmContextAdmin[context].start_index; i<k; i++)
            {
              code_offset = code_offset + (unsigned short)FmAdmin[i].code_size;
            }
            ja_codepointer = (unsigned long*)(FmContextAdmin[context].code_start_address + code_offset);
            *ja_codepointer = (((unsigned long )((unsigned long)NOP_INSTR<<16)&0xFFFF0000)|(JADR9_INSTR | ((FmAdmin[k].code_size<<1)-1)));         
          }
          break;
        }
      }
    }  
  }

  // First deactivate block
  if(ja_codepointer != code_ptr)  // If the jump start/exit has been written here, then do not overwrite with jump relative
  {
    
    *code_ptr++ = (((unsigned long )((unsigned long)NOP_INSTR<<16)&0xFFFF0000)|(JADR9_INSTR | ((FmAdmin[admin_index].code_size<<1)-1)));
  }
  else
  {
    // increment to point to next valid 32 bit instruction
    code_ptr++; 
  }
  // then wait for safe execution
  GdspWait(FmContextAdmin[context].context_id);
  // Then fill block with NOPs
  for (i=1;i<FmAdmin[admin_index].code_size;i++)
  {
    *code_ptr++ = (((unsigned long )((unsigned long)NOP_INSTR<<16)&0xFFFF0000)|(NOP_INSTR));
  }
  return GDSP_SUCCESS;
}


GdspReturnCode GdspRemove(unsigned short* ldo_address)
/****************************************************************************
* DESCRIPTION:  
****************************************************************************/
{
    unsigned short  admin_index;
    unsigned short  context;
    unsigned long   *code_ptr=0;

    admin_index = LdoAddressToIndex(ldo_address,&code_ptr);

    if(BS_FREE == FmAdmin[admin_index].block_free)
    {
        FM_ASSERT_ERROR(0);
        return GDSP_INVALID_PARAMETER;
    }

    if (MAX_FM_ADMIN_BLOCKS>admin_index)
    {
      context = IndexToContext(admin_index);
      // if active code
      if (0 < FmAdmin[admin_index].code_size)
      {
        #if  (MAX_NO_FM_USER_FUNCTIONS > 0)
        if (FmAdmin[admin_index].function_index & 0x01) // if user function
        {
            unsigned short user_fn_nr;
            GdspCoreNumberType dsp_nr;

            dsp_nr = IndexToDsp(admin_index);

            user_fn_nr = (unsigned short)INDEX_TO_USER_FN(FmAdmin[admin_index].function_index); 
            FmDspAdmin[dsp_nr].UserFnAdmin[user_fn_nr]--;  // decrement number of instances, if 0 then remove from jumptable
            if (GDSP_USERFN_FREE == FmDspAdmin[dsp_nr].UserFnAdmin[user_fn_nr])
            {
              FmDspAdmin[dsp_nr].user_jumptable[user_fn_nr] =  GDSP_32BITOPCODE(RTS_INSTR,NOP_INSTR); // default JT to RTS
            }
        }
        #endif

        if (GDSP_SUCCESS != RemoveCode(admin_index,code_ptr,context))
        {
          FM_ASSERT_ERROR(0);
          return GDSP_NO_SUCCESS;
        }
      }
      if(!FmAdmin[admin_index].static_mem)
      {        
        FmFreeData(IndexToDsp(admin_index),GenDspDataAddress_to_Cr16(IndexToDsp(admin_index), (FM_DSP_PTR_TYPE)FmAdmin[admin_index].data_ptr));
      }
      FmAdmin[admin_index].data_ptr = FM_DSP_NULL_PTR; // clr pointer
      // Mark Block as free
      FmAdmin[admin_index].block_free = BS_FREE; 
      // Defragment the DSP code
      // Here a defragmentation of the DSP code could be implemented
      return GDSP_SUCCESS;
    }
    else
    {
      FM_ASSERT_ERROR(0);
      return GDSP_INVALID_PARAMETER;
    }
}



unsigned short GdspFindFreeIndex(unsigned short codesize, unsigned char context)
/****************************************************************************
* DESCRIPTION:  
****************************************************************************/
{
  unsigned short i;
  unsigned short free_index=MAX_FM_ADMIN_BLOCKS;
  unsigned short min_free_code = (MAX_CODE_BLOCK+1);
  
  if (no_contexts <= context)
    return MAX_FM_ADMIN_BLOCKS; // Invalid context
  // Find an empty block in this context
  for (i=FmContextAdmin[context].start_index;i<FmContextAdmin[context].end_index;i++)
  {    
    if (FmAdmin[i].block_free)
    {
        if (FmAdmin[i].code_size >= codesize) // is there room for code in this block too
        {
          if (FmAdmin[i].code_size < min_free_code) // better code fit
          {
            min_free_code = (unsigned short)FmAdmin[i].code_size;
            free_index = i;
          }
        }
        if((MAX_CODE_BLOCK+1) == min_free_code) // If no other code block was found before this end block
        {
          free_index = i;
        }
        
    }
    if (codesize == min_free_code)
    {
       // Perfect fit do not search any further
      break;
    }
  }
  return free_index;
}


GdspReturnCode GdspAddStaticData(const unsigned long* function_block_code, unsigned short codesize, unsigned short *datapointer, CONTEXT_TYPE context_id)
/****************************************************************************
* DESCRIPTION:  
****************************************************************************/
{
  unsigned short free_index;
  unsigned char  context;

  context = ContextIdToContext(context_id);
  if (no_contexts <= context)
  {
    FM_ASSERT_ERROR(0);
    return GDSP_INVALID_PARAMETER;  
  }

  // Get a free index. 
  free_index = GdspFindFreeIndex(codesize,context);

  if (FmContextAdmin[context].end_index > free_index) //Found a free block 
  {
    FmAdmin[free_index].block_free = BS_ALLOCATED;  // Mark block as alocated
   
    if (MAX_CODE_BLOCK == FmAdmin[free_index].code_size) // If first time alloc then overwrite code_size otherwise leave untouched
    {      
      FmAdmin[free_index].code_size = codesize; // Set this block to the new code size
      FmContextAdmin[context].max_code_size = FmContextAdmin[context].max_code_size + codesize;  // Sum code size. Used to see how code ram is used in each context
      FmContextAdmin[context].max_index      = free_index;// Last active index.   Used to set the max number of context blocks  
    }
    FmAdmin[free_index].static_mem = 1;                                      // Mark as static
  
    FmAdmin[free_index].data_ptr  = Cr16_to_GenDspDataAddress(IndexToDsp(free_index),datapointer); // For static memory store dataaddress in data_size

    if (codesize)
    {
      if (GDSP_SUCCESS != InsertCode(free_index, function_block_code, codesize, datapointer,context,0)) 
      {
        FM_ASSERT_ERROR(0);
        return GDSP_NO_SUCCESS;
      }
    }

    return GDSP_SUCCESS;
  }
  else
  {
    FM_ASSERT_ERROR(0);
    return GDSP_NO_SUCCESS;
  }
}

static GdspReturnCode GdspAddUserFnCommon(unsigned long* user_code, unsigned short **datapointer, unsigned short data_size, CONTEXT_TYPE context_id)
/****************************************************************************
* DESCRIPTION:  
****************************************************************************/
{
  #if  (MAX_NO_FM_USER_FUNCTIONS > 0)
  unsigned long jump_to_user_code[2];
  userfn_admin_type userfn_nr;
  unsigned short user_code_gdsp_address; 
  GdspCoreNumberType dsp_nr;

  if (GDSP_DSP2_BACKGROUND_CONTEXT > context_id)
  {
    dsp_nr = GDSP_CORE1;
  }
  else
  {
    dsp_nr = GDSP_CORE2;
  }

  user_code_gdsp_address = (unsigned short)Cr16_to_GenDspCodeAddress(dsp_nr,user_code);


  // Find out if user function has been added - in that case this is just another instance
  for (userfn_nr=0;userfn_nr<MAX_NO_FM_USER_FUNCTIONS;userfn_nr++)
  {
      if (GDSP_USERFN_FREE != FmDspAdmin[dsp_nr].UserFnAdmin[userfn_nr])
      {
        if (user_code_gdsp_address == (FmDspAdmin[dsp_nr].user_jumptable[userfn_nr]>>16))
        {
          // Already added so use call the same function again
          break;
        }       
      }
  }

  if (MAX_NO_FM_USER_FUNCTIONS == userfn_nr)
  {
    for (userfn_nr=0;userfn_nr<MAX_NO_FM_USER_FUNCTIONS;userfn_nr++)
    {
      if (GDSP_USERFN_FREE == FmDspAdmin[dsp_nr].UserFnAdmin[userfn_nr])
      {
        break; // Found a free user function entry
      }
    }
  }

  if (MAX_NO_FM_USER_FUNCTIONS > userfn_nr)
  {
    if (GDSP_USERFN_FREE == FmDspAdmin[dsp_nr].UserFnAdmin[userfn_nr])
    {
      // put this address in the UserJT Cr16_to_GenDspCodeAddress(user_code)
      FmDspAdmin[dsp_nr].user_jumptable[userfn_nr] = GDSP_32BITOPCODE(JA_INSTR, user_code_gdsp_address);    
    }

    FmDspAdmin[dsp_nr].UserFnAdmin[userfn_nr]++;  // Count how many times this user function is added - used to see when to remove it from 

    // build small program to call user code, and then call AddStatic
    jump_to_user_code[0] = GDSP_32BITOPCODE(CALL_INSTR, USER_FN_TO_INDEX(userfn_nr));
    jump_to_user_code[1] = GDSP_32BITOPCODE(LDO_INSTR,0);     // 0 means datapointer + 0

    if(0 != *datapointer)
    {
      return GdspAddStaticData((const unsigned long*) jump_to_user_code, sizeof(jump_to_user_code)/4, *datapointer, context_id);
    }
    else
    {
      return GdspAdd((const unsigned long*) jump_to_user_code, sizeof(jump_to_user_code)/4, datapointer, data_size, context_id);
    }
  }
  else
  {
    FM_ASSERT_ERROR(0);
    return GDSP_NO_SUCCESS;
  }
  #else
    FM_ASSERT_ERROR(0);
    return GDSP_NO_SUCCESS;
  #endif
}


GdspReturnCode GdspAddUserFn(unsigned long* user_code, unsigned short *datapointer, CONTEXT_TYPE context_id)
/****************************************************************************
* DESCRIPTION:  
****************************************************************************/
{
  return GdspAddUserFnCommon(user_code,&datapointer,0,context_id);
}

GdspReturnCode GdspAddUserFnDynamicData(unsigned long* user_code, unsigned short **datapointer, unsigned short datasize , CONTEXT_TYPE context_id)
/****************************************************************************
* DESCRIPTION:  
****************************************************************************/
{
  *datapointer = 0;
  return GdspAddUserFnCommon(user_code,datapointer,datasize,context_id);
}

unsigned char gdsplasterror=0;
unsigned short totalcodesize=0;

GdspReturnCode GdspAdd(const unsigned long* function_block_code, unsigned short codesize, unsigned short **datapointer, unsigned short datasize, CONTEXT_TYPE context_id)
/****************************************************************************
* DESCRIPTION:  
****************************************************************************/
{
	  char *ptr;
  unsigned char  return_code = GDSP_NO_SUCCESS;
  unsigned char  context;
  unsigned short free_index=MAX_FM_ADMIN_BLOCKS;
  gdsplasterror=0;
  context = ContextIdToContext(context_id);
  /* ptr = StringPrint(StatusString, "[");
   ptr = StrPrintHexWord(ptr, codesize);
   ptr = StringPrint(ptr, ",");
   ptr = StrPrintHexWord(ptr, datasize);
  ptr = StringPrint(ptr, "]");
  PrintStatus(0, StatusString);*/
  if (no_contexts <= context)
  {
    FM_ASSERT_ERROR(0);
    gdsplasterror=1;
    return GDSP_INVALID_PARAMETER;  
  }

  // Get a free context from codesize and context
  free_index = GdspFindFreeIndex(codesize,context);
  if (free_index==MAX_FM_ADMIN_BLOCKS)
	    PrintStatus(0,"MAX_FM_ADMIN_BLOCKS reached");

  /*ptr = StringPrint(StatusString, "GdspAdd!free_index [");
  ptr = StrPrintHexByte(ptr, free_index);
  ptr = StringPrint(ptr, "]");
  PrintStatus(0, StatusString);*/
  if (FmContextAdmin[context].end_index > free_index) //Found a free block 
  {    
    FmAdmin[free_index].block_free = BS_ALLOCATED;  // Mark block as alocated
   
    if (MAX_CODE_BLOCK == FmAdmin[free_index].code_size) // If first time alloc then overwrite code_size otherwise leave untouched
    {      
      FmAdmin[free_index].code_size = codesize; // Set this block to the new code size
      FmContextAdmin[context].max_code_size = FmContextAdmin[context].max_code_size + codesize;  // Sum code size. Used to see how code ram is used in each context
      FmContextAdmin[context].max_index     = free_index;// Last active index.   Used to set the max number of context blocks  
    }
    //else leave the data sizes in their original size, because size is used to calculate pointers
    //{
    //}
    FmAdmin[free_index].static_mem = 0;  // mark block as dynamic

    // Get pointer to struct in shared ram
    /*ptr = StringPrint(StatusString, "GdspAdd!FmAllocData [");
    ptr = StrPrintHexByte(ptr, datasize);
    ptr = StringPrint(ptr, "]");
    PrintStatus(0, StatusString);*/
    totalcodesize+=codesize;
    *datapointer = FmAllocData(IndexToDsp(free_index),datasize);
    if (0 == *datapointer)
    {
      FM_ASSERT_ERROR(0);
      ptr = StringPrint(StatusString, "GdspAdd!FmAllocData [");
      ptr = StrPrintHexWord(ptr, datasize);
      ptr = StringPrint(ptr, ",");
      ptr = StrPrintHexWord(ptr, IndexToDsp(free_index));
      
      ptr = StringPrint(ptr, "]");
      PrintStatus(0, StatusString);
      gdsplasterror=3;
      return GDSP_NO_SUCCESS; // return NO_SUCCES
    }
    
    FmAdmin[free_index].data_ptr = Cr16_to_GenDspDataAddress(IndexToDsp(free_index),*datapointer);

    /*ptr = StringPrint(StatusString, "GdspAdd!codesize [");
    ptr = StrPrintHexByte(ptr, codesize);
    ptr = StringPrint(ptr, "]");
    PrintStatus(0, StatusString);*/
    if (codesize)
    {
      // Insert code
      if (GDSP_SUCCESS != InsertCode(free_index, function_block_code, codesize, *datapointer,context,0))
      {
        FM_ASSERT_ERROR(0);
        ptr = StringPrint(StatusString, "InsertCode [");
        ptr = StrPrintHexWord(ptr, codesize);
        ptr = StringPrint(ptr, ",");
        ptr = StrPrintHexWord(ptr, IndexToDsp(free_index));
       
        ptr = StringPrint(ptr, "]");
        PrintStatus(0, StatusString);
        gdsplasterror=4;
        return GDSP_NO_SUCCESS;
      }
    }
    return_code = GDSP_SUCCESS;
  }
  else
  {
    FM_ASSERT_ERROR(0);
    PrintStatus(0, "no Free size!");
    gdsplasterror=5;
    return_code = GDSP_NO_SUCCESS;
  }
  return return_code;
}


GdspReturnCode GdspChangeContext(unsigned short *datapointer, CONTEXT_TYPE new_context_id)
/****************************************************************************
* DESCRIPTION:  
****************************************************************************/
{
  unsigned short admin_index,free_index;
  unsigned long  *code_ptr;
  unsigned char  context;
  FM_DSP_PTR_TYPE tmp_datapointer;
  GdspReturnCode return_code = GDSP_NO_SUCCESS;

  admin_index = LdoAddressToIndex(datapointer,&code_ptr);

  if(BS_FREE == FmAdmin[admin_index].block_free)
  {
      FM_ASSERT_ERROR(0);
      return GDSP_INVALID_PARAMETER;
  }

  context = ContextIdToContext(new_context_id);
  if (no_contexts <= context)
  {
    FM_ASSERT_ERROR(0);
    return GDSP_INVALID_PARAMETER;  
  }

  if (IndexToContext(admin_index) == context)  // already in this context return succes
  {
    return GDSP_SUCCESS;  
  }

  if (0 < FmAdmin[admin_index].code_size)
  {
    GdspStop(datapointer);
  }

  // Get a free index from codesize and new context
  free_index = GdspFindFreeIndex((unsigned short)FmAdmin[admin_index].code_size,context);

  if (FmContextAdmin[context].end_index > free_index) //Found a free block 
  {    
    FmAdmin[free_index].block_free = BS_ALLOCATED;  // Mark block as alocated
   
    if (MAX_CODE_BLOCK == FmAdmin[free_index].code_size) // If first time alloc then overwrite code_size otherwise leave untouched
    {      
      FmAdmin[free_index].code_size = FmAdmin[admin_index].code_size; // Set this block to the new code size
      FmContextAdmin[context].max_code_size = FmContextAdmin[context].max_code_size + (unsigned short)FmAdmin[admin_index].code_size;  // Sum code size. Used to see how code ram is used in each context
      FmContextAdmin[context].max_index     = free_index;// Last active index.   Used to set the max number of context blocks  
    }
    //else leave the data sizes in their original size, because size is used to calculate pointers
    //{ 
    //}
    if (0 < FmAdmin[admin_index].code_size)
    {
      // Insert code
      if (GDSP_SUCCESS != InsertCode(free_index, code_ptr, (unsigned short)FmAdmin[admin_index].code_size, datapointer,context,1))
      {
        FM_ASSERT_ERROR(0);
        return GDSP_NO_SUCCESS;
      }
    }

    // Remove the old code 
    if (0 < FmAdmin[admin_index].code_size)
    {
      if (GDSP_SUCCESS != RemoveCode(admin_index,code_ptr,IndexToContext(admin_index)))
      {
        FM_ASSERT_ERROR(0);
        return GDSP_NO_SUCCESS;
      }
    }
    // Copy relevant old to new admin parameters
    FmAdmin[free_index].static_mem     = FmAdmin[admin_index].static_mem;
    FmAdmin[free_index].function_index = FmAdmin[admin_index].function_index;

    // Swap datapointers
    tmp_datapointer = FmAdmin[admin_index].data_ptr;
    FmAdmin[admin_index].data_ptr = FM_DSP_NULL_PTR; // clr pointer
    FmAdmin[free_index].data_ptr = tmp_datapointer;
    
    // Mark old block as free
    FmAdmin[admin_index].block_free = BS_FREE; 
    return_code = GDSP_SUCCESS;
  }
  else
  {
    FM_ASSERT_ERROR(0);
    return_code = GDSP_NO_SUCCESS;
  }
  return return_code;
}


GdspReturnCode GdspTriggerContext(CONTEXT_TYPE context_id)
/****************************************************************************
* DESCRIPTION:  
****************************************************************************/
{
  #ifdef GDSP_FRAMEBASED_BACKGROUND_TASK
  unsigned short context;

  if(GDSP_DSP1_BACKGROUND_CONTEXT == context_id)
  {
    for( context=0; context < no_contexts; context++ )
    {
      if(FmContextAdmin[context].context_id == context_id)
      {
        break;
      }
    }
    if (context<no_contexts)
    {
      if (DSP_CONTEXT_RUN == *FmContextAdmin[context].ContextTriggerFlag) // Already running == overflow
      {
        FM_ASSERT_ERROR(0);
        return GDSP_NO_SUCCESS;
      }
      else
      {
        *FmContextAdmin[context].ContextTriggerFlag = DSP_CONTEXT_RUN;
        return GDSP_SUCCESS;
      }
    }

  }
  FM_ASSERT_ERROR(0);
  return GDSP_INVALID_PARAMETER;
  #else 
  if (context_id)
  {
  }; // Remove warning.

  FM_ASSERT_ERROR(0);
  return GDSP_INVALID_PARAMETER;
  #endif
}

unsigned char lastinit_error=0;
GdspReturnCode GdspInit(GDSP_INIT_STRUCT init)
/****************************************************************************
* DESCRIPTION:  
****************************************************************************/
{
  unsigned short i,j,k;
  unsigned long  *dsp1_irq_jt_start_addr=0;
  unsigned long  *dsp2_irq_jt_start_addr=0;
  unsigned char  interrupt_mask=0;
  unsigned short number_of_cores=0;

  no_contexts = init.no_contexts;

  if (MAX_NO_FM_CONTEXTS < init.no_contexts) 
  {
     FM_ASSERT_ERROR(0);
     lastinit_error=1;
     return GDSP_INVALID_PARAMETER;
  }


  for( i=0; i < init.no_contexts; i++ )
  {
    FmContextAdmin[i].code_start_address  = init.dsp_context_memory_config[i].function_manager_codemem_start;
    FmContextAdmin[i].code_end_address    = init.dsp_context_memory_config[i].function_manager_codemem_end;
    FmContextAdmin[i].context_id          = init.dsp_context_memory_config[i].context_id;
    
    // Check if room for minimum context code space 
    if (GDSP_DSP1_BACKGROUND_CONTEXT==FmContextAdmin[i].context_id || GDSP_DSP2_BACKGROUND_CONTEXT == FmContextAdmin[i].context_id)
    {
      if ((FmContextAdmin[i].code_end_address + 1) < (FmContextAdmin[i].code_start_address+GDSP_MINIMUM_BACKGRD_CODE_SPACE))
      {
        FM_ASSERT_ERROR(0);
        lastinit_error=2;
        return GDSP_INVALID_PARAMETER;
      }
    }
    else
    {
      if ((FmContextAdmin[i].code_end_address + 1) < (FmContextAdmin[i].code_start_address+GDSP_MINIMUM_CONTEXT_CODE_SPACE))
      {
        FM_ASSERT_ERROR(0);
        lastinit_error=3;
        return GDSP_INVALID_PARAMETER;
      }
    }    

    if (0 < i)
    {
      FmContextAdmin[i].start_index       = FmContextAdmin[i-1].end_index;
    }
    else
    {
      FmContextAdmin[i].start_index       = 0;

    }

    for (k=0;k<GDSP_DSP_MAX_CONTEXT;k++)
    {
      if (FmContextAdmin[i].context_id == MaxContextIndexConvertTable[k].context_id)
      {
        break;
      }
    }
    if (GDSP_DSP_MAX_CONTEXT == k)
    {
      FM_ASSERT_ERROR(0);
      lastinit_error=4;
      return GDSP_INVALID_PARAMETER;
    }
    FmContextAdmin[i].end_index  = FmContextAdmin[i].start_index + MaxContextIndexConvertTable[k].max_context_blocks;    
    
    FmContextAdmin[i].last_active_index   = FmContextAdmin[i].start_index;
    FmContextAdmin[i].interrupt_source    = init.dsp_context_memory_config[i].interrupt_source;

    if (DSP_NO_INT > FmContextAdmin[i].interrupt_source)
    {
      interrupt_mask |= (0x1 << FmContextAdmin[i].interrupt_source);
      interrupt_mask = interrupt_mask & 0x1F;
    }
 
    if ((PTR_TYPE)FmContextAdmin[i].code_start_address & (PTR_TYPE) 0x3)
    {
      // Code address not 32 bit alligned
      FmContextAdmin[i].code_start_address = (unsigned long*)(((PTR_TYPE)FmContextAdmin[i].code_start_address+0x3)&(PTR_TYPE)(~0x3));
    }
    if ((PTR_TYPE)FmContextAdmin[i].code_end_address & (PTR_TYPE) 0x3)
    {
      // Code address not 32 bit alligned
      FmContextAdmin[i].code_end_address = (unsigned long*)(((PTR_TYPE)FmContextAdmin[i].code_end_address)&(PTR_TYPE)(~0x3));
    }

    // Get Stack Pointer for each DSP
    if (GDSP_DSP1_BACKGROUND_CONTEXT==FmContextAdmin[i].context_id || GDSP_DSP2_BACKGROUND_CONTEXT == FmContextAdmin[i].context_id)
    {
      unsigned char dsp_nr = (GDSP_DSP2_BACKGROUND_CONTEXT == FmContextAdmin[i].context_id); // 0 if DSP 1 and 1 if DSP 2

      FmDspAdmin[dsp_nr].data_start_address  = init.dsp_context_memory_config[i].function_manager_datamem_start;
      if ((PTR_TYPE)FmDspAdmin[dsp_nr].data_start_address & (PTR_TYPE)0x1) 
      {
        // Data start address not 16 bit alligned
        FmDspAdmin[dsp_nr].data_start_address = (unsigned short*)((unsigned char*)FmDspAdmin[dsp_nr].data_start_address+1);
      }

      FmDspAdmin[dsp_nr].data_end_address    = init.dsp_context_memory_config[i].function_manager_datamem_end;
      if ((PTR_TYPE)FmDspAdmin[dsp_nr].data_end_address & (PTR_TYPE)0x1) 
      {
        // Data end address not 16 bit alligned
        FmDspAdmin[dsp_nr].data_end_address = (unsigned short*)((unsigned char*)FmDspAdmin[dsp_nr].data_end_address-1);
      }

      FmDspAdmin[dsp_nr].stack_end_address   = init.dsp_context_memory_config[i].function_manager_stack_end;
      if ((PTR_TYPE)FmDspAdmin[dsp_nr].stack_end_address & (PTR_TYPE) 0x3) 
      {
        // Stack address not 32 bit alligned
        FmDspAdmin[dsp_nr].stack_end_address = (unsigned short*)(((PTR_TYPE)FmDspAdmin[dsp_nr].stack_end_address)&(PTR_TYPE)(~0x3));
      }
    }
  }

  // Find BACKGROUND_TASKS first
	for( i=0; i < init.no_contexts; i++ )
  {
    switch (FmContextAdmin[i].context_id)
    {
      case  GDSP_DSP1_BACKGROUND_CONTEXT:
      case  GDSP_DSP2_BACKGROUND_CONTEXT:
        {
          unsigned long  *bkgrd_start_addr,*bkgrd_end_addr;
          unsigned short dsp_nr=0;
          unsigned long  **dsp_irq_jt_start_addr;
          unsigned short *dsp_pc_start_reg;

        /* HM Uncommented to make sure it is possible to make a interrupt from background task */
            if (DSP_NO_INT != FmContextAdmin[i].interrupt_source)
          {
             FM_ASSERT_ERROR(0);
             lastinit_error=5;
             return GDSP_INVALID_PARAMETER; // Makes no sense to set interrrupt source for background task
          }

          if (GDSP_DSP1_BACKGROUND_CONTEXT == FmContextAdmin[i].context_id)
          {
            dsp_nr = 0;
            dsp_irq_jt_start_addr = &dsp1_irq_jt_start_addr;
            dsp_pc_start_reg = dsp1_pc_start_reg;
            number_of_cores++;
          }
          else 
          {
            dsp_nr = 1;
            dsp_irq_jt_start_addr = &dsp2_irq_jt_start_addr;
            dsp_pc_start_reg = dsp2_pc_start_reg;
            number_of_cores++;
          }


          #ifndef PCCOMPILE
            *dsp_pc_start_reg = Cr16_to_GenDspCodeAddress(dsp_nr,FmContextAdmin[i].code_start_address); // Set start register equal to the very first code context address
          #endif

          #if (MAX_NO_FM_CONTEXTS > 1) // If only backgroundtask then do not waste codespace on the Irq-JT.
            // Place the interrupt jumptable at end of background task context:            
            *dsp_irq_jt_start_addr = FmContextAdmin[i].code_end_address -(sizeof(gdsp_default_irq_jt_code)/4);

            // Find a 0xF address alignmenet address at end because IRQ jumptable must be on a 0xF alligned address   
            #ifndef PCCOMPILE
            *dsp_irq_jt_start_addr = (unsigned long*)((unsigned long)*dsp_irq_jt_start_addr & (unsigned long)~0x1F);
            #endif
            
            FmContextAdmin[i].code_end_address = *dsp_irq_jt_start_addr;
            for (j=0;j<sizeof(gdsp_default_irq_jt_code)/4;j++)
            {
              *FmContextAdmin[i].code_end_address++ = gdsp_default_irq_jt_code[j]; // Copy the default interrupt jump table              
              FmContextAdmin[i].max_code_size++;              
            }
            FmContextAdmin[i].code_end_address = *dsp_irq_jt_start_addr - 1; // Set new context end address
          #else
            *dsp_irq_jt_start_addr = 0; // Remove warning
          #endif

          #if  (MAX_NO_FM_USER_FUNCTIONS > 0)  // Allocate a user function jumptable in backgrund code             
            for (j=0;j<MAX_NO_FM_USER_FUNCTIONS;j++)
            {
              FmDspAdmin[dsp_nr].UserFnAdmin[j] = GDSP_USERFN_FREE;
              *FmContextAdmin[i].code_end_address-- = GDSP_32BITOPCODE(RTS_INSTR,NOP_INSTR); // default JT to RTS 
              FmContextAdmin[i].max_code_size++;
            }
            FmDspAdmin[dsp_nr].user_jumptable = FmContextAdmin[i].code_end_address + 1;
          #endif

          // Dsp init code:           
          // Load DSP1_IRQ_START_REG with IRQ jumptable
          #if (MAX_NO_FM_CONTEXTS > 1) // If only backgroundtask then do not waste codespace on the Irq-JT.
          *FmContextAdmin[i].code_start_address++ = GDSP_32BITOPCODE(LOAD_D2_INSTR,Cr16_to_GenDspCodeAddress(dsp_nr,*dsp_irq_jt_start_addr)); 
          // Load stack pointer - order of instructions are due to pipeline stall between load irq_jt_start_addr and store irq_jt_start_addr
          *FmContextAdmin[i].code_start_address++ = GDSP_32BITOPCODE(SP_INSTR,((unsigned short)Cr16_to_GenDspDataAddress(dsp_nr,FmDspAdmin[dsp_nr].stack_end_address) & 0xFFFE));
          *FmContextAdmin[i].code_start_address++ = GDSP_32BITOPCODE(STORE_D2_INSTR,_DSP_IRQ_START_REG);     
          *FmContextAdmin[i].code_start_address++ = GDSP_32BITOPCODE((IM_INSTR | interrupt_mask),NOP_INSTR); // Mask default all interrupt in 
          *FmContextAdmin[i].code_start_address++ = GDSP_32BITOPCODE(EI_INSTR,NOP_INSTR);      // Enable Int 
          #else
          *FmContextAdmin[i].code_start_address++ = GDSP_32BITOPCODE(SP_INSTR,((unsigned short)Cr16_to_GenDspDataAddress(dsp_nr,FmDspAdmin[dsp_nr].stack_end_address) & 0xFFFE));
          #endif

          bkgrd_start_addr = FmContextAdmin[i].code_start_address; // Save this address as it is the context starting point

          // Set code end point as end of context point
          bkgrd_end_addr = FmContextAdmin[i].code_end_address;
          // Insert JA to background start address at end of context
          *FmContextAdmin[i].code_end_address-- = GDSP_32BITOPCODE(JA_INSTR,Cr16_to_GenDspCodeAddress(dsp_nr,bkgrd_start_addr)); // Jump back to start always
          FmContextAdmin[i].max_code_size += 1;

          // If an end of frame interrupt is requested then insert IRQ before end of context
          if(init.dsp_context_memory_config[i].end_of_context_interrupt_vector)
          {           
             // Set new code end point as end of context point
             bkgrd_end_addr = FmContextAdmin[i].code_end_address;
             *FmContextAdmin[i].code_end_address-- = GDSP_32BITOPCODE(IRQ_INSTR, init.dsp_context_memory_config[i]. end_of_context_interrupt_vector);
             FmContextAdmin[i].max_code_size += 1;
          }

          // Insert init code -- code for gdsp wiat
          // Allocate 1 variable in data ram for the wait variable
          FmContextAdmin[i].WaitVariable = FmDspAdmin[dsp_nr].data_start_address++; 
          *FmContextAdmin[i].WaitVariable = DSP_UNSAFE_POINT;  // Set default to unsafe 

          #ifdef GDSP_FRAMEBASED_BACKGROUND_TASK
          // Allocate ram for ContextTriggerFlag
          FmContextAdmin[i].ContextTriggerFlag  = FmDspAdmin[dsp_nr].data_start_address++; 
          *FmContextAdmin[i].ContextTriggerFlag = DSP_CONTEXT_DONT_RUN; // Do not run
          
          // Reverse order of execution for next 3 instructions, because the are place at end of backgroundtask
          *FmContextAdmin[i].code_end_address-- = GDSP_32BITOPCODE(STORE_D2_INSTR,Cr16_to_GenDspDataAddress(dsp_nr,FmContextAdmin[i].ContextTriggerFlag));
          *FmContextAdmin[i].code_end_address-- = GDSP_32BITOPCODE(NOP_INSTR,NOP_INSTR);
          // Set new end address
          bkgrd_end_addr = FmContextAdmin[i].code_end_address;
          *FmContextAdmin[i].code_end_address-- = GDSP_32BITOPCODE(LOAD_D2_INSTR,DSP_CONTEXT_DONT_RUN);
          FmContextAdmin[i].max_code_size += 3;
          #endif

          *FmContextAdmin[i].code_start_address++ = GDSP_32BITOPCODE(LOAD_D2_INSTR,DSP_SAFE_POINT); // Set wait variable to UN-SAFE
          *FmContextAdmin[i].code_start_address++ = GDSP_32BITOPCODE(NOP_INSTR,NOP_INSTR); 
          *FmContextAdmin[i].code_start_address++ = GDSP_32BITOPCODE(STORE_D2_INSTR,Cr16_to_GenDspDataAddress(dsp_nr,FmContextAdmin[i].WaitVariable)); // Set wait variable to UN-SAFE = 0, D2 is set before WTF due to pipeline stall
          *FmContextAdmin[i].code_start_address++ = GDSP_32BITOPCODE(WTF_INSTR,NOP_INSTR); 
          *FmContextAdmin[i].code_start_address++ = GDSP_32BITOPCODE(STORE_D2_INSTR,Cr16_to_GenDspDataAddress(dsp_nr,FmContextAdmin[i].WaitVariable)); // Set wait variable to UN-SAFE = 0, D2 is set before WTF due to pipeline stall

          #ifdef GDSP_FRAMEBASED_BACKGROUND_TASK          
          *FmContextAdmin[i].code_start_address++ = GDSP_32BITOPCODE(LDC_INSTR,Cr16_to_GenDspDataAddress(dsp_nr,FmContextAdmin[i].ContextTriggerFlag));
          *FmContextAdmin[i].code_start_address++ = GDSP_32BITOPCODE(NOP_INSTR,JCAR9_INSTR | 0x0 ); 
          *FmContextAdmin[i].code_start_address++ = GDSP_32BITOPCODE(JA_INSTR,Cr16_to_GenDspCodeAddress(dsp_nr,bkgrd_start_addr)); // If flag not set then do not execute conext, jump back to start 
          // else continue -- clear flag at end of context -- which is the code before WTF
          FmContextAdmin[i].max_code_size += 8;
          #endif

          FmContextAdmin[i].JaStartExitInst    = GDSP_32BITOPCODE(JA_INSTR,Cr16_to_GenDspCodeAddress(dsp_nr, bkgrd_end_addr)); 
          // Set the very first active code address to this jump back to the WTF
          *FmContextAdmin[i].code_start_address = FmContextAdmin[i].JaStartExitInst;
          // Make sure that there is always room for a Jump back at the end of the code
          FmContextAdmin[i].code_end_address--; 
          FmContextAdmin[i].max_code_size += 11;
        }
        break;        
      default:
        break;
    }
  }


  // Then find other context
	for( i=0; i < init.no_contexts; i++ )
  {
    switch (FmContextAdmin[i].context_id)
    {
      case  GDSP_DSP1_8KHZ_CONTEXT:
      case  GDSP_DSP1_16KHZ_CONTEXT:
      case  GDSP_DSP1_32KHZ_CONTEXT:
      case  GDSP_DSP1_CR16INT_CONTEXT:
      case  GDSP_DSP1_DIPINT_CONTEXT:
      case  GDSP_DSP1_DSP2INT_CONTEXT:
      case  GDSP_DSP2_8KHZ_CONTEXT:
      case  GDSP_DSP2_16KHZ_CONTEXT:
      case  GDSP_DSP2_32KHZ_CONTEXT:
      case  GDSP_DSP2_CR16INT_CONTEXT:
      case  GDSP_DSP2_DIPINT_CONTEXT:
      case  GDSP_DSP2_DSP1INT_CONTEXT:
        {
          unsigned long *context_start_addr;
          unsigned long *context_end_addr;     
          unsigned long *dsp_irq_jt_start_addr;
          GdspCoreNumberType dsp_nr;

          if(GDSP_DSP2_BACKGROUND_CONTEXT > FmContextAdmin[i].context_id) // DSP1
          {
            if (0 == dsp1_irq_jt_start_addr)  // No background task set, so not possible to set interrupt context
            {
              FM_ASSERT_ERROR(0);
              lastinit_error=6;
              return GDSP_INVALID_PARAMETER;
            }
            dsp_irq_jt_start_addr = dsp1_irq_jt_start_addr;
            dsp_nr = GDSP_CORE1;
          }
          else
          {
            if (0 == dsp2_irq_jt_start_addr)  // No background task set, so not possible to set interrupt context
            {
              FM_ASSERT_ERROR(0);
              lastinit_error=7;
              return GDSP_INVALID_PARAMETER;
            }          
            dsp_irq_jt_start_addr = dsp2_irq_jt_start_addr;
            dsp_nr = GDSP_CORE2;
          }


          if (DSP_NO_INT <= FmContextAdmin[i].interrupt_source) // Check if interrupt source parameter is valid
          {
            FM_ASSERT_ERROR(0);
            lastinit_error=8;
            return GDSP_INVALID_PARAMETER; // Makes no sense to set interrrupt source for background task
          }

          // Allocate 1 variable in data ram for the wait variable
          FmContextAdmin[i].WaitVariable = FmDspAdmin[dsp_nr].data_start_address++; 
          *FmContextAdmin[i].WaitVariable = DSP_UNSAFE_POINT;  

          context_start_addr = FmContextAdmin[i].code_start_address;
          dsp_irq_jt_start_addr[FmContextAdmin[i].interrupt_source] = GDSP_32BITOPCODE(JA_INSTR,Cr16_to_GenDspCodeAddress(dsp_nr,context_start_addr));

          // context save
          for (j=0;j<sizeof(gdsp_context_save_code)/4;j++)
          {
            if(CND_CMP_NEG == gdsp_context_save_code[j])    // replace runime with address of irq jumptable 
            {
            *FmContextAdmin[i].code_start_address++
                = GDSP_32BITOPCODE(CND_CMP_NEG | (((unsigned short)Cr16_to_GenDspCodeAddress(dsp_nr,&dsp_irq_jt_start_addr[FmContextAdmin[i].interrupt_source])>>12) & 0xf),((unsigned short)Cr16_to_GenDspCodeAddress(dsp_nr,&dsp_irq_jt_start_addr[FmContextAdmin[i].interrupt_source])<<4));
            }
            else
            {
              *FmContextAdmin[i].code_start_address++ = gdsp_context_save_code[j];  // Increment the admin pointer to code, this will leave the init code resident in memory
            }
          }

          if (0 < FmContextAdmin[i].interrupt_source) // If not interrupt 0 then allow nesting
          {
            unsigned char IntSourceMaskTemp;
            IntSourceMaskTemp = (0x1 << FmContextAdmin[i].interrupt_source)-1;  // "1"->0x2->0x1, "2"->0x4->0x3, "3"->0x8->0x7,"4"->0x10->0xf,"5"->0x20->0x1F,
            // Mask with overall interrupt mask, so that non existing interrupts do no get enabled.
            IntSourceMaskTemp = IntSourceMaskTemp & interrupt_mask;
            if (IntSourceMaskTemp)
            {
              *FmContextAdmin[i].code_start_address++ = GDSP_32BITOPCODE((IM_INSTR | IntSourceMaskTemp),NOP_INSTR);
              *FmContextAdmin[i].code_start_address++ = GDSP_32BITOPCODE(EI_INSTR,NOP_INSTR);      // Enable Int 
            }
          }

          // Set Wait Flag to indicate that we are at the begining of the code.
          *FmContextAdmin[i].code_start_address++ = GDSP_32BITOPCODE(LOAD_D2_INSTR,DSP_SAFE_POINT); // Set wait variable
          *FmContextAdmin[i].code_start_address++ = GDSP_32BITOPCODE(NOP_INSTR,NOP_INSTR); 
          *FmContextAdmin[i].code_start_address++ = GDSP_32BITOPCODE(STORE_D2_INSTR,Cr16_to_GenDspDataAddress(dsp_nr,FmContextAdmin[i].WaitVariable)); // Set wait variable nops due to pipeline stall

          k = sizeof(gdsp_context_restore_code)/4;
          for (j=0;j<sizeof(gdsp_context_restore_code)/4;j++)
          {
            k--;
            *FmContextAdmin[i].code_end_address-- = gdsp_context_restore_code[k];  // Increment the admin pointer to code, this will leave the init code resident in memory
          }    
          *FmContextAdmin[i].code_end_address-- =  GDSP_32BITOPCODE((ISR_ACK_INSTR | (0x1 << FmContextAdmin[i].interrupt_source)),NOP_INSTR); // Ack int

          context_end_addr = FmContextAdmin[i].code_end_address+1; // Save this address as it is the context exit point
          
          FmContextAdmin[i].JaStartExitInst    = GDSP_32BITOPCODE(JA_INSTR,Cr16_to_GenDspCodeAddress(dsp_nr,context_end_addr)); 
          // Set the very first active code address to this jump to exit
          *FmContextAdmin[i].code_start_address = FmContextAdmin[i].JaStartExitInst;
        }        
        break;
      case  GDSP_DSP1_BACKGROUND_CONTEXT:
      case  GDSP_DSP2_BACKGROUND_CONTEXT:
        // already handled
        break;
      default:
        FM_ASSERT_ERROR(0);
        lastinit_error=9;
        return GDSP_INVALID_PARAMETER;
    }
  }

  // init data heap
  for( i=0; i< number_of_cores; i++ ) 
	{
    unsigned short DspDataHeapSize;
    DspDataHeapSize = (unsigned short) (FmDspAdmin[i].data_end_address - FmDspAdmin[i].data_start_address) + 1;
    DspDataHeapSize = (DspDataHeapSize-(2*FM_DSP_HEAP_ADM_SIZE)) & FM_DSP_HEAP_BLOCK_MAX; // -2*FM_DSP_HEAP_ADM_SIZE because of first and last heap admin word
    *FmDspAdmin[i].data_end_address   = FM_DSP_HEAP_END;
    *FmDspAdmin[i].data_start_address = FM_DSP_HEAP_BLOCK_FREE |  DspDataHeapSize; // Mark first block as free with max datasize
    FmDspAdmin[i].heap_free_peak      = DspDataHeapSize;
    FmDspAdmin[i].heap_free           = DspDataHeapSize;
  }
  // init administration in shared ram.
	for( i=0; i< MAX_FM_ADMIN_BLOCKS; i++ ) 
	{
	  FmAdmin[i].block_free      = BS_FREE;
    FmAdmin[i].static_mem      = 0;
    FmAdmin[i].data_ptr        = FM_DSP_NULL_PTR;
    FmAdmin[i].code_size       = MAX_CODE_BLOCK;  // Mark that this block has not yet been used   
    FmAdmin[i].function_index  = 0;
  }
  return GDSP_SUCCESS;
}

#ifdef PCCOMPILE
unsigned short *Cr16_to_GenDspCodeAddress(GdspCoreNumberType gDspCoreNr, unsigned long* addr )
/****************************************************************************
* DESCRIPTION:  Returns the DSP offset in the code segment of the CR16 address
****************************************************************************/
{
  if(gDspCoreNr);
  return (unsigned short *)addr;
}
#else
unsigned short Cr16_to_GenDspCodeAddress(GdspCoreNumberType gDspCoreNr, unsigned long* addr )
/****************************************************************************
* DESCRIPTION:  Returns the DSP offset in the code segment of the CR16 address
****************************************************************************/
{
  if (GDSP_CORE1 ==  gDspCoreNr)
  {
    if (addr <= (unsigned long*) GDSP_FM_SHARED_RAM1_END)  // This is only true for Sc14480, Sc14450 cannot execute code from ram (misuse is not detected!)
    {
      return (unsigned short)(( ((unsigned short*)addr - (unsigned short*)GDSP_FM_SHARED_RAM1_START)) + 0x4000); // becuase the pointers are short*, the subtraction gives dsp addresses
    }
    else if (addr < (unsigned long*) GDSP_FM_DSP_MC_RAM2_START)
    {
      return (unsigned short)(((unsigned short*)addr - (unsigned short* )GDSP_FM_DSP_MC_RAM1_START)); // becuase the pointers are short*, the subtraction gives dsp addresses
    }
    else
    {
      return (unsigned short)(((unsigned short*)addr - (unsigned short* )GDSP_FM_DSP_MC_RAM2_START)) + (unsigned short)0x4000; // becuase the pointers are short*, the subtraction gives dsp addresses
    }
  }
  else
  {
    if (addr < (unsigned long*) GDSP_FM_DSP_MC_RAM2_START)
    {
      return (unsigned short)(((unsigned short*)addr - (unsigned short* )GDSP_FM_DSP_MC_RAM1_START)) + (unsigned short)0x4000; // becuase the pointers are short*, the subtraction gives dsp addresses
    }
    else
    {
      return (unsigned short)(((unsigned short*)addr - (unsigned short* )GDSP_FM_DSP_MC_RAM2_START)); // becuase the pointers are short*, the subtraction gives dsp addresses
    }
  }
}
#endif
#ifdef PCCOMPILE
unsigned short *Cr16_to_GenDspDataAddress(GdspCoreNumberType gDspCoreNr,  unsigned short* addr )
/****************************************************************************
* DESCRIPTION:  
****************************************************************************/
{
  if(gDspCoreNr);
  return (unsigned short *)addr;
}
#else
unsigned short Cr16_to_GenDspDataAddress(GdspCoreNumberType gDspCoreNr,  unsigned short* addr )
/****************************************************************************
* DESCRIPTION:  
****************************************************************************/
{
  if (GDSP_CORE1 ==  gDspCoreNr)
  {
    if (addr <= (unsigned short*) GDSP_FM_SHARED_RAM1_END)
    {
      // becuase the pointers are short*, the subtraction gives dsp addresses
      return   (unsigned short)(addr - (unsigned short*)GDSP_FM_SHARED_RAM1_START); 
    }
    else
    {
      // becuase the pointers are short*, the subtraction gives dsp addresses
      return   (unsigned short)(addr - (unsigned short*)GDSP_FM_SHARED_RAM2_START) + (unsigned short)0x4000;  
    }
  }
  else
  {
    if (addr <= (unsigned short*) GDSP_FM_SHARED_RAM1_END)
    {
      // becuase the pointers are short*, the subtraction gives dsp addresses
      return   (unsigned short)(addr - (unsigned short*)GDSP_FM_SHARED_RAM1_START) + (unsigned short)0x4000; 
    }
    else
    {
      // becuase the pointers are short*, the subtraction gives dsp addresses
      return   (unsigned short)(addr - (unsigned short*)GDSP_FM_SHARED_RAM2_START);  
    }
  }
}
#endif
#ifdef PCCOMPILE
unsigned short *GenDspDataAddress_to_Cr16(GdspCoreNumberType gDspCoreNr,  unsigned short *addr)
/****************************************************************************
* DESCRIPTION:
****************************************************************************/
{
  if(gDspCoreNr);
  return (unsigned short *)addr;
}
#else
unsigned short *GenDspDataAddress_to_Cr16(GdspCoreNumberType gDspCoreNr,  unsigned short addr )
/****************************************************************************
* DESCRIPTION:
****************************************************************************/
{
  if (GDSP_CORE1 ==  gDspCoreNr)
  {
    if (addr <= (unsigned short) 0x4000)
    {
      // becuase the pointers are short*, the subtraction gives dsp addresses
      return   (unsigned short*)(addr + (unsigned short*)GDSP_FM_SHARED_RAM1_START); 
    }
    else
    {
      // becuase the pointers are short*, the subtraction gives dsp addresses      
      return   (unsigned short*)((addr - 0x4000) + (unsigned short*)GDSP_FM_SHARED_RAM2_START);  
    }
  }
  else
  {
    if (addr <= (unsigned short) 0x4000)
    {
      // becuase the pointers are short*, the subtraction gives dsp addresses
      return   (unsigned short*)(addr + (unsigned short*)GDSP_FM_SHARED_RAM2_START); 
    }
    else
    {
      // becuase the pointers are short*, the subtraction gives dsp addresses
      return   (unsigned short*)((addr - 0x4000) + (unsigned short*)GDSP_FM_SHARED_RAM1_START);  
    }
  }
}
#endif

unsigned short LdoAddressToIndex(unsigned short* cr16_data_address, unsigned long** code_offset)
/****************************************************************************
* DESCRIPTION:
****************************************************************************/
{
    unsigned char  context;    
    unsigned short i;

    FM_DSP_PTR_TYPE dsp1_data_address;
    FM_DSP_PTR_TYPE dsp2_data_address;

    dsp1_data_address = Cr16_to_GenDspDataAddress(GDSP_CORE1,cr16_data_address);
    dsp2_data_address = Cr16_to_GenDspDataAddress(GDSP_CORE2,cr16_data_address);

    for (context=0; context < no_contexts; context++)
    {
      *code_offset = FmContextAdmin[context].code_start_address;
      for(i = FmContextAdmin[context].start_index; i<FmContextAdmin[context].end_index; i++)
      {
      if ((FmAdmin[i].data_ptr == dsp1_data_address) || (FmAdmin[i].data_ptr == dsp2_data_address))
         {           
           return i;
         }
         *code_offset = *code_offset + FmAdmin[i].code_size;
      }
    }
    return MAX_FM_ADMIN_BLOCKS;    
}

GdspReturnCode GdspInitFunctionBlock(const unsigned short* block_init_struct, unsigned short* block_ramDst)
/****************************************************************************
* DESCRIPTION:
****************************************************************************/
{
  unsigned short  admin_index;
  unsigned long*  code_ptr;
  unsigned short  CtrlWord;
  unsigned short* blok_data_start_pointer;
  unsigned short* blok_data_end_pointer;
  char *ptr;
  GdspCoreNumberType dsp_nr;
 
  admin_index = LdoAddressToIndex(block_ramDst,&code_ptr);

  if(BS_FREE == FmAdmin[admin_index].block_free)
  {
      FM_ASSERT_ERROR(0);
    ptr = StringPrint(StatusString, "GdspInitFunctionBlock!block_free [");
    //ptr = StrPrintHexWord(ptr, datasize);
    //ptr = StringPrint(ptr, ",");
    //ptr = StrPrintHexWord(ptr, IndexToDsp(free_index));

    ptr = StringPrint(ptr, "]");
    PrintStatus(0, StatusString);
      return GDSP_INVALID_PARAMETER;
  }

  blok_data_start_pointer = block_ramDst;
  blok_data_end_pointer = blok_data_start_pointer + FmGetDataSize(block_ramDst);

  dsp_nr = IndexToDsp(admin_index);

  if (MAX_FM_ADMIN_BLOCKS>admin_index)
  {
    int hm_cout=0;
    CtrlWord = *block_init_struct++; // Get first CtrlWord

    while (GDSP_INIT_CTRL_END != CtrlWord)
    {
	    unsigned short length = CtrlWord & GDSP_INIT_CTRL_LENGTH_MASK;   // default, but could be interpreted differnetly later

      if (blok_data_end_pointer < block_ramDst) // writing out of bounds
      {
        if(!FmAdmin[admin_index].static_mem)
        {
          FM_ASSERT_ERROR(0);
          ptr = StringPrint(StatusString, "GdspInitFunctionBlock!static_mem [");
          //ptr = StrPrintHexWord(ptr, datasize);
          //ptr = StringPrint(ptr, ",");
          //ptr = StrPrintHexWord(ptr, IndexToDsp(free_index));

          ptr = StringPrint(ptr, "]");
          PrintStatus(0, StatusString);
          return GDSP_INVALID_PARAMETER;
        }
        // else no boundry check
      }
      hm_cout++;
      switch (GDSP_INIT_CTRL_MASK & CtrlWord)
      {
		    case GDSP_INIT_CTRL_DEFAULT: // Copy following default parameter from init struct to data ram  
			    for (;length>0;length--)
			    {
				    *block_ramDst++ = *block_init_struct++;  // Copy default parameters, not using mempy because we want to increment the pointers					
			    }
			    break;
        case GDSP_INIT_CTRL_REL_PTR_32BIT_ALIGN:
		      for (;length>0;length--)
		      {
             unsigned short relative_offset;

             relative_offset = *block_init_struct++; // Get relative offset from init struct 
             relative_offset = relative_offset + (unsigned short)Cr16_to_GenDspDataAddress(dsp_nr,blok_data_start_pointer); // add offset to absolute begin address

             if (0x1 & relative_offset) // if uneven 16bit address then increment by one 16bit address to get 32bit alignment
             {
               relative_offset = relative_offset + 1;
             }
			       *block_ramDst++ = relative_offset;
		      }
          break;
        case GDSP_INIT_CTRL_REL_PTR:  // Relative offset to ram-base address
          {
			      for (;length>0;length--)
			      {
              unsigned short relative_offset;
              relative_offset = *block_init_struct++; // Get relative offset from init struct 
				      *block_ramDst++ = relative_offset + (unsigned short)Cr16_to_GenDspDataAddress(dsp_nr,blok_data_start_pointer); // add offset to absolute begin address
			      }
          }
          break;
		    case GDSP_INIT_CTRL_PTR:
			    block_ramDst  = block_ramDst  + length;  // increment past the pointers not to be touched
			    break;
		    case GDSP_INIT_CTRL_ZERO:
			    for (;length>0;length--)
			    {
				    *block_ramDst++ = 0;
			    }			    
			    break;
        case GDSP_INIT_CTRL_FILL:
          {
            unsigned short fillvalue;
            fillvalue = *block_init_struct++;
			      for (;length>0;length--)
			      {
				      *block_ramDst++ = fillvalue;
			      }		
          }
          break;
        case GDSP_INIT_CTRL_CONST_PTR:          
			      for (;length>0;length--)
			      {
              #ifdef FM_DSP_DATA_ROM_AVAILABLE
                *block_ramDst++ = *block_init_struct++;  // Copy default parameter this is the original data rom address
              #else
                *block_ramDst++ = (unsigned short)Cr16_to_GenDspDataAddress(dsp_nr, FmGetRomTableAddress(*block_init_struct++));
              #endif
			      }
          break;
		    default:
			    // Should not happend undefined CTRL word
          FM_ASSERT_ERROR(0);
          ptr = StringPrint(StatusString, "GdspInitFunctionBlock!undefined CTRL [");
          ptr = StrPrintHexWord(ptr, CtrlWord);
          ptr = StringPrint(ptr, ",");
          ptr = StrPrintHexWord(ptr, hm_cout);

          ptr = StringPrint(ptr, "]");
          PrintStatus(0, StatusString);
          return GDSP_INVALID_PARAMETER;
			    //break;

	    }
	    CtrlWord = *block_init_struct++; // Get next CtrlWord      
	  }
    return GDSP_SUCCESS;
  }
  else
  {
    FM_ASSERT_ERROR(0);
    ptr = StringPrint(StatusString, "GdspInitFunctionBlock!GDSP_INVALID_PARAMETER [");
    //ptr = StrPrintHexWord(ptr, datasize);
    //ptr = StringPrint(ptr, ",");
    //ptr = StrPrintHexWord(ptr, IndexToDsp(free_index));

    ptr = StringPrint(ptr, "]");
    PrintStatus(0, StatusString);
    return GDSP_INVALID_PARAMETER;
  }
}

unsigned short GdspDsp1Running(void)
/****************************************************************************
* DESCRIPTION:
****************************************************************************/
{
#ifndef PCCOMPILE
  if(*dsp1_pc_start_reg != *dsp1_pc_reg)
  {
    if (0==(*dsp_main_ctrl_reg&0x300)) /*!< if main counter is turned off, then DSP is not running */
    {
      return !DSP1_RUNNIG;
    }
    else
    {
      // If PC not changed for 2 Cr16c instructions then not running
      unsigned short lDspPc;
      volatile unsigned short *tDspPc;
      volatile unsigned short testcount=2;

      tDspPc = dsp1_pc_reg;
      lDspPc= *tDspPc;
      while ((*tDspPc == lDspPc) && testcount)
        --testcount;
      if (*tDspPc == lDspPc)
      {
        return !DSP1_RUNNIG;
      }
      else
      {
        return DSP1_RUNNIG;
      }
    }
  }  
  else
#endif
  {
    return !DSP1_RUNNIG;
  }  
}

unsigned short GdspDsp2Running(void)
/****************************************************************************
* DESCRIPTION:
****************************************************************************/
{
#ifndef PCCOMPILE
  if(*dsp2_pc_start_reg != *dsp2_pc_reg)
  {
    if (0==(*dsp_main_ctrl_reg&0x300)) /*!< if main counter is turned off, then DSP is not running */
    {
      return !DSP2_RUNNIG;
    }
    else
    {
      // If PC not changed for 2 Cr16c instructions then not running
      unsigned short lDspPc;
      volatile unsigned short *tDspPc;
      volatile unsigned short testcount=2;

      tDspPc = dsp2_pc_reg;
      lDspPc= *tDspPc;
      while ((*tDspPc == lDspPc) && testcount)
        --testcount;
      if (*tDspPc == lDspPc)
      {
        return !DSP2_RUNNIG;
      }
      else
      {
        return DSP2_RUNNIG;
      }
    }
  }
  else
#endif
  {
    return !DSP2_RUNNIG;
  }  
}


unsigned short IndexToContext(unsigned short index)
/****************************************************************************
* DESCRIPTION: Convert admin index admin context
****************************************************************************/
{
  unsigned short i;
  for( i=0; i < no_contexts; i++ )
  {
    if( (FmContextAdmin[i].start_index <= index) && (FmContextAdmin[i].end_index > index))
    {
      return i;
    }
  }
  return no_contexts;
}

GdspCoreNumberType IndexToDsp(unsigned short index)
/****************************************************************************
* DESCRIPTION: Convert admin index admin dsp core number
****************************************************************************/
{
  unsigned short Context;
  
  Context = IndexToContext(index);

  if (GDSP_DSP2_BACKGROUND_CONTEXT > FmContextAdmin[Context].context_id)
  {
    return GDSP_CORE1;  // DSP 1
  }
  else
  {
    return GDSP_CORE2; // DSP 2
  }
}

unsigned char ContextIdToContext(CONTEXT_TYPE context_id)
/****************************************************************************
* DESCRIPTION: Convert Context_ID admin context
****************************************************************************/
{
  unsigned char context;
  unsigned short i;
  // check if valid context
  context = no_contexts;
  for (i=0;i<no_contexts;i++)
  {
    if(FmContextAdmin[i].context_id == context_id)
    {
      context = (unsigned char)i;
      break;
    }    
  }
  return context;
}



unsigned long FunctionIndexToCallInst(unsigned char jumptable_index)
/****************************************************************************
* DESCRIPTION: Convert function index to absolute function address. 
****************************************************************************/
{
    return( (((unsigned long)(jumptable_index+_BASE_ADDR_)<<16)|CALL_INSTR));
}


GdspReturnCode GdspWait(CONTEXT_TYPE context_id)
/****************************************************************************
* DESCRIPTION: Does not return until DSP is registered to have passed a safe place, for example next WTF
****************************************************************************/
{
  unsigned short context;
  volatile unsigned short wait_loop_backdoor;

  for( context=0; context < no_contexts; context++ )
  {
    if(FmContextAdmin[context].context_id == context_id)
    {
      break;
    }
  }
  
  if (GDSP_DSP2_BACKGROUND_CONTEXT > context_id) // DSP1?
  {
    if(DSP1_RUNNIG != GdspDsp1Running())
    {
      return GDSP_SUCCESS; // If Dsp not running then it is always safe
    }
  }
  else
  {
    if(DSP2_RUNNIG != GdspDsp2Running()) 
    {
      return GDSP_SUCCESS; // If Dsp not running then it is always safe
    }
  }


  if (context<no_contexts)
  {
    wait_loop_backdoor=0xff;
    *FmContextAdmin[context].WaitVariable = DSP_UNSAFE_POINT;
    while ((DSP_SAFE_POINT != *FmContextAdmin[context].WaitVariable) && (wait_loop_backdoor--))
      ; // wait one context frame
    return GDSP_SUCCESS;
  }
  else
  {
    FM_ASSERT_ERROR(0);
    return GDSP_NO_SUCCESS;
  }
}


GdspReturnCode InsertCode(unsigned short admin_index,const unsigned long* function_block_code,unsigned short codesize, unsigned short *datapointer, unsigned char context, unsigned char skip_relative_calc)
/****************************************************************************
* DESCRIPTION: Helper function to insert code into DSP
****************************************************************************/
{
  unsigned short i,code_offset;
  unsigned long  *codepointer, *org_code;
  GdspCoreNumberType dsp_nr;

  dsp_nr = IndexToDsp(admin_index);

  code_offset = 0;
  for(i=FmContextAdmin[context].start_index; i<admin_index; i++)  // add codeoffsets from index 0 and up to free_index, but not including, this is the starting point of the allocated code struct - also counting the free blocks
  {
    code_offset = code_offset + (unsigned short)FmAdmin[i].code_size;
  }
  codepointer = (unsigned long*)(FmContextAdmin[context].code_start_address + code_offset);

  // Check if out of code bounds
  if ((codepointer+FmAdmin[admin_index].code_size) > FmContextAdmin[context].code_end_address)
  {
    FM_ASSERT_ERROR(0);
    return GDSP_NO_SUCCESS; // return NO_SUCCES
  }

  // If last active block, then move the JA START/EXIT to code address after block!
  if (admin_index >= FmContextAdmin[context].last_active_index) 
  {
    unsigned long  *ja_codepointer;

    if (admin_index < (FmContextAdmin[context].end_index)) 
    {
      code_offset = code_offset + (unsigned short)FmAdmin[admin_index].code_size; //codesize;  // Add this blocks code size to the code offset
      ja_codepointer = (unsigned long*)(FmContextAdmin[context].code_start_address + code_offset);
      // Add the new jump 
      *ja_codepointer = FmContextAdmin[context].JaStartExitInst;
    }        

    // Find the last JaStartExitInstr and overwrite
    if (FmContextAdmin[context].last_active_index < (FmContextAdmin[context].end_index-1))
    {
      code_offset = 0;
      if (FmContextAdmin[context].start_index != admin_index) // ONly overwrite if not the very first block FmContextAdmin[context].last_active_index) 
      {
        for(i=FmContextAdmin[context].start_index; i<=FmContextAdmin[context].last_active_index; i++)
        {
          code_offset = code_offset + (unsigned short)FmAdmin[i].code_size;
        }
      
        ja_codepointer = (unsigned long*)(FmContextAdmin[context].code_start_address + code_offset);
        // Overwrite with jump past the block
        for (i=(FmContextAdmin[context].last_active_index+1);i<(FmContextAdmin[context].end_index-1);i++)
        {
          if (0 < FmAdmin[i].code_size)
          {
            if (MAX_CODE_BLOCK != FmAdmin[i].code_size)
            {
              *ja_codepointer = (((unsigned long )((unsigned long)NOP_INSTR<<16)&0xFFFF0000)|(JADR9_INSTR | ((FmAdmin[i].code_size<<1)-1)));  // Convert codesize to 8 bit addresses
            }
            break;
          }
        }
      }
    }
    // Set new last_active to this index
    FmContextAdmin[context].last_active_index = admin_index;
  }

  // First make block inactive, by setting a jump past the code
  *codepointer++ = (((unsigned long)((unsigned long)NOP_INSTR<<16)&0xFFFF0000)|(JADR9_INSTR | ((((unsigned short)FmAdmin[admin_index].code_size)<<1)-1)));
  // Then wait until DSP is not reading opcodes from next address      
  GdspWait(FmContextAdmin[context].context_id);
  org_code = (unsigned long*)&function_block_code[0];
  //extract function index
  FmAdmin[admin_index].function_index = (unsigned char)((*org_code & 0x00FF0000)>>16); //extract jumptable index from init struct
  org_code++;
  for(i=1;i<codesize;i++)
  {
    unsigned short org_instr = (unsigned short)(*org_code&0xFFFF);
    unsigned short org_arg   = (unsigned short)((*org_code)>>16);
    if (((LDO_INSTR == org_instr) || (LDC_INSTR == org_instr)) && !skip_relative_calc)
    {
      org_arg = org_arg + (unsigned short)Cr16_to_GenDspDataAddress(dsp_nr,datapointer);
      *codepointer = GDSP_32BITOPCODE(org_instr,org_arg); 
    }
    else
    {
      *codepointer = *org_code;
    }
    codepointer++;
    org_code++;
  }

  return GDSP_SUCCESS;
}

unsigned short FmGetDataSize(unsigned short *datapointer)
{
  unsigned short block_datasize;
  block_datasize = (*(datapointer-FM_DSP_HEAP_ADM_SIZE)) & FM_DSP_HEAP_BLOCK_MAX;
  return block_datasize;
}


void FmFreeData(GdspCoreNumberType gDspCoreNr, unsigned short *datapointer)
/****************************************************************************
* DESCRIPTION: Dsp Heap Free Function
****************************************************************************/
{
  unsigned short *this_block_ptr,*next_block_ptr;
  this_block_ptr = datapointer-FM_DSP_HEAP_ADM_SIZE;

  *this_block_ptr |= FM_DSP_HEAP_BLOCK_FREE;  // Mark block as free

  FmDspAdmin[gDspCoreNr].heap_free = FmDspAdmin[gDspCoreNr].heap_free + (*this_block_ptr & FM_DSP_HEAP_BLOCK_MAX);

  // Collect all consecutive blocks into one block
  this_block_ptr = FmDspAdmin[gDspCoreNr].data_start_address;
  while (*this_block_ptr != FM_DSP_HEAP_END)
  {
    unsigned short block_datasize = *this_block_ptr & FM_DSP_HEAP_BLOCK_MAX;
    next_block_ptr  = this_block_ptr + block_datasize + FM_DSP_HEAP_ADM_SIZE; // point to next block
    while((*this_block_ptr & FM_DSP_HEAP_BLOCK_FREE) && (*next_block_ptr & FM_DSP_HEAP_BLOCK_FREE))
    {
      unsigned short next_block_datasize = *next_block_ptr & FM_DSP_HEAP_BLOCK_MAX;
      *this_block_ptr = ((block_datasize + next_block_datasize + FM_DSP_HEAP_ADM_SIZE) & FM_DSP_HEAP_BLOCK_MAX) | FM_DSP_HEAP_BLOCK_FREE;            
      block_datasize = *this_block_ptr & FM_DSP_HEAP_BLOCK_MAX;
      next_block_ptr  = this_block_ptr + block_datasize + FM_DSP_HEAP_ADM_SIZE; // point to next block
      FmDspAdmin[gDspCoreNr].heap_free = FmDspAdmin[gDspCoreNr].heap_free + FM_DSP_HEAP_ADM_SIZE;
    }    
    this_block_ptr = next_block_ptr;
  }
  datapointer = 0;
}
unsigned short totalfmallocdatasize=0;
unsigned short *FmAllocData(GdspCoreNumberType gDspCoreNr, unsigned short datasize)
/****************************************************************************
* DESCRIPTION: Dsp Heap Alloc Function
****************************************************************************/
{
  unsigned short *this_block_ptr,*next_block_ptr, *free_block_ptr=0;
  unsigned short *datapointer;
  unsigned short min_free_block=0xFFFF;
  this_block_ptr = FmDspAdmin[gDspCoreNr].data_start_address;

  datapointer = 0;
  totalfmallocdatasize+=datasize;
  while (*this_block_ptr != FM_DSP_HEAP_END)
  {
    unsigned short block_datasize = *this_block_ptr & FM_DSP_HEAP_BLOCK_MAX;
    next_block_ptr  = this_block_ptr + block_datasize + FM_DSP_HEAP_ADM_SIZE; // point to next block

    if (*this_block_ptr & FM_DSP_HEAP_BLOCK_FREE)
    {
      if (block_datasize >= datasize)
      { 
        if(block_datasize <= min_free_block)
        {
          min_free_block = block_datasize;
          free_block_ptr = this_block_ptr;
          if(block_datasize == datasize)
          {
            // Found a perfect match
            break;
          }
        }
      }
    }    
    this_block_ptr = next_block_ptr;
  }

  if (free_block_ptr)
  {
    unsigned short block_datasize = *free_block_ptr & FM_DSP_HEAP_BLOCK_MAX;
    next_block_ptr  = free_block_ptr + block_datasize + FM_DSP_HEAP_ADM_SIZE; // point to next block

    if (block_datasize != datasize)
    {
      *free_block_ptr = datasize & FM_DSP_HEAP_BLOCK_MAX;
      next_block_ptr = free_block_ptr + datasize + FM_DSP_HEAP_ADM_SIZE; // point to next block
      *next_block_ptr = ((block_datasize - datasize - FM_DSP_HEAP_ADM_SIZE) & FM_DSP_HEAP_BLOCK_MAX) | FM_DSP_HEAP_BLOCK_FREE;     
      FmDspAdmin[gDspCoreNr].heap_free = FmDspAdmin[gDspCoreNr].heap_free - FM_DSP_HEAP_ADM_SIZE;
    }
    FmDspAdmin[gDspCoreNr].heap_free = FmDspAdmin[gDspCoreNr].heap_free - datasize;
    if (FmDspAdmin[gDspCoreNr].heap_free < FmDspAdmin[gDspCoreNr].heap_free_peak)
    {
      FmDspAdmin[gDspCoreNr].heap_free_peak = FmDspAdmin[gDspCoreNr].heap_free;
    }
    

    *free_block_ptr &= ~FM_DSP_HEAP_BLOCK_FREE; // Mark as not free
    datapointer = free_block_ptr + FM_DSP_HEAP_ADM_SIZE;
  }

  return datapointer;
}




