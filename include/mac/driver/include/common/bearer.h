/*
 ********************************************************************
 *
 * Module:  bearerp.h
 *
 *  Config-item:  ?
 *
 * Contents:  This is the header file for BEARERP.C.
 *
 *  Author:
 *
 * Copyright Kirk Telecom A/S. All rights reserved.
 *
 ********************************************************************
 */

#ifndef __BEARER_H
#define __BEARER_H

#include "../../../../common/include/_stddef.h"
#include "../../../../common/include/rtxdef.h"

typedef enum
{
    SLOTSTATENULL=0x00,
    SLOTSTATE1,
    SLOTSTATE2,
    SLOTSTATE3,
    SLOTSTATE4,
    SLOTSTATE5,
    SLOTSTATE6,
    SLOTSTATE7,
    SLOTSTATE8,
    SLOTSTATE9,
    SLOTSTATE10,
    SLOTSTATE11,
    SLOTSTATE12,
    SLOTSTATE13,
    SLOTSTATE14,
    SLOTSTATE15,
    SLOTSTATE16,
    SLOTSTATE17,
    SLOTSTATE18,
    SLOTSTATE19,
    SLOTSTATE20
} ENUM8(WaitForNextSlotJumpStates);

extern BYTE CurrentSlot;
extern BYTE ActiveBearers;
extern BYTE MacPark[5];
extern BYTE MacPliPP;
extern BYTE ParkCtrlFlagPP;

/* EEPROM LockMode flag */
#define LOWDUTYCYCLE_PATT  0x01
#define LOWCPUCLOCK_PATT   0x02
#define LOWSEARCHDUTY_PATT 0x04
#define EIWAIT_PATT 0x08

#endif
