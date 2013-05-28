#ifndef __HSCCF_H
#define __HSCCF_H

/***************************************************************************
 * Project   : DECT                                                        *
 * Module    : Handset HsCcf                                               *
 * Reference :                                                             *
 * Type      : Header file                                                 *
 * Function  :                                                             *
 * Systems   : Handset                                                     *
 *-------------------------------------------------------------------------*
 * Copyright (c) 2001 by KIRK telecom A/S, Denmark.                        *
 * $Header:   K:/PH/140960xx/00/Archive/H/HSCCF.H_v   1.2   22 Oct 2003 17:13:14   mne  $
 * $Log:   K:/PH/140960xx/00/Archive/H/HSCCF.H_v  $
 *
 *    Rev 1.2   22 Oct 2003 17:13:14   mne
 * Warnings removed no function change.
 *
 *    Rev 1.1   17 Sep 2003 08:14:00   mne
 * First release KEH put.
 *
 *    Rev 1.0   Oct 24 2002 11:50:50   mne
 * Initial PP5 version for 428
 *
 *    Rev 1.3.1.4   Oct 17 2001 16:07:50   oo
 * Structure and mac states moved from c-file to here.
 **************************************************************************/

#include "../../../../common/include/_stddef.h"
#include "../../../../os/include/maildef.h"

#define OTHERBASETABLESIZE 4
#define NUMBER_OF_SLOTS  12
#define NUMBER_OF_FREQ   10

typedef struct
{
    BYTE Channel;       /* OBS! Must be same order as BearerScanIndType*/
    BYTE Rssi;
    BYTE LifeTime;
    BYTE Rfpi[5];
}
HandOverMapPPType;

extern HandOverMapPPType *OtherBase;
extern HandOverMapPPType OtherBasesPP[OTHERBASETABLESIZE];


#ifdef POSITION_APP
extern void SendRSSITransferSimple(void);
extern void SendRSSITransferCompressed(void);

typedef struct {
      BYTE Rpn;
      BYTE Rssi;
         }ScanResultType;
         
#define SCANRESULTTYPE_SIZE 2/*sizeof(ScanResultType)*/

typedef struct {
	  BYTE Amount;
	  ScanResultType ScanResult[120];
		 }PositionScanResult_Type;

typedef struct {
      BYTE Rpn;
      BYTE Rssi;
      BYTE Amount;
         }ScanPackType;
         
#define SCANPACKTYPE_SIZE 3/*sizeof(ScanResultType)*/

typedef struct {
	  unsigned int PackAmount;
	  unsigned int DataAmount;
	  ScanPackType ScanPack[POSITION_DEPLOY];
		 }PositionScanPack_Type;

extern PositionScanPack_Type PositionScanPack;
extern RSSIScannStateType RSSIScannState;

extern BYTE StopScanFlag;
extern BYTE StopScanFlag1;
extern int StartScanTime;
extern int ScanTime;
extern int LastScanTime;
extern int ScanTimeOverrun;
extern WORD FreeRunCounter;
/*#define MAX_RESULT (sizeof(PositionScanResult.ScanResult)/ALARMKEYELEMENTTYPE_SIZE)*/
#endif

extern BYTE  HoTest;


extern BYTE ActionMonitorReg;

extern BYTE Locked2RfpiPP[5];

extern void ResetSariScan(void);
extern void RestartMacBmc(BYTE Reason);

#ifdef _BEST_BASES
extern BYTE RunFastRssiScanning;

#define BESTBASESTABLESIZE 50       /* LHJ 19/11-98*/
#define BEST_BASES_LIFETIME 15    /* 25 seconds lifetime in the BEST BASES table*/

typedef struct
{
    HandOverMapType BaseFound[BESTBASESTABLESIZE];
    /*   BYTE RssiIndex[BESTBASESTABLESIZE];*/
    BYTE RfpiInput[5];
    BYTE MaskInput;
    BYTE bNumberOfFoundBases;
    BYTE ActuelRfpi[5];
    BYTE OldBaseIndex;
    BYTE Semaphore;
}
BestBasesType;

#ifdef USERTASK_C__
extern void SortTheBestBases(void);
#else
extern BestBasesType *BestBases;
#endif

extern void ResetBestBases(void);

/* Free channel functions and data.*/
extern BYTE RssiTable[NUMBER_OF_SLOTS][NUMBER_OF_FREQ];       /* 12 slots, 10 frequencies.*/
extern void ResetRssiScanning(void);
extern BYTE GetFreeChannels(BYTE bMaxLevel, BYTE bMinLevel);

/* Rssi levels*/
#define MINUS_90_DBM  (150-90)
#define MINUS_85_DBM  (150-85)
#define MINUS_80_DBM  (150-80)
#define MINUS_75_DBM  (150-75)
#define MINUS_70_DBM  (150-70)
#define MINUS_65_DBM  (150-65)
#define MINUS_60_DBM  (150-60)
#endif /*_BEST_BASES*/



typedef enum /* 1 byte */
{
    MAC_UNLOCKED,         /* 0x00 */
    MAC_LOCKED,           /* 0x01 */
    MAC_CONNECTPENDING,   /* 0x02 */
    MAC_CONNECT,          /* 0x03 */
    MAC_HANDOVERPENDING,  /* 0x04 */
    MAC_HANDOVER          /* 0x05 */

}
Enum_MbcStateType;
typedef BYTE MbcStateType;



typedef struct
{
    BYTE UsedChannel,HoChannel;
    MbcStateType State;
    BYTE ReqDataSegmentNr;
    BYTE IndDataSegmentNr;
    BYTE BearerReqCount;
    BYTE EncStatus;
    BYTE CcfFlag;          /* Lower bits counts the number of active bearers and requests */
    BYTE Data[SDU_SIZE];
#ifdef HSCCF_QUALITY
    BYTE Quality;
    BYTE Rssi;
    BYTE HoQuality;
    BYTE HoRssi;
#endif
}
MacConnectionType;




#endif



