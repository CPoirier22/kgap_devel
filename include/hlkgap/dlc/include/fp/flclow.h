/*
 ********************************************************************
 *
 * Module: f_lclow.h
 *
 * Config-item: ?
 *
 * Contents: This file contains the Lc low level function structures and
 *     prototype declarations.
 *
 * Author: MK
 *
 * Copyright Kirk Telecom A/S. All rights reserved.
 ********************************************************************
 */

#ifndef Lc_LOW_HEADER__
#define Lc_LOW_HEADER__

#include "../lc.h"
#include "../lapc.h"
#include "../../../hlme/include/hlmepri.h"
#include "../faframe.h"
#include "../../../maclnk/include/ccf.h"

enum LcStateSet
{
    LcActive = 0,
    LcHandoverPending,
    LcReleasePending
};

struct LcFAFrameQueueStruct
{
    UByte *DataPointer;
    struct LcFAFrameQueueStruct *NextFAFrame;
    UByte BytesLeftToSend, DeleteSignalFlag, module2module;
};
typedef struct LcFAFrameQueueStruct LcFAFrameQueueType;

struct LcProcessStructFP
{
    DLEIType LcInstanceId;        /* BCF + LCN + PMID */
    MCEIType MCEI[2];
    UByte NewestConnectionNumber;
    UByte SegmentCount[2];
    UByte *SegmentQueue[2], *SegmentPointer[2];
    LcFAFrameQueueType *FAFrameQueue, *FALastFrame;
    enum LcStateSet LcState;
    TimerType *DL05Timer;
    UByte EncryptionEnabledFlag;
    UByte EncryptionKey[8];
    UByte Lsig[2];
    UByte NewMeState;
};
typedef struct LcProcessStructFP LcProcessTypeFP;

#define DisableInvoHO   0x01

int FCheckCRC(UByte * TPDU, UByte FAFrameLength, UByte * Lsig);
SignalType *FBuildSegmentSignal(LcProcessTypeFP * TheLcInstance, UByte ConnectionNumber);
void FReassembleSegments(LcProcessTypeFP * TheProcessInstance, UByte ConnectionNumber, SignalType * TheSignal);
void FReleaseLcInstance(LcProcessTypeFP * TheLcInstance);
void FSendLcDataInd(UByte * FAFrame, LcProcessTypeFP * TheProcessInstance);
void FSendLcMacDisInd(DLEIType DLEI);
void FAddToFAFrameQueue(LcProcessTypeFP * TheLcInstance, LcDataReqType * LcDataReq);
void FStartDL05Timer(LcProcessTypeFP * TheLcInstance);
void FStopDL05Timer(LcProcessTypeFP * TheLcInstance);


void SendMacCoDataReqSignal(MCEIType MCEI, SignalType * SegmentSignal);
void SendMacDisReqSignal(MCEIType MCEI);
void SendHlMeUPlaneInd(LcProcessTypeFP * TheLcProcess, UByte Action);
void SendHlMeDataInd(LcProcessTypeFP * TheLcProcess, UByte DataType);
void SendMacEncKeyReqSignal(SignalType * TheSignal, MCEIType MCEI);
void InitialiseLcInstance(MacConIndType * MacConInd);
UByte FValidFAFrameHeader(SignalType * TheSignal);
SignalType *BuildFAFrameSignalFromSegments(LcProcessTypeFP * TheLcInstance);
#endif /* Lc_LOW_HEADER__ */
