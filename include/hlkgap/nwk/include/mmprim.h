/*
 ********************************************************************
 *
 * Module:      mmprim.h
 *
 *      Config-item:    ?
 *
 * Contents:    Primitives for MM signalhandler is defined in this file.
 *
 *      Author: DDU
 *
 * Copyright Kirk Telecom A/S. All rights reserved.
 ********************************************************************
 */

#ifndef MM_PRIMITIVES__
#define MM_PRIMITIVES__

#include "../../../common/include/identify.h"
#include "../../common/include/sformat.h"
#include "../../dduos/include/dduos.h"

/****************************************************************************/

#define MM_AUTHENTICATE_req                     0x00
#define MM_AUTHENTICATE_cfm                     0x01
#define MM_AUTHENTICATE_ind                     0x02
#define MM_AUTHENTICATE_res                     0x03

#define MM_KEY_ALLOCATE_req                     0x04
#define MM_KEY_ALLOCATE_cfm                     0x05
#define MM_KEY_ALLOCATE_ind                     0x06
#define MM_KEY_ALLOCATE_res                     0x07

#define MM_ACCESS_RIGHTS_req                    0x08
#define MM_ACCESS_RIGHTS_cfm                    0x09
#define MM_ACCESS_RIGHTS_ind                    0x0A
#define MM_ACCESS_RIGHTS_res                    0x0B

#define MM_ACCESS_RIGHTS_TERMINATE_req          0x0C
#define MM_ACCESS_RIGHTS_TERMINATE_cfm          0x0D
#define MM_ACCESS_RIGHTS_TERMINATE_ind          0x0E
#define MM_ACCESS_RIGHTS_TERMINATE_res          0x0F

#define MM_CIPHER_req                           0x10
#define MM_CIPHER_cfm                           0x11
#define MM_CIPHER_ind                           0x12
#define MM_CIPHER_res                           0x13

#define MM_INFO_req                             0x14
#define MM_INFO_cfm                             0x15
#define MM_INFO_ind                             0x16
#define MM_INFO_res                             0x17

#define MM_LOCATE_req                           0x18
#define MM_LOCATE_cfm                           0x19
#define MM_LOCATE_ind                           0x1A
#define MM_LOCATE_res                           0x1B

#define MM_DETACH_req                           0x1C
#define MM_DETACH_cfm                           0x1D
#define MM_DETACH_ind                           0x1E
#define MM_DETACH_res                           0x1F

#define MM_IDENTITY_req                         0x20
#define MM_IDENTITY_cfm                         0x21
#define MM_IDENTITY_ind                         0x22
#define MM_IDENTITY_res                         0x23

#define MM_IDENTITY_ASSIGN_req                  0x24
#define MM_IDENTITY_ASSIGN_cfm                  0x25
#define MM_IDENTITY_ASSIGN_ind                  0x26
#define MM_IDENTITY_ASSIGN_res                  0x27

typedef struct
{
    SignalType SignalHeader;
}
MMIdentityIndType;

#define getMMIdentityIndTypeIE(signal) ((unsigned char*)signal + sizeof(SignalType))

typedef struct
{
    SignalType SignalHeader;
}
MMIdentityResType;

#define getMMIdentityResTypeIE(signal) ((unsigned char*)signal + sizeof(SignalType))

typedef struct
{
    SignalType SignalHeader;
    Boolean Accept;
}
MMIdentityAssignResType;

#define getMMIdentityAssignResTypeIE(signal) ((unsigned char*)signal + offsetof(MMIdentityAssignResType, Accept) + sizeof(Boolean))

typedef struct
{
    SignalType SignalHeader;
}
MMAuthenticateReqAFType;      /* Used as part of Auth. of FT */

typedef struct
{
    SignalType SignalHeader;
    Boolean Accept;
}
MMAuthenticateReqKAType;      /* Used as part of key alloc. */

#define getMMAuthenticateReqKATypeIE(signal) ((unsigned char*)signal + offsetof(MMAuthenticateReqKAType, Accept) + sizeof(Boolean))

typedef struct
{
    SignalType SignalHeader;
}
MMAuthenticateIndType;

#define getMMAuthenticateIndTypeIE(signal) ((unsigned char*)signal + sizeof(SignalType))

typedef struct
{
    SignalType SignalHeader;
    Boolean Accept;
}
MMAuthenticateCfmType;

#define getMMAuthenticateCfmTypeIE(signal) ((unsigned char*)signal + offsetof(MMAuthenticateCfmType, Accept) + sizeof(Boolean))

typedef struct
{
    SignalType SignalHeader;
}
MMLocateReqType;

#define getMMLocateReqTypeIE(signal) ((unsigned char*)signal + sizeof(SignalType))

typedef struct
{
    SignalType SignalHeader;
    Boolean Accept;
}
MMLocateCfmType;

#define getMMLocateCfmTypeIE(signal) ((unsigned char*)signal + offsetof(MMLocateCfmType, Accept) + sizeof(Boolean))

typedef struct
{
    SignalType SignalHeader;
}
MMAccessRightsReqType;

#define getMMAccessRightsReqTypeIE(signal) ((unsigned char*)signal + sizeof(SignalType))

typedef struct
{
    SignalType SignalHeader;
    Boolean Accept;
}
MMAccessRightsCfmType;

#define getMMAccessRightsCfmTypeIE(signal) ((unsigned char*)signal + offsetof(MMAccessRightsCfmType, Accept) + sizeof(Boolean))

typedef struct
{
    SignalType SignalHeader;
}
MMAccessRightsTerminateReqType;

#define getMMAccessRightsTerminateReqTypeIE(signal) ((unsigned char*)signal + sizeof(SignalType))

typedef struct
{
    SignalType SignalHeader;
    Boolean Accept;
}
MMAccessRightsTerminateCfmType;

typedef struct
{
    SignalType SignalHeader;
}
MMKeyAllocateIndType;

#define getMMKeyAllocateIndTypeIE(signal) ((unsigned char*)signal + sizeof(SignalType))

typedef struct
{
    SignalType SignalHeader;
}
MMInfoIndType;

#define getMMInfoIndTypeIE(signal) ((unsigned char*)signal + sizeof(SignalType))

typedef struct
{
    SignalType SignalHeader;
}
MMCipherIndType;

#define getMMCipherIndTypeIE(signal) ((unsigned char*)signal + sizeof(SignalType))

typedef struct
{
    SignalType SignalHeader;
    Boolean Accept;
}
MMCipherResType;

#define MM_AUTHENTICATE_req                     0x00
#define MM_AUTHENTICATE_cfm                     0x01
#define MM_AUTHENTICATE_ind                     0x02
#define MM_AUTHENTICATE_res                     0x03

#define MM_KEY_ALLOCATE_req                     0x04
#define MM_KEY_ALLOCATE_cfm                     0x05
#define MM_KEY_ALLOCATE_ind                     0x06
#define MM_KEY_ALLOCATE_res                     0x07


#define MM_ACCESS_RIGHTS_req                    0x08
#define MM_ACCESS_RIGHTS_cfm                    0x09
#define MM_ACCESS_RIGHTS_ind                    0x0A
#define MM_ACCESS_RIGHTS_res                    0x0B

#define MM_ACCESS_RIGHTS_TERMINATE_req          0x0C
#define MM_ACCESS_RIGHTS_TERMINATE_cfm          0x0D
#define MM_ACCESS_RIGHTS_TERMINATE_ind          0x0E
#define MM_ACCESS_RIGHTS_TERMINATE_res          0x0F

#define MM_CIPHER_req                           0x10
#define MM_CIPHER_cfm                           0x11
#define MM_CIPHER_ind                           0x12
#define MM_CIPHER_res                           0x13

#define MM_INFO_req                             0x14
#define MM_INFO_cfm                             0x15
#define MM_INFO_ind                             0x16
#define MM_INFO_res                             0x17

#define MM_LOCATE_req                           0x18
#define MM_LOCATE_cfm                           0x19
#define MM_LOCATE_ind                           0x1A
#define MM_LOCATE_res                           0x1B

#define MM_DETACH_req                           0x1C
#define MM_DETACH_cfm                           0x1D
#define MM_DETACH_ind                           0x1E
#define MM_DETACH_res                           0x1F

#define MM_IDENTITY_req                         0x20
#define MM_IDENTITY_cfm                         0x21
#define MM_IDENTITY_ind                         0x22
#define MM_IDENTITY_res                         0x23

#define MM_IDENTITY_ASSIGN_req                  0x24
#define MM_IDENTITY_ASSIGN_cfm                  0x25
#define MM_IDENTITY_ASSIGN_ind                  0x26
#define MM_IDENTITY_ASSIGN_res                  0x27

typedef struct
{
    SignalType SignalHeader;
    Boolean Accept;
}
MMIdentityAssignCfmType;

typedef struct
{
    SignalType SignalHeader;
}
MMAuthenticateReqType;

#define getMMAuthenticateReqTypeIE(signal) ((unsigned char*)signal + sizeof(SignalType))

typedef struct
{
    SignalType SignalHeader;
}
MMAuthenticateIndAFType;

#define getMMAuthenticateIndAFTypeIE(signal) ((unsigned char*)signal + sizeof(SignalType))

typedef struct
{
    SignalType SignalHeader;
    Boolean Accept;
}
MMAuthenticateIndKAType;

#define getMMAuthenticateIndKATypeIE(signal) ((unsigned char*)signal + offsetof(MMAuthenticateIndKAType, Accept) + sizeof(Boolean))

typedef struct
{
    SignalType SignalHeader;
    Boolean Accept;
}
MMAuthenticateResType;

#define getMMAuthenticateResTypeIE(signal) ((unsigned char*)signal + offsetof(MMAuthenticateResType, Accept) + sizeof(Boolean))

typedef struct
{
    SignalType SignalHeader;
}
MMLocateIndType;

#define getMMLocateIndTypeIE(signal) ((unsigned char*)signal + sizeof(SignalType))

typedef struct
{
    SignalType SignalHeader;
    Boolean Accept;
}
MMLocateResType;

#define getMMLocateResTypeIE(signal) ((unsigned char*)signal + offsetof(MMLocateResType, Accept) + sizeof(Boolean))

typedef struct
{
    SignalType SignalHeader;
}
MMAccessRightsIndType;

#define getMMAccessRightsIndTypeIE(signal) ((unsigned char*)signal + sizeof(SignalType))

typedef struct
{
    SignalType SignalHeader;
    Boolean Accept;
}
MMAccessRightsResType;

#define getMMAccessRightsResTypeIE(signal) ((unsigned char*)signal + offsetof(MMAccessRightsResType, Accept) + sizeof(Boolean))

typedef struct
{
    SignalType SignalHeader;
}
MMAccessRightsTerminateIndType;

typedef struct
{
    SignalType SignalHeader;
    Boolean Accept;
}
MMAccessRightsTerminateResType;

typedef struct
{
    SignalType SignalHeader;
}
MMKeyAllocateReqType;

#define getMMKeyAllocateReqTypeIE(signal) ((unsigned char*)signal + sizeof(SignalType))

typedef struct
{
    SignalType SignalHeader;
    DckType Dck;
}
MMCipherReqType;

#define getMMCipherReqTypeIE(signal) ((unsigned char*)signal + offsetof(MMCipherReqType, Dck) + sizeof(DckType))

typedef struct
{
    SignalType SignalHeader;
    Boolean Accept;
}
MMCipherCfmType;

#define getMMCipherCfmTypeIE(signal) ((unsigned char*)signal + offsetof(MMCipherCfmType, Accept) + sizeof(Boolean))

/****************************************************************************/
#endif /* MM_PRIMITIVES */
