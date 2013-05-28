/**************************************************************************
 * Project   : DECT PP5                                                   *
 * Module    : DIP Program Labels                                         *
 * Reference :                                                            *
 * Type      :                                                            *
 * Function  :                                                            *
 * Systems   : Handset                                                    *
 *------------------------------------------------------------------------*
 * Copyright (c) 2002 by KIRK telecom A/S.                                *
 *                                                                        *
 * $Header:   K:/PH/SRCLIB/PP5/BASIS/ARCHIVE/H/BMC_Labels.h_v   1.3   07 Sep 2005 09:28:14   mne  $                                                               *
 *                                                                        *
 * $Log:   K:/PH/SRCLIB/PP5/BASIS/ARCHIVE/H/BMC_Labels.h_v  $                                                                  *
 *
 *    Rev 1.3   07 Sep 2005 09:28:14   mne
 * New functions for 1g9 USA Syntese added.
 *
 *    Rev 1.2   11 Feb 2005 13:56:28   MNE
 * #ifdef _LMX4168_ changed to #ifdef _LMX4169_
 * Unused code removed.
 *
 *    Rev 1.1   11 Aug 2004 13:00:02   MNE
 * Now possible to comp. National or Infineon.
 *
 *    Rev 1.0   17 Sep 2003 09:16:04   mne
 * First release KEH put.
 **************************************************************************/

extern const WORD LBL_FrameBegin;
extern const WORD LBL_Slot0_PP;
extern const WORD LBL_Slot13;
extern const WORD LBL_SlotEnd;
extern const WORD LBL_AudioCtr;
extern const WORD LBL_IdleSlot;
extern const WORD LBL_SuspendProg;
extern const WORD LBL_SenduWireOn0;
extern const WORD LBL_LoadBmcCtrl;
extern const WORD LBL_StartTx_PP;
extern const WORD LBL_StartTxEnc;
extern const WORD LBL_SyntAlternating;
extern const WORD LBL_StartRx_PP;
extern const WORD LBL_StartRxB1;
extern const WORD LBL_StartRxEnc;
extern const WORD LBL_XcalcSub;
extern const WORD LBL_RxBXZ;
extern const WORD LBL_RxBXZLong;
extern const WORD LBL_TxBXZLong;
extern const WORD LBL_TxLongSlot;
extern const WORD LBL_RxLongSlot;
extern const WORD LBL_SaveEncStatus;
extern const WORD LBL_RxLastField;
extern const WORD LBL_RxE1;

extern const WORD LBL_RxABp0;
extern const WORD LBL_RxABp1;
extern const WORD LBL_RxBfieldWait;
extern const WORD LBL_DoRxAfield;
extern const WORD LBL_DoRxInTxField;
extern const WORD LBL_CmdEnSlAdj;
extern const WORD LBL_RxBXcalc;
extern const WORD LBL_RxE1;
extern const WORD LBL_RxinTxE0;
extern const WORD LBL_RxinTxE1;

extern const WORD LBL_TxABp0;
extern const WORD LBL_TxABp1;

extern const WORD LBL_TxAfieldOnly;
extern const WORD LBL_TxBXZ;
extern const WORD LBL_TxXZ;
extern const WORD LBL_TxXZ1;
extern const WORD LBL_TxBXcalc;

extern const WORD LBL_SearchNxFreq_PP;
extern const WORD LBL_SearchSync;
extern const WORD LBL_NextSearch;
extern const WORD LBL_Unlock;
extern const WORD LBL_SearchMore;
extern const WORD LBL_SearchExit1_PP;
extern const WORD LBL_SyncFound;
extern const WORD LBL_WaitQch_PP;
extern const WORD LBL_SearchExit2_PP;
extern const WORD LBL_TestLoop;
extern const WORD LBL_SuspendSearch;
extern const WORD LBL_RxE2;


extern const WORD LBL_InitBMCPrg1;
extern const WORD LBL_InitDone_PP;
extern const WORD LBL_DbgInit;
extern const WORD LBL_DebugLoop;
extern const WORD LBL_DbgLoop;
extern const WORD LBL_Wait1;
extern const WORD LBL_Wait2;
extern const WORD LBL_ContTX;
extern const WORD LBL_ContRX;
extern const WORD LBL_SearchTest;
extern const WORD LBL_SenduWireOn1;
extern const WORD LBL_SenduWire1;
extern const WORD LBL_TxShort;
extern const WORD LBL_TxAB;

extern const WORD LBL_Snd24Bits;
extern const WORD LBL_Snd24Done_PP;

extern const WORD LBL_Calibrate_PP;
extern const WORD LBL_RFEN;
extern const WORD LBL_RFDIS;
extern const WORD LBL_Calibrate;
extern const WORD LBL_RSSISlot0;
extern const WORD LBL_RSSISlot23;
extern const WORD LBL_StartRSSIRx;
extern const WORD LBL_StartRSSIRxRTN;
extern const WORD LBL_ScannRSSIFast;
extern const WORD LBL_ScannRSSIFastRTN;
extern const WORD LBL_RSSIScannLoop;


