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
#ifndef DSP_TASK_PP_H
#define DSP_TASK_PP_H

#include "../../../../common/include/bitsdef.h"

extern const long DSP_PP_START_ADR;
extern const long DSP_PP_END_ADR;
extern const WORD DSP_PP_SIZE;
extern const WORD DSP_Loop_DSP_ADDR;   /* address to write to DSP_ADDR_REG to start DSP_Loop program*/
extern const WORD Codec_Loop_DSP_ADDR; /* address to write to DSP_ADDR_REG to start Code_Loop program*/
extern const WORD Filter_DSP_ADDR;
extern const WORD AudioplaybackVolume_Adr;
extern const WORD audioplayback_Adr;
extern const WORD Mic_Filter_coef_Adr;  /* RAM address of the filter coefficient to the Mic filter*/
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
extern const WORD AGCTreshold_Adr;
extern const WORD AGCdecay_Adr;
extern const WORD AGCattack_Adr;
extern const WORD AGCscaling_Adr;

extern const WORD Pow_Det_Out_Adr;      /* RAM address of the filter coefficient to the Ear filter*/

typedef struct
{
    WORD C0 ;
    WORD C1 ;
    WORD C2 ;
    WORD C3 ;
    WORD C4 ;
    WORD InputAtt;
    WORD FoutGain;
}
BiQuadFilterType;

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
}
FifhtOrderFilterType;


typedef struct
{
	UByte onoff;
    WORD Treshold ;
    WORD Decay ;
    WORD Attack ;
    WORD Scaling ;
    WORD Attenuation ;
}
AGCParameterType;

typedef struct
{
    WORD TimerPreset1 ;
    WORD TimerPreset2 ;
    WORD argsin1 ;
    WORD argcos1 ;
    WORD atten1  ;
    WORD argsin2 ;
    WORD argcos2 ;
    WORD atten2  ;
    WORD argsin3 ;
    WORD argcos3 ;
    WORD atten3  ;
    WORD dmy[6];
    WORD Timer1_out;
    WORD Timer2_out;
}
TripToneGenParamType;

typedef struct
{
    WORD argsin;
    WORD argcos;
    WORD Freq;
}
GenDspFreqType;


enum GetFilterSet
{
    MIC_COEFF,
    EARPIECE_COEFF,
    SPEAKER_COEFF,
    HEADSET_RX_COEFF,
    HFREE_PARAMETERS,
    READ_AGC_PARAMETERS
};

#define DspParamRam_Size 0x500  /* NB shie size must not exceed SIZEOF(DSPSEGMENT_PP)*/

extern __no_init BYTE DspParamRam_PP[DspParamRam_Size];   /* reserve memory for entire DSP program*/

#endif
