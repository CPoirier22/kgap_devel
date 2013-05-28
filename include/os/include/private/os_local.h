#ifndef __OS_LOCAL_H
#define __OS_LOCAL_H
/******************************************************************************
* Project   : DECT                                                            *
* Module    : Operating system                                                *
* Reference : Modulespecification for the Operating system                    *
* Type      : Headerfile for internal data structures for the Operating System*
* Function  :                                                                 *
* Systems   : Base,Handset                                                    *
*-----------------------------------------------------------------------------*
* Copyright (c) 1994 by RTX Research Aps.                                     *
* $Header:   K:/ph/srclib/os/variant/archive/h/OS_LOCAL.H_V   1.1.1.1   May 06 2003 13:08:28   on  $ *
******************************************************************************/

#include "../../../common/include/rtxdef.h"
#include "../tasks.h"

typedef struct LinkedElementStruct
{
    struct LinkedElementStruct *Next;
}
LinkedElementType;

typedef struct PP_RTC_Struct
{
    uint32 TimeGuard;
    uint32 UP_Time;
    uint32 Time_ms;
    uint32 Date;
    uint32 DateGuard;
}
PP_RTC_Type;

/* local constants */
#define ENDOFLIST 0xff
#define ENDOFTIMERLIST 0xff
#define TIMER_RUN_OUT  0xfd
#define STOPPED  0xfe

/* local variables */
extern volatile uint16 SystemTick;  /* Incremented by timer interrupt in target system */
extern BYTE NewMailSize;
extern BYTE FirstTimerIndex;

extern TaskIdType CurrentTask;
typedef void *VoidPtr;

extern volatile uint16 SystemTick;
extern uint16 FreeRunCounter;

#endif
