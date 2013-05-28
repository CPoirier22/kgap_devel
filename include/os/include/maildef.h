
#ifndef __MAILDEF_H

#define __MAILDEF_H

/******************************************************************************
* Project   : DECT                                                            *
* Module    : General Mail structure definition                               *
* Reference :                                                                 *
* Type      : Headerfile containing global mail structure definitions
* Function  :                                                                 *
* Systems   : Base,Handset                                                    *
* Comment   : Originates from GAP maildef.h, Feb 97.
*-----------------------------------------------------------------------------*
* Copyright (c) 1996 by RTX Research A/S.                                     *
* $Header:   K:/ph/srclib/os/variant/archive/h/MAILDEF.H_V   1.12.1.5.1.1   Nov 19 2003 10:00:44   on  $ *
*******************************************************************************/

#define SDU_SIZE      5


#include "mailprim.h"
#include "../../common/include/_stddef.h"

/* Public variables ***********************************************************/

#define MCEI_DEF  BYTE Mcei;
#define DLEI_DEF  BYTE Dlei;
#define CCEI_DEF  BYTE Ccei;

#if defined(_MERCURY_)
#define RPN_DEF   BYTE Rpn;
#define HSNO_DEF  BYTE HsNo;
#else
#define RPN_DEF
#define HSNO_DEF
#endif

#if defined(_D2_)
#define MAC_BASIC      0
#define MAC_ADVANCED   1

typedef struct
{
    BYTE bTail1_Ecn7654_Lbn3210;
    BYTE bTail2_BearerType76_ServiceType543_MaxLife210;
    BYTE bTail3_SlotType7654_Cf3_Spr210;
    BYTE bTail4_Spr76543210;
}
AttributesTtailType;

#define CONN_TYPE_DEF           BYTE ConnectionType;
#define ECN_DEF                 BYTE bEcn;
#define ATTRIBUTES_T_TAIL_DEF   AttributesTtailType AttributesTtail;

#define BASIC_SERVICE BYTE CallClassBasicServ;
#define RATE          BYTE Rate;
#define NEGOTIATION   BYTE Negotiation;
#define IWU_SERVICE   BYTE IwuService;
#else
#define CONN_TYPE_DEF
#define ECN_DEF
#define ATTRIBUTES_T_TAIL_DEF

#define BASIC_SERVICE
#define RATE
#define NEGOTIATION
#define IWU_SERVICE
#endif

#define USE_EVEN_SLOT     1
#define USE_ODD_SLOT      2
#define USE_EVEN_ODD_SLOT 3

typedef struct
{
    PrimitiveType Primitive;
    BYTE Mcei;
    BYTE CHovFlag;
    CONN_TYPE_DEF
}
_MacConReqType;
typedef struct
{
    PrimitiveType Primitive;
    BYTE Mcei;
    BYTE Pmid[3];
}
_MacConCfmType;


typedef struct
{
    PrimitiveType Primitive;
    BYTE Mcei;
    BYTE Pmid[3];
    BYTE CHovF;
    CONN_TYPE_DEF
    ECN_DEF
}
_MacConIndType;

typedef struct
{
    PrimitiveType Primitive;
    BYTE Mcei;
}
_MacConResType;

typedef struct
{
    PrimitiveType Primitive;
    BYTE Mcei;
    BYTE Sdu[SDU_SIZE];
}
_MacCoDataReqType;


typedef struct
{
    PrimitiveType Primitive;
    BYTE Mcei;
    BYTE Sdu[SDU_SIZE];
}
_MacCoDataIndType;


typedef struct
{
    PrimitiveType Primitive;
    BYTE Mcei;
}
_MacCoDtrIndType;


typedef struct
{
    PrimitiveType Primitive;
    BYTE Mcei;
}
_MacDisReqType;


typedef struct
{
    PrimitiveType Primitive;
    BYTE Mcei;
    BYTE Reason;
}
_MacDisIndType;


typedef struct
{
    PrimitiveType Primitive;
    BYTE Mcei;
}
_MacDisCfmType;


typedef struct
{
    PrimitiveType Primitive;
    BYTE PageFieldLength;
    BYTE LongPageFlag;
}
_MacPageReqHeaderType;


typedef struct
{
    _MacPageReqHeaderType Header;
    BYTE Sdu[3];
}
__MacPageReqType;


typedef struct
{
    PrimitiveType Primitive;
    BYTE Dummy;
    BYTE Rfpi[5];
    BYTE SyncCap[2];
}
__MacMeFtSystemType;

typedef struct
{
    PrimitiveType Primitive;
    BYTE PageFieldLength;
    BYTE LpAndCrcFlag;
}
__MacPageIndHeaderType;


typedef struct
{
    __MacPageIndHeaderType H;
    BYTE Sdu[3];
}
__MacPageIndType;


typedef struct
{
    PrimitiveType Primitive;
    BYTE Mcei;
    BYTE EncKey[8];
}
_MacEncKeyReqType;


typedef struct
{
    PrimitiveType Primitive;
    BYTE Mcei;
    BYTE Command;
}
_MacEncEksReqType;


typedef struct
{
    PrimitiveType Primitive;
    BYTE Mcei;
    BYTE Status;
}
_MacEncEksIndType;


typedef struct
{
    PrimitiveType Primitive;
    BYTE Mcei;
    BYTE Status;
}
_MacEncEksCfmType;


typedef struct
{
    PrimitiveType Primitive;
    BYTE Mcei;
}
_MacResDlcIndType;

typedef struct
{
    PrimitiveType Primitive;
    BYTE Mcei;
    BYTE Direction;
}
_MacMeConUplaneReqType;


typedef struct
{
    PrimitiveType Primitive;
    BYTE Mcei;
    BYTE Direction;
}
_MacMeDisUplaneReqType;

typedef struct
{
    PrimitiveType Primitive;
    BYTE Mcei;
}
_MacMeConHandIndType;

typedef struct
{
    PrimitiveType Primitive;
    BYTE CtrlInfo;
    BYTE Pmid[3];
    BYTE Park[5];
    BYTE Pli;
}
_MacMePtSystemReqType;

typedef struct
{
    PrimitiveType Primitive;
    RPN_DEF BYTE CtrlInfo;
    BYTE Rfpi[5];
    BYTE HLCapabilities[2];
}
_MacMeFtSystemIndType;

typedef struct
{
    PrimitiveType Primitive;
    RPN_DEF BYTE CtrlInfo;
    BYTE Rfpi[5];
    BYTE HLCapabilities[2];
}
_MacMeFtSystemCfmType;

typedef struct
{
    PrimitiveType Primitive;
    BYTE CtrlInfo;
}
_MacMeFtSystemReqType;

typedef struct
{
    PrimitiveType Primitive;
    BYTE Sari[5];
}
_MacMeSariIndType;

typedef struct
{
    PrimitiveType Primitive;
    BYTE Status;
}
_MacRfpStatusIndType;


typedef struct
{
    PrimitiveType Primitive;
    RPN_DEF
}
_CcfMeCdmIndType;


typedef struct
{
    PrimitiveType Primitive;
    RPN_DEF
}
_CcfMeCdvIndType;


typedef struct {

  PrimitiveType Primitive;
  RPN_DEF
  WORD CableDelay;
}
_CcfMeCdvResType;


typedef struct
{
    PrimitiveType Primitive;
    BYTE Mcei;
    BYTE Un;
}
_CcfMeUplaneReqType;


typedef struct
{
    PrimitiveType Primitive;
    RPN_DEF BYTE HLCapabilities[2];
    BYTE Rfpi[5];
}
_CcfMePreloadReqType;


typedef struct
{
    PrimitiveType Primitive;
    BYTE NotAccept;
}
_CcfMePreloadCfmType;


typedef struct
{
    PrimitiveType Primitive;
    RPN_DEF
}
_CcfMeMfnoIndType;


typedef struct
{
    PrimitiveType Primitive;
    RPN_DEF BYTE MultiFrameNo[3];
}
_CcfMeMfnoResType;

typedef struct
{
    PrimitiveType Primitive;
    RPN_DEF
}
_CcfMetestModeReqType;


typedef struct
{
    PrimitiveType Primitive;
    RPN_DEF BYTE Channel;
}
_MacMeDummyBearerIndType;

typedef struct
{
    PrimitiveType Primitive;
    RPN_DEF BYTE Channel;
    BYTE AcceptFlag;
}
_MacMeDummyBearerResType;


typedef enum
{
    SIG_LINK_DOWN,
    SIG_LINK_UP,
    SIG_LINK_PH_DOWN,
    SIG_LINK_PH_UP,
    SIG_LINK_DECT_SYNC_LOST              = 4,
    SIG_LINK_DECT_SYNC_UP                = 5,
    SIG_LINK_DECT_SYNC_UP_ALTERNATE      = 6,
    SIG_LINK_DECT_RADIO_BUSY             = 7,
    SIG_LINK_DECT_RADIO_NOT_BUSY         = 8,
    SIG_LINK_DECT_SYNC_UP_SELF           = 9
}LinkInfoStatusType;

typedef struct
{
    PrimitiveType Primitive;
    LinkInfoStatusType LinkInfoStatus;
	BYTE Rpn[3];
}
_LinkInfoType;

typedef struct
{
    BYTE MsgType;
}
SframeType;

typedef struct
{
    BYTE TaskID;
    BYTE EEmessageID;
    BYTE NoOfBytes;
    /*DWORD EEaddress;*/
    WORD EEaddress; /* preserve compatibility with Serio Service*/
}
EEPROMType;

typedef struct
{
    PrimitiveType Primitive;
}
NullMsgType;

typedef struct
{
    PrimitiveType Primitive;
    BYTE TimerId;
}
TimeOutMsgType;

typedef struct
{
    PrimitiveType Primitive;
}
InitTaskMsgType;


typedef struct
{
    PrimitiveType Primitive;
    BYTE Channel;
    BYTE Quality;
    BYTE RssiLevel;
    BYTE RPN;
    BYTE RssiLevelUcomp;
    BYTE AcrcSum;
    BYTE ZcrcSum;
    BYTE PtSlideSum;
    BYTE FtSlideSum;
    BYTE FtAcrcErr;
    BYTE FtBreject;
    BYTE FtSlideErr;
}
BearerQualityIndType;

typedef struct
{
    PrimitiveType Primitive;
    BYTE Channel;
    BYTE RssiLevel;
    BYTE Rfpi[5];
}
BearerScanIndType;

typedef struct
{
    PrimitiveType Primitive;
}
BearerScanReqType;

/* This struct MUST match the start of BearerReqType*/
/* since the send BROADCAST_CHAN_req is later casted to BearerReqType in hscsf.c*/
typedef struct
{
    PrimitiveType Primitive;
    BYTE Channel;
    BYTE AudioBuffer;  /* Dummy to match BearerReqType*/
    BYTE Rfpi[5];
}
BroadCastChanReqType;

typedef struct
{
    PrimitiveType Primitive;
    BYTE Channel;
}
BroadCastChanIndType;

typedef struct
{
    PrimitiveType Primitive;
    BYTE Channel;
}
ConferenceChanIndType;

typedef struct
{
    PrimitiveType Primitive;
    BYTE ScanningType;
}
FastRSSIScanEndType;

typedef struct
{
    PrimitiveType Primitive;
    BYTE Channel;
    BYTE AudioBuffer;
    BYTE Rfpi[5];
    BYTE Pmid[3];
    BYTE HOparm;
    BYTE RssiLevel;
    CONN_TYPE_DEF
    ATTRIBUTES_T_TAIL_DEF
}
BearerReqType;

typedef struct
{
    PrimitiveType Primitive;
    BYTE ConfChannel;
}
ConferenceBearerReqType;

typedef struct
{
    PrimitiveType Primitive;
    BYTE Channel;
}
BearerEncReqType;

typedef struct
{
    PrimitiveType Primitive;
    BYTE Channel;
}
BearerCfmType;

typedef struct
{
    PrimitiveType Primitive;
    BYTE Channel;
}
ConferenceBearerCfmType;

typedef struct
{
    PrimitiveType Primitive;
    BYTE Channel;
    BYTE Pmid[3];
    BYTE HOparm;
    CONN_TYPE_DEF
    ATTRIBUTES_T_TAIL_DEF
}
BearerIndType;


typedef struct
{
    PrimitiveType Primitive;
    BYTE Channel;
}
BearerReleaseReqType;

typedef struct
{
    PrimitiveType Primitive;
    BYTE Channel;
}
BearerReleaseCfmType;

typedef struct
{
    PrimitiveType Primitive;
    BYTE Channel;
    BYTE Cause;
}
BearerReleaseIndType;

typedef struct
{
    PrimitiveType Primitive;
    BYTE Channel;
}
BearerReConnReqType;

typedef struct
{
    PrimitiveType Primitive;
    BYTE Channel;
    BYTE Info;
}
BearerFailIndType;

typedef struct
{
    PrimitiveType Primitive;
    BYTE Channel;
    BYTE SegmentNr;
    BYTE Data[SDU_SIZE];
}
BearerDataReqType;

typedef struct
{
    PrimitiveType Primitive;
    BYTE Channel;
    BYTE Q2;
}
BearerDtrIndType;

typedef struct
{
    PrimitiveType Primitive;
    BYTE Channel;
    BYTE SegmentNr;
    BYTE Data[SDU_SIZE];
}
BearerDataIndType;


typedef struct
{
    PrimitiveType Primitive;
    BYTE Channel;
}
BearerEncEksReqType;


typedef struct
{
    PrimitiveType Primitive;
    BYTE Channel;
}
BearerEncEksIndType;

typedef struct
{
    PrimitiveType Primitive;
    BYTE Channel;
}
BearerEncEksCfmType;


typedef struct
{
    PrimitiveType Primitive;
    BYTE Channel;
    BYTE EncKey[8];
}
BearerEncKeyReqType;

typedef struct
{
    PrimitiveType Primitive;
    BYTE Channel;
    BYTE AudioBuffer;  /* Dummy to match BearerReqType*/
    BYTE Rfpi[5];
}
BearerSyncInfoReqType;

typedef struct
{
    PrimitiveType Primitive;
    BYTE Channel;
    BYTE Synchronized;
}
BearerSyncInfoCfmType;

typedef struct
{
    PrimitiveType Primitive;
    CCEI_DEF BYTE Size;
    SframeType Frame;
}
SframeReqType;

typedef struct
{
    PrimitiveType Primitive;
    CCEI_DEF BYTE Size;
    SframeType Frame;
}
SframeIndType;

typedef struct
{
    PrimitiveType Primitive;
    CCEI_DEF
}
LceReleaseReqType;

typedef struct
{
    PrimitiveType Primitive;
    BYTE Sdu[SDU_SIZE];
}
DlBroadcastReqType;

typedef struct
{
    PrimitiveType Primitive;
    BYTE Sdu[SDU_SIZE];
}
DlBroadcastIndType;


typedef struct
{
    PrimitiveType Primitive;
    CCEI_DEF HSNO_DEF
}
MnccReqType;

typedef struct
{
    PrimitiveType Primitive;
    CCEI_DEF HSNO_DEF
}
MnccIndType;

typedef struct
{
    PrimitiveType Primitive;
    CCEI_DEF BYTE Parm[1];
}
_MnccIndType;


typedef struct
{
    PrimitiveType Primitive;
    BYTE AlertInfo;
}
AlertBroadcastReqType;

typedef struct
{
    PrimitiveType Primitive;
    BYTE AlertInfo;
}
AlertBroadcastIndType;


/*----------------------------------------------*/
typedef struct
{
    PrimitiveType Primitive;
    BYTE NumOfBytes;
}
BusTxMailType;

typedef struct
{
    PrimitiveType Primitive;
    BYTE NumOfBytes;
    BYTE BusTxBytes[1];
}
_BusTxMailType;

typedef struct
{
    PrimitiveType Primitive;
    BYTE RxIntByte;
}
RxIntMailType;

typedef enum
{ /* RecordTypeType */
    DataRecord,                   /* 0x00*/
    EndOfFileRecord,              /* 0x01*/
    ExtendedSegmentAddressRecord, /* 0x02*/
    StartSEgmentAddressRecord,    /* 0x03*/
    ExtendedLinearAddressRecord,  /* 0x04*/
    StartLinearAddressRecord      /* 0x05*/
}
RecordTypeType;

typedef enum
{ /* CmdType */
    HPIC_Function,
    HPID_Function,
    Start_Addr_Function
}
CmdType;

typedef struct
{ /* DspLoadMailType */
    PrimitiveType   Primitive;
    BYTE            RecordMark;    /* Start mark; Always: ":" 0x3A */
    BYTE            RecordLength;  /* Length of data */
    BYTE            LoadMsbOffset; /* MSB offset describe where in RAM to place data */
    BYTE            LoadLsbOffset; /* LSB offset describe where in RAM to place data */
    RecordTypeType  RecordType;    /* Type of data */
}
DspLoadMailType;               /* Intel HEX format with a length and a primitive in front */

typedef struct
{ /* ReadDspDataMailType */
    PrimitiveType   Primitive;
    CmdType         Cmd;             /* Command */
    BYTE            StartMsbAddress; /* Address describe where in RAM to start read data */
    BYTE            StartLsbAddress; /* Address describe where in RAM to start read data */
    BYTE            NrOfAddress;     /* Address describe where in RAM to stop read data */
    BYTE            ExtraAddress;    /* Address describe where in RAM to stop read data */
}
ReadDspDataMailType;             /* Read Dsp data */

typedef struct
{ /* SetDspDataMailType */
    PrimitiveType   Primitive;
    CmdType         Cmd;             /* Command */
    BYTE            MsbAddress;      /* Address describe where in RAM to set data */
    BYTE            LsbAddress;      /* Address describe where in RAM to set data */
    BYTE            MsbData;         /* Data */
    BYTE            LsbData;         /* Data */
}
SetDspDataMailType;              /* Set Dsp data */

typedef struct
{ /* HpiMailType */
    PrimitiveType   Primitive;
    BYTE            Length;
    BYTE            Msg2Dsp[1];
}
HpiMailType;


typedef struct
{
    PrimitiveType Primitive;
    BYTE Activate;
    BYTE Conference;
    BYTE Channel;
}
ChangePPStatusType;

/*----------------------------------------------*/
typedef struct
{
    PrimitiveType Primitive;
    EEPROMType EEprom;
}
EEwriteReqType;

typedef struct
{
    PrimitiveType Primitive;
    EEPROMType EEprom;
    BYTE EEbuffer[1];
}
EEwriteReqBufferType;



typedef struct
{
    PrimitiveType Primitive;
    EEPROMType EEprom;
}
EEreadReqType;

typedef struct
{
    PrimitiveType Primitive;
    BYTE EEmessageID;
    BYTE NoOfBytes;
}
EEdataCfmType;

typedef struct
{
    PrimitiveType Primitive;
    BYTE EEmessageID;
    BYTE NoOfBytes;
    WORD EEaddress;
    BYTE EEbuffer[1];
}
EEdataCfmBufferType;

typedef struct
{
    PrimitiveType Primitive;
    BYTE EEmessageID;
    BYTE NoOfBytes;
    BYTE EEbuffer[1];
}
EETestCmdType;


typedef struct
{
    PrimitiveType Primitive;
    BYTE Channel;
    BYTE BufferNr;
}
BearerAudioReqType;

typedef struct
{
    PrimitiveType Primitive;
    MCEI_DEF BYTE BufferNr;
}
MacAudioReqType;

typedef struct
{
    PrimitiveType Primitive;
    BYTE Lid;
    BYTE Mcei;
    BYTE Connect;
}
AudioLineReqType;


typedef struct
{
    PrimitiveType Primitive;
    BYTE Lid;
    BYTE Pmid_2;
    BYTE Pmid_1;
    BYTE Connect;
}
AudioLineReqTypeFP;

typedef struct
{
    PrimitiveType Primitive;
    BYTE Size;
    BYTE Function;
    union
    {
        BYTE Data[1];
        WORD Instr[1];
    } Arg;
}
BmcLowLevelTestReqType;


typedef struct
{
    PrimitiveType Primitive;
    BYTE Function;
    BYTE Channel;
    BYTE Flags;
}
MacLayerTestIndType;



typedef struct
{
    PrimitiveType Primitive;
    BYTE Pli;
    BYTE Park[5];
    BYTE AC[4];
    WORD HsLocalNo;
}
MnccSubsCreateReqType;

typedef struct
{
    PrimitiveType Primitive;
}
MnccSubsRemoveReqType;


typedef struct
{
    PrimitiveType Primitive;
    BYTE Accept;
}
MnccSubsRemoveCfmType;

typedef struct
{
    PrimitiveType Primitive;
    BYTE Reject;
    WORD HsLocalNo;
}
MnccSubsCreateCfmType;

typedef struct
{
    PrimitiveType Primitive;
    BYTE SubsNo;
    BOOLEAN Status;
}
MnccSubsStatusIndType;


typedef struct
{
    PrimitiveType Primitive;
    BYTE Action;
}
MnccSearchRfpiReqType;


typedef struct
{
    PrimitiveType Primitive;
    BYTE Pli;
    BYTE Park[5];
    WORD HLCapabilities;
}
MnccSearchRfpiIndType;

typedef struct
{
    PrimitiveType Primitive;
    BYTE SubsNo;
}
MnccSubsSelectReqType;

typedef struct
{
    PrimitiveType Primitive;
}
MnccPromptUpiIndType;


typedef struct
{
    PrimitiveType Primitive;
    BYTE UPI[4];
}
MnccPromptUpiResType;


typedef struct
{
    PrimitiveType Primitive;
    BYTE CtrlInfo;
}
MacSearchReqType;

typedef struct
{
    PrimitiveType Primitive;
    BOOLEAN bWakeUp;
}
MacWakeUpReqType;


typedef struct
{
    PrimitiveType Primitive;
    BYTE Function;
}
TestCmdReqType;

typedef struct
{
    PrimitiveType Primitive;
    BYTE Function;
    BYTE Parm[34];
}
_TestCmdReqType;

#define BMC_INT_TYPE 		0
#define SET_LOCKED_CH 		1
#define WRONG_PP_CH 		2
#define Q1Q2error			3
#define CRCerror			4
#define MODIFY_SLOT         6
#define MT_HEAD_DEBUG       7

typedef struct
{
    PrimitiveType Primitive;
    BYTE Type;
    BYTE Data[1];
}
_MacDebugType;

typedef struct
{
    PrimitiveType Primitive;
    BYTE Length;
}
LongBroadCastReqType;

typedef struct
{
    PrimitiveType Primitive;
    BYTE RepCount;
    BYTE Length;
    BYTE Info[1];
}
_LongBroadCastReqType;

typedef struct
{
    PrimitiveType Primitive;
    BYTE Length;
    BYTE Slot;
    BYTE Header;
    WORD AddrSection;
    BYTE Discriminator;
    BYTE BitCount;
    BYTE Frame1;
    BYTE PropDiscriminator;
    BYTE Info[1];
}
LongBroadCastIndType;

typedef struct
{
    PrimitiveType Primitive;
    BYTE Length;
    BYTE Slot;
    BYTE Info[1];
}
_LongBroadCastIndType;

typedef struct
{
    PrimitiveType Primitive;
    BYTE Length;
}
MnclUnitDataReqType;

typedef struct
{
    PrimitiveType Primitive;
    BYTE Length;
    BYTE Info[1];
}
_MnclUnitDataReqType;

typedef struct
{

    PrimitiveType Primitive;
    BYTE Length;
}
MnclUnitDataIndType;


typedef struct
{

    PrimitiveType Primitive;
    BYTE Length;
    BYTE Info[1];
}
_MnclUnitDataIndType;

typedef struct
{
    BYTE TMailID;
    BYTE TaskID;
    BYTE NoOfBytes;
}
BiL3TMailType;


typedef struct
{
    BYTE Primitive;
    RPN_DEF WORD MailTime;
}
BiL3MailTestType;


typedef struct
{
    PrimitiveType Primitive;
    BYTE ActiveMode;
}
MacResetReqType;



typedef struct
{
    PrimitiveType Primitive;
    CCEI_DEF HSNO_DEF BYTE PresentFlag;
    BYTE Progress;
}
_MnccSetupAckType;


typedef struct
{
    PrimitiveType Primitive;
    CCEI_DEF HSNO_DEF BYTE PresentFlag;
    BYTE Progress;
}
_MnccAlertReqType;


typedef struct
{
    PrimitiveType Primitive;
    CCEI_DEF BYTE Reason;
}
_MnccReleaseReqType;

typedef struct
{
    PrimitiveType Primitive;
    CCEI_DEF BYTE Reason;
}
_MnccReleaseResType;


typedef struct
{
    PrimitiveType Primitive;
    CCEI_DEF BYTE Reason;
}
_MnccRejectReqType;

typedef struct
{
    PrimitiveType Primitive;
    CCEI_DEF RATE
    NEGOTIATION
    IWU_SERVICE
}
_MnccConnectReqType;

typedef struct
{
    PrimitiveType Primitive;
    CCEI_DEF RATE
    NEGOTIATION
    IWU_SERVICE
}
_MnccConnectIndType;


typedef struct
{
    PrimitiveType Primitive;
    CCEI_DEF BYTE Length;
}
_MnccMultiKeyPadReqType;

typedef struct
{
    PrimitiveType Primitive;
    CCEI_DEF BYTE Length;
    BYTE Data[1];
}
__MnccMultiKeyPadReqType;

typedef struct
{
    PrimitiveType Primitive;
    CCEI_DEF BYTE Length;
}
_MnccMultiKeyPadIndType;

typedef struct
{
    PrimitiveType Primitive;
    CCEI_DEF HSNO_DEF BYTE Length;
    BYTE Data[1];
}
__MnccMultiKeyPadIndType;

typedef struct
{
    PrimitiveType Primitive;
    CCEI_DEF HSNO_DEF BYTE Length;
}
_MnccIwuToIwuReqType;

typedef struct
{
    PrimitiveType Primitive;
    CCEI_DEF HSNO_DEF BYTE Length;
    BYTE Data[1];
}
__MnccIwuToIwuReqType;

typedef struct
{
    PrimitiveType Primitive;
    CCEI_DEF BYTE Parm;
}
_MnccSignalIndType;


typedef struct
{
    PrimitiveType Primitive;
    CCEI_DEF HSNO_DEF BYTE Parm;
}
_MnccSignalReqType;

typedef struct
{
    PrimitiveType Primitive;
    CCEI_DEF HSNO_DEF BYTE Length;
}
_MnccIwuToIwuIndType;


typedef struct
{
    PrimitiveType Primitive;
    CCEI_DEF HSNO_DEF BYTE Length;
    BYTE Data[1];
}
__MnccIwuToIwuIndType;


typedef struct
{
    PrimitiveType Primitive;
    WORD TaskFlags;               /* bit 15=timeout enable*/
}
BusTraceReqType;

typedef struct
{
    PrimitiveType Primitive;
    DWORD TaskFlags;              /* bit 31=timeout enable*/
    BYTE OptionLen;
    BYTE Options[1];
}
BusTraceExtReqType;


typedef struct
{
    PrimitiveType Primitive;
    CCEI_DEF BYTE Length;
}
_MnccMultiDisplayIndType;

typedef struct
{
    PrimitiveType Primitive;
    CCEI_DEF BYTE Length;
    BYTE Data[1];
}
__MnccMultiDisplayIndType;

typedef struct
{
    PrimitiveType Primitive;
    CCEI_DEF HSNO_DEF BYTE Length;
}
_MnccMultiDisplayReqType;

typedef struct
{
    PrimitiveType Primitive;
    CCEI_DEF HSNO_DEF BYTE Length;
    BYTE Data[1];
}
__MnccMultiDisplayReqType;


typedef struct
{
    PrimitiveType Primitive;
    BYTE HsNumber;
}
_MnccLocateIndType;

#ifdef _TAD_
typedef struct
{
    PrimitiveType Primitive;
    BYTE ModeCmd;
    BYTE Param;
}
TadModeReqType;


typedef struct
{
    PrimitiveType Primitive;
    BYTE ModeCmd;
    BYTE Param;
}
TadModeCfmType;


typedef struct
{
    PrimitiveType Primitive;
    BYTE ModeCmd;
}
TadStatusReqType;


typedef struct
{
    PrimitiveType Primitive;
    BYTE ModeCmd;
    BYTE Size;
    BYTE Parm[1];
}
TadStatusCfmType;

#endif


typedef struct
{
    PrimitiveType Primitive;
    BYTE Pm1;
    BYTE Pm2;
}
MsgPmType;



typedef struct
{
    PrimitiveType Primitive;
    BYTE ToneIndicator;
}
ToneReqType;



typedef struct
{
    PrimitiveType Primitive;
    BYTE Frequency;
    BYTE Length;
}
SineWawReqType;



typedef struct
{
    PrimitiveType Primitive;
    BYTE Key;
    BYTE Key_action;
}
KeyIndType;


typedef struct
{
    PrimitiveType Primitive;
    BYTE CtrlCmd;
    BYTE CtrlValue;
}
AudioCtrlReqType;

typedef struct
{
    PrimitiveType Primitive;
    BYTE CtrlCmd;
    BYTE CtrlValue;
}
HWinterfaceReqType;

typedef struct
{
    PrimitiveType Primitive;
    BYTE Gain;
    WORD Codec_LSR;
}
AudioCtrlCodecReqType;

typedef struct
{
    PrimitiveType Primitive;
    CCEI_DEF BYTE Operation;
    BYTE HsLocalNo;
    BYTE FpPassWord[2];
}
MnccRegistReqType;

typedef struct
{
    PrimitiveType Primitive;
    BYTE HsNumber;
    BYTE OwnHs;
}
MnccRegistIndType;

typedef struct
{
    PrimitiveType Primitive;
    BYTE HsNumber;
}
MnccDeRegistIndType;


typedef struct
{
    PrimitiveType Primitive;
    BYTE nCmd;                    /* command ID*/
    union
    {
        void *pData;
        BYTE nData[2];
        WORD wData;
    } Data;
}
TaskCmdReqType;


typedef struct
{
    PrimitiveType Primitive;
    BYTE Message;
}
TaskCmdCfmType;


typedef struct
{
    PrimitiveType Primitive;
    BYTE nType;                   /* <nType> 0 : set volume*/
    /*         1 : set ringer volume*/
    BYTE nVolume;                 /* <nVolume> 0 volume off*/
    /*           1-32 volume steps*/
    /*           0xff set volume to normal level*/
}
ToneVolumeReqType;            /* TONE_VOL_req*/

typedef struct
{
    PrimitiveType Primitive;
    BYTE Channel;
    BOOLEAN InLock;
}
PpLockedIndType;


typedef struct
{
    PrimitiveType Primitive;
    BYTE LineID;
    BYTE Hs;
    BYTE Digit;
}
DigitNalReqType;

/*

 As far as possible, use the _MnccIwuToIwuIndType or
 _MnccIwuToIwuIndDataType types instead.

*/

typedef struct
{
    PrimitiveType Primitive;
    CCEI_DEF BYTE nSize;          /* sizeof(parm)+1*/
    BYTE IWU_Code;
}
IwuToIwuMailType;


typedef struct
{
    PrimitiveType Primitive;
    CCEI_DEF BYTE nSize;          /* sizeof(parm)+1*/
    BYTE IWU_Code;
    BYTE Parm[1];
}
IwuToIwuMailParmType;

typedef struct
{
    PrimitiveType Primitive;
    BYTE TempChargeActive;
}
HookSwitchIndType;

typedef struct UttIndType_s
{
    PrimitiveType Primitive;
    BYTE command;
    WORD val1;
    WORD val2;
}
UttIndType;

typedef struct MmiEventIndType_s
{
    BYTE Primitive;
    BYTE event;
    BYTE subevent;
    WORD size;
}
MmiEventIndType;

typedef struct BatteryIndType_s
{
    BYTE Primitive;
    BYTE event;
    BYTE value;
}
BatteryIndType;

typedef struct
{
    PrimitiveType Primitive;
    BYTE nCmd;                    /* defined by display task*/
    BYTE nP1;                     /* parameter 1*/
    BYTE nP2;                     /* parameter 2*/
}
DisplayCmdReqType;

typedef struct
{
    PrimitiveType Primitive;
    BYTE HoReq;                   /* Request bearer og connection handover. Used by Service/deployment.*/
}
HandoverDebugReqType;

typedef struct
{
    PrimitiveType Primitive;
    BYTE           Pmid[3];
}
_ExtHOCom_indType;

typedef struct
{
    PrimitiveType Primitive;
    BYTE UsedSlot;
}
SelectSlotIndType;

typedef struct UserInputMailType_s
{
    PrimitiveType Primitive;
    BYTE noKeys;
}
UserInputMailType;


typedef struct JavaMailType_s
{
    PrimitiveType Primitive;
    BYTE subEvent;
}
JavaMailType;

typedef enum {
    SET_MEM_SIZE,
    GET_MEM_SIZE,
    TEST_MEM,
    CLEAR_MEM,
    SET_MEM,
    START_JVM,
    STOP_JVM,
    JLI_INITVM,
    JLI_RUNVM,
    JLI_STOPVM,
    JLI_RUNGC
} JVMMAILSubEvent;

typedef struct
{
    PrimitiveType Primitive;
    BYTE maxRetries;
    BYTE seqNoLow;
    BYTE seqNoHigh;
    BYTE timeLow;
    BYTE timeHigh;
    BYTE length;
}
SerialMessageType;

typedef struct
{
    PrimitiveType Primitive;
    BYTE idy;
    DWORD idx;
    BYTE fate;
    BYTE length;
}
MailMonitorType;

typedef struct
{
	PrimitiveType Primitive;
	BYTE type;
	BYTE serial_number[5];
	BYTE search_ari[5]; /*only used by pp*/
}
MacStartupIndType;

typedef struct
{
	PrimitiveType Primitive;
	BYTE index;
}
MacReadPPUserType;

typedef struct
{
	PrimitiveType Primitive;
	BYTE index;
	BYTE rfpi[6];
	BYTE access_level;
}
MacReadPPUserResType;

typedef struct
{
	PrimitiveType Primitive;
	BYTE selectedbase;         /*0xFE == auto, 0xFF == no selection*/
	BYTE selectedSumPoint;     /*0,1,2 == sum point, 0xFF == no selection*/
	BYTE volumeIndex;
	BYTE voxIndex;
	BYTE micIndex;
	BYTE subMode;/*not stored*/
	BYTE PPsettings;  /*ptt1_sum1; ptt2_sum2; ptt2_momentary; ptt2_plus_sum1; ptt2_RA2_PTT; ptt3_sum3; ptt3_momentary; ptt3_RA3_PTT;*/
	BYTE PPsettings2; /*ptt3_Local_RA; ptt3_plus_sum1;*/
	BYTE FPsettings; /*sum1_enabled; sum2_enabled; sum3_enabled; sum_locked; nosidetone_gm; ra2; ra3;*/
}
PeltorStateReadWriteType;

typedef struct
{
	PrimitiveType Primitive;
	BYTE sumpoint;
}
PeltorStartSumType;

typedef struct
{
	PrimitiveType Primitive;
	BYTE code;         /*0x00 == no trap, 0x01 == Exception, 0x02-0x04 == out of range*/
}
TrapWriteType;

typedef struct
{
	PrimitiveType Primitive;
}
PeltorReadStateReqType;


#define MAIL_MONITOR_HEADER_LENGTH offsetof(MailMonitorType, buffer)

/*----------- MailType -----------*/

typedef union
{
    PrimitiveType Primitive;
    SerialMessageType message;
    JavaMailType javamail;
    MailMonitorType mailMonitorMail;
    _LinkInfoType _Link_Info_Ind; /*ECT::MSE*/
    _MacConIndType _MacConInd;
    _MacConResType _MacConRes;
    _MacCoDataReqType _MacCoDataReq;
    _MacCoDataIndType _MacCoDataInd;
    _MacCoDtrIndType _MacCoDtrInd;
    _MacDisReqType _MacDisReq;
    _MacDisIndType _MacDisInd;

    __MacPageReqType __MacPageReq;
    __MacPageIndType __MacPageInd;
    __MacMeFtSystemType __MacMeFtSystem;

    _MacEncKeyReqType _MacEncKeyReq;
    _MacEncEksIndType _MacEncEksInd;
    _MacEncEksReqType _MacEncEksReq;
    _MacEncEksCfmType _MacEncEksCfm;
    _MacResDlcIndType _MacResDlcInd;
    _CcfMeUplaneReqType _CcfMeUplaneReq;
    _CcfMePreloadReqType _CcfMePreloadReq;
    _CcfMePreloadCfmType _CcfMePreloadCfm;
    _CcfMeMfnoIndType _CcfMeMfnoInd;
    _CcfMeMfnoResType _CcfMeMfnoRes;
    _CcfMetestModeReqType _CcfMetestModeReq;
    _MacConReqType _MacConReq;
    _MacConCfmType _MacConCfm;
    _MacDisCfmType _MacDisCfm;
    _MacMeConUplaneReqType _MacMeConUplaneReq;
    _MacMeDisUplaneReqType _MacMeDisUplaneReq;
    _MacMeConHandIndType _MacMeConHandInd;
    _MacMeFtSystemIndType _MacMeFtSystemInd;
    _MacMeFtSystemCfmType _MacMeFtSystemCfm;
    _MacMeFtSystemReqType _MacMeFtSystemReq;
    _MacMePtSystemReqType _MacMePtSystemReq;
    _MacMeDummyBearerIndType _MacMeDummyBearerInd;
    _MacMeDummyBearerResType _MacMeDummyBearerRes;
    _MacMeSariIndType _MacMeSariInd;
    _MacRfpStatusIndType _MacRfpStatusInd;

    NullMsgType NullMsg;
    TimeOutMsgType TimeOutMsg;
    InitTaskMsgType InitTaskMsg;

    MsgPmType MsgPm;
    PpLockedIndType PpLockedInd;
    BearerQualityIndType BearerQualityInd;
    BearerScanIndType BearerScanInd;
    BearerScanReqType BearerScanReq;
    BroadCastChanReqType BroadCastChanReq;
    BroadCastChanIndType BroadCastChanInd;
    ConferenceChanIndType ConferenceChanInd;
    FastRSSIScanEndType FastRSSIScanEnd;
    BearerReqType BearerReq;
    ConferenceBearerReqType ConferenceBearerReq;
    BearerEncReqType BearerEncReq;
    BearerCfmType BearerCfm;
    ConferenceBearerCfmType ConferenceBearerCfm;
    BearerIndType BearerInd;
    BearerReleaseReqType BearerReleaseReq;
    BearerReleaseCfmType BearerReleaseCfm;
    BearerReleaseIndType BearerReleaseInd;
    BearerReConnReqType BearerReConnReq;
    BearerFailIndType BearerFailInd;
    BearerDataReqType BearerDataReq;
    BearerDtrIndType BearerDtrInd;
    BearerDataIndType BearerDataInd;
    BearerEncEksReqType BearerEncEksReq;
    BearerEncEksCfmType BearerEncEksCfm;
    BearerEncEksIndType BearerEncEksInd;
    BearerEncKeyReqType BearerEncKeyReq;
    BearerSyncInfoReqType BearerSyncInfoReq;
    BearerSyncInfoCfmType BearerSyncInfoCfm;
    SframeReqType SframeReq;
    SframeIndType SframeInd;
    LceReleaseReqType LceReleaseReq;
    DlBroadcastReqType DlBroadcastReq;
    DlBroadcastIndType DlBroadcastInd;
    MnccReqType MnccReq;
    _MnccIndType MnccInd;
    AlertBroadcastReqType AlertBroadcastReq;
    AlertBroadcastIndType AlertBroadcastInd;
    _BusTxMailType BusTxMail;
    RxIntMailType RxIntMail;
    EEwriteReqBufferType EEwriteReq;
    EEreadReqType EEreadReq;
    EEdataCfmBufferType EEdataCfm;

    BiL3TMailType BiL3TMail;
    BiL3MailTestType BiL3MailTest;

    BearerAudioReqType BearerAudioReq;
    MacAudioReqType MacAudioReq;
    AudioLineReqType AudioLineReq;
    AudioLineReqTypeFP AudioLineReqFP;
    ToneReqType ToneReq;
    SineWawReqType SineWawReq;
    KeyIndType KeyInd;
    BmcLowLevelTestReqType BmcLowLevelTestReq;
    MacLayerTestIndType MacLayerTestInd;
    AudioCtrlReqType AudioCtrlReq;
    AudioCtrlCodecReqType AudioCtrlCodecReq;
    HWinterfaceReqType HWinterfaceReq;
    MnccSubsCreateReqType MnccSubsCreateReq;
    MnccSubsCreateCfmType MnccSubsCreateCfm;
    MnccSubsRemoveReqType MnccSubsRemoveReq;
    MnccSubsRemoveCfmType MnccSubsRemoveCfm;
    MnccSearchRfpiReqType MnccSearchRfpiReq;
    MnccSearchRfpiIndType MnccSearchRfpiInd;
    MnccSubsSelectReqType MnccSubsSelect;
    MnccPromptUpiIndType MnccPromptUpiInd;
    MnccPromptUpiResType MnccPromptUpiRes;
    MnccSubsStatusIndType MnccSubsStatusInd;
    MnccRegistIndType MnccRegistsInd;
    MnccDeRegistIndType MnccDeRegistsInd;
    MacSearchReqType MacSearchReq;
    MacWakeUpReqType MacWakeUpReq;
    __MnccMultiKeyPadIndType MnccMultiKeyPadInd;
    __MnccMultiKeyPadReqType MnccMultiKeyPadReq;
    __MnccIwuToIwuIndType MnccIwuToIwuInd;
    __MnccIwuToIwuReqType MnccIwuToIwuReq;
    _MnccConnectReqType MnccConnectReq;
    _MnccConnectIndType MnccConnectInd;
    _MnccSignalIndType MnccSignalInd;
    _MnccSignalReqType MnccSignalReq;
    _MnccSetupAckType MnccSetupAck;
    _MnccAlertReqType MnccAlertReq;
    _MnccReleaseReqType MnccReleaseReq;
    _MnccReleaseResType MnccReleaseRes;
    _MnccRejectReqType MnccRejectReq;
    __MnccMultiDisplayIndType MnccMultiDisplayInd;
    __MnccMultiDisplayReqType MnccMultiDisplayReq;
    _MnccLocateIndType MnccLocateInd;
    _TestCmdReqType TestCmdReq;
    _MacDebugType _MacDebug;
    _LongBroadCastReqType LongBroadCastReq;
    _LongBroadCastIndType _LongBroadCastInd;
    LongBroadCastIndType LongBroadCastInd;
    _MnclUnitDataReqType MnclUnitDataReq;
    _MnclUnitDataIndType MnclUnitDataInd;
    MacResetReqType MacResetReq;

    TaskCmdReqType TaskCmdReq;
    TaskCmdCfmType TaskCmdCfm;
    ToneVolumeReqType ToneVolumeReq;
/*    RingReqType RingReq;*/
    DigitNalReqType DigitNalReq;

    IwuToIwuMailParmType IwuToIwuMail;
    BusTraceReqType BusTraceReq;
    BusTraceExtReqType BusTraceExtReq;

    HookSwitchIndType HookSwitchInd;
    SelectSlotIndType SelectSlotInd;

#ifdef _TAD_
    TadModeReqType TadModeReq;
    TadModeCfmType TadModeCfm;
    TadStatusReqType TadStatusReq;
    TadStatusCfmType TadStatusCfm;
#endif
    DisplayCmdReqType DisplayCmdReq;
    HandoverDebugReqType HandoverDebugReq;
    UttIndType UttInd;
    MmiEventIndType MmiEventInd;
    BatteryIndType BatteryInd;
    HpiMailType HpiMail;
    DspLoadMailType DspLoadMail;
    ReadDspDataMailType ReadDspDataMail;
    SetDspDataMailType SetDspDataMail;
    ChangePPStatusType ChangePPStatus;
    MacStartupIndType MacStartupInd;
    MacReadPPUserType MacReadPPUser;
    MacReadPPUserResType MacReadPPUserRes;
    PeltorReadStateReqType PeltorReadStateReq;
	PeltorStateReadWriteType PeltorStateReadWrite;
	TrapWriteType TrapWrite;
	PeltorStartSumType PeltorStartSum;
} MailType;
#endif
