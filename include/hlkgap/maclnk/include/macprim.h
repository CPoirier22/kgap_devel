/*
 ********************************************************************
 *
 * Module: macprim.h
 *
 * Config-item: ?
 *
 * Contents: This file contains the portable part mac primitive
 *     definitions.
 *
 * Author: DDU
 *
 * Copyright Kirk Telecom A/S. All rights reserved.
 *
 * $Header:   K:/ph/srclib/mac/basis/archive/h/macprim.h_v   1.5   Nov 06 1996 15:53:10   MK  $
 ********************************************************************
 */

#ifndef MAC_PRIMITIVES__
#define MAC_PRIMITIVES__
#include "../../../os/include/mailprim.h"

#define MAC_CON_req     _MAC_CON_req
#define MAC_CON_cfm     _MAC_CON_cfm
#define MAC_CON_ind     _MAC_CON_ind
#define MAC_CON_res     _MAC_CON_res
#define MAC_CO_DATA_req _MAC_CO_DATA_req
#define MAC_CO_DATA_ind _MAC_CO_DATA_ind
#define MAC_CO_DTR_ind  _MAC_CO_DTR_ind
#define MAC_DIS_req     _MAC_DIS_req
#define MAC_DIS_ind     _MAC_DIS_ind
#define MAC_RES_DLC_ind _MAC_RES_DLC_ind
#define MAC_PAGE_req    _MAC_PAGE_req
#define MAC_PAGE_ind    _MAC_PAGE_ind
#define MAC_ENC_KEY_req _MAC_ENC_KEY_req
#define MAC_ENC_EKS_req _MAC_ENC_EKS_req
#define MAC_ENC_EKS_cfm _MAC_ENC_EKS_cfm
#define MAC_ENC_EKS_ind _MAC_ENC_EKS_ind

#define NO_ARI                  0
#define P_ARI                   2
#define LOAD_PARK               4
#define LOAD_PMID               5
#define INIT_SEARCH             6
#define SEARCH_NEXT             7

#endif /* MAC_PRIMITIVES__ */

