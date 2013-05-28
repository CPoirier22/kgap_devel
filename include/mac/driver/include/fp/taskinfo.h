#ifndef __TASKINFO_H
#define __TASKINFO_H
/****************************************************************************
* Project   : DECT                                                          *
* Module    : General, Task information module                              *
* Reference :                                                               *
* Type      : Header file                                                   *
* Function  :                                                               *
* Systems   : Base,Handset                                                  *
*---------------------------------------------------------------------------*
* Copyright (c) 1995 by RTX Research Aps.                                   *
* $Header:   K:/PH/SRCLIB/OS/VARIANT/ARCHIVE/H/TASKINFO.H_v   1.2   23 Feb 1999 10:12:40   oo  $ *
****************************************************************************/

#define DONTCARE 0xfffe
#include "../../../../os/include/tasks.h"

typedef struct
{
    BYTE       Abbreviation[3];
    TaskIdType TaskId;
}
TaskDescType;

typedef struct
{
    BYTE       Abbreviation[30];
    TaskIdType TimerId;
    BYTE       TaskWinRow;
}
TimerDescType;

#define TASK_DISPLAY_OFF  0
#define TASK_DISPLAY_COL1 1
#define TASK_DISPLAY_COL2 2

typedef struct
{
    char Symbol[20];
    WORD Value;
    int  column;
}
SymbolDefType;


#if defined(__M16C__) && !defined(__TURBOC__)
#pragma memory=constseg(FAR_CONST):far
#endif

extern const TaskDescType TaskDescription[];
extern const TimerDescType TimerDescription[];
extern const SymbolDefType SymbolDef[];

#if defined(__M16C__) && !defined(__TURBOC__)
#pragma memory=default
#endif

#ifdef __NOWARNINGS__
#pragma warnings=off
#endif

#endif
