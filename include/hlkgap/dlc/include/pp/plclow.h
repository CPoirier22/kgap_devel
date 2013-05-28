/*
 ********************************************************************
 *
 * Module:  lclow.h
 *
 *  Config-item:  ?
 *
 * Contents:  This file contains the Lc low level function structures and
 *          prototype declarations.
 *
 *  Author: DDU
 *
 * Copyright Kirk Telecom A/S. All rights reserved.
 *
 * $Header:   K:/PH/140960xx/00/Archive/H/p_lclow.h_v   1.0   Oct 24 2002 11:51:36   mne  $
 *
 * $Log:   K:/PH/140960xx/00/Archive/H/p_lclow.h_v  $
 *
 *    Rev 1.0   Oct 24 2002 11:51:36   mne
 * Initial PP5 version for 428
 *
 *    Rev 1.5   23 Feb 1999 09:58:00   oo
 * File changed for PP2 HW. (Lucy).
 *
 *    Rev 1.1   Oct 16 1997 10:27:30   BJR
 * Added functions to start and stop timers <DL.05> and <DL.06>.
 *
 *    Rev 1.0   Mar 05 1997 14:11:20   MK
 * Initial revision based on lclow.h.
 * The Lc made as an static allocated instance.
 * Flow of code simplified.
 * Code reduction.
 *
 *    Rev 1.13   Feb 13 1997 09:59:52   MK
 * PORTABLE_PART: MCEIs now an array of 2.
 * Added ReleasePending flag to LcInstance.
 * FIXED_PART: Removed HOVValue from LcInstance.
 *
 *    Rev 1.12   Dec 20 1996 13:45:38   MK
 * MCEI and NewMCEI is now indexed with NewestConnectionNumber.
 *
 *    Rev 1.11   Sep 09 1996 17:20:02   MK
 * SendLcMacConCfm function added.
 *
 *    Rev 1.10   May 29 1996 12:17:02   MK
 * Syntax changes.
 *
 *    Rev 1.9   Mar 29 1996 13:36:16   MK
 * Prototype for SendLlmeConhandRes added.
 *
 *    Rev 1.8   Mar 22 1996 13:42:18   MK
 * FAFrameDataStruct changed to LcFAFrameDataStruct.
 *
 *    Rev 1.7   Mar 19 1996 08:59:32   MK
 * Decommented code for encryption.
 *
 *    Rev 1.6   05 Mar 1996 13:26:32   MK
 * SegmentsLeftToReceive added to ConnectionDataStruct.
 * SegmentQueue changed to pointer to UByte.
 * LastSegment replaced with SegmentPointer of type UByte.
 * Prototype of SendLcDataInd changed.
 * Prototype of CheckCRCInSegments replaced by CheckCRC.
 * Prototype of ReassembleSegments added.
 *
 *    Rev 1.5   27 Feb 1996 11:10:44   MK
 * LcOpenPending removed from LcStateSet when Fixed Part is defined.
 * FAFrameDataStruct added.
 * ConnectionDataStruct changed.
 * Prototyping changed.
 *
 *    Rev 1.4   02 Feb 1996 13:12:16   MK
 * Added ConnectionHandoverAttemptCounter in Instance Structure for PP
 *
 *    Rev 1.3   29 Jan 1996 13:15:28   MK
 * NewestConnectionUPlaneConfirmed removed from PT LcProcessStruct.
 * PtLcWaitUPlaneReserve state removed.
 * InvoluntaryHandover state commented out.
 * Functions to send encryption primitives added.
 * Encryption commented out.
 *
 *    Rev 1.2   11 Oct 1995 17:38:30   MK
 * LcProcessStruct changed.
 * InvoluntaryHandover State commented out.
 *
 *
 *    Rev 1.1   26 Jan 1995 13:07:54   CB
 * Fileheader added
 *
 *    Rev 1.0   20 Jan 1995 11:44:06   CB
 * Initial version
 *
 ********************************************************************
 */

#ifndef Lc_LOW_HEADER__
#define Lc_LOW_HEADER__

#include "../lc.h"
#include "../lapc.h"
#include "../../../maclnk/include/macprim.h"
#include "../../../maclnk/include/ccf.h"
#include "../faframe.h"
#include "../../../common/include/dispatch.h"

enum LcStateSet
{
    LcOpenPending = 0,
    LcActive,
    LcHandoverPending,
    LcReleasePending,
    LcIdle
};

struct LcFAFrameQueueStruct
{
    UByte *DataPointer;
    struct LcFAFrameQueueStruct *NextFAFrame;
    UByte BytesLeftToSend, DeleteSignalFlag, module2module;
};
typedef struct LcFAFrameQueueStruct LcFAFrameQueueType;

struct LcProcessStructPP
{
    DLEIType LcInstanceId;        /* BCF + LCN + USN */
    MCEIType MCEI;
    UByte *SegmentQueue[2], *SegmentPointer[2], SegmentCount[2];
    LcFAFrameQueueType *FAFrameQueue, *FALastFrame;
    UByte ConnectionHandoverAttemptCounter, ConnectionHandoverFlag, ConnectionHandoverDisabledFlag, FrameBoundaryFlag;
    enum LcStateSet LcState;
    TimerType *DL_05_Timer, *DL_06_Timer;
    UByte EncryptionEnabledFlag;
    UByte EncryptionKey[8];
    UByte Lsig[2];
};
typedef struct LcProcessStructPP LcProcessTypePP;

/* global variables */
extern LcProcessTypePP TheLcInstance;

int PCheckCRC(UByte * TPDU, UByte FAFrameLength);
SignalType *PBuildSegmentSignal(UByte ConnectionNumber);
void PReassembleSegments(UByte ConnectionNumber, SignalType * TheSignal);
void PReleaseLcInstance(void);
void PSendLcDataInd(UByte * DataPointer);
void PSendLcMacDisInd(DLEIType DLEI);
void PAddToFAFrameQueue(LcDataReqType * LcDataReq);
void PStartDL05Timer(void);
void FStopDL05Timer(void);

void SendLcMacConCfm(DLEIType DLEI);
void SendLlmeUPlaneInd(UByte Action);
void SendLlmeConhandCfm(void);
void StartDL06Timer(void);
void StopDL06Timer(void);

#endif /* Lc_LOW_HEADER__ */
