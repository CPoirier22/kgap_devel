/*
 *-----------------------------------------------------------------------------
 *
 *               @@@@@@@      *   @@@@@@@@@           *
 *              @       @             @               *
 *              @             *       @      ****     *
 *               @@@@@@@      *       @     *    *    *
 *        ___---        @     *       @     ******    *
 *  ___---      @       @     *       @     *         *
 *   -_          @@@@@@@  _   *       @      ****     *
 *     -_                 _ -
 *       -_          _ -
 *         -_   _ -        s   e   m   i   c   o   n   d   u   c   t   o   r
 *           -
 *
 * (C) Copyright SiTel Semiconductor BV, unpublished work.
 * This computer program includes Confidential, Proprietary Information and
 * is a Trade Secret of SiTel Semiconductor BV.
 * All use, disclosure, and/or reproduction is prohibited unless authorized
 * in writing. All Rights Reserved.
 *----------------------------------------------------------------------------
 * $Workfile:   gdsp_functionmanager_api.h$
 * ========================================
 * Description: Type definitions and function prototypes of the API.
 * by:  G. Wolters & D. Lex
 * Part of Gen2DSP Functionmanager V1.3
 *-----------------------------------------------------------------------------
 */

/*#include "intrinsics.h"*/
/*#include "sitel_io.h"*/
#include "../../../../include/common/include/_stddef.h"
#include "../../../../include/common/include/map_480_gcc.h"
#ifndef BOOL
#define BOOL BOOLEAN
#endif
#ifdef SC14480
  /*#include "gen2dsp480_iar.h"*/
#endif
#ifdef SC14450
  /*#include "gen2dsp450_iar.h"*/
#endif
/*#include "gdsp_functionmanagerdefs.h"*/
/*typedef unsigned char GdspReturnCode;*/
/*=============================================================================*/
/* Global Defines                                                              */
/*=============================================================================*/
/* Interrupt vectors*/
#define INT1  				0x0001
#define INT2  				0x0002
#define INT3  				0x0004
#define INT4  				0x0008
#define INT5  				0x0010
#define INT6  				0x0020
#define INT7  				0x0040
#define INT8  				0x0080
#define INT9  				0x0100
#define INT10 				0x0200
#define INT11 				0x0400
#define INT12    			0x0800
#define INT13 	    		        0x1000
#define INT14 		    	        0x2000
#define INT15 			        0x4000
#define INT16 		    	        0x8000
#define OVERFLOW                        0xffff

/* PLL defines*/
#define PLL_40              40
#define PLL_80              80
#define PLL_124             124
#define PLL_160             160
#define PLL_OFF             0

/* CORE defines*/
#define DSP1 1
#define DSP2 2

/* DSP SYNC defines*/
#define DIPSYNC             2
#define FREERUNNING         1

#define GDSP_SUCCESS              7 /*  111 The execution of the GDSP API function was successful. */
#define GDSP_INVALID_PARAMETER    6 /*  110 One or more of the parameters in the function call are invalid */                                                    /* GDSP API function was invalid.                         */
#define GDSP_NO_SUCCESS           5 /*  101 The execution of the GDSP API function was not successful */

#define NO_OF_INT     16  /* number of possible interrupts for sc14450 OR 480 devices */

typedef unsigned char DriverReturnCode;

/*==============================INCLUDE FILES======================================*/

/*=============================================================================*/
/*  Data type definitions                                                      */
/*=============================================================================*/
typedef enum
{
  GDSP_SLAVE = 0,                     /* PCM interface mode               */
  GDSP_MASTER = 1
}
GDSP_PCM_INT_MODE;


typedef struct
{
  BOOL int_enabled;                   /* Interrupts enabled               */
  BYTE int_priority;                  /* Interrupt priority: 0=disabled,  */
                                      /* 1=lowest, 7=highest              */
  GDSP_PCM_INT_MODE pcm_interf_mode;  /* PCM interface mode  */
}
GDSP_INTERFACE_INIT_STRUCT;


/*=============================================================================*/
/*  Callback function type                                                     */
/*=============================================================================*/
typedef void (*GdspCallbackFn)(WORD vector);

typedef struct
{
	WORD int_vector;                /*interrupt vector*/
	GdspCallbackFn cb_function;     /* pointer to callback function*/
} GDSP_INT_STRUCT;

/*=============================================================================*/
/* init function prototypes                                                     */
/*=============================================================================*/
void Pll_On();
void InitDSPCODEC(void);
void InitDSPSYNC(BYTE syncsource);
void InitInterrupts(GDSP_INIT_STRUCT init);
void SetInterrupPrio(unsigned short int_number, unsigned short input_number, unsigned short core_number);

/*=============================================================================*/
/* API function prototypes                                                     */
/*=============================================================================*/
DriverReturnCode InitGdspInterface(GDSP_INTERFACE_INIT_STRUCT interface_init);
DriverReturnCode GdspStartDsp(BYTE syncsource);
DriverReturnCode GdspStopDsp(void);
DriverReturnCode GdspHookVector(WORD vector,GdspCallbackFn cb_function, unsigned short core);
DriverReturnCode GdspUnhookVector(WORD int_vect, unsigned short core);

