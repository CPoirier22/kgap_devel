/****************************************************************************
*  Program/module: RtxDef.h                                                 *
*  Description:                                                             *
*                                                                           *
*  Programmer: MHP                                                          *
*  Created: 990217  13:29:50                                                *
*  Last update: 991215 10:17:13                                             *
*                                                                           *
****************************************************************************/
/****************************************************************************
*                                                                           *
*  PROJECT:                                                                 *
*  CONTROLLING DOCUMENT:                                                    *
*  SYSTEM DEPENDENCIES:                                                     *
*                                                                           *
****************************************************************************/



/****************************************************************************
*                                 PVCS info                                 *
*****************************************************************************

$Author:   on  $
$Date:   May 06 2003 13:31:36  $
$Revision:   1.0  $
$Modtime:   Jan 31 2003 10:35:16  $

*/
#ifndef RTXDEF_H
#define RTXDEF_H
/*******************************************************************************
* GLOBAL TYPEDEFINITIONS                                                       *
*******************************************************************************/

#ifdef GCCCOMPILE
#define PACKED  __attribute__((packed))
#else
#define PACKED
#endif

#ifdef PLATFORM_PC
typedef unsigned int uint32;
typedef signed int int32;
typedef unsigned char uint8;
typedef signed char int8;
typedef unsigned short uint16;
typedef signed short int16;
typedef void* ptrsize;
#else
typedef unsigned long uint32;
typedef signed long int32;
typedef unsigned char uint8;
typedef signed char int8;
typedef unsigned short uint16;
typedef signed short int16;
typedef void* ptrsize;
#endif

typedef float float32;
/* typedef uint32 bool;*/
typedef unsigned char boolean;
typedef unsigned int bitfield;

/*******************************************************************************
* GLOBAL DEFINITIONS                                                           *
*******************************************************************************/
#define BIT0                               0x0001
#define BIT1                               0x0002
#define BIT10                              0x0400
#define BIT11                              0x0800
#define BIT12                              0x1000
#define BIT13                              0x2000
#define BIT14                              0x4000
#define BIT15                              0x8000
#define BIT2                               0x0004
#define BIT3                               0x0008
#define BIT4                               0x0010
#define BIT5                               0x0020
#define BIT6                               0x0040
#define BIT7                               0x0080
#define BIT8                               0x0100
#define BIT9                               0x0200

#ifndef TRUE
#define TRUE       1
#endif
#ifndef FALSE
#define FALSE      0
#endif

#define BAD

#define YES        TRUE
#define NO         FALSE

#define UP         TRUE
#define DOWN       FALSE

#define OUTPUT     TRUE
#define INPUT      FALSE

#define ENABLE     TRUE
#define ENABLED    TRUE
#define DISABLE    FALSE
#define DISABLED   FALSE

#define HIGH       TRUE
#define LOW        FALSE

#define UPPER      TRUE
#define LOWER      FALSE

#define OPEN       TRUE
#define OPENED     TRUE
#define CLOSE      FALSE
#define CLOSED     FALSE

#define ENUM8(EnumName)  Enum_##EnumName; typedef uint8  EnumName
#define ENUM16(EnumName) Enum_##EnumName; typedef uint16 EnumName
#define ENUM32(EnumName) Enum_##EnumName; typedef uint32 EnumName

/* Define NULL pointer value */
#define FP_NULL ((ProcPtrType) 0)

/******************************************************************************
* Bit definitions                                                             *
******************************************************************************/
#define BIT16        0x00010000
#define BIT17        0x00020000
#define BIT18        0x00040000
#define BIT19        0x00080000
#define BIT20        0x00100000
#define BIT21        0x00200000
#define BIT22        0x00400000
#define BIT23        0x00800000

#define BIT24        0x01000000
#define BIT25        0x02000000
#define BIT26        0x04000000
#define BIT27        0x08000000
#define BIT28        0x10000000
#define BIT29        0x20000000
#define BIT30        0x40000000
#define BIT31        0x80000000

/******************************************************************************
* Bit manipulation macros.                                                    *
******************************************************************************/

#define SETBIT(var,bitno) ((var) |= (bitno))
#define CLRBIT(var,bitno) ((var) &= ~(bitno))
#define TSTBIT(var,bitno) ((var) & (bitno))


/*******************************************************************************
* Bit counts/positions/masks                                                   *
*******************************************************************************/
/* Bit counts */
#define BITS_IN_NIBBLE             4
#define BITS_IN_UINT8              8
#define BITS_IN_INT8               8
#define BITS_IN_UINT16             16
#define BITS_IN_INT16              16
#define BITS_IN_UINT32             32
#define BITS_IN_INT32              32

/* Bit positions */

#define MSB_POS_IN_UINT8           7
#define MSB_POS_IN_INT8            7
#define MSB_POS_IN_UINT16          15
#define MSB_POS_IN_INT16           15
#define MSB_POS_IN_UINT32          31
#define MSB_POS_IN_INT32           31

/* Bit masks */
#define LOW_NIBBLE                 0x0f
#define HIGH_NIBBLE                0xf0
#define MSB_MASK_IN_UINT8          0x80
#define MSB_MASK_IN_INT8           0x80
#define MSB_MASK_IN_UINT16         0x8000
#define MSB_MASK_IN_INT16          0x8000
#define MSB_MASK_IN_UINT32         0x80000000
#define MSB_MASK_IN_INT32          0x80000000

/*******************************************************************************
* Conversion macros                                                            *
*******************************************************************************/

#define INT8_TO_INT16(h, l)   ((h << BITS_IN_INT8) + l)
#define UINT8_TO_UINT16(h, l) ((h << BITS_IN_UINT8) + l)
#define HIGH_INT8(w)          ((int8) (w >> BITS_IN_INT8))
#define HIGH_UINT8(w)         ((uint8) (w >> BITS_IN_UINT8))
#define HIGH_BYTE(w)          ((uint8) (w >> BITS_IN_UINT8))
#define LOW_INT8(w)           ((int8) w)
#define LOW_UINT8(w)          ((uint8) w)
#define LOW_BYTE(w)           ((uint8) w)
#define BYTE0_OF_UINT32(var) ((uint8) var)
#define BYTE1_OF_UINT32(var) ((uint8) (var >> 8))
#define BYTE2_OF_UINT32(var) ((uint8) (var >> 16))
#define BYTE3_OF_UINT32(var) ((uint8) (var >> 24))
#define BYTE0_OF_INT32(var)  ((uint8) var)
#define BYTE1_OF_INT32(var)  ((uint8) (var >> 8))
#define BYTE2_OF_INT32(var)  ((uint8) (var >> 16))
#define BYTE3_OF_INT32(var)  ((uint8) (var >> 24))

/*******************************************************************************
* Offsetof macro                                                               *
*******************************************************************************/
#define OFFSETOF(s_name, m_name) (unsigned int) &(((s_name*)0)->m_name)

/*******************************************************************************
 *                             Port control macros                             *
 ******************************************************************************/

/* These macros allow 1 bit to be manipulated. The bit number (not the bitmask)
 * must be specified:

 * 1 bit port Access */

#define SET_PORT(port,bit)          port |=  (1<<bit)
#define CLR_PORT(port,bit)          port &= ~(1<<bit)
#define TOGGLE_PORT(port,bit)       port ^= (1<<bit)
#define GET_PORT(port,bit)         (port & (1<<bit))
#define INPUT_PORT(port,bit)        port &= ~(1<<bit)
#define OUTPUT_PORT(port,bit)       port |=  (1<<bit)


/* These macros allow multiple bits to be manipulated in one go. The BITx macros
 * are intended for use with these macros. They may be combined to form a bitmask.

 * Multiple bit port Access */
#define SET_PORTBITS(port,bits)     port |=  (bits)
#define CLR_PORTBITS(port,bits)     port &= ~(bits)
#define TOGGLE_PORTBITS(port,bit)   port ^=  (bits)
#define GET_PORTBITS(port,bits)    (port &   (bits))
#define INPUT_PORTBITS(port,bits)   port &= ~(bits)
#define OUTPUT_PORTBITS(port,bits)  port |=  (bits)

/* 1 bit port Access to dedicated port */
#define SET_PORT0(bit)  P0_SET_OUTPUT_DATA_REG = (1<<bit)
#define CLR_PORT0(bit)  P0_RESET_OUTPUT_DATA_REG = (1<<bit)
#define SET_PORT1(bit)  P1_SET_OUTPUT_DATA_REG = (1<<bit)
#define CLR_PORT1(bit)  P1_RESET_OUTPUT_DATA_REG = (1<<bit)
#define SET_PORT2(bit)  P2_SET_OUTPUT_DATA_REG = (1<<bit)
#define CLR_PORT2(bit)  P2_RESET_OUTPUT_DATA_REG = (1<<bit)

#define GET_PORT0(bit)  (P0_IN_OUT_DATA_REG & (1<<bit))
#define GET_PORT1(bit)  (P1_IN_OUT_DATA_REG & (1<<bit))
#define GET_PORT2(bit)  (P2_IN_OUT_DATA_REG & (1<<bit))

#endif /* header */
