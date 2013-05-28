/*
 ********************************************************************
 *
 * Module: cissprim.h
 *
 * Config-item: ?
 *
 * Contents: This file contains the definitions of primitives
 *     related to CISS (both fixed and portable part)
 *
 * Author: Kirk telecom / BJR
 *
 * Copyright Kirk Telecom A/S. All rights reserved.
 ********************************************************************
 */

#ifndef CISSPRIM__
#define CISSPRIM__

#include "../../dduos/include/dduos.h"
#include "../../../common/include/identify.h"
#include "../../common/include/sformat.h"

#define MNSS_SETUP_req     0x00
#define MNSS_SETUP_ind  0x02

#define MNSS_FACILITY_req  0x08
#define MNSS_FACILITY_ind  0x0A

#define MNSS_RELEASE_req   0x10
#define MNSS_RELEASE_ind   0x12

/* typedefinitions of S-format primitives related to CISS */

/* MnssPrimitiveType is a common type definition for MNSS_SETUP_req, MNSS_SETUP_ind,
   MNSS_FACILITY_req, MNSS_FACILITY_ind, MNSS_RELEASE_req, MNSS_RELEASE_ind          */

typedef struct
{
    SignalType TheSignal;
    MessageLengthType MessageLength;
    UByte TiPd;
    UByte MessageType;
}
MnssPrimitiveType;

#define getMnssPrimitiveTypeIE(signal) ((unsigned char*)signal + offsetof(MnssPrimitiveType, MessageType) + sizeof(UByte))

typedef struct
{
    SignalType TheSignal;
    MessageLengthType MessageLength;
    UByte TiPd;
}
MnssSetupReqType;

#define getMnssSetupReqTypeIE(signal) ((unsigned char*)signal + offsetof(MnssSetupReqType, TiPd) + sizeof(UByte))

typedef struct
{
    SignalType TheSignal;
    MessageLengthType MessageLength;
    UByte TiPd;
    UByte MessageType;
}
MnssSetupIndType;

#define getMnssSetupIndTypeIE(signal) ((unsigned char*)signal + offsetof(MnssSetupIndType, MessageType) + sizeof(UByte))

typedef struct
{
    SignalType TheSignal;
    MessageLengthType MessageLength;
    UByte TiPd;
    UByte MessageType;
}
MnssFacilityReqType;

#define getMnssFacilityReqTypeIE(signal) ((unsigned char*)signal + offsetof(MnssFacilityReqType, MessageType) + sizeof(UByte))

typedef struct
{
    SignalType TheSignal;
    MessageLengthType MessageLength;
    UByte TiPd;
    UByte MessageType;
}
MnssFacilityIndType;

#define getMnssFacilityIndTypeIE(signal) ((unsigned char*)signal + offsetof(MnssFacilityIndType, MessageType) + sizeof(UByte))

typedef struct
{
    SignalType TheSignal;
    MessageLengthType MessageLength;
    UByte TiPd;
    UByte MessageType;
}
MnssReleaseReqType;

#define getMnssReleaseReqTypeIE(signal) ((unsigned char*)signal + offsetof(MnssReleaseReqType, MessageType) + sizeof(UByte))

typedef struct
{
    SignalType TheSignal;
    MessageLengthType MessageLength;
    UByte TiPd;
    UByte MessageType;
}
MnssReleaseIndType;

#define getMnssReleaseIndTypeIE(signal) ((unsigned char*)signal + offsetof(MnssReleaseIndType, MessageType) + sizeof(UByte))

#endif /* CISSPRIM__ */
