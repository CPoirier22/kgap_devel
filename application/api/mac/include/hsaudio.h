#ifndef __HSAUDIO_H
#define __HSAUDIO_H
/*****************************************************************************
* Project   : DECT                                                           *
* Module    : Handset audio control task.                                    *
* Reference :                                                                *
* Type      : Headerfile containing audio control commands                   *
* Function  :                                                                *
* Systems   : Handset                                                        *
*----------------------------------------------------------------------------*
* Copyright (c) 1994 by RTX Research Aps.                                    *
* $Header:   K:/PH/SRCLIB/PP5/BASIS/ARCHIVE/H/hsaudio.h_v   1.3   Jul 12 2005 11:26:48   jkf  $
* $Log:   K:/PH/SRCLIB/PP5/BASIS/ARCHIVE/H/hsaudio.h_v  $
 * 
 *    Rev 1.3   Jul 12 2005 11:26:48   jkf
 * CheckHeadset command added. Audio is closed under Alert if no headset is detected
 * 
 *    Rev 1.2   22 Oct 2003 17:13:16   mne
 * Warnings removed no function change.
 * 
 *    Rev 1.1   17 Sep 2003 08:13:40   mne
 * First release KEH put.
 * 
 *    Rev 1.0   Oct 24 2002 11:51:24   mne
 * Initial PP5 version for 428 
 * 
 *    Rev 1.4   17 Jun 1999 14:54:04   oo
 * SIDETONEON_cmd added.
*****************************************************************************/

#define OPENAUDIO_cmd       0x01
#define CLOSEAUDIO_cmd      0x02
#define TXMUTE_cmd          0x03
#define TXUNMUTE_cmd        0x04
#define RXMUTE_cmd          0x05
#define RXUNMUTE_cmd        0x06
#define STOPINBANDTONE_cmd  0x07
#define STARTINBANDTONE_cmd 0x08
#define TONE_TXMUTE_cmd     0x09
#define TONE_TXUNMUTE_cmd   0x0A
#define SIDETONEOFF_cmd     0x0B
#define TXTESTTONE_cmd      0x0C
#define SIDETONEON_cmd      0x0D
#define CHECKHEADSET_cmd	0x0E
#define TXSOFTMUTE_cmd		0x0F


#define RXVOLUMEN_cmd       0x20

extern BOOLEAN Speaker_On;
extern void InternalSpeaker(BOOLEAN sp_on);
extern void LS_ON(BOOLEAN on);

#endif
