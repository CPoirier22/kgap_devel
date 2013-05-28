/*
 ********************************************************************
 *
 * Module: lcprim.h
 *
 * Config-item: ?
 *
 * Contents: This file contains the Lc primitive definitions.
 *
 * Author: DDU
 *
 * Copyright Kirk Telecom A/S. All rights reserved.
 ********************************************************************
 */

#ifndef Lc_PRIMITIVES__
#define Lc_PRIMITIVES__

#define Lc_MAC_CON_req   0x00
#define Lc_MAC_CON_cfm   0x01
#define Lc_MAC_CON_ind   0x02
#define Lc_MAC_CON_res   0x03

#define Lc_MAC_DIS_req   0x04
#define Lc_MAC_DIS_cfm       0x05
#define Lc_MAC_DIS_ind       0x06
#define Lc_MAC_DIS_res       0x07

#define Lc_DATA_req    0x08
#define Lc_DATA_cfm          0x09
#define Lc_DATA_ind          0x0A
#define Lc_DATA_res          0x0B

#define Lc_UNIT_DATA_req  0x0C
#define Lc_UNIT_DATA_cfm     0x0D
#define Lc_UNIT_DATA_ind     0x0E
#define Lc_UNIT_DATA_res     0x0F

#define Lc_ENC_KEY_req   0x10
#define Lc_ENC_KEY_cfm   0x11
#define Lc_ENC_KEY_ind   0x12
#define Lc_ENC_KEY_res   0x13

#define Lc_ENCRYPT_req   0x14
#define Lc_ENCRYPT_cfm   0x15
#define Lc_ENCRYPT_ind   0x16
#define Lc_ENCRYPT_res   0x17

#endif /* Lc_PRIMITIVES__ */
