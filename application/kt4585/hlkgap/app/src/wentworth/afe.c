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
* $History:: afe.c                                                           $ *
*                                                                               *
* Initial Revision                                                              *
*********************************************************************************
*/
// Audio Front End module
#include "../../../../../../include/common/include/print_status.h"
#include "../../../../../../include/os/include/os_timer.h"
#include "../../../../../../include/mac/eeprom/include/fnvm.h"
#include "../dsp/gdsp_all_inits.h"
#include "afe.h"
#include "wentworth_pp.h"
#include "wentworth_fp.h"

void AFEInit(void)
{

}

/**********************************************************************************
 * final dB =
 *       input multiplied by pre_attn/0x7FFF (attenuates by specified dB)
 *       left shift n times (each shift adds 6dB)
 *       multiply by post_attn/0x7FFF (attenuates by specified dB)
 *
 * formula for gain block implemented below is as follows:
 * for -10dB to -60dB: pre-attn = -n dB
 * for -1dB to -9dB: pre_attn = 1/2(-n dB), shift = 0, post_attn = 1/2(-n dB)
 * for 0dB: pre_attn = 0x8000, shift = 0, post_Attn = 0x8000 (0x8000 = -1)
 * for 1dB to 18dB: pre_attn = 1/2(-y dB), shift = x, post_attn = 1/2(-y dB)
 *      where x = ceiling(n dB/6) and y = (6*x - n)
 **********************************************************************************/
static void SetPGain(gdsp_gain *p_g,int vol_set)
{
//char *ptr;
//ptr = StringPrint(StatusString, "SetPGain[");
//ptr = StrPrintDecByte(ptr, vol_set);
//ptr = StringPrint(ptr, "]");
//PrintStatus(0, StatusString);
	// 0 is mute , 7 is 100%
	switch (vol_set)
	{
    case -60: p_g->pre_attn=0x0021; p_g->shift=0x0000; p_g->post_attn=0x7FFF; break;	// -60dB
    case -40: p_g->pre_attn=0x0148; p_g->shift=0x0000; p_g->post_attn=0x7FFF; break;	// -40dB
    case -20: p_g->pre_attn=0x0CCD; p_g->shift=0x0000; p_g->post_attn=0x7FFF; break;	// -20dB
    case -19: p_g->pre_attn=0x0E5C; p_g->shift=0x0000; p_g->post_attn=0x7FFF; break;	// -19dB
    case -18: p_g->pre_attn=0x101D; p_g->shift=0x0000; p_g->post_attn=0x7FFF; break;	// -18dB
    case -17: p_g->pre_attn=0x1214; p_g->shift=0x0000; p_g->post_attn=0x7FFF; break;	// -17dB
    case -16: p_g->pre_attn=0x1449; p_g->shift=0x0000; p_g->post_attn=0x7FFF; break;	// -16dB
    case -15: p_g->pre_attn=0x16C2; p_g->shift=0x0000; p_g->post_attn=0x7FFF; break;	// -15dB
    case -14: p_g->pre_attn=0x1989; p_g->shift=0x0000; p_g->post_attn=0x7FFF; break;	// -14dB
    case -13: p_g->pre_attn=0x1CA7; p_g->shift=0x0000; p_g->post_attn=0x7FFF; break;	// -13dB
    case -12: p_g->pre_attn=0x2026; p_g->shift=0x0000; p_g->post_attn=0x7FFF; break;	// -12dB
    case -11: p_g->pre_attn=0x2412; p_g->shift=0x0000; p_g->post_attn=0x7FFF; break;	// -11dB
    case -10: p_g->pre_attn=0x287A; p_g->shift=0x0000; p_g->post_attn=0x7FFF; break;	// -10dB
    case -9: p_g->pre_attn=0x4C3E; p_g->shift=0x0000; p_g->post_attn=0x4C3E; break;		// -9dB
    case -8: p_g->pre_attn=0x50C2; p_g->shift=0x0000; p_g->post_attn=0x50C2; break;		// -8dB
    case -7: p_g->pre_attn=0x558B; p_g->shift=0x0000; p_g->post_attn=0x558B; break;		// -7dB
    case -6: p_g->pre_attn=0x5A9D; p_g->shift=0x0000; p_g->post_attn=0x5A9D; break;		// -6dB
    case -5: p_g->pre_attn=0x5FFB; p_g->shift=0x0000; p_g->post_attn=0x5FFB; break;		// -5dB
    case -4: p_g->pre_attn=0x65AB; p_g->shift=0x0000; p_g->post_attn=0x65AB; break;		// -4dB
    case -3: p_g->pre_attn=0x6BB1; p_g->shift=0x0000; p_g->post_attn=0x6BB1; break;		// -3dB
    case -2: p_g->pre_attn=0x7213; p_g->shift=0x0000; p_g->post_attn=0x7213; break;		// -2dB
    case -1: p_g->pre_attn=0x78D7; p_g->shift=0x0000; p_g->post_attn=0x78D7; break;		// -1dB
    case 0: p_g->pre_attn=0x8000; p_g->shift=0x0000; p_g->post_attn=0x8000; break;		// 0 dB
    case 1: p_g->pre_attn=0x5FDF; p_g->shift=0x0001; p_g->post_attn=0x5FDF; break;		// 1 dB
    case 2: p_g->pre_attn=0x658E; p_g->shift=0x0001; p_g->post_attn=0x658E; break;		// 2 dB
    case 3: p_g->pre_attn=0x6B92; p_g->shift=0x0001; p_g->post_attn=0x6B92; break;		// 3 dB
    case 4: p_g->pre_attn=0x71F2; p_g->shift=0x0001; p_g->post_attn=0x71F2; break;		// 4 dB
    case 5: p_g->pre_attn=0x78B2; p_g->shift=0x0001; p_g->post_attn=0x78B2; break;		// 5 dB
    case 6: p_g->pre_attn=0x7FB2; p_g->shift=0x0001; p_g->post_attn=0x7FB2; break;		// 6 dB
    case 7: p_g->pre_attn=0x5FC2; p_g->shift=0x0002; p_g->post_attn=0x5FC2; break;		// 7 dB
    case 8: p_g->pre_attn=0x656F; p_g->shift=0x0002; p_g->post_attn=0x656F; break;		// 8 dB
    case 9: p_g->pre_attn=0x6B72; p_g->shift=0x0002; p_g->post_attn=0x6B72; break;		// 9 dB
    case 10: p_g->pre_attn=0x71CF; p_g->shift=0x0002; p_g->post_attn=0x71CF; break; 	// 10 dB
    case 11: p_g->pre_attn=0x788E; p_g->shift=0x0002; p_g->post_attn=0x788E; break;		// 11 dB
    case 12: p_g->pre_attn=0x7FB2; p_g->shift=0x0002; p_g->post_attn=0x7FB2; break;		// 12 dB
    case 13: p_g->pre_attn=0x5FA5; p_g->shift=0x0003; p_g->post_attn=0x5FA5; break;		// 13 dB
    case 14: p_g->pre_attn=0x6550; p_g->shift=0x0003; p_g->post_attn=0x6550; break;		// 14 dB
    case 15: p_g->pre_attn=0x6B51; p_g->shift=0x0003; p_g->post_attn=0x6B51; break;		// 15 dB
    case 16: p_g->pre_attn=0x71AD; p_g->shift=0x0003; p_g->post_attn=0x71AD; break;		// 16 dB
    case 17: p_g->pre_attn=0x7869; p_g->shift=0x0003; p_g->post_attn=0x7869; break;		// 17 dB
    case 18: p_g->pre_attn=0x7F8C; p_g->shift=0x0003; p_g->post_attn=0x7F8C; break;		// 18 dB
    default: PrintStatus(0, "SetPGain() request not supported"); break;
	}
}

unsigned char mic_val=0;
unsigned char AFEGetCodecMicGain(void)
{
	return mic_val; //?
}

extern void SetMicGain(unsigned char value);
void AFESetCodecMicGain(unsigned char value)
{
	SetMicGain(value);
	mic_val = value;
}

void AFESetVolume(int vol_set)
{
	SetPGain(p_gain_encoder_pp, vol_set);
}

void AFESetGainInboundVolumePP(int vol_set)
{
	SetPGain(p_gain_decoder_pp, vol_set);						// sets post decoder PP gain block
//char *ptr;
//ptr = StringPrint(StatusString, "gain_decoder_pp[");
//ptr = StrPrintDecByte(ptr, vol_set);
//ptr = StringPrint(ptr, "dB]");
//PrintStatus(0, StatusString);
}

void AFESetGainSpkrVolumePP(int vol_set)
{
    SetPGain(p_gain_spkr_pp, vol_set);							// sets pre LSR PP gain block
}

void AFESetGainInboundVolumeFP(int vol_set)
{
    SetPGain(p_gain_inbound, (vol_set * 2));					// sets post MIC FP gain block
}

void AFESetGainSpkrVolumeFP(int vol_set)
{
    SetPGain(p_gain_spkr_fp, ((vol_set * 2) - 6));				// sets pre LSR FP gain block
}

extern void BroadcastSystemModeState(PPIDType user);
void AFESetGainPP2PPMixer(int vol_set)
{
	(base_station).InboundVol = vol_set;
	BroadcastSystemModeState(-1);

	switch (vol_set)
	{																		// MIXER ATTEN dB = (InboundVol x -2) - 2.5
	case 0: (base_station).CurrentInboundVolumeMixerAtten = 0x5FFB; break;	//  -2.5dB
	case 1: (base_station).CurrentInboundVolumeMixerAtten = 0x4C3E; break;	//  -4.5dB
	case 2: (base_station).CurrentInboundVolumeMixerAtten = 0x3C8F; break;	//  -6.5dB
	case 3: (base_station).CurrentInboundVolumeMixerAtten = 0x301B; break;	//  -8.5dB
	case 4: (base_station).CurrentInboundVolumeMixerAtten = 0x2636; break;	// -10.5dB
	case 5: (base_station).CurrentInboundVolumeMixerAtten = 0x1E5A; break;	// -12.5dB
	case 6: (base_station).CurrentInboundVolumeMixerAtten = 0x181C; break;	// -14.5dB
	case 7: (base_station).CurrentInboundVolumeMixerAtten = 0x1326; break;	// -16.5dB
	case 8: (base_station).CurrentInboundVolumeMixerAtten = 0x0F36; break;	// -18.5dB
	case 9: (base_station).CurrentInboundVolumeMixerAtten = 0x0C15; break;	// -20.5dB
	}

	int i = 0;
	for (i = 0; i < 5; i++)
	{
		p_dynmixer0->weights[i] = (base_station).CurrentInboundVolumeMixerAtten;
		p_dynmixer1->weights[i] = (base_station).CurrentInboundVolumeMixerAtten;
		p_dynmixer2->weights[i] = (base_station).CurrentInboundVolumeMixerAtten;
		p_dynmixer3->weights[i] = (base_station).CurrentInboundVolumeMixerAtten;
		p_dynmixer4->weights[i] = (base_station).CurrentInboundVolumeMixerAtten;
		p_dynmixer5->weights[i] = (base_station).CurrentInboundVolumeMixerAtten;
	}
}

int tonegenerator_running=0;
extern void EnableDSPForTonegeneratorPP(void);
extern int reinit_tonegenerator_pp(void);
void StartTonegeneratorPP(unsigned int argsin,unsigned int argcos, unsigned char filterenabled)
{
	char *ptr;
	if (!tonegenerator_running)
	{
		ptr = StringPrint(StatusString,"AFEConnectTonegeneratorPP[");
		ptr = StrPrintHexWord(ptr, argsin);
		ptr = StringPrint(ptr, ",");
		ptr = StrPrintHexWord(ptr, argcos);
		ptr = StringPrint(ptr, "]");
		PrintStatus(0,StatusString);
		reinit_tonegenerator_pp();
		p_tonegen->argsin1_1=argsin;
		p_tonegen->argcos1_1=argcos;
		p_tonegen->timerpreset2=0xFFFF; // no off tone
		GdspConnect(&(p_summator->in2_ptr), &(p_tonegen->tone_out));
		p_gendspgainconstant_pp->value=headset.WavAtten;				// p_summator->in3_ptr; attenuation of .WAV files
		GdspStart((unsigned short*)p_tonegen);
		EnableDSPForTonegeneratorPP();
	}
	p_tonegen->argsin1_1=argsin;
	p_tonegen->argcos1_1=argcos;
	p_tonegen->t1att_1=0x7FFF;
	tonegenerator_running=1;
}

extern void StateStopDSP(void);
void StopTonegeneratorPP(void)
{
	tonegenerator_running=0;
	PrintStatus(0,"AFEDisconnectTonegeneratorPP");
	p_gendspgainconstant_pp->value=0x0000;								// p_summator->in3_ptr
	GdspConnect(&(p_summator->in2_ptr), &(p_law2lin->linear_out));
	StateStopDSP();
}

void AFEDisconnectPlaybackPP(void)
{
	PrintStatus(0,"AFEDisconnectPlayback");
	GdspStop((unsigned short*)p_playbackbuffer);// no reason to have playback buffer activated
	GdspStop((unsigned short*)p_law2lin);
	p_gendspgainconstant_pp->value = 0x0000;							// p_summator->in3_ptr
}

void AFEConnectPlaybackPP(void)
{
	PrintStatus(0,"AFEConnectPlaybackPP");
	p_gendspgainconstant_pp->value = headset.WavAtten;					// p_summator->in3_ptr; attenuation of .WAV files
	GdspConnect(&(p_summator->in2_ptr), &(p_law2lin->linear_out));
	GdspStart((unsigned short*)p_playbackbuffer);
	GdspStart((unsigned short*)p_law2lin);
}

void AFEDisconnectAudioPathPP(void)
{
	//PrintStatus(0,"AFEDisconnectAudioPathPP");
	p_summator->in1_atten = 0x0000;										// multiply with 0 -> no signal to summator on in1_ptr
}

void AFEReenableVoice(void)
{
	PrintStatus(0,"AFEReenableVoice");
	p_summator->in1_atten = 0x7FFF;										// multiply with 1.00 for 0dB -> enable signal to summator on in1_ptr
}

void AFEConnectAudioPathPP(void)
{
	p_summator->in1_atten = 0x7FFF;										// multiply with 1.00 -> enable signal to summator on in1_ptr
}

void AFEDisableMicPathPP(void) 		// remove mic audio path
{
	PrintStatus(0,"AFEDisableMicPathPP");
	p_gendspgainconstant_encoder->value = 0x0000;						// NULL used to mute encoder input
	GdspConnect(&(p_g726encoder_pp->g_in1_ptr), &(p_gendspgainconstant_encoder->value));		// mute PP out to FP
}

void AFEEnableMicPathPP(void)		// Re-enable mic audio path
{
	PrintStatus(0,"AFEEnableMicPathPP");
	GdspConnect(&(p_g726encoder_pp->g_in1_ptr), &(p_gain_encoder_pp->out));	// enable PP out to FP
}

void AFEDisablePostMicPath(void) 	// remove post mic audio path
{
	p_gendspgainconstant_fp->value = 0x0000;							// NULL used to mute post mic input
	GdspConnect(&(p_gain_inbound->in_ptr), &(p_gendspgainconstant_fp->value));
}

void AFEEnablePostMicPath(void)		// Re-enable post mic audio path
{
	GdspConnect(&(p_gain_inbound->in_ptr), &(p_gendspcodecsource->codecdatainsrc));
}

void AFEEnableMicSpkrPath(void)		// to play messages to LO headsets in expanded system
{
	GdspConnect(&(p_gain_spkr_fp->in_ptr), &(p_gain_inbound->out));		// gain_inbound output which carries message audio
}

void AFEDisableMicSpkrPath(void)	// to stop playing messages to LO headsets in expanded system
{
	GdspConnect(&(p_gain_spkr_fp->in_ptr), &(p_dynmixer6->out));		// normal audio out to post gain block
}
