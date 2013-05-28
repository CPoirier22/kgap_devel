/*
 ********************************************************************
 *
 * Module: f_eeprom.h
 *
 * Config-item: ?
 *
 * Contents: This file is the header file for f_eeprom.c.
 *
 * Author: MK
 *
 * Copyright Kirk Telecom A/S. All rights reserved.
 *
 * $Header:   K:/ph/srclib/util/basis/archive/h/f_eeprom.h_v   1.4.1.1   Nov 18 2003 13:37:18   on  $
 *
 * $Log:   K:/ph/srclib/util/basis/archive/h/f_eeprom.h_v  $
 *
 *    Rev 1.4.1.1   Nov 18 2003 13:37:18   on
 * Initial version for IP 600
 *
 *    Rev 1.4.1.0   02 Jan 2001 11:14:28   on
 * DECT z 500 1a
 *
 *    Rev 1.4   Dec 17 1996 18:05:40   BJR
 * Added ResetEEprom.
 * Moved EEPROM_PAGE_SIZE, EEPROM_PAGE_ADDR_MASK and EEPROM_LAST_ADDR from F_NVM.H.
 * Removed parameter DeviceAddr from EEpromWriteBytes and EEpromReadBytes.
 *
 *    Rev 1.3   Nov 20 1996 16:38:56   MK
 * Updated to following new parameters in functions.
 * Defines moved to f_nvm.h.
 *
 *    Rev 1.2   Nov 04 1996 13:14:50   BJR
 * Now 8. kb of EEPROM is supported.
 *
 *    Rev 1.1   Sep 25 1996 14:36:12   MK
 * Adresses for system data in EEPROM defined.
 *
 *    Rev 1.0   Sep 09 1996 11:28:12   MK
 * Initial revision.
 *
 *
 ********************************************************************
 */
#ifndef F_EEPROM_HEADER__
#define F_EEPROM_HEADER__

#include "../../../common/include/identify.h"

#define EEPROM_LAST_ADDR            8191

Boolean EEpromReadDirect_(WORD EEaddress, BYTE * DataBuffer, WORD BufferSize);
void StartWriteBytesDirect(WORD EEaddress, BYTE * DataBuffer, WORD BufferSize);
void EEpromRead(U16Bits Addr, UByte * NVMCache, U16Bits BufferSize);
void EeInit(void);
void EeSetStart(void);
void EeSetStop(void);
void EeSendByte(BYTE a);
void Start_I2CBus(void);
void Stop_I2CBus(void);
void tSendLcdByte(BYTE Data);

#endif
