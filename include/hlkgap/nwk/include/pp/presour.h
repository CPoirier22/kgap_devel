/*
 ********************************************************************
 *
 * Module:  p_resour.h
 *
 *  Config-item:  ?
 *
 * Contents:  Header file for Resource table and their routines
 *
 *  Author: DDU
 *
 * Copyright Kirk Telecom A/S. All rights reserved.
 *
 * $Header:   K:/PH/140960xx/00/Archive/H/p_resour.h_v   1.0   Oct 24 2002 11:51:36   mne  $
 *
 * $Log:   K:/PH/140960xx/00/Archive/H/p_resour.h_v  $
 *
 *    Rev 1.0   Oct 24 2002 11:51:36   mne
 * Initial PP5 version for 428
 *
 *    Rev 1.2   14 Nov 1995 15:51:26   BJR
 * Removed LCE_RESOURCE_RELEASE.
 *
 *    Rev 1.1   26 Jan 1995 13:08:06   CB
 * Fileheader added
 *
 *    Rev 1.0   20 Jan 1995 12:55:06   CB
 * Initial version
 *
 ********************************************************************
 */
#ifndef P_RESOUR_H__
#define P_RESOUR_H__
#include "../../../dduos/include/dduos.h"
#include "../../../../common/include/identify.h"

Boolean PLCE_RESOURCE_RESERVE ( SignalType * Signal, XXEIType XXEI, DLEIType DLEI );

#endif /*  P_RESOUR_H__ */
