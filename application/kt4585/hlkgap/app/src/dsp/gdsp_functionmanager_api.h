#ifndef GDSP_FUNCTIONMANAGER_API
#define GDSP_FUNCTIONMANAGER_API

/*==============================INCLUDE FILES======================================*/
#include "gdsp_functionmanagerdefs.h"

/*=============================================================================*/
/*  Data type definitions                                                      */
/*=============================================================================*/


#define GDSP_SUCCESS              7 /*  111 The execution of the GDSP API function was successful. */ 
#define GDSP_INVALID_PARAMETER    6 /*  110 One or more of the parameters in the function call are invalid */                                                    /* GDSP API function was invalid.                         */                                            
#define GDSP_NO_SUCCESS           5 /*  101 The execution of the GDSP API function was not successful */      

typedef unsigned char GdspReturnCode;

typedef enum
{
  GDSP_CORE1 = 0,
  GDSP_CORE2 = 1
} GdspCoreNumberType;


// Must be grouped DSP-wise.
typedef enum
{
  // DSP1 TASKS
  GDSP_DSP1_BACKGROUND_CONTEXT,
  GDSP_DSP1_8KHZ_CONTEXT,
  GDSP_DSP1_16KHZ_CONTEXT,
  GDSP_DSP1_32KHZ_CONTEXT,
  GDSP_DSP1_CR16INT_CONTEXT,
  GDSP_DSP1_DIPINT_CONTEXT,
  GDSP_DSP1_DSP2INT_CONTEXT,
  //DSP2 TASKS
  GDSP_DSP2_BACKGROUND_CONTEXT,
  GDSP_DSP2_8KHZ_CONTEXT,
  GDSP_DSP2_16KHZ_CONTEXT,
  GDSP_DSP2_32KHZ_CONTEXT,
  GDSP_DSP2_CR16INT_CONTEXT,
  GDSP_DSP2_DIPINT_CONTEXT,
  GDSP_DSP2_DSP1INT_CONTEXT,
  // MAX
  GDSP_DSP_MAX_CONTEXT
} Enum_CONTEXT_TYPE; typedef unsigned char CONTEXT_TYPE;

// default conversion from mdl2code output
#ifndef DSP1_BACKGND
  #define DSP1_BACKGND GDSP_DSP1_BACKGROUND_CONTEXT
#endif
#ifndef DSP1_8KHZ
  #define DSP1_8KHZ    GDSP_DSP1_8KHZ_CONTEXT
#endif
#ifndef DSP1_16KHZ
  #define DSP1_16KHZ   GDSP_DSP1_16KHZ_CONTEXT
#endif
#ifndef DSP1_32KHZ
  #define DSP1_32KHZ   GDSP_DSP1_32KHZ_CONTEXT
#endif
#ifndef DSP1_CR16INT
  #define DSP1_CR16INT GDSP_DSP1_CR16INT_CONTEXT
#endif
#ifndef DSP1_DIPINT
  #define DSP1_DIPINT  GDSP_DSP1_DIPINT_CONTEXT
#endif
#ifndef DSP1_DSPINT
  #define DSP1_DSPINT  GDSP_DSP1_DSP2INT_CONTEXT
#endif
#ifndef DSP1_BACKGND
  #define DSP2_BACKGND GDSP_DSP2_BACKGROUND_CONTEXT
#endif
#ifndef DSP2_8KHZ
  #define DSP2_8KHZ    GDSP_DSP2_8KHZ_CONTEXT
#endif
#ifndef DSP2_16KHZ
  #define DSP2_16KHZ   GDSP_DSP2_16KHZ_CONTEXT
#endif
#ifndef DSP2_32KHZ
  #define DSP2_32KHZ   GDSP_DSP2_32KHZ_CONTEXT
#endif
#ifndef DSP2_CR16INT
  #define DSP2_CR16INT GDSP_DSP2_CR16INT_CONTEXT
#endif
#ifndef DSP1_BACKGND
  #define DSP2_DIPINT  GDSP_DSP2_DIPINT_CONTEXT
#endif
#ifndef DSP2_DSPINT
  #define DSP2_DSPINT  GDSP_DSP2_DSP1INT_CONTEXT
#endif



typedef enum
{
  DSP_INT0=0,
  DSP_INT1=1,
  DSP_INT2=2,
  DSP_INT3=3,
  DSP_INT4=4,
  DSP_INT5=5,
  DSP_NO_INT,
} Enum_interrupt_souce_type; typedef unsigned char interrupt_souce_type;

//#pragma pack(push ,FMPACK,2)
typedef struct 
{
  unsigned long*          function_manager_codemem_start;       /* Start address of context code memory                               */
  unsigned long*          function_manager_codemem_end;         /* End address of context code memory                                 */
  unsigned short*         function_manager_datamem_start;       /* Start address of data memory  - only valid for bkgd context        */
  unsigned short*         function_manager_datamem_end;         /* End address of data memory    - only valid for bkgd context        */
  unsigned short*         function_manager_stack_end;           /* End address of STACK area     - only valid for bkgd context        */
  CONTEXT_TYPE            context_id;                           /* What context is this config for?                                   */  
  interrupt_souce_type    interrupt_source;                     /* What interrupt source : 0-6                                        */
  unsigned short          end_of_context_interrupt_vector;      /* Interrupt vector generated at end of context                       */ 
} dsp_context_memory_config_t;


typedef struct
{
  dsp_context_memory_config_t *dsp_context_memory_config; /* Start & End addresses for Gen2Dsp code and data - pointer to array for all contexts */
  unsigned char   no_contexts;                            /* Number of contexts*/   
} GDSP_INIT_STRUCT;

//#pragma pack(pop ,FMPACK)



/****************************************************************************
*  Definitions for initialization control of DSP blocks
****************************************************************************/
#define GDSP_INIT_CTRL_LENGTH_MASK          0x0FFF      
#define GDSP_INIT_CTRL_MASK                 0xF000
#define GDSP_INIT_CTRL_REL_PTR_32BIT_ALIGN  0x7000
#define GDSP_INIT_CTRL_CONST_PTR            0x6000
#define GDSP_INIT_CTRL_FILL                 0x5000
#define GDSP_INIT_CTRL_REL_PTR              0x4000
#define GDSP_INIT_CTRL_DEFAULT              0x3000
#define GDSP_INIT_CTRL_PTR                  0x2000
#define GDSP_INIT_CTRL_ZERO                 0x1000
#define GDSP_INIT_CTRL_END                  0x0000

         
/*=============================================================================*/
/* API function prototypes                                                     */
/*=============================================================================*/
GdspReturnCode GdspInit(GDSP_INIT_STRUCT init);
GdspReturnCode GdspTriggerContext(CONTEXT_TYPE context);

void GdspConnect(unsigned short* destination_address, unsigned short* source_address);

GdspReturnCode GdspStart(unsigned short* ldo_instr);
GdspReturnCode GdspStop(unsigned short* ldo_instr);

GdspReturnCode GdspAdd(const unsigned long* function_block_code, unsigned short codesize, unsigned short **datapointer, unsigned short datasize, CONTEXT_TYPE context);
GdspReturnCode GdspAddStaticData(const unsigned long* function_block_code, unsigned short codesize, unsigned short *datapointer, CONTEXT_TYPE context_id);
GdspReturnCode GdspRemove(unsigned short* block_address);

GdspReturnCode GdspAddUserFnDynamicData(unsigned long* user_code, unsigned short **datapointer, unsigned short datasize , CONTEXT_TYPE context_id);
GdspReturnCode GdspAddUserFn(unsigned long* user_code, unsigned short *datapointer, CONTEXT_TYPE context_id);

GdspReturnCode GdspInitFunctionBlock(const unsigned short* block_init_struct, unsigned short* block_address);

GdspReturnCode GdspChangeContext(unsigned short *datapointer, CONTEXT_TYPE new_context_id);

unsigned short *FmAllocData(GdspCoreNumberType gDspCoreNr, unsigned short datasize);
void FmFreeData(GdspCoreNumberType gDspCoreNr, unsigned short *datapointer);

#ifndef FM_DSP_DATA_ROM_AVAILABLE
  extern unsigned short *FmGetRomTableAddress(unsigned short OrgGen2DspTableAddress);
#endif

/*=============================================================================*/
/* Include a default set of all dsp functions                                  */
/*=============================================================================*/
#include "gdsp_all_structdefs.h"
#include "gdsp_all_inits.h"
#endif


