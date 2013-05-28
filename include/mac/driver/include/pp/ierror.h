/****************************************************************************
*  Program/file: Error
*
*  Copyright (C) by RTX TELECOM A/S, Denmark.
*  These computer program listings and specifications, are the property of
*  RTX TELECOM A/S, Denmark and shall not be reproduced or copied or used in
*  whole or in part without written permission from RTX TELECOM A/S, Denmark.
*
*  Programmer: CM
*
*  MODULE:
*  CONTROLLING DOCUMENT:
*  SYSTEM DEPENDENCIES:
*
*
*  DESCRIPTION:
*
*       Generic module to be used to report errors.
*       By default the module provides the function Error_RuntimeError which will write
*       an errorcode and a taskid into EEPROM and perform a SW reset.
*
*       Special error situations such as Watchdog and Exception will update
*       special EEPROM error entries and afterwards proceed with a call to
*       Error_RuntimeError. See special configurations below
*
*       Compiler flags for the ERROR module:
*
*       ERROR_ENABLE_ASSERT:
*          When defined ERROR_ASSERT can be used like Error_RuntimeError
*          to report errors
*
*       ERROR_RUNTIME_ERROR_NO_RESET:
*          When set Error_RunTimeError will not perform SW reset
*          ERROR_ASSERT will still make the reset.
*          Also Watchdog and Exception errors will still result in reset
*
*       ERROR_FLUSH_MAIL_QUEUE
*          When defined the error module will try to dump mail queue to debug
*          bus. Requires module RDBG and OS flag OS_MAIL_QUEUE_DUMP_SUPPORT
*
*       NO_ERROR_IN_EEPROM
*          When set error information will not be written to EEPROM
*          NO_ERROR_IN_EEPROM is implicit set if NOEEPROM is defined.
*
*       ERROR_REPORT_LINE_NUMBER
*          When set line number is also reported.
*
*       PROJCFG_ERROR_MAX_NUM_ERRORS
*          By default max errors is determined by EEPROM_ERROR_NEWEST_ERROR and
*          EEPROM_ERROR_FIRST_ERROR, but if NO_ERROR_IN_EEPROM or NOEEPROM this
*          define may overrule the default for the module
*
*       PROJCFG_EEPROM_EXCEP_ERROR_SIZE
*          Specifies the length of data to be reported upon exception and
*          watchdog errors. If not defined a default will be used.
*          Length must be equal to or greater than the number of bytes returned
*          by the platform specific BuildException routine
*
*       ERROR_WATCHDOG_TIMEOUT
*          Defines the expire time for the Watchdog timer. If not defined a
*          default value is used. Time is specified in whatever unit the OS
*          uses.
*
*       PROJCFG_SW_RESET_FUNCTION
*          If defined it must refer a project specific reset function
*          declared as:
*              void PROJCFG_SW_RESET_FUNCTION(void)
*
*       Other required defines:
*
*       Following are not necessary if NO_ERROR_IN_EEPROM or NOEEPROM
*       EEPROM_ERROR_NEWEST_ERROR - Address of newest error
*       EEPROM_ERROR_FIRST_ERROR  - Address of first error
*       EEPROM_ERROR_COUNT        - Actual number of errors reported
*
*       EEPROM_WATCH_DOG_COUNT - Actual number of watchdog errors
*       EPPROM_EXCEP_COUNT     - Actual number of Exception errors
*       EEPROM_EXCEP_ERROR     - Address to store exception error at
*
****************************************************************************/

/****************************************************************************
*                                  PVCS info
*****************************************************************************

$Author:   mne  $
$Date:   Oct 24 2002 11:50:52  $
$Revision:   1.0  $
$Modtime:   Oct 23 2002 13:00:40  $

*/

#ifndef IERROR_H
#define IERROR_H

#include "../../../../common/include/rtxdef.h"

/****************************************************************************
*                              Macro definitions
****************************************************************************/
#ifdef PCCOMPILE
#define __interrupt
#define __huge2
#endif



#ifdef ERROR_FLUSH_SERIAL
#ifndef ERROR_FLUSH_MAIL_QUEUE
#define ERROR_FLUSH_MAIL_QUEUE
#endif
#endif

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/




enum {
    ERROR_NO_ERROR                             = 0,
    /* All the junk*/
    INVALID_SIZE                               = 1,
    NO_MEM                                     = 2,
    INVALID_POINTER                            = 3,
    PRIMITIVES_LOG_ERROR                       = 4,
    WRONG_FUNCTIONTIMER_TIME                   = 5,
    WRONG_MAILTIMER_TIME                       = 6,
    MAIL_TAIL_OVERWRITE                        = 7,
    HEAP_OVERWRITE                             = 8,
    SYNC_ERROR                                 = 9,
    MAIL_QUEUE_FULL                            = 0xa,
    ALLOC_MAIL_PACKET_IS_OxFF                  = 0xb,
    ALLOC_MAIL_PACKET_IS_NOT_O                 = 0xc,
    ERROR_BMC_INITIALIZE_ERROR                 = 0xd,
    DSP_WATCHDOG_ERROR                         = 0xe,
    XBC_STATE_ERROR                            = 0xf,
    NO_MORE_HEAP                               = 0x10,
    WRONG_RETURN_POINTER                       = 0x11,
    ERROR_START_TIME_ZERO                      = 0x12,
    HEAP_TAIL_OVERWRITE_IN_FREE                = 0x13,
    HEAP_TAIL_OVERWRITE_IN_ALLOC               = 0x14,
    HEAP_FILLDATA_OVERWRITE_IN_ALLOC           = 0x15,
    DB_NO_MORE_CONNECTION_IDENTITIES           = 0x16,
    ERROR_STACK_OVERFLOW                       = 0x17,
    ERROR_USB_STATE_ERROR                      = 0x18,
    ERROR_ISTACK_OVERFLOW                      = 0x19,

    ERROR_MAC__NO_MORE_AUDIO_BUFFERS           = 0x20,


    /* resource errors*/
    PROJCFG_NO_MORE_FREE_RESOURCES             = 0x50,
    PROJCFG_NO_MORE_INSTANCES                  = 0x51,
    PROJCFG_WRONG_CONNECTION_IDENTITIES        = 0x52,
    PROJCFG_INSTANCE_NOT_IN_USE                = 0x53,
    /* DataBase errors*/
    ERROR_DB_NO_MORE_SUBSCRIPTIONS             = 0x60,
    /* LU10 errors.*/
    ERROR_ACK_OUT_OF_SEQUENCE                  = 0x70,
    /* HW Errors*/
    ERROR_HW_FAIL                              = 0x100,
    ERROR_EEPROM,
    ERROR_FLASH,
    /* Kernel errors*/
    ERROR_OS_MAIL_QUEUE_FULL                   = 0x200,
    ERROR_OS_MAIL_TAIL_OVERWRITE,
    ERROR_OS_MAIL_DELIVERMAIL_NOT_CALLED,

    ERROR_OS_START_TIME_ZERO,
    ERROR_OS_INIT_TIMER_SYSTEM,
    ERROR_OS_HEAP__WRONG_RETURN_POINTER,
    ERROR_OS_HEAP__NO_MORE_HEAP,
    ERROR_OS_HEAP__TAIL_OVERWRITE_IN_FREE,
    ERROR_OS_HEAP__TAIL_OVERWRITE_IN_ALLOC,
    ERROR_OS_HEAP__FILLDATA_OVERWRITE_IN_ALLOC,
    ERROR_OS_HEAP__BLOCK_NOT_ALLOCATED,
    ERROR_OS_HEAP__NO_BLOCKS_ALLOCATED,

    ERROR_FUNCTIMER__STARTTIMER_INVALID_ID,
    ERROR_FUNCTIMER__STOPTIMER_INVALID_ID,
    ERROR_FUNCTIMER__STARTTIMER_VALUE_ZERO,

    ERROR_MAILTIMER__STARTTIMER_INVALID_ID,
    ERROR_MAILTIMER__STOPTIMER_INVALID_ID,
    ERROR_MAILTIMER__STARTTIMER_VALUE_ZERO,

    /* Kernel errors*/
    ERROR_EEPROM_WRONG_WRITE_ADR               = 0x300,
    ERROR_EEPROM_WRONG_READ_ADR,

    ERROR__URSULA_BDL_TASK__INVALID_BDLEI      = 0x400,

    /* Use the function Error_CustomRuntimeError (xx) for*/
    /* project specific errors.  This will produce the error*/
    /* 0xAAxx*/
    ERROR__CUSTOM_ERROR_BASE                   = 0xAA00,

    /* General errors*/
    ERROR_ASSERT_FAIL                          = 0xff00,
    ERROR_SHADOW_MAC__BDL_SYNC_LOST,
    /* Watch dog*/
    ERROR_V0_TRAP,
    ERROR_WATCH_DOG,
    ERROR_V2_TRAP,
    ERROR_V3_TRAP,
    ERROR_V4_TRAP,
    ERROR_SVC_TRAP,
    ERROR_DVZ_TRAP,
    ERROR_FLG_TRAP,
    ERROR_BPT_TRAP,
    ERROR_TRC_TRAP,
    ERROR_UND_TRAP,
    ERROR_V11_TRAP,
    ERROR_V12_TRAP,
    ERROR_V13_TRAP,
    ERROR_DBG_TRAP,
    ERROR_ISE_TRAP
};


/****************************************************************************
*                           Global variables/const
****************************************************************************/

/****************************************************************************
*                             Function prototypes
****************************************************************************/
/****************************************************************************
*  FUNCTION: Error_Init
*
*  INPUTS  : none
*  OUTPUTS : none
*  RETURNS : none
*
*  DESCRIPTION: Initiates the Error module.
*               If e.g. errors are stored in EEPROM they will be read by
*               this funciton
*
****************************************************************************/
void Error_Init(void);


/****************************************************************************
*  FUNCTION: Error_Flush
*
*  INPUTS  : none
*  OUTPUTS : none
*  RETURNS : none
*
*  DESCRIPTION: Clears all errors in EEPROM
*
****************************************************************************/
void Error_FlushErrors(void);


/****************************************************************************
*  FUNCTION: ERROR_ASSERT
*
*  INPUTS  : Condition - if condition is not true an Assert error is made
*  OUTPUTS : none
*  RETURNS : none
*
*  DESCRIPTION: Interface to assert errors.
*               By default disabled
*
****************************************************************************/
#ifdef ERROR_ENABLE_ASSERT
#if defined (PROM) || defined (EMULATOR)
/* Target version treats assert as a special case of runtime error. It does not store filenames to limit codesize*/
/* Line number is stored*/
#define ERROR_ASSERT( c )  { if ( !(c) ) { Error_HandleAssert( __LINE__); } }
#else
#define ERROR_ASSERT( c )  { if ( !(c) ) { Error_HandleAssert( __FILE__, __LINE__); } }
#endif
#else
#define ERROR_ASSERT( c )
#endif


/****************************************************************************
*  FUNCTION: Error_HandleAssert
*
*  INPUTS  : none
*  OUTPUTS : none
*  RETURNS : none
*
*  DESCRIPTION: Function behind ERROR_ASSERT macro.
*               Except for updating special EEPROM assert entry it behaves
*               like Error_RuntimeError
*
****************************************************************************/
#if defined (PROM) || defined (EMULATOR)
void Error_HandleAssert(uint16 line);
#else
void Error_HandleAssert(const char *pErrStr, uint16 line);
#endif

/****************************************************************************
*  FUNCTION: Error_RunTimeError
*
*  INPUTS  : ErrorCode - specifies the error code to be reported
*  OUTPUTS : none
*  RETURNS : none
*
*  DESCRIPTION: Macro wrapping for Error_RunTimeErrorHandler
*               Error_RuntimeErrorHandler updates the error array with errorcode
*               and if activated line number of caller.
*               It further more by default make a reset of the device
*
****************************************************************************/
#define Error_RunTimeError(e) Error_RunTimeErrorHandler(e,__LINE__)
void Error_RunTimeErrorHandler(uint16 errorCode, uint16 sourceLine);



/****************************************************************************
*  FUNCTION: Error_CustomRunTimeError
*
*  INPUTS  : ErrorCode - 8 bits error code specific to the calling module
*  OUTPUTS : none
*  RETURNS : none
*
*  DESCRIPTION: Macro wrapping for Error_RunTimeError
*               When calling this function in a module the errorcode will always
*               consist of the MSB of ERROR__CUSTOM_ERROR_BASE and the ErrorCode
*               supplied as argument.
*               Use this function for special errors not relevant for other modules
*               and therefor not worth putting into this file
*
****************************************************************************/
#define Error_CustomRuntimeError(x) Error_RunTimeError ((uint8)x & ERROR__CUSTOM_ERROR_BASE)

/****************************************************************************
*  FUNCTION: Error_WatchdogHandler
*
*  INPUTS  : none
*  OUTPUTS : none
*  RETURNS : none
*
*  DESCRIPTION: Error_WatchdogHandler is supposed to be called by ErrorWatchdogISR
*               when the watchdog 'bargs'.
*               If feature activated the mail queue will be flushed and special
*               watchdog related EEPROM entries will be updated.
*
****************************************************************************/
void Error_WatchdogHandler(void);

/****************************************************************************
*  FUNCTION: Error_WatchdogISR
*
*  INPUTS  : none
*  OUTPUTS : none
*  RETURNS : none
*
*  DESCRIPTION: Interrupt Service Routine for the watchdog.
*               This routine is a platform specific routine which is supposed
*               to call Error_WAtchdogHandler, but in special situations, e.g.
*               while running in EMULATOR it may behave different.
*
****************************************************************************/
INTERRUPT_FUNC(Error_WatchdogISR,ERROR_WATCHDOGISR_VECTOR_NR);

/****************************************************************************
*  FUNCTION: Error_ExceptionHandler
*
*  INPUTS  : Exception - Id of exception
*  OUTPUTS : none
*  RETURNS : none
*
*  DESCRIPTION: Routine to be called when special exceptions occur.
*               How and when it is called is platform dependant.
*               While called special Exception specific EEPROM values will be
*               updated.
*
****************************************************************************/
void Error_ExceptionHandler(uint16 Exception);

/****************************************************************************
*  FUNCTION: Error_HaltSw
*
*  INPUTS  : none
*  OUTPUTS : none
*  RETURNS : none
*
*  DESCRIPTION: On PC and in EMULATOR this routine will be called instead of
*               Error_SwReset. The function is platform specific while running
*               in emulator.
*
****************************************************************************/
extern void Error_HaltSw(void);
#endif








