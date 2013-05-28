/*
 ********************************************************************
 *
 * Module:  lapc.h
 *
 *  Config-item:  ?
 *
 * Contents:  This file contains the general LAPC definitions and
 *          structures. It also includes the necessary modules used by
 *          LAPC.
 *
 *  Author: DDU
 *
 * Copyright Kirk Telecom A/S. All rights reserved.
 ********************************************************************
 */

#ifndef PLAPC_HEADER__
#define PLAPC_HEADER__
#include "../../../dduos/include/dduos.h"
#include "../../../../common/include/identify.h"
#include "../../../util/include/bintree.h"

#define DL_04_Cs_TIME_OUT_VALUE   204
#define DL_07_TIME_OUT_VALUE    200

enum ClassAStateSet
{
    AOpenPending = 0,
    AActive, APendingCfm = 2
};

struct LAPCProcessStruct
{
    DLEIType LAPCInstanceId;      /* BCF + LCN + <PMID | USN> */
    void *ClassPointer;
    UByte Lsig[2];
};
typedef struct LAPCProcessStruct LAPCProcessType;

extern BinTreeTopType LAPCTreeTop;

extern void PInitializeLAPC(void);
extern void LAPCSignalHandler(SignalType * TheSignal);
#endif /* PLAPC_HEADER__ */
