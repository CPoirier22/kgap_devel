/*
 ********************************************************************
 *
 * Module: apomprim.h
 *
 * Config-item: ?
 *
 * Contents: Defines the primitives for f_app_om.
 *
 * Author: Kirk telecom / HN
 *
 * Copyright Kirk Telecom A/S. All rights reserved.
 *
 ********************************************************************
 */

#ifndef APOMPRIM_HEADER__
#define APOMPRIM_HEADER__

/* Imports */
#include "../../dduos/include/dduos.h"
#include "../../../common/include/identify.h"

/* Definition of the primitives - used as SubEvent parameter */
#define APP_OM_SUBS_REMOVE_req 0x00

/* Definition of parameter in primitives */

/* Error parameter */
#define NoSubsRemoveError 0
#define InvalidUser   1

/* Definition of the primitive types */

/* APP_OM_SUBS_REMOVE */
typedef struct
{
    SignalType SignalHeader;      /* PMID in Address field */
    UByte LID;
}
AppOmSubsRemoveReqType;

typedef struct
{
    SignalType SignalHeader;      /* PMID in Address field */
}
AppOmLocatRegIndType;

#endif /* APOMPRIM_HEADER__ */
