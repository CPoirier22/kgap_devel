#ifndef __CSFMAIL_H
#define __CSFMAIL_H
/****************************************************************************
* Project   : DECT                                                          *
* Module    : Defintion of interface to CSF-MAIL system.                    *
* Reference :                                                               *
* Type      : Headerfile definitions of function interface.                 *
* Function  :                                                               *
* Systems   : Base,Handset                                                  *
*---------------------------------------------------------------------------*
* Copyright (c) 1994 by RTX Research Aps.                                   *
* $Header:   K:/ph/srclib/os/basis/archive/h/INTMAIL.H_V   1.4.1.0   May 06 2003 11:00:42   on  $ *
****************************************************************************/

#include "../../common/include/rtxdef.h"
#include "tasks.h"

#ifndef _2_4_GHZ_
extern void PutInterruptMail(uint8 Element);
extern void DeliverInterruptMail(uint8 TaskId);
#endif

#ifdef _2_4_GHZ_
extern void DeliverInterruptMailArr(uint8 *Data);
#endif
extern BYTE PagingSegmentBufferRx[37];
extern const char *printMailPrimitive(PrimitiveType primitive);

#define INTMAILBUFFSIZE 0x100

#endif
