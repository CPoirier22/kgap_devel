#ifndef __HSLLME_H
#define __HSLLME_H

/**************************************************************************
* Project   : DECT                                                        *
* Module    : Handset Hsllme                                              *
* Reference :                                                             *
* Type      : Header file                                                 *
* Function  :                                                             *
* Systems   : Handset                                                     *
*-------------------------------------------------------------------------*
* Copyright (c) 1994 by RTX Research Aps.                                 *
***************************************************************************
* $Header:   K:/PH/140960xx/00/Archive/H/hsllme.h_v   1.0   Oct 24 2002 11:51:24   mne  $ *
* $Log:   K:/PH/140960xx/00/Archive/H/hsllme.h_v  $
 *
 *    Rev 1.0   Oct 24 2002 11:51:24   mne
 * Initial PP5 version for 428
 *
 *    Rev 1.0   23 Feb 1999 16:23:34   oo
 * Inital ver. for PP2 (Lucy).
**************************************************************************/

/* CtrlInfo Type*/
typedef enum {

    NO_ARI,            /* NO_ARI PP out of lock*/
    S_ARI,             /* SARI is found*/
    P_ARI,             /* PARI is found*/
    U_PARI,            /* PARI holding the found SARI*/
    LOAD_PARK,
    LOAD_PMID,
    INIT_SEARCH,       /* First command to search for ARI*/
    SEARCH_NEXT        /* Following search commands*/

} ScanCtrlType;

#define ARI_SEARCH_MODE (ParkCtrlFlagPP & 0x80)
#define SARI_SEARCH     0x08

#endif
