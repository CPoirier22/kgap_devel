#ifndef __INITHOST_H
#define __INITHOST_H
/*******************************************************************************
* Project   : DECT                                                             *
* Module    : Initialize Host Hardware                                         *
* Reference : M37702 hardware manual.                                          *
* File      : \dect\sw\task\os\source\inithost.h                               *
* Type      : Headerfile for host initialization functions                     *
* Function  : The functions initializes all the IO ports and peripherial       *
*             hardware or files for the host system.                           *
*             Related C-source files:                                          *
*                INITHS.C                                                      *
*                INITBS.C                                                      *
*                INITPC.C                                                      *
* Systems   : Base,Handset,PC                                                  *
*------------------------------------------------------------------------------*
* Owner: JTP                                                                   *
* $Header:   K:/PH/SRCLIB/OS/BASIS/ARCHIVE/H/INITHOST.H_v   1.1   23 Feb 1999 10:03:44   oo  $ *
*******************************************************************************/

extern void InitIO(void);
extern void InitSystem(void);

#endif
