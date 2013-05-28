/*==============================================================================
;*
;*  DESCRIPTION: Interface GenDSP Task
;*
;*  REFERENCES :
;*
;*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
;*  The information in this document is confidential and sole property of
;*  KIRK telecom A/S. (c) Copyright 2003 by KIRK telecom A/S.
;*============================================================================*/

/*
extern const long DSP_START_ADR;
extern const long DSP_END_ADR;
extern const WORD DSP_SIZE;
extern const WORD SampleAdr;
extern const WORD Sample_Play_DSP_ADDR;
extern const WORD DSP_Loop_DSP_ADDR;   // address to write to DSP_ADDR_REG to start DSP_Loop program
extern const WORD Codec_Loop_DSP_ADDR; // address to write to DSP_ADDR_REG to start Code_Loop program
extern const WORD Filter_DSP_ADDR; 
extern const WORD Sine_Play_DSP_ADDR; 
extern const WORD HFree_DSP_ADDR; 
extern const WORD RingTone_DSP_ADDR; 
extern const WORD OddBuf_DSP_ADDR;
extern const WORD EvenBuf_DSP_ADDR;
extern const WORD SineTable_Adr;
extern const WORD SineLength_Adr;
extern const WORD ToneGenPar_Adr;
extern const WORD Mic_Filter_coef_Adr;  // RAM address of the filter coefficient to the Mic filter
extern const WORD HF_Speaker_Filt_Adr;  // RAM address of the filter coefficient to loudspeaker when in Handsfree
extern const WORD HFree_Par_8_Adr;          // RAM address of parameter 8 in the HFREE code
extern const WORD Ringer_Attenuation;       // 0 to INF dB attenuation
extern const WORD Ear_Filt_C0_1_Adr;
extern const WORD Ear_Filt_C1_1_Adr;
extern const WORD Ear_Filt_C2_1_Adr;
extern const WORD Ear_Filt_C0_2_Adr;
extern const WORD Ear_Filt_C1_2_Adr;
extern const WORD Ear_Filt_C2_2_Adr;
extern const WORD Ear_Filt_C3_3_Adr;
extern const WORD Ear_Filt_C4_3_Adr;
extern const WORD Ear_Filt_InputAtt_Adr;
extern const WORD Ear_FoutGain1_Adr;
extern const WORD Ear_FoutGain2_Adr;
extern const WORD Ear_FoutGain3_Adr;
extern const WORD Pow_Det_Out_Adr;      // RAM address of the filter coefficient to the Ear filter
extern const WORD Loud_Filt_C0_1_Adr;
extern const WORD Loud_Filt_C1_1_Adr;
extern const WORD Loud_Filt_C2_1_Adr;
extern const WORD Loud_Filt_C0_2_Adr;
extern const WORD Loud_Filt_C1_2_Adr;
extern const WORD Loud_Filt_C2_2_Adr;
extern const WORD Loud_Filt_C3_3_Adr;
extern const WORD Loud_Filt_C4_3_Adr;
extern const WORD Loud_Filt_InputAtt_Adr;
extern const WORD Loud_FoutGain1_Adr;
extern const WORD Loud_FoutGain2_Adr;
extern const WORD Loud_FoutGain3_Adr;
*/

/*
typedef struct
{
  WORD C0 ;
  WORD C1 ;
  WORD C2 ;
  WORD C3 ;
  WORD C4 ;
  WORD InputAtt;
  WORD FoutGain;
} BiQuadFilterType;
*/

/*
typedef struct
{
  WORD C0_1 ;
  WORD C1_1 ;
  WORD C2_1 ;
  WORD C0_2 ;
  WORD C1_2 ;
  WORD C2_2 ;
  WORD C3_3 ;
  WORD C4_3 ;
  WORD InputAtt;
  WORD FoutGain;
} FifhtOrderFilterType;
*/


typedef struct
{
  WORD argsin;
  WORD argcos;
  WORD Freq;
} GenDspFreqType;



enum GetFilterSet
{
  MIC_COEFF,
  EARPIECE_COEFF,
  HEADSET_RX_COEFF,
  HFREE_PARAMETERS
};

typedef enum
{
  DSP_ADPCM_LOOP,
  DSP_HFREE_LOOP,
  DSP_LOOPBACK_LOOP,
  DSP_SINE_LOOP,
  DSP_RINGTONE_LOOP
} DSPProgram_t;

/* included only to DSP_Task.c*/
#ifdef _DSP_TASK_H
const int16 sine[8]={0, 1448, 2048, 1448, 0, -1448, -2048, -1448};

#else
#include "Ringtones.h"

extern const GenDspFreqType FreqTabel[];
extern void PlayPolyphonicTone(Ring_Tone_req nr, Ring_Vol_req vol);
extern void PlaySineWave(BYTE Freq);
extern void SetPolyphonicVolume(Ring_Vol_req vol);
void Start_DSP_program(DSPProgram_t dsp_program);
extern void Stop_DSP();

#endif
