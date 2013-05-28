/*
 ********************************************************************
 *
 * Module: calcprim.h
 *
 * Config-item: ?
 *
 * Contents: Primitives for the authentication calculation process is defined in this file.
 *
 * Author:    Kirk telecom / BJR.
 *
 * Copyright Kirk Telecom A/S. All rights reserved.
 ********************************************************************
 */

#ifndef CALCPRIM_H__
#define CALCPRIM_H__

#include "../../../common/include/identify.h"
#include "../../dduos/include/dduos.h"

#define CALC_RES1_DCK_req  0x00
#define CALC_RES1_DCK_cfm  0x01

#define CALC_RES1_req  0x04
#define CALC_RES1_cfm  0x05

#define CALC_RES2_req  0x08
#define CALC_RES2_cfm  0x09

#define CALC_RES2_UAK_req 0x0C
#define CALC_RES2_UAK_cfm 0x0D

#define CALC_ACTIVATE      0x10

typedef struct
{
    SignalType SignalHeader;
    AddressType ReturnAddress;
    UByte *K_Ptr;
    UByte *Rs_Ptr;
    UByte *Rand_F_Ptr;
    UByte *Res1_Ptr;
    UByte *Dck_Ptr;
}
CalcRes1DckReqType;

typedef struct
{
    SignalType SignalHeader;
}
CalcRes1DckCfmType;

typedef struct
{
    SignalType SignalHeader;
    AddressType ReturnAddress;
    UByte *K_Ptr;
    UByte *Rs_Ptr;
    UByte *Rand_F_Ptr;
    UByte *Res1_Ptr;
}
CalcRes1ReqType;

typedef struct
{
    SignalType SignalHeader;
}
CalcRes1CfmType;

typedef struct
{
    SignalType SignalHeader;
    AddressType ReturnAddress;
    UByte *K_Ptr;
    UByte *Rs_Ptr;
    UByte *Rand_P_Ptr;
    UByte *Res2_Ptr;
}
CalcRes2ReqType;

typedef struct
{
    SignalType SignalHeader;
}
CalcRes2CfmType;

typedef struct
{
    SignalType SignalHeader;
    AddressType ReturnAddress;
    UByte *K_Ptr;
    UByte *Rs_Ptr;
    UByte *Rand_P_Ptr;
    UByte *Res2_Ptr;
    UByte *Uak_Ptr;
}
CalcRes2UakReqType;

typedef struct
{
    SignalType SignalHeader;
}
CalcRes2UakCfmType;

#endif /*CALCPRIM_H__ */
