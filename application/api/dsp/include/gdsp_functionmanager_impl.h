#ifndef _GDSP_FUNCTIONMANAGER_IMPL_H
#define _GDSP_FUNCTIONMANAGER_IMPL_H
/*===========================Local DSP Macros ===========================================*/  
#define GDSP_32BITOPCODE(opcode,arg) (((unsigned long)arg)<<16|(opcode))

#define PTR_TYPE unsigned long

#define GDSP_USERFN_FREE 0x0

#ifdef PCCOMPILE
  #pragma warning(disable : 4305) 
  #define FM_DSP_PTR_TYPE unsigned short *
#else
  #define FM_DSP_PTR_TYPE unsigned short
#endif

/*===========================Local DSP code arrays =======================================*/  
extern const unsigned long gdsp_default_irq_jt_code[SIZEOF_DEFAULT_IRQ_JT_CODE];
extern const unsigned long gdsp_context_save_code[SIZEOF_CONTEXT_SAVE_CODE];
extern const unsigned long gdsp_context_restore_code[SIZEOF_CONTEXT_RESTORE_CODE];

/*===========================Local Typedefs =======================================*/  
typedef struct
{
  CONTEXT_TYPE  context_id;
  interrupt_souce_type interrupt_source;
  unsigned short start_index;
  unsigned short end_index;
  unsigned short last_active_index;     /* Used to mark Jump Absolute to start/exit of context*/
  unsigned long* code_start_address;
  unsigned long* code_end_address;
  unsigned long JaStartExitInst;      /* Contains the instruction inserted as the last jump in a context body. For example jump to context restore.*/
  unsigned short* WaitVariable;
  #ifdef GDSP_FRAMEBASED_BACKGROUND_TASK
  unsigned short* ContextTriggerFlag;
  #endif
  unsigned short max_code_size;
  unsigned short max_index;
} FmContextAdmin_t;


typedef unsigned char userfn_admin_type;

typedef struct 
{
  unsigned short* data_start_address;
  unsigned short* data_end_address;
  unsigned short* stack_end_address;
  #if  (MAX_NO_FM_USER_FUNCTIONS > 0)
  userfn_admin_type  UserFnAdmin[MAX_NO_FM_USER_FUNCTIONS]; 
  unsigned long* user_jumptable;
  #endif  
  unsigned short heap_free;
  unsigned short heap_free_peak;
} FmDspAdmin_t;

/* Function manager admin struct */
typedef struct 
{
    FM_DSP_PTR_TYPE data_ptr;                /* pointer to data for the function*/
    unsigned int  static_mem      :   1;     /* Set if static memory*/
    unsigned int  block_free      :   1;     /* Bit to tell if block is free   */
    unsigned int  code_size       :   6;     /* length of code in 32 bit instructions.*/
    unsigned int  function_index  :   8;     /* Jumptable index number*/
} Function_manager_admin_type;

#endif
