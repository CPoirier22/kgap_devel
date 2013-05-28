/*
 ********************************************************************
 *
 * Module: ccprim.h
 *
 * Config-item: ?
 *
 * Contents: This file contains the definitions of primitives
 *     related to CC signalhandler (both fixed and portable
 *     part)
 *
 * Author: DDU
 *
 * Copyright Kirk Telecom A/S. All rights reserved.
 ********************************************************************
 */

#ifndef CC_PRIMITIVES__
#define CC_PRIMITIVES__

#include "../../dduos/include/dduos.h"
#include "../../../common/include/identify.h"
#include "../../common/include/sformat.h"

#define MNCC_SETUP_req   0x00
#define MNCC_SETUP_ind   0x01

#define MNCC_SETUP_ACK_req  0x02
#define MNCC_SETUP_ACK_ind      0x03

#define MNCC_INFO_req   0x04
#define MNCC_INFO_ind        0x05

#define MNCC_CALL_PROC_req      0x06
#define MNCC_CALL_PROC_ind      0x07
#define MNCC_ALERT_req   0x08
#define MNCC_ALERT_ind          0x09

#define MNCC_CONNECT_req        0x0A
#define MNCC_CONNECT_cfm        0x0B
#define MNCC_CONNECT_ind  0x0C

#define MNCC_CONNECT_ACK_req    0x0D

#define MNCC_IWU_INFO_req     0x0E
#define MNCC_IWU_INFO_ind     0x0F

#define MNCC_NOTIFY_req   0x10    /* Only used in fixed part */

#define MNCC_REJECT_req         0x11
#define MNCC_REJECT_ind         0x12

#define MNCC_RELEASE_req        0x13
#define MNCC_RELEASE_cfm        0x14
#define MNCC_RELEASE_ind        0x15
#define MNCC_RELEASE_res        0x16

/* typedefinitions of S-format primitives related to CC */
struct MnccSetupReqStruct
{
    SignalType TheSignal;
    MessageLengthType MessageLength;
    UByte TiPd;
    UByte MessageType;
};
typedef struct MnccSetupReqStruct MnccSetupReqType;

#define getMnccSetupReqTypeIE(signal) ((unsigned char*)signal + offsetof(MnccSetupReqType, MessageType) + sizeof(UByte))

struct MnccSetupIndStruct
{
    SignalType TheSignal;
    MessageLengthType MessageLength;
    UByte TiPd;
    UByte MessageType;
};
typedef struct MnccSetupIndStruct MnccSetupIndType;

struct MnccSetupAckReqStruct
{
    SignalType TheSignal;
    MessageLengthType MessageLength;
    UByte TiPd;
    UByte MessageType;
};
typedef struct MnccSetupAckReqStruct MnccSetupAckReqType;

struct MnccSetupAckIndStruct
{
    SignalType TheSignal;
    MessageLengthType MessageLength;
    UByte TiPd;
    UByte MessageType;
};
typedef struct MnccSetupAckIndStruct MnccSetupAckIndType;

#define getMnccSetupAckIndTypeIE(signal) ((unsigned char*)signal + offsetof(MnccSetupAckIndType, MessageType) + sizeof(UByte))

struct MnccInfoReqStruct
{
    SignalType TheSignal;
    MessageLengthType MessageLength;
    UByte TiPd;
    UByte MessageType;
};
typedef struct MnccInfoReqStruct MnccInfoReqType;

#define getMnccInfoReqTypeIE(signal) ((unsigned char*)signal + offsetof(MnccInfoReqType, MessageType) + sizeof(UByte))

struct MnccInfoIndStruct
{
    SignalType TheSignal;
    MessageLengthType MessageLength;
    UByte TiPd;
    UByte MessageType;
};
typedef struct MnccInfoIndStruct MnccInfoIndType;

#define getMnccInfoIndTypeIE(signal) ((unsigned char*)signal + offsetof(MnccInfoIndType, MessageType) + sizeof(UByte))

struct MnccCallProcReqStruct
{
    SignalType TheSignal;
    MessageLengthType MessageLength;
    UByte TiPd;
    UByte MessageType;
};
typedef struct MnccCallProcReqStruct MnccCallProcReqType;

struct MnccCallProcIndStruct
{
    SignalType TheSignal;
    MessageLengthType MessageLength;
    UByte TiPd;
    UByte MessageType;
};
typedef struct MnccCallProcIndStruct MnccCallProcIndType;

#define getMnccCallProcIndTypeIE(signal) ((unsigned char*)signal + offsetof(MnccCallProcIndType, MessageType) + sizeof(UByte))

struct MnccAlertReqStruct
{
    SignalType TheSignal;
    MessageLengthType MessageLength;
    UByte TiPd;
    UByte MessageType;
};
typedef struct MnccAlertReqStruct MnccAlertReqType;

#define getMnccAlertReqTypeIE(signal) ((unsigned char*)signal + offsetof(MnccAlertReqType, MessageType) + sizeof(UByte))

struct MnccAlertIndStruct
{
    SignalType TheSignal;
    MessageLengthType MessageLength;
    UByte TiPd;
    UByte MessageType;
};
typedef struct MnccAlertIndStruct MnccAlertIndType;

#define getMnccAlertIndTypeIE(signal) ((unsigned char*)signal + offsetof(MnccAlertIndType, MessageType) + sizeof(UByte))

struct MnccConnectReqStruct
{
    SignalType TheSignal;
    MessageLengthType MessageLength;
    UByte TiPd;
    UByte MessageType;
};
typedef struct MnccConnectReqStruct MnccConnectReqType;

#define getMnccConnectReqTypeIE(signal) ((unsigned char*)signal + offsetof(MnccConnectReqType, MessageType) + sizeof(UByte))

struct MnccConnectCfmStruct
{
    SignalType TheSignal;
    MessageLengthType MessageLength;
    UByte TiPd;
    UByte MessageType;
};
typedef struct MnccConnectCfmStruct MnccConnectCfmType;

#define getMnccConnectCfmTypeIE(signal) ((unsigned char*)signal + offsetof(MnccConnectCfmType, MessageType) + sizeof(UByte))

struct MnccConnectIndStruct
{
    SignalType TheSignal;
    MessageLengthType MessageLength;
    UByte TiPd;
    UByte MessageType;
};
typedef struct MnccConnectIndStruct MnccConnectIndType;

#define getMnccConnectIndTypeIE(signal) ((unsigned char*)signal + offsetof(MnccConnectIndType, MessageType) + sizeof(UByte))

struct MnccConnectAckReqStruct
{
    SignalType TheSignal;
    MessageLengthType MessageLength;
    UByte TiPd;
    UByte MessageType;
    UByte lid;
};
typedef struct MnccConnectAckReqStruct MnccConnectAckReqType;

#define getMnccConnectAckReqTypeIE(signal) ((unsigned char*)signal + offsetof(MnccConnectAckReqType, lid) + sizeof(UByte))

struct MnccIwuInfoReqStruct
{
    SignalType TheSignal;
    MessageLengthType MessageLength;
    UByte TiPd;
    UByte MessageType;
};
typedef struct MnccIwuInfoReqStruct MnccIwuInfoReqType;

struct MnccIwuInfoIndStruct
{
    SignalType TheSignal;
    MessageLengthType MessageLength;
    UByte TiPd;
    UByte MessageType;
};
typedef struct MnccIwuInfoIndStruct MnccIwuInfoIndType;

struct MnccNotifyReqStruct
{
    SignalType TheSignal;
    MessageLengthType MessageLength;
    UByte TiPd;
    UByte MessageType;
    TimerRestartType TimerRestart;
};
typedef struct MnccNotifyReqStruct MnccNotifyReqType;

struct MnccRejectReqStruct
{
    SignalType TheSignal;
    MessageLengthType MessageLength;
    UByte TiPd;
    UByte MessageType;
};
typedef struct MnccRejectReqStruct MnccRejectReqType;

struct MnccRejectIndStruct
{
    SignalType TheSignal;
    MessageLengthType MessageLength;
    UByte TiPd;
    UByte MessageType;
};
typedef struct MnccRejectIndStruct MnccRejectIndType;

#define getMnccRejectIndTypeIE(signal) ((unsigned char*)signal + offsetof(MnccRejectIndType, MessageType) + sizeof(UByte))

struct MnccReleaseReqStruct
{
    SignalType TheSignal;
    MessageLengthType MessageLength;
    UByte TiPd;
    UByte MessageType;
};
typedef struct MnccReleaseReqStruct MnccReleaseReqType;

#define getMnccReleaseReqTypeIE(signal) ((unsigned char*)signal + offsetof(MnccReleaseReqType, MessageType) + sizeof(UByte))

struct MnccReleaseCfmStruct
{
    SignalType TheSignal;
    MessageLengthType MessageLength;
    UByte TiPd;
    UByte MessageType;
};
typedef struct MnccReleaseCfmStruct MnccReleaseCfmType;

#define getMnccReleaseCfmTypeIE(signal) ((unsigned char*)signal + offsetof(MnccReleaseCfmType, MessageType) + sizeof(UByte))

struct MnccReleaseIndStruct
{
    SignalType TheSignal;
    MessageLengthType MessageLength;
    UByte TiPd;
    UByte MessageType;
};
typedef struct MnccReleaseIndStruct MnccReleaseIndType;

#define getMnccReleaseIndTypeIE(signal) ((unsigned char*)signal + offsetof(MnccReleaseIndType, MessageType) + sizeof(UByte))

struct MnccReleaseResStruct
{
    SignalType TheSignal;
    MessageLengthType MessageLength;
    UByte TiPd;
    UByte MessageType;
};
typedef struct MnccReleaseResStruct MnccReleaseResType;

#define getMnccReleaseResTypeIE(signal) ((unsigned char*)signal + offsetof(MnccReleaseResType, MessageType) + sizeof(UByte))

#endif /* CC_PRIMITIVES__ */
