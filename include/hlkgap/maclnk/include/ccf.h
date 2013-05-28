/*
 ********************************************************************
 *
 * Module: ccf.h
 *
 * Config-item: ?
 *
 * Contents: This file contains the fixed part cluster control function
 *     definitions and structures.
 *
 * Author: DDU
 *
 * Copyright Kirk Telecom A/S. All rights reserved.
 *
 * $Header:   K:\ph\132580xx\xx\basis\archive\header\ccf.h_v   1.5   08 Mar 1996 14:31:58   MK  $
 ********************************************************************
 */

#ifndef CCF_HEADER__
#define CCF_HEADER__

#define CLsCHANNEL   0x10
#define CLfCHANNEL   0x11
#define SInCHANNEL   0x13

#define MAC_NORMAL_PAGING 0x00
#define MAC_FAST_PAGING  0xFF

#include "../../common/include/sformat.h"

struct MacCoDtrIndStruct
{
    SignalType TheSignal;
};
typedef struct MacCoDtrIndStruct MacCoDtrIndType;

struct MacConIndStruct
{
    SignalType TheSignal;
    PMIDType PMID;
    UByte ConnectionHandoverFlag;
};
typedef struct MacConIndStruct MacConIndType;

struct MacDisIndStruct
{
    SignalType TheSignal;
    UByte Reason;
};
typedef struct MacDisIndStruct MacDisIndType;

typedef SignalType MacDisReqType;

struct MacCoDataReqStruct
{
    SignalType TheSignal;
};
typedef struct MacCoDataReqStruct MacCoDataReqType;

struct MacCoDataIndStruct
{
    SignalType TheSignal;
};
typedef struct MacCoDataIndStruct MacCoDataIndType;

struct MacPageReqStruct
{
    SignalType  TheSignal;
    UByte       PageFieldLength;
    UByte       LongPageFlag;
};
typedef struct MacPageReqStruct MacPageReqType;

#define getMacPageReqTypeIE(signal) ((unsigned char*)signal + offsetof(MacPageReqType, LongPageFlag) + sizeof(UByte))

struct MacEncKeyReqStruct
{
    SignalType TheSignal;
    DckType EncKey; /* Dck = Derived Cipher Key (That's what it's called on NWK layer) */
};
typedef struct MacEncKeyReqStruct MacEncKeyReqType;

struct MacEncEksIndStruct
{
    SignalType TheSignal;
    UByte EncryptionStatus;
};
typedef struct MacEncEksIndStruct MacEncEksIndType;

#endif /* CCF_HEADER__ */
