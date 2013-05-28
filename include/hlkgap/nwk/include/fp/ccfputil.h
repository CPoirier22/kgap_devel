/*
 ********************************************************************
 *
 * Module: ccutil.h
 *
 * Config-item: ?
 *
 * Contents: This file contains miscellaneous low level functions
 *     for the CC protocol entity. E.g functions for sending
 *     signals, checking parameters, handling of queues etc.
 *
 * Author: DDU
 *
 * Copyright Kirk Telecom A/S. All rights reserved.
 ********************************************************************
 */

#ifndef CC_UTIL__
#define CC_UTIL__

#include "../cc.h"
#include "../ccerror.h"
#include "../../../common/include/sformat.h"

UByte FCheckParameters(SFormatType * SignalPtr);

void FClearCCInstanceData(CCProcessType * InstancePtr);

Boolean FCreateNewCCInstance(XXEIType CCEI, CCProcessType ** TheInstance);

CCProcessType *FGetCCInstanceData(XXEIType CCEI);

void FPutSignalOnCCQueue(SignalType * SignalPtr, CCProcessType * InstancePtr);

void FRestoreCCSignalQueue(CCProcessType * InstancePtr);

Boolean FSendingMethodOK(SignalType * SignalPtr, UByte ActualSendingMethod, CCProcessType * InstancePtr);

void FSendCCReleaseComplete(XXEIType CCEI, UByte ReleaseReasonValue);

void FSendCCRelease(XXEIType CCEI, UByte ReleaseReasonValue);

UByte FSendLceResourceReserveReq(SFormatType * SetupSignal);

void FSendLceLinkReleaseReq(XXEIType XXEI);

void FSendMnccRejectInd(XXEIType CCEI, UByte ReleaseReasonValue);

void FSendMnccReleaseCfm(XXEIType CCEI, UByte ReleaseReasonValue);

void FSendMnccReleaseInd(XXEIType CCEI, UByte ReleaseReasonValue);

void FStartCCTimer(UByte TimerId, CCProcessType * InstancePtr, U16Bits TimeOutValue);

void FStopCCTimer(UByte TimerId, CCProcessType * InstancePtr);

#endif /* CC_UTIL__ */
