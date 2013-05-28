/*
 ********************************************************************
 *
 * Module:  mm.h
 *
 *  Config-item:  ?
 *
 * Contents:  This is a common header file for both the fixed part
 *          MM signal handler and the portable part MM signal handler
 *
 *  Author: DDU
 *
 * Copyright Kirk Telecom A/S. All rights reserved.
 *
 * $Header:   K:/PH/140960xx/00/Archive/H/MM.H_v   1.0   Oct 24 2002 11:51:02   mne  $
 *
 * $Log:   K:/PH/140960xx/00/Archive/H/MM.H_v  $
 *
 *    Rev 1.0   Oct 24 2002 11:51:02   mne
 * Initial PP5 version for 428
 *
 *    Rev 1.14   23 Feb 1999 10:02:12   oo
 * File changed for PP2 HW. (Lucy).
 *
 *    Rev 1.13   May 02 1997 17:19:08   BJR
 * FIXED_PART__: Added MMEncryptLinkTreeTop.
 *
 *    Rev 1.12   Jan 24 1997 14:49:20   BJR
 * Removed timers TIMER_MM_ACCESS_WAIT and TIMER_MM_LOCATE_WAIT (<MM_WAIT>). Was not used in FIXED_PART__.
 *
 *    Rev 1.11   Dec 17 1996 18:14:30   BJR
 * Removed FT_AUTHENTICATE_res_State.
 *
 *    Rev 1.10   Oct 31 1996 12:41:58   BJR
 * PORTABLE_PART__: Removed LocatePendingState.
 *
 *    Rev 1.9   Sep 02 1996 17:04:50   BJR
 * FIXED_PART__: Corrected NumberOfMMStates.
 *
 *    Rev 1.8   Sep 02 1996 10:12:10   BJR
 * PORTABLE_PART__: Added MMCipherRequestState to MMStateList.
 * FIXED_PART__: Added CIPHER_REQUEST_State to MMStateType.
 *
 *    Rev 1.7   Jul 18 1996 15:58:30   BJR
 * Replaced far with far__. Added Level1InFirstSubInstance to MM instance data.
 *
 *    Rev 1.6   Jun 28 1996 11:46:52   MK
 * MMTreeTop declared far.
 *
 *    Rev 1.5   29 Feb 1996 12:27:40   BJR
 * PORTABLE_PART__: Replaced inclusion of DDUOS.H with PDDUOS.H.
 *
 *    Rev 1.4   15 Dec 1995 11:23:32   BJR
 * PORTABLE_PART__: Removed the state MM_FT_Authenticate.
 *
 *    Rev 1.3   11 Dec 1995 11:38:16   BJR
 * FIXED_PART: Brought consistens to the state names.
 *
 *    Rev 1.2   27 Jan 1995 10:43:48   CB
 * Syntax error corrected
 *
 *    Rev 1.1   26 Jan 1995 13:08:00   CB
 * Fileheader added
 *
 *    Rev 1.0   20 Jan 1995 11:44:06   CB
 * Initial version
 *
 ********************************************************************
 */

#ifndef PMM_HEADER__
#define PMM_HEADER__

#include "../mm.h"

#define MMAccess1   6000        /*  60s */
#define MMAccess2   2000        /*  20s */
#define MMAuth1   1000          /*  10s */
#define MMAuth2    10000        /* 100s */
#define MMCipher2   1000        /*  10s */
#define MMLocate    2000        /*  20s */
#define MMWait     30000        /* 300s */

enum MMStateList
{
    LCEResourceReserveState = 1,      /* 1 */
    MMIdentityRequestState,       /* 2 */
    MMTpuiAssignmentState,        /* 3 */
    MMAuthenticateState,          /* 4 */
    MMUserAuthenticateState,      /* 5 */
    LocateReplyState,             /* 6 */
    AccessRightsReplyState,       /* 7 */
    AccessRightsTerminateReplyState,      /* 8 */
    MMAccessRightsTerminateState, /* 9 */
    MMKeyAllocateState,           /* A */
    MMKeyAllocateReplyState,      /* B */
    MMCipherRequestState,         /* C */

    /* Order is of special importans here after. Used in MMUtil.c */
    LCEResourceReserveStateLevel1,        /* E *//* Only for level one procedurer */
    AuthenticateReplyState        /* F *//* Only for level one procedurer */
};
typedef enum MMStateList MMStateType;
#define NumberOfMMStates    16

#endif /* PMM_HEADER__ */
