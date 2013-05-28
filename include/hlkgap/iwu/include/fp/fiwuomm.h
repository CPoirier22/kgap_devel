/*
 ********************************************************************
 *
 * Module: fiwuomm.h
 *
 * Config-item: ?
 *
 * Contents: This is the header file for fiwuomm.c.
 *
 * Author: ?Kirk telecom / BJR.
 *
 * Copyright Kirk Telecom A/S. All rights reserved.
 ********************************************************************
 */

#ifndef FIWUOMM_H__
#define FIWUOMM_H__

#include "../../../dduos/include/dduos.h"
#include "fiwuinst.h"

typedef enum
{
    SPR_Continue,
    SPR_Passed,
    SPR_Failed
} SecurityProceduresResultType;

void SendOmSubsRemove(PMIDType Pmid);

void StartSecurityProcedures(IWUDataType * InstData, SecurityDescriptorIEType * SecurityDescriptorIE, OriMMCallerType OriMMCaller);

void AbortSecurityProcedures(IWUDataType * InstData, OriMMCallerType Caller);

void SubsTermAction(IWUDataType * InstData, PortableIdentityType * Ipui);

void IwuOriMMHandler(IWUDataType * InstData, SignalType * Signal);

#endif /* FIWUOMM_H__ */
