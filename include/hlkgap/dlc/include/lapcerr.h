/*
 ********************************************************************
 *
 * Module: lapcerr.h
 *
 * Config-item: ?
 *
 * Contents: This file contains the error log numbers. The general LAPC
 *     numbers range from 1 to 1000. The Class errors range from:
 *     U: 1001 - 2000, A: 2001 - 3000 and B: 3001 - .
 *
 * Author: DDU
 *
 * Copyright Kirk Telecom A/S. All rights reserved.
 ********************************************************************
 */

#ifndef LAPC_ERRORS__
#define LAPC_ERRORS__

#define LAPC_UNKNOWN_CLASS_ERROR  1
#define LAPC_UNKNOWN_PRIMITIVE_ERROR 2

#define CLASS_U_PORTABLE_SAPI_3_ERROR 1001
#define CLASS_U_MAXIMUM_LENGTH_ERROR 1002
#define CLASS_U_NO_INSTANCE_ERROR  1003
#define CLASS_U_UNKNOWN_SIGNAL_ERROR 1004

#define CLASS_A_NO_INSTANCE_ERROR  2001
#define CLASS_A_UNKNOWN_SIGNAL_ERROR 2002
#define CLASS_A_SEQUENCE_ERROR   2003
#define CLASS_A_CONTROL_FIELD_ERROR  2004

#define CLASS_B_UNKNOWN_SIGNAL_ERROR 3001

#endif /* LAPC_ERRORS__ */
