/*
 ********************************************************************
 *
 * Module: fiwuinst.h
 *
 * Config-item: ?
 *
 * Contents: This is the header file for fiwuinst.c.
 *
 * Author: ?Kirk telecom / BJR.
 *
 * Copyright Kirk Telecom A/S. All rights reserved.
 ********************************************************************
 */

#ifndef FIWUINST_H__
#define FIWUINST_H__

#include "../../../nwk/include/ccprim.h"
#include "fiwuprim.h"
#include "../../../nwk/include/mmprim.h"
#include "../../../common/include/sformat.h"


extern FixedIdentityType Park;

#define REASON_MISSING 0xFF

#define DefaultLal   0x1F

#define ORI_MM ( 0x00 | PD_MM )
#define DST_MM ( 0x80 | PD_MM )

typedef enum
{
    CCIdle,
    Active,
    WaitForReleaseCfm,
    WaitForReleaseCom,
    IncSetupWaitForSecurityProcedures,
    WaitForAlertInd,
    WaitForConnectInd,
    WaitForConnectAck,
    OutSetupWaitForSecurityProcedures,
    OutSetupWaitForIwuPrim
}
CCStateType;

typedef enum
{
    CissIdle,
    CissActive
} CissStateType;

typedef enum
{
    OriMMIdle,
    KAWaitForAuthInd,
    KAWaitForCalcRES1,
    KAWaitForCalcRES2,
    STFWaitForAccessRigthsTermCfm,
    APWaitForAuthCfm,
    APWaitForCalculation,
    AUWaitForAuthCfm,
    AUWaitForCalculation,
    COWaitForCipherCfm
} OriMMStateType;

typedef enum
{
    DstMMIdle,
    SRWaitForSubsCreateReq,
    SRWaitForSecurityProcedures,
    LRWaitForAttachRes,
    LRWaitForSecurityProcedures,
    LRWaitForIdentityAssignCfm,
    AFWaitForCalculation
} DstMMStateType;

typedef enum
{
    CCIsCaller,
    DstMMIsCaller
} OriMMCallerType;

typedef struct SecurityOrderStruct
{
    struct SecurityOrderStruct *NextSecurityOrder;
    OriMMCallerType Caller;
    Boolean SecurityProceduresAborted;
    SecurityDescriptorIEType SecurDescript;
}
SecurityOrderType;

typedef struct
{
    PMIDType Pmid;
    PMIDType AssignedPmid;
    CCStateType CCState;
    CissStateType CissState;
    OriMMStateType OriMMState;
    DstMMStateType DstMMState;
    UByte CCTIPD;
    UByte CISSTIPD;
    CcSetupPrimType *PreservedCcSetupPrim;
    MnccSetupIndType *PreservedMnccSetupInd;
    SignalType *IwuPrimQueueFront;
    SignalType *IwuPrimQueueBack;
    OmSubsCreateReqType *PreservedOmSubsCreateReq;
    OmAttachResType *PreservedOmAttachRes;
    MMAccessRightsIndType *PreservedMMAccessRightsInd;
    MMLocateIndType *PreservedMMLocateInd;
    SecurityOrderType *SecurityOrderQueueFront;
    SecurityOrderType *SecurityOrderQueueBack;
    UByte CurrentSecurSpecIndex;
    ProcessIdType PreservedReturnProcessId;
    Boolean SubsRemoveOrderedFromApp;
    TimerType *CCIwuTimer;
    PortableIdentityType Ipui;
    UByte K[16];
    UByte Rs[8];
    UByte RandF[8];
    UByte RandP[8];
    UByte Res1[4];
    UByte CalcRes[4];
    UByte Uak[MaxUakOctets];
    UByte Dck[MaxDckOctets];
    UByte RejectReasonCode;
    /*UByte                      timerflag; //used to detech wrong usage of the CCIwuTimer*/
}
IWUDataType;

IWUDataType *ObtainIWUInstanceData(PMIDType Pmid);

void ClearIWUInstanceDataIfIdle(IWUDataType * InstanceData);

void InitIwuInstanceTree(void);

#define WAIT_FOR_RELEASE_CFM  1
#define WAIT_FOR_RELEASE_COM  2

#define WAIT_FOR_RELEASE_CFM_VAL 50     /* 38 sec. */
#define WAIT_FOR_RELEASE_COM_VAL 50     /* 38 sec. */


#endif /* FIWUINST_H__ */
