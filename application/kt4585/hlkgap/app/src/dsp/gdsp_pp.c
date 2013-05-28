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
* $History:: gdsp_pp.c                                                        $ *
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
#include "../../../../../../include/common/include/print_status.h"

int ES7=0;
extern unsigned char lastinit_error;
int gen2dspblock_init_pp(GDSP_INIT_STRUCT *init_str,GDSP_INTERFACE_INIT_STRUCT *interface_str)
{
  BYTE result = GDSP_SUCCESS;

  if (CHIP_TEST1_REG==0x12)
	ES7=1; // the ES7 revision has some bugs regarding PAEC

  InitDSPCODEC();                     // Codec initialization
  InitInterrupts(*init_str);           // Initialize Gen2DSP triggers & interrupts

  result &= InitGdspInterface(*interface_str);
  if(GDSP_SUCCESS != result) {PrintStatus(0,"-A-");return GDSP_NO_SUCCESS;}
  result &= GdspInit(*init_str);
  if(GDSP_SUCCESS != result) {PrintStatus(0,"-1-");return GDSP_NO_SUCCESS;}
  // Start of API Calls to build a DSP application

  /****************************************************************************
   *  Copy user function to ram here                                         *
   ****************************************************************************/
  // HM Note, currently no user functions
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
  result &= GdspAdd((const unsigned long*)&gendsppcmsource_code,sizeof(gendsppcmsource_code)/4,(unsigned short**)&p_gendsppcmsource,sizeof(gdsp_pcmsource)/2,DSP1_8KHZ);
  result &= GdspAdd((const unsigned long*)&gendsppcmmasterdestinations_code,sizeof(gendsppcmmasterdestinations_code)/4,(unsigned short**)&p_gendsppcmmasterdestinations,sizeof(gdsp_pcmmasterdestinations)/2,DSP1_8KHZ);
  result &= GdspAdd((const unsigned long*)&gendspcodecdestinations_code,sizeof(gendspcodecdestinations_code)/4,(unsigned short**)&p_gendspcodecdestinations,sizeof(gdsp_codecdestinations)/2,DSP1_8KHZ);
  result &= GdspAdd((const unsigned long*)&g726decoder_code,sizeof(g726decoder_code)/4,(unsigned short**)&p_g726decoder_pp,sizeof(gdsp_adpcmnbdecoder)/2,DSP1_8KHZ);
  result &= GdspAdd((const unsigned long*)&playbackbuffer_code,sizeof(playbackbuffer_code)/4,(unsigned short**)&p_playbackbuffer,sizeof(gdsp_playbackbuffer_18)/2,DSP1_8KHZ);
  result &= GdspAdd((const unsigned long*)&gain_code,sizeof(gain_code)/4,(unsigned short**)&p_gain_encoder_pp,sizeof(gdsp_gain)/2,DSP1_8KHZ);
  result &= GdspAdd((const unsigned long*)&gain_code,sizeof(gain_code)/4,(unsigned short**)&p_gain_decoder_pp,sizeof(gdsp_gain)/2,DSP1_8KHZ);
  result &= GdspAdd((const unsigned long*)&gain_code,sizeof(gain_code)/4,(unsigned short**)&p_gain_spkr_pp,sizeof(gdsp_gain)/2,DSP1_8KHZ);
  result &= GdspAdd((const unsigned long*)&g726encoder_code,sizeof(g726encoder_code)/4,(unsigned short**)&p_g726encoder_pp,sizeof(gdsp_adpcmnbencoder)/2,DSP1_8KHZ);
  result &= GdspAdd((const unsigned long*)&summator_code,sizeof(summator_code)/4,(unsigned short**)&p_summator,sizeof(gdsp_summator)/2,DSP1_8KHZ);
  result &= GdspAdd((const unsigned long*)&tonegen_code,sizeof(tonegen_code)/4,(unsigned short**)&p_tonegen,sizeof(gdsp_tonegen)/2,DSP1_8KHZ);
  result &= GdspAdd((const unsigned long*)&law2lin_code,sizeof(law2lin_code)/4,(unsigned short**)&p_law2lin,sizeof(gdsp_lawlin)/2,DSP1_8KHZ);
  result &= GdspAdd((const unsigned long*)0,0,(unsigned short**)&p_gendspgainconstant_pp,sizeof(gdsp_constant)/2,DSP1_8KHZ);
  result &= GdspAdd((const unsigned long*)0,0,(unsigned short**)&p_gendspgainconstant_encoder,sizeof(gdsp_constant)/2,DSP1_8KHZ);

  if (GDSP_SUCCESS != result)
    PrintStatus(0, "*** GdspAdd() failed *** ");
  if (GDSP_SUCCESS != result)
    return GDSP_NO_SUCCESS;

  result &= GdspInitFunctionBlock((const unsigned short*)&gendsppcmsource,(unsigned short*)p_gendsppcmsource);
  result &= GdspInitFunctionBlock((const unsigned short*)&gendsppcmmasterdestinations,(unsigned short*)p_gendsppcmmasterdestinations);
  result &= GdspInitFunctionBlock((const unsigned short*)&gendspcodecdestinations,(unsigned short*)p_gendspcodecdestinations);
  result &= GdspInitFunctionBlock((const unsigned short*)&g726decoder,(unsigned short*)p_g726decoder_pp);
  result &= GdspInitFunctionBlock((const unsigned short*)&playbackbuffer,(unsigned short*)p_playbackbuffer);
  result &= GdspInitFunctionBlock((const unsigned short*)&gain,(unsigned short*)p_gain_encoder_pp);
  result &= GdspInitFunctionBlock((const unsigned short*)&gain,(unsigned short*)p_gain_decoder_pp);
  result &= GdspInitFunctionBlock((const unsigned short*)&gain,(unsigned short*)p_gain_spkr_pp);
  result &= GdspInitFunctionBlock((const unsigned short*)&g726encoder,(unsigned short*)p_g726encoder_pp);
  result &= GdspInitFunctionBlock((const unsigned short*)&summator,(unsigned short*)p_summator);
  result &= GdspInitFunctionBlock((const unsigned short*)&tonegen,(unsigned short*)p_tonegen);
  result &= GdspInitFunctionBlock((const unsigned short*)&law2lin,(unsigned short*)p_law2lin);
  result &= GdspInitFunctionBlock((const unsigned short*)&gendspgainconstant,(unsigned short*)p_gendspgainconstant_pp);
  result &= GdspInitFunctionBlock((const unsigned short*)&gendspgainconstant,(unsigned short*)p_gendspgainconstant_encoder);

  if (GDSP_SUCCESS != result)
    PrintStatus(0, "*** GdspInitFunctionBlock() failed *** ");
  else
    PrintStatus(0, "*** GdspAdd() & GdspInitFunctionBlock() passed *** ");

  // Connect pointers for p_g726encoder
  GdspConnect(&(p_g726encoder_pp->g_in1_ptr), &(p_gain_encoder_pp->out)); 				// from pre encoder gain block

  // Connect pointers for p_law2lin
  GdspConnect(&(p_law2lin->lawin_ptr), &(p_playbackbuffer->out));

  // Connect pointers for p_summator - adds .WAV files to headset output
  p_summator->in1_atten = 0x7FFF;														// multiply in1_ptr by 1.00 for 0dB atten of audio
  GdspConnect(&(p_summator->in1_ptr), &(p_g726decoder_pp->g_out1));						// audio in from decoder
  GdspConnect(&(p_summator->in2_ptr), &(p_law2lin->linear_out));						// .wav files input
  GdspConnect(&(p_summator->in3_ptr), &(p_gendspgainconstant_pp->value));				// .wav files atten

  // Connect pointers for p_gendsppcmmasterdestinations: route to PCM[0] to BC5
  GdspConnect(&(p_gain_decoder_pp->in_ptr), &(p_summator->out));						// route audio to variable gain block
  GdspConnect(&(p_gendsppcmmasterdestinations->scrptr0), &(p_gain_decoder_pp->out));	// route audio to PCM[0] to BC5 for Echo Cancellation

  // Connect pointers for p_gain_encoder_pp
  GdspConnect(&(p_gain_encoder_pp->in_ptr), &(p_gendsppcmsource->pcm0insrc));			// connect PCM[0] from BC5 MIC to GAIN input

  // Connect pointers for LSR
  GdspConnect(&(p_gain_spkr_pp->in_ptr), &(p_gendsppcmsource->pcm1insrc));				// connect gain_spkr_pp from PCM[1] from BC5 Echo Cancellation
  GdspConnect(&(p_gendspcodecdestinations->codecdataoutsrc), &(p_gain_spkr_pp->out));	// codecdataoutsrc = LSR

  // Start routines
  result &= GdspStart((unsigned short*)p_gendsppcmsource);
  result &= GdspStart((unsigned short*)p_gendsppcmmasterdestinations);
  result &= GdspStart((unsigned short*)p_gendspcodecdestinations);
  result &= GdspStart((unsigned short*)p_g726decoder_pp);
  result &= GdspStart((unsigned short*)p_playbackbuffer);
  result &= GdspStart((unsigned short*)p_gain_encoder_pp);
  result &= GdspStart((unsigned short*)p_gain_decoder_pp);
  result &= GdspStart((unsigned short*)p_gain_spkr_pp);
  result &= GdspStart((unsigned short*)p_g726encoder_pp);
  result &= GdspStart((unsigned short*)p_summator);
  result &= GdspStart((unsigned short*)p_tonegen);
  result &= GdspStart((unsigned short*)p_law2lin);

  return result;
}
unsigned char global_dsp_debug_path = 0;
void gdsp_BC5SpeakerPath(unsigned char bypass)
{
  char *tmp;
  tmp = StringPrint(StatusString, "gdsp_BC5SpeakerPath[");
  tmp = StrPrintHexByte(tmp, bypass);
  tmp = StringPrint(tmp, "]");
  PrintStatus(0, StatusString);
  global_dsp_debug_path = bypass;
  if (bypass & 0x01)		// HM inserted for test - bypass PCM bus and BC5
	GdspConnect(&(p_gain_spkr_pp->in_ptr), &(p_g726decoder_pp->g_out1));
  if (bypass & 0x02)		// mute speaker before gain
    GdspConnect(&(p_gain_spkr_pp->in_ptr), &(p_gendspgainconstant_pp->value));
  if (bypass & 0x04)		// mute speaker before LSR register
    GdspConnect(&(p_gendspcodecdestinations->codecdataoutsrc), &(p_gendspgainconstant_pp->value));
  if (bypass & 0x08)		// Connect from our microphone
    GdspConnect(&(p_gendspcodecdestinations->codecdataoutsrc), &(p_gain_encoder_pp->out));
  if (bypass & 0x10)		// Connect from GainVolume out to GainSpkrVolume in
    GdspConnect(&(p_gain_spkr_pp->in_ptr), &(p_gain_encoder_pp->out));
  if (bypass & 0x20)		// Connect from PCM0 out to LSR
    GdspConnect(&(p_gendspcodecdestinations->codecdataoutsrc), &(p_gendsppcmsource->pcm0insrc));
  if (bypass & 0x40)		// Connect from PCM0 out to pre LSR gain
    GdspConnect(&(p_gain_spkr_pp->in_ptr), &(p_gendsppcmsource->pcm0insrc));
  if (bypass & 0x80)		// Connect from post decoder gain to LSR
	GdspConnect(&(p_gendspcodecdestinations->codecdataoutsrc), &(p_gain_decoder_pp->out));
}

int reinit_tonegenerator_pp(void)
{
  BYTE result = GDSP_SUCCESS;
  result &= GdspInitFunctionBlock((const unsigned short*)&tonegen,(unsigned short*)p_tonegen);
  result &= GdspInitFunctionBlock((const unsigned short*)&law2lin,(unsigned short*)p_law2lin);
  return result;
}
