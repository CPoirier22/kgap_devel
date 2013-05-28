#ifndef _MAC_H__
#define _MAC_H__

#include "../../../hlkgap/dduos/include/dduos.h"
#include "../../../hlkgap/common/include/sformat.h"

#define MAC_ME_FT_SYSTEM_ind  0x1F
#define MAC_ME_FT_SYSTEM_cfm  0xF6

struct MacConReqStruct
{
    SignalType TheSignal;
    UByte ConnectionHandoverFlag;
};
typedef struct MacConReqStruct MacConReqType;

struct MacPageIndStruct
{
    SignalType TheSignal;
    UByte PageFieldLength;
    UByte LpAndCrcFlag;
};
typedef struct MacPageIndStruct MacPageIndType;

#define getMacPageIndTypeIE(signal) ((unsigned char*)signal + offsetof(MacPageIndType, LpAndCrcFlag) + sizeof(UByte))

struct MacEncEksReqStruct
{
    SignalType TheSignal;
    UByte EncryptionCommand;
};
typedef struct MacEncEksReqStruct MacEncEksReqType;

struct MacEncEksCfmStruct
{
    SignalType TheSignal;
    UByte EncryptionStatus;
};
typedef struct MacEncEksCfmStruct MacEncEksCfmType;

struct MacConCfmStruct
{
    SignalType TheSignal;
};
typedef struct MacConCfmStruct MacConCfmType;

struct MacMeConHandIndStruct
{
    SignalType TheSignal;
};
typedef struct MacMeConHandIndStruct MacMeConHandIndType;

typedef struct
{
    SignalType SignalHeader;
    UByte CtrlInfo;
    UByte Rfpi[MaxAriRpnOctets];
    U16Bits HigherLayerCap;
}
MacMeFtSystemIndType;

typedef struct
{
    SignalType SignalHeader;
    UByte CtrlInfo;
    UByte Rfpi[MaxAriRpnOctets];
    U16Bits HigherLayerCap;
}
MacMeFtSystemCfmType;

typedef struct
{
    SignalType SignalHeader;
    UByte CtrlInfo;
    PMIDType Pmid_Tpui;
    UByte Park[MaxParkOctets];
    UByte Pli;
}
MacMePtSystemReqType;

typedef struct
{
    SignalType  TheSignal;
    BYTE Length;
    WORD TPUI;
    BYTE Info[32];
}
LongBroadcastType;

typedef enum
{
    HLC_LocRegSupp =        0x0002,
    HLC_AccRightsReqSupp =  0x0800,
    HLC_GapPapSupported  =  0x0040
} HLC_SupportEnum;

extern void SendMacConReq(MCEIType MCEI, UByte HOVFlag, int sessionID);
extern void SendMacEncEksReq(SignalType * TheSignal, MCEIType MCEI, int sessionID);
extern void SendMacEncKeyReq(SignalType * TheSignal, MCEIType MCEI, int sessionID);
extern void SendMacCoDataReq(MCEIType MCEI, SignalType * SegmentSignal);
extern void SendMacDisReq(MCEIType MCEI, int sessionID);
extern void SendMacMeConUPlaneReq(MCEIType MCEI, UByte Direction, int sessionID);
extern void SendMacMeDisUPlaneReq(MCEIType MCEI, UByte Direction, int sessionID);
extern void SendMacMeFtSystemReq(int sessionID);
extern void SendMacMePtSystemReq(MacMePtSystemReqType * MacMePtSystemReq, int noPark, int sessionID);
extern void SendPpLockedInd(UByte Channel, Boolean InLock, int sessionID);

#endif /* _MAC_H__*/
