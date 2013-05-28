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
 * $Workfile:   gdsp_driver_functions.c$
 * =========================
 * Description: Implementation of the Gen2DSP function manager API.
 * by:  G. Wolters & D. Lex
 * Part of Gen2DSP Functionmanager V1.3          
 *-----------------
 * ------------------------------------------------------------*/
#include "gdsp_functionmanager_api.h"
#include "gdsp_driver_functions_api.h"
#include "../../../../../../include/common/include/map_480_gcc.h"

#define GetByte(a)  	(* (  volatile BYTE*)(a) )
#define GetWord(a)  	(* (  volatile WORD*)(a) )
#define GetDword(a)  	(* (  volatile DWORD*)(a) )
#define GetBits(a,f)	(( (  volatile struct __##a *)(a))->BITFLD_##f )
#define GetDbits(a,f)	(( (  volatile struct __##a *)(a))->BITFLD_##f )
#define SetByte(a,d)	(* (  volatile BYTE*)(a)=(d) )
#define SetWord(a,d)	(* (  volatile WORD*)(a)=(d) )
#define SetDword(a,d)	(* (  volatile DWORD*)(a)=(d) )
#define SetBits(a,f,d)	( SetWord( a, (GetWord(a)&(~(WORD)f)) | ((WORD)(d)<<SHIF(f)) ))
#define SetDbits(a,f,d)	( SetDword(a, (GetDword(a)&(~(DWORD)f)) | (((DWORD)d)<<DSHIF(f)) ))

/*======================LOCAL VARIABLES====================================*/

#if MAX_NO_FM_DSP_CORES >1
volatile GDSP_INT_STRUCT gdspInterrupts[NO_OF_INT+1+16]; //Array of interrupts and pointers to callback functions
#else
volatile GDSP_INT_STRUCT gdspInterrupts[NO_OF_INT + 1]; //Array of interrupts and pointers to callback functions
#endif

/*===========================Local Function Prototypes=======================================*/
void GdspInitGlobalVariables(void);
void gdsp_isr(WORD int_vector);

/* hardware dependent interrupts */
inline void HwInitInterrupts(BOOL int_enabled);
inline void HwSetIntMask(WORD int_vect, unsigned short core);
inline void HwResetIntMask(WORD int_vect, unsigned short core);
inline void HwDspStart(void);
inline void HwDspStop(void);
inline void HwInitPcm(WORD mode);
#ifdef GDSP_PCMMASTERSOURCE
inline void HwSetPcmMasters( gdsp_pcmmastersource* pcm_master );
#endif

#ifdef SC14450
#define DSP_INT_PRIO  DSP1_INT_PRIO
#define DSP_INT DSP1_INT
#define DSP_INT_PEND DSP1_INT_PEND
#define DSP_MC_RAM_START DSP_MC_RAM1_START
#endif

DriverReturnCode InitGdspInterface(GDSP_INTERFACE_INIT_STRUCT interface_init) {
	GdspInitGlobalVariables();
	HwInitPcm(interface_init.pcm_interf_mode);
	if (interface_init.int_priority == 0 || interface_init.int_priority > 7) {
		SetBits(INT0_PRIORITY_REG_ADDR, DSP_INT_PRIO, 0x0000);
#ifdef SC14450
		SetBits(INT0_PRIORITY_REG, DSP2_INT_PRIO, 0x0000);
#endif
	} else {
		SetBits(INT0_PRIORITY_REG_ADDR, DSP_INT_PRIO, interface_init.int_priority);
#ifdef SC14450
		SetBits(INT0_PRIORITY_REG, DSP2_INT_PRIO, interface_init.int_priority);
#endif
	}
	HwInitInterrupts(interface_init.int_enabled);
	return GDSP_SUCCESS;
}

/*========================================================================================*/
/*  Function       : DriverReturnCode GdspHookVector(unsigned short int_vect, GdspCallbackFn cb_func)
 *
 *  Purpose        : Hooks callback function to Gen2DSP interrupt vector.
 */
/*========================================================================================*/
DriverReturnCode GdspHookVector(unsigned short int_vect,
		GdspCallbackFn cb_func, unsigned short core) {
	unsigned short i;
	unsigned short offset;
	unsigned short no_of_int;

	if ((core == 2) && (MAX_NO_FM_DSP_CORES > 1)) {
		no_of_int = NO_OF_INT + 17;
		offset = 17;
	} else {
		no_of_int = NO_OF_INT + 1;
		offset = 0;
	}
	// Find interrupt vector in registration   
	for (i = offset; i < no_of_int; i++) {
		if (gdspInterrupts[i].int_vector == int_vect) {
			HwSetIntMask(int_vect, core);
			gdspInterrupts[i].cb_function = cb_func;
			return GDSP_SUCCESS;
		}
	}
	return GDSP_INVALID_PARAMETER;
}
/*========================================================================================*/
/*  Function       : DriverReturnCode GdspUnhookVector(unsigned short int_vect)
 *
 *  Purpose        : Unhooks callback function from Gen2DSP interrupt vector.
 */
/*========================================================================================*/
DriverReturnCode GdspUnhookVector(unsigned short int_vect, unsigned short core) {
	unsigned short i;
	unsigned short offset;
	unsigned short no_of_int;

	if ((core == 2) && (MAX_NO_FM_DSP_CORES > 1)) {
		no_of_int = NO_OF_INT + 17;
		offset = 17;
	} else {
		no_of_int = NO_OF_INT + 1;
		offset = 0;
	}

	// Find interrupt vector in registration 
	for (i = offset; i < no_of_int; i++) {
		if (gdspInterrupts[i].int_vector == int_vect) {
			HwResetIntMask(int_vect, core);
			gdspInterrupts[i].cb_function = 0;

			return GDSP_SUCCESS;
		}
	}
	return GDSP_NO_SUCCESS;
}
/*============================================================================================*/
/*  Function       : void GdspInitGlobalVariables(void)
 *
 *  Purpose        : Initializes global variables
 */
/*============================================================================================*/
void GdspInitGlobalVariables(void) {
	WORD i;
	unsigned short no_of_int;

	// Initialize interrupt registration
	gdspInterrupts[0].int_vector = OVERFLOW;
	gdspInterrupts[1].int_vector = INT1;
	gdspInterrupts[2].int_vector = INT2;
	gdspInterrupts[3].int_vector = INT3;
	gdspInterrupts[4].int_vector = INT4;
	gdspInterrupts[5].int_vector = INT5;
	gdspInterrupts[6].int_vector = INT6;
	gdspInterrupts[7].int_vector = INT7;
	gdspInterrupts[8].int_vector = INT8;
	gdspInterrupts[9].int_vector = INT9;
	gdspInterrupts[10].int_vector = INT10;
	gdspInterrupts[11].int_vector = INT11;
	gdspInterrupts[12].int_vector = INT12;
	gdspInterrupts[13].int_vector = INT13;
	gdspInterrupts[14].int_vector = INT14;
	gdspInterrupts[15].int_vector = INT15;
	gdspInterrupts[16].int_vector = INT16;
#if MAX_NO_FM_DSP_CORES > 1

	gdspInterrupts[17].int_vector = INT1;
	gdspInterrupts[18].int_vector = INT2;
	gdspInterrupts[19].int_vector = INT3;
	gdspInterrupts[20].int_vector = INT4;
	gdspInterrupts[21].int_vector = INT5;
	gdspInterrupts[22].int_vector = INT6;
	gdspInterrupts[23].int_vector = INT7;
	gdspInterrupts[24].int_vector = INT8;
	gdspInterrupts[25].int_vector = INT9;
	gdspInterrupts[26].int_vector = INT10;
	gdspInterrupts[27].int_vector = INT11;
	gdspInterrupts[28].int_vector = INT12;
	gdspInterrupts[29].int_vector = INT13;
	gdspInterrupts[30].int_vector = INT14;
	gdspInterrupts[31].int_vector = INT15;
	gdspInterrupts[32].int_vector = INT16;
	no_of_int = NO_OF_INT + 16;

#else
	no_of_int = NO_OF_INT;
#endif

	for (i = 0; i < no_of_int; i++) {
		gdspInterrupts[i].cb_function = 0;
	}

}

/*============================================================================================
 Function       : DriverReturnCode GdspStartDsp(BYTE syncsource)
 Purpose       : Power up Gen2DSP
 ============================================================================================*/
DriverReturnCode GdspStartDsp(BYTE syncsource) {

	// Power up Gen2DSP
	HwDspStart();
	InitDSPSYNC(syncsource);

	return GDSP_SUCCESS;
}
/*============================================================================================
 Function       : DriverReturnCode GdspStopDsp(void)
 Purpose        : Power down the Gen2DSP
 ============================================================================================*/
DriverReturnCode GdspStopDsp(void) {
	BYTE result;

	HwDspStop();
	result = GDSP_SUCCESS;
	return result;
}

/*============================================================================================
 Function       : void gdsp_isr( WORD intvector )
 Purpose        : The hardware independent part of the Gen2DSP ISR
 ============================================================================================*/
void gdsp_isr(WORD int_vector) {
	if ((int_vector & OVERFLOW) == OVERFLOW) {
		if (gdspInterrupts[0].cb_function != 0) {
			(*gdspInterrupts[0].cb_function)(int_vector);
		}
	}
	if ((int_vector & INT1) == INT1) {
		if (gdspInterrupts[1].cb_function != 0) {
			(*gdspInterrupts[1].cb_function)(int_vector);
		}
	}

	if ((int_vector & INT2) == INT2) {
		if (gdspInterrupts[2].cb_function != 0) {
			(*gdspInterrupts[2].cb_function)(int_vector);
		}
	}

	if ((int_vector & INT3) == INT3) {
		if (gdspInterrupts[3].cb_function != 0) {
			(*gdspInterrupts[3].cb_function)(int_vector);
		}
	}

	if ((int_vector & INT4) == INT4) {
		if (gdspInterrupts[4].cb_function != 0) {
			(*gdspInterrupts[4].cb_function)(int_vector);
		}
	}

	if ((int_vector & INT5) == INT5) {
		if (gdspInterrupts[5].cb_function != 0) {
			(*gdspInterrupts[5].cb_function)(int_vector);
		}
	}

	if ((int_vector & INT6) == INT6) {
		if (gdspInterrupts[6].cb_function != 0) {
			(*gdspInterrupts[6].cb_function)(int_vector);
		}
	}

	if ((int_vector & INT7) == INT7) {
		if (gdspInterrupts[7].cb_function != 0) {
			(*gdspInterrupts[7].cb_function)(int_vector);
		}
	}

	if ((int_vector & INT8) == INT8) {
		if (gdspInterrupts[8].cb_function != 0) {
			(*gdspInterrupts[8].cb_function)(int_vector);
		}
	}

	if ((int_vector & INT9) == INT9) {
		if (gdspInterrupts[9].cb_function != 0) {
			(*gdspInterrupts[9].cb_function)(int_vector);
		}
	}

	if ((int_vector & INT10) == INT10) {
		if (gdspInterrupts[10].cb_function != 0) {
			(*gdspInterrupts[10].cb_function)(int_vector);
		}
	}

	if ((int_vector & INT11) == INT11) {
		if (gdspInterrupts[11].cb_function != 0) {
			(*gdspInterrupts[11].cb_function)(int_vector);
		}
	}

	if ((int_vector & INT12) == INT12) {
		if (gdspInterrupts[12].cb_function != 0) {
			(*gdspInterrupts[12].cb_function)(int_vector);
		}
	}

	if ((int_vector & INT13) == INT13) {
		if (gdspInterrupts[13].cb_function != 0) {
			(*gdspInterrupts[13].cb_function)(int_vector);
		}
	}

	if ((int_vector & INT14) == INT14) {
		if (gdspInterrupts[14].cb_function != 0) {
			(*gdspInterrupts[14].cb_function)(int_vector);
		}
	}

	if ((int_vector & INT15) == INT15) {
		if (gdspInterrupts[15].cb_function != 0) {
			(*gdspInterrupts[15].cb_function)(int_vector);
		}
	}

	if ((int_vector & INT16) == INT16) {
		if (gdspInterrupts[16].cb_function != 0) {
			(*gdspInterrupts[16].cb_function)(int_vector);
		}
	}
}

#if MAX_NO_FM_DSP_CORES > 1
/*============================================================================================
 Function       : void gdsp_isr( WORD intvector )
 Purpose        : The hardware independent part of the Gen2DSP ISR
 ============================================================================================*/
void gdsp2_isr( WORD int_vector )
{
	if ((int_vector & INT1) == INT1)
	{
		if (gdspInterrupts[17].cb_function != 0)
		{
			(*gdspInterrupts[17].cb_function)(int_vector);
		}
	}

	if ((int_vector & INT2) == INT2)
	{
		if (gdspInterrupts[18].cb_function != 0)
		{
			(*gdspInterrupts[18].cb_function)(int_vector);
		}
	}

	if ((int_vector & INT3) == INT3)
	{
		if (gdspInterrupts[19].cb_function != 0)
		{
			(*gdspInterrupts[19].cb_function)(int_vector);
		}
	}

	if ((int_vector & INT4) == INT4)
	{
		if (gdspInterrupts[20].cb_function != 0)
		{
			(*gdspInterrupts[20].cb_function)(int_vector);
		}
	}

	if ((int_vector & INT5) == INT5)
	{
		if (gdspInterrupts[21].cb_function != 0)
		{
			(*gdspInterrupts[21].cb_function)(int_vector);
		}
	}

	if ((int_vector & INT6) == INT6)
	{
		if (gdspInterrupts[22].cb_function != 0)
		{
			(*gdspInterrupts[22].cb_function)(int_vector);
		}
	}

	if ((int_vector & INT7) == INT7)
	{
		if (gdspInterrupts[23].cb_function != 0)
		{
			(*gdspInterrupts[23].cb_function)(int_vector);
		}
	}

	if ((int_vector & INT8) == INT8)
	{
		if (gdspInterrupts[24].cb_function != 0)
		{
			(*gdspInterrupts[24].cb_function)(int_vector);
		}
	}

	if ((int_vector & INT9) == INT9)
	{
		if (gdspInterrupts[25].cb_function != 0)
		{
			(*gdspInterrupts[25].cb_function)(int_vector);
		}
	}

	if ((int_vector & INT10) == INT10)
	{
		if (gdspInterrupts[26].cb_function != 0)
		{
			(*gdspInterrupts[26].cb_function)(int_vector);
		}
	}

	if ((int_vector & INT11) == INT11)
	{
		if (gdspInterrupts[27].cb_function != 0)
		{
			(*gdspInterrupts[27].cb_function)(int_vector);
		}
	}

	if ((int_vector & INT12) == INT12)
	{
		if (gdspInterrupts[28].cb_function != 0)
		{
			(*gdspInterrupts[28].cb_function)(int_vector);
		}
	}

	if ((int_vector & INT13) == INT13)
	{
		if (gdspInterrupts[29].cb_function != 0)
		{
			(*gdspInterrupts[29].cb_function)(int_vector);
		}
	}

	if ((int_vector & INT14) == INT14)
	{
		if (gdspInterrupts[30].cb_function != 0)
		{
			(*gdspInterrupts[30].cb_function)(int_vector);
		}
	}

	if ((int_vector & INT15) == INT15)
	{
		if (gdspInterrupts[31].cb_function != 0)
		{
			(*gdspInterrupts[31].cb_function)(int_vector);
		}
	}

	if ((int_vector & INT16) == INT16)
	{
		if (gdspInterrupts[32].cb_function != 0)
		{
			(*gdspInterrupts[32].cb_function)(int_vector);
		}
	}
}
#endif
/*
 **************************************************************
 *    HW dependent functions
 **************************************************************
 */

/*=======================================================================================
 Purpose        : Pointers to all needed peripherlal addresses above 0x1000000
 Needed as work-around for the IAR compiler
 =========================================================================================*/

const __data24 uint16* drv_dsp_main_sync0_reg = (uint16*)DSP_MAIN_SYNC0_REG_ADDR;
const __data24 uint16* drv_dsp_main_sync1_reg = (uint16*)DSP_MAIN_SYNC1_REG_ADDR;
const __data24 uint16* drv_dsp_main_ctrl_reg = (uint16*)DSP_MAIN_CTRL_REG_ADDR;
const __data24 uint16* drv_dsp_pcm_ctrl_reg = (uint16*)DSP_PCM_CTRL_REG_ADDR;
const __data24 uint16* drv_dsp_pcm_in0_reg = (uint16*)DSP_PCM_IN0_REG_ADDR;
const __data24 uint16* drv_dsp_pcm_in1_reg = (uint16*)DSP_PCM_IN1_REG_ADDR;
const __data24 uint16* drv_dsp_pcm_in2_reg = (uint16*)DSP_PCM_IN2_REG_ADDR;
const __data24 uint16* drv_dsp_pcm_in3_reg = (uint16*)DSP_PCM_IN3_REG_ADDR;

#ifdef SC14480
const __data24 uint16* drv_dsp_pc_start_reg = (uint16*)DSP_PC_START_REG_ADDR;
const __data24 uint16* drv_dsp_int_mask_reg = (uint16*)DSP_INT_MASK_REG_ADDR;
const __data24 uint16* drv_dsp_irq_start_reg = (uint16*)DSP_IRQ_START_REG_ADDR;
const __data24 uint16* drv_dsp_int_reg = (uint16*)DSP_INT_REG_ADDR;
const __data24 uint16* drv_dsp_int_prio1_reg = (uint16*)DSP_INT_PRIO1_REG_ADDR;
const __data24 uint16* drv_dsp_int_prio2_reg = (uint16*)DSP_INT_PRIO2_REG_ADDR;
const __data24 uint16* drv_dsp_ctrl_reg = (uint16*)DSP_CTRL_REG_ADDR;
#endif

#ifdef SC14450
const __data24 uint16* drv_dsp_pc_start_reg = (uint16*)DSP1_PC_START_REG;
const __data24 uint16* drv_dsp_int_mask_reg = (uint16*)DSP1_INT_MASK_REG;
const __data24 uint16* drv_dsp_irq_start_reg = (uint16*)DSP1_IRQ_START_REG;
const __data24 uint16* drv_dsp_int_reg = (uint16*)DSP1_INT_REG;
const __data24 uint16* drv_dsp_int_prio1_reg = (uint16*)DSP1_INT_PRIO1_REG;
const __data24 uint16* drv_dsp_int_prio2_reg = (uint16*)DSP1_INT_PRIO2_REG;
const __data24 uint16* drv_dsp_ctrl_reg = (uint16*)DSP1_CTRL_REG;

const __data24 uint16* drv_dsp2_pc_start_reg = (uint16*)DSP2_PC_START_REG;
const __data24 uint16* drv_dsp2_int_mask_reg = (uint16*)DSP2_INT_MASK_REG;
const __data24 uint16* drv_dsp2_irq_start_reg = (uint16*)DSP2_IRQ_START_REG;
const __data24 uint16* drv_dsp2_int_reg = (uint16*)DSP2_INT_REG;
const __data24 uint16* drv_dsp2_int_prio1_reg = (uint16*)DSP2_INT_PRIO1_REG;
const __data24 uint16* drv_dsp2_int_prio2_reg = (uint16*)DSP2_INT_PRIO2_REG;
const __data24 uint16* drv_dsp2_ctrl_reg = (uint16*)DSP2_CTRL_REG;
#endif

/*========================================================================================*/
/*  Function       : __interrupt void GdspISR(void)
 *
 *  Purpose        : Gets Gen2DSP interrupt vector, clears interrupt, passes vector
 *                   on to registered callback functions.
 */
/*========================================================================================*/
void GdspISR(void) // Handled from mac_user_main.c
{
	volatile WORD int_vector;
	int_vector = GetWord( drv_dsp_int_reg );
	SetWord(drv_dsp_int_reg, int_vector); // write back vector to clear the vector bits
	// HM TODO - until then make sure interrupt is cleared in function instead
	//SetWord(0xFF5402, DSP_INT_PEND); // Clear pending bit - RESET_INT_PENDING_REG,
	gdsp_isr(int_vector);
}

#ifdef SC14450
#if MAX_NO_FM_DSP_CORES >1
/*========================================================================================*/
/*  Function       : __interrupt void Gdsp2ISR(void)
 *
 *  Purpose        : Gets Gen2DSP interrupt vector, clears interrupt, passes vector
 *                   on to registered callback functions.
 */
/*========================================================================================*/

#pragma vector=DSP2_INT
__interrupt void Gdsp2ISR(void)
{
	volatile WORD int_vector;

	int_vector = GetWord( drv_dsp2_int_reg );
	SetWord(drv_dsp2_int_reg, int_vector); // write back vector to clear the vector bits
	SetWord(RESET_INT_PENDING_REG, DSP2_INT_PEND); // Clear pending bit
	gdsp2_isr( int_vector );
}
#endif
#endif
/*============================================================================================
 Function       : void HwInitInterrupts( BOOL int_enabled )
 Purpose        : Enable interrupts id int_enabled
 ============================================================================================*/
inline void HwInitInterrupts(BOOL int_enabled) {
	if (int_enabled == TRUE) {
		SetWord( drv_dsp_int_mask_reg, 0); /* Mask all DSP interrupts   */
		SetWord( RESET_INT_PENDING_REG_ADDR, DSP_INT_PEND ); /* Clear  DSP interrupts        */
#ifdef SC14450
		SetWord( drv_dsp2_int_mask_reg, 0); /* Mask all DSP interrupts   */
		SetWord( RESET_INT_PENDING_REG_ADDR, DSP2_INT_PEND ); /* Clear  DSP interrupts        */
#endif
		__enable_interrupt();
		__set_PSR_I_bit();
	} else {
		__disable_interrupt();
	}
}

/*============================================================================================
 Function       : void HwSetIntMask( WORD int_vec )
 Purpose        : Set interrupt mask, according to int_vec
 ============================================================================================*/
inline void HwSetIntMask(WORD int_vect, unsigned short core) {
	if (core == 2) {
#ifdef SC14450
		WORD temp_mask = GetWord(drv_dsp2_int_mask_reg);
		SetWord(drv_dsp2_int_mask_reg, temp_mask | int_vect );
#endif
	} else {
		WORD temp_mask = GetWord(drv_dsp_int_mask_reg);
		SetWord(drv_dsp_int_mask_reg, temp_mask | int_vect );
	}
}

/*============================================================================================
 Function       : void HwResetIntMask( WORD int_vec )
 Purpose        : Reset interrupt mask, according to int_vec
 ============================================================================================*/
inline void HwResetIntMask(WORD int_vect, unsigned short core) {
	if (core == 2) {
#ifdef SC14450
		WORD temp_mask = GetWord( drv_dsp2_int_mask_reg );
		SetWord( drv_dsp2_int_mask_reg, temp_mask & ~int_vect );
#endif
	} else {
		WORD temp_mask = GetWord( drv_dsp_int_mask_reg );
		SetWord( drv_dsp_int_mask_reg, temp_mask & ~int_vect );
	}
}

/*============================================================================================
 Function       : void HwDspStart( void )
 Purpose        : Start the Gen2DSP
 =========================================================================================*/
inline void HwDspStart(void) {
	SetWord( drv_dsp_ctrl_reg, 0x0004); // Switch on DSP & DSP clock
#ifdef SC14450
	if(MAX_NO_FM_DSP_CORES >1) {
		SetWord( drv_dsp2_ctrl_reg, 0x0004); // Switch on DSP & DSP clock
	}
#endif
}

/*============================================================================================
 Function       : void HwDspStop( void )
 Purpose        : Stop the Gen2DSP
 =========================================================================================*/
inline void HwDspStop(void) {
	SetWord( drv_dsp_ctrl_reg, 0x0000); // Switch off DSP
#ifdef SC14450
	if(MAX_NO_FM_DSP_CORES >1) {
		SetWord( drv_dsp2_ctrl_reg, 0x0000); // Switch off DSP
	}
#endif
}

/*============================================================================================
 Function       : void HwInitPcm( WORD mode )
 Purpose        : initiate the PCM
 =========================================================================================*/
inline void HwInitPcm(WORD mode) {
	if (mode == GDSP_MASTER) {
		SetBits( drv_dsp_pcm_ctrl_reg, PCM_MASTER, 1 );
	} else {
		SetBits( drv_dsp_pcm_ctrl_reg, PCM_MASTER , 0);
	}
}

/*============================================================================================
 Function       : void HwSetPcmMasters( gdsp_pcmmastersource* pcm_master )
 Purpose        : Set peripheral addresses for PCM masters in PCVM data structure
 =========================================================================================*/
#ifdef GDSP_PCMMASTERSOURCE
inline void HwSetPcmMasters( gdsp_pcmmastersource* pcm_master )
{
	// offset from start of block to PCM20_REG
	pcm_master->srcstart = per_offset( drv_dsp_pcm_in0_reg );
	// offset from start of block to PCM21_REG
	pcm_master->srcend = per_offset( drv_dsp_pcm_in1_reg );
}
#endif

void SetInterrupPrio(unsigned short int_number, unsigned short input_number,
		unsigned short core_number) {
	if (core_number == 2) {
#ifdef SC14450
		if (input_number < 3)
		{
			SetBits(drv_dsp2_int_prio1_reg, (0x0700 >> (input_number*4)), int_number);
		}
		else {
			SetBits(drv_dsp2_int_prio2_reg, (0x0700 >> ((input_number-3)*4)), int_number);
		}
#endif
	} else {
		if (input_number < 3) {
			SetBits(drv_dsp_int_prio1_reg, (0x0700 >> (input_number*4)), int_number);
		} else {
			SetBits(drv_dsp_int_prio2_reg, (0x0700 >> ((input_number-3)*4)), int_number);
		}
	}
}

/*******************************************************************************************
 *  Function       : void InitInterrupts(BYTE no_contexts)                                *
 *  Purpose        : Set the interrupt priorities                                          *
 *******************************************************************************************/

void InitInterrupts(GDSP_INIT_STRUCT init) {
	unsigned short i;
	CONTEXT_TYPE Context;
	interrupt_souce_type Int_input;

	SetBits(drv_dsp_main_sync1_reg, DSP_SYNC0,0); // 8KHZ strobe to SYNC0
	SetBits(drv_dsp_main_sync1_reg, DSP_SYNC1,1); // 16KHZ strobe to SYNC1
	SetBits(drv_dsp_main_sync1_reg, DSP_SYNC2,2); // 32KHZ strobe to SYNC2

	for (i = 0; i < init.no_contexts; i++) {
		Context = init.dsp_context_memory_config[i].context_id;
		Int_input = init.dsp_context_memory_config[i].interrupt_source;

		switch (Context) {
		case GDSP_DSP1_BACKGROUND_CONTEXT:
			break;
		case GDSP_DSP1_8KHZ_CONTEXT:
			SetInterrupPrio(0, Int_input, 1);
			break;
		case GDSP_DSP1_16KHZ_CONTEXT:
			SetInterrupPrio(1, Int_input, 1);
			break;
		case GDSP_DSP1_32KHZ_CONTEXT:
			SetInterrupPrio(2, Int_input, 1);
			break;
		case GDSP_DSP1_DSP2INT_CONTEXT:
			SetInterrupPrio(3, Int_input, 1);
			break;
		case GDSP_DSP1_DIPINT_CONTEXT:
			SetInterrupPrio(4, Int_input, 1);
			break;
		case GDSP_DSP1_CR16INT_CONTEXT:
			SetInterrupPrio(5, Int_input, 1);
			break;
		case GDSP_DSP2_BACKGROUND_CONTEXT:
			break;
		case GDSP_DSP2_8KHZ_CONTEXT:
			SetInterrupPrio(0, Int_input, 2);
			break;
		case GDSP_DSP2_16KHZ_CONTEXT:
			SetInterrupPrio(1, Int_input, 2);
			break;
		case GDSP_DSP2_32KHZ_CONTEXT:
			SetInterrupPrio(2, Int_input, 2);
			break;
		case GDSP_DSP2_DSP1INT_CONTEXT:
			SetInterrupPrio(3, Int_input, 2);
			break;
		case GDSP_DSP2_DIPINT_CONTEXT:
			SetInterrupPrio(4, Int_input, 2);
			break;
		case GDSP_DSP2_CR16INT_CONTEXT:
			SetInterrupPrio(5, Int_input, 2);
			break;
		default:
			break;

		}
	}

}

void InitDSPSYNC(BYTE syncsource) {
	SetBits(drv_dsp_main_ctrl_reg, DSP_MAIN_CTRL, 0); // DSP main counter in reset.

	switch (syncsource) {
	case DIPSYNC:
		SetBits(drv_dsp_main_ctrl_reg, DSP_MAIN_PRESET, 0xF); // DSP main preset value set to 15.
		SetBits(drv_dsp_main_ctrl_reg, DSP_MAIN_CTRL, 2); // DSP main counter out of reset, free running
		break;
	case FREERUNNING:
		SetBits(drv_dsp_main_ctrl_reg, DSP_MAIN_CTRL, 1); // DSP main counter out of reset, free running
		break;
	default:
		break;
	}
}

/*******************************************************************************************
 *  Function       : void Pll_on()                                                         *
 *  Purpose        : Switch to PLL Clock                                                   *
 *  Affects        : CLK_PLL_CTRL_REG                                                      *
 *******************************************************************************************/
void Pll_On() {
	WORD i;
	for (i = 0; i < 1000; i++)
		;
#ifdef SC14450
	SetBits(CLK_PLL_CTRL_REG_ADDR, PLL_CLK_SEL,1); // PLL on
#else
	SetBits(CLK_PLL_CTRL_REG_ADDR, PLL_CLK_SEL,1); // PLL on
#endif
}

/********************************************************************************************
 *                                                                                          *
 *                             SC14450 Specific functions                                   *
 *                                                                                          * 
 ********************************************************************************************/
#ifdef SC14450

/*******************************************************************************************
 *  Function         : void InitClocks(BYTE pll_freq)                                      *
 *  Purpose          : Select PLL fequency or select XTAL frequency.                       *
 *                     Set Main clock, Codec AD/DA clocks, ClassD clock and PCM clock      *
 *                     The Function is valid for execution from FLASG                      *
 *                     This function can be used to increase/decrease DSP/CR16 performance *
 *                     while maintaing the DIP synchronisation (10.368 DIP clock)          * 
 *  Precondition     : Function can be called to switch from any given clock setting to    *
 *                     another setting. This is done by providing the desired PLL mode as  *
 *                     argument. Audio must be muted and DSP must be stopped because the   *
 *                     codec clock generation is derived from the PLL/2 path in order to   *
 *                     support wide band audio                                             *
 *  Postcondition    : HCLK and PCLK are set to the highest possible frequency for FLASH   *
 *                     and ROM. Although execution from RAM can be faster, it is kept      *
 *                     the same as ROM and FLASH                                           *
 *                     AMBA_CLK_REG[MEM_STROBE] is set to optimal value for power saving   *
 *                     MEM_CONFIG_REG[T_RC] is set to optimal value for FLASH access       *
 *                     (this is don't care for ROM and RAM access)                         *
 *  Argument defines : PLL_40  = 41,472 MHz PLL clock                                      *
 *                     PLL_80  = 82,944 MHz PLL clock                                      *
 *                     PLL_160 = 165.88 MHz PLL clock                                      *
 *  Note 1           : To use wideband audio pre define WIDEBAND in the project settings   *
 *******************************************************************************************/
void InitClockRegisters(BYTE pll_freq)
{
	WORD i;
	SetBits(CLK_PLL1_CTRL_REG, PLL_CLK_SEL,0); // PLL off
	for(i=0;i<10;i++);
	SetWord(CLK_PLL1_CTRL_REG, 0x0800); // Switch to XTAL mode before changing PLL mode
	SetWord(CLK_CODEC_DIV_REG,0x9);
	SetBits(CLK_AMBA_REG,HCLK_DIV,1); // CR16C clock @ 10Mhz
	SetWord(CLK_PER_DIV_REG, 9);

	switch (pll_freq) {
		case PLL_40:
		SetBits(CLK_AMBA_REG,HCLK_DIV,1); // CR16C clock @ 20Mhz
		// turn on pll
		SetWord(CLK_PLL1_DIV_REG ,0x005); // PLL @ 41,472 Mhz
		SetWord(CLK_PER_DIV_REG, 9);
		SetWord(CLK_CODEC_DIV_REG,0x92);
		SetWord(CLK_PLL1_CTRL_REG, 0x200 | DYN_SW | VCO_ON | CP_ON); // PLL_DIP_DIV = 4 Dip lck @ 10.368 MHz
		Pll_On(); // Switch to PLL clock
		break;
		case PLL_80:
		SetBits(CLK_AMBA_REG,HCLK_DIV,1); // CR16C clock @ 40Mhz
		// turn on pll
		SetWord(CLK_PLL1_DIV_REG ,0x001D); // PLL @ 80 Mhz
		SetWord(CLK_PER_DIV_REG, 9);
		SetWord(CLK_CODEC_DIV_REG,0xA4);
		SetWord(CLK_PLL1_CTRL_REG, 0x400 | DYN_SW | HF_SEL | VCO_ON | CP_ON); // PLL_DIP_DIV = 8, Dip clock @ 10.368 MHz
		Pll_On(); // Switch to PLL clock
		break;
		case PLL_160:
		SetBits(CLK_AMBA_REG,HCLK_DIV,2); // CR16C clock @ 40Mhz
		// turn on pll
		SetWord(CLK_PLL1_DIV_REG ,0x001C); // PLL @ 165.88 Mhz
		SetWord(CLK_PER_DIV_REG, 9);
		SetWord(CLK_CODEC_DIV_REG,0xC8);
		SetWord(CLK_PLL1_CTRL_REG, DYN_SW | HF_SEL | VCO_ON | CP_ON); // PLL_DIP_DIV = 0, Dip clock @ 10.368 MHz
		Pll_On(); // Switch to PLL clock
		break;
		case PLL_OFF:
		// XTAL mode is selected at function entry
		break;
		default:
		break;
	}

#ifdef WIDEBAND
	SetWord(CLK_CODEC_REG, 0x7DA9); // Main clock @ 1.152 MHz, Codec AD/DA clocks, ClassD clock @ 2.304 MHz, PCM clock @ 1.152 MHz
#else
	SetWord(CLK_CODEC_REG, 0x7D55); // Main clock @ 1.152 MHz, Codec AD/DA clocks, ClassD clock @ 1.152 MHz, PCM clock @ 1.152 MHz
#endif
	SetBits(CLK_AMBA_REG, MCRAM1_EN, 1);
	SetBits(CLK_AMBA_REG, SRAM1_EN, 1);
	SetBits(CLK_AMBA_REG, MCRAM2_EN, 1);
	SetBits(CLK_AMBA_REG, SRAM2_EN, 1);
}

void InitDSPCODEC(void)
{
	SetWord(CODEC_VREF_REG, 0x0014); // vrefs on
	SetWord(CODEC_ADDA_REG, 0x00E8); // enable AD/DA
	SetWord(CODEC_LSR_REG, 0x0052); // enable LSRN LSRP differential, 0 dB
	SetWord(CODEC_MIC_REG, 0x1000); // enable MIC
	SetWord(CLK_DSP_REG, 0x0009); // Gen2DSP clock divider enabled, DSP_EN starts Gen2DSP
	SetBits(drv_dsp_ctrl_reg, DSP_CLK_EN, 0); // Gen2DSP clock disabled after WTF execution. Wakes up on SYNC event

	if(MAX_NO_FM_DSP_CORES >1) {
		SetWord(CLK_DSP_REG, 0x0099); // Gen2DSP clock divider enabled, DSP_EN starts Gen2DSP
		SetBits(drv_dsp2_ctrl_reg, DSP_CLK_EN, 0); // Gen2DSP clock disabled after WTF execution. Wakes up on SYNC event
	}

#ifdef WIDEBAND
	SetBits(drv_dsp_main_sync1_reg, AD_SYNC,1); // 16KHZ CODEC MIC Samples
	SetBits(drv_dsp_main_sync1_reg, DA_LSR_SYNC,1); // 16KHZ CODEC LSR Samples
	SetBits(drv_dsp_main_sync1_reg, DA_CLASSD_SYNC,1); // 16KHZ CLASSD Samples
#else
	SetBits(drv_dsp_main_sync1_reg, AD_SYNC,0); // 8KHZ CODEC MIC Samples
	SetBits(drv_dsp_main_sync1_reg, DA_LSR_SYNC,0); // 8KHZ CODEC LSR Samples
	SetBits(drv_dsp_main_sync1_reg, DA_CLASSD_SYNC,0); // 8KHZ CLASSD Samples
#endif
}

#endif

/********************************************************************************************
 *                                                                                          *
 *                             SC14480 Specific functions                                   *
 *                                                                                          * 
 ********************************************************************************************/
#ifdef SC14480

/*******************************************************************************************
 *  Function         : void InitClocks(BYTE pll_freq)                                      *
 *  Purpose          : Select PLL fequency or select XTAL frequency.                       *
 *                     Set Main clock, Codec AD/DA clocks, ClassD clock and PCM clock      *
 *                     The Function is valid for execution from FLASG                      *
 *                     This function can be used to increase/decrease DSP/CR16 performance *
 *                     while maintaing the DIP synchronisation (10.368 DIP clock)          * 
 *  Precondition     : Function can be called to switch from any given clock setting to    *
 *                     another setting. This is done by providing the desired PLL mode as  *
 *                     argument. Audio must be muted and DSP must be stopped because the   *
 *                     codec clock generation is derived from the PLL/2 path in order to   *
 *                     support wide band audio                                             *
 *  Postcondition    : HCLK and PCLK are set to the highest possible frequency for FLASH   *
 *                     and ROM. Although execution from RAM can be faster, it is kept      *
 *                     the same as ROM and FLASH                                           *
 *                     AMBA_CLK_REG[MEM_STROBE] is set to optimal value for power saving   *
 *                     MEM_CONFIG_REG[T_RC] is set to optimal value for FLASH access       *
 *                     (this is don't care for ROM and RAM access)                         *
 *  Argument defines : PLL_40  = 41,472 MHz PLL clock                                      *
 *                     PLL_80  = 82,944 MHz PLL clock                                      *
 *                     PLL_160 = 165.88 MHz PLL clock                                      *
 *  Note 1           : To use wideband audio pre define WIDEBAND in the project settings   *
 *******************************************************************************************/
void InitClockRegisters(BYTE pll_freq) {
	WORD i;
	SetBits(CLK_PLL_CTRL_REG_ADDR, PLL_CLK_SEL,0); // PLL off
	for (i = 0; i < 10; i++)
		;
	SetWord(CLK_PLL_CTRL_REG_ADDR, 0x0800); // Switch to XTAL mode before changing PLL mode
	SetWord(CLK_CODEC_DIV_REG_ADDR,0x9);
	SetBits(MEM_CONFIG_REG_ADDR,T_RC,0);
	SetBits(CLK_AMBA_REG_ADDR, MEM_STROBE,0); // Memory acces strobe for power reduction// 0 wait cycles for flash access
	SetBits(CLK_AMBA_REG_ADDR,HCLK_DIV,1); // CR16C clock @ 10Mhz
	SetWord(CLK_PER_DIV_REG_ADDR, 9);

	switch (pll_freq) {
	case PLL_40:
		SetBits(MEM_CONFIG_REG_ADDR,T_RC,0); // 0 wait cycles for flash access
		SetBits(CLK_AMBA_REG_ADDR,HCLK_DIV,1); // CR16C clock @ 20Mhz
		// turn on pll
		SetWord(CLK_PLL_DIV_REG_ADDR ,0x005); // PLL @ 41,472 Mhz
		SetWord(CLK_PER_DIV_REG_ADDR, 9);
		SetWord(CLK_CODEC_DIV_REG_ADDR,0x92);
		SetWord(CLK_PLL_CTRL_REG_ADDR, 0x200 | DYN_SW | VCO_ON | CP_ON); // PLL_DIP_DIV = 4 Dip lck @ 10.368 MHz
		Pll_On(); // Switch to PLL clock
		SetBits(CLK_AMBA_REG_ADDR, MEM_STROBE,1); // Memory acces strobe for power reduction
		break;
	case PLL_80:
		SetBits(MEM_CONFIG_REG_ADDR,T_RC,1); // Insert wait cycle for flash access
		SetBits(CLK_AMBA_REG_ADDR,HCLK_DIV,1); // CR16C clock @ 40Mhz
		// turn on pll
		SetWord(CLK_PLL_DIV_REG_ADDR ,0x001D); // PLL @ 80 Mhz
		SetWord(CLK_PER_DIV_REG_ADDR, 9);
		SetWord(CLK_CODEC_DIV_REG_ADDR,0xA4);
		SetWord(CLK_PLL_CTRL_REG_ADDR, 0x400 | DYN_SW | HF_SEL | VCO_ON | CP_ON); // PLL_DIP_DIV = 8, Dip clock @ 10.368 MHz
		Pll_On(); // Switch to PLL clock
		SetBits(CLK_AMBA_REG_ADDR, MEM_STROBE,2); // Memory acces strobe for power reduction
		break;
	case PLL_160:
		SetBits(MEM_CONFIG_REG_ADDR,T_RC,1); // Insert wait cycle for flash access
		SetBits(CLK_AMBA_REG_ADDR,HCLK_DIV,2); // CR16C clock @ 40Mhz
		// turn on pll
		SetWord(CLK_PLL_DIV_REG_ADDR ,0x001C); // PLL @ 165.88 Mhz
		SetWord(CLK_PER_DIV_REG_ADDR, 9);
		SetWord(CLK_CODEC_DIV_REG_ADDR,0xC8);
		SetWord(CLK_PLL_CTRL_REG_ADDR, DYN_SW | HF_SEL | VCO_ON | CP_ON); // PLL_DIP_DIV = 0, Dip clock @ 10.368 MHz
		Pll_On(); // Switch to PLL clock
		SetBits(CLK_AMBA_REG_ADDR, MEM_STROBE,4); // Memory acces strobe for power reduction
		break;
	case PLL_OFF:
		// XTAL mode is selected at function entry
		SetBits(CLK_AMBA_REG_ADDR, MEM_STROBE,1); // Memory acces strobe for power reduction
		break;
	default:
		break;
	}

#ifdef WIDEBAND
	SetWord(CLK_CODEC_REG_ADDR, 0x7DA9); // Main clock @ 1.152 MHz, Codec AD/DA clocks, ClassD clock @ 2.304 MHz, PCM clock @ 1.152 MHz
#else
	SetWord(CLK_CODEC_REG_ADDR, 0x7D55); // Main clock @ 1.152 MHz, Codec AD/DA clocks, ClassD clock @ 1.152 MHz, PCM clock @ 1.152 MHz
#endif
	SetBits(CLK_AMBA_REG_ADDR, MCRAM1_EN, 1);
	SetBits(CLK_AMBA_REG_ADDR, SRAM1_EN, 1);
}

void InitDSPCODEC(void) {
	SetWord(CODEC_VREF_REG_ADDR, 0x0014); // vrefs on
	SetWord(CODEC_ADDA_REG_ADDR, 0x00E8); // enable AD/DA
	SetWord(CODEC_LSR_REG_ADDR, 0x0052); // enable LSRN LSRP differential, 0 dB
	SetWord(CODEC_MIC_REG_ADDR, 0x1800); // enable MIC
	SetWord(CLK_DSP_REG_ADDR, 9); // Gen2DSP clock divider enabled, DSP_EN starts Gen2DSP
	SetBits(drv_dsp_ctrl_reg, DSP_CLK_EN, 0);// Gen2DSP clock disabled after WTF execution. Wakes up on SYNC event

#ifdef WIDEBAND
	SetBits(drv_dsp_main_sync1_reg, AD_SYNC,1); // 16KHZ CODEC MIC Samples
	SetBits(drv_dsp_main_sync1_reg, DA_LSR_SYNC,1); // 16KHZ CODEC LSR Samples
	SetBits(drv_dsp_main_sync1_reg, DA_CLASSD_SYNC,1); // 16KHZ CLASSD Samples
#else
	SetBits(drv_dsp_main_sync1_reg, AD_SYNC,0); // 8KHZ CODEC MIC Samples
	SetBits(drv_dsp_main_sync1_reg, DA_LSR_SYNC,0); // 8KHZ CODEC LSR Samples
	SetBits(drv_dsp_main_sync1_reg, DA_CLASSD_SYNC,0); // 8KHZ CLASSD Samples
#endif
}

#endif 
