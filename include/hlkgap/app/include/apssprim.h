/*
 ********************************************************************
 *
 * Module:      apssprim.h
 *
 *      Config-item:    ?
 *
 * Contents:    This file contains the definitions of primitives
 *                                      related to F-App-SS.
 *
 *      Author: Kirk telecom / SC
 *
 * Copyright Kirk Telecom A/S. All rights reserved.
 *
 ********************************************************************
 */

#ifndef APSSPRIM__
#define APSSPRIM__

#include "../../dduos/include/dduos.h"
#include "apdbprim.h"
#include "../../common/include/aformat.h"

/* Constant declarations */
#define DisplayTxtLength                36
#define MailTxtLength                   72
#define CallBackNoLength      24
#define MaxStatusIndLength      78
#define SSAAADLength            6

#define Format_1                         1
#define Format_2                         2

/* Primitive definitions */
#define SIO_MSF_SETUP_req  0x00
#define SIO_MSF_SETUP_ind  0x01
#define SIO_MSF_CONNECT_res 0x04
#define SIO_MSF_CONNECT_cfm 0x05
#define SIO_MSF_INFO_req  0x08
#define SIO_MSF_INFO_ind  0x09
#define SIO_MSF_RELEASE_req 0x0c
#define SIO_MSF_RELEASE_ind 0x0d
#define SIO_MSF_STATUS_ind  0x10

#define SIO_BLOCK_CALL_req  0x12
#define SIO_BLOCK_CALL_cfm  0x13

#define SIO_PP_LOAD_SETUP_req          0x14
#define SIO_PP_LOAD_SETUP_cfm          0x15
#define SIO_PP_LOAD_DATA_req           0x18
#define SIO_PP_LOAD_DATA_cfm           0x19
#define SIO_PP_LOAD_REL_req            0x1C
#define SIO_PP_LOAD_REL_ind            0x1E

#define SIO_PP_STATUS_ind              0x28
#define SIO_PP_STATUS_req              0x29
#define SIO_PP_STATUS_cfm              0x2A

#define SIO_MSF_OUTG_MESSAGE_ind       0x2C

/* MSF Release reason definitions */
#define MsfPpNormalRelease             0x00
#define MsfPpOffHook                   0x01
#define MsfPpNoAnswer                  0x02
#define MsfPpOutOfRange                0x03
#define MsfPpBusy                      0x04
#define MsfPpUserUnknown               0x05
#define MsfPpUnknownReleaseReason      0x06
#define MsfUnknownReleaseReason        0x54
#define MsfNoReleaseReason             0x55

#define MsfCcfpNoAnswer                0x20
#define MsfCcfpException01             0x21
#define MsfCcfpException02             0x22
#define MsfCcfpException03             0x23

#define MsfPcNormalRelease             0x00
#define MsfPcException01               0x30
#define MsfPcException02               0x31
#define MsfPcException03               0x32

#define NILchar      0x7f

/* type definitions of s-format types related to F-App-SS */
typedef UByte MsfReleaseReasonType;

/* type definitions of S-format primitives related to F-App-SS */

typedef struct
{
    SignalType SignalHeader;
    UByte PpSetup;
/* Contains LocalNo with 0x00 terminataion and
 * DisplayTxt with 0x00 termination and
 * CallBackNo with 0x00 termination and
 * if of format II also
 * SetupSpec2 and
 * SetupSpec3 and
 * AlertPattern and
 * AlertTone and
 * AlertTimeout and
 * DisplayTimeout and
 * DateAndTime */
} SioMsfSetupReqType;

#define getSioMsfSetupReqTypeIE(signal) ((unsigned char*)signal + offsetof(SioMsfSetupReqType, PpSetup) + sizeof(UByte))

typedef enum
{
    MessageToLong, OutOfRange, SendToExternalDevice, MsgNotDelivered
} ResponseMsgToSendType;

#define TC_BIT    0x80
#define DRA_BIT   0x40
#define DLA_BIT   0x20
#define RAE_BIT   0x10
#define LAE_BIT   0x08

#define RAS_BIT   0x08
#define AD_BIT    0x04
#define NA_BIT    0x02
#define SIS_BIT   0x01

#define F2_BIT    0x80
#define F1_BIT    0x40
#define F0_BIT    0x20
#define CO_BIT    0x10
#define VT_BIT    0x08
#define AA_BIT    0x04
#define VA_BIT    0x02
#define MU_BIT    0x01

typedef struct
{
    SignalType SignalHeader;
} SioMsfSetupIndType;

#define getSioMsfSetupIndTypeIE(signal) ((unsigned char*)signal + sizeof(SignalType))

typedef struct
{
    SignalType SignalHeader;
} SioMsfConnectResType;

typedef struct
{
    SignalType SignalHeader;
    UByte PpSetup;
    /* Contains LocalNo with 0x00 terminataion and
     *     DisplayTxt with 0x00 termination and
     * CallBackNo with 0x00 termination
     */
} SioMsfInfoReqType;

#define getSioMsfInfoReqTypeIE(signal) ((unsigned char*)signal + offsetof(SioMsfInfoReqType, PpSetup) + sizeof(UByte))

typedef struct
{
    SignalType SignalHeader;
    /* Contains LocalNo with 0x00 terminataion and
     *     MsfReleaseReason with length = 1
     */
} SioMsfReleaseReqType;

typedef struct
{
    SignalType SignalHeader;
    /* Contains LocalNo with 0x00 terminataion and
     *     MsfReleaseReason with length = 1
     */
} SioMsfReleaseIndType;

typedef struct
{
    SignalType SignalHeader;
    UByte StatusType;
} SioPpStatusIndType;

#define getSioPpStatusIndTypeIE(signal) ((unsigned char*)signal + offsetof(SioPpStatusIndType, StatusType) + sizeof(UByte))

typedef struct
{
    SignalType SignalHeader;
} SioPpStatusReadReqType;

#endif /* APSSPRIM__ */
