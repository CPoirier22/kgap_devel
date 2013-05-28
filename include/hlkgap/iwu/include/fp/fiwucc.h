/*
 ********************************************************************
 *
 * Module: fiwucc.h
 *
 * Config-item: ?
 *
 * Contents: This is the header file for fiwucc.c.
 *
 * Author: ?Kirk telecom / BJR.
 *
 * Copyright Kirk Telecom A/S. All rights reserved.
 ********************************************************************
 */

#ifndef FIWUCC_H__
#define FIWUCC_H__

#include "../../../dduos/include/dduos.h"
#include "fiwuomm.h"
#include "fiwuinst.h"

void IwuCCHandler(IWUDataType * InstData, SignalType * Signal);

void CCReportSecurityProceduresResult(IWUDataType * InstData, SecurityProceduresResultType SecurityProceduresResult, UByte ReleaseReasonCode);

void AbnormalCCReleaseAction(IWUDataType * InstData);

#endif /* FIWUCC_H__ */
