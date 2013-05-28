/*
 ********************************************************************
 *
 * Module: lapc.h
 *
 * Config-item: ?
 *
 * Contents: This file contains the general LAPC definitions and
 *     structures. It also includes the necessary modules used by
 *     LAPC.
 *
 * Author: DDU
 *
 * Copyright Kirk Telecom A/S. All rights reserved.
 ********************************************************************
 */

#ifndef LAPC_HEADER__
#define LAPC_HEADER__

#include "../../dduos/include/dduos.h"
#include "../../../common/include/identify.h"
#include "lapcprim.h"
#include "lcprim.h"
#include "lc.h"
#include "faframe.h"

#define CLASS_U       0
#define CLASS_A       1
#define CLASS_B0      2
#define CLASS_B1      3
#define CLASS_B2      4
#define CLASS_B3      5
#define CLASS_B4      6
#define CLASS_B_UNASSIGNED  7
#define DLEI_SAPI_0     0x00
#define DLEI_SAPI_3     SAPI_MASK
#define DL_04_TIMER     4
#define DL_07_TIMER     7

#define N250        3
#define DL_NORMAL_RELEASE 0
#define DL_ABNORMAL_RELEASE 1
#define Cs_CHANNEL      0
#define NLF_SET       0x80
#define NLF_CLEAR     0x00
#define MAX_FRAMES_PR_MSG_RX 2
#define MAX_FRAMES_PR_MSG_TX 2

struct FAFrameQueueStruct
{
    struct FAFrameQueueStruct *NextFAFramePointer;
    FAFrameDataType *FAFrameData;
    UByte InUseFlag;
    UByte module2module;
};
typedef struct FAFrameQueueStruct FAFrameQueueType;

struct DlDataIndStruct
{
    SignalType TheSignal;
    U16Bits MessageUnitLength;
};
typedef struct DlDataIndStruct DlDataIndType;

#define getDlDataIndTypeIE(signal) ((unsigned char*)signal + offsetof(DlDataIndType, MessageUnitLength) + sizeof(U16Bits))

struct ClassAStruct
{
    UByte ClassAState;
    UByte Vs, Va, Vr;
    TimerType *DL_04_Timer, *DL_07_Timer;
    UByte NormalReleaseFlag, MsgFull,     /* TRUE if MAX_FRAMES_PR_MSG_RX frames are recieved for a message*/
    RetransmissionCounter;
    FAFrameQueueType *NWKMessageQueue,    /* from DL_DATA_req */
    *NWKLastMessage;
    DlDataIndType *DlDataInd;     /* Used while receiving data for a multi-frame message*/
    UByte NoOfFAFrameRcvForMsg;
};

typedef struct ClassAStruct ClassAType;

struct DlEstablishIndStruct
{
    SignalType TheSignal;
    U16Bits MessageUnitLength;
};
typedef struct DlEstablishIndStruct DlEstablishIndType;

#define getDlEstablishIndTypeIE(signal) ((unsigned char*)signal + offsetof(DlEstablishIndType, MessageUnitLength) + sizeof(U16Bits))

struct DlReleaseReqStruct
{
    SignalType TheSignal;
    UByte ReleaseMode;
};
typedef struct DlReleaseReqStruct DlReleaseReqType;

struct DlReleaseIndStruct
{
    SignalType TheSignal;
    UByte ReleaseMode;
};
typedef struct DlReleaseIndStruct DlReleaseIndType;

struct DlReleaseCfmStruct
{
    SignalType TheSignal;
    UByte ReleaseMode;
};
typedef struct DlReleaseCfmStruct DlReleaseCfmType;

struct DlEstablishReqStruct
{
    SignalType TheSignal;
    U16Bits MessageUnitLength;
};
typedef struct DlEstablishReqStruct DlEstablishReqType;

#define getDlEstablishReqTypeIE(signal) ((unsigned char*)signal + offsetof(DlEstablishReqType, MessageUnitLength) + sizeof(U16Bits))

struct DlDataReqStruct
{
    SignalType TheSignal;
    U16Bits MessageUnitLength;
};
typedef struct DlDataReqStruct DlDataReqType;

#define getDlDataReqTypeIE(signal) ((unsigned char*)signal + offsetof(DlDataReqType, MessageUnitLength) + sizeof(U16Bits))

typedef enum
{
    Clear,
    Encrypted
} EncryptionStatusType;

typedef struct
{
    SignalType TheSignal;
    DckType Dck;
}
DlEncKeyReqType;

typedef struct
{
    SignalType TheSignal;
    EncryptionStatusType EncryptionCommand;
}
DlEncryptReqType;

typedef struct
{
    SignalType TheSignal;
    EncryptionStatusType EncryptionStatus;
}
DlEncryptCfmType;

typedef struct
{
    SignalType TheSignal;
    EncryptionStatusType EncryptionStatus;
}
DlEncryptIndType;

#endif /* LAPC_HEADER__ */
