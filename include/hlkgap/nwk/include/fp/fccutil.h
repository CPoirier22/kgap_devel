/*
 ********************************************************************
 *
 * Module: f_ccutil.h
 *
 * Config-item: ?
 *
 * Contents: This file contains prototypes for action functions and
 *     low level utility functions for fixed part CC
 *
 * Author: DDU
 *
 * Copyright Kirk Telecom A/S. All rights reserved.
 ********************************************************************
 */

#ifndef F_CC_UTIL__
#define F_CC_UTIL__

#include "../cc.h"

#ifndef F_CC_UTIL_THE_MODULE__

void CcSendHlMeUPlaneIndRelease(UByte * CCEI);

CCStateType BackwardMnccPrimitiveAction(SubEventType BackwardAction, SignalType * SignalPtr, CCProcessType * InstancePtr);

CCStateType MnccConnectAckReqAction(SignalType * SignalPtr, CCProcessType * InstancePtr);

CCStateType MnccConnectReqAction(SignalType * SignalPtr, CCProcessType * InstancePtr);

CCStateType MnccNotifyReqAction(SignalType * SignalPtr, CCProcessType * InstancePtr);

#endif /* F_CC_UTIL_THE_MODULE__ */

#endif /* F_CC_UTIL__ */
