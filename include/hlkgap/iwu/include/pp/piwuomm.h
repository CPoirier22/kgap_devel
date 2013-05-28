/*
 ********************************************************************
 *
 * Module:   piwuomm.h
 *
 *  Config-item:  ?
 *
 * Contents: Header file for PIWUOMM.C.
 *
 *  Author:  Kirk telecom / BJR
 *
 * Copyright Kirk Telecom A/S. All rights reserved.
 *
 * $Header:   K:/PH/SRCLIB/PP5/BASIS/ARCHIVE/H/piwuomm.h_v   1.1   26 Nov 2003 15:21:26   mne  $
 *
 * $Log:   K:/PH/SRCLIB/PP5/BASIS/ARCHIVE/H/piwuomm.h_v  $
 *
 *    Rev 1.1   26 Nov 2003 15:21:26   mne
 * Duration timer added.
 *
 *    Rev 1.0   Oct 24 2002 11:51:42   mne
 * Initial PP5 version for 428
 *
 *    Rev 1.3   23 Feb 1999 09:58:12   oo
 * File changed for PP2 HW. (Lucy).
 *
 *    Rev 1.2   Apr 04 1997 12:24:36   BJR
 * Removed InitiateAuthOfFt.
 *
 *    Rev 1.1   Jun 24 1996 18:21:52   BJR
 *
 *
 *    Rev 1.0   Apr 16 1996 19:17:32   BJR
 * First revision.
 *
 ********************************************************************
 */

#ifndef PIWUOMM_H__
#define PIWUOMM_H__

#include "../../../dduos/include/dduos.h"

void InitiateLocUpdate(int sessionID);

extern BYTE TimeDuration;
extern WORD TimeUnit;

#endif /*not PIWUOMM_H__ */
