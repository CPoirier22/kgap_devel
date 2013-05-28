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
* $Header:   K:/PH/140960xx/00/Archive/H/blowtest.h_v   1.0   Oct 24 2002 11:51:10   mne  $ *
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
extern void BmcLowLevelTestFunction_PP(MailType *MailPtr);

#endif
