/*
 ********************************************************************
 *
 * Module:  plcedata.h
 *
 *  Config-item:  ?
 *
 * Contents:  Datatypes for LCE signalhandler is defined in this file.
 *          Only PORTABLEPART uses these datatypes
 ********************************************************************
 */

#ifndef PLCEDATA_H__
#define PLCEDATA_H__

#include "../../../dduos/include/dduos.h"

/*************************** DL Data Types **********************************/
typedef struct DLEstablishCfmStruct
{
    SignalType Header;            /* Address = DLEI */
}
DLEstablishCfmType;

#endif /* PLCEDATA_H__ */
