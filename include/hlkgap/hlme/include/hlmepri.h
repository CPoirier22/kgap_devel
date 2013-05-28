/*
 ********************************************************************
 *
 * Module: hlmepri.h
 *
 * Config-item: ?
 *
 * Contents: This file contains the fixed part data link layer LLME
 *     primitive definitions.
 *
 * Author: DDU
 *
 * Copyright Kirk Telecom A/S. All rights reserved.
 *
 * $Header:   K:/ph/srclib/me/basis/archive/h/hlmepri.h_v   1.6.1.3.1.2   Nov 18 2003 15:24:02   on  $
 *
 * $Log:   K:/ph/srclib/me/basis/archive/h/hlmepri.h_v  $
 *
 *    Rev 1.6.1.3.1.2   Nov 18 2003 15:24:02   on
 * Initial version of IP 600
 *
 *    Rev 1.6.1.3.1.1   20 Nov 1999 15:43:26   bjr
 * Added support of connection from PP to PP.
 *
 *    Rev 1.6.1.3.1.0   13 Oct 1999 15:24:50   bjr
 * Removed HL_ME_DATA_ind DataType LINK_DOWN that was not used anyhow.
 * Removed primitive HL_ME_DATA_res that was not used anyhow.
 *
 *    Rev 1.6.1.3   10 Aug 1999 15:38:36   BJR
 * Added parameter Lrpns to HL_ME_START_CDM_req.
 *
 *    Rev 1.6.1.2   14 Jun 1999 09:39:04   BJR
 * Added HL_ME_EE_READ_req, HL_ME_EE_READ_cfm, HL_ME_EE_WRITE_req and HL_ME_EE_WRITE_cfm.
 *
 *    Rev 1.6.1.1   08 Jun 1999 14:21:44   mth
 * Implemented DiagnosticTool features
 *
 *    Rev 1.6.1.0   21 May 1999 10:39:14   BJR
 * Added HL_ME_LOAD_FLASH_RFP_req and HL_ME_LOAD_FLASH_RFP_cfm.
 *
 *    Rev 1.6   20 Aug 1998 10:38:26   bjr
 * Added HL_ME_RESTART_RFP_req.
 *
 *    Rev 1.5   23 Feb 1998 12:50:54   BJR
 * Moved definition of primitive structures from F_HL_ME.H.
 * Added AcceptFlag to HL_ME_U_PLANE_ind (is now identical to HL_ME_U_PLANE_res).
 * Removed HL_ME_INIT_RPN_ind that was not used.
 * Added primitives HL_ME_TRUNK_U_PLANE_req and HL_ME_TRUNK_U_PLANE_cfm.
 * Removed definition of DataType LINK_DOWN that was unused.
 *
 *    Rev 1.4   Jul 29 1997 15:15:52   BJR
 * Added HL_ME_START_CDM_cfm.
 *
 *    Rev 1.3   Sep 16 1996 14:00:50   MK
 * Definition of HL_ME_START_CDM_req added.
 *
 *    Rev 1.2   Jun 27 1996 08:57:32   MK
 * Defined HL_ME_INIT_RPN_ind.
 *
 *    Rev 1.1   Jun 11 1996 21:15:32   BJR
 * Added HL_ME_PRELOAD_req.
 *
 *    Rev 1.0   26 Sep 1995 12:11:34   MK
 * Initial Version based on dlcmepri.h
 * Only used primitives defined.
 *
 *    Rev 1.1   26 Jan 1995 13:07:24   CB
 * Fileheader added
 *
 *    Rev 1.0   20 Jan 1995 12:54:50   CB
 * Initial version
 *
 ********************************************************************
 */

#ifndef HLMEPRI_H__
#define HLMEPRI_H__

#include "../../common/include/sformat.h"

#define HL_ME_U_PLANE_ind     0x02
#define HL_ME_U_PLANE_res     0x03

#define HL_ME_DATA_ind      0x06

#define HL_ME_PRELOAD_req     0x08

#define HL_ME_START_CDM_req      0x0C
#define HL_ME_START_CDM_cfm      0x0D

#define HL_ME_TRUNK_U_PLANE_req 0x10
#define HL_ME_TRUNK_U_PLANE_cfm  0x11

#define HL_ME_RESTART_RFP_req    0x14

#define HL_ME_LOAD_FLASH_RFP_req 0x16
#define HL_ME_LOAD_FLASH_RFP_cfm 0x17

#define HL_ME_EE_READ_RFP_req    0x1A
#define HL_ME_EE_READ_RFP_cfm    0x1B

#define HL_ME_EE_WRITE_RFP_req   0x1C
#define HL_ME_EE_WRITE_RFP_cfm   0x1D

#define HL_ME_U_PLANE_RELAY_ind 0x22

#define HL_ME_INSTANCE_DATA_req  0x24


/*Used by DiagnosticTool*/
#ifdef Diagnostic_Tool
#define HL_ME_DIAGNOSTIC_SLAVE_SETUP_req              0x30
#define HL_ME_DIAGNOSTIC_SLAVE_CallStatistic_req      0x31
#define HL_ME_DIAGNOSTIC_SLAVE_USERLOGSTOP_req        0x32
#define HL_ME_DIAGNOSTIC_SLAVE_GETCCFPDATA_req        0x33
#define HL_ME_DIAGNOSTIC_SLAVE_GETVARIABLESTATUS_req  0x35
#define HL_ME_DIAGNOSTIC_MASTER_GETVARIABLESTATUS_cfm 0x36
#define HL_ME_DIAGNOSTIC_MASTER_LOGSTOP_req           0x37
#define HL_ME_DIAGNOSTIC_SLAVE_LOGSTOP_req            0x38
#define HL_ME_DIAGNOSTIC_SLAVE_ResetCounters_req      0x39
#endif /* Diagnostic_Tool*/

typedef struct
{
    SignalType  TheSignal;
    ProcessIdType ReturnProcess;
    AddressType ReturnAddress;
    UByte     Action;
    UByte       AcceptFlag;
    UByte       NewMeState;
}
HlMeUPlaneIndType;

#define getHlMeUPlaneIndTypeIE(signal) ((unsigned char*)signal + offsetof(HlMeUPlaneIndType, NewMeState) + sizeof(UByte))

typedef struct
{
    SignalType  TheSignal;
    ProcessIdType       ReturnProcess;
    AddressType ReturnAddress;
    UByte     Action;
    UByte       AcceptFlag;
}
HlMeUPlaneResType;

/* Action (used in HL_ME_U_PLANE_ind/res)*/
#define HL_ME_U_PLANE_CONNECT             0x01
#define HL_ME_U_PLANE_RELEASE             0x03
#define HL_ME_U_PLANE_START_HANDOVER      0x04
#define HL_ME_U_PLANE_PROCEED_HANDOVER    0x05
#define HL_ME_U_PLANE_HANDOVER_FAIL       0x07
#define HL_ME_U_PLANE_START_INVOL_HO      0x08
#define HL_ME_U_PLANE_PROCEED_INVOL_HO    0x09
#define HL_ME_U_PLANE_CONNECT_PP_TO_PP    0x0A
#define HL_ME_U_PLANE_EXTERNAL_HANDOVER   0x0B     /* OZ 0x08 is used in ECI project!*/

typedef struct
{
    SignalType  TheSignal;
    UByte       ReturnProcess;
    AddressType ReturnAddress;
    UByte       DataType;
}
HlMeDataIndType;

/* DataType (used in HL_ME_DATA_ind/res)*/
#define MCEI_SET     0x00
#define DISCONNECT   0x02
#define EXTERN_HO    0x03

typedef struct
{
    SignalType  SignalHeader;     /* CPN in address field */
    UByte       TrunkAction;
}
HlMeTrunkUPlaneReqType;

typedef struct
{
    SignalType  SignalHeader;     /* CPN in address field */
    UByte       TrunkError;
}
HlMeTrunkUPlaneCfmType;

/* TrunkAction (used in HL_ME_TRUNK_U_PLANE_req)*/
#define HL_ME_TRUNK_U_PLANE_RESERVE_CONNECT  0x00
#define HL_ME_TRUNK_U_PLANE_CONNECT          0x01
#define HL_ME_TRUNK_U_PLANE_RELEASE_FREE     0x02
#define HL_ME_TRUNK_U_PLANE_RELEASE          0x03
#define HL_ME_TRUNK_U_PLANE_CONNECT_DOWNLINK 0x04
#define HL_ME_TRUNK_U_PLANE_CONNECT_UPLINK   0x05
#define HL_ME_TRUNK_U_PLANE_MUTE_DOWNLINK    0x06
#define HL_ME_TRUNK_U_PLANE_CONNECT_SIMPLEX  0x07

/* TrunkError (used in HL_ME_TRUNK_U_PLANE_cfm)*/
#define HL_ME_TRUNK_U_PLANE_OK                  0x00
#define HL_ME_TRUNK_U_PLANE_NO_TRUNK_LINE_AVAIL 0x01

typedef UByte TLIDType;

#define MAX_TLID  63
#define TLID_NIL  0xFF

typedef enum
{
    HLC_ADPCM_G27_VoiceServ =  0x0080,
    HLC_GAP_PAP_BasicSpeech =  0x0040,
    HLC_NonVoiceCirSwServ =    0x0020,
    HLC_NonVoicePackSwServ =   0x0010,
    HLC_StdAuthRequired =      0x0008,
    HLC_StdCipheringSupp =     0x0004,
    HLC_LocRegSupp =           0x0002,
    HLC_SIM_ServAvail =        0x0001,
    HLC_CISS_ServAvail =       0x4000,
    HLC_CLMS_ServAvail =       0x2000,
    HLC_COMS_ServAvail =       0x1000,
    HLC_AccRightsReqSupp =     0x0800,
    ExtHandoverSupp =          0x0400,
    ConHandoverSupp =          0x0200
}HDLCCodeType;

typedef struct
{
    SignalType  SignalHeader;
    UByte length;
}
HlMeSimulatorType;

typedef struct
{
    SignalType  SignalHeader;
    U16Bits     HigherLayerCap;
    UByte       Pari [ MaxAriOctets - 1 ]; /* We are only supporting class B, C and D so 4 bytes is enough */
}
HlMePreloadReqType;

typedef struct
{
    SignalType  SignalHeader;  /* CPN in address field*/
    U16Bits     Lrpns;         /* Bit-pattern representing the RFP's to perform CDM on (by LRPN)*/
}
HlMeStartCdmReqType;

typedef struct
{
    SignalType  SignalHeader;  /* CPN in address field*/
    UByte       Rpn;
}
HlMeRestartRfpReqType;

typedef struct
{
    SignalType  SignalHeader;  /* CPN in address field*/
    U16Bits     Lrpns;         /* Bit-pattern representing the RFP's to load code to defined by LRPN's*/
}
HlMeLoadFlashRfpReqType;

typedef struct
{
    SignalType  SignalHeader;
}
HlMeLoadFlashRfpCfmType;

typedef enum
{
    RFP_EE_EC_Success           = 0x00,
    RFP_EE_EC_NoContact         = 0x01,
    RFP_EE_EC_ErrorDoingReading = 0x02
}RFPEEContactType;

typedef struct
{
    SignalType  SignalHeader;  /* CPN in address field*/
    RPNType     Rpn;
    UByte       EEmessage;
    UByte       NoOfBytes;
    U16Bits     EEaddress;
}
HlMeEeReadRfpReqType;

typedef struct
{
    SignalType  SignalHeader;
    RPNType     Rpn;
    UByte       EEmessage;
    UByte       NoOfBytes;
    U16Bits     EEaddress;
    UByte       ErrorCode;
}
HlMeEeReadRfpCfmType;

#define getHlMeEeReadRfpCfmTypeIE(signal) ((unsigned char*)signal + offsetof(HlMeEeReadRfpCfmType, ErrorCode) + sizeof(UByte))

typedef struct
{
    SignalType  SignalHeader;  /* CPN in address field*/
    RPNType     Rpn;
    UByte       EEmessage;
    UByte       NoOfBytes;
    U16Bits     EEaddress;
}
HlMeEeWriteRfpReqType;

typedef struct
{
    SignalType  SignalHeader;
    RPNType     Rpn;
    UByte       EEmessage;
    UByte       NoOfBytes;
    U16Bits     EEaddress;
    UByte       ErrorCode;
}
HlMeEeWriteRfpCfmType;

typedef struct
{
    SignalType  TheSignal;
    PMIDType    DormantPmid;
    UByte       ReturnProcess;
    AddressType ReturnAddress;
    UByte       RelayAction;
    UByte       AcceptFlag;
}
HlMeUPlaneRelayIndType;

#define getHlMeUPlaneRelayIndTypeIE(signal) ((unsigned char*)signal + offsetof(HlMeUPlaneRelayIndType, AcceptFlag) + sizeof(UByte))

/* RelayAction (used in HL_ME_U_PLANE_RELAY_ind)*/
#define HL_ME_U_PLANE_RELAY_DISCONNECT 0x80

typedef struct
{
    SignalType  SignalHeader;  /* CPN in address field*/
    PMIDType    DormantPmid;
    RPNType     Rpn;
    UByte       Cn;
}
HlMeInstanceDataReqType;


#endif /* HLMEPRI_H__ */
