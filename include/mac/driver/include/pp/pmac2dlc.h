
#ifndef __PMAC2DLC_H
#define __PMAC2DLC_H


/**************************************************************************
* Project   : DECT                                                        *
* Module    : Handset CCF to DLC interface functions                      *
* Reference :                                                             *
* Type      : Function                                                        *
* Function  :                                                             *
* Systems   : Handset                                                     *
*-------------------------------------------------------------------------*
* Copyright (c) 1994 by RTX Research Aps.                                 *
* $Header:   K:/PH/140960xx/00/Archive/H/pmac2dlc.h_v   1.0   Oct 24 2002 11:51:44   mne  $ *
* $Log:   K:/PH/140960xx/00/Archive/H/pmac2dlc.h_v  $
 *
 *    Rev 1.0   Oct 24 2002 11:51:44   mne
 * Initial PP5 version for 428
 *
 *    Rev 1.3   23 Feb 1999 10:01:06   oo
 * File changed for PP2 HW. (Lucy).
 *
 *    Rev 1.2   Jun 13 1996 09:35:54   OO
 * New revision from RTX.
**************************************************************************/

extern void SendMacDisInd(BYTE Mcei, BYTE Reason);
extern void SendMacConCfm(BYTE Mcei,BYTE Pmid[3]);
extern void SendMacCoDtrInd(BYTE Mcei);
extern void SendMacCoDataInd(MailType *MailPtr);
extern void SendMacPageInd(MailType *MailPtr);
extern void SendMacMeConHandInd(BYTE Mcei);
extern void SendMacEncEksCfm(BYTE Mcei);
extern void SendMacMeFtSystemInd(MailType *MailPtr);
extern void SendMacMeFtSystemCfm(MailType *MailPtr);

#endif


