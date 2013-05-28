/*
 ********************************************************************
 *
 * Module: recfmt.h
 *
 * Config-item: ?
 *
 * Contents:  This header file contains definitions of the diagnostic file records (CCFP)
 *
 * Author:   Kirk telecom / BJR
 *
 * Copyright: Kirk Telecom A/S. All rights reserved.
 *
 * $Header:   K:/ph/srclib/util/basis/archive/h/recfmt.h_v   1.4.1.0   Nov 19 2003 11:02:22   on  $
 *
 * $Log:   K:/ph/srclib/util/basis/archive/h/recfmt.h_v  $
 *
 *    Rev 1.4.1.0   Nov 19 2003 11:02:22   on
 * Initial version of IP 600
 *
 *    Rev 1.4   Jan 29 1997 14:10:14   BJR
 * Added def. of <<Time>>, <<Date>>, <<Variable>> and <<Heap block>>.
 *
 *    Rev 1.3   Jan 20 1997 11:42:34   BJR
 * Added <<Flash SW part no>>.
 *
 *    Rev 1.2   Nov 21 1996 09:39:10   BJR
 * Corrected error in RestartDataRecType.
 *
 *    Rev 1.1   Nov 19 1996 14:58:08   BJR
 * Added NumberOfRecId.
 *
 *    Rev 1.0   Nov 04 1996 13:35:48   BJR
 * First revision.
 *
 ********************************************************************
 */

#ifndef RECFMT_H__
#define RECFMT_H__

#include "../../../common/include/bitsdef.h"

/***************************************************************************/
/****************   Definition of the generic record    ********************/
/***************************************************************************/

/*****************   Definition of the <record type>  **********************/

#define RestartDataRecId      0x00
#define NfeDataRecId          0x01
#define AriRecId              0x02
#define FlashSwVersionRecId   0x03
#define BootSwVersionRecId    0x04
#define FlashSwPartNoRecId    0x05
#define DateRecId             0x06
#define TimeRecId             0x07
#define VariableRecId         0x08
#define HeapBlockRecId        0x09
#define NumberOfRecId         0x0A

typedef UByte     RecordTypType;
typedef U16Bits   RecordLengthType;

typedef struct
{
    RecordLengthType RecordLength;
    RecordTypType     RecordTyp;
    UByte             Data [];
}
RecordFormatType;


/***************************************************************************/
/*******************   Definition of specific records   ********************/
/***************************************************************************/

/***********************   Definition of <<ARI>>   *************************/

typedef struct
{
    RecordLengthType RecordLength;
    RecordTypType     RecordTyp;
    UByte             Ari [ 5 ];
}
AriRecType;

/***********************   Definition of <<Data>>   ************************/

typedef struct
{
    RecordLengthType    RecordLength;
    RecordTypType        RecordTyp;
}
DateRecType;

/********************   Definition of <<Heap block>>   *********************/

typedef struct
{
    RecordLengthType    RecordLength;
    RecordTypType        RecordTyp;
    UByte                Address [ 3 ];
    U16Bits              BlockLength;
    UByte                BlockData [];
}
HeapBlockRecType;

/*******************   Definition of <<NFE data>>   ************************/



/*******************   Definition of <<Restart data>>   ********************/

/***********************   Definition of <<Time>>   ************************/

typedef struct
{
    RecordLengthType    RecordLength;
    RecordTypType        RecordTyp;
}
TimeRecType;

/*********************   Definition of <<Variable>>   **********************/

typedef struct
{
    RecordLengthType    RecordLength;
    RecordTypType        RecordTyp;
    UByte                NameAddrData[];
}
VariableRecType;

#endif /* RECFMT_H__*/
