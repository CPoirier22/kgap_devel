#ifndef __SLTBUILD_H
#define __SLTBUILD_H
/*****************************************************************************
* Project   : DECT                                                           *
* Module    : New Slot builder                                               *
* Reference :                                                                *
* Type      : Headerfile for slot builder module.                            *
* Function  :                                                                *
* Systems   : Handset                                                        *
*----------------------------------------------------------------------------*
* $Header:   K:/PH/140960xx/00/Archive/H/sltbuild.h_v   1.0   Oct 24 2002 11:51:46   mne  $ *
*****************************************************************************/


extern void ActivateSyncBuilder(BYTE Channel, BYTE Cmd);
extern void SyncBuildHandler(void);
extern BOOLEAN ReleaseBearer(BYTE Channel);

#endif
