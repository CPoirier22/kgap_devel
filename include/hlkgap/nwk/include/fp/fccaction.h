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

CCStateType FCCReleaseComAction(SignalType * SignalPtr, CCProcessType * InstancePtr);

CCStateType FMnccReleaseReqAction(SignalType * SignalPtr, CCProcessType * InstancePtr);

CCStateType FMnccReleaseResAction(SignalType * SignalPtr, CCProcessType * InstancePtr);

CCStateType FLCELinkReleaseIndAction(SignalType * SignalPtr, CCProcessType * InstancePtr);

CCStateType FReleaseBothSidesAction(CCProcessType * InstancePtr, UByte ReleaseReasonCode);

CCStateType AbnormalReleaseBothSidesAction(SignalType * SignalPtr, CCProcessType * InstancePtr);

#endif /* CC_ACTION__ */
