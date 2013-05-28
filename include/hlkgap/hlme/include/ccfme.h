/*
 ********************************************************************
 *
 * Module:  ccfme.h
 *
 *  Config-item:  ?
 *
 * Contents:  This file contains the fixed part cluster control function
 *          LLME structures.
 *
 *  Author: DDU
 *
 * Copyright Kirk Telecom A/S. All rights reserved.
 ********************************************************************
 */

#ifndef FIXED_CCF_LLME_HEADER__
#define FIXED_CCF_LLME_HEADER__

#include "../../dduos/include/dduos.h"

struct CcfMeUPlaneCfmStruct
{
    SignalType TheSignal;
    UByte BCF, LCN, ReturnProcess, ReturnAddress[4], Action;
};
typedef struct CcfMeUPlaneCfmStruct CcfMeUPlaneCfmType;

struct AudioLineCtrlReqStruct
{
    SignalType TheSignal;
    UByte Lid;
    PMIDType Pmid;
    UByte option;
};
typedef struct AudioLineCtrlReqStruct AudioLineCtrlReqType;

struct CcfMeUPlaneReqStruct
{
    SignalType TheSignal;
    UByte UPlaneSlotNo;
};
typedef struct CcfMeUPlaneReqStruct CcfMeUPlaneReqType;

struct CcfMeDummyIndStruct
{
    SignalType TheSignal;
    UByte Channel;
};
typedef struct CcfMeDummyIndStruct CcfMeDummyIndType;

struct CcfMeDummyResStruct
{
    SignalType TheSignal;
    UByte Channel;
    UByte AcceptFlag;
};
typedef struct CcfMeDummyResStruct CcfMeDummyResType;

struct CcfMeMfnoResStruct
{
    SignalType TheSignal;
    long Mfno;
};
typedef struct CcfMeMfnoResStruct CcfMeMfnoResType;

struct CcfMeCdvResStruct
{
    SignalType TheSignal;
    U16Bits CableDelay;
};
typedef struct CcfMeCdvResStruct CcfMeCdvResType;

typedef struct
{
    SignalType TheSignal;
    U16Bits HigherLayerCap;
    UByte Rfpi[5];
}
CcfMePreloadReqType;

typedef struct
{
    SignalType TheSignal;
    UByte EEmessageID;
    UByte NoOfBytes;
}
CcfMeEeDataCfmType;

#define getCcfMeEeDataCfmTypeIE(signal) ((unsigned char*)signal + offsetof(CcfMeEeDataCfmType, NoOfBytes) + sizeof(UByte))

typedef struct
{
    SignalType TheSignal;
    UByte TaskID;
    UByte EEmessageID;
    UByte NoOfBytes;
    U16Bits EEaddress;
}
CcfMeEeReadReqType;

typedef struct
{
    SignalType TheSignal;
    UByte TaskID;
    UByte EEmessageID;
    UByte NoOfBytes;
    U16Bits EEaddress;
}
CcfMeEeWriteReqType;

struct ExtHOComindStruct
{
    SignalType TheSignal;
    UByte Pmid[3];
};
typedef struct ExtHOComindStruct ExtHOComindType;
#endif /* FIXED_CCF_LLME_HEADER__ */
