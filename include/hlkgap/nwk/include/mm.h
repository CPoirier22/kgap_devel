/*
 ********************************************************************
 *
 * Module: mm.h
 *
 * Config-item: ?
 *
 * Contents: This is a common header file for both the fixed part
 *     MM signal handler and the portable part MM signal handler
 *
 * Author: DDU
 *
 * Copyright Kirk Telecom A/S. All rights reserved.
 ********************************************************************
 */

#ifndef MM_HEADER__
#define MM_HEADER__

#include "../../dduos/include/dduos.h"
#include "../../../common/include/identify.h"
#include "../../util/include/bintree.h"

/* MMTimers */
#define TIMER_MM_ACCESS1     0x00    /* PT: MM_ACCESS_RIGHTS timer */
#define TIMER_MM_ACCESS2     0x01    /* Both: MM_ACCESS_TERMINATE timer */
#define TIMER_MM_AUTH1   0x02    /* Both: MM_AUTHENTICATION */
#define TIMER_MM_AUTH2   0x03    /* Both: MM_USER_AUTHENTICATION */
#define TIMER_MM_CIPHER1        0x04    /* FT: Cipher timer */
#define TIMER_MM_CIPHER2        0x05    /* PT: Cipher timer */
#define TIMER_MM_LOCATE      0x06    /* PT: MM loacte timer */
#define TIMER_MM_IDENT1   0x07    /* FT: Temporary-Identity-Assign */
#define TIMER_MM_IDENT2   0x08    /* FT: Identity-Request */
#define TIMER_MM_KEY1   0x09    /* FT: Key-Allocate */

/* Defined for MMUtil.c as return value from CheckParameters, */
#define NotRejected  0x00    /* with no reject value. Internal use only */
#define MMWaitRunning 0x99    /* also for internal use only */
#define MMNotSupported  0x98    /* also for internal use only */

extern BinTreeTopType MMEncryptLinkTreeTop;

struct SubInstance
{
    /* UByte   MMProcedureID;*//* Which MM procedure is running */
    UByte MMState;          /* Which state the procedure has */
    UByte TIPD;                   /* FT or PT initiated and priority */
    TimerType *TimerPointer;      /* Pointer to running timer */
    SignalType *QuePointer;       /* Any qued message */
};
typedef struct SubInstance SubInstanceType;

struct MMInstanceStruct
{
    XXEIType MMInstanceId;        /* TI + PD + <PMID | USN> */
    SubInstanceType FirstSubInstance;     /* Max two instances of MM pr. call */
    SubInstanceType SecondSubInstance;
    Boolean Level1InFirstSubInstance;
};
typedef struct MMInstanceStruct MMInstanceType;

enum CreateList                 /* States in the Call Control protocol entity */
{
    Reject = 0,
    Create1,
    Create2
};
typedef enum CreateList CreateType;
extern BinTreeTopType MMTreeTop;

#define IdleState 0

#endif /* MM_HEADER__ */
