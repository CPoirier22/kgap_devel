/*
 ********************************************************************
 *
 * Module: lapclow.h
 *
 * Config-item: ?
 *
 * Contents: This file contains the low level functions used by the
 *     different LAPC state functions.
 *
 * Author: DDU
 *
 * Copyright Kirk Telecom A/S. All rights reserved.
 ********************************************************************
 */

#ifndef LAPC_LOW__
#define LAPC_LOW__

#include "lapc.h"
#include "lapcerr.h"
#include "faframe.h"

#ifndef LAPC_LOW_THE_MODULE__

void CalculateCRC(FAFrameHeaderType * FAFrameHeader, int Length, FAFrameTailType * FAFrameTail, UByte * Lsig);
void PrepareFAFrame(ClassAType * TheClassInstance, UByte FAAddress, UByte FAControl, UByte * Lsig);
void QueueNWKMessage(ClassAType * TheClassInstance, DlDataReqType * DlDataReq,UByte module2module);
RRFrameType *BuildRRFrameOnQueue(UByte FAAddress, UByte FAControl, UByte * Lsig);
UByte GetFADataType(SignalType * TheSignal);
void SendDlEstablishInd(DLEIType DLEI, UByte SAPI_n_LLN, int DataLength, UByte * Data);
void SendDlEstablishCfm(DLEIType DLEI, UByte SAPI_n_LLN);
void SendDlReleaseInd(DLEIType DLEI, UByte SAPI_n_LLN, UByte ReleaseMode);
void SendDlReleaseCfm(DLEIType DLEI, UByte SAPI_n_LLN, UByte ReleaseMode);
void SendDlDataInd(SignalType * TheSignal, DLEIType DLEI, UByte SAPI_n_LLN);
void SendLcMacConReq(DLEIType DLEI);
void SendLcMacDisReq(DLEIType DLEI, UByte Reason);
void SendLcDataReq(DLEIType DLEI, void *Address, UByte DeleteTheSignal);
void LAPCDeleteInstance(void **TheClass);
void LAPCLogError(U16Bits ErrorCode, SignalType * TheSignal);

#endif /* LAPC_LOW_THE_MODULE__ */

#endif /* LAPC_LOW__ */
