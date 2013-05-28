/*
 ********************************************************************
 *
 * Module: apdbprim.h
 *
 * Config-item: ?
 *
 * Contents: Defines the primitives for the FP application data base (F-App-DB).
 *
 * Author: Kirk telecom / HN
 *
 * Copyright Kirk Telecom A/S. All rights reserved.
 *
 ********************************************************************
 */

#ifndef APDBPRIM_HEADER__
#define APDBPRIM_HEADER__

/* Imports */
#include "../../dduos/include/dduos.h"
#include "../../common/include/sformat.h"
#include "../../../common/include/identify.h"

/* Definition of the type sizes */
#define LocalNoLength             12      /* Must be an even number */
#define ExchCodeLength            4       /* Must be an even number */
#define IPEISize              5
#define NameLength              10
#define StbTxtStdLength             10
#define StbTxtExtLength             14
#define StbTxtLength             36       /*(StbTxtExtLength + StbTxtStdLength)   // = 24*/
#define PresTxtLength               32
#define ExtNameLength               10+1+1+1    /*NameLength+S/M+Pos/NULL*/
#define FirmLength              10
#define TBLocalNoLength             24  /* Must be an even number */
#define Ext_StbTxtLength            38  /*  A pp can show 36 Caracters + 1 NULL termination + 1 lengthindication  //MTH*/
#define StandByTextSupplementLength 26
#define PartNoLength                 4
#define PCSLength                    3
#define ACLength                     8
#define PPSwPartNoLen                4
#define PPSwPCSNoLen                 3
#define ACUpiLen                     4


/* Definition of the primitives - used as SubEvent parameter */
#define SUBS_DATA_req              0x08
#define SUBS_DATA_cfm              0x09
#define STBTXT_BEARER_READ_req          0x41
#define STBTXT_BEARER_READ_cfm       0x42
#define PP_DATA_WRITE_req           0x46
#define PP_DATA_WRITE_cfm             0x47
#define ACUPI_SYSTEM_WRITE_req			0x48

/* Error parameter */
#define NoError    0
#define InvalidEntry   1
#define InvalidLID   2
#define InvalidIPEI   3
#define InvalidNumber  4
#define ParameterMissing 5
#define OutOfMemory   6
#define InvalidInput   7


/* Definition of data types */
typedef UByte LocalNoType[LocalNoLength];
typedef UByte IPEIType[IPEISize];
typedef UByte AC_UPIType[MaxAcOctets];  /* Compressed to 4 octets */
typedef char StbTxtType[StbTxtLength];
typedef char Ext_StbTxtType[Ext_StbTxtLength];
typedef char StandByTextSupplementType[StandByTextSupplementLength + 1];
typedef UByte PartNoType[PartNoLength];
typedef char PCSType[PCSLength];
/* Definition of the primitive types */
typedef UByte PackedLocalNoType[LocalNoLength / 2];



typedef struct  /*Warning DO NOT swap the content of this struct*/
{
    UByte              EmptyMarker;           /* 1                      */
    UByte              Upi [ MaxUpiOctets ];  /*  4   Total 5           */
    UByte              Uak [ MaxUakOctets ];  /* 16   Total 21*/
    UByte              CheckSum;              /*  1   Total 22*/
    UByte 			   access_level;		  /*  1   TOtal 31*/
    DckType            Dck;                   /*  8   Total 31*/
}
QuickDatabaseType;
extern QuickDatabaseType QuickData[MAX_Allowed_Users];


/* SUBS_DATA */
typedef struct
{
    SignalType SignalHeader;      /* Address field used */
    IPEIType IPEI;
    ProcessIdType ReturnProcessId;
    AddressType ReturnAddress;
}
SubsDataReqType;

typedef struct
{
    SignalType SignalHeader;
    UByte Error;
    IPEIType IPEI;
    PPIDType PPID;
    AC_UPIType AC_UPI;
}
SubsDataCfmType;

/* PP_DATA_WRITE */
typedef struct
{
    SignalType SignalHeader;      /* PPID placed in Address field */
    ProcessIdType ReturnProcessId;
    AddressType ReturnAddress;
}
PPDataWriteReqType;

#define getWriteReqData(signal) ((unsigned char*)signal + offsetof(PPDataWriteReqType, ReturnAddress) + sizeof(AddressType))

typedef struct
{
    SignalType SignalHeader;
    UByte Error;
}
PPDataWriteCfmType;


typedef struct
{
    SignalType SignalHeader;
    ProcessIdType OriginatorProcess;
}
SoftkeyReqType;

typedef struct
{
   SignalType      SignalHeader;
   UByte           ACUpi[ACUpiLen];
} SysAcReqType;


#endif /* APDBPRIM_HEADER__ */
