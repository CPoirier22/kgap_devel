/**************************************************************************
* Project   : DECT                                                        *
* Module    : Basestation CellSiteFunction task                           *
* Reference :                                                             *
* Type      : Task                                                        *
* Function  :                                                             *
* Systems   : Base                                                        *
*-------------------------------------------------------------------------*
* Copyright (c) 1996 by RTX Research A/S.                                 *
* $        $ *
**************************************************************************/

#ifndef __BSCSF_H
#define __BSCSF_H

#define TESTCMD_ENTER_TESTMODE  0x01

#define TESTCMD_SET_COMPERATOR  0x03
#define TESTCMD_WARMSTART       0x04
#define TESTCMD_FREQUNCY_SHIFT  0x05
#define TESTCMD_CONT_RX_QUAD_TRACK 0x06
#define TESTCMD_D2_BER_TEST     0x07
#define TESTCMD_STOP_RX_QUAD_TRACK 0x08
#define TESTCMD_RF_CHANNEL_SHIFT 0x09
#define TESTCMD_STARTLOGRXFRAME 0x99

void SetupCalibrLMX(void);



#endif

