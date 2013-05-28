#ifndef __FPSYNC_H
#define __FPSYNC_H
/*****************************************************************************
* Project   : DECT                                                           *
* Module    : Fixed part synchronization                                     *
* Reference :                                                                *
* Type      : Headerfile for FP synchronization module                       *
* Function  :                                                                *
* Systems   : Base                                                           *
*----------------------------------------------------------------------------*
* Copyright (c) 2003 by RTX Telecom A/S.                                     *
* $Header:   xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx  $ *
*****************************************************************************/

#include "../../../../common/include/bitsdef.h"

extern void FpSyncInitialSearchHandler(void);
extern void FpSyncBroadcastRxHandler(BYTE NewChannel);
extern void FpSyncEndOfFrameHandler(void);

extern BYTE RxSearchMode;
extern BYTE LockedChannelFP;
extern BYTE RearrangeSlot;

#define OTHERBASETABLESIZE (0x9B+1) /* 155 = (10 freq=9) , (12 chan=B)*/

#ifdef OTHERBASES
typedef struct
{
    BYTE Rssi;
    BYTE LifeTime;
}
UsedChType;
#endif

typedef struct {
  BYTE Chan;
  BYTE Rssi;
  BYTE LifeTime;
  unsigned long LockedFPNumber;
  BYTE CorrectEMC;
  BYTE DummyInfo;
  BYTE LifeTimeDummy;
}HandOverMapFPType;
#define GOOD_RSSI 20
#define FREQUENCY_ADJUST_5 0x05
#define FREQUENCY_ADJUST_20 0x0A
#define FREQUENCY_ADJUST_DELAY 100
#define FREQUENCY_CHANGE_TIME 600

#ifdef __FPSYNC__
  #ifdef OTHERBASES
  HandOverMapFPType OtherBasesFP[OTHERBASETABLESIZE];
  UsedChType UsedCh[10][12];
  #endif

  /*Pointers to PRIMARY / SECUNDARY dummy bearer (or trafic, if dummy not seen)*/
  #ifdef OTHERBASES
  HandOverMapFPType * PriOtherBase = OtherBasesFP+0x0c; /* Ptr set to known unused area*/
  HandOverMapFPType * SecOtherBase = OtherBasesFP+0x0c;
  #endif

  BOOLEAN FlagSendOtherBaseList=0;
#else
  extern void OtherBaseTime2Live(void);
  extern void UsedChTime2Live(void);
  #ifdef OTHERBASES
  extern HandOverMapFPType OtherBasesFP[OTHERBASETABLESIZE];
  extern UsedChType UsedCh[10][12];
  #endif
  extern BOOLEAN FlagSendOtherBaseList;
#endif
#endif
