/*******************************************************************************
* Project   : DECT                                                             *
*                                                                              *
* Module    : Value Check                                                      *
*                                                                              *
* Reference :                                                                  *
*                                                                              *
* File      : \DECT\SW\TASK\UTIL\SOURCE\CHECKS.H                               *
*                                                                              *
* Type      : Header file with the macro definition for value check.           *
*                                                                              *
* Function  : Usage:  When defining the symbol CHECKS the macro CHECKVALUE     *
*                     can be used for generating an error message on a         *
*                     true condition.                                          *
*                     Syntax:  CHECKVALUE(<condition>,<Error-message-string>); *
*                                                                              *
*                     When defining the symbol DEBUGDISP the argument to       *
*                     macro DEBUGLIST will be executed.                        *
*                                                                              *
* Systems   : Base,Handset                                                     *
*------------------------------------------------------------------------------*
********************************************************************************
* $Header:   K:/PH/SRCLIB/UTIL/VARIANT/ARCHIVE/H/CHECKS.H_V   1.1   23 Feb 1999 10:14:22   oo  $ *
*******************************************************************************/
#ifndef __CHECKS_H
#define __CHECKS_H

#ifdef CHECKS
extern void CheckError(const char msg[]);
#define CHECKVALUE(cond,msg) do { if (cond) CheckError(msg); } while (0)
#else
#define CHECKVALUE(cond,msg) /* Nothing */
#endif

#ifdef DEBUG
#define DEBUGDISP(print) print
#else
#define DEBUGDISP(print)  /* Nothing */
#endif

#endif
