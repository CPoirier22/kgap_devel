/*
 ********************************************************************
 *
 * Module:  plceprim.h
 *
 *  Config-item:  ?
 *
 * Contents:  Primitives for LCE signalhandler is defined in this file.
 *
 *  Author: DDU
 *
 * Copyright Kirk Telecom A/S. All rights reserved.
 *
 * $Header:   K:/PH/140960xx/00/Archive/H/plceprim.h_v   1.0   Oct 24 2002 11:51:42   mne  $
 *
 * $Log:   K:/PH/140960xx/00/Archive/H/plceprim.h_v  $
 *
 *    Rev 1.0   Oct 24 2002 11:51:42   mne
 * Initial PP5 version for 428
 *
 *    Rev 1.7   Sep 02 1996 10:20:26   BJR
 * Added LCE_LINK_RELEASE_ALL_req.
 *
 *    Rev 1.6   Aug 06 1996 17:57:30   BJR
 * Replaced LCE_READ_TPUI primitives with LCE_READ_IWU_DATA primitives.
 *
 *    Rev 1.5   Jul 18 1996 15:54:54   BJR
 * Added LCE_READ_TPUI_ind and LCE_READ_TPUI_res.
 *
 *    Rev 1.4   06 Feb 1996 10:12:56   BJR
 * Reintroduced LCE_ESTABLISH_ind.
 *
 *    Rev 1.3   26 Jan 1996 13:15:50   BJR
 * Removed primitives LCE_PAGE_ind, LCE_PAGE_res and LCE_ESTABLISH_ind.
 *
 *    Rev 1.2   14 Nov 1995 15:56:54   BJR
 * Added LCE primitive structures.
 *
 *    Rev 1.1   26 Jan 1995 13:08:08   CB
 * Fileheader added
 *
 *    Rev 1.0   20 Jan 1995 12:55:06   CB
 * Initial version
 *
 ********************************************************************
 */

#ifndef P_LCE_PRIMITIVES__
#define P_LCE_PRIMITIVES__

/****************************************************************************/
#define LCE_DATA_req                0x00
#define LCE_DATA_ind                0x01

#define LCE_RESOURCE_RESERVE_req    0x02
#define LCE_RESOURCE_RESERVE_cfm    0x03

#define LCE_ESTABLISH_req           0x04
#define LCE_ESTABLISH_cfm           0x05
#define LCE_ESTABLISH_ind           0x06

#define LCE_LINK_RELEASE_req        0x07
#define LCE_LINK_RELEASE_ind        0x08

#define LCE_READ_IWU_DATA_ind       0x09
#define LCE_READ_IWU_DATA_res       0x0A

#define LCE_LINK_RELEASE_ALL_req    0x0B

#define LCE_TUNNEL_req              0x0C

typedef struct LCEDataReqStruct
{
    SignalType  Header;        /* Address = XXEI */
    U16Bits     MessageLength;
    UByte       MessageUnit[48];
}
LCEDataReqType;

typedef struct LCEDataIndStruct
{
    SignalType  Header;        /* Address = XXEI */
    U16Bits     MessageLength;
    UByte       MessageUnit[48];
}
LCEDataIndType;

typedef struct LCEResourceReserveReqStruct
{
    SignalType  Header;         /* Address = XXEI */
    UByte       CallAttributes[48];
}
LCEResourceReserveReqType;

typedef struct LCEResourceReserveCfmStruct
{
    SignalType  Header;         /* Address = XXEI */
    UByte       CallAttributes[50]; /*The call attributes are followed by additional parameters*/
}
LCEResourceReserveCfmType;

typedef struct LCELinkReleaseReqStruct
{
    SignalType  Header;         /* Address = XXEI */
    UByte       ReleaseReason[2];
}
LCELinkReleaseReqType;

typedef struct LCELinkReleaseIndStruct
{
    SignalType  Header;         /* Address = XXEI */
}
LCELinkReleaseIndType;

typedef struct
{
    SignalType  Header;
    UByte *     TpuiPtr;
}
LCEReadIwuDataIndType;

typedef struct
{
    SignalType  Header;
    UByte       SubsNo;
}
LCEReadIwuDataResType;

typedef struct LCELinkReleaseAllReqStruct
{
    SignalType  Header;         /* Address not used */
}
LCELinkReleaseAllReqType;

#endif /* P_LCE_PRIMITIVES */
