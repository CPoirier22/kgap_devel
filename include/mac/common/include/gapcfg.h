#ifndef __GAPCFG_H
#define __GAPCFG_H

/*****************************************************************************
* Project   : GAP                                                            *
* Module    : GAPCFG.H  GAP configuration module.                            *
* Reference :                                                                *
* Type      : Headerfile for definition of GAP configuration.                *
* Function  :                                                                *
* Systems   : Base,Handset                                                   *
*----------------------------------------------------------------------------*
* Copyright (c) 1994 by RTX Research Aps.                                    *
* $Header:   K:/ph/srclib/mac/basis/archive/h/GAPCFG.H_v   1.1.1.3   Nov 18 2003 14:34:20   on  $ *
*****************************************************************************/

#ifdef SLOT_12
#define TEMPSLOTINCREMENT       1
#define SLOTINCREMENT           1
#define NUMBEROFCONNECTIONS  12
#define NUMBEROFTRANSMITTERS 12
#else
#define TEMPSLOTINCREMENT       2
#define SLOTINCREMENT           2
#define NUMBEROFCONNECTIONS  6
#define NUMBEROFTRANSMITTERS 6
#endif
#define SLOTCOUNT               12
#define FIRST_SLOT    0
#define LAST_SLOT    11
#define LAST_LONG_SLOT    		  10
#define FREQUENCYCOUNT            10
#endif
