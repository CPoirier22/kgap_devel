/*
 ********************************************************************
 *
 * Module:  pllme.h
 *
 *  Config-item:  ?
 *
 * Contents:  This file contains the portable part LLME structures and
 *          function prototypes.
 *
 *  Author: DDU
 *
 * Copyright Kirk Telecom A/S. All rights reserved.
 *
 * $Header:   K:/PH/140960xx/00/Archive/H/PLLME.H_v   1.0   Oct 24 2002 11:51:04   mne  $
 *
 * $Log:   K:/PH/140960xx/00/Archive/H/PLLME.H_v  $
 *
 *    Rev 1.0   Oct 24 2002 11:51:04   mne
 * Initial PP5 version for 428
 *
 *    Rev 1.5   23 Feb 1999 10:01:28   oo
 * File changed for PP2 HW. (Lucy).
 *
 *    Rev 1.4   Mar 29 1996 13:33:46   MK
 * Changed because pllme needs to now the MCEI.
 *
 *    Rev 1.3   26 Oct 1995 12:42:42   BJR
 * Redefined fields "ReturnAddress" in primitive structures to 2 byte of length as they always are in the PP.
 *
 *    Rev 1.2   11 Oct 1995 17:27:14   MK
 * LlmeUPlane structures changed.
 *
 *
 *
 *    Rev 1.1   26 Jan 1995 13:08:08   CB
 * Fileheader added
 *
 *    Rev 1.0   20 Jan 1995 12:55:08   CB
 * Initial version
 *
 ********************************************************************
 */
#ifndef LLME_HEADER__
#define LLME_HEADER__

#define LLME_U_PLANE_ind      0x02
#define LLME_U_PLANE_res      0x03

#define LLME_CONHAND_req      0x0C
#define LLME_CONHAND_cfm      0x0E

#define LLME_U_PLANE_RESERVE  0
#define LLME_U_PLANE_START    1
#define LLME_U_PLANE_STOP   2
#define LLME_U_PLANE_MODIFY   3

struct LlmeUPlaneIndStruct
{
    SignalType TheSignal;
    UByte ReturnProcess,
    ReturnAddress[4],
    Action;
};
typedef struct LlmeUPlaneIndStruct LlmeUPlaneIndType;

struct LlmeUPlaneResStruct
{
    SignalType TheSignal;
    UByte ReturnProcess,
    ReturnAddress[4],
    Action,
    AcceptFlag;
};
typedef struct LlmeUPlaneResStruct LlmeUPlaneResType;

struct LlmeConhandResStruct
{
    SignalType TheSignal;
};
typedef struct LlmeConhandResStruct LlmeConhandResType;

extern void InitializeLlme(void);
extern void PtLlmeSignalHandler(SignalType * TheSignal);

#endif /* LLME_HEADER__ */
