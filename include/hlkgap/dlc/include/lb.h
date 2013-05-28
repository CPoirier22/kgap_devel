/*
 ********************************************************************
 *
 * Module: lb.h
 *
 * Config-item: ?
 *
 * Contents: This file contains the Lb function prototypes. It also
 *     includes the necessary files to use the Lb process.
 *
 * Author: DDU
 *
 * Copyright Kirk Telecom A/S. All rights reserved.
 ********************************************************************
 */

#ifndef Lb_HEADER__
#define Lb_HEADER__

#include "../../../common/include/identify.h"
#include "lberror.h"
#include "lbprim.h"
#include "../../dduos/include/dduos.h"
#include "../../maclnk/include/macprim.h"
#include "../../maclnk/include/ccf.h"

struct DlBroadcastReqStruct
{
    SignalType TheSignal;
    UByte MessageUnitLength;
};
typedef struct DlBroadcastReqStruct DlBroadcastReqType;

#define getDlBroadcastReqTypeIE(signal) ((unsigned char*)signal + offsetof(DlBroadcastReqType, MessageUnitLength) + sizeof(UByte))

struct DlBroadcastIndStruct
{
    SignalType TheSignal;
    UByte MessageUnitLength;
};
typedef struct DlBroadcastIndStruct DlBroadcastIndType;

#define getDlBroadcastIndTypeIE(signal) ((unsigned char*)signal + offsetof(DlBroadcastIndType, MessageUnitLength) + sizeof(UByte))

#endif /* Lb_HEADER__ */
