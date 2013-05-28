/*
 ********************************************************************
 *
 * Module: gimprim.h
 *
 * Config-item: ?
 *
 * Contents: GIM (Generic Interface Message) primitives.
 *
 * Author:    Kirk telecom / BJR.
 *
 * Copyright Kirk Telecom A/S. All rights reserved.
 * Definition of Events and SubEvent moved from COMM_ESC.H with some smale changes.
 * Added NIF System Events, NIF Call Control Events and NIC Management Events.
 ********************************************************************
 */

#ifndef GIMPRIM_H__
#define GIMPRIM_H__

#include "../../dduos/include/dduos.h"

/****************************************************************************/



#define GIM_MSG_req 0x00
#define GIM_MSG_ind 0x02
#define GIM_incoming_MSG 0x03


/* New defines for use to NIC and LID */
#define OTHER_TYPE_MASK 0xE0 /* 1110 0000 */



typedef enum
{
    SioPortType,
    NifPortType
} PortTypeType;




typedef UByte PortNoType;




#define TransactionTagNil 0xFFFF

typedef U16Bits TransactionTagType;



typedef enum
{
    NoUPlaneEndpoint  = 0x00,
    UChUPlaneEndpoint = 0x01
} UPlaneEndpointType;



/* MessageID */
typedef struct
{
    UByte OrgAddress[4];
    UByte OrgEvent;
    UByte OrgSubEvent;
    ProcessIdType OrgProcessID;
    ProcessIdType OrgOriginatorProcess;
    U16Bits PPID;
}
MessageIDType;


typedef struct
{
    SignalType  SignalHeader;  /* Addess field of signal header contains PortType, PortNo and*/
    /* TransactionTag as follows:*/
    /* Address[0]: Least significant byte of TransactionTag*/
    /* Address[1]: Most  significant byte of TransactionTag*/
    /* Address[2]: Bit 0 to 4: Full PortNo*/
    /*             Bit 6: CPN (CPN Placement I)*/
    /* Address[3]: PortType*/
    ProcessIdType OriginatorProcess;
    unsigned char Event;
    unsigned char SubEvent;
    unsigned char Length;
}
GimDataReqType;

#define getGimDataReqTypeIE(signal) ((unsigned char*)signal + offsetof(GimDataReqType, Length) + sizeof(unsigned char))

typedef struct
{
    SignalType  SignalHeader;  /* Addess field of signal header contains PortType, PortNo and*/
    /* TransactionTag as follows:*/
    /* Address[0]: Least significant byte of TransactionTag*/
    /* Address[1]: Most  significant byte of TransactionTag*/
    /* Address[2]: Bit 0 to 4: Full PortNo*/
    /*             Bit 6: CPN (CPN Placement I)*/
    /* Address[3]: PortType*/
    ProcessIdType OriginatorProcess;
    unsigned char Event;
    unsigned char SubEvent;
    unsigned char Length;
}
GimDataIndType;

#define getGimDataIndTypeIE(signal) ((unsigned char*)signal + offsetof(GimDataIndType, Length) + sizeof(unsigned char))

typedef struct
{
    unsigned char Event;
    unsigned char Subevent;
    unsigned char Length;
    unsigned char InfoElementOffset ;
    unsigned char LocalNumber;
}
NICHandoverReqType;

typedef struct
{
    unsigned char Event;
    unsigned char Subevent;
    unsigned char Length;
    unsigned char InfoElementOffset;
    unsigned char LocalNumber[12];
    unsigned char HO_data_len;
}
NICHandoverCfmType;

typedef struct             /* This structure type is used for the header of a Normalized GIM*/
{                          /* message, i.e. the format is the same whether an extended header was*/
    unsigned char Event;    /* used or not*/
    unsigned char SubEvent;
    unsigned char Length;
}
NormGimMsgType;

typedef struct
{
    SignalType  SignalHeader;  /* Addess field of signal header contains PortType, PortNo and*/
    /* TransactionTag as follows:*/
    /* Address[0]: Least significant byte of TransactionTag*/
    /* Address[1]: Most  significant byte of TransactionTag*/
    /* Address[2]: Bit 0 to 4: Full PortNo*/
    /*             Bit 6: CPN (CPN Placement I)*/
    /* Address[3]: PortType*/
    ProcessIdType OriginatorProcess;
    unsigned char Event;       /* used or not*/
    unsigned char SubEvent;
    unsigned char Length;
    unsigned char MessageID[sizeof(MessageIDType)];
    unsigned long StartAddress;
    unsigned short LengthOfAreaToFill;
    unsigned char Fill;
}
NICEEpromFillType;

typedef struct
{
    SignalType  SignalHeader;  /* Addess field of signal header contains PortType, PortNo and*/
    /* TransactionTag as follows:*/
    /* Address[0]: Least significant byte of TransactionTag*/
    /* Address[1]: Most  significant byte of TransactionTag*/
    /* Address[2]: Bit 0 to 4: Full PortNo*/
    /*             Bit 6: CPN (CPN Placement I)*/
    /* Address[3]: PortType*/
    ProcessIdType OriginatorProcess;
    unsigned char Event;
    unsigned char SubEvent;
    unsigned char Length;
    unsigned char MessageID[sizeof(MessageIDType)];
    unsigned long StartAddress; /* 4 octets*/
    unsigned short LengthOfData;
}
NICEEpromWriteIndType;

typedef struct
{
    SignalType  SignalHeader;  /* Addess field of signal header contains PortType, PortNo and*/
    /* TransactionTag as follows:*/
    /* Address[0]: Least significant byte of TransactionTag*/
    /* Address[1]: Most  significant byte of TransactionTag*/
    /* Address[2]: Bit 0 to 4: Full PortNo*/
    /*             Bit 6: CPN (CPN Placement I)*/
    /* Address[3]: PortType*/
    ProcessIdType OriginatorProcess;
    unsigned char Event;
    unsigned char SubEvent;
    unsigned char Length;
    unsigned char MessageID[sizeof(MessageIDType)];
    unsigned char Response;
}
NICEEpromWriteResType;

typedef struct
{
    SignalType  SignalHeader;  /* Addess field of signal header contains PortType, PortNo and*/
    /* TransactionTag as follows:*/
    /* Address[0]: Least significant byte of TransactionTag*/
    /* Address[1]: Most  significant byte of TransactionTag*/
    /* Address[2]: Bit 0 to 4: Full PortNo*/
    /*             Bit 6: CPN (CPN Placement I)*/
    /* Address[3]: PortType*/
    ProcessIdType OriginatorProcess;
    unsigned char Event;       /* used or not*/
    unsigned char SubEvent;
    unsigned char Length;
    unsigned char MessageID[sizeof(MessageIDType)];
    unsigned long StartAddress;
    unsigned short LengthOfData;
}
NICEEpromReadIndType;

typedef struct
{
    SignalType  SignalHeader;  /* Addess field of signal header contains PortType, PortNo and*/
    /* TransactionTag as follows:*/
    /* Address[0]: Least significant byte of TransactionTag*/
    /* Address[1]: Most  significant byte of TransactionTag*/
    /* Address[2]: Bit 0 to 4: Full PortNo*/
    /*             Bit 6: CPN (CPN Placement I)*/
    /* Address[3]: PortType*/
    ProcessIdType OriginatorProcess;
    unsigned char Event;       /* used or not*/
    unsigned char SubEvent;
    unsigned char Length;
    unsigned char MessageID[sizeof(MessageIDType)];
    unsigned char Response;
}
NICEEpromReadResType;

typedef struct
{
    SignalType  SignalHeader;  /* Addess field of signal header contains PortType, PortNo and*/
    /* TransactionTag as follows:*/
    /* Address[0]: Least significant byte of TransactionTag*/
    /* Address[1]: Most  significant byte of TransactionTag*/
    /* Address[2]: Bit 0 to 4: Full PortNo*/
    /*             Bit 6: CPN (CPN Placement I)*/
    /* Address[3]: PortType*/
}
RecGIMMessageType;

struct GIMEventPtrStructure
{
    EventType      Event;
    SubEventType     SubEvent;
    UByte        SignalLength;
};
typedef struct GIMEventPtrStructure GIMEventPtrType;

#define getGIMEventPtrTypeIE(signal) ((unsigned char*)signal + offsetof(GIMEventPtrType, SignalLength) + sizeof(UByte))

typedef enum
{
    ControlEvent    = 0x20,
    MsfEvent      = 0x21,
    UserDataEvent    = 0x22,
#ifndef IP_600
    IwuDataEvent    = 0x23,
#endif
    SystemOptionsEvent  = 0x24,
    StatusEvent    = 0x25,
#ifndef IP_600
    IwuCallControlEvent  = 0x26,
#endif
    DiagnosticEvent      = 0x27,
    RFPManagementEvent   = 0x28,
#ifndef IP_600
    PhoneBookEvent       = 0x29,
#endif
    NIFSystemEvent       = 0x2A,
    NIFCallControlEvent  = 0x2B,
    NICManagementEvent   = 0x2C,
    NICUserDataEvent     = 0x2D,
    NIFUtilityEvent      = 0x2E,
    NICHandOverEvent     = 0x40,
    NIFMailTraceEvent    = 0x50
} GimEventType;

typedef enum
{
    MessageSegment = 0x00
} ProtocolEventType;

typedef enum
{



    QuitSlaveCmdModeReq     = 0x26,

    CfmOnIlLegalRequest     = 0x49, /* I */

    CfmOnUnKnownRequest     = 0x55, /* U */
    DefaultModeEnteredReq = 0x56  /* V */
} ControlEventType;

typedef enum
{
    MsfSetupReq   = 0x20,
    MsfDispReq   = 0x21,
    MsfConRes   = 0x22,
    MsfRelReq   = 0x23,
    MsfSetupInd   = 0x24,
    MsfKeypadInd  = 0x25,
    MsfRelInd   = 0x26,
    MsfConCfm   = 0x27,
    PPLoadSetupReq  = 0x28,
    PPLoadSetupCfm  = 0x29,
    PPLoadDataReq  = 0x2A,
    PPLoadDataCfm  = 0x2B,
    PPLoadRelReq  = 0x2C,
    PPLoadRelInd  = 0x2D,


    MsfOutgMessageInd = 0x30,
    PPStatusInd       = 0x38,
    PPStatusReq     = 0x39

} MsfEventType;

typedef enum
{

























    SoftKeyPasswordReq = 0x44,
    PINCodeStatusReq  = 0x45,
    PINCodeStatusCfm  = 0x46,
    NumberAnalyseReq     = 0x50,
    NumberAnalyseCfm     = 0x51
} UserDataEventType;

typedef enum
{
    NumberNotFound    = 0x00,
    MoreDigitsNeeded  = 0x01,
    NumberComplete    = 0x02
} NumberAnalyseReponseType;

typedef enum
{
    SubscrAllowWriteReq    = 0x20,










    SystemConfRestoreReq    = 0x2B,


    SystemRestartReq     = 0x31,
    SystemInformationReadReq  = 0x32,
    SystemInformationReadCfm  = 0x33,

    ChangePassWordReq             = 0x3A,
    ChangePassWordCfm             = 0x3B,

    SubscrAllowReadReq            = 0x3E,
    SubscrAllowReadCfm            = 0x3F,


    NVMBackupReq                  = 0x42,
    NVMBackupInd                  = 0x43,
    NVMBackupRes                  = 0x44,
    SecurityConfigRWReq           = 0x4A,
    SecurityConfigRWCfm           = 0x4B,
    CallBlockRWReq                = 0x4C,
    CallBlockRWCfm                = 0x4D,

    BearerModeReadReq       = 0x50,
    BearerModeReadCfm       = 0x51,
    BearerModeWriteReq    = 0x52,
    BearerModeWriteCfm            = 0x53,
    ReadNVMRrq                    = 0x70,
    ReadNVMCfm                    = 0x71,
    WriteNVMRrq                   = 0x72,
    WriteNVMCfm                   = 0x73,
    CipheringRWReq                = 0x74,
    CipheringRWCfm                = 0x75,
    UserDefaultReq                = 0x76,
    UserDefaultCfm                = 0x77,
    ProgramAriReq                 = 0x78,
    ProgramAriCfm                = 0x79,
    ClearNVMWriteReq              = 0x7A,
    ClearNVMWriteCfm             = 0x7B,
    ReadSyncParReq               = 0x7C,
    ReadSyncParCfm               = 0x7D,
    WriteSyncParReq               = 0x7E,
    WriteSyncParCfm               = 0x7F
} SystemOptionsEventType;

typedef enum
{
    StatusLevelReadReq = 0x20,
    StatusLevelReadCfm = 0x21,
    StatusLevelWriteReq = 0x22,
    StatusLevelWriteCfm = 0x23,
    StatusMessageInd  = 0x24,

    TraceLevelWriteReq = 0x50,
    TraceLevelWriteCfm = 0x51,
    StartLogWriteReq   = 0x52,
    StartLogWriteCfm   = 0x53,
    StopLogWriteReq     = 0x54,
    StopLogWriteCfm     = 0x55,
    StatusLogWriteReq   = 0x56,
    StatusLogWriteCfm   = 0x57,
    LogDumpWriteReq     = 0x58,
    LogDumpWriteCfm     = 0x59,
    LogDumpWriteP1Cfm   = 0x5A,
    LogDumpWrite1Req    = 0x5B,
    LogDumpWrite1Cfm    = 0x5C
}StatusEventType;

typedef enum
{
    DiagnosticSetUpReq               = 0x20,
    DiagnosticSetUpCfm               = 0x21,
    DiagnosticStopInd                = 0x22,
    DiagnosticReadOutInd             = 0x23,
    DiagnosticCallStatisticCfm       = 0x24,
    DiagnosticCallStatisticReq       = 0x25,
    DiagnosticVariableStatusReq      = 0x26,
    DiagnosticVariableStatusCfm      = 0x27,
    DiagnosticUserLogStopReq         = 0x28,
    DiagnosticUserLogStopCfm         = 0x29,
    DiagnosticGetCCFPDataReq         = 0x30,
    DiagnosticResetCountersReq       = 0x32,
    DiagnosticResetCountersCfm       = 0x33
}DiagnosticEventType;

typedef enum
{
    AntennaDiversityReadReq          = 0x30,
    AntennaDiversityReadCfm          = 0x31,
    AntennaDiversityWriteReq        = 0x32,
    AntennaDiversityWriteCfm        = 0x33,
    RestartRFReq                = 0x34,
    RestartRFCfm                = 0x35,
    ContRxReq                   = 0x36,
    ContRxCfm                   = 0x37,
    ReadQuadtuneReq               = 0x38,
    ReadQuadtuneCfm               = 0x39,
    WriteQuadtuneReq             = 0x3A,
    WriteQuadtuneCfm             = 0x3B,
    ContTxReq                   = 0x3C,
    ContTxCfm                   = 0x3D,
    ReadModulationReq              = 0x3E,
    ReadModulationCfm             = 0x3F,
    WriteModulationReq            = 0x40,
    WriteModulationCfm            = 0x41,
    ReadClockReq                = 0x42,
    ReadClockCfm                 = 0x43,
    WriteClockReq                = 0x44,
    WriteClockCfm                = 0x45,
    ReadTestmodeReq               = 0x46,
    ReadTestmodeCfm               = 0x47,
    WriteTestmodeReq             = 0x48,
    WriteTestmodeCfm              = 0x49,
    ReadRSSIReq                  = 0x4A,
    ReadRSSICfm                 = 0x4B,
    ReadAVd2Req                  = 0x4C,
    ReadAVd2Cfm                  = 0x4D,
    WriteAVd2Req                = 0x4E,
    WriteAVd2Cfm                 = 0x4F,
    WriteRedLEDReq               = 0x50,
    WriteRedLEDCfm                = 0x51,
    WriteGreenLEDReq             = 0x52,
    WriteGreenLEDCfm              = 0x53,
    ADPCMLoopReq                 = 0x54,
    ADPCMLoopCfm                  = 0x55,
    IncSyncReq                   = 0x56,
    IncSyncCfm                    = 0x57,
    DecSyncReq                       = 0x58,
    HeapStatusReq                 = 0x59,
    HeapStatusCfm                  = 0x5A,
    ReadMemReq                       = 0x5B,
    ReadMemCfm                       = 0x5C,
    LinkInfoInd                      = 0x5D,
    WriteSyncOnlyReq                 = 0x5e,
    WriteSyncOnlyCfm                 = 0x5f,
    OtherBasesReq                    = 0x60,
    OtherBasesCfm                    = 0x61,
    SetSecurityLevelReq              = 0x62,
    SetSecurityLevelCfm              = 0x63,
    GetResetTraceReq                 = 0x64,
    GetResetTraceCfm                 = 0x65,
    GenerelPurposeReq                = 0x66,
    GenerelPurposeCfm                = 0x67
}RfpManagementEventType;

#ifndef IP_600
typedef enum
{
    TBWriteDataReq     = 0x20,
    TBWriteDataCfm       = 0x21,
    TBReadDataReq        = 0x22,
    TBReadDataInd       = 0x23,
    TBClearDataReq       = 0x24,
    TBClearDataCfm       = 0x25
} PhoneBookEventType;
#endif
typedef enum
{
    NIFStartupReq     = 0x20,
    NIFStartupCfm     = 0x21,
    NIFUChAllocateInd = 0x22,
    NIFUChAllocateRes = 0x23,
    NIFProceedInd     = 0x24,
    NIFLoadCodeInd    = 0x25,
    NifInterfacePingInd = 0x28,
    NifInterfacePingRes = 0x29
} NIFSystemEventType;

typedef enum
{
    NIFCCSetupReq        = 0x20,
    NIFCCSetupInd        = 0x21,
    NIFCCSetupAckReq     = 0x22,
    NIFCCInfoReq         = 0x23,
    NIFCCInfoInd         = 0x24,
    NIFCCCallProcReq     = 0x25,
    NIFCCAlertingReq     = 0x26,
    NIFCCAlertingInd     = 0x27,
    NIFCCConnectReq      = 0x28,
    NIFCCConnectInd      = 0x29,
    NIFCCConnectAckReq   = 0x2A,
    NIFCCReleaseReq      = 0x2B,
    NIFCCReleaseInd      = 0x2C,
    NIFCCReleaseComReq   = 0x2D,
    NIFCCReleaseComInd   = 0x2E,
    NIFCCExtHOComInd     = 0x2F,
    NIFCCFacilityReq     = 0x30
} NIFCallControlEventType;

typedef enum
{
    NICHandoverReq       = 0x20,
    NICHandoverCfm       = 0x21
}NICHandOverEventType;

typedef enum
{
    NICInfoReq        = 0x20,
    NICInfoCfm        = 0x21,
    NICLoadCodeReq    = 0x22,
    NICEEpromWriteReq = 0x50,
    NICEEpromWriteCfm = 0x51,
    NICEEpromFillReq = 0x52,
    NICEEpromFillCfm = 0x53,
    NICEEpromReadReq = 0x54,
    NICEEpromReadCfm = 0x55
} NICManagementEventType;

typedef enum
{
    NicCreateUserDatReq           = 0x20,
    NicCreateUserDatCfm           = 0x21,
    NicReadUserDatReq             = 0x22,
    NicReadUserDatCfm             = 0x23,
    NicWriteUserDatReq            = 0x24,
    NicWriteUserDatCfm            = 0x25,
    NicRemoveUserReq              = 0x28,
    NicRemoveUserCfm              = 0x29,

    NicSubsAndUserDatReq          = 0x30,
    NicSubscribeInd               = 0x31,
    NicRemoveSubsReq              = 0x32,
    NicRemoveSubsCfm              = 0x33,
    NicSystemACReq                = 0x34,
    NicSystemARIReq               = 0x35,
    NicSystemRPNReq               = 0x36
} NICUserDataEventType;

typedef enum
{
    NICEEpromWriteInd             = 0x50,
    NICEEpromWriteRes             = 0x51,
    NICEEpromFillInd              = 0x52,
    NICEEpromFillRes              = 0x53,
    NICEEpromReadInd              = 0x54,
    NICEEpromReadRes              = 0x55
} NIFUtilityEventType;


typedef enum
{
    NIFMailTraceInd               = 0x20
} NIFMailTraceEventType;


/****************************************************************************/
#endif /*GIMPRIM_H__ */
