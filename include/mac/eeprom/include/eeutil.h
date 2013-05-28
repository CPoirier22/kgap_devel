/******************************************************************************
*  $Header:
*
*  DESCRIPTION: Common base/handset EEPROM utility functions
*
*  REFERENCES :
*
*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*  The information in this document is confidential and sole property of
*  RTX Research A/S. (c) Copyright 1997 by RTX Research A/S.
******************************************************************************/

#ifndef __EEUTIL_H
#define __EEUTIL_H

/*============================ MACROS / CONSTANTS ============================*/


/*================================== TYPES ===================================*/
extern BYTE getAdjustAddressSize();
extern WORD getAdjustAddress(BYTE xx);

typedef struct
{
    BYTE  FillValue;
    WORD  FillStart;
    WORD  FillEnd;
}
FillType;



/*============================= EXTERN VARIABLES =============================*/

/*================================ PROTOTYPES ================================*/

void BurnEeArrayN(BYTE *Array, int Size, BYTE Mode);
void ReadEEPromData(UByte * DestinPtr, EEPromAdressCodeType AddrCode);
Boolean WriteEEPromData(UByte * srcPtr, EEPromAdressCodeType AddrCode);

/*=================================== END ====================================*/
#endif







