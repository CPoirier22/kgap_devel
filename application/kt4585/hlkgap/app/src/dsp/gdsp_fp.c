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
* $History:: gdsp_fp.c                                                        $ *
*                                                                               *
* Initial Revision                                                              *
*********************************************************************************
*/
/*=============================================================================*/
/*  Include files                                                              */
/*=============================================================================*/
#include "gdsp_functionselector.h"
#include "gdsp_functionmanager_api.h" 
#include "gdsp_all_structdefs.h"
#include "gdsp_all_inits.h"
#include "gdsp_driver_functions_api.h"
#include "gdsp_mdl2code_size_defines.h"
#include "gdsp_local_config.h"
#include "gdsp_local_defines.h"
#include "../../../../../../include/common/include/print_status.h"
#include "../../../../../../include/mac/startup/include/fp/bmc_3f_6sl.h"
#include "../../../../../../include/common/include/map_480_gcc.h"
#define FP_CONTEXT DSP1_8KHZ

#include "background_trigger.e.PM"

#define BACKGROUND_TRIGGER_FUNC FP_BACKGROUND_TRIGGER_FUNC

extern int ES7;
extern unsigned char lastinit_error;

unsigned int GetDSPStackRemaining(void)
{
  int i = 0;
  char *stack_start_ptr = (char *) FP_DSP_STACK_START;
  char *stack_end_ptr = (char *) FP_DSP_STACK_INIT;
  while (stack_start_ptr < stack_end_ptr)
  {
    if (*stack_start_ptr++ != 'S')
      break;
    else
      i++;
  }
  return i;
}

unsigned char dum_silent_buffer[40];
int gen2dspblock_init_fp(GDSP_INIT_STRUCT *init_str,GDSP_INTERFACE_INIT_STRUCT *interface_str)
{
  BYTE result = GDSP_SUCCESS;
  int i;

  if (CHIP_TEST1_REG == 0x12)
  {
	ES7 = 1;
    PrintStatus(0, "*** ES7 == 0x12 *** ");
  }
  else
  {
	ES7 = 0;
    PrintStatus(0, "*** ES7 != 0x12 *** ");
  }

  InitDSPCODEC();                     // Codec initialization
  InitInterrupts(*init_str);           // Initialize Gen2DSP triggers & interrupts
  for (i = 0; i < 40; i++)
    dum_silent_buffer[i] = 0;
  // Initialize DSP_STACK for post mortem analyses
  char *stack_start_ptr = (char *) FP_DSP_STACK_START;
  char *stack_end_ptr = (char *) FP_DSP_STACK_INIT;
  while (stack_start_ptr < stack_end_ptr)
    *stack_start_ptr++ = 'S';

  char *debug_start_ptr = (char *) FP_DSP_DATA_START;
  char *debug_end_ptr = (char *) FP_DSP_DATA_END;
  while (debug_start_ptr < debug_end_ptr)
    *debug_start_ptr++ = '5';

  result &= InitGdspInterface(*interface_str);
  if (GDSP_SUCCESS != result)
  {
    PrintStatus(0, "-A- ");
    return GDSP_NO_SUCCESS;
  }
  result &= GdspInit(*init_str);
  if (GDSP_SUCCESS != result)
  {
    PrintStatus(0, "-1- ");
    return GDSP_NO_SUCCESS;
  }

  // Start of API Calls to build a DSP application
  /****************************************************************************
   *  Add blocks to the background context                                    *
   *                                                                          *
   *  GdspAddUserFnDynamicData: Is used to add the backgroundtrigger and      *
   *                            pointer_updater because they are ram functions*
   *                                                                          *
   *  GdspAddStaticData:        Is used to add the SVC encoder and decoder to *
   *                            make sure they are 32 bits aligned            *
   *                                                                          *
   ****************************************************************************/
  result &= GdspAdd((const unsigned long*)&copySpeechBuffer1_code,sizeof(copySpeechBuffer1_code)/4,(unsigned short**)&p_copySpeechBuffer1,sizeof(copySpeecBuffers)/2,FP_CONTEXT);
  result &= GdspAdd((const unsigned long*)&clearPointers1_code,sizeof(clearPointers1_code)/4,(unsigned short**)&p_clearPointers1,sizeof(clearPointers)/2,FP_CONTEXT);

  result &= GdspAdd((const unsigned long*)&g726decoder1_code,sizeof(g726decoder1_code)/4,(unsigned short**)&p_g726decoder[0],sizeof(gdsp_adpcmnbdecoder)/2,FP_CONTEXT);
  result &= GdspAdd((const unsigned long*)&g726encoder1_code,sizeof(g726encoder1_code)/4,(unsigned short**)&p_g726encoder[0],sizeof(gdsp_adpcmnbencoder)/2,FP_CONTEXT);
  result &= GdspAdd((const unsigned long*)&g726decoder2_code,sizeof(g726decoder2_code)/4,(unsigned short**)&p_g726decoder[1],sizeof(gdsp_adpcmnbdecoder)/2,FP_CONTEXT);
  result &= GdspAdd((const unsigned long*)&g726encoder2_code,sizeof(g726encoder2_code)/4,(unsigned short**)&p_g726encoder[1],sizeof(gdsp_adpcmnbencoder)/2,FP_CONTEXT);
  result &= GdspAdd((const unsigned long*)&g726decoder3_code,sizeof(g726decoder3_code)/4,(unsigned short**)&p_g726decoder[2],sizeof(gdsp_adpcmnbdecoder)/2,FP_CONTEXT);
  result &= GdspAdd((const unsigned long*)&g726encoder3_code,sizeof(g726encoder3_code)/4,(unsigned short**)&p_g726encoder[2],sizeof(gdsp_adpcmnbencoder)/2,FP_CONTEXT);
  result &= GdspAdd((const unsigned long*)&g726decoder4_code,sizeof(g726decoder4_code)/4,(unsigned short**)&p_g726decoder[3],sizeof(gdsp_adpcmnbdecoder)/2,FP_CONTEXT);
  result &= GdspAdd((const unsigned long*)&g726encoder4_code,sizeof(g726encoder4_code)/4,(unsigned short**)&p_g726encoder[3],sizeof(gdsp_adpcmnbencoder)/2,FP_CONTEXT);
  result &= GdspAdd((const unsigned long*)&g726decoder5_code,sizeof(g726decoder5_code)/4,(unsigned short**)&p_g726decoder[4],sizeof(gdsp_adpcmnbdecoder)/2,FP_CONTEXT);
  result &= GdspAdd((const unsigned long*)&g726encoder5_code,sizeof(g726encoder5_code)/4,(unsigned short**)&p_g726encoder[4],sizeof(gdsp_adpcmnbencoder)/2,FP_CONTEXT);
  result &= GdspAdd((const unsigned long*)&g726decoder6_code,sizeof(g726decoder6_code)/4,(unsigned short**)&p_g726decoder[5],sizeof(gdsp_adpcmnbdecoder)/2,FP_CONTEXT);
  result &= GdspAdd((const unsigned long*)&g726encoder6_code,sizeof(g726encoder6_code)/4,(unsigned short**)&p_g726encoder[5],sizeof(gdsp_adpcmnbencoder)/2,FP_CONTEXT);

  result &= GdspAdd((const unsigned long*)0,0,(unsigned short**)&p_dataArea0,sizeof(dataArea_40)/2,FP_CONTEXT);
  result &= GdspAdd((const unsigned long*)0,0,(unsigned short**)&p_dataArea2,sizeof(dataArea_40)/2,FP_CONTEXT);
  result &= GdspAdd((const unsigned long*)0,0,(unsigned short**)&p_dataArea4,sizeof(dataArea_40)/2,FP_CONTEXT);
  result &= GdspAdd((const unsigned long*)0,0,(unsigned short**)&p_dataArea6,sizeof(dataArea_40)/2,FP_CONTEXT);
  result &= GdspAdd((const unsigned long*)0,0,(unsigned short**)&p_dataArea8,sizeof(dataArea_40)/2,FP_CONTEXT);
  result &= GdspAdd((const unsigned long*)0,0,(unsigned short**)&p_dataArea10,sizeof(dataArea_40)/2,FP_CONTEXT);
  result &= GdspAdd((const unsigned long*)0,0,(unsigned short**)&p_dataArea12,sizeof(dataArea_40)/2,FP_CONTEXT);
  result &= GdspAdd((const unsigned long*)0,0,(unsigned short**)&p_dataArea14,sizeof(dataArea_40)/2,FP_CONTEXT);
  result &= GdspAdd((const unsigned long*)0,0,(unsigned short**)&p_dataArea16,sizeof(dataArea_40)/2,FP_CONTEXT);
  result &= GdspAdd((const unsigned long*)0,0,(unsigned short**)&p_dataArea18,sizeof(dataArea_40)/2,FP_CONTEXT);
  result &= GdspAdd((const unsigned long*)0,0,(unsigned short**)&p_dataArea20,sizeof(dataArea_40)/2,FP_CONTEXT);
  result &= GdspAdd((const unsigned long*)0,0,(unsigned short**)&p_dataArea22,sizeof(dataArea_40)/2,FP_CONTEXT);

  result &= GdspAdd((const unsigned long*)0,0,(unsigned short**)&p_stopcopyconstant,sizeof(gdsp_constant)/2,FP_CONTEXT);

#ifdef ENABLE_TONEGEN
  result &= GdspAdd((const unsigned long*)&tonegen_code,sizeof(tonegen_code)/4,(unsigned short**)&p_tonegen,sizeof(gdsp_tonegen)/2,FP_CONTEXT);
  result &= GdspAdd((const unsigned long*)&playbackbuffer_code,sizeof(playbackbuffer_code)/4,(unsigned short**)&p_playbackbuffer,sizeof(gdsp_playbackbuffer_18)/2,FP_CONTEXT);
  result &= GdspAdd((const unsigned long*)&law2lin_code,sizeof(law2lin_code)/4,(unsigned short**)&p_law2lin,sizeof(gdsp_lawlin)/2,DSP1_8KHZ);
#endif
  result &= GdspAdd((const unsigned long*)&gendspcodecdestinations_code,sizeof(gendspcodecdestinations_code)/4,(unsigned short**)&p_gendspcodecdestinations,sizeof(gdsp_codecdestinations)/2,FP_CONTEXT);
  result &= GdspAdd((const unsigned long*)&gendspcodecsource_code,sizeof(gendspcodecsource_code)/4,(unsigned short**)&p_gendspcodecsource,sizeof(gdsp_codecsource)/2,FP_CONTEXT);
  result &= GdspAdd((const unsigned long*)0,0,(unsigned short**)&p_gendspgainconstant_fp,sizeof(gdsp_constant)/2,FP_CONTEXT);

  result &= GdspAdd((const unsigned long*)&gain_code,sizeof(gain_code)/4,(unsigned short**)&p_gain_inbound,sizeof(gdsp_gain)/2,FP_CONTEXT);
  result &= GdspAdd((const unsigned long*)&gain_code,sizeof(gain_code)/4,(unsigned short**)&p_gain_spkr_fp,sizeof(gdsp_gain)/2,FP_CONTEXT);

  result &= GdspAdd((const unsigned long*)&dynmixer_code,sizeof(dynmixer_code)/4,(unsigned short**)&p_dynmixer0,sizeof(gdsp_mixer)/2,FP_CONTEXT);
  result &= GdspAdd((const unsigned long*)&dynmixer_code,sizeof(dynmixer_code)/4,(unsigned short**)&p_dynmixer1,sizeof(gdsp_mixer)/2,FP_CONTEXT);
  result &= GdspAdd((const unsigned long*)&dynmixer_code,sizeof(dynmixer_code)/4,(unsigned short**)&p_dynmixer2,sizeof(gdsp_mixer)/2,FP_CONTEXT);
  result &= GdspAdd((const unsigned long*)&dynmixer_code,sizeof(dynmixer_code)/4,(unsigned short**)&p_dynmixer3,sizeof(gdsp_mixer)/2,FP_CONTEXT);
  result &= GdspAdd((const unsigned long*)&dynmixer_code,sizeof(dynmixer_code)/4,(unsigned short**)&p_dynmixer4,sizeof(gdsp_mixer)/2,FP_CONTEXT);
  result &= GdspAdd((const unsigned long*)&dynmixer_code,sizeof(dynmixer_code)/4,(unsigned short**)&p_dynmixer5,sizeof(gdsp_mixer)/2,FP_CONTEXT);
  result &= GdspAdd((const unsigned long*)&dynmixer_code,sizeof(dynmixer_code)/4,(unsigned short**)&p_dynmixer6,sizeof(gdsp_mixer)/2,FP_CONTEXT);
  result &= GdspAdd((const unsigned long*)&dynmixer_code,sizeof(dynmixer_code)/4,(unsigned short**)&p_dynmixer7,sizeof(gdsp_mixer)/2,FP_CONTEXT);

  result &= GdspAdd((const unsigned long*)&gendsppcmsource_code,sizeof(gendsppcmsource_code)/4,(unsigned short**)&p_gendsppcmsource,sizeof(gdsp_pcmsource)/2,DSP1_8KHZ);
  result &= GdspAdd((const unsigned long*)&gendsppcmmasterdestinations_code,sizeof(gendsppcmmasterdestinations_code)/4,(unsigned short**)&p_gendsppcmmasterdestinations,sizeof(gdsp_pcmmasterdestinations)/2,DSP1_8KHZ);
  result &= GdspAdd((const unsigned long*)&pcm_buffer_code,sizeof(pcm_buffer_code)/4,(unsigned short**)&p_pcm_buffer,sizeof(gdsp_recordbuffer_18)/2,FP_CONTEXT);
  result &= GdspAdd((const unsigned long*)0,0,(unsigned short**)&p_gendsp_pcm_command_out,sizeof(gdsp_constant)/2,FP_CONTEXT);

  if (GDSP_SUCCESS != result)
    PrintStatus(0, "*** GdspAdd() failed *** ");
  if (GDSP_SUCCESS != result)
    return GDSP_NO_SUCCESS;

  result &= GdspInitFunctionBlock((const unsigned short*)&gendsppcmsource,(unsigned short*)p_gendsppcmsource);
  result &= GdspInitFunctionBlock((const unsigned short*)&gendsppcmmasterdestinations,(unsigned short*)p_gendsppcmmasterdestinations);
  result &= GdspInitFunctionBlock((const unsigned short*)&pcm_buffer,(unsigned short*)p_pcm_buffer);
  result &= GdspInitFunctionBlock((const unsigned short*)&gendspgainconstant,(unsigned short*)p_gendsp_pcm_command_out);

#ifdef ENABLE_TONEGEN
  result &= GdspInitFunctionBlock((const unsigned short*) &playbackbuffer, (unsigned short*) p_playbackbuffer);
#endif

  result &= GdspInitFunctionBlock((const unsigned short*)&copySpeechBuffer1,(unsigned short*)p_copySpeechBuffer1);
  result &= GdspInitFunctionBlock((const unsigned short*)&clearPointers1,(unsigned short*)p_clearPointers1);

  result &= GdspInitFunctionBlock((const unsigned short*)&g726decoder1,(unsigned short*)p_g726decoder[0]);
  result &= GdspInitFunctionBlock((const unsigned short*)&g726encoder1,(unsigned short*)p_g726encoder[0]);
  result &= GdspInitFunctionBlock((const unsigned short*)&g726decoder2,(unsigned short*)p_g726decoder[1]);
  result &= GdspInitFunctionBlock((const unsigned short*)&g726encoder2,(unsigned short*)p_g726encoder[1]);
  result &= GdspInitFunctionBlock((const unsigned short*)&g726decoder3,(unsigned short*)p_g726decoder[2]);
  result &= GdspInitFunctionBlock((const unsigned short*)&g726encoder3,(unsigned short*)p_g726encoder[2]);
  result &= GdspInitFunctionBlock((const unsigned short*)&g726decoder4,(unsigned short*)p_g726decoder[3]);
  result &= GdspInitFunctionBlock((const unsigned short*)&g726encoder4,(unsigned short*)p_g726encoder[3]);
  result &= GdspInitFunctionBlock((const unsigned short*)&g726decoder5,(unsigned short*)p_g726decoder[4]);
  result &= GdspInitFunctionBlock((const unsigned short*)&g726encoder5,(unsigned short*)p_g726encoder[4]);
  result &= GdspInitFunctionBlock((const unsigned short*)&g726decoder6,(unsigned short*)p_g726decoder[5]);
  result &= GdspInitFunctionBlock((const unsigned short*)&g726encoder6,(unsigned short*)p_g726encoder[5]);

  result &= GdspInitFunctionBlock((const unsigned short*)&dataArea0,(unsigned short*)p_dataArea0);
  result &= GdspInitFunctionBlock((const unsigned short*)&dataArea2,(unsigned short*)p_dataArea2);
  result &= GdspInitFunctionBlock((const unsigned short*)&dataArea4,(unsigned short*)p_dataArea4);
  result &= GdspInitFunctionBlock((const unsigned short*)&dataArea6,(unsigned short*)p_dataArea6);
  result &= GdspInitFunctionBlock((const unsigned short*)&dataArea8,(unsigned short*)p_dataArea8);
  result &= GdspInitFunctionBlock((const unsigned short*)&dataArea10,(unsigned short*)p_dataArea10);
  result &= GdspInitFunctionBlock((const unsigned short*)&dataArea12,(unsigned short*)p_dataArea12);
  result &= GdspInitFunctionBlock((const unsigned short*)&dataArea14,(unsigned short*)p_dataArea14);
  result &= GdspInitFunctionBlock((const unsigned short*)&dataArea16,(unsigned short*)p_dataArea16);
  result &= GdspInitFunctionBlock((const unsigned short*)&dataArea18,(unsigned short*)p_dataArea18);
  result &= GdspInitFunctionBlock((const unsigned short*)&dataArea20,(unsigned short*)p_dataArea20);
  result &= GdspInitFunctionBlock((const unsigned short*)&dataArea22,(unsigned short*)p_dataArea22);

  result &= GdspInitFunctionBlock((const unsigned short*)&stopcopyconstant,(unsigned short*)p_stopcopyconstant);

#ifdef ENABLE_TONEGEN
  result &= GdspInitFunctionBlock((const unsigned short*)&tonegen,(unsigned short*)p_tonegen);
  result &= GdspInitFunctionBlock((const unsigned short*)&law2lin,(unsigned short*)p_law2lin);
#endif
  result &= GdspInitFunctionBlock((const unsigned short*)&gendspcodecsource,(unsigned short*)p_gendspcodecsource);		// MIC in from AFE
  result &= GdspInitFunctionBlock((const unsigned short*)&gendspcodecdestinations,(unsigned short*)p_gendspcodecdestinations);
  result &= GdspInitFunctionBlock((const unsigned short*)&gendspgainconstant,(unsigned short*)p_gendspgainconstant_fp);

  result &= GdspInitFunctionBlock((const unsigned short*)&gain,(unsigned short*)p_gain_inbound);
  result &= GdspInitFunctionBlock((const unsigned short*)&gain,(unsigned short*)p_gain_spkr_fp);

  result &= GdspInitFunctionBlock((const unsigned short*)&dynmixer_pp,	(unsigned short*)p_dynmixer0);
  result &= GdspInitFunctionBlock((const unsigned short*)&dynmixer_pp,	(unsigned short*)p_dynmixer1);
  result &= GdspInitFunctionBlock((const unsigned short*)&dynmixer_pp,	(unsigned short*)p_dynmixer2);
  result &= GdspInitFunctionBlock((const unsigned short*)&dynmixer_pp,	(unsigned short*)p_dynmixer3);
  result &= GdspInitFunctionBlock((const unsigned short*)&dynmixer_pp,	(unsigned short*)p_dynmixer4);
  result &= GdspInitFunctionBlock((const unsigned short*)&dynmixer_pp,	(unsigned short*)p_dynmixer5);
  result &= GdspInitFunctionBlock((const unsigned short*)&dynmixer_post,(unsigned short*)p_dynmixer6);
  result &= GdspInitFunctionBlock((const unsigned short*)&dynmixer_pcm,	(unsigned short*)p_dynmixer7);

  if (GDSP_SUCCESS != result)
    PrintStatus(0, "*** GdspInitFunctionBlock() failed *** ");
  else
    PrintStatus(0, "*** GdspAdd() & GdspInitFunctionBlock() passed *** ");

  /*Connect speechbuffers to data areas*/
  GdspConnect(&(p_copySpeechBuffer1->data0start), &(p_dataArea0->taps[0]));
  GdspConnect(&(p_copySpeechBuffer1->data0end), &(p_dataArea0->taps[19]));
  GdspConnect(&(p_copySpeechBuffer1->SB0start), (unsigned short*) (SPEECHBUFFER0_OFS + 0x10000));
  GdspConnect(&(p_copySpeechBuffer1->SB2start),(unsigned short*) (SPEECHBUFFER2_OFS + 0x10000));
  GdspConnect(&(p_copySpeechBuffer1->SB2end), (unsigned short*) (SPEECHBUFFER2_OFS + 39 + 0x10000));
  GdspConnect(&(p_copySpeechBuffer1->data2start), &(p_dataArea2->taps[0]));

  GdspConnect(&(p_copySpeechBuffer1->data4start), &(p_dataArea4->taps[0]));
  GdspConnect(&(p_copySpeechBuffer1->data4end), &(p_dataArea4->taps[19]));
  GdspConnect(&(p_copySpeechBuffer1->SB4start), (unsigned short*) (SPEECHBUFFER4_OFS + 0x10000));
  GdspConnect(&(p_copySpeechBuffer1->SB6start),(unsigned short*) (SPEECHBUFFER6_OFS + 0x10000));
  GdspConnect(&(p_copySpeechBuffer1->SB6end), (unsigned short*) (SPEECHBUFFER6_OFS + 39 + 0x10000));
  GdspConnect(&(p_copySpeechBuffer1->data6start), &(p_dataArea6->taps[0]));

  GdspConnect(&(p_copySpeechBuffer1->data8start), &(p_dataArea8->taps[0]));
  GdspConnect(&(p_copySpeechBuffer1->data8end), &(p_dataArea8->taps[19]));
  GdspConnect(&(p_copySpeechBuffer1->SB8start), (unsigned short*) (SPEECHBUFFER8_OFS + 0x10000));
  GdspConnect(&(p_copySpeechBuffer1->SB10start),(unsigned short*) (SPEECHBUFFER10_OFS + 0x10000));
  GdspConnect(&(p_copySpeechBuffer1->SB10end), (unsigned short*) (SPEECHBUFFER10_OFS + 39 + 0x10000));
  GdspConnect(&(p_copySpeechBuffer1->data10start), &(p_dataArea10->taps[0]));

  GdspConnect(&(p_copySpeechBuffer1->data12start), &(p_dataArea12->taps[0]));
  GdspConnect(&(p_copySpeechBuffer1->data12end), &(p_dataArea12->taps[19]));
  GdspConnect(&(p_copySpeechBuffer1->SB12start), (unsigned short*) (SPEECHBUFFER12_OFS + 0x10000));
  GdspConnect(&(p_copySpeechBuffer1->SB14start),(unsigned short*) (SPEECHBUFFER14_OFS + 0x10000));
  GdspConnect(&(p_copySpeechBuffer1->SB14end), (unsigned short*) (SPEECHBUFFER14_OFS + 39 + 0x10000));
  GdspConnect(&(p_copySpeechBuffer1->data14start), &(p_dataArea14->taps[0]));

  GdspConnect(&(p_copySpeechBuffer1->data16start), &(p_dataArea16->taps[0]));
  GdspConnect(&(p_copySpeechBuffer1->data16end), &(p_dataArea16->taps[19]));
  GdspConnect(&(p_copySpeechBuffer1->SB16start), (unsigned short*) (SPEECHBUFFER16_OFS + 0x10000));
  GdspConnect(&(p_copySpeechBuffer1->SB18start),(unsigned short*) (SPEECHBUFFER18_OFS + 0x10000));
  GdspConnect(&(p_copySpeechBuffer1->SB18end), (unsigned short*) (SPEECHBUFFER18_OFS + 39 + 0x10000));
  GdspConnect(&(p_copySpeechBuffer1->data18start), &(p_dataArea18->taps[0]));

  GdspConnect(&(p_copySpeechBuffer1->data20start), &(p_dataArea20->taps[0]));
  GdspConnect(&(p_copySpeechBuffer1->data20end), &(p_dataArea20->taps[19]));
  GdspConnect(&(p_copySpeechBuffer1->SB20start), (unsigned short*) (SPEECHBUFFER20_OFS + 0x10000));
  GdspConnect(&(p_copySpeechBuffer1->SB22start),(unsigned short*) (SPEECHBUFFER22_OFS + 0x10000));
  GdspConnect(&(p_copySpeechBuffer1->SB22end), (unsigned short*) (SPEECHBUFFER22_OFS + 39 + 0x10000));
  GdspConnect(&(p_copySpeechBuffer1->data22start), &(p_dataArea22->taps[0]));

  //Connect pointers for decoders
  GdspConnect(&(p_g726decoder[0]->b_buf_start), &(p_dataArea2->taps[0]));
  GdspConnect(&(p_g726decoder[0]->b_buf_end), &(p_dataArea2->taps[19]));
  GdspConnect(&(p_g726decoder[0]->b_buf_ptr), &(p_dataArea2->taps[0]));
  GdspConnect(&(p_g726decoder[1]->b_buf_start), &(p_dataArea6->taps[0]));
  GdspConnect(&(p_g726decoder[1]->b_buf_end), &(p_dataArea6->taps[19]));
  GdspConnect(&(p_g726decoder[1]->b_buf_ptr), &(p_dataArea6->taps[0]));
  GdspConnect(&(p_g726decoder[2]->b_buf_start), &(p_dataArea10->taps[0]));
  GdspConnect(&(p_g726decoder[2]->b_buf_end), &(p_dataArea10->taps[19]));
  GdspConnect(&(p_g726decoder[2]->b_buf_ptr), &(p_dataArea10->taps[0]));
  GdspConnect(&(p_g726decoder[3]->b_buf_start), &(p_dataArea14->taps[0]));
  GdspConnect(&(p_g726decoder[3]->b_buf_end), &(p_dataArea14->taps[19]));
  GdspConnect(&(p_g726decoder[3]->b_buf_ptr), &(p_dataArea14->taps[0]));
  GdspConnect(&(p_g726decoder[4]->b_buf_start), &(p_dataArea18->taps[0]));
  GdspConnect(&(p_g726decoder[4]->b_buf_end), &(p_dataArea18->taps[19]));
  GdspConnect(&(p_g726decoder[4]->b_buf_ptr), &(p_dataArea18->taps[0]));
  GdspConnect(&(p_g726decoder[5]->b_buf_start), &(p_dataArea22->taps[0]));
  GdspConnect(&(p_g726decoder[5]->b_buf_end), &(p_dataArea22->taps[19]));
  GdspConnect(&(p_g726decoder[5]->b_buf_ptr), &(p_dataArea22->taps[0]));

  //Connect pointers for encoders
  GdspConnect(&(p_g726encoder[0]->b_buf_start), &(p_dataArea0->taps[0]));
  GdspConnect(&(p_g726encoder[0]->b_buf_end), &(p_dataArea0->taps[19]));
  GdspConnect(&(p_g726encoder[0]->b_buf_ptr), &(p_dataArea0->taps[0]));
  GdspConnect(&(p_g726encoder[1]->b_buf_start), &(p_dataArea4->taps[0]));
  GdspConnect(&(p_g726encoder[1]->b_buf_end), &(p_dataArea4->taps[19]));
  GdspConnect(&(p_g726encoder[1]->b_buf_ptr), &(p_dataArea4->taps[0]));
  GdspConnect(&(p_g726encoder[2]->b_buf_start), &(p_dataArea8->taps[0]));
  GdspConnect(&(p_g726encoder[2]->b_buf_end), &(p_dataArea8->taps[19]));
  GdspConnect(&(p_g726encoder[2]->b_buf_ptr), &(p_dataArea8->taps[0]));
  GdspConnect(&(p_g726encoder[3]->b_buf_start), &(p_dataArea12->taps[0]));
  GdspConnect(&(p_g726encoder[3]->b_buf_end), &(p_dataArea12->taps[19]));
  GdspConnect(&(p_g726encoder[3]->b_buf_ptr), &(p_dataArea12->taps[0]));
  GdspConnect(&(p_g726encoder[4]->b_buf_start), &(p_dataArea16->taps[0]));
  GdspConnect(&(p_g726encoder[4]->b_buf_end), &(p_dataArea16->taps[19]));
  GdspConnect(&(p_g726encoder[4]->b_buf_ptr), &(p_dataArea16->taps[0]));
  GdspConnect(&(p_g726encoder[5]->b_buf_start), &(p_dataArea20->taps[0]));
  GdspConnect(&(p_g726encoder[5]->b_buf_end), &(p_dataArea20->taps[19]));
  GdspConnect(&(p_g726encoder[5]->b_buf_ptr), &(p_dataArea20->taps[0]));

  // connect the CODEC_MIC to the gain_inbound block
  GdspConnect(&(p_gain_inbound->in_ptr), &(p_gendspcodecsource->codecdatainsrc));

  // NULL the unused PCM slot2, use PCM slot3 for sending commands
  GdspConnect(&(p_gendsppcmmasterdestinations->scrptr2), &(p_gendspgainconstant_fp->value));
  GdspConnect(&(p_gendsppcmmasterdestinations->scrptr3), &(p_gendsp_pcm_command_out->value));		// for sending cmds to other FP

  // connect PCM[3] to PCM buffer for receiving commands
  GdspConnect(&(p_pcm_buffer->in_ptr), &(p_gendsppcmsource->pcm3insrc));

  // Connect 7 sources to each of the mixer inputs
  // no ch0 input needed to mixer0
  GdspConnect(&(p_dynmixer0->inputs[0]), &(p_g726decoder[1]->g_out1));
  GdspConnect(&(p_dynmixer0->inputs[1]), &(p_g726decoder[2]->g_out1));
  GdspConnect(&(p_dynmixer0->inputs[2]), &(p_g726decoder[3]->g_out1));
  GdspConnect(&(p_dynmixer0->inputs[3]), &(p_g726decoder[4]->g_out1));
  GdspConnect(&(p_dynmixer0->inputs[4]), &(p_g726decoder[5]->g_out1));
  GdspConnect(&(p_dynmixer0->inputs[5]), &(p_gendspgainconstant_fp->value));			// NULL the PCM input initially
  GdspConnect(&(p_dynmixer0->inputs[6]), &(p_gain_inbound->out));

  // no ch1 input needed to mixer1
  GdspConnect(&(p_dynmixer1->inputs[0]), &(p_g726decoder[0]->g_out1));
  GdspConnect(&(p_dynmixer1->inputs[1]), &(p_g726decoder[2]->g_out1));
  GdspConnect(&(p_dynmixer1->inputs[2]), &(p_g726decoder[3]->g_out1));
  GdspConnect(&(p_dynmixer1->inputs[3]), &(p_g726decoder[4]->g_out1));
  GdspConnect(&(p_dynmixer1->inputs[4]), &(p_g726decoder[5]->g_out1));
  GdspConnect(&(p_dynmixer1->inputs[5]), &(p_gendspgainconstant_fp->value));			// NULL the PCM input initially
  GdspConnect(&(p_dynmixer1->inputs[6]), &(p_gain_inbound->out));

  // no ch2 input needed to mixer2
  GdspConnect(&(p_dynmixer2->inputs[0]), &(p_g726decoder[0]->g_out1));
  GdspConnect(&(p_dynmixer2->inputs[1]), &(p_g726decoder[1]->g_out1));
  GdspConnect(&(p_dynmixer2->inputs[2]), &(p_g726decoder[3]->g_out1));
  GdspConnect(&(p_dynmixer2->inputs[3]), &(p_g726decoder[4]->g_out1));
  GdspConnect(&(p_dynmixer2->inputs[4]), &(p_g726decoder[5]->g_out1));
  GdspConnect(&(p_dynmixer2->inputs[5]), &(p_gendspgainconstant_fp->value));			// NULL the PCM input initially
  GdspConnect(&(p_dynmixer2->inputs[6]), &(p_gain_inbound->out));

  // no ch3 input needed to mixer3
  GdspConnect(&(p_dynmixer3->inputs[0]), &(p_g726decoder[0]->g_out1));
  GdspConnect(&(p_dynmixer3->inputs[1]), &(p_g726decoder[1]->g_out1));
  GdspConnect(&(p_dynmixer3->inputs[2]), &(p_g726decoder[2]->g_out1));
  GdspConnect(&(p_dynmixer3->inputs[3]), &(p_g726decoder[4]->g_out1));
  GdspConnect(&(p_dynmixer3->inputs[4]), &(p_g726decoder[5]->g_out1));
  GdspConnect(&(p_dynmixer3->inputs[5]), &(p_gendspgainconstant_fp->value));			// NULL the PCM input initially
  GdspConnect(&(p_dynmixer3->inputs[6]), &(p_gain_inbound->out));

  // no ch4 input needed to mixer4
  GdspConnect(&(p_dynmixer4->inputs[0]), &(p_g726decoder[0]->g_out1));
  GdspConnect(&(p_dynmixer4->inputs[1]), &(p_g726decoder[1]->g_out1));
  GdspConnect(&(p_dynmixer4->inputs[2]), &(p_g726decoder[2]->g_out1));
  GdspConnect(&(p_dynmixer4->inputs[3]), &(p_g726decoder[3]->g_out1));
  GdspConnect(&(p_dynmixer4->inputs[4]), &(p_g726decoder[5]->g_out1));
  GdspConnect(&(p_dynmixer4->inputs[5]), &(p_gendspgainconstant_fp->value));			// NULL the PCM input initially
  GdspConnect(&(p_dynmixer4->inputs[6]), &(p_gain_inbound->out));

  // no ch5 input needed to mixer5
  GdspConnect(&(p_dynmixer5->inputs[0]), &(p_g726decoder[0]->g_out1));
  GdspConnect(&(p_dynmixer5->inputs[1]), &(p_g726decoder[1]->g_out1));
  GdspConnect(&(p_dynmixer5->inputs[2]), &(p_g726decoder[2]->g_out1));
  GdspConnect(&(p_dynmixer5->inputs[3]), &(p_g726decoder[3]->g_out1));
  GdspConnect(&(p_dynmixer5->inputs[4]), &(p_g726decoder[4]->g_out1));
  GdspConnect(&(p_dynmixer5->inputs[5]), &(p_gendspgainconstant_fp->value));			// NULL the PCM input initially
  GdspConnect(&(p_dynmixer5->inputs[6]), &(p_gain_inbound->out));

  // no MIC input needed to mixer6 - output to the post MIC and SPEAKER
  GdspConnect(&(p_dynmixer6->inputs[0]), &(p_g726decoder[0]->g_out1));
  GdspConnect(&(p_dynmixer6->inputs[1]), &(p_g726decoder[1]->g_out1));
  GdspConnect(&(p_dynmixer6->inputs[2]), &(p_g726decoder[2]->g_out1));
  GdspConnect(&(p_dynmixer6->inputs[3]), &(p_g726decoder[3]->g_out1));
  GdspConnect(&(p_dynmixer6->inputs[4]), &(p_g726decoder[4]->g_out1));
  GdspConnect(&(p_dynmixer6->inputs[5]), &(p_g726decoder[5]->g_out1));
  GdspConnect(&(p_dynmixer6->inputs[6]), &(p_gendspgainconstant_fp->value));			// NULL the PCM input initially

  // mixer7 to send to 2nd base
  GdspConnect(&(p_dynmixer7->inputs[0]), &(p_g726decoder[0]->g_out1));
  GdspConnect(&(p_dynmixer7->inputs[1]), &(p_g726decoder[1]->g_out1));
  GdspConnect(&(p_dynmixer7->inputs[2]), &(p_g726decoder[2]->g_out1));
  GdspConnect(&(p_dynmixer7->inputs[3]), &(p_g726decoder[3]->g_out1));
  GdspConnect(&(p_dynmixer7->inputs[4]), &(p_g726decoder[4]->g_out1));
  GdspConnect(&(p_dynmixer7->inputs[5]), &(p_g726decoder[5]->g_out1));
  GdspConnect(&(p_dynmixer7->inputs[6]), &(p_gain_inbound->out));

  //Connect outputs from mixer blocks to destinations
  GdspConnect(&(p_g726encoder[0]->g_in1_ptr), &(p_dynmixer0->out));
  GdspConnect(&(p_g726encoder[1]->g_in1_ptr), &(p_dynmixer1->out));
  GdspConnect(&(p_g726encoder[2]->g_in1_ptr), &(p_dynmixer2->out));
  GdspConnect(&(p_g726encoder[3]->g_in1_ptr), &(p_dynmixer3->out));
  GdspConnect(&(p_g726encoder[4]->g_in1_ptr), &(p_dynmixer4->out));
  GdspConnect(&(p_g726encoder[5]->g_in1_ptr), &(p_dynmixer5->out));
  GdspConnect(&(p_gain_spkr_fp->in_ptr), &(p_dynmixer6->out));							// audio out to post gain block
  GdspConnect(&(p_gendspcodecdestinations->codecdataoutsrc), &(p_gain_spkr_fp->out));	// gain block out to post

  //Workaround counters
  GdspConnect(&(p_copySpeechBuffer1->inputToCounter), &(p_copySpeechBuffer1->counter));
  GdspConnect(&(p_clearPointers1->inputToCounter), &(p_clearPointers1->counter));

  //Connect pointers for clearing routine
  GdspConnect(&(p_clearPointers1->sourceStart), &(p_clearPointers1->pointer1));
  GdspConnect(&(p_clearPointers1->sourceEnd), &(p_clearPointers1->pointer14));
  GdspConnect(&(p_clearPointers1->destinationBegin), &(p_clearPointers1->pointer1dest));

  GdspConnect(&(p_clearPointers1->pointer1), &(p_stopcopyconstant->value));
  GdspConnect(&(p_clearPointers1->pointer1dest), &(p_copySpeechBuffer1->copycondition));
  GdspConnect(&(p_clearPointers1->pointer2), &(p_stopcopyconstant->value));
  GdspConnect(&(p_clearPointers1->pointer2dest), &(p_clearPointers1->clearcondition));

  GdspConnect(&(p_clearPointers1->pointer3), &(p_g726decoder[0]->b_buf_start));
  GdspConnect(&(p_clearPointers1->pointer3dest), &(p_g726decoder[0]->b_buf_ptr));
  GdspConnect(&(p_clearPointers1->pointer4), &(p_g726encoder[0]->b_buf_start));
  GdspConnect(&(p_clearPointers1->pointer4dest), &(p_g726encoder[0]->b_buf_ptr));

  GdspConnect(&(p_clearPointers1->pointer5), &(p_g726decoder[1]->b_buf_start));
  GdspConnect(&(p_clearPointers1->pointer5dest), &(p_g726decoder[1]->b_buf_ptr));
  GdspConnect(&(p_clearPointers1->pointer6), &(p_g726encoder[1]->b_buf_start));
  GdspConnect(&(p_clearPointers1->pointer6dest), &(p_g726encoder[1]->b_buf_ptr));

  GdspConnect(&(p_clearPointers1->pointer7), &(p_g726decoder[2]->b_buf_start));
  GdspConnect(&(p_clearPointers1->pointer7dest), &(p_g726decoder[2]->b_buf_ptr));
  GdspConnect(&(p_clearPointers1->pointer8), &(p_g726encoder[2]->b_buf_start));
  GdspConnect(&(p_clearPointers1->pointer8dest), &(p_g726encoder[2]->b_buf_ptr));

  GdspConnect(&(p_clearPointers1->pointer9), &(p_g726decoder[3]->b_buf_start));
  GdspConnect(&(p_clearPointers1->pointer9dest), &(p_g726decoder[3]->b_buf_ptr));
  GdspConnect(&(p_clearPointers1->pointer10), &(p_g726encoder[3]->b_buf_start));
  GdspConnect(&(p_clearPointers1->pointer10dest), &(p_g726encoder[3]->b_buf_ptr));

  GdspConnect(&(p_clearPointers1->pointer11), &(p_g726decoder[4]->b_buf_start));
  GdspConnect(&(p_clearPointers1->pointer11dest), &(p_g726decoder[4]->b_buf_ptr));
  GdspConnect(&(p_clearPointers1->pointer12), &(p_g726encoder[4]->b_buf_start));
  GdspConnect(&(p_clearPointers1->pointer12dest), &(p_g726encoder[4]->b_buf_ptr));

  GdspConnect(&(p_clearPointers1->pointer13), &(p_g726decoder[5]->b_buf_start));
  GdspConnect(&(p_clearPointers1->pointer13dest), &(p_g726decoder[5]->b_buf_ptr));
  GdspConnect(&(p_clearPointers1->pointer14), &(p_g726encoder[5]->b_buf_start));
  GdspConnect(&(p_clearPointers1->pointer14dest), &(p_g726encoder[5]->b_buf_ptr));

#ifdef ENABLE_TONEGEN
  GdspConnect(&(p_law2lin->lawin_ptr), &(p_playbackbuffer->out));

  p_tonegen->timerpreset2=0xFFFF; // no off tone
#endif

  result &= GdspStart((unsigned short*)p_gendsppcmsource);
  result &= GdspStart((unsigned short*)p_gendsppcmmasterdestinations);
  result &= GdspStart((unsigned short*)p_pcm_buffer);

#ifdef ENABLE_TONEGEN
  result &= GdspStart((unsigned short*) p_playbackbuffer);
#endif
  if (GDSP_SUCCESS != result)
    PrintStatus(0, "*** B GdspStart() failed *** ");

  result &= GdspStart((unsigned short*)p_copySpeechBuffer1);
  result &= GdspStart((unsigned short*)p_clearPointers1);
  for (i=0;i<6;i++)
  {
    result &= GdspStart((unsigned short*)p_g726decoder[i]);
    result &= GdspStart((unsigned short*)p_g726encoder[i]);
  }

#ifdef ENABLE_TONEGEN
  result &= GdspStart((unsigned short*)p_tonegen);
#endif
  result &= GdspStart((unsigned short*)p_gendspcodecsource);		// MIC in from AFE
  result &= GdspStart((unsigned short*)p_gendspcodecdestinations);

  result &= GdspStart((unsigned short*)p_gain_inbound);
  result &= GdspStart((unsigned short*)p_gain_spkr_fp);

  result &= GdspStart((unsigned short*)p_dynmixer0);
  result &= GdspStart((unsigned short*)p_dynmixer1);
  result &= GdspStart((unsigned short*)p_dynmixer2);
  result &= GdspStart((unsigned short*)p_dynmixer3);
  result &= GdspStart((unsigned short*)p_dynmixer4);
  result &= GdspStart((unsigned short*)p_dynmixer5);
  result &= GdspStart((unsigned short*)p_dynmixer6);
  result &= GdspStart((unsigned short*)p_dynmixer7);

  return result;
}

void MuteDSPCopyBuffer(unsigned char mute)
{
  if (mute)
  {
    PrintStatus(0, "MuteCopyBuffer Mute");
    GdspConnect(&(p_copySpeechBuffer1->SB2start),(unsigned short*) dum_silent_buffer );
    GdspConnect(&(p_copySpeechBuffer1->SB2end), (unsigned short*) &(dum_silent_buffer[39]));
    GdspConnect(&(p_copySpeechBuffer1->SB6start),(unsigned short*) dum_silent_buffer);
    GdspConnect(&(p_copySpeechBuffer1->SB6end), (unsigned short*) &(dum_silent_buffer[39]));
    GdspConnect(&(p_copySpeechBuffer1->SB10start),(unsigned short*) dum_silent_buffer);
    GdspConnect(&(p_copySpeechBuffer1->SB10end), (unsigned short*) &(dum_silent_buffer[39]));
    GdspConnect(&(p_copySpeechBuffer1->SB14start),(unsigned short*) dum_silent_buffer);
    GdspConnect(&(p_copySpeechBuffer1->SB14end), (unsigned short*) &(dum_silent_buffer[39]));
    GdspConnect(&(p_copySpeechBuffer1->SB18start),(unsigned short*) dum_silent_buffer);
    GdspConnect(&(p_copySpeechBuffer1->SB18end), (unsigned short*) &(dum_silent_buffer[39]));
    GdspConnect(&(p_copySpeechBuffer1->SB22start),(unsigned short*) dum_silent_buffer);
    GdspConnect(&(p_copySpeechBuffer1->SB22end), (unsigned short*) &(dum_silent_buffer[39]));
  }
  else
  {
    PrintStatus(0, "MuteCopyBuffer UnMute");
    GdspConnect(&(p_copySpeechBuffer1->SB2start),(unsigned short*) (SPEECHBUFFER2_OFS + 0x10000));
    GdspConnect(&(p_copySpeechBuffer1->SB2end), (unsigned short*) (SPEECHBUFFER2_OFS + 39 + 0x10000));
    GdspConnect(&(p_copySpeechBuffer1->SB6start),(unsigned short*) (SPEECHBUFFER6_OFS + 0x10000));
    GdspConnect(&(p_copySpeechBuffer1->SB6end), (unsigned short*) (SPEECHBUFFER6_OFS + 39 + 0x10000));
    GdspConnect(&(p_copySpeechBuffer1->SB10start),(unsigned short*) (SPEECHBUFFER10_OFS + 0x10000));
    GdspConnect(&(p_copySpeechBuffer1->SB10end), (unsigned short*) (SPEECHBUFFER10_OFS + 39 + 0x10000));
    GdspConnect(&(p_copySpeechBuffer1->SB14start),(unsigned short*) (SPEECHBUFFER14_OFS + 0x10000));
    GdspConnect(&(p_copySpeechBuffer1->SB14end), (unsigned short*) (SPEECHBUFFER14_OFS + 39 + 0x10000));
    GdspConnect(&(p_copySpeechBuffer1->SB18start),(unsigned short*) (SPEECHBUFFER18_OFS + 0x10000));
    GdspConnect(&(p_copySpeechBuffer1->SB18end), (unsigned short*) (SPEECHBUFFER18_OFS + 39 + 0x10000));
    GdspConnect(&(p_copySpeechBuffer1->SB22start),(unsigned short*) (SPEECHBUFFER22_OFS + 0x10000));
    GdspConnect(&(p_copySpeechBuffer1->SB22end), (unsigned short*) (SPEECHBUFFER22_OFS + 39 + 0x10000));
  }
}

#ifdef ENABLE_TONEGEN
void EnableTonegeneratorFPToMixer(void)
{
  // HM Testing
    int i;
    for (i=0;i<6;i++)
    {
      p_dynmixer0->weights[i] = 0x0000;
      p_dynmixer1->weights[i] = 0x0000;
      p_dynmixer2->weights[i] = 0x0000;
      p_dynmixer3->weights[i] = 0x0000;
      p_dynmixer4->weights[i] = 0x0000;
      p_dynmixer5->weights[i] = 0x0000;
      p_dynmixer6->weights[i] = 0x0000;
      p_dynmixer7->weights[i] = 0x0000;
    }

    /*GdspConnect(&(p_dynmixer0->inputs[6]), &(p_law2lin->linear_out));
    GdspConnect(&(p_dynmixer1->inputs[6]),&(p_law2lin->linear_out));
    GdspConnect(&(p_dynmixer2->inputs[6]),&(p_law2lin->linear_out));
    GdspConnect(&(p_dynmixer3->inputs[6]),&(p_law2lin->linear_out));
    GdspConnect(&(p_dynmixer4->inputs[6]),&(p_law2lin->linear_out));
    GdspConnect(&(p_dynmixer5->inputs[6]),&(p_law2lin->linear_out));
    GdspConnect(&(p_dynmixer6->inputs[6]),&(p_law2lin->linear_out));
    GdspConnect(&(p_dynmixer7->inputs[6]),&(p_law2lin->linear_out));*/

	GdspConnect(&(p_dynmixer0->inputs[6]), &(p_tonegen->tone_out));
    GdspConnect(&(p_dynmixer1->inputs[6]), &(p_tonegen->tone_out));
    GdspConnect(&(p_dynmixer2->inputs[6]), &(p_tonegen->tone_out));
    GdspConnect(&(p_dynmixer3->inputs[6]), &(p_tonegen->tone_out));
    GdspConnect(&(p_dynmixer4->inputs[6]), &(p_tonegen->tone_out));
    GdspConnect(&(p_dynmixer5->inputs[6]), &(p_tonegen->tone_out));
    GdspConnect(&(p_dynmixer6->inputs[6]), &(p_tonegen->tone_out));
    GdspConnect(&(p_dynmixer7->inputs[6]), &(p_tonegen->tone_out));

    GdspConnect(&(p_g726encoder[0]->g_in1_ptr), &(p_tonegen->tone_out));
    GdspConnect(&(p_g726encoder[1]->g_in1_ptr), &(p_tonegen->tone_out));
    GdspConnect(&(p_g726encoder[2]->g_in1_ptr), &(p_tonegen->tone_out));
    GdspConnect(&(p_g726encoder[3]->g_in1_ptr), &(p_tonegen->tone_out));
    GdspConnect(&(p_g726encoder[4]->g_in1_ptr), &(p_tonegen->tone_out));
    GdspConnect(&(p_g726encoder[5]->g_in1_ptr), &(p_tonegen->tone_out));
}
#endif

void ConnectPCM(void)
{
	// connect audio in from PCM[0] bus when it is known that a second FP is present
	GdspConnect(&(p_dynmixer0->inputs[5]), &(p_gendsppcmsource->pcm0insrc));			// entire conference audio in from other base on PCM[0]
	GdspConnect(&(p_dynmixer1->inputs[5]), &(p_gendsppcmsource->pcm0insrc));			// entire conference audio in from other base on PCM[0]
	GdspConnect(&(p_dynmixer2->inputs[5]), &(p_gendsppcmsource->pcm0insrc));			// entire conference audio in from other base on PCM[0]
	GdspConnect(&(p_dynmixer3->inputs[5]), &(p_gendsppcmsource->pcm0insrc));			// entire conference audio in from other base on PCM[0]
	GdspConnect(&(p_dynmixer4->inputs[5]), &(p_gendsppcmsource->pcm0insrc));			// entire conference audio in from other base on PCM[0]
	GdspConnect(&(p_dynmixer5->inputs[5]), &(p_gendsppcmsource->pcm0insrc));			// entire conference audio in from other base on PCM[0]
	GdspConnect(&(p_gendsppcmmasterdestinations->scrptr0), &(p_dynmixer7->out));		// entire conference audio out to other base on PCM[0]
	// connect audio without PAGED PPs on PCM[1] bus for use at POST
	if (P3_DATA_REG & Px_7_DATA)
		GdspConnect(&(p_dynmixer6->inputs[6]), &(p_gendsppcmsource->pcm1insrc));		// audio from second base (without PAGED PPs for post) on PCM[1]
	else
		GdspConnect(&(p_gendsppcmmasterdestinations->scrptr1), &(p_dynmixer6->out));	// audio out to first base (without PAGED PPs for post) on PCM[1]
}
