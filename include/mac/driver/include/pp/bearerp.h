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
 * $Header:   K:/PH/SRCLIB/PP5/BASIS/ARCHIVE/H/bearerp.h_v   1.2   23 Jan 2006 12:08:28   mne  $
 *
 * $Log:   K:/PH/SRCLIB/PP5/BASIS/ARCHIVE/H/bearerp.h_v  $
 *
 *    Rev 1.2   23 Jan 2006 12:08:28   mne
 * New Interrupt routine added, and Low Duty Cycle changed.
 *
 *    Rev 1.1   17 Sep 2003 08:11:02   mne
 * First release KEH put.
 *
 *    Rev 1.0   Oct 24 2002 11:51:10   mne
 * Initial PP5 version for 428
 *
 *    Rev 1.10   08 Jan 2001 11:16:16   oo
 * Parameters for new search routine with RFPI tabel added/changed.
 *
 *    Rev 1.9   13 Sep 1999 10:26:54   BJR
 * Added OldPSCN and OldPSCNInUse.
 * Added header.
 *
 ********************************************************************
 */

#ifndef __BEARERP_H
#define __BEARERP_H

#include "../../../../common/include/_stddef.h"
#include "../../../../common/include/rtxdef.h"
#include "../bmcdef.h"

typedef struct
{
/*    PPBearerRxDataType  __data16 *RxPtr;*/
/*    PPBearerTxDataType  __data16 *TxPtr;*/
    PPBearerRxDataType  *RxPtr;
    PPBearerTxDataType  *TxPtr;
    uint8            SlotJumpIndex;
    BYTE             Slot;
    BYTE             RfCarrier;
    BYTE             Cmd;
    BYTE             FmidPmid[4];
    BYTE             Rfpi[5];
    BYTE             Ctrl;
    BYTE             ConnectionTimer;
    BYTE             DiversityState;
    BYTE             Rssi_1;
    BYTE             Rssi_2;
    BYTE			 RxAudioSlot;
    BYTE 			 RxEncryptBuild;
}
SlotDataTypePP;      /* B?r flyttes til SlotSw module... */

typedef SlotDataTypePP SlotDataArrayTypePP[2];

typedef struct
{
    BYTE Pmid[3];
    BYTE RssiLevel;
    BYTE HOparm;
    BYTE Rfpi[5];
    BYTE DataReqSlot;
    BYTE DataSegmentNr;
    BYTE DataReqSegment[5];
}
BearerRequestParmType;

typedef struct
{
    BYTE Channel;
    BYTE Cmd;
}
BearerBuildRequestType;

typedef struct
{
    BYTE Rfpi[5];         /* rfpi*/
    BYTE ReceiveCount;    /* number of times received (Time to live)*/
}
SearchKnownRfpiType;

#define M_SEARCHFLG_RSSIADJ  0x04
#define SEARCH_FOUND_COUNT   10    /* number of times received in search before recheck for registration bit*/
#define M_SEARCHFLG_REG      0x02
#define CSF_SEARCH_ONLY_A44  1     /* 1=only search for base's with A44=1 ("Access Rights Requests" supported)*/


extern BYTE MacPmid[3];
extern BYTE RpnMask;
extern SearchKnownRfpiType *KnownRfpiPtr;
extern WORD ReceivePhasePP;

extern BYTE PrimRecvScanCarrierPP,PrimRecvScanCarrierPP_p2;

extern BYTE OldPSCN;
extern BYTE OldPSCNInUse;

extern BYTE FrameNumberPP;
extern BYTE MultiFrameNumberPP[3];
extern BYTE ScannedRfCarrier;
extern BYTE CurrentSdIndex;

extern BYTE Mac_T208,PpLockedTimer;
extern BYTE FrequencyCountPP;
extern BYTE LockedChannelPP;
extern WORD BlindSlotInfoPP;
extern BYTE HighDutyCycleCount;
extern BYTE DisablePhaseAdjustCntPP;
extern SlotDataArrayTypePP SlotDataPP;
extern SlotDataTypePP *SdPtrPP;  /* Slot data pointer */
extern BYTE AudioControlFifo[8];
extern BYTE AudioControlWri,AudioControlRdi;


extern BYTE HandOverInfo;
extern BYTE HandOverMask;



extern BYTE FPCapabilities[5];
extern BYTE ExtendedFPCapabilities[5];
extern WORD RfCarrierAvailInfoPP;

extern BYTE Locked2RfpiPP[5];
extern BearerRequestParmType BearerRequestParm;

extern BearerBuildRequestType BearerBuildRequest[2];

extern void BearerControllerPP(void);
extern void UpdatePrimRecvScanCarrierPP(void);
extern void EndOfFrameHandlerPP(void);

#define LOOPBACK_PATT 0x80
#define KNOWN_RFPI_NO 25
#endif
