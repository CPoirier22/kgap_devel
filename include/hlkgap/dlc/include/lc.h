/*
 ********************************************************************
 *
 * Module: lc.h
 *
 * Config-item: ?
 *
 * Contents: This file contains the Lc definitions and structures.
 *
 * Author: DDU
 *
 * Copyright Kirk Telecom A/S. All rights reserved.
 ********************************************************************
 */

#ifndef Lc_HEADER__
#define Lc_HEADER__

#include "../../../common/include/identify.h"
#include "../../util/include/bintree.h"
#include "lcprim.h"
#include "../../common/include/sformat.h"
#include "../../dduos/include/dduos.h"


#define MAC_ABNORMAL_DISCONNECT     1
#define MAC_NORMAL_DISCONNECT       0

#define DL_05_TIMER                 5
#define DL_06_TIMER                 6
#define DL_05_TIME_OUT_VALUE        1000
#define DL_06_TIME_OUT_VALUE        400

#define N251                        3

#define SDU_SIZE                    5


struct LcEncryptIndStruct
{
    SignalType TheSignal;
    UByte EncryptionStatus;
};
typedef struct LcEncryptIndStruct LcEncryptIndType;

struct LcDataReqStruct
{
    SignalType TheSignal;
    void *DataPointer;
    UByte DeleteTheSignal;
};
typedef struct LcDataReqStruct LcDataReqType;

struct LcDataIndStruct
{
    SignalType TheSignal;
    void *DataPointer;
};
typedef struct LcDataIndStruct LcDataIndType;

struct LcMacDisReqStruct
{
    SignalType TheSignal;
    UByte Reason;
};
typedef struct LcMacDisReqStruct LcMacDisReqType;

struct LcMacDisIndStruct
{
    SignalType TheSignal;
    UByte Reason;
};
typedef struct LcMacDisIndStruct LcMacDisIndType;

struct LcEncKeyReqStruct
{
    SignalType TheSignal;
    DckType EncKey;               /* Dck = Derived Cipher Key (That's what it's called on NWK layer) */
};
typedef struct LcEncKeyReqStruct LcEncKeyReqType;

extern BinTreeTopType LcTreeTop;
extern BinTreeTopType MCEITreeTop;

#endif /* Lc_HEADER__ */
