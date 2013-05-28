/*
 ********************************************************************
 *
 * Module: cissmsg.h
 *
 * Config-item: ?
 *
 * Contents: This file contains definitions of CISS messages
 *
 * Author: Kirk telecom / BJR
 *
 * Copyright Kirk Telecom A/S. All rights reserved.
 ********************************************************************
 */

#ifndef CISSMSG_H__
#define CISSMSG_H__

#include "../../dduos/include/dduos.h"
#include "../../common/include/sformat.h"

/* Definition of CISS messages */
#define CISS_RELEASE_COM   0x5A
#define FACILITY     0x62
#define CISS_REGISTER      0x64

typedef struct
{
    SignalType TheSignal;
    MessageLengthType MessageLength;
    UByte TiPd;
    UByte MessageType;
}
CissReleaseComType;

typedef struct
{
    SignalType TheSignal;
    MessageLengthType MessageLength;
    UByte TiPd;
    UByte MessageType;
}
FacilityType;

typedef struct
{
    SignalType TheSignal;
    MessageLengthType MessageLength;
    UByte TiPd;
    UByte MessageType;
}
CissRegisterType;

#endif /* CISSMSG_H__ */
