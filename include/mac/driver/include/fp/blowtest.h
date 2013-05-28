#ifndef __BLOWTEST_H
#define __BLOWTEST_H

/*****************************************************************************
* Project   : DECT                                                           *
* Module    : BMC lowlevel test function                                     *
* Type      : Test hardware driver                                           *
* Function  : Interprets function commands and controls the BMC in low level *
*             test mode.                                                     *
* Systems   : Base,Handset                                                   *
*----------------------------------------------------------------------------*
* $Header:   K:/PH/133002XX/00/PCS_2/ARCHIVE/BMC/BLOWTEST.H_V   1.1   May 05 2003 10:55:56   on  $ *
*****************************************************************************/

#define INIT_tbmc 1
#define ADDRESS_tbmc 2
#define WRTPRGS_tbmc 3
#define WRTPRG_tbmc 4
#define WRTDATA_tbmc 5
#define EXEC_tbmc 6
#define EXIT_tbmc 7
#define STARTAUTOMAIL_tbmc 8
#define AUTOMAIL_tbmc 9

extern void SendSerialRespond(BYTE c);
extern void BmcLowLevelTestFunction_FP(MailType *MailPtr);

extern void bmclowt_ContinuousTxSynthesis(BYTE Freq);
extern void bmclowt_ContinuousRxSynthesis(BYTE Freq);
extern void bmclowt_BurstTx(BYTE Freq, BYTE Antenna);
extern void bmclowt_SetBurstPaOn(BYTE Parm);
extern void bmclowt_EnableLoopBack(void);

#endif
