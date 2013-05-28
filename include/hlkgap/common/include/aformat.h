/*********************************************************************
 *
 * Module:      aformat.h
 *
 * Config-item:    ?
 *
 * Contents:    This header file contains macroes, type definitions etc.
 *              parameter definitions related to application proprietary
 *              messages and primitives.
 *
 * Author:  OZ?, Kirk Telecom
 *
 * Copyright Kirk Telecom A/S. All rights reserved.
 *
 *********************************************************************/

#ifndef AFORMAT__
#define AFORMAT__

/********   Identifiers for application proprietary extended information elements   *****/
#define PhoneBookAPEIEId                0xc0
#define StandByTxtAPEIEId               0xc1
#define B_answerAPEIEId                 0xc2
#define MsfSetupAPEIEId                 0xc3
#define MsfFunctionAPEIEId              0xc4
#define MsfKeypadInfoAPEIEId            0xc5
#define IconHandlingAPEIEId             0xc6
#define EepromLoadAPEIEId               0xc7
#define NoAndPCSAPEIEId                 0xc8
#define SysBearerInfoAPEIEId            0xc9
#define AlarmCallInfoAPEIEId            0xca
#define MSFOutgMessageAPEIEId           0xcb
#define PPStatusInfoAPEIEId             0xcf
#define FixedPartInfoAPEIEId            0xda
#define OEM_APEIEId                     0xFF
#define StandByTxtCfmAPEIEId            0xcc
#define AsciiStrReqAPEIEId              0xd6
#define AsciiStrCfmAPEIEId              0xd7
#define MenuSelectSetupReqAPEIEId       0xd8
#define MenuSelectCfmAPEIEId            0xd9
#define TimeMessageInfoId               0xD3

/**********************************/
/***    Constant definitions    ***/
/**********************************/

typedef enum                    /* OEMBrancheType */
{
    OEM_13258597,
    NoOEM = 0xFF
} OEMBrancheType;


/***************************************************************************************/
/**********   application proprietary extended information elements   ******************/
/***************************************************************************************/

/**********   PhoneBook  ********************************************************/


typedef struct
{
    UByte IEID;                   /* Always EscapeForExtensionId = 0x7F */
    UByte LengthOfContents;       /*  */
    UByte APEIEID;                /* Always PhoneBookAPEIEId = 0xc0    */
}
PhoneBookIEType;

/**********   AsciiStrRequest ************************************************/

typedef struct
{
    UByte IEID;                   /* Always EscapeForExtensionId = 0x7F*/
    UByte LengthOfContents;
    UByte APEIEID;                /* Always AsciiStrRequestAPEIEId = 0xD6*/
    UByte ASCII_Mode;
    UByte MinStrLen;
    UByte MaxStrLen;
}
AsciiStrRequestIEType;

/**********   StandByTxt  ********************************************************/

#define STANDBYTXT_LENGTH       10

typedef struct
{
    UByte IEID;                   /* Always EscapeForExtensionId = 0x7F */
    UByte LengthOfContents;       /* Always STANDBYTXT_LENGTH + 1 = 11  */
    UByte APEIEID;                /* Always StandByTxtAPEIEId = 0xc1    */
    UByte StandByTxt[STANDBYTXT_LENGTH];
}
StandByTxtIEType;


/**********   B-answer  ********************************************************/

typedef struct
{
    UByte IEID;                   /* Always EscapeForExtensionId = 0x7F */
    UByte LengthOfContents;       /* Always 1  */
    UByte APEIEID;                /* Always B-answerAPEIEId = 0xc2    */
}
B_answerIEType;

/**********   StandByTxtCfm  *****************************************************/
typedef struct
{
    UByte IEID;                   /* Always EscapeForExtensionId = 0x7F */
    UByte LengthOfContents;       /* Always 2  */
    UByte APEIEID;                /* Always StandByTxtAPEIEId = 0xcc    */
    UByte Error;
}
StandByTxtCfmIEType;

/**********   MsfSetup  ********************************************************/
#define SIS_MASK   0x01         /*Save In Stack*/
#define  NA_MASK   0x02         /*No Acknowledge*/
#define  AD_MASK   0x04         /*Automatic delay*/
#define RAS_MASK   0x08         /*Re Attempt Setup*/
#define  MU_MASK   0x01         /*MSF UP (Automatic MSF setup)*/
#define  VA_MASK   0x02         /*Vibrate Always*/
#define  AA_MASK   0x04         /*Tone Always*/
#define  VT_MASK   0x08         /*Vibrate/Tone (both Vibrator and Tone on)*/
#define  CO_MASK   0x10         /**/
#define  F0_MASK   0x20         /* F0,F1,F2, Handling of LED and MAIL icon*/
#define  F1_MASK   0x40         /**/
#define  F2_MASK   0x80         /**/

typedef struct
{
    UByte IEID;                   /* Always EscapeForExtensionId = 0x7F */
    UByte LengthOfContents;
    UByte APEIEID;                /* Always MsfSetupAPEIEId = 0xc3 */
    UByte PpSetup;
    /*  IE Contains  Length of DisplayTxt, DisplayTxt,
     *  Length of CallBackNo,  CallBackNo
     *  */
}
MsfSetupIEType;

#define getMsfSetupIETypeIE(signal) ((unsigned char*)signal + offsetof(MsfSetupIEType, PpSetup) + sizeof(UByte))

/**********   MsfFunction ******************************************************/

#define FunctionNoLength   04

typedef struct
{
    UByte IEID;                   /* Always EscapeForExtensionId = 0x7F */
    UByte LengthOfContents;       /* Always 5 */
    UByte APEIEID;                /* Always MsfFunctionAPEIEId = 0xc4 */
    UByte FunctionNo[FunctionNoLength];
}
MsfFunctionIEType;

/**********   MsfKeypadInfo ****************************************************/

typedef struct
{
    UByte IEID;                   /* Always EscapeForExtensionId = 0x7F */
    UByte LengthOfContents;       /* Always 2 */
    UByte APEIEID;                /* Always MsfKeypadInfoAPEIEId = 0xc5 */
    UByte KeypadInfo;
}
MsfKeypadInfoIEType;

/**********   Icon handling ****************************************************/

typedef struct
{
    UByte IEID;                   /* Always EscapeForExtensionId = 0x7F */
    UByte LengthOfContents;       /* Always 2 */
    UByte APEIEID;                /* Always IconHandlingAPEIEId = 0xc6 */
    UByte IconInfo[2];
}
IconHandlingIEType;

/**********  MenuSelectSetupRequest ****************************************************/

typedef struct
{
    UByte IEID;                   /* Always EscapeForExtensionId = 0x7F*/
    UByte LengthOfContents;
    UByte APEIEID;                /* Always MenuSelectSetupRequestAPEIEId = 0xD8*/
    UByte NumberOfMenuItems;
    UByte MenuItemLength;
}
MenuSelectSetupRequestIEType;

typedef struct
{
    UByte IEID;
    UByte LengthOfContents;
    UByte TimeMessageInfo_Id;
    UByte Time_Type;
}
TimeMessageInfoType;

typedef struct
{
    BYTE AT_Cmd;                  /**/
}
PPInfoDataTransferType;

/**********   Eeprom Load / Miscellaneous ***************************************/

/* Defining types: */
#define LOAD_MENU     00
#define LOAD_TEXT     01
#define MSF_PRE_REL   02
#define MSF_ALERT     03
#define EEPROM_RD_REQ 04        /*Request to read eeprom data in PP*/
#define EEPROM_RD_RES 05        /*Responce of eeprom data from PP*/
#define EEPROM_WR     06    /*Write data to the PP's eeprom. AdrOffset is the absolute addr.*/

typedef struct
{
    UByte IEID;                   /* Always EscapeForExtensionId = 0x7F */
    UByte LengthOfContents;
    UByte APEIEID;                /* Always EepromLoadAPEIEId = 0xc7 */
    UByte Type;
    U16Bits AdrOffset;
}
EepromLoadIEType;

typedef struct
{
    UByte IEID;                   /* Always EscapeForExtensionId = 0x7F */
    UByte LengthOfContents;
    UByte APEIEID;                /* Always EepromLoadAPEIEId = 0xc7 */
}
Ext_Serv_IEType;

/**********   SW No and PCS ****************************************************/
#define NoLen 4
#define PCSLen 3
typedef struct
{
    UByte IEID;                   /* Always EscapeForExtensionId = 0x7F */
    UByte LengthOfContents;
    UByte APEIEID;                /* Always NoAndPCSAPEIEId = 0xc8 */
    UByte Version[NoLen + PCSLen];        /* Taken from ShowVersionPCS defined in userpart*/
}
NoAndPCSIEType;

/********** System Bearer Information ****************************************************/

#define MIXED_SLOT    0         /* Use both even and odd slots mixed in the system (default).*/
#define EVEN_SLOT     1         /* Use only even slot*/
#define ODD_SLOT      2         /* Use only odd slot*/
#define EVEN_ODD_SLOT 3         /* Use even slot on even RPN and odd slot on odd RPN.*/
typedef struct
{
    UByte IEID;                   /* Always EscapeForExtensionId = 0x7F */
    UByte LengthOfContents;
    UByte APEIEID;                /* Always SysBearerInfoAPEIEId = 0xc9 */
    UByte SysBearerInfo;
}
SysBearerInfoIEType;



/**********   OEM_APEIId  **************************************************/

typedef struct
{
    UByte IEID;                   /* Always EscapeForExtensionId = 0x7F */
    UByte LengthOfContents;
    UByte APEIEID;                /* Always OEM_APEIEId = 0xFF    */
    OEMBrancheType Byte_4_Custumer;       /* Describe which branche to use eg. Philips */
    UByte Ext_info_element;       /* Extended information element dependent on branche */
    /* Contain data associated to Ext_info_element */
}
OEM_IEType;


/**********   Alarm call  ********************************************************/

typedef struct
{
    UByte IEID;                   /* Always EscapeForExtensionId = 0x7F */
    UByte LengthOfContents;       /* Always 1  */
    UByte APEIEID;                /* Always B-answerAPEIEId = 0xca    */
}
AlarmCallIEType;

/********** MSF-OutgMessage **************************************************/

typedef struct
{
    UByte IEID;                   /* Always EscapeForExtensionId = 0x7F */
    UByte LengthOfContents;
    UByte APEIEID;                /* Always OEM_APEIEId = 0xFF    */
    UByte SetupSpec2;             /* As in MfsSetup format II */
    UByte SetupSpec3;             /* As in MfsSetup format III */
    UByte AlertPattern;
    UByte AlertTone;
    UByte AlertTimeout;           /* In seconds */
    UByte DisplayTimeout;         /* In seconds */
    /* Contains : DestinationIdLenght + DestinationId*/
    /*            DisplaytextLength + DisplayText*/
    /*            CallBackNoLength + CallBackNo*/
}
MSFOutgMessageIEType;

#define getMSFOutgMessageIETypeIE(signal) ((unsigned char*)signal + offsetof(MSFOutgMessageIEType, DisplayTimeout) + sizeof(UByte))

/**********   PPStatus ****************************************************/

typedef struct
{
    UByte IEID;                   /* Always EscapeForExtensionId = 0x7F*/
    UByte LengthOfContents;
    UByte APEIEID;                /* Always SoftKeypadInfoAPEIEId = 0xcf*/
    UByte StatusType;
}
PPStatusInfoIEType;

#define getPPStatusInfoIETypeIE(signal) ((unsigned char*)signal + offsetof(PPStatusInfoIEType, StatusType) + sizeof(UByte))

#define PpStatusInd            0x01
#define PpStatusReadReq        0x02
#define PpStatusReadCfm        0x03
#define PpStatusRes            0x04
#define PpChargerStatusInd     0x0B
#define PPAlarm                0x0C     /* see 1325 8576-PA*/
#define PPRSSITransferReq      0x0D     /* see 1325 8576-PA*/
#define PPRSSITransferCfm      0x0E     /* see 1325 8576-PA*/
#define PPDistTransferInd      0x0F
#define PPDistTransferRes      0x10
#define PPInfoDataTransferReq  0x11     /* see 1325 8576-PA*/
#define PPInfoDataTransferCfm  0x12     /* see 1325 8576-PA*/
#define PPUploadJavaProgInfo   0x13
#define PPUploadJavaProg       0x14
#define PPPeltorAlarm          0x22     /* see 1325 8576-PA*/
#define PPPeltorUpdateNumber   0x23


/*
#define PpStatusInd         0x01
#define PpChargerStatusInd  0x0B
#define PPAlarm             0x0C  // see 1325 8576-PA
#define PPRSSITransferReq      0x0D  // see 1325 8576-PA
#define PPRSSITransferCfm      0x0E  // see 1325 8576-PA
#define PPInfoDataTransferReq  0x11  // see 1325 8576-PA
#define PPInfoDataTransferCfm  0x12  // see 1325 8576-PA
#define	PPDiversityMesReq      0x12
#define	PPDiversityMesCfm      0x13 */

/********** FixedPartInfo ****************************************************/
typedef enum
{ HANDOVER_TYP = 0x01 } HoDataType;

typedef struct
{
    unsigned char FAPPCC_State;
    unsigned char FIWU_CCState;
    unsigned char FIWU_CissState;
    unsigned char FIWU_CCTIPD;
    unsigned char CC_CCState;
    unsigned char FLCE_CCState;
    unsigned char LAPC_Vs;
    unsigned char LAPC_Va;
    unsigned char LAPC_Vr;
    unsigned char LAPC_ClassAState;
    unsigned char HLME_State;
    unsigned char ErrorCode;
}
HandoverDataType;

typedef enum
{ HANDOVER_OK, HANDOVER_REJECT } HoErrorType;

typedef struct
{
    UByte IEID;                   /* Always EscapeForExtensionId = 0x7F*/
    UByte LengthOfContents;
    UByte APEIEID;                /* Always FixedPartInfoAPEIEId = 0xda*/
    HoDataType DataType;
    HoErrorType ErrorCode;
    UByte DataLen;
}
FixedPartInfoIEType;

#define getFixedPartInfoIETypeIE(signal) ((unsigned char*)signal + offsetof(FixedPartInfoIEType, DataLen) + sizeof(UByte))

#endif /* AFORMAT__ */
