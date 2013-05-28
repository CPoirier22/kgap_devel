/*
 ********************************************************************
 *
 * Module: ccaction.h
 *
 * Config-item: ?
 *
 * Contents: This file contains prototypes for action functions for CC
 *
 * Author: DDU
 *
 * Copyright Kirk Telecom A/S. All rights reserved.
 ********************************************************************
 */

#ifndef CC_ACTION__
#define CC_ACTION__

#include "../cc.h"

CCStateType PCCReleaseComAction(SignalType * SignalPtr, CCProcessType * InstancePtr);

CCStateType PMnccReleaseReqAction(SignalType * SignalPtr, CCProcessType * InstancePtr);

CCStateType PMnccReleaseResAction(SignalType * SignalPtr, CCProcessType * InstancePtr);

CCStateType PLCELinkReleaseIndAction(SignalType * SignalPtr, CCProcessType * InstancePtr);

CCStateType PReleaseBothSidesAction(CCProcessType * InstancePtr, UByte ReleaseReasonCode);

#endif /* CC_ACTION__ */
