/*
 ********************************************************************
 *
 * Module: lapcprim.h
 *
 * Config-item: ?
 *
 * Contents: This file contains the LAPC primitive definitions.
 *
 * Author: DDU
 *
 * Copyright Kirk Telecom A/S. All rights reserved.
 ********************************************************************
 */

#ifndef LAPC_PRIMITIVES__
#define LAPC_PRIMITIVES__

#define DL_ESTABLISH_req  0x00
#define DL_ESTABLISH_cfm  0x01
#define DL_ESTABLISH_ind  0x02
#define DL_ESTABLISH_res  0x03

#define DL_RELEASE_req   0x04
#define DL_RELEASE_cfm       0x05
#define DL_RELEASE_ind       0x06
#define DL_RELEASE_res       0x07

#define DL_DATA_req    0x08
#define DL_DATA_cfm          0x09
#define DL_DATA_ind          0x0A
#define DL_DATA_res          0x0B

#define DL_UNIT_DATA_req  0x0C
#define DL_UNIT_DATA_cfm     0x0D
#define DL_UNIT_DATA_ind     0x0E
#define DL_UNIT_DATA_res     0x0F

#define DL_ENC_KEY_req   0x10
#define DL_ENC_KEY_cfm   0x11
#define DL_ENC_KEY_ind   0x12
#define DL_ENC_KEY_res   0x13

#define DL_ENCRYPT_req   0x14
#define DL_ENCRYPT_cfm   0x15
#define DL_ENCRYPT_ind   0x16
#define DL_ENCRYPT_res   0x17

#define DL_TUNNEL_REQ   0x18

#endif /* LAPC_PRIMITIVES__ */
