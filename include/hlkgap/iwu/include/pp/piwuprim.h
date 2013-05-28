/*
 ********************************************************************
 *
 * Module:      piwuprim.h
 *
 *  Config-item: ?
 *
 * Contents:   Header file containing definition of the P-IWU primitives.
 *
 *  Author:     Kirk telecom / BJR.
 *
 * Copyright Kirk Telecom A/S. All rights reserved.
 *
 * $Header:   K:/PH/SRCLIB/PP5/BASIS/ARCHIVE/H/piwuprim.h_v   1.2   27 Nov 2003 14:32:10   mne  $
 *
 * $Log:   K:/PH/SRCLIB/PP5/BASIS/ARCHIVE/H/piwuprim.h_v  $
 *
 *    Rev 1.2   27 Nov 2003 14:32:10   mne
 * Error corr.
 *
 *    Rev 1.1   26 Nov 2003 12:06:28   mne
 * E2_MESSAGE added in #ifdef _E2_MESSAGE__
 *
 *    Rev 1.0   Oct 24 2002 11:51:42   mne
 * Initial PP5 version for 428
 *
 *    Rev 1.7.1.0   14 Jun 2000 13:24:40   bjr
 * Added AUTO_LOGIN_BIT.
 *
 *    Rev 1.7   23 Feb 1999 09:58:12   oo
 * File changed for PP2 HW. (Lucy).
 *
 *    Rev 1.6   Feb 17 1997 08:17:18   BJR
 * _CISS__: Added SS_SETUP, SS_FACILITY and SS_RELEASE primitives.
 *
 *    Rev 1.5   Nov 25 1996 18:14:26   BJR
 * OM_ATTACH__: Added OM_ATTACH_ind primitive (conditioned by define OM_ATTACH__).
 *
 *    Rev 1.4   Oct 28 1996 17:19:52   BJR
 * Added subscription status 'Location registration succeeded' (SS_LocRegSucceeded)
 *
 *    Rev 1.3   Oct 10 1996 11:42:26   BJR
 * Added HigherLayerCap to OmSearchRfpiIndType.
 * Replaced Action with Mode in OmSearchRfpiReqType.
 *
 *    Rev 1.2   Sep 02 1996 10:18:54   BJR
 * Added OM_SEARCH_RFPI and OM_USER_ABORT primitives.
 * Removed parameter Status from OM_SUBS_SELECT_cfm.
 *
 *    Rev 1.1   Jul 18 1996 15:53:40   BJR
 * Removed OM_PROMPT_AC_ind and OM_PROMPT_AC_res.
 * Added OM_SUBS_SELECT_req, OM_SUBS_SELECT_cfm, OM_SUBS_STATUS_req, OM_SUBS_STATUS_cfm and
 * OM_SUBS_STATUS_ind.
 *
 *    Rev 1.0   26 Feb 1996 09:59:24   BJR
 * Initial revision.
 *
 ********************************************************************
 */

#ifndef PIWUPRIM_H__
#define PIWUPRIM_H__

#include "../../../dduos/include/dduos.h"
#include "../../../common/include/sformat.h"

enum
{
    OM_SUBS_CREATE_req = 0x00,
    OM_SUBS_CREATE_cfm = 0x01,

    OM_SUBS_REMOVE_req = 0x04,
    OM_SUBS_REMOVE_cfm = 0x05,
    OM_SUBS_REMOVE_ind = 0x06,

    OM_PROMPT_UPI_ind = 0x0A,
    OM_PROMPT_UPI_res = 0x0B,

    OM_SUBS_SELECT_req = 0x0E,
    OM_SUBS_SELECT_cfm = 0x0F,

    OM_SUBS_STATUS_req = 0x10,
    OM_SUBS_STATUS_cfm = 0x11,
    OM_SUBS_STATUS_ind = 0x12,

    OM_SEARCH_RFPI_req = 0x14,
    OM_SEARCH_RFPI_set = 0x15,
    OM_SEARCH_RFPI_ind = 0x16,

    OM_USER_ABORT_req = 0x18,

    OM_ATTACH_ind = 0x1E,

    CC_SETUP_prim = 0x80,
    CC_SETUP_ACK_prim = 0x81,
    CC_INFO_prim = 0x82,
    CC_CALL_PROC_prim = 0x83,
    CC_ALERTING_prim = 0x84,
    CC_CONNECT_prim = 0x85,
    CC_CONNECT_ACK_prim = 0x86,
    CC_RELEASE_prim = 0x87,
    CC_RELEASE_COM_prim = 0x88,

    SS_SETUP_prim = 0xA0,
    SS_FACILITY_prim = 0xA1,
    SS_RELEASE_prim = 0xA2,
    SS_TUNNEL_prim = 0xA4
};

enum                            /* Bits in Status */
{
    SS_Locked = 0x01u,
    SS_Subscripted = 0x02u,
    SS_LocRegSucceeded = 0x04u
};

typedef struct
{
    SignalType SignalHeader;
}
OmSubsCreateReqType;

#define getOmSubsCreateReqTypeIE(signal) ((unsigned char*)signal + sizeof(SignalType))

typedef struct
{
    SignalType SignalHeader;
    Boolean NotAccepted;
}
OmSubsCreateCfmType;

typedef struct
{
    SignalType SignalHeader;
}
OmSubsRemoveReqType;

typedef struct
{
    SignalType SignalHeader;
    Boolean NotAccepted;
}
OmSubsRemoveCfmType;

typedef struct
{
    SignalType SignalHeader;
}
OmSubsRemoveIndType;

typedef struct
{
    SignalType SignalHeader;
}
OmPromptUpiIndType;

typedef struct
{
    SignalType SignalHeader;
}
OmPromptUpiResType;

#define getOmPromptUpiResTypeIE(signal) ((unsigned char*)signal + sizeof(SignalType))

#define FIND_SUBS_FIX_RFPI 0xFF /* Special value for SubsNo*/

#define AUTO_LOGIN_BIT 0x80     /* Bit in SubsNo*/

typedef struct
{
    SignalType SignalHeader;
    UByte SubsNo;
    UByte Rfpi[5];                /* Unused if SubsNo != FIND_SUBS_FIX_RFPI*/
}
OmSubsSelectReqType;

typedef struct
{
    SignalType SignalHeader;
    Boolean NotAccepted;
}
OmSubsSelectCfmType;

typedef struct
{
    SignalType SignalHeader;
}
OmSubsStatusReqType;

typedef struct
{
    SignalType SignalHeader;
    UByte SubsNo;
    UByte Status;
}
OmSubsStatusCfmType;

typedef struct
{
    SignalType SignalHeader;
    UByte SubsNo;
    UByte Status;
}
OmSubsStatusIndType;

typedef enum
{
    SM_Normal = 0x00,
    SM_FindRfpis = 0x01,
    SM_Passiv = 0x02
} SearchModeType;

typedef struct
{
    SignalType SignalHeader;
    UByte SearchMode;
}
OmSearchRfpiReqType;

typedef struct
{
    SignalType SignalHeader;
}
OmUserAbortReqType;

typedef struct
{
    SignalType SignalHeader;
    UByte Rfpi[MaxAriRpnOctets];
    U16Bits HigherLayerCap;
}
OmSearchRfpiIndType;

typedef struct
{
    SignalType SignalHeader;
}
OmAttachIndType;

#define getOmAttachIndTypeIE(signal) ((unsigned char*)signal + sizeof(SignalType))

typedef struct
{
    SignalType SignalHeader;
}
CcSetupPrimType;

#define getCcSetupPrimTypeIE(signal) ((unsigned char*)signal + sizeof(SignalType))

typedef struct
{
    SignalType SignalHeader;
}
CcSetupAckPrimType;

#define getCcSetupAckPrimTypeIE(signal) ((unsigned char*)signal + sizeof(SignalType))

typedef struct
{
    SignalType SignalHeader;
}
CcInfoPrimType;

#define getCcInfoPrimTypeIE(signal) ((unsigned char*)signal + sizeof(SignalType))

typedef struct
{
    SignalType SignalHeader;
}
CcIwuInfoPrimType;

typedef struct
{
    SignalType SignalHeader;
}
CcCallProcPrimType;

#define getCcCallProcPrimTypeIE(signal) ((unsigned char*)signal + sizeof(SignalType))

typedef struct
{
    SignalType SignalHeader;
}
CcAlertingPrimType;

#define getCcAlertingPrimTypeIE(signal) ((unsigned char*)signal + sizeof(SignalType))

typedef struct
{
    SignalType SignalHeader;
}
CcConnectPrimType;

#define getCcConnectPrimTypeIE(signal) ((unsigned char*)signal + sizeof(SignalType))

typedef struct
{
    SignalType SignalHeader;
}
CcConnectAckPrimType;

#define getCcConnectAckPrimTypeIE(signal) ((unsigned char*)signal + sizeof(SignalType))

typedef struct
{
    SignalType SignalHeader;
}
CcReleasePrimType;

#define getCcReleasePrimTypeIE(signal) ((unsigned char*)signal + sizeof(SignalType))

typedef struct
{
    SignalType SignalHeader;
}
CcReleaseComPrimType;

#define getCcReleaseComPrimTypeIE(signal) ((unsigned char*)signal + sizeof(SignalType))

/* SsPrimitiveType is a common type definition for SS_SETUP, SS_FACILITY and SS_RELEASE */

typedef struct
{
    SignalType SignalHeader;
}
SsPrimitiveType;

#define getSsPrimitiveTypeIE(signal) ((unsigned char*)signal + sizeof(SignalType))

typedef struct
{
    SignalType SignalHeader;
}
SsSetupPrimType;

typedef struct
{
    SignalType SignalHeader;
}
SsFacilityPrimType;

#define getSsFacilityPrimTypeIE(signal) ((unsigned char*)signal + sizeof(SignalType))

typedef struct
{
    SignalType SignalHeader;
}
SsReleasePrimType;

#define getSsReleasePrimTypeIE(signal) ((unsigned char*)signal + sizeof(SignalType))

#endif /* PIWUPRIM_H__ */
