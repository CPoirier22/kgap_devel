/*******************************************************************************
* Project   : DECT                                                             *
* Module    : -                                                                *
* Reference : -                                                                *
* File      : Stddef.h                                                         *
* Type      : standard includefile                                             *
* Function  : -                                                                *
* Systems   : All systems                                                      *
*------------------------------------------------------------------------------*
* Owner:                                                                       *
* $Header:   K:/ph/srclib/util/variant/archive/h/STDDEF.H_V   1.2.1.1.1.6   May 19 2004 12:08:58   on  $ *
*******************************************************************************/

/******************************************************************************
* Compiler dependent definitions                                               *
*******************************************************************************/
#ifndef __STDDEF_H
#define __STDDEF_H

/* #define _BEST_BASES*/

#ifdef __IAR_SYSTEMS_ICC__
#if __IAR_SYSTEMS_ICC__ >= 5
#define _2 __data24
/* byte alignment*/

#pragma pack(1)
#pragma diag_error=Pe549,Pe170
#pragma diag_suppress=Pa039,Pe68,Pe069
#endif
#endif


/*******************************************************************************
* GLOBAL TYPEDEFINITIONS                                                       *
*******************************************************************************/

#ifndef BYTE
typedef unsigned char BYTE;     /* byte 0..255 */
#endif
#ifndef WORD
typedef unsigned short WORD;    /* word 0..65535 */
#endif
#ifndef SHORT
typedef signed short SHORT;     /* 16-bit -32768..32767 */
#endif
#ifndef DWORD
typedef unsigned long DWORD;    /* 32-bit 0..4294967295 */
#endif
#ifndef ASCII
typedef unsigned char ASCII;    /* ascii 0..255 */
#endif
#ifndef BOOLEAN
typedef unsigned char BOOLEAN;  /* 0 is logical FALSE, !0 is logical TRUE */
#endif

extern void* mem_malloc(unsigned int size, BYTE id);
extern void mem_free(void* buffer);

typedef struct
{
    BYTE lo;
    BYTE hi;
}
WordType;                     /* Access BYTEs in a WORD */

typedef void (*ProcPtrType) (void);

/*******************************************************************************
* GLOBAL DEFINITIONS                                                           *
*******************************************************************************/
#ifndef TRUE
#define TRUE    1
#endif
#ifndef FALSE
#define FALSE   0
#endif
#define NIL 0                   /* pointer to nothing */


/*******************************************************************************
* TARGET DEPENDANT DEFINITIONS                                                 *
*******************************************************************************/

extern int _sprintf_(char* str, char* fmt, ...);
extern int _printf_(char* fmt, ...);

typedef unsigned char BITFIELD;
#define huge
#define far

/* The IAR CR16 compiler prepends all extended*/
/* keywords with two underscores:*/
#define interrupt __interrupt
#define no_init __no_init

/*******************************************************************************
* MORE GLOBAL TYPEDEFINITIONS
*******************************************************************************/

#ifndef NULL
#define NULL ((void *)0)
#endif


#define SET_PORT(port,bit)  port |=  (1<<bit)
#define CLR_PORT(port,bit)  port &= ~(1<<bit)
#define TOGGLE_PORT(port,bit) port ^= (1<<bit)
#define GET_PORT(port,bit)  (port & (1<<bit))
#define INPUT_PORT(port,bit)   port &= ~(1<<bit)
#define OUTPUT_PORT(port,bit)  port |=  (1<<bit)

/*
???????????????????????????????????????????????????????????????????????????????
?                        Compiler dependents hiding macros                    ?
???????????????????????????????????????????????????????????????????????????????

These macros are intended as a way of removing compiler specific code
from the sourcefiles. If a compiler does not support some of these macros
they should be defined to nothing.

The following standard macros has been defined so far:

NONBANKED  force function (ex: void NONBANKED f(void)) into the common segment
           when banking model is used. Defined to nothing in other models.

FAR,NEAR   Far and near directives.

INTERRUPT  Declare function as an interrupt handler

DISABLE_INTERRUPTS  Disable all interrupts
ENABLE_INTERRUPTS   Enable all interrupts


*/

#ifdef __IAR_SYSTEMS_ICC__
#define FAR
#define NEAR __near
#define INTERRUPT __interrupt
#define ENABLE_INTERRUPTS __enable_interrupt()
#define DISABLE_INTERRUPTS __disable_interrupt()
#ifdef MEMORY_MODEL_BANKED
#define NONBANKED __near_func
#else
#define NONBANKED
#endif
#else
/* So far other compilers does not support this scheme. Please implement, somebody!*/
#define FAR
#define NEAR
#define NONBANKED
#define DISABLE_INTERRUPTS
#define ENABLE_INTERRUPTS
#endif


/*
???????????????????????????????????????????????????????????????????????????????
?                         Alternate ioport control macros                     ?
???????????????????????????????????????????????????????????????????????????????

These macros allow multiple bits to be manipulated in one go. The bit macros
below are intended for use with these macros:

*/

#ifndef NO_PORTBITS_MACROS
#define SET_PORTBITS(port,bits)     port |=  (bits)
#define CLR_PORTBITS(port,bits)     port &= ~(bits)
#define TOGGLE_PORTBITS(port,bit)   port ^=  (bits)
#define GET_PORTBITS(port,bits)    (port &   (bits))
#define INPUT_PORTBITS(port,bits)   port &= ~(bits)
#define OUTPUT_PORTBITS(port,bits)  port |=  (bits)
#endif










#ifndef NO_DTMF_MACROS
typedef enum
{
    DTMF_0 = 0,                   /*  0*/
    DTMF_1,                       /*  1*/
    DTMF_2,                       /*  2*/
    DTMF_3,                       /*  3*/
    DTMF_4,                       /*  4*/
    DTMF_5,                       /*  5*/
    DTMF_6,                       /*  6*/
    DTMF_7,                       /*  7*/
    DTMF_8,                       /*  8*/
    DTMF_9,                       /*  9*/
    DTMF_A,                       /*  A*/
    DTMF_B,                       /*  B*/
    DTMF_C,                       /*  C*/
    DTMF_D,                       /*  D*/
    DTMF_STAR,                    /*  E*/
    DTMF_HASH                     /*  F*/
} DtmfKeyType;
#endif

#endif /* header */
