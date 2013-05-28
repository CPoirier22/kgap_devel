/*
 ********************************************************************
 *
 * Module:  p_route.h
 *
 *  Config-item:  ?
 *
 * Contents:  Header file for Routing Table and their routines
 *
 *  Author: DDU
 *
 * Copyright Kirk Telecom A/S. All rights reserved.
 *
 * $Header:   K:/PH/140960xx/00/Archive/H/P_ROUTE.H_v   1.0   Oct 24 2002 11:51:06   mne  $
 *
 * $Log:   K:/PH/140960xx/00/Archive/H/P_ROUTE.H_v  $
 *
 *    Rev 1.0   Oct 24 2002 11:51:06   mne
 * Initial PP5 version for 428
 *
 *    Rev 1.5   23 Feb 1999 10:02:06   oo
 * File changed for PP2 HW. (Lucy).
 *
 *    Rev 1.4   Feb 17 1997 08:31:50   BJR
 * _CISS__: Changed MAXOWNERS to 4.
 *
 *    Rev 1.3   29 Feb 1996 11:27:44   BJR
 * Replaced inclusion of DDUOS.H with PDDUOS.H.
 *
 *    Rev 1.2   14 Nov 1995 15:49:26   BJR
 * Changes in relation to rewriting P_LCE.C.
 *
 *    Rev 1.1   26 Jan 1995 13:08:06   CB
 * Fileheader added
 *
 *    Rev 1.0   20 Jan 1995 12:55:06   CB
 * Initial version
 *
 ********************************************************************
 */

#ifndef P_ROUTE_H__
#define P_ROUTE_H__

#include "../../../../common/include/identify.h"
#include "../../../nwk/include/pp/plce.h"
#include "../../../dduos/include/dduos.h"

/*************************** LAPC INSTANCE *********************************/
#define MAXOWNERS 4             /* 1*CC + 2*MM + 1*CISS */

#define FreeFlag 0xFF

/* LAPCInstance is the entries in the routing table (in the PP there is only one entry). */
struct LAPCInstanceStructPP
{
    DLEIType DLEI;                /* Identifies the link. */
    UByte State;                  /* Link state for lapc */
    UByte TIPD[MAXOWNERS];        /* List of link owners. The empty places are always last in the array.
                                               The first empty place (if any) is marked with a FreeFlag */
    UByte OwnerOfLCE02;           /* TI-PD of higher layer entity that have started timer LCE02 */
    UByte CallAttrib[6];          /* Only room for default call attrib. */
    TimerType *Timer;
};
typedef struct LAPCInstanceStructPP LAPCInstanceTypePP;

/* link states for lapc */
#define LINK_RELEASED       0
#define LINK_ESTABLISHED    1
#define ESTABLISH_PENDING   2
#define RELEASE_PENDING     3
#define LINK_SUSPEND        4   /* Not used in this version (Class B not supported) */
#define SUSPEND_PENDING     5   /* Not used in this version (Class B not supported) */
#define RESUME_PENDING      6   /* Not used in this version (Class B not supported) */

typedef enum
{ Ok,
  LinkOutOfUse,
  NotFound,
  UnknownError
} RouteResultType;

void PLCE_LINK_INIT(void);

void PGET_LINK_INSTANCE_DATA(LAPCInstanceTypePP ** LAPCInstance);

void PLCE_LINK_RESERVE(XXEIType XXEI, DLEIType DLEI, LAPCInstanceTypePP ** LAPCInstance);

void PLCE_LINK_PAGE(DLEIType DLEI, LAPCInstanceTypePP ** LAPCInstance);

void PDOWN_ROUTE(SignalType * Signal, LAPCInstanceTypePP ** LAPCInstance);

void PROUTE_UP(SignalType * Signal, LAPCInstanceTypePP ** LAPCInstance);

RouteResultType PLCE_LINK_RELEASE(XXEIType XXEI, LAPCInstanceTypePP ** LAPCInstance);

RouteResultType PLCE_LINK_MAINTAIN(XXEIType XXEI, LAPCInstanceTypePP ** LAPCInstance);

#endif /* P_ROUTE_H__ */
