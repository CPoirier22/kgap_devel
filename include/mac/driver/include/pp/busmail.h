#ifndef __BUSMAIL_H
#define __BUSMAIL_H
/****************************************************************************
* Project   : DECT                                                          *
* Module    : Defintion of interface to BUS-MAIL system.                    *
* Reference :                                                               *
* Type      : Headerfile definitions of function interface.                 *
* Function  :                                                               *
* Systems   : Base,Handset                                                  *
*---------------------------------------------------------------------------*
* Copyright (c) 1997 by Kirk telecom A/S.                                   *
* $Header:   K:/PH/140960xx/00/Archive/H/busmail.h_v   1.1   22 Oct 2003 17:13:14   mne  $ *
****************************************************************************/

#define BUSMAILBUFFSIZE 0x20

extern BYTE BusMailBuffer[BUSMAILBUFFSIZE];
extern BYTE BusMailRdp;
extern BYTE BusMailWrp;

extern void CheckForBusMail(void);

#endif
