/*
 ********************************************************************
 *
 * Module: f_appdef.h
 *
 * Config-item: ?
 *
 * Contents: Defines identifiers used on the application level.
 *
 * Author: Kirk telecom / HN
 *
 * Copyright Kirk Telecom A/S. All rights reserved.
 *
 ********************************************************************
 */

#ifndef F_APPDEF_HEADER__
#define F_APPDEF_HEADER__

/* Imports */
#include "apdbprim.h"

/* Constants */
#define MaxUsers    8       /* 64*/
#define MaxNoInClipStack 05
#define KIRK_EMC    0x004D
#define KIRK_EMC_SE   0x4D00  /*For testing against mashine running small endian*/
#define NilPPID    0xFF
#define NilLID     0xFF
#define ExtCallPPIDValue 0xFE

/* Definition of special digits */
#define RKeyDigit    0xB
#define NilDigit    0xC
#define PauseDigit   0xD
#define StarDigit    0xE
#define SquareDigit   0xF
/*
typedef struct
{
 PPIDType    PPID;
 MonthType   Month;
 DayInMonthType  Date;
 HourType    Hour;
 MinuteType   Minute;
}ClipStackContentType;

typedef ClipStackContentType ClipStackType[MaxNoInClipStack];
*/
#endif /* F_APPDEF_HEADER__ */
