/*
 ********************************************************************
 *
 * Module:     fiwuprim.h
 *
 * Config-item: ?
 *
 * Contents:  Header file containing definition of the F-IWU primitives.
 *
 * Author:     Kirk telecom / BJR.
 *
 * Copyright Kirk Telecom A/S. All rights reserved.
 ********************************************************************
 */

#ifndef FIWUPRIM_H__
#define FIWUPRIM_H__

#include "../../../dduos/include/dduos.h"
#include "../../../../common/include/identify.h"

enum
{
    /* OM primitives - - - - - - -*/

    OM_SUBS_CREATE_req = 0x00,
    OM_SUBS_CREATE_cfm = 0x01,
    OM_SUBS_CREATE_ind = 0x02,

    OM_SUBS_REMOVE_req = 0x04,
    OM_SUBS_REMOVE_cfm = 0x05,
    OM_SUBS_REMOVE_ind = 0x06,

    OM_ATTACH_ind = 0x0E,
    OM_ATTACH_res = 0x0F,

    /* CC primitives - - - - - - -*/

    CC_SETUP_prim = 0x80,
    CC_SETUP_ACK_prim = 0x81,
    CC_INFO_prim = 0x82,
    CC_CALL_PROC_prim = 0x83,
    CC_ALERTING_prim = 0x84,
    CC_CONNECT_prim = 0x85,
    CC_CONNECT_ACK_prim = 0x86,
    CC_RELEASE_prim = 0x87,
    CC_RELEASE_COM_prim = 0x88,

    /* Handover primitives - - - -*/
    EXT_HANDOVER_req = 0x98,
    EXT_HANDOVER_res = 0x99,
    EXT_HANDOVER_Rel_ind = 0x9A,
    EXT_HANDOVER_DATA_res = 0x9B,

    /* SS primitives - - - - - - -*/

    SS_SETUP_prim = 0xA0,
    SS_FACILITY_prim = 0xA1,
    SS_RELEASE_prim = 0xA2,
    SS_MSF_prim = 0xA3,
    SS_TUNNEL_prim = 0xA4,
    /* Long Broadcast primitives - - - -*/

    MN_CL_UNITDATA_CBI_req = 0xB0,
    MN_CL_UNITDATA_req = 0xB1,
    MN_CL_UNITDATA_GBI_req = 0xB2,

    MASTER_RPN_NUMBER = 0xBF,

    /* Security primitives - - - -*/

    SECURITY_req = 0x40,
    SECURITY_cfm = 0x41,

    /* Miscellaneous primitives- - - -*/
  	DATE_AND_TIME_res = 0xC0  /* Forwarded StatusPPLocateRegRes from ip.*/
};

typedef struct
{
    SignalType SignalHeader; /* Default PMID in address field */
    Boolean NotAccepted;
    PMIDType NewPmid;
} OmSubsCreateReqType;

#define getOmSubsCreateReqTypeIE(signal) ((unsigned char*)signal + offsetof(OmSubsCreateReqType, NewPmid) + sizeof(PMIDType))

typedef struct
{
    SignalType SignalHeader; /* Default PMID in address field */
    Boolean NotAccepted;
} OmSubsCreateCfmType;

#define getOmSubsCreateCfmTypeIE(signal) ((unsigned char*)signal + offsetof(OmSubsCreateCfmType, NotAccepted) + sizeof(Boolean))

typedef struct
{
    SignalType SignalHeader; /* Default PMID in address field */
} OmSubsCreateIndType;

#define getOmSubsCreateIndTypeIE(signal) ((unsigned char*)signal + sizeof(SignalType))

typedef struct
{
    SignalType SignalHeader; /* Assigned PMID in address field */
} OmSubsRemoveReqType;

typedef struct
{
    SignalType SignalHeader; /* Assigned PMID in address field */
} OmSubsRemoveCfmType;

typedef struct
{
    SignalType SignalHeader; /* Assigned PMID in address field */
} OmSubsRemoveIndType;

typedef struct
{
    SignalType SignalHeader; /* Address field not used */
    Boolean Allow;
} OmSubsAllowReqType;

typedef struct
{
    SignalType SignalHeader; /* Default PMID in address field */
    PMIDType PmidIdentifyingPP;
} OmAttachIndType;

#define getOmAttachIndTypeIE(signal) ((unsigned char*)signal + offsetof(OmAttachIndType, PmidIdentifyingPP) + sizeof(PMIDType))

typedef struct
{
    SignalType SignalHeader; /* Default PMID in address field */
    Boolean NotAccepted;
} OmAttachResType;

#define getOmAttachResTypeIE(signal) ((unsigned char*)signal + offsetof(OmAttachResType, NotAccepted) + sizeof(Boolean))

/* CcPrimitiveType is a common type definition for CC_SETUP, CC_SETUP_ACK, CC_INFO, CC_CALL_PROC,
 CC_ALERTING, CC_CONNECT, CC_CONNECT_ACK, CC_RELEASE, CC_RELEASE_COM                            */

typedef struct
{
    SignalType SignalHeader;
} CcPrimitiveType;

#define getCcPrimitiveTypeIE(signal) ((unsigned char*)signal + sizeof(SignalType))

typedef struct
{
    SignalType SignalHeader; /* Assigned PMID in address field */
} CcSetupPrimType;

#define getCcSetupPrimTypeIE(signal) ((unsigned char*)signal + sizeof(SignalType))

typedef struct
{
    SignalType SignalHeader; /* Assigned PMID in address field */
} CcSetupAckPrimType;

#define getCcSetupAckPrimTypeIE(signal) ((unsigned char*)signal + sizeof(SignalType))

typedef struct
{
    SignalType SignalHeader; /* Assigned PMID in address field */
} CcInfoPrimType;

#define getCcInfoPrimTypeIE(signal) ((unsigned char*)signal + sizeof(SignalType))

typedef struct
{
    SignalType SignalHeader; /* Assigned PMID in address field */
} CcCallProcPrimType;

#define getCcCallProcPrimTypeIE(signal) ((unsigned char*)signal + sizeof(SignalType))

typedef struct
{
    SignalType SignalHeader; /* Assigned PMID in address field */
} CcAlertingPrimType;

#define getCcAlertingPrimTypeIE(signal) ((unsigned char*)signal + sizeof(SignalType))

typedef struct
{
    SignalType SignalHeader; /* Assigned PMID in address field */
} CcConnectPrimType;

#define getCcConnectPrimTypeIE(signal) ((unsigned char*)signal + sizeof(SignalType))

typedef struct
{
    SignalType SignalHeader; /* Assigned PMID in address field */
    UByte lid;
} CcConnectAckPrimType;

#define getCcConnectAckPrimTypeIE(signal) ((unsigned char*)signal + offsetof(CcConnectAckPrimType, lid) + sizeof(UByte))

typedef struct
{
    SignalType SignalHeader; /* Assigned PMID in address field */
} CcReleasePrimType;

#define getCcReleasePrimTypeIE(signal) ((unsigned char*)signal + sizeof(SignalType))

typedef struct
{
    SignalType SignalHeader; /* Assigned PMID in address field */
} CcReleaseComPrimType;

#define getCcReleaseComPrimTypeIE(signal) ((unsigned char*)signal + sizeof(SignalType))

typedef struct
{
    SignalType SignalHeader; /* Assigned PMID in address field*/
    PMIDType PMID;
    LIDType LID;
    UByte MeState;
    UByte Error;
} EXTHOPrimType;

typedef struct
{
    SignalType SignalHeader; /* Assigned PMID in address field*/
    LIDType LID;
} EXTHODataPrimType;

#define getEXTHODataPrimTypeIE(signal) ((unsigned char*)signal + offsetof(EXTHODataPrimType, LID) + sizeof(LIDType))

typedef struct
{
    SignalType SignalHeader; /* Assigned PMID in address field */
} SsSetupPrimType;

#define getSsSetupPrimTypeIE(signal) ((unsigned char*)signal + sizeof(SignalType))

typedef struct
{
    SignalType SignalHeader; /* Assigned PMID in address field */
} SsFacilityPrimType;

#define getSsFacilityPrimTypeIE(signal) ((unsigned char*)signal + sizeof(SignalType))

typedef struct
{
    SignalType SignalHeader; /* Assigned PMID in address field */
} APPMSFind;

#define getAPPMSFindIE(signal) ((unsigned char*)signal + sizeof(SignalType))

typedef struct
{
    SignalType SignalHeader; /* Assigned PMID in address field */
} SsReleasePrimType;

#define getSsReleasePrimTypeIE(signal) ((unsigned char*)signal + sizeof(SignalType))

typedef struct
{
    SignalType SignalHeader; /* Assigned PMID in address field */
    ProcessIdType ReturnProcessId;
} SecurityReqType;

typedef struct
{
    SignalType SignalHeader; /* Assigned PMID in address field */
    Boolean NotAccepted;
} SecurityCfmType;

#endif /* FIWUPRIM_H__ */
