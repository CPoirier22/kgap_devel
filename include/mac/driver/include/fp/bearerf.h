/**************************************************************************
* Project   : DECT                                                        *
* Module    : Lower MAC                                                   *
* Reference :                                                             *
* Type      :                                                             *
* Function  :                                                             *
* Systems   : Base                                                        *
*-------------------------------------------------------------------------*
* Copyright (c) 1996 by RTX Research A/S.                                 *
* $Header:   K:/PH/140999xx/Xx/Variant/Archive/H/bearerf.h_v   1.1   Nov 17 2003 11:16:44   on  $ *
**************************************************************************/
#ifndef __BEARERF_H
#define __BEARERF_H

#include "../../../common/include/gapcfg.h"

extern BYTE PrimRecvScanCarrierFP;
extern BYTE FrameNumberFP;
extern BYTE MultiFrameNumberFP[3];
extern BYTE BroadCastBearer;
extern BYTE PagingSegmentFull;
extern BYTE PagingRepCount;
extern BYTE PagingSegmentBufferFP[37];
extern BYTE CsSegmentArray[NUMBEROFCONNECTIONS][6];
extern BYTE LoopBackModeFP;
extern BYTE HLCapabilities[2];
extern BYTE MacRfpi[5];
extern BYTE Fmid[2];

extern BYTE RssiScanReq;
extern BYTE RssiScanChannel;
extern BYTE NumberOfOneBits;
extern WORD SlotDataFPSize;
extern BYTE ConnectionTimeOut;
extern BYTE DiversityMode;
extern void UpdatePrimRecvScanCarrierFP(void);

extern BYTE RfpStatusFP;
extern void BearerControllerFP(void);
extern void EndOfFrameHandlerFP(void);

#define LOOPBACK_PATT 0x80

#define SHORT_PAGE_REQ     0x80
#define FULL_PAGE_REQ      0x40
#define BUF_FULL_PAGE_REQ  0x20
#define PAGE_CNT_MASK      0x0F
#define EXTENDED_FP_INFO  0x08
#define PAGE_REPETITION           0x10
#define LOW_DUTY_CYCLE_REPEAT_CNT 0x03

#define NO_BEARER_HANDOVER             0x00
#define INTRACELL_BEARER_HANDOVER      0x01
#define ALL_INTERNAL_BEARER_HANDOVER   0x02
#define SOME_INTERNAL_BEARER_HANDOVER  0x03

#endif
