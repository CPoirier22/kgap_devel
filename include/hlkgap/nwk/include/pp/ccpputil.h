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

UByte PCheckParameters(SFormatType * SignalPtr);

void PClearCCInstanceData(CCProcessType * InstancePtr);

Boolean PCreateNewCCInstance(XXEIType CCEI, CCProcessType ** TheInstance);

CCProcessType *PGetCCInstanceData(XXEIType CCEI);

void PPutSignalOnCCQueue(SignalType * SignalPtr, CCProcessType * InstancePtr);

void PRestoreCCSignalQueue(CCProcessType * InstancePtr);

Boolean PSendingMethodOK(SignalType * SignalPtr, UByte ActualSendingMethod, CCProcessType * InstancePtr);

void PSendCCReleaseComplete(XXEIType CCEI, UByte ReleaseReasonValue);

void PSendCCRelease(XXEIType CCEI, UByte ReleaseReasonValue);

UByte PSendLceResourceReserveReq(SFormatType * SetupSignal);

void PSendLceLinkReleaseReq(XXEIType XXEI);

void PSendMnccRejectInd(XXEIType CCEI, UByte ReleaseReasonValue);

void PSendMnccReleaseCfm(XXEIType CCEI, UByte ReleaseReasonValue);

void PSendMnccReleaseInd(XXEIType CCEI, UByte ReleaseReasonValue);

void PStartCCTimer(UByte TimerId, CCProcessType * InstancePtr, U16Bits TimeOutValue);

void PStopCCTimer(UByte TimerId, CCProcessType * InstancePtr);

#endif /* CC_UTIL__ */
