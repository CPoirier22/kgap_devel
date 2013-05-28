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




typedef struct
{
    BYTE  FillValue;
    WORD  FillStart;
    WORD  FillEnd;
}
FillType;

typedef struct
{
    UByte LengthOfContents;
    UByte LengthOfIdentityValue;      /* Length of IPUI in bits, MSB set to 1 */
    UByte IpuiValue [ MaxIpuiOctets ];
}
EE_IpuiType;

typedef struct
{
    UByte LengthOfContents;
    UByte LengthOfIdentityValue;      /* Length of PARK in bits plus 1, MSB set to 1 */
    UByte ParkValue [ MaxParkOctets ];
}
EE_ParkType;

typedef struct
{
    UByte PresentFlag;
    UByte LalValue;
}
EE_LalType;

typedef struct
{
    UByte PresentFlag;
    UByte RfpiValue [ MaxAriRpnOctets ];
}
EE_RfpiType;

typedef struct
{
    UByte PresentFlag;
    UByte ZapValue;
}
EE_ZapFieldType;

typedef struct
{
    UByte PresentFlag;
    UByte ServiceClassField;
}
EE_ServiceClassType;

typedef struct
{
    UByte KeyType;                      /* Use 0, UakPEIEId and AcPEIEId */
    UByte UakAcValue [ MaxUakOctets ];
}
EE_UakAcType;

typedef struct
{
    UByte   IpeiValue [ MaxIpeiOctets ];
}
EE_IpeiType;



/*============================= EXTERN VARIABLES =============================*/

/*================================ PROTOTYPES ================================*/

void BurnEeArrayN(BYTE *Array, BYTE Size,BYTE Mode);
/*=================================== END ====================================*/
#endif







