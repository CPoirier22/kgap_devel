/*
 ********************************************************************
 *
 * Module: fiwuciss.h
 *
 * Config-item: ?
 *
 * Contents: This is the header file for fiwuciss.c.
 *
 * Author:    Kirk telecom / BJR.
 *
 * Copyright Kirk Telecom A/S. All rights reserved.
 ********************************************************************
 */

#ifndef FIWUCISS_H__
#define FIWUCISS_H__

#include "../../../dduos/include/dduos.h"
#include "fiwuinst.h"

void IwuCissHandler(IWUDataType * InstData, SignalType * Signal);

void CissReleaseAction(IWUDataType * InstData);

#endif /* FIWUCISS_H__ */
