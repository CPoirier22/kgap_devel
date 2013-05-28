/*
 ********************************************************************
 *
 * Module:  sformat.h
 *
 *  Config-item:  ?
 *
 * Contents:  This header file contains macroes, type definitions etc.
 *          parameter definitions related to S-format messages and
 *          primitives.
 *
 *  Author: DDU
 *
 * Copyright Kirk Telecom A/S. All rights reserved.
 *
 ********************************************************************
 */

#ifndef SFORMAT__
#define SFORMAT__

#include "../../dduos/include/dduos.h"
#include "../../../common/include/identify.h"

/***************************************************************************/
/**********   Typedefinition of general S-format message   *****************/
/***************************************************************************/

/* Protocol discriminators */
#define PD_LCE            0
#define PD_CC                 3
#define PD_CISS         4
#define PD_MM           5
#define PD_CLMS         6
#define PD_COMS         7

/* TI related constant */
#define TransactionValueExtension 7
#define TransactionOriginator   0
#define TransactionDestination  1

/********   Identifiers for fixed length information elements   ************/
#define ReservedSingleOctetId 0x80
#define ShiftId         0x90
#define SendingCompleteId   0xA1
#define DelimiterRequestId    0xA2
#define RepeatIndicatorId   0xD0
#define BasicServiceId      0xE0
#define ReleaseReasonId     0xE2
#define SignalId          0xE4
#define TimerRestartId      0xE5
#define TestHookControlId   0xE6
#define SingleDisplayId     0xE8
#define SingleKeypadId      0xE9
#define ReservedEscapeId    0xEF

/********   Identifiers for variable length information elements   *********/
#define InfoTypeId              0x01
#define IdentityTypeId        0x02
#define PortableId          0x05
#define FixedId           0x06
#define LocationAreaId           0x07
#define NwkAssignedIdentityId    0x09
#define AuthTypeId               0x0A
#define AllocationTypeId         0x0B
#define RandId                   0x0C
#define ResId                    0x0D
#define RsId                     0x0E
#define IwuAttributesId          0x12
#define CallAttributesId      0x13
#define ServiceChangeInfoId      0x16
#define ConnectionAttributesId  0x17
#define CipherInfoId             0x19
#define CallIdentityId           0x1A
#define ConnectionIdentityId     0x1B
#define FacilityId               0x1C
#define ProgressIndicatorId   0x1E
#define MultiDisplayId           0x28
#define MultiKeypadId       0x2C
#define FeatureActivateId        0x38
#define FeatureIndicateId        0x39
#define NetworkParameterId       0x41
#define ZapFieldId               0x52
#define ServiceClassId        0x54
#define KeyId                    0x56
#define RejectReasonId        0x60
#define SetupCapabilityId        0x62
#define TerminalCapabilityId     0x63
#define EndToEndCapabilityId     0x64
#define RateParametersId         0x65
#define TransitDelayId           0x66
#define WindowSizeId             0x67
#define CallingPartyNoId      0x6C
#define CalledPartyNoId       0x70
#define CalledPartySubaddrId     0x71
#define DurationId               0x72
#define SegmentedInfoId          0x75
#define AlphanumericId           0x76
#define IwuToIwuId               0x77
#define IwuPacketId              0x7A
#define EscapeToProprietaryId    0x7B
#define EscapeForExtensionId     0x7F

/********   Identifiers for proprietary extended information elements   *****/
#define UakPEIEId                0x80
#define AcPEIEId                 0x81
#define UpiPEIEId                0x82
#define LidPEIEId                0x83
#define SecurityDescriptorPEIEId 0x84
#define MODULE_SHORT_MSF         0x85

#define AcPEIEId_bytes           0x09

#define MessageCallSetup            0x40
#define LRMSEprofile                0x05

/* Length of various fields in a S-format messages */
#define LengthOfTiPdField       1
#define LengthOfMessageType   1
#define LengthOfInfoElemId      1
#define LengthOfLengthOfContents  1

/* MASK definitions related to S-format messages */
#define BIT8_MASK           0x80
#define HIGH_NIBBLE_MASK      0xF0
#define LOW_NIBBLE_MASK       0x0F
#define MESSAGETYPE_MASK      0x7F
#define REPEAT_SHIFT_ID_MASK    0xF0
#define DOUBLE_OCTET_MASK     0xE0
#define CODE_STD_MASK       0x60
#define PROG_DESCRIPTION_MASK    0x7F
#define UPI_MASK                 0x30

/* Type definition of MessageLengthType used i S-format signals */
typedef U16Bits MessageLengthType;

struct SFormatStruct
{
    SignalType TheSignal;
    MessageLengthType MessageLength;
    UByte TiPd;
    UByte MessageType;
};
typedef struct SFormatStruct SFormatType;

#define getSFormatStructIE(signal) ((unsigned char*)signal + offsetof(struct SFormatStruct, MessageType) + sizeof(UByte))

/* Macros related to S-format messages */
#define GET_TI_FROM_MESSAGE(Signal) \
  ((((SFormatType *) Signal)->TiPd & TI_MASK) >> 4)

#define SET_TI_IN_MESSAGE(Signal, TI) \
  Signal->TiPd = ((TI << 4) | (Signal->TiPd & PD_MASK))

#define GET_PD_FROM_MESSAGE(Signal) \
  (((SFormatType *) Signal)->TiPd & PD_MASK)

#define SET_PD_IN_MESSAGE(Signal, PD) \
  Signal->TiPd = (PD | (Signal->TiPd & TI_MASK))

/* GET_MESSAGETYPE_FROM_MESSAGE returns 0x80 if no message type present */
#define GET_MESSAGETYPE_FROM_MESSAGE(Signal) \
  ( (((SFormatType*)Signal)->MessageLength >= 2) ? \
    (((SFormatType*)Signal)->MessageType & MESSAGETYPE_MASK) : \
    0x80 )


#define SET_MESSAGETYPE_IN_MESSAGE(Signal, MESSAGETYPE) \
  Signal->MessageType = (MESSAGETYPE & MESSAGETYPE_MASK)

#define GET_CODE_STANDARD(CodeStdAndLocation) \
  ((CodeStdAndLocation & CODE_STD_MASK) >> 5)

#define GET_PROGRESS_DESCRIPTION(ProgDescriptionByte) \
  (ProgDescriptionByte & PROG_DESCRIPTION_MASK)

#define GET_TI_AND_PD_FROM_XXEI(XXEI) \
  XXEI[3]

/* Typedefinitions of information elements in S-format messages */

/***************************************************************************/
/**********   Definition of fixed length IE   ******************************/
/***************************************************************************/

/**********   Definition of <<Basic Service>>   ****************************/

/*Call Class*/
#define CALL_CLASS_MASK 0xF0

#define NormalCallSetup     0x80
#define InternalCall        0x90
#define EmergencyCallSetup    0xA0
#define ServiceCallSetup    0xB0
#define ExtHandoverCallSetup  0xC0
#define SupplServiceCallSetup 0xD0

#define BASIC_SERVICE_VALUE_MASK  0x0F
#define DefaultSetupAttrib  0x00
#define DectGsmIwpProfile 0x04
#define OtherSetupAttrib  0x0F

#define GET_CALL_CLASS(InfoElem) \
  ((((UByte *) InfoElem)[1] & CALL_CLASS_MASK))

#define SET_CALL_CLASS(InfoElem, CallClass) \
  InfoElem->CallClassAndBasicService = \
  ((CallClass | (InfoElem->CallClassAndBasicService & BASIC_SERVICE_VALUE_MASK))

#define GET_BASIC_SERVICE_VALUE(InfoElem) \
  (((UByte *) InfoElem)[1] & BASIC_SERVICE_VALUE_MASK)


struct BasicServiceStruct
{
    UByte IEID;
    UByte CallClassAndBasicService;
};
typedef struct BasicServiceStruct BasicServiceType;


/**********   Definition of <<Release-Reason>>   ***************************/

#define LengthOfReleaseReason   2

/* RELEASE REASON codes */

/* general values */
#define NormalReleaseReason           0x00
#define UnexpectedMessage             0x01
#define UnknownTransactionId          0x02
#define ManInfoElemMissing            0x03
#define InvalidInfoElemContents       0x04
#define IncompatibleService           0x05
#define ServiceNotImplemented         0x06
#define NegotiationNotSupported       0x07
#define InvalidIdentity               0x08
#define AuthenticationFailed          0x09
#define TimerExpiry                   0x0D
#define PartialRelease                0x0E
#define UnknownReleaseReason          0x0F

/* user values */
#define UserDetached                  0x10
#define UserNotInRange                0x11
#define UserUnknown                   0x12
#define UserAlreadyActive             0x13
#define UserBusy                      0x14
#define UserRejection                 0x15

#define KIRK_ABNORMAL                 0x70

/* external handover values */
#define ExternalHandoverNotSupported  0x21
#define NetworkParametersMissing      0x22
#define ExternalHandoverRelease       0x23

/* temporary overloaded values */
#define Overload                      0x31
#define InsufficientResources         0x32
#define InsufficientBearersAvailable  0x33
#define IwuCongestion                 0x34

struct ReleaseReasonStruct
{
    UByte IEID;
    UByte ReleaseReasonCode;
};
typedef struct ReleaseReasonStruct ReleaseReasonType;


/**********   Definition of <<Signal>>   ***********************************/

#define DialToneOn                0x00
#define RingBackToneOn            0x01
#define InterceptToneOn           0x02
#define NetworkCongestionToneOn   0x03
#define BusyToneOn                0x04
#define ConfirmToneOn             0x05
#define AnswerToneOn              0x06
#define CallWaitingToneOn         0x07
#define OffHookWarningToneOn      0x08
#define TonesOff                  0x3f

#define AlertingOnPattern0        0x40
#define AlertingOnPattern1        0x41
#define AlertingOnPattern2        0x42
#define AlertingOnPattern3        0x43
#define AlertingOnPattern4        0x44
#define AlertingOnPattern5        0x45
#define AlertingOnPattern6        0x46
#define AlertingOnPattern7        0x47
#define AlertingOnContinuous      0x48
#define AlertingOff               0x4f


struct SignalIEStruct
{
    UByte IEID;
    UByte SignalValue;
};
typedef struct SignalIEStruct SignalIEType;


/**********   Definition of <<Timer-Restart>>   ****************************/

#define TimerRestartCode      0

struct TimerRestartStruct
{
    UByte IEID;
    UByte TimerRestartValue;
};
typedef struct TimerRestartStruct TimerRestartType;


/***************************************************************************/
/**********   Definition of variable length IE   ***************************/
/***************************************************************************/

/**********   A generic variable information element ***********************/

typedef struct
{
    UByte IEID;
    UByte LengthOfContents;
}
VarInfoElemType;

/**********   Definition of <<Allocation-Type>>   **************************/

#define ALLOC_DECT_AUTH_ALGORITHM 0x01

#define UAK_NUMBER_MASK 0xF0
#define AC_NUMBER_MASK  0x0F

#define UAK_IPUI_PARK   0x80
#define AC_IPUI_PARK    0x08

typedef struct
{
    UByte IEID;
    UByte LengthOfContents;
    UByte AuthenticationAlgorithmId;
    UByte UakNrAcNr;
}
AllocationTypeType;


/**********   Definition of <<Auth-Type>>   *********************************/

#define DECT_AuthCode         0x01
#define GSM_AuthCode          0x40
#define Escape_AuthCode       0x7F

#define DECT_AUTH_ALGORITHM   0x01
#define GSM_AUTH_ALGORITHM    0x40
#define PROP_AUTH_ALGORITHM   0x7F

#define AUTH_KEY_TYPE_MASK    0xF0
#define AUTH_KEY_NUMBER_MASK  0x0F

#define UAK_AUTH_KEY          0x10
#define UPI_AUTH_KEY          0x30
#define AC_AUTH_KEY           0x40

#define AUTH_KEY_IPUI_PARK    0x08

#define AUTH_TYPE_INC         0x80
#define AUTH_TYPE_TXC         0x20
#define AUTH_TYPE_UPC         0x10

#define CIPHER_KEY_NR_PARK    0x0F

#define CIPHER_KEY_IPUI_PARK  0x08


struct AuthTypeStruct
{
    UByte IEID,                   /* AuthTypeId (0x0A) */
    LengthOfContents,           /* 3 (4 if proprietary algorithm) */
    AuthenticationAlgorithmId,  /* 0x01 = DECT */
    /* 0x40 = GSM */
    /* 0x7F = Proprietary, NOTE: Contains an additional Id (Byte) */
    AuthenticationKey,          /* TTTTNNNN, where */
    /* TTTT=AuthenticationKeyType, and */
    /* NNNN=AuthenticationKeyNumber (MUST BE 8 IN GAP) */
    IncTxcUpcCipherKey;         /* I0TUCCCC, where */
    /* I=ZAP field increment flag, */
    /* T=Transmit derived cipher key in reply flag, */
    /* U=Store derived cipher key flag, and */
    /* CCCC=Cipher key number */
};
typedef struct AuthTypeStruct AuthTypeType;


/**********   Call-Attributes   ********************************************/

#define DECTStandardCode    0
#define PublicAccessProfile 1
#define ClassALinkShared    2
#define CsOnly              0
#define SymmetricUPlane     0
#define LU1                 1
#define Class0MinDelay      0
#define FU1                 1

struct SymmetricCallAttributesStruct
{
    UByte IEID;
    UByte LengthOfContents;
    UByte CodeStdAndNWKLayerAttributes;
    UByte CPlaneClassAndRouting;
    UByte UPlaneSymmetryAndLUIdentification;
    UByte UPlaneClassAndFrameType;
};
typedef struct SymmetricCallAttributesStruct SymmetricCallAttributesType;


/**********   Calling-Party-No   *******************************************/

typedef enum
{
    NT_Unknown = 0x00,
    NT_InternatioNo = 0x10,
    NT_NationalNo = 0x20,
    NT_NwkSpecificNo = 0x30,
    NT_SubsNo = 0x40,
    NT_AbbrevNo = 0x60,
    NT_ResrvExt = 0x70
} NoTypType;

typedef enum
{
    NP_Unknown = 0x00,
    NP_ISDNRecom = 0x01,
    NP_DataPlanRecom = 0x03,
    NP_NationalStd = 0x08,
    NP_Privat = 0x09,
    NP_ResrvExt = 0x0F
} NoPlanType;

typedef enum
{
    PI_PresentAllow = 0x00,
    PI_PresentRestrict = 0x40,
    PI_NoNotAvail = 0x80
} PresentIndicType;

typedef enum
{
    SI_UserNotScreen = 0x00,
    SI_UserVerAndPass = 0x01,
    SI_UserVerAndFail = 0x02,
    SI_NwkProvided = 0x03
} ScreenIndicType;

typedef struct
{
    UByte IEID;
    UByte LengthOfContents;
    UByte NoTypAndNoPlanId;
    /* PresAndScreenInd placed in first octet if bit 8 in NoTypAndNoPlanId is 0 */
}
CallingPartyNoType;

#define getCallingPartyNoTypeOct3ff(ptr) ((unsigned char*)ptr + offsetof(CallingPartyNoType, NoTypAndNoPlanId) + sizeof(UByte))

/**********   Cipher-Info   ************************************************/

#define DisableCiphering   0x00
#define EnableCiphering    0x80

#define DectStdCipherAlgorithm   0x01
#define EscTpProprietaryCiphAl   0x7F

#define DerivedCipherKey   0x90
#define StaticCipherKey    0cA0

#define CipherKeyIpuiPark  0x08

typedef struct
{
    UByte IEID;
    UByte LengthOfContents;
    UByte EnDisAndCipherAlgorithm;
    UByte CipherKey;
}
CipherInfoType;


/**********   Definition of <<Fixed-identity>>   ***************************/

/* Type of fixed identity */
#define AriCode         0x80
#define AriRpnCode      0x81
#define ParkCode        0xA0
#define MaxAriOctets       5    /*  Max. 36 bits (class A)             */
#define MaxAriRpnOctets    5    /*  Max. 40 bits (all classes)         */
#define MaxParkOctets      5    /*  Max. 36 bits (class A)             */

struct AriStruct
{
    UByte LengthOfIdentityValue;  /* length in bits */
    UByte AriValue[MaxAriOctets];
};
typedef struct AriStruct AriType;

struct AriRpnStruct
{
    UByte LengthOfIdentityValue;  /* length in bits */
    UByte AriRpnValue[MaxAriRpnOctets];
};
typedef struct AriRpnStruct AriRpnType;

struct ParkStruct
{
    UByte LengthOfIdentityValue;  /* length in bits + 1 */
    UByte ParkValue[MaxParkOctets];
};
typedef struct ParkStruct ParkType;

union TypeOfFixedIdentityUnion
{
    AriType Ari;
    AriRpnType AriRpn;
    ParkType Park;
};
typedef union TypeOfFixedIdentityUnion TypeOfFixedIdentityType;

struct FixedIdentityStruct
{
    UByte IEID;
    UByte LengthOfContents;
    UByte IdentityType;
    TypeOfFixedIdentityType IdentityValue;
};
typedef struct FixedIdentityStruct FixedIdentityType;


/**********   Definition of <<Identity-Type>>   *****************************/

#define IDENTITY_GROUP_MASK         0x0F

#define PORTABLE_IDENTITY_GROUP     0x00
#define NETWORK_IDENTITY_GROUP      0x01
#define FIXED_IDENTITY_GROUP        0x04
#define PROPRIETARY_IDENTITY_GROUP  0x0F

#define PORTABLE_IPUI_TYPE          0x80
#define PORTABLE_IPEI_TYPE          0x90
#define PORTABLE_TPUI_TYPE          0xA0

#define FIXED_ARI_TYPE              0x80
#define FIXED_ARI_RPN_TYPE          0x81
#define FIXED_PARK_TYPE             0xA0

#define NETWORK_GSM_TYPE            0xF4
#define NETWORK_PROPRIETARY_TYPE    0xFF

struct IdentityTypeStruct
{
    UByte IEID,                   /* IdentityTypeId (0x02) */
    LengthOfContents,           /* 2 */
    Identity,                   /* 1000GGGG, GGGG=IdentityGroup, where */
    /* GGGG=0x00 = PortableIdentity, */
    /* GGGG=0x01 = NetworkAssignedIdentity, */
    /* GGGG=0x04 = FixedIdentity (including PARK), */
    /* GGGG=0x0F = Proprietary */
    Type;                       /* 1TTTTTTT */
    /* PortableIdentityGroup: */
    /*     0x00=IPUI */
    /*     0x10=IPEI */
    /*     0x20=TPUI */
    /* FixedIdentityGroup: */
    /*     0x00=ARI */
    /*     0x01=ARI+RPN */
    /*     0x20=PARK */
    /* NetworkIdentityGroup */
    /*     0x74=GSM */
    /*     0x7F=Proprietary */
};
typedef struct IdentityTypeStruct IdentityTypeType;


/**********   Definition of <<Info-Type>>   ********************************/

#define LocateSuggest                       0x00
#define ExternalHandoverParameters          0x08
#define LocationAreaInfo                    0x09
#define HandoverReference                   0x0A
#define ExternalHandoverCandidate           0x0C
#define SyncronisedExternelHOCandidate      0x0D
#define NonSyncronisedExternelHOCandidate   0x0E
#define OldFixedIdentity                    0x10
#define OldNetworkAssignedIdentity          0x11
#define OldNetworkAssignedLocationArea      0x12
#define OldNetworkAssignedHandoverReference 0x13
#define Billing                             0x20
#define Debiting                            0x21

struct InfoTypeStruct
{
    UByte IEID;
    UByte LengthOfContents;
    UByte ParamType;
};
typedef struct InfoTypeStruct InfoTypeType;


/**********   Definition of <<IWU-to-IWU>>   ********************************/

/* Protocol discriminator */
#define UserSpecific 0xC0

/* Discriminator type */
#define UseOfEmc 0x81

typedef struct
{
    UByte IEID;
    UByte LengthOfContents;
    UByte ProtocolDiscrim;
    UByte DiscrimType;
    UByte Emc[2];
}
IwuToIwuType;

#define getIwuToIwuSIE(ie) ((unsigned char*)ie + offsetof(IwuToIwuType, Emc) + 2 * sizeof(UByte))

/**********   Definition of <<Key>>   **************************************/

/* Key type */
#define DckCode 0x90

#define MaxDckOctets  8         /*  Always 64 bits */

typedef UByte DckType[MaxDckOctets];

union GenericKeyUnion
{
    DckType Dck;
};
typedef union GenericKeyUnion GenericKeyType;

struct KeyStruct
{
    UByte IEID;
    UByte LengthOfContents;
    UByte KeyCode;
    GenericKeyType KeyValue;
};
typedef struct KeyStruct KeyType;


/**********   Definition of <<Location-area>>   ****************************/

/* LI-type */
#define LITypeMask 0xC0
#define LalIncluded 0x40

/* LAL */
#define LALMask 0x3F

struct LocationAreaStruct
{
    UByte IEID;
    UByte LengthOfContents;
    UByte LITypeAndLAL;
};
typedef struct LocationAreaStruct LocationAreaType;


/**********   Definition of <<Multi-Display>>   *****************************/

struct MultiDisplayStruct
{
    UByte IEID;
    UByte LengthOfContents;
};
typedef struct MultiDisplayStruct MultiDisplayType;


/**********   Definition of <<Multi-Keypad>>   *****************************/

struct MultiKeypadStruct
{
    UByte IEID;
    UByte LengthOfContents;
    UByte Keypad;
};
typedef struct MultiKeypadStruct MultiKeypadType;


/**********   Definition of <<Portable-identity>>   ************************/

/* Type of portable identity */
#define IpuiCode        0x80
#define IpeiCode        0x90
#define TpuiCode        0xA0
#define MaxIpuiOctets     13    /*  Max. 100 bits (type N, R, S, O, P, Q, T, U)  */
#define MaxIpeiOctets      5    /*  Always 36 bits                               */
#define MaxTpuiOctets      3    /*  Always 20 bits                               */

struct IpuiStruct
{
    UByte LengthOfIdentityValue;
    UByte IpuiValue[MaxIpuiOctets];
};
typedef struct IpuiStruct IpuiType;

struct IpeiStruct
{
    UByte LengthOfIdentityValue;
    UByte IpeiValue[MaxIpeiOctets];
};
typedef struct IpeiStruct IpeiType;

struct TpuiStruct
{
    UByte LengthOfIdentityValue;  /*  Always 20  */
    UByte TpuiValue[MaxTpuiOctets];
};
typedef struct TpuiStruct TpuiType;

union TypeOfPortableIdentityUnion
{
    IpuiType Ipui;
    IpeiType Ipei;
    TpuiType Tpui;
};
typedef union TypeOfPortableIdentityUnion TypeOfPortableIdentityType;

struct PortableIdentityStruct
{
    UByte IEID;
    UByte LengthOfContents;
    UByte IdentityType;
    TypeOfPortableIdentityType IdentityValue;
};
typedef struct PortableIdentityStruct PortableIdentityType;


/**********   Definition of <<Progress-Indicator>>   ***********************/

#define CCITTStandardCoding 0

/* Progress description */
#define CallNotEndtoEndISDN     1
#define DestinationNonISDN      2
#define OriginationNonISDN      3
#define CallReturnedToISDN      4
#define InbandInfoAvailable     8
#define InbandInfoNotAvailable  9

struct ProgressIndicatorStruct
{
    UByte IEID;
    UByte LengthOfContents;
    UByte CodeStdAndLocation;
    UByte ProgressDescription;
};
typedef struct ProgressIndicatorStruct ProgressIndicatorType;

/**********   Definition of <<Rand>>   *************************************/

#define MaxRandOctets 8         /*  Always 64 bits (DSAA)              */

typedef UByte RandValueType[MaxRandOctets];

struct RandStruct
{
    UByte IEID;
    UByte LengthOfContents;
    RandValueType RandValue;
};
typedef struct RandStruct RandType;


/**********   Definition of <<Reject-Reasons>>   ***************************/

/* Reject Reasons */
#define TPUIUnknown                         0x01
#define IPUIUnknown                         0x02
#define NetWorkAssignedIdentityUnknown      0x03
#define IPEINotAccepted                     0x05

#define AuthenticateFailed                  0x10
#define NoAuthenticationAlgorithm           0x11
#define AuthenticationAlgorithmNotSupported 0x12
#define AuthenticationKeyNotSupported       0x13
#define UPINotEntered                       0x14
#define NoCipherAlgorithm                   0x17
#define CipherAlgorithmNotSupported         0x18
#define CipherKeyNotSupported               0x19
#define RejectIncompatibleService           0x20
#define FalseLCEReply                       0x21
#define LateLCEReply                        0x22
#define InvalidTPUI                         0x23
#define TPUIAssignmentLimitsUnacceptable    0x24
#define insufficientMemory                  0x2F
#define OverLoad                            0x30
#define TestCallBackNormalEnBloc            0x40
#define TestCallBackNormalPiecewise         0x41
#define TestCallBackEmergencyEnBloc         0x42
#define TestCallBackEmergencyPiecewise      0x43
#define InvalidMessage                      0x5F
#define InformationElementError             0x60
#define InvalidInformationElementContents   0x64
#define RejectTimerExpiry                   0x70

struct RejectReasonStruct
{
    UByte IEID;
    UByte LengthOfContents;
    UByte RejectReasonCodeValue;
};
typedef struct RejectReasonStruct RejectReasonType;


/**********   Definition of <<Res>>   **************************************/

#define MaxResOctets  4         /*  Always 32 bits (DSAA)              */

typedef UByte ResValueType[MaxResOctets];

struct ResStruct
{
    UByte IEID;
    UByte LengthOfContents;
    ResValueType ResValue;
};
typedef struct ResStruct ResType;


/**********   Definition of <<Rs>>   ***************************************/

#define MaxRsOctets 8           /*  Always 64 bits (DSAA)              */

typedef UByte RsValueType[MaxRsOctets];

struct RsStruct
{
    UByte IEID;
    UByte LengthOfContents;
    RsValueType RsValue;
};
typedef struct RsStruct RsType;


/**********   Definition of <<Service-Class>>   ****************************/

#define ONE_NOMINATED_NUMBER              0x01
#define LOCAL_CALLS                       0x02
#define NATIONAL_CALLS                    0x03
#define MOBILE_AND_PREMIUM_SERVICE_CALLS  0x04
#define INTERNATIONAL_CALLS               0x05
#define SATELITE_SERVICES                 0x06

struct ServiceClassStruct
{
    UByte IEID;
    UByte LengthOfContents;
    UByte ServiceClassField;
};
typedef struct ServiceClassStruct ServiceClassType;

/**********   Definition of <<Setup-Capability>>   **************************/

#define NORMAL_PAGING_CAPABILITY  0x01
#define FAST_PAGING_CAPABILITY    0x02
#define NORMAL_SETUP_CAPABILITY   0x04
#define FAST_SETUP_CAPABILITY     0x08

#define SET_CAPABILITIES(X, PAGING_CAPABILITY, SETUP_CAPABILITY) \
    X = ((SETUP_CAPABILITY) & 0x0C) | ((PAGING_CAPABILITY) & 0x03)

struct SetupCapabilityStruct
{
    UByte IEID, LengthOfContents, Capabilities;
};
typedef struct SetupCapabilityStruct SetupCapabilityType;


/**********   Definition of <<Terminal-Capability>>   **********************/

/* Display capability */
#define DisplayNotApplicable  0x00
#define NoDisplay             0x01
#define Numeric               0x02
#define NumericPlus           0x03
#define Alfanumeric           0x04
#define FullDisplay           0x05
#define ExtentedDisplayCapab  0x0F

/* Tone capability */
#define ToneNotApplicable     0x00
#define NoToneCapab           0x10
#define DialToneOnly          0x20
#define E182TonesSup          0x30
#define CompleteDECTTonesSup  0x40

/* Adaptive volume control provision (A-VOL) */
#define AVOLNotApplicable     0x00
#define NoPPAVOL              0x01
#define PPAVOLUsed            0x02
#define DisableFPAVOL         0x03

/* PP ambient noise rejection capability (N-REJ) */
#define NREJNotApplicable     0x00
#define NoNREJ                0x04
#define NREJProvided          0x08

/* Echo parameters */
#define EchoParamNotApplicable  0x00
#define MinimumTCL              0x10
#define FullTCL                 0x20

/* Slot type capability */
#define HalfSlot    0x01
#define FullSlot    0x08
#define DoubleSlot  0x10

/* Profile Indicator_1 */
#define GAP_PAP_supported     0x02
#define GSM_profile_supported 0x04
#define ISDN_supported        0x08
#define DataServicesProfileABClass1 0x10
#define DataServicesProfileABClass2 0x20
#define DataServicesProfileCClass2  0x40

/* Spare(4bits) + Control Codes(3 bits) */
#define ClrDisplay          0x01        /* ascii 0C clear display*/
#define ClrDisAndMoveCursor 0x02        /* 0x02: Coding 001 plus 08 to 0B and 0D.*/
/* 0x03: Coding 010 plus 02, 03, 06, 07, 19 and 1A.*/
/* 0x04: Coding 011 plus 0E and 0F.*/

struct TerminalCapabilityStruct
{
    UByte IEID;
    UByte LengthOfContents;
    UByte DisplayAndToneCapab;
    UByte AVOLNREJAndEchoParam;
    UByte SlotTypeCapab;
    UByte NumberOfStoredDispCharMS;
    UByte NumberOfStoredDispCharLS;
    UByte NumberOfLinesInDisp;
    UByte NumberOfCharPerLine;
    UByte ProfileIndicator_1;
    UByte ControlCodes;
};
typedef struct TerminalCapabilityStruct TerminalCapabilityType;

/**********   Definition of <<Zap-Field>>   ********************************/

#define ZAP_FIELD_MASK 0x0F

struct ZapFieldStruct
{
    UByte IEID;
    UByte LengthOfContents;
    UByte ContentsField;
};
typedef struct ZapFieldStruct ZapFieldType;

/***************************************************************************/
/**********   Proprietary extended information elements   ******************/
/***************************************************************************/

/**********   AC   *********************************************************/

#define MaxAcOctets 4

typedef struct
{
    UByte IEID;                   /* Always EscapeForExtensionId = 0x7F */
    UByte LengthOfContents;       /* Always MaxAcOctets + 1 = 5         */
    UByte PEIEID;                 /* Always AcPEIEId = 0x81             */
    UByte Ac[MaxAcOctets];
}
AcIEType;

/**********   LID   ********************************************************/

typedef struct
{
    UByte IEID;                   /* Always EscapeForExtensionId = 0x7F */
    UByte LengthOfContents;       /* Always 2                           */
    UByte PEIEID;                 /* Always LidPEIEId = 0x83            */
    LIDType Lid;
}
LidIEType;

/**********   Security descriptor    ***************************************/

/* Security specification */
#define SuspendOperation      0x80
#define AbortOperationOnFail  0x40
#define RemoveSubsOnFail      0x20
#define ProcedureMask         0x0F
#define ProcKeyAlloc          0x00
#define ProcAuthOfPt          0x01
#define ProcAuthOfUser        0x02
#define ProcCipherOn          0x03
#define ProcAuthOfPtGenDck    0x04

typedef struct
{
    UByte IEID;                   /* Always EscapeForExtensionId = 0x7F     */
    UByte LengthOfContents;       /* Always NoOfSecuritySpec + 2            */
    UByte PEIEID;                 /* Always SecurityDescriptorPEIEId = 0x84 */
    UByte NoOfSecuritySpec;
}
SecurityDescriptorIEType;

#define getSecuritySpec(ie) ((unsigned char*)ie + offsetof(SecurityDescriptorIEType, NoOfSecuritySpec) + sizeof(UByte))

/**********   UAK   ********************************************************/

#define MaxUakOctets  16        /* Always 128 bits */

typedef struct
{
    UByte IEID;                   /* Always EscapeForExtensionId = 0x7F */
    UByte LengthOfContents;       /* Always MaxUakOctets + 1 = 17       */
    UByte PEIEID;                 /* Always UakPEIEId = 0x80            */
    UByte Uak[MaxUakOctets];
}
UakIEType;

/**********   UPI   ********************************************************/

#define MaxUpiOctets  4         /* Always 32 bits */

typedef struct
{
    UByte IEID;                   /* Always EscapeForExtensionId = 0x7F */
    UByte LengthOfContents;       /* Always MaxUpiOctets + 1 = 5        */
    UByte PEIEID;                 /* Always UpiPEIEId = 0x82            */
    UByte Upi[MaxUpiOctets];
}
UpiIEType;

#endif /* SFORMAT__ */
