/*==============================================================================
;*  $Header:   K:/PH/140960xx/00/Archive/H/eedrv.h_v   1.1   17 Sep 2003 08:12:58   mne  $
;*
;*  DESCRIPTION: EEPROM hardware driver header.
;*
;*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
;*  The information in this document is confidential and sole property of
;*  RTX Research A/S. (c) Copyright 1997 by RTX Research A/S.
;*============================================================================*/

#ifndef __EEDRV_H
#define __EEDRV_H

/*============================ MACROS / CONSTANTS ============================*/

/*================================== TYPES ===================================*/

/*============================= EXTERN VARIABLES =============================*/

/*================================ PROTOTYPES ================================*/

extern void EeInit(void);
extern void EeWriteByte(WORD EEaddress, BYTE EEdata);
extern void EeReadRandomAddress(WORD NoBytes, WORD EEaddress, BYTE* ReadBuf);
extern WORD EeGetSize(void);
extern WORD EeGetWriteTime(void);
extern WORD EeGetWriteDelayLoopCount(void);

#ifdef _PAGE_WRITE_ALLOWED_
extern WORD EeGetPageSize(void);
#endif

/*=================================== END ====================================*/

#endif

