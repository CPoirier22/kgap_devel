/*
 ********************************************************************
 *
 * Module: f_hl_me.h
 *
 * Config-item: ?
 *
 * Contents: This file contains the fixed part higher layer ME
 *     structures.
 *
 * Author: DDU
 *
 * Copyright Kirk Telecom A/S. All rights reserved.
 ********************************************************************
 */

#ifndef HL_LLME_HEADER__
#define HL_LLME_HEADER__

#include "../../dduos/include/dduos.h"
#include "hlmepri.h"
#include "../../common/include/sformat.h"

typedef enum
{
    MeReserved,
    MeConnected,
    MeConPpToPp,
    MeReservedHandoverPending,
    MeConnectedHandoverPending,
    MeConPpToPpHandoverPending,
    MeReservedInvolHOPending,
    MeConnectedInvolHOPending,
    MeConPpToPpInvolHOPending,
    MeDormant,
    MeDormantWaitForInstanceData
} MeStateType;

typedef enum
{
    /* These variant are used when reserved and connected to LID */
    HOLocalToLocal,
    HOLocalToRemote,
    HORemoteToLocal,
    HORemoteToRemote,
    /* These variant are used when connected between two PP */
    HOLocalToLocalConLocal,
    HOLocalToRemoteConLocal,
    HORemoteToLocalConLocal,
    HORemoteToRemoteConLocal,
    HOLocalToLocalConRemote,
    HOLocalToRemoteConRemote,
    HORemoteToLocalConRemote,
    HORemoteToRemoteConRemote
} HOVariantType;

typedef struct
{
    PMIDType Pmid;
    PMIDType OtherPmid;
    MeStateType MeState;
    HOVariantType HOVariant;
    UByte HOMcei;                 /* Points at the affected MCEI (field Mcei) doing handover of a*/
    /* combined instance*/
    UByte Lid;
    struct
    {
        UByte Rpn;
        UByte Cn;
        UByte NextRpn;
        UByte NextCn;
    }
    Mcei[2];                    /* If not a combined instance only MCEI 0 in use*/
    /* If a combined instance host in MCEI 0 and guest in MCEI 1*/
    HlMeUPlaneIndType *PreservedHlMeUPlaneInd;
    SignalType *SignalQueueFirst;
    SignalType *SignalQueueLast;
}
MeInstanceType;

typedef struct
{
    RPNType Rpn;
    UByte NextCcfMeEeReadReqAddress;
    HlMeEeReadRfpReqType *HlMeEeReadRfpReqQueueFront;
    HlMeEeReadRfpReqType *HlMeEeReadRfpReqQueueBack;
    TimerType *EeReadRfpTimer;
    UByte PutIndex;
    HlMeEeReadRfpCfmType *HlMeEeReadRfpCfm;
}
EeReadRfpInstanceType;

#endif /* HL_LLME_HEADER__ */
