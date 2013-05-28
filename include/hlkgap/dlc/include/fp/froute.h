/*
 ********************************************************************
 *
 * Module: f_route.h
 *
 * Config-item: ?
 *
 * Contents: Header file for Routing Table and their routines
 *
 * Author: DDU
 *
 * Copyright Kirk Telecom A/S. All rights reserved.
 ********************************************************************
 */

#ifndef F_ROUTE_H__
#define F_ROUTE_H__

#include "../../../../common/include/identify.h"
#include "../../../dduos/include/dduos.h"
#include "../../../nwk/include/fp/flce.h"
#include "../../../common/include/sformat.h"

/*************************** LAPC INSTANCE *********************************/
#define MAXOWNERS 4             /* 2*CC; 2*MM; */
#define FreeFlag 0xFF

/* LAPCInstance is the entries in the routing table (LCETreeTop). */
struct LAPCInstanceStructFP
{
    DLEIType DLEI;                /* Identifies the link. Is used as address in the routing table
                                               tree (LCETreeTop). Only PMID part of DLEI is used as address
                                               in the tree */
    UByte State;                  /* Link state for lapc */
    UByte TIPD[MAXOWNERS];        /* List of link owners. The empty places are always last in the
                                               array. The first empty place (if any) is marked with a
                                               FreeFlag */
    UByte OwnerOfLCE02;           /* TI-PD of higher layer entity that have started timer LCE02 */
    UByte CallAttrib[6];          /* Only room for default call attrib. */
    TimerType *Timer;
    PortableIdentityType Ipui;    /* Used for paging */
    UByte RetryCount;             /* Used for paging */
    SignalType *LCEPrimitiveQueueFront;   /* Primitives from higher layer entities are queued while in */
    SignalType *LCEPrimitiveQueueBack;    /* RELEASE-PENDING state */
};

typedef struct LAPCInstanceStructFP LAPCInstanceTypeFP;

/* link states for lapc */
#define LINK_RELEASED       00  /* Waiting for IPUI from DB */
#define LINK_ESTABLISHED    01
#define ESTABLISH_PENDING   02
#define RELEASE_PENDING     03
#define LINK_SUSPEND        04  /* Not used in this version (Class B not supported) */
#define SUSPEND_PENDING     05  /* Not used in this version (Class B not supported) */
#define RESUME_PENDING      06  /* Not used in this version (Class B not supported) */

typedef enum
{ Ok,
  NewLink,
  LinkOutOfUse,
  LinkReset,
  NotFound,
  MemAllocError,
  UnknownError
} RouteResultType;

void FLCE_LINK_INIT(void);

RouteResultType FGET_LINK_INSTANCE_DATA(DLEIType DLEI, LAPCInstanceTypeFP ** LAPCInstance);

RouteResultType FLCE_LINK_RESERVE(XXEIType XXEI, DLEIType DLEI, LAPCInstanceTypeFP ** LAPCInstance);

RouteResultType LCE_LINK_ESTABLISHED(SignalType * Signal, LAPCInstanceTypeFP ** LAPCInstance);

RouteResultType FLCE_LINK_PAGE(PMIDType PMID, LAPCInstanceTypeFP ** LAPCInstance);

RouteResultType FDOWN_ROUTE(SignalType * Signal, LAPCInstanceTypeFP ** LAPCInstance);

RouteResultType FROUTE_UP(SignalType * Signal, LAPCInstanceTypeFP ** LAPCInstance);

RouteResultType FLCE_LINK_RELEASE(XXEIType XXEI, LAPCInstanceTypeFP ** LAPCInstance);

RouteResultType FLCE_LINK_MAINTAIN(XXEIType XXEI, LAPCInstanceTypeFP ** LAPCInstance);

RouteResultType LCE_LINK_RELEASED(DLEIType DLEI);

#endif /* F_ROUTE_H__ */
