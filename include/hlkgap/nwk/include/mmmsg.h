/*
 ********************************************************************
 *
 * Module: mm_msg.h
 *
 * Config-item: ?
 *
 * Contents: MM message type codings in s-format
 *
 * Author: DDU
 *
 * Copyright Kirk Telecom A/S. All rights reserved.
 ********************************************************************
 */

#ifndef MM_MSG__
#define MM_MSG__
#include "../../common/include/sformat.h"

#define AUTHENTICATE_REQUEST   0x40
#define AUTHENTICATE_REPLY    0x41
#define KEY_ALLOCATE     0x42
#define AUTHENTICATE_REJECT    0x43

#define ACCESS_RIGHTS_REQUEST   0x44
#define ACCESS_RIGHTS_ACCEPT   0x45
#define ACCESS_RIGHTS_REJECT   0x47

#define ACCESS_RIGHTS_TERMINATE_REQUEST 0x48
#define ACCESS_RIGHTS_TERMINATE_ACCEPT 0x49
#define ACCESS_RIGHTS_TERMINATE_REJECT 0x4B

#define CIPHER_REQUEST     0x4C
#define CIPHER_SUGGEST     0x4E
#define CIPHER_REJECT     0x4F

#define MM_INFO_REQUEST     0x50
#define MM_INFO_ACCEPT     0x51
#define MM_INFO_SUGGEST     0x52
#define MM_INFO_REJECT     0x53

#define LOCATE_REQUEST     0x54
#define LOCATE_ACCEPT     0x55
#define DETACH       0x56
#define LOCATE_REJECT     0x57

#define IDENTITY_REQUEST    0x58
#define IDENTITY_REPLY     0x59

#define TEMPORARY_IDENTITY_ASSIGN  0x5A
#define TEMPORARY_IDENTITY_ASSIGN_Ack 0x5D
#define TEMPORARY_IDENTITY_ASSIGN_Rej   0x5F


#endif /* MM_MSG__ */
