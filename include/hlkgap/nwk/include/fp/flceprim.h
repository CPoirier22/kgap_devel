/*
 ********************************************************************
 *
 * Module: flceprim.h
 *
 * Config-item: ?
 *
 * Contents: Primitives for the fixed part LCE signalhandler is defined in this file.
 *
 * Author: DDU
 *
 * Copyright Kirk Telecom A/S. All rights reserved.
 ********************************************************************
 */

#ifndef FLCEPRIM_H__
#define FLCEPRIM_H__

#define LCE_DATA_req     0x00
#define LCE_DATA_ind     0x01

#define LCE_RESOURCE_RESERVE_req 0x02
#define LCE_RESOURCE_RESERVE_cfm 0x03

#define LCE_LINK_RELEASE_req  0x04
#define LCE_LINK_RELEASE_ind  0x05

#define LCE_LINK_RELEASE_ORI_MM_ind 0x06

#define LCE_ESTABLISH_ind   0x09

#define LCE_ENCRYPT_ind   0x0A

#define LCE_TUNNEL_req 0x0C

typedef struct LCEDataReqStruct
{
    SignalType Header;            /* Address = XXEI */
    U16Bits MessageLength;
    UByte MessageUnit[48];
}
LCEDataReqType;

typedef struct LCEDataIndStruct
{
    SignalType Header;            /* Address = XXEI */
    U16Bits MessageLength;
    UByte MessageUnit[48];
}
LCEDataIndType;

typedef struct LCEResourceReserveReqStruct
{
    SignalType Header;            /* Address = XXEI */
    UByte CallAttributes[48];
}
LCEResourceReserveReqType;

typedef struct LCEResourceReserveCfmStruct
{
    SignalType Header;            /* Address = XXEI */
    UByte CallAttributes[50];     /*The call attributes are followed by additional parameters */
}
LCEResourceReserveCfmType;

typedef struct LCEEstablishIndStruct
{
    SignalType Header;            /* Address = XXEI */
    U16Bits MessageLength;
    UByte MessageUnit[48];
}
LCEEstablishIndType;

#define NormalDisregardLCE02 0xFF       /* This value is given as release reason code in a LCE_LINK_RELEASE_req*/
/* primitive if the link shall be released (normal release) if the only*/
/* remaining owner of the link is the owner that has a LCE02 timer running*/

typedef struct LCELinkReleaseReqStruct
{
    SignalType Header;            /* Address = XXEI */
    UByte ReleaseReason[2];
}
LCELinkReleaseReqType;

typedef struct LCELinkReleaseIndStruct
{
    SignalType Header;            /* Address = XXEI */
}
LCELinkReleaseIndType;

typedef struct LCELinkReleaseOriMMIndStruct
{
    SignalType Header;            /* Address = XXEI */
}
LCELinkReleaseOriMMIndType;

typedef struct LCEEncryptIndStruct
{
    SignalType Header;            /* Address = XXEI */
    UByte Encrypted;
}
LCEEncryptIndType;

/************************************************************************/
#endif /* FLCEPRIM_H__ */
