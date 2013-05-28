/*
 *-----------------------------------------------------------------------------
 *                                                                             
 *               @@@@@@@      *   @@@@@@@@@           *                                     
 *              @       @             @               *                            
 *              @             *       @      ****     *                                 
 *               @@@@@@@      *       @     *    *    *                              
 *        ___---        @     *       @     ******    *                                 
 *  ___---      @       @     *       @     *         *                             
 *   -_          @@@@@@@  _   *       @      ****     *                               
 *     -_                 _ -                                                     
 *       -_          _ -                                                       
 *         -_   _ -        s   e   m   i   c   o   n   d   u   c   t   o   r 
 *           -                                                                    
 *                                                                              
 * (C) Copyright SiTel Semiconductor BV, unpublished work.
 * This computer program includes Confidential, Proprietary Information and
 * is a Trade Secret of SiTel Semiconductor BV.
 * All use, disclosure, and/or reproduction is prohibited unless authorized
 * in writing. All Rights Reserved.
 *
 *---------------------------------------------------------------------------------
 *
 *-----------------------------------------------------------------------------
 * Filename: <sitel_io.h >
 * Purpose : <io header file Sitel>
 * Created : <08-2005>
 * By      : <SW>
 * Country : <The Netherlands>
 *
 *-----------------------------------------------------------------------------
 */ 
#ifndef SITEL_IO_H
#define SITEL_IO_H

typedef unsigned char      uint8;
typedef char               int8;
typedef unsigned short     uint16;
typedef short              int16;
typedef unsigned long int  uint32;
typedef long int           int32;

typedef unsigned char      bool;

//#define TRUE (unsigned char)  1
//#define FALSE (unsigned char) 0
typedef enum
    {
        FALSE  = 0,
        TRUE   = 1
    } BOOLEAN, BOOL;

#ifndef NULL
#define NULL (uint8*)(-1)
#endif

#ifdef NSST_MODE
    typedef unsigned char      BYTE;
    typedef unsigned short     WORD;
    typedef unsigned long int  DWORD;


    #ifdef IAR
    #define  __far
    #define inline	
    #endif

    #define __far
    
    #if defined SC14428
       #include "ns14428.h"
    #elif defined SC14430
       #include "ns14430.h"
    #elif defined SC14434
       #include "ns14434.h"
    #elif defined SC14451
       #include "ns14451.h"
    #elif defined SC14470
       #include "ns14470.h"
    #elif defined SC14450
       #include "sc14450.h"
    #elif defined SC14480
       #include "sc14480.h"
    #else
    #error NO device IO include file
    #endif
#else
    #if defined SC14428
        #include "iosc14428.h" /* from IAR distributiopn */
    #elif defined SC14430
        #include "iosc14430.h"
    #elif defined SC14434
        #include "iosc14434.h"
    #elif defined SC14450
        #include "iosc14450.h"
   #elif defined SC14480
        #include "iosc14480.h"
    #elif defined SC14451
        #include "iosc14451.h"
    #elif defined SC14470
        #include "iosc14470.h"
    #else
    #error NO device IO include file
    #endif

    #define GetByte(a)  	(* (uint8*)(a) )
    #define GetWord(a)  	(* (uint16*)(a) )
    #define GetBits(a,f)	(##a##_bit.##f )
    #define SetByte(a,d)	(* (uint8*)(a)=(d) )
    #define SetWord(a,d)	(* (uint16*)(a)=(d) )
    #define SetBits(a,f,d)	(##a##_bit.##f##=(d))
#endif

#endif
