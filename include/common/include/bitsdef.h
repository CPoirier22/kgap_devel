/*
 ********************************************************************
 *
 * Module: bitsdef.h
 *
 * Config-item: ?
 *
 * Contents: This file contains the CPU/COMPILER dependant type
 *     definitions. It also contains the event id's used in
 *     relation with the signal queue. It is also in this file that
 *     the size of the memory pool is set! The memory pool is
 *     segmented into 128 bytes blocks. So the
 *     NUMBER_OF_128_BYTE_BUFFERS define indicates how many blocks
 *     of 128 bytes the pool should consist of.
 *     The user should set/write this file according to the
 *     specific implementation/environment.
 *
 * Author: DDU
 *
 * Copyright Kirk Telecom A/S. All rights reserved.
 *
 * $Header:   K:/ph/srclib/os/basis/archive/h/bitsdef.h_v   1.6   Jun 13 1997 14:41:50   BJR  $
 *
 * $Log:   K:/ph/srclib/os/basis/archive/h/bitsdef.h_v  $
 *
 *    Rev 1.6   Jun 13 1997 14:41:50   BJR
 * Moved NUMBER_OF_128_BYTE_BUFFERS to DDUOS.H.
 *
 *    Rev 1.5   Jan 20 1997 14:20:36   MK
 * NUMBER_OF_128_BYTE_BUFFERS set to 511 (Heap size of 64K - 128 bytes).
 *
 *    Rev 1.4   Nov 04 1996 13:15:32   BJR
 * Added ACTIVATE_EVENT.
 *
 *    Rev 1.3   Aug 23 1996 11:17:44   MK
 * Heap size set to 32 K.
 *
 *    Rev 1.2   Jun 24 1996 19:04:28   BJR
 * Added BitCntToByteCnt.
 *
 *    Rev 1.1   26 Jan 1995 13:07:10   CB
 * Fileheader added
 *
 ********************************************************************
 */

#ifndef BITS_DEFINITION__
#define BITS_DEFINITION__

#include "_stddef.h"

#ifndef TRUE
#define TRUE (1)
#endif /* TRUE */

#ifndef FALSE
#define FALSE (0)
#endif /* FALSE */

typedef char Boolean;
typedef unsigned char UByte;
typedef unsigned short int U16Bits;

/* Event IDs */

#define INITIALIZE_EVENT 0x00
#define TIME_OUT_EVENT  0x01
#define ACTIVATE_EVENT  0x02

#define BitCntToByteCnt(NoOfBits) ((NoOfBits%8)?(NoOfBits/8+1):(NoOfBits/8))

#endif /* BITS_DEFINITION__ */
