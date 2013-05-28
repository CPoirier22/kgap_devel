/*
 ********************************************************************
 *
 * Module:  p_ccutil.h
 *
 *  Config-item:  ?
 *
 * Contents:  This file contains prototypes for action functions and low
 *           level utility functions for portable part CC
 *
 *  Author: DDU
 *
 * Copyright Kirk Telecom A/S. All rights reserved.
 *
 * $Header:   K:/PH/140960xx/00/Archive/H/P_CCUTIL.H_v   1.0   Oct 24 2002 11:51:06   mne  $
 *
 * $Log:   K:/PH/140960xx/00/Archive/H/P_CCUTIL.H_v  $
 *
 *    Rev 1.0   Oct 24 2002 11:51:06   mne
 * Initial PP5 version for 428
 *
 *    Rev 1.3   23 Feb 1999 10:01:56   oo
 * File changed for PP2 HW. (Lucy).
 *
 *    Rev 1.2   Mar 29 1996 14:11:50   BJR
 * Added CCSendLlmeUPlaneInd.
 *
 *    Rev 1.1   26 Jan 1995 13:08:04   CB
 * Fileheader added
 *
 *    Rev 1.0   20 Jan 1995 12:55:04   CB
 * Initial version
 *
 ********************************************************************
 */

#ifndef P_CC_UTIL__
#define P_CC_UTIL__

#include "../cc.h"

void CCSendLlmeUPlaneInd(UByte BCF, UByte LCN, UByte * CCEI, UByte Action);
CCStateType BackwardCCSignalAction(UByte BackwardAction, SignalType * SignalPtr, CCProcessType * InstancePtr);
CCStateType CCConnectAckAction(SignalType * SignalPtr, CCProcessType * InstancePtr);
CCStateType CCConnectAction(SignalType * SignalPtr, CCProcessType * InstancePtr);
#endif /* P_CC_UTIL__ */
