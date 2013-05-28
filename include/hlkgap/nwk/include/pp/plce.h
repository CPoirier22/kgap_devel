/*
 ********************************************************************
 *
 * Module:  p_lce.h
 *
 *  Config-item:  ?
 *
 * Contents:  Keep declerations for p_lce
 *
 *  Author: DDU
 *
 * Copyright Kirk Telecom A/S. All rights reserved.
 *
 * $Header:   K:/PH/140960xx/00/Archive/H/p_lce.h_v   1.0   Oct 24 2002 11:51:34   mne  $
 *
 * $Log:   K:/PH/140960xx/00/Archive/H/p_lce.h_v  $
 *
 *    Rev 1.0   Oct 24 2002 11:51:34   mne
 * Initial PP5 version for 428
 *
 *    Rev 1.2   14 Nov 1995 15:58:50   BJR
 * Changes in relation to rewriting of P_LCE.C.
 *
 *    Rev 1.1   26 Jan 1995 13:08:04   CB
 * Fileheader added
 *
 *    Rev 1.0   20 Jan 1995 12:55:04   CB
 * Initial version
 *
 ********************************************************************
 */

#ifndef _P_LCE_H__
#define _P_LCE_H__

/* timer definitions */
#define TIMER_LCE_01    01
#define TIMER_LCE_02    02
#define TIMER_LCE_03  03
#define TIMER_LCE_04    04

#define LCE_01_VALUE      500
#define LCE_02_VALUE     1000
#define LCE_03_VALUE      300
#define LCE_04_VALUE      500     /* 5s with timer of 10mS pr. tick */

#endif /* _P_LCE_H__ */
