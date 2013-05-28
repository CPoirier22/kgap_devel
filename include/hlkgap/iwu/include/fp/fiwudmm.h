/*
 ********************************************************************
 *
 * Module: fiwudmm.h
 *
 * Config-item: ?
 *
 * Contents: This is the header file for fiwudmm.c.
 *
 * Author: ?Kirk telecom / BJR.
 *
 * Copyright Kirk Telecom A/S. All rights reserved.
 ********************************************************************
 */

#ifndef FIWUDMM_H__
#define FIWUDMM_H__

#include "../../../dduos/include/dduos.h"
#include "fiwuomm.h"
#include "fiwuinst.h"

void SendOmSubsCreateReject(PMIDType Pmid, UByte RejectReasonCode);
void DstMMReportSecurityProceduresResult(IWUDataType * InstData, SecurityProceduresResultType SecurityProceduresResult, UByte RejectReasonCode);
void IwuDstMMHandler(IWUDataType * InstData, SignalType * Signal);

#endif /* FIWUDMM_H__ */
