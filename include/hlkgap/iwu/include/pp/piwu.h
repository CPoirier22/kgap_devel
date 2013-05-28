/*
 ********************************************************************
 *
 * Module:  p_iwu.h
 *
 * Config-item: ?
 *
 * Contents: Header file for P_IWU.C.
 *
 * Author:  Kirk telecom / BJR
 *
 * Copyright Kirk Telecom A/S. All rights reserved.
 *
 * $Header:   K:/PH/SRCLIB/PP5/BASIS/ARCHIVE/H/p_iwu.h_v   1.1   27 Nov 2003 11:15:18   mne  $
 *
 * $Log:   K:/PH/SRCLIB/PP5/BASIS/ARCHIVE/H/p_iwu.h_v  $
 *
 *    Rev 1.1   27 Nov 2003 11:15:18   mne
 * E2 message added in #ifdef _E2_MESSAGE__
 *
 *    Rev 1.23   11 Aug 2003 14:05:58   mne
 * E2 mail handling.
 *
 *    Rev 1.22   Oct 12 2001 13:11:42   kje
 * DurationTimer added (used in connection with reject at location registration)
 * Function StartDurationTimer added.
 *
 *    Rev 1.21   22 Aug 2000 12:53:06   bjr
 * Added flag FixedRfpi to IWUDataType.
 *
 *    Rev 1.20   14 Jun 2000 13:27:36   bjr
 * Changed field SubsNo in IWUData into a union of a bit field where MSB now is a AutoLogin bit and a combined value.
 * Added AutoLoginFindRfpi to CommonStartStateType.
 *
 *    Rev 1.19   23 Feb 1999 09:58:12   oo
 * File changed for PP2 HW. (Lucy).
 *
 *    Rev 1.18   17 Aug 1998 14:50:48   bjr
 * Removed SRWaitForLocateCfm from OriMMStateType.
 *
 *    Rev 1.17   Apr 04 1997 12:23:14   BJR
 * Removed AFWaitForAuthCfm and AFWaitForCalculation from OriMMStateType.
 * Removed STFWaitForAuthOfFt from DstMMStateType.
 * Removed Uak from STFDataType.
 * Removed AFData from IWUData.
 *
 *    Rev 1.16   Feb 17 1997 08:27:32   BJR
 * _CISS__: Added CISSTIPD to IWUData. Added NO_TIPD.
 *
 *    Rev 1.15   Jan 24 1997 14:50:06   BJR
 * Combined states LUWaitForLocateCfm and LUWaitForLocateCfm to LRLUWaitForLocateCfm.
 *
 *    Rev 1.14   Nov 04 1996 10:20:36   BJR
 * Added OrderedSearchModeChange and MacMeFtSysIndReceived to IWUData.
 *
 *    Rev 1.13   Oct 28 1996 17:19:08   BJR
 * Put booleans in IWUData into a bit field called Flags.
 *
 *    Rev 1.12   Oct 10 1996 11:43:16   BJR
 * Removed CommonStartState IWUSearchStopped.
 * Added PassivAtLock to IWUData.
 * Added BackToNormal to IWUData.LocRegReason.
 *
 *    Rev 1.11   Oct 08 1996 20:04:48   BJR
 * Added PutSignalBack.
 *
 *    Rev 1.10   Oct 01 1996 13:51:08   BJR
 * Update from RTX/TD.
*
*    Rev 1.4   26 Sep 1996 17:08:04   JTP
* New state: IWUSearchStopped
*
*    Rev 1.3   Sep 19 1996 11:16:46   td
* Opdatering fra JBR!
*   Det skulle nu v�re muligt at fjerne en
*   subscription.
 *
 *    Rev 1.9   Sep 10 1996 11:11:36   BJR
 * Changed def. of STPDataType.
 *
 *    Rev 1.8   Sep 09 1996 09:54:16   BJR
 * Added RemoveSubscription and StartInitAction.
 * Removed OriMMState STPWaitForAccessRigthsTermCfm. Changed def. of STPDataType.
 *
 *    Rev 1.7   Sep 02 1996 15:11:56   BJR
 * Moved external def. of TerminalCapability to PIWUAUX.H.
 *
 *    Rev 1.6   Sep 02 1996 10:14:00   BJR
 * Added MakeDefaultTpuiFromIpui.
 * Renamed state SRWaitForMacMeFtSysCfm to SRWaitForMacMeFtSysCfmInd.
 * Removed MakeEmcFromIpei.
 * Replaced PreservedBasicService with PreservedCcSetupPrim in OutDataType.
 * Alterations of CommenStartDataType, SRDataType and KADataType.
 * Added PowerUpWaitForEEReadDataCfm, IWUFindParks and SelectWaitForCfm to CommonStartStateType.
 * Added RfpiMatchPark.
 * OriMMData, DstMMData and CommonStartData are now allocated on the heap.
 * Added external TerminalCapability.
 *
 *    Rev 1.5   Aug 08 1996 12:50:54   BJR
 * Added OriMMState AFWaitForCalculation.
 *
 *    Rev 1.4   Aug 06 1996 17:56:32   BJR
 * Added SendOmSubsStatusInd.
 *
 *    Rev 1.3   Jul 23 1996 15:29:06   BJR
 * Added MakeEmcFromIpei.
 *
 *    Rev 1.2   Jul 18 1996 15:52:20   BJR
 * Adapted that TPUI and DCK no longer are stored in EEPROM. Introduced that <<Basic service>> can
 * be send in a CC_SETUP. Removed OurEmc (EMC part of IPEI is now used in stead).
 *
 *    Rev 1.1   Jun 24 1996 19:09:40   BJR
 * Finished.
 *
 *    Rev 1.0   Apr 16 1996 19:19:50   BJR
 * First revision.
 *
 ********************************************************************
 */

#ifndef P_IWU_H__
#define P_IWU_H__

#include "../../../nwk/include/ccprim.h"
#include "../../../nwk/include/mmprim.h"
#include "../../../../mac/driver/include/pp/eeutil.h"

#include "./piwuprim.h"

#define ORI_MM ( 0x00 | PD_MM )
#define DST_MM ( 0x80 | PD_MM )
#define NO_TIPD 0xFF

#define IPUI_N_LEN      9
#define TPUI_LEN        7
#define LAL_LEN         3
#define RFPI_LEN        9
#define AUTH_TYPE_LEN   5
#define RAND_LEN        10
#define RES_LEN         6
#define SERV_CLASS_LEN  3
#define ZAP_FIELD_LEN   3

#define LOC_REG_RETRY_TIMER      0
#define LOC_REG_RETRY_TIMER_VAL  3000   /* 30 sec.*/

#define NO_SEARCH_MODE_CHANGE_ORDERED 255

typedef enum
{
    PowerUpWaitForEEReadDataCfm,
    InitWaitForEEReadDataCfm,
    IWUReady,
    IWUFindParks,
    SelectWaitForParks,
    SelectWaitForCfm,
    AutoLoginFindRfpi
} CommonStartStateType;

typedef enum
{
    CCIdle,
    Active,
    WaitForReleaseCfm,
    WaitForReleaseCom,
    OutSetupWaitForEEReadDataCfm,
    WaitForSetupAckInd,
    WaitForCallProcInd,
    WaitForAlertInd,
    WaitForConnectInd,
    RelComWaitForEEReadDataCfm,
    IncSetupWaitForEEReadDataCfm,
    WaitForAlerting,
    WaitForConnect,
    WaitForConnectCfm,
    IdleWaitForEEReadDataCfm
} CCStateType;

typedef enum
{
    OriMMIdle,
    SRWaitForMacMeFtSysCfmInd,
    SRWaitForEEReadDataCfm,
    SRWaitForAccessRightsCfm,
    STPWaitForEEReadDataCfm,
    LRWaitForEEReadDataCfm,
    LRLUWaitForLocateCfm,
    LUWaitForMacMeFtSysCfm,
    LUWaitForEEReadDataCfm
} OriMMStateType;

typedef enum
{
    DstMMIdle,
    STFWaitForEEReadDataCfm,
    APWaitForEEReadDataCfm,
    APWaitForCalculation,
    APACWaitForEEReadDataCfm,
    APACWaitForCalculation,
    AUWaitForEEReadDataCfm,
    AUWaitForPromptUpiRes,
    AUWaitForCalculation,
    IDWaitForEEReadDataCfm,
    KAWaitForEEReadDataCfm,
    KAWaitForCalcRES1,
    KAWaitForAuthCfm,
    KAWaitForCalcRES2
} DstMMStateType;

typedef struct
{
    UByte EEReadDataCfmCount;
    EE_IpuiType Ipui;
    EE_ParkType Park;
    EE_IpeiType Ipei;
    UByte ParkCnt;
    CommonStartStateType ReturnState;
}
CommenStartDataType;

typedef struct
{
    CcSetupPrimType *PreservedCcSetupPrim;
}
OutDataType;

typedef struct
{
    MnccSetupIndType *PreservedMnccSetupInd;
}
IncDataType;

typedef struct
{
    OmSubsCreateReqType *PreservedOmSubsCreateReq;
    MMAccessRightsCfmType *PreservedMMAccessRightsCfm;
    FixedIdentityType *ParkPtr;
    U16Bits HigherLayerCap;
    UByte NewRfpi[MaxAriRpnOctets];
    EE_ParkType OldPark;
    EE_ParkType NewPark;
    EE_IpeiType Ipei;
}
SRDataType;

typedef struct
{
    EE_IpeiType Ipei;
}
STPDataType;

typedef struct
{
    U16Bits HigherLayerCap;
    UByte NewRfpi[MaxAriRpnOctets];
    EE_IpuiType Ipui;
    EE_LalType Lal;
    EE_ParkType Park;
    EE_RfpiType OldRfpi;
}
LRLUDataType;

typedef struct
{
    EE_IpeiType Ipei;
}
STFDataType;

typedef struct
{
    UByte IncUpc;                 /* Store in the format of octet 5 in <<AUTH-TYPE>> */
    UByte Rand_F[8];
    UByte Rs[8];
    EE_ZapFieldType ZapField;
    EE_ServiceClassType ServiceClass;
    EE_UakAcType Uak;
    UByte Res1[4];
}
APDataType;

typedef struct
{
    UByte IncUpc;                 /* Store in the format of octet 5 in <<AUTH-TYPE>> */
    UByte Rand_F[8];
    UByte Rs[8];
    EE_ZapFieldType ZapField;
    EE_ServiceClassType ServiceClass;
    EE_UakAcType Ac_K;
    UByte Res1[4];
}
APACDataType;

typedef struct
{
    UByte IncUpc;                 /* Store in the format of octet 5 in <<AUTH-TYPE>> */
    UByte Rand_F[8];
    UByte Rs[8];
    EE_ZapFieldType ZapField;
    EE_ServiceClassType ServiceClass;
    EE_UakAcType Uak_K;
    UByte Res1[4];
}
AUDataType;

typedef enum
{
    IDIpui,
    IDIpei,
    IDAri,
    IDAriRpn,
    IDPark
} IDGroupTypeType;

typedef struct
{
    IDGroupTypeType IDGroupType;
    union
    {
        EE_IpuiType Ipui;
        EE_IpeiType Ipei;
        struct
        {
            EE_RfpiType Rfpi;
            EE_ParkType Park;
        }
        RfpiPark;
        EE_RfpiType Rfpi;
        EE_ParkType Park;
    } Data;
}
IDDataType;

typedef struct
{
    UByte Rand[8];
    UByte Rs[8];
    EE_UakAcType Ac_K;
    UByte Res1[4];
    UByte CalcRes2[4];

    UByte Uak[16];
}
KADataType;

#define FIELD_FLAG_No 0x7F
#define FIELD_FLAG_AutoLogin 0x80

#define getFIELD_FLAG_No(FieldFlag)             (FieldFlag & FIELD_FLAG_No)
#define getFIELD_FLAG_AutoLogin(FieldFlag)      ((FieldFlag & FIELD_FLAG_AutoLogin) >> 7)

#define setFIELD_FLAG_No(FieldFlag, val)        (FieldFlag = (FieldFlag & ~FIELD_FLAG_No) | (val & FIELD_FLAG_No))
#define setFIELD_FLAG_AutoLogin(FieldFlag, val) (FieldFlag = (FieldFlag & ~FIELD_FLAG_AutoLogin) | ((val << 7) & FIELD_FLAG_AutoLogin))

#define FLAGS_DckPresent              0x01
#define FLAGS_LocRegOrdered           0x02
#define FLAGS_PassivAtLock            0x04
#define FLAGS_MacMeFtSysIndReceived   0x08
#define FLAGS_FixedRfpi               0x10

#define getFLAGS_DckPresent(Flags)            (Flags & FLAGS_DckPresent)
#define getFLAGS_LocRegOrdered(Flags)         ((Flags & FLAGS_LocRegOrdered) >> 1)
#define getFLAGS_PassivAtLock(Flags)          ((Flags & FLAGS_PassivAtLock) >> 2)
#define getFLAGS_MacMeFtSysIndReceived(Flags) ((Flags & FLAGS_MacMeFtSysIndReceived) >> 3)
#define getFLAGS_FixedRfpi(Flags)             ((Flags & FLAGS_FixedRfpi) >> 4)

#define setFLAGS_DckPresent(Flags, val)            (Flags = (Flags & ~FLAGS_DckPresent) | (val & FLAGS_DckPresent))
#define setFLAGS_LocRegOrdered(Flags, val)         (Flags = (Flags & ~FLAGS_LocRegOrdered) | ((val << 1) & FLAGS_LocRegOrdered))
#define setFLAGS_PassivAtLock(Flags, val)          (Flags = (Flags & ~FLAGS_PassivAtLock) | ((val << 2) & FLAGS_PassivAtLock))
#define setFLAGS_MacMeFtSysIndReceived(Flags, val) (Flags = (Flags & ~FLAGS_MacMeFtSysIndReceived) | ((val << 3) & FLAGS_MacMeFtSysIndReceived))
#define setFLAGS_FixedRfpi(Flags, val)             (Flags = (Flags & ~FLAGS_FixedRfpi) | ((val << 4) & FLAGS_FixedRfpi))

typedef struct
{
    CommonStartStateType CommonStartState;
    CCStateType CCState;
    OriMMStateType OriMMState;
    DstMMStateType DstMMState;
    union
    {
        UByte FieldFlag;
        UByte Combined;
    }
    SubsNo;
    UByte Status;
    UByte Tpui[MaxTpuiOctets];
    UByte Dck[MaxDckOctets];
    UByte CCTIPD;
    UByte CISSTIPD;
    UByte Flags;
    enum
    {
        JustPoweredUp,
        NewSubs,
        BackToNormal,
        NonOfTheAbove
    } LocRegReason;
    SearchModeType OrderedSearchModeChange;       /* Set to NO_SEARCH_MODE_CHANGE_ORDERED (255) if no search mode*/
    /* change is ordered*/
    UByte *SelectRfpiPtr;
    TimerType *AutoLoginTimer;
    TimerType *DurationTimer;
    EE_IpuiType CCIpui;
    EE_ParkType CCPark;
    union
    {
        IncDataType IncData;
        OutDataType OutData;
    } CCData;

    CommenStartDataType *CommonStartData; /*Not data belonging to a real MM procedure */
    union
    {
        SRDataType *SRData;
        STPDataType *STPData;
        LRLUDataType *LRLUData;
    } OriMMData;
    union
    {
        STFDataType *STFData;
        APDataType *APData;
        APACDataType *APACData;
        AUDataType *AUData;
        IDDataType *IDData;
        KADataType *KAData;
    } DstMMData;
}
IWUDataType;

extern IWUDataType IWUData;

void PutSignalBack(SignalType * Signal);

void SendOmSubsCreateReject(void);

void SendOmSubsRemoveReject(void);

void SendOmSubsStatusInd(void);

void GenerateRand(UByte * Rand);

void ConvAcToK(UByte * Ac, UByte * K);

void ConvUpiAndUakToK(UByte * Upi, UByte * Uak, UByte * K);

void MakeDefaultTpuiFromIpei(UByte * Tpui, UByte * Ipei);

void MakeDefaultIpuiFromIpei(IpuiType * Ipui, UByte * Ipei);

void MakeDefaultTpuiFromIpui(UByte * Tpui, UByte LenOfIdVal, UByte * IdValue);

Boolean RfpiMatchPark(UByte * Rfpi, UByte * Park, UByte Pli);

void RemoveSubscription(UByte * Ipei, Boolean DownloadNoParkToMac, int sessionID);

void StartInitAction(void);

void ServiceAutoLogin(void);

void StartDurationTimer(UByte TimeoutVal);

#endif /*not P_IWU_H__ */
