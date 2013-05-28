#ifndef __BSLLME_H
#define __BSLLME_H
/*****************************************************************************
* Project   : DECT                                                           *
* Module    : Basestation Lower Layer Management Entity                      *
* Reference :                                                                *
* Type      : Headerfile for Management module                               *
* Function  :                                                                *
* Systems   : Base                                                           *
*----------------------------------------------------------------------------*
* Copyright (c) 1994 by RTX Research Aps.                                    *
* $Header:   K:/PH/140211xx/source/bsllme.h_v   1.0.1.0   May 05 2003 12:16:22   on  $ *
*****************************************************************************/

#include "../../../common/include/gapcfg.h"

#define LINESPEECHBUFFER0      0x00
#define LINESPEECHBUFFER1      0x04
#define INTCOMSPEECHBUFFER     0x02
#define INTCOMSPEECHBUFFERREV  0x03
#define INTCOMSPEECHBUFFER0    0x00
#define INTCOMSPEECHBUFFERREV0 0x01
#define LINESPEECHBUFFER       LINESPEECHBUFFER0 /* bmcdrivf.c uses this define for muting control*/
#define SILENTSPEECHBUFFER     0x7e
#define SILENTSPEECHBUFFERREV  0x7f


extern const BYTE EmptyIpui[6];

extern BYTE AllocateMacConId(void);
extern void DeAllocateMacConId(BYTE Mcei);

#endif
