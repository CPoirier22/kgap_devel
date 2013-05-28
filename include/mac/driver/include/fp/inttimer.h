/*
 ********************************************************************
 *
 * Module: inttimer.h
 *
 * Config-item: ?
 *
 * Contents: This file is the header file for inttimer.s28
 *
 * Author: Kirk telecom / BJR
 *
 * Copyright Kirk Telecom A/S. All rights reserved.
 *
 * $Header:   K:/ph/srclib/os/basis/archive/h/inttimer.h_v   1.5.2.1   May 06 2003 11:04:42   on  $
 *
 * $Log:   K:/ph/srclib/os/basis/archive/h/inttimer.h_v  $
 *
 *    Rev 1.5.2.1   May 06 2003 11:04:42   on
 * 1'st version of DZ500 2G4 A8
 *
 *    Rev 1.5.2.0   03 Jan 2001 09:52:00   on
 * DECT z 500 1a
 *
 *    Rev 1.5   Dec 05 1997 11:13:30   BJR
 * Added flag LinearTimingOfHkBitSet.
 *
 *    Rev 1.4   Oct 15 1997 14:22:30   BJR
 * Added flag NarrowWriteToIwuMode.
 *
 *    Rev 1.3   Sep 18 1997 09:12:26   BJR
 * Added PiggybackTimerCount and PiggybackTimerExpired.
 *
 *    Rev 1.2   Sep 16 1997 12:11:12   BJR
 * Added FreeRunCounter.
 *
 *    Rev 1.1   Jan 02 1997 13:59:00   MK
 * HlafSelector changed to QuartSelector.
 *
 *    Rev 1.0   Oct 31 1996 15:51:42   BJR
 * First revision.
 *
 ********************************************************************
 */

#ifndef INTTIMER_H__
#define INTTIMER_H__

#include "../../../../common/include/bitsdef.h"
#include "../../../../common/include/identify.h"



extern far UByte QuartSelector;

extern far unsigned int FreeRunCounter;

#endif /* INTTIMER_H__ */
