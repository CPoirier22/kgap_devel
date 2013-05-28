/*******************************************************************************
* Project   : DECT                                                             *
* Module    : -                                                                *
* Reference : -                                                                *
* File      : BsHw_Def.h                                                       *
* Type      : standard includefile                                             *
* Function  : Base hardware definitions.                                       *
* Systems   : All systems                                                      *
*------------------------------------------------------------------------------*
* Owner:                                                                       *
* $Header:   K:/PH/140999xx/Xx/Variant/Archive/H/bshw_def.h_v   1.3   Jan 08 2004 15:40:16   on  $ *
*******************************************************************************/

/*
?????????????????????????????????????????????????????????????????????????????
?                                 PVCS info                                 ?
?????????????????????????????????????????????????????????????????????????????

$Author:   on  $
$Date:   Jan 08 2004 15:40:16  $
$Revision:   1.3  $
$Modtime:   Jan 08 2004 09:38:20  $

*/


#ifndef __BSHW_DEF_H
#define __BSHW_DEF_H


#define SC144XX_CLK_DIV   0x0001

/*---------------------------------------------------------------------------
 | PORT DEFINE
 *--------------------------------------------------------------------------*/


/*==========================================================================*/



#define OSTIMER_INT_CLR_PENDING  RESET_INT_PENDING_REG = TIM0_INT_PEND
#define OSTIMER_START            TIMER_CTRL_REG|=TIM0_CTRL
#define OSTIMER_INT_ENABLE       SET_TIM0_INT_PRIO(1); \
                                 RESET_INT_PENDING_REG = TIM0_INT_PEND
#define FASTTIMER_INT_CLR_PENDING  RESET_INT_PENDING_REG = TIM1_INT_PEND
#define FASTTIMER_START          TIMER_CTRL_REG|=TIM1_CTRL
#define FASTTIMER_INT_ENABLE     SET_TIM1_INT_PRIO(0); \
                                 RESET_INT_PENDING_REG = TIM1_INT_PEND
#define KEYB_INT_CLR_PENDING     RESET_INT_PENDING_REG = KEYB_INT_PEND
#define CLK100_INT_CLR_PENDING   RESET_INT_PENDING_REG = CLK100_INT_PEND
#define CLK100_INT_ENABLE        SET_CLK100_INT_PRIO(5); \
                                 RESET_INT_PENDING_REG = CLK100_INT_PEND
#define CLK8K_INT_CLR_PENDING    RESET_INT_PENDING_REG = CLK8K_INT_PEND
#define ADPCM_INT_ENABLE         SET_DSP_INT_PRIO(4); \
                                 DSP_INT_MASK_REG = 0x87ff; \
                                 RESET_INT_PENDING_REG = CLEAR_PENDING_DSP_INTERRUPT
#endif
