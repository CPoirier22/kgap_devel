/********************************************************************************
 *********************************************************************************
 *                                                                               *
 *     E ENEEEEEEEEEEEE             CCCC CCC         TTTTTTT TTTTTTTTTT          *
 *     E EEEEEEEEEEEEEE          CCCCC  C CCCC             T TTTTT               *
 *     E EEEE                   CCCCC    C CCCC            T TTTTT               *
 *     E EEEE                  CCCCC      C CCCC           T TTTTT               *
 *     E EEEE                 CCCCC                        T TTTTT               *
 *     E EEEEEEEEEEEEEE      CCCCC                         T TTTTT               *
 *     E EEEEEEEEEEEEEE      C CCCC                        T TTTTT               *
 *     E EEEE                 C CCCC                       T TTTTT               *
 *     E EEEE                  C CCCC      CCCCC           T TTTTT               *
 *     E EEEEEEEEEEEEEE         C CCCC   CCCCC             T TTTTT               *
 *     E EEEEEEEEEEEEEE  OO      C CCCCCCCC         OO     T TTTTT     OO        *
 *                       OO                         OO                 OO        *
 *                                                                               *
 *     Electronic Communication Technology A/S.                                  *
 *     Sintrupvej 23, DK-8220 Brabrand, Tel.: +45 87441230                       *
 *     Website: www.ect.dk                                                       *
 *                                                                               *
 *********************************************************************************
 * $History:: gdsp_main.c                                                      $ *
 *                                                                               *
 * Initial Revision                                                              *
 *********************************************************************************
 */
/*=============================================================================*/
/*  Include files                                                              */
/*=============================================================================*/
#include "gdsp_functionselector.h"
#include "gdsp_functionmanager_api.h" 
#include "gdsp_driver_functions_api.h" 
#include "gdsp_mdl2code_size_defines.h"
#include "gdsp_local_config.h" 
#include "../../../../../../include/common/include/print_status.h"
#include "gdsp_local_defines.h"
/*============================================================================*/
/*  Global variables                                                          */
/*============================================================================*/

#ifdef GCCCOMPILE
BYTE DspParamRam[DSP_SEGMENT_SIZE] __attribute__ ((section (".dspdataram")));
#endif 

/*============================================================================*/
/*  Memory layout                                                             */
/*  Can be changed by user!                                                   */
/*  Please make sure that the highest sample rate has the highest priority    */
/*  interrupt!! (DSP_INT0 = highest, DSP_INT5 = lowest)                       */
/*============================================================================*/
const dsp_context_memory_config_t PP_Layout[2] = {
// Background layout
    { (unsigned long*) PP_DSP_BG_CODE_START, (unsigned long*) PP_DSP_BG_CODE_END, (unsigned short*) PP_DSP_DATA_START, (unsigned short*) PP_DSP_DATA_END, (unsigned short*) PP_DSP_STACK_INIT, GDSP_DSP1_BACKGROUND_CONTEXT, DSP_NO_INT, // Background has no trigger interrupt
        0 },
    // Context 1 layout
    { (unsigned long*) PP_DSP_CONTEXT1_CODE_START, (unsigned long*) PP_DSP_CONTEXT1_CODE_END, 0, 0, 0, GDSP_DSP1_8KHZ_CONTEXT, // Sample rate for context 1
        DSP_INT0, // Trigger interrupt for context 1
        0 } };

const dsp_context_memory_config_t FP_CONF_Layout2[2] = {
// Background layout
    { (unsigned long*) FP_DSP_BG_CODE_START, (unsigned long*) FP_DSP_BG_CODE_END, (unsigned short*) FP_DSP_DATA_START, (unsigned short*) FP_DSP_DATA_END, (unsigned short*) FP_DSP_STACK_INIT, GDSP_DSP1_BACKGROUND_CONTEXT, DSP_NO_INT, // Background has no trigger interrupt
        0 },
    // Context 1 layout
    { (unsigned long*) FP_DSP_CONTEXT1_CODE_START, (unsigned long*) FP_DSP_CONTEXT1_CODE_END, 0, 0, 0, GDSP_DSP1_8KHZ_CONTEXT, // Sample rate for context 1
        DSP_INT0, // Trigger interrupt for context 1
        0 } };

const dsp_context_memory_config_t FP_CONF_Layout1[1] = {
// Background layout
    { (unsigned long*) FP_DSP_BG_CODE_START, (unsigned long*) FP_DSP_BG_CODE_END, (unsigned short*) FP_DSP_DATA_START, (unsigned short*) FP_DSP_DATA_END, (unsigned short*) FP_DSP_STACK_INIT, GDSP_DSP1_BACKGROUND_CONTEXT, DSP_INT0, // Background has no trigger interrupt
        0 }
};

extern UByte getRunMode(void);
extern int gen2dspblock_init_pp(GDSP_INIT_STRUCT *init_str, GDSP_INTERFACE_INIT_STRUCT *interface_str);
extern int gen2dspblock_init_fp(GDSP_INIT_STRUCT *init_str, GDSP_INTERFACE_INIT_STRUCT *interface_str);

static GDSP_INIT_STRUCT init_str;
static GDSP_INTERFACE_INIT_STRUCT interface_str;

static void pause(int x)
{
    volatile int i;
    for (i = 0; i < x; i++) {
        ;
    }
}

static void startPLL(unsigned char MHz)
{
  if (MHz==165)
  {
    CLK_PLL_DIV_REG = 0x1c;
    CLK_PLL_CTRL_REG |= (VCO_ON | CP_ON | HF_SEL);
    CLK_PLL_CTRL_REG &= ~PLL_DIP_DIV;

    CLK_AMBA_REG &= ~HCLK_DIV;
    CLK_AMBA_REG |= 0x0004; /* 7, 6, 5, 4, 3, 2 ok, 1 not ok */
    CLK_AMBA_REG &= ~PCLK_DIV;

    pause(100); /* wait 760 usec*/

    CLK_PLL_CTRL_REG |= PLL_CLK_SEL;

  }
  else
  {
    CLK_PLL_DIV_REG = 0x04;
    CLK_PLL_CTRL_REG |= (VCO_ON | CP_ON | HF_SEL);

    pause(100); /* wait 760 usec*/

    CLK_PLL_CTRL_REG &= ~PLL_DIP_DIV;
    CLK_PLL_CTRL_REG |= 8 << 7; /* DIP Clock divider*/
    CLK_PLL_CTRL_REG |= PLL_CLK_SEL;

    CLK_AMBA_REG &= ~HCLK_DIV;
    CLK_AMBA_REG |= 0x0002; /* 7, 6, 5, 4, 3, 2 ok, 1 not ok */
    CLK_AMBA_REG &= ~PCLK_DIV;
  }
}


int gen2dsp_init(void)
{
  BYTE result;
  if (getRunMode())
  {
    init_str.dsp_context_memory_config = (dsp_context_memory_config_t *) FP_CONF_Layout2;
    init_str.no_contexts = 2;
    interface_str.int_enabled = TRUE;
    interface_str.int_priority = 7;
	if (P3_DATA_REG & Px_7_DATA)
	{
	  PrintStatus(0,"Initialising DSP for FP mode, PCM slave, menu A");
	  interface_str.pcm_interf_mode = GDSP_SLAVE;
	}
	else
	{
	  PrintStatus(0,"Initialising DSP for FP mode, PCM master, menu B");
	  interface_str.pcm_interf_mode = GDSP_MASTER;
	}
    result = gen2dspblock_init_fp(&init_str, &interface_str);
    // IMPORTANT - make sure DSP is maxed out, otherwise we don't have enough DSP processing power for a 6-7 party conference with ADPCM encoding/decoding
    // InitClockRegisters(PLL_160); // CRC16=41MHz, DSP=82MHz, Fpll=165Mhz - see also AN-D-181 and SC14480ClockTree excel spreadsheet
    startPLL(165); // preliminary solution until InitClockRegisters(PLL_160) is working
  }
  else
  {
    init_str.dsp_context_memory_config = (dsp_context_memory_config_t *) PP_Layout;
    init_str.no_contexts = 2; // Change this if number of contexts is not 1!
    interface_str.int_enabled = TRUE;
    interface_str.int_priority = 7;
    interface_str.pcm_interf_mode = GDSP_MASTER;
    result = gen2dspblock_init_pp(&init_str, &interface_str);
    PrintStatus(0,"Initialising DSP for PP mode");
    startPLL(82); // maybe we dont need this when running PP - time will tell....
  }
  return result;
}
