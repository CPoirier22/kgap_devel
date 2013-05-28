/*
 ********************************************************************
 *
 * Module: except.h
 *
 * Config-item: ?
 *
 * Contents:    Header file for except.c.
 *
 * Author: ?Kirk telecom / BJR
 *
 * Copyright Kirk Telecom A/S. All rights reserved.
 *
 * $Header:   K:/ph/srclib/util/basis/archive/h/except.h_v   1.15   Nov 18 2003 10:22:10   on  $
 *
 * $Log:   K:/ph/srclib/util/basis/archive/h/except.h_v  $
 *
 *    Rev 1.15   Nov 18 2003 10:22:10   on
 * Initial version of IP 600
 *
 *    Rev 1.14   05 Oct 1999 12:58:28   bjr
 * Added RST_InvalidParameter to RestartSubtypType.
 *
 *    Rev 1.13   04 Dec 1998 11:16:46   BJR
 * Added RST_LinkEstabFailed to RestartSubtypType.
 *
 *    Rev 1.12   16 Sep 1998 12:09:34   bjr
 * Added RST_SlaveRestarted to RestartSubtypType.
 *
 *    Rev 1.11   Jul 24 1998 10:44:34   bjr
 * Added RST_InvalidMessage to RestartSubtypType.
 *
 *    Rev 1.10   10 Jun 1998 13:48:28   BJR
 * Added RST_InvalidPrimitive to RestartSubtypType.
 *
 *    Rev 1.9   11 Feb 1998 13:12:06   BJR
 * Added RST_Timeout to RestartSubtypType.
 *
 *    Rev 1.8   29 Jan 1998 11:19:36   BJR
 * Added RST_InvalidState to RestartSubtypType.
 *
 *    Rev 1.7   Jan 29 1997 14:12:20   BJR
 * Now really removed DebugModeLoop.
 * Added InitStackSystemHaltedLoop.
 *
 *    Rev 1.6   Jan 08 1997 20:02:04   BJR
 * Added RST_InconsistentDataStructure to RestartSubtypType.
 *
 *    Rev 1.5   Nov 30 1996 12:12:30   BJR
 * Added RST_Unspecified and RST_VitalParameterMissing to RestartSubtypType.
 *
 *    Rev 1.4   Nov 23 1996 18:00:52   BJR
 * Removed DebugModeLoop.
 *
 *    Rev 1.3   Nov 21 1996 09:35:46   BJR
 * Moved FullAddressType from EXCEPT.C.
 *
 *    Rev 1.2   Nov 14 1996 18:52:20   BJR
 * Changed return type of DumpExcept.
 *
 *    Rev 1.1   Nov 11 1996 09:47:36   BJR
 * Corrected errors.
 *
 *    Rev 1.0   Nov 04 1996 13:35:34   BJR
 * First revision.
 *
 ********************************************************************
 */

#ifndef EXCEPT_H__
#define EXCEPT_H__

void SyncLostException( UByte radio_id, UByte rssi, UByte crc );
void DipDownException(BYTE Cause);
void NifInterfaceDown(void);

#endif /* EXCEPT_H__ */
