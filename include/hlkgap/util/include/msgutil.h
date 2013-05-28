/*
 ********************************************************************
 *
 * Module: msgutil.h
 *
 * Config-item: ?
 *
 * Contents: Header file for msgutil.c
 *
 * Author: Kirk telecom / BJR
 *
 * Copyright Kirk Telecom A/S. All rights reserved.
 ********************************************************************
 */

#ifndef MSGUTIL_HEADER__
#define MSGUTIL_HEADER__

#include "../../../common/include/bitsdef.h"
#include "../../common/include/sformat.h"
#include "../../dduos/include/dduos.h"

extern void *FindInfoElement(UByte InfoElementId, UByte * Message, int MessageLength);
extern void *FindSuccInfoElement(UByte InfoElementId, UByte * Message, int MessageLength, UByte * InfoElement);
extern void CheckMessage(SFormatType * Message);
extern unsigned int sizeOfSignalHeader(SignalType* signal);

#endif /*Not MSGUTIL_HEADER__ */
