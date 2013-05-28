/*****************************************************************************
* Project   : DECT
* Module    :
* Reference :
* Type      : Header file.
* Function  :
* Systems   : Handset
*----------------------------------------------------------------------------
* Copyright (c) 1998 by RTX Telecom.
* $Header:   K:/PH/140211xx/source/os_ext.h_v   1.3   May 06 2003 13:06:14   on  $
*****************************************************************************/
#ifndef __OS_EXT_H
#define __OS_EXT_H

#include "../../../common/include/bitsdef.h"

/***********************************************************************\
  Defines
\***********************************************************************/

#define _T1_MS     1
#define _T2_MS     2
#define _T5_MS     5        /* Timer-constant for waiting 5 ms           */
#define _T10_MS    10       /* Timer-constant for waiting 10 ms          */
#define _T100_MS   100      /* Timer-constant for waiting 100 ms         */
#define _T1_SEC    1000     /* Timer-constant for waiting 1 second       */
#define _T10_SEC   10000    /* Timer-constant for waiting 10 seconds     */

#define M_TIMERID_INTERRUPTCALL 0x80

/***********************************************************************\
  Types
\***********************************************************************/

typedef void (*OsTimerCallBackFnType)(void);

/***********************************************************************\
  Variables
\***********************************************************************/


/***********************************************************************\
  Prototypes
\***********************************************************************/

void NONBANKED InitHighResTimerSystem(void);
void NONBANKED InitFastTimerSystem(void);
INTERRUPT void NONBANKED HighResTimerInterrupt(void);
INTERRUPT void NONBANKED FastTimerInterrupt(void);
void NONBANKED StartHighResTimer(BYTE TimerId, WORD Time, OsTimerCallBackFnType CallBackFn);
void NONBANKED StopHighResTimer(BYTE TimerId);
void NONBANKED RunHighResTimerSystem(void);

void NONBANKED SuspendHighResTimer(BYTE TimerId);
void NONBANKED ResumeHighResTimer(BYTE TimerId);

extern void RunKernelIdle(void);



#endif
