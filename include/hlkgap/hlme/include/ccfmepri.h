/*
 ********************************************************************
 *
 * Module: ccfmepri.h
 *
 * Config-item: ?
 *
 * Contents: This file contains the fixed part cluster control function
 *     LLME primitive definitions.
 *
 * Author: DDU
 *
 * Copyright Kirk Telecom A/S. All rights reserved.
 ********************************************************************
 */

#ifndef FIXED_CCF_LLME_PRIMITIVES__
#define FIXED_CCF_LLME_PRIMITIVES__

#define CCF_ME_UPLANE_req 0x00

#define CCF_ME_CDM_ind 0x06

#define CCF_ME_CDV_ind 0x0A
#define CCF_ME_CDV_res 0x0B

#define CCF_ME_PRELOAD_req 0x0C

#define CCF_ME_DUMMY_ind 0x14
#define CCF_ME_DUMMY_res 0x15

#define CCF_ME_TEST_MODE_req 0x16

#define CCF_ME_DBG_TXT_ind    0x21

#define CCF_ME_EE_WRITE_req   0x3B
#define CCF_ME_EE_READ_req    0x3C
#define CCF_ME_EE_DATA_cfm    0x3D
#define EXTHOCOM_ind          0x44

#endif /* FIXED_CCF_LLME_PRIMITIVES__ */
