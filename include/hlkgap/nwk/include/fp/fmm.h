/*
 ********************************************************************
 *
 * Module: mm.h
 *
 * Config-item: ?
 *
 * Contents: This is a common header file for both the fixed part
 *     MM signal handler and the portable part MM signal handler
 *
 * Author: DDU
 *
 * Copyright Kirk Telecom A/S. All rights reserved.
 ********************************************************************
 */

#ifndef FMM_HEADER__
#define FMM_HEADER__

#include "../mm.h"

#define MMAccess2  1000    /*  10s */
#define MMAuth1  1000    /*  10s */
#define MMAuth2    10000        /* 100s */
#define MMCipher1   1000        /*  10s */
#define MMIdent1    1000        /*  10s */
#define MMIdent2    1000        /*  10s */
#define MMKey       1000        /*  10s */

enum MMStateList
{
    LCE_RESOURCE_RESERVE_State = 1,   /* 01h */
    ACCESS_RIGHTS_TERMINATE_State,        /* 02h */
    AUTHENTICATION_REPLY_State,   /* 03h */
    IDENTITY_REPLY_State,         /* 04h */
    AUTHENTICATION_REQUEST_State, /* 05h */
    TEMPORARY_IDENTITY_ASSIGN_State,      /* 06h */
    MM_AUTHENTICATE_res_State,    /* 07h */
    MM_ACCESS_RIGHTS_res_State,   /* 08h */
    MM_ACCESS_RIGHTS_TERMINATE_res_State, /* 09h */
    MM_LOCATE_res_State,          /* 0Ah */
    CIPHER_REQUEST_State          /* 0Bh */
};
typedef enum MMStateList MMStateType;
#define NumberOfMMStates  13

extern BinTreeTopType MMEncryptLinkTreeTop;

#endif /* FMM_HEADER__ */
