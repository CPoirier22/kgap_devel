/*
 ********************************************************************
 *
 * Module:  bformat.h
 *
 *  Config-item:  ?
 *
 * Contents:  This header file contains macroes, type definitions etc.
 *          parameter definitions related to B-format messages and
 *          primitives.
 *
 *  Author: Kirk telecom / BJR
 *
 * Copyright Kirk Telecom A/S. All rights reserved.
 *
 * $Header:   K:/PH/140960xx/00/Archive/H/bformat.h_v   1.0   Oct 24 2002 11:51:10   mne  $
 *
 * $Log:   K:/PH/140960xx/00/Archive/H/bformat.h_v  $
 *
 *    Rev 1.0   Oct 24 2002 11:51:10   mne
 * Initial PP5 version for 428
 *
 *    Rev 1.4   23 Feb 1999 10:01:38   oo
 * File changed for PP2 HW. (Lucy).
 *
 *    Rev 1.3   May 21 1997 15:37:50   OO
 * defines for ALERT_BROADCAST_ind added.
 *
 *    Rev 1.2   06 Mar 1996 15:03:16   BJR
 * Adapted to new format of DL_BROADCAST_ind.
 *
 *    Rev 1.1   29 Feb 1996 12:26:42   BJR
 * PORTABLE_PART__: Replaced inclusion of DDUOS.H with PDDUOS.H.
 *
 *    Rev 1.0   14 Nov 1995 15:41:46   BJR
 * Initial revision.
 *
 ********************************************************************
 */

#ifndef BFORMAT_H__
#define BFORMAT_H__

#include "../../dduos/include/dduos.h"

/***************************************************************************/
/**********   Typedefinition of general B-format message   *****************/
/***************************************************************************/

typedef UByte MessageUnitLengthType;

struct BFormatStruct
{
    SignalType TheSignal;
    MessageUnitLengthType MessageUnitLength;
};
typedef struct BFormatStruct BFormatType;


/**********   LCE request page short message format   **********************/

#define AssignedTpui  0x08

#define INMinDelay  0x04

#define PageAlertingOn0       0x00
#define PageAlertingOn1       0x01
#define PageAlertingOn2       0x02
#define PageAlertingOn3       0x03
#define PageAlertingOn4       0x04
#define PageAlertingOn5       0x05
#define PageAlertingOn6       0x06
#define PageAlertingOn7       0x07
#define PageAlertingOnCont    0x08
#define PageReleasedByFP      0x0a
#define PageAnswered          0x0b
#define PageAlertingOff       0x0f

#endif /* BFORMAT_H__ */
