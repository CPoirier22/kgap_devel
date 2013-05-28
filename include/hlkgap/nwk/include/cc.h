/*
 ********************************************************************
 *
 * Module: cc.h
 *
 * Config-item: ?
 *
 * Contents: This is a common header file for both the fixed part
 *     CC signal handler and the portable part CC signal handler
 *
 * Author: DDU
 *
 * Copyright Kirk Telecom A/S. All rights reserved.
 ********************************************************************
 */

#ifndef CC_HEADER__
#define CC_HEADER__

#include "../../dduos/include/dduos.h"
#include "../../../common/include/identify.h"

#define IncomingCall    0       /* Constant in CallType */
#define OutgoingCall    1       /* Constant in CallType */

#define UndefinedSendingMethod  0       /* Constant in SendingMethod */
#define EnblocSendingMethod     1       /* Constant in SendingMethod */
#define KeypadSendingMethod     2       /* Constant in SendingMethod */

#define CC_01_TIMER    1
#define CC_02_TIMER    2
#define CC_03_TIMER    3
#define CC_04_TIMER    4
#define CC_05_TIMER    5
#define ME_U_PLANE_TIMER  7

#define CC_01_TIMEOUT_VALUE   2000    /* 20 s */
#define CC_02_TIMEOUT_VALUE     3600    /* 36 s */
#define CC_03_TIMEOUT_VALUE     2000    /* 20 s */
#define CC_04_TIMEOUT_VALUE     10000   /* 100 s */
#define CC_05_TIMEOUT_VALUE     1000    /* 10 s */
#define U_PLANE_TIMEOUT_VALUE   200     /* 2 s */
#define RestartTimer   0       /* indicates restart of timer */


enum CCStateList                /* States in the Call Control protocol entity */
{
    NullState = 0,
    LceResourceReservePendingState,
    WaitLceResourceReserveCfmState,
    CallInitiatedState,
    OverlapSendingState,
    CallProceedingState,
    CallDeliveredState,
    CallPresentState,
    CallReceivedState,
    ConnectPendingState,
    WaitMeUPlaneResState,
    ActiveState,
    ReleasePendingState,
    ReleasePendingBothSidesState,
    ReverseReleasePendingState,
    NumberOfCCStates
};
typedef enum CCStateList CCStateType;

struct CCProcessStruct
{
    XXEIType CCInstanceId;        /* TI + PD + <PMID | USN> */
    CCStateType CCState;          /* State of CC */
    UByte CallType;               /* Indicates whether the call is incoming or outgoing */
    UByte SendingMethod;          /* Indicates the used method of sending B-number */
    Boolean UPlaneInstalled;      /* Indicates whether U-plane is installed or not */
    Boolean RestoreCCQueueInProgress;     /* Indicates whether a restore of CC internal
                                                       queue is in progress. Meanwhile must the
                                                       the instance not be deleted */
    Boolean AirReleaseDone;       /* Indicates whether a CC has finished release
                                               procedure on the air interface */
    Boolean IwuReleaseDone;       /* Indicates whether a CC has finished release
                                               procedure on the IWU interface */
    SignalType *CCQueuePointer;   /* Pointer to CC internal queue */
    TimerType *CCTimer;           /* Pointer to CC timer */
    LIDType Lid;                  /* The LID */
};
typedef struct CCProcessStruct CCProcessType;

typedef void (*StateFunctionType) (SignalType * TheSignal, CCProcessType * CCProcessInstance);

#ifndef CC_THE_MODULE__

extern void CCSignalHandler(SignalType * TheSignal);

#endif /* CC_THE_MODULE__ */

#endif /* CC_HEADER__ */
