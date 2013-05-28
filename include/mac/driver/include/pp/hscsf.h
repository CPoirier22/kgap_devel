
#ifndef __HSCSF_H
#define __HSCSF_H
/**************************************************************************
* Project   : DECT                                                        *
* Module    : Handset CellSiteFunction task                               *
* Reference :                                                             *
* Type      : Task                                                        *
* Function  :                                                             *
* Systems   : Handset                                                     *
*-------------------------------------------------------------------------*
* Copyright (c) 1998 by RTX Research A/S.                                 *
* $Header:   K:/PH/140960xx/00/Archive/H/hscsf.h_v   1.0   Oct 24 2002 11:51:24   mne  $ *
**************************************************************************/

/*#define POSITION_APP	// Fast RSSI scan. 260606 MAJ*/

#ifdef POSITION_APP

#define POSITION_DEPLOY 200 /* No. of results, NOT bytes. MAJ 190606. */


/*Used for debug HDM 07-09-2006*/
#define BMCfastScanBuild		/*"1" used for debug. disable scan routine build in bmc when NOT defined. MAJ 150806*/
#define BMCfastScanRemove		/*"2" used for debug. disable scan routine remove in bmc when NOT defined. MAJ 150806*/
#define RSSISCANINTswitch		/*"3" used for debug. disable RSSI scan interrupt switch when NOT defined. MAJ 150806*/
#define RSSISCANconsiderations		/*"4" used for debug. disable RSSI scan in buildRx/buildTx/buildIdle when NOT defined. MAJ 150806*/
#define RSSISCANinterrupt		/*"5" used for debug.*/
#define RSSISCAN_FAST_RSSI_SCAN_END		/*"6" used for debug. */


#define POSITION_TIMER 	/*kan ikke fjernes sammen uden UserApp og usertask*/
#define POSITION_UserApp	/*kan ikke fjernes sammen uden usertask og TIMER*/
#define POSITION_usertask	/*kan ikke fjernes sammen uden UserApp og TIMER*/


#define POSITION_hsccf
#define POSITION_hscsf
#define POSITION_BMC
#define POSITION_MSF




#define LIMIT_DataInMSF 100
#define LIMIT_NoOfValues (LIMIT_DataInMSF/sizeof(AlarmKeyElementType))
#define LIMIT_TimeBetweenSearch 30	/* time to sent the MSF (in sec.). MAJ 150806*/
#define START_SCAN_DELAY (100*T10_MS)	/* time to sent initial respons. MAJ 150806*/

/*								   FEDCBA9876543210*/
#define ODDSCAN_MASK  0x0AAA	/* 0000101010101010*/
#define EVENSCAN_MASK 0x0555	/* 0000010101010101*/
#define SCAN_MASK 	  0x0FFF	/* 0000111111111111*/

typedef enum {
	   			NOT_ACTIVE_STATE = 0,	 /* scan routine not active. MAJ 170806*/
	  			WAIT_ODDSCAN_STATE,	  /* wait scan routine started. wait for frame 8 to be done. MAJ 170806*/
	  			ODDSCAN_STATE,	  /* scan odd slots. MAJ 170806*/
	  			WAIT_EVENSCAN_STATE,	  /* wait for frame 8 to be done. MAJ 170806*/
	  			EVENSCAN_STATE,	  /* scan even slots. MAJ 170806*/
             } RSSIScannStateType;

typedef enum {
	   			OUT_OF_LOCK,	 /* PP is out of lock.*/
	  			IN_LOCK,	  /* PP in lock.*/
             } PositionLockStateType;

typedef enum {
	  			IDLE,  /* search routine not active.*/
	  			INIT_SCAN,	/* init new scan.*/
	  			END_OF_SCAN,
	  			WAIT_FOR_MSFTX,
	  			SCAN_AGAIN
             } PositionSearchStateType;

typedef enum {
				STOP_SEARCH = 0x00,
				START_INFINITE_SEARCH = 0x01,
				START_FINITE_SEARCH = 0x02,
				START_MULTISCAN = 0x03,

#ifdef POSITION_DEPLOY
				START_DEPLOY_SCAN = 0xF0,
#endif
             } PositionSearchModeType;
#endif

#ifdef POSITION_APP
extern BYTE FastRSSIScanEnded;
extern BYTE FastRSSITimer;
extern BYTE PPLockedStartTimer;

extern PositionLockStateType PositionLockState;
extern PositionSearchStateType PositionSearchState;
extern PositionSearchModeType PositionSearchMode;
extern BYTE PPInLock;
extern PositionSearchModeType EnableSearch;
extern BYTE TimeBetweenSearch;
extern BYTE NoOfSearch;
extern unsigned int NoOfValues;
extern BYTE MultiScanTime;
extern WORD MultiScanCounter;

extern BYTE RSSIscanSent;
#endif


#define TESTCMD_ENTER_TESTMODE  0x01
#define TESTCMD_EXIT_TESTMODE   0x02
#define TESTCMD_SET_COMPERATOR  0x03
#define TESTCMD_WARMSTART       0x04
#define TESTCMD_FREQUNCY_SHIFT  0x05
#define TESTCMD_CONT_RX_QUAD_TRACK 0x06

#define TESTCMD_STARTLOGRXFRAME 0x99
#endif

