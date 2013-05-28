#ifndef __TESTMODE_H
#define __TESTMODE_H
/*****************************************************************************
* Project   : DECT                                                           *
* Module    : Test mode functions                                            *
* Reference :                                                                *
* Type      : Headerfile for testmode functions                              *
* Function  :                                                                *
* Systems   : Base,Handset                                                   *
*----------------------------------------------------------------------------*
* Copyright (c) 1994 by RTX Research Aps.                                    *
* $Header:   K:/PH/140960xx/00/Archive/H/testmode.h_v   1.0   Oct 24 2002 11:51:48   mne  $ *
*****************************************************************************/

#include "../../../../common/include/_stddef.h"

extern BYTE BusActive;
extern void WarmStart(void);

void setTestMode(BYTE value);
BYTE inTestMode(void);

#endif
