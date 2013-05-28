/*
 ********************************************************************
 *
 * Module:   piwuaux.h
 *
 *  Config-item:  ?
 *
 * Contents: Header file for PIWUAUX.H.
 *
 *  Author:   Kirk telecom / BJR
 *
 * Copyright Kirk Telecom A/S. All rights reserved.
 *
 * $Header:   K:/PH/SRCLIB/PP5/BASIS/ARCHIVE/H/piwuaux.h_v   1.1   17 May 2004 14:36:04   mne  $
 *
 * $Log:   K:/PH/SRCLIB/PP5/BASIS/ARCHIVE/H/piwuaux.h_v  $
 *
 *    Rev 1.1   17 May 2004 14:36:04   mne
 * ShowVersionPCS now 21 byte.
 *
 *    Rev 1.0   Oct 24 2002 11:51:40   mne
 * Initial PP5 version for 428
 *
 *    Rev 1.4   23 Feb 1999 09:58:10   oo
 * File changed for PP2 HW. (Lucy).
 *
 *    Rev 1.3   Jul 31 1997 15:23:34   OO
 * Changes for sending Number and PCS to CCFP at location reistration.
 *
 *    Rev 1.2   Jul 31 1997 11:18:20   BJR
 * Added MaxLenOfIwuToIwuLocateRequest and ReadIwuToIwuLocateRequest.
 *
 *    Rev 1.1   Sep 03 1996 09:36:58   BJR
 * TerminalCapability is now defined as const to remove type conflict.
 *
 *    Rev 1.0   Sep 02 1996 15:11:06   BJR
 * First revision.
 *
 ********************************************************************
 */

#ifndef PIWUAUX_H__
#define PIWUAUX_H__

#include "../../../../common/include/bitsdef.h"
#include "../../../common/include/aformat.h"

extern const UByte TerminalCapability [];
extern const BYTE ShowVersionPCS[21];
#define MaxLenOfIwuToIwuLocateRequest (sizeof(IwuToIwuType) + sizeof(NoAndPCSIEType))
/* Is the maximum length of the <<IWU-to-IWU> info. elem. returned*/
/* by ReadIwuToIwuLocateRequest*/

UByte ReadIwuToIwuLocateRequest ( UByte * IwuToIwuAddr );

#endif /*not PIWUAUX_H__*/
