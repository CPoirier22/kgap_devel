/*
 ********************************************************************
 *
 * Module: ccmsg.h
 *
 * Config-item: ?
 *
 * Contents: This file contains definitions of CC messages
 *
 * Author: DDU
 *
 * Copyright Kirk Telecom A/S. All rights reserved.
 ********************************************************************
 */

#ifndef CC_MSG__
#define CC_MSG__

#include "../../dduos/include/dduos.h"
#include "../../common/include/sformat.h"

/* Definition of CC messages */
#define ReservedCCMessage  0x00
#define CC_ALERTING    0x01
#define CC_CALL_PROC   0x02
#define CC_SETUP    0x05
#define CC_CONNECT              0x07
#define CC_SETUP_ACK            0x0D
#define CC_CONNECT_ACK          0x0F
#define CC_SERVICE_CHANGE       0x20
#define CC_SERVICE_ACCEPT       0x21
#define CC_SERVICE_REJECT       0x23
#define CC_RELEASE              0x4D
#define CC_RELEASE_COM          0x5A
#define IWU_INFO                0x60
#define CC_NOTIFY               0x6E
#define CC_INFO     0x7B

struct CCSetupStruct
{
    SignalType TheSignal;
    MessageLengthType MessageLength;
    UByte TiPd;
    UByte MessageType;
};
typedef struct CCSetupStruct CCSetupType;

struct CCSetupAckStruct
{
    SignalType TheSignal;
    MessageLengthType MessageLength;
    UByte TiPd;
    UByte MessageType;
};
typedef struct CCSetupAckStruct CCSetupAckType;

struct CCCallProcStruct
{
    SignalType TheSignal;
    MessageLengthType MessageLength;
    UByte TiPd;
    UByte MessageType;
};
typedef struct CCCallProcStruct CCCallProcType;

struct CCAlertingStruct
{
    SignalType TheSignal;
    MessageLengthType MessageLength;
    UByte TiPd;
    UByte MessageType;
};
typedef struct CCAlertingStruct CCAlertingType;

struct CCConnectStruct
{
    SignalType TheSignal;
    MessageLengthType MessageLength;
    UByte TiPd;
    UByte MessageType;
};
typedef struct CCConnectStruct CCConnectType;

struct CCConnectAckStruct
{
    SignalType TheSignal;
    MessageLengthType MessageLength;
    UByte TiPd;
    UByte MessageType;
    UByte lid;
};
typedef struct CCConnectAckStruct CCConnectAckType;

struct CCNotifyStruct
{
    SignalType TheSignal;
    MessageLengthType MessageLength;
    UByte TiPd;
    UByte MessageType;
    TimerRestartType TimerRestart;
};
typedef struct CCNotifyStruct CCNotifyType;

struct CCReleaseStruct
{
    SignalType TheSignal;
    MessageLengthType MessageLength;
    UByte TiPd;
    UByte MessageType;
};
typedef struct CCReleaseStruct CCReleaseType;

struct CCReleaseCompleteStruct
{
    SignalType TheSignal;
    MessageLengthType MessageLength;
    UByte TiPd;
    UByte MessageType;
};
typedef struct CCReleaseCompleteStruct CCReleaseCompleteType;

#endif /* CC_MSG__ */
