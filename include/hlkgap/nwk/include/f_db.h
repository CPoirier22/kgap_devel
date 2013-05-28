/*
 ********************************************************************
 *
 * Module:  f_db.h
 *
 * Config-item: ?
 *
 * Contents: This is the header file for f_db.c.
 *
 * Author:  Kirk telecom / BJR.
 *
 * Copyright Kirk Telecom A/S. All rights reserved.
 ********************************************************************
 */

#ifndef F_DB_H__
#define F_DB_H__

#include "../../../common/include/identify.h"

#ifndef F_DB_C__
extern UByte AriInRam[4];
#endif

void TransferAri(void);

#endif /* F_DB_H__ */
