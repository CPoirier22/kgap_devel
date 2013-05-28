#ifndef __BMCDRIV_H
#define __BMCDRIV_H
/*****************************************************************************
* Project   : DECT
* Module    : BMC driver
* Reference :
* Type      : Headerfile for slot switching interrupt handler.
* Function  :
* Systems   : Handset
*
* Copyright (c) 1996 by Kirk telecom A/S.
*****************************************************************************/

extern void AdjustFrequency_Ext_Sync(uint8 bBs424Phase, uint8 CableDelay);
extern void memcpy5(uint8 * Dest, uint8 * Source);
extern void memcpy4(uint8 * Dest, uint8 * Source);

#endif
