/*
 ********************************************************************
 *
 * Module: dbprim.h
 *
 * Config-item: ?
 *
 * Contents: Defines the primitives for the FP subscription data base (DB).
 *
 * Author: Kirk telecom / BJR
 *
 * Copyright Kirk Telecom A/S. All rights reserved.
 ********************************************************************
 */

#ifndef DBPRIM_HEADER__
#define DBPRIM_HEADER__

#include "../../dduos/include/dduos.h"
#include "../../common/include/sformat.h"

typedef struct
{
    UByte ErrorCode;
}
DBReadDataCfmType;

#define getDBReadDataCfmTypeIE(signal) ((unsigned char*)signal + sizeof(UByte))

typedef struct
{
    U16Bits DataTypes;
    PPIDType ppid;
}
DBStoreDataReqType;

#define getDBStoreDataReqTypeIE(signal) ((unsigned char*)signal + offsetof(DBStoreDataReqType, ppid) + sizeof(PPIDType))

typedef struct
{
    PMIDType Tpui;
    UByte ErrorCode;
}
DBFindTpuiCfmType;

/* Data types */
#define NO_OF_DATATYPES 7
#define DBDT_Dck     0x0002
#define DBDT_Ipui     0x0004
#define DBDT_Upi   0x0020
#define DBDT_Uak   0x0040

/* Not accepted */
#define NoError   0
#define OtherError  1
#define NoEntry   2
#define CheckSumError   3

#endif /* DBPRIM_HEADER__ */
