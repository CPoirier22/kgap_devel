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
* $History:: afe.h                                                            $ *
*                                                                               *
* Initial Revision                                                              *
*********************************************************************************
*/

#ifndef AFE_H_
#define AFE_H_

/**
 * This function is for the initialization of the AFE (Audio Front End)
 * @return void
 */
void AFEInit(void);

void AFEReenableVoice(void);
void AFESetVolume(int vol_set);
void AFESetGainInboundVolumePP(int vol_set);
void AFESetGainSpkrVolumePP(int vol_set);
void AFESetGainInboundVolumeFP(int vol_set);
void AFESetGainSpkrVolumeFP(int vol_set);
void AFESetGainPP2PPMixer(int vol_set);
void AFEDisconnectAudioPathPP(void);
void AFEConnectAudioPathPP(void);
void AFEDisconnectPlaybackPP(void);
void AFEConnectPlaybackPP(void);
unsigned char AFEGetCodecMicGain(void);
void AFESetCodecMicGain(unsigned char value);
void AFEDisableMicPathPP(void);
void AFEEnableMicPathPP(void);
void AFEDisablePostMicPath(void);
void AFEEnablePostMicPath(void);
void AFEEnableMicSpkrPath(void);
void AFEDisableMicSpkrPath(void);


#endif /*AFE_H_*/
