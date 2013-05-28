#ifndef __SEARCH_H
#define __SEARCH_H
/*****************************************************************************
* Project   : DECT                                                           *
* Module    : Initial search for basestation.                                *
* Reference :                                                                *
* Type      : Headerfile for initial search module.                          *
* Function  :                                                                *
* Systems   : Handset                                                        *
*----------------------------------------------------------------------------*
* Copyright (c) 1994 by RTX Research Aps.                                    *
* $Header:   K:/PH/140960xx/00/Archive/H/search.h_v   1.0   Oct 24 2002 11:51:46   mne  $ *
*****************************************************************************/

extern BYTE RxSearchModePP;
extern BYTE DIP_Running_PP;

extern void InitialSearchHandler(void);

#endif
