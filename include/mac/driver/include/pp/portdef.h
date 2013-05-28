/*
********************************************************************
*
* Module:   portdef.h
*
* Config-item:  ?
*
* Contents: Header file for HW ports
*
* Author:  Kirk telecom
*
* Copyright Kirk Telecom A/S. All rights reserved.
*
* $Header:   K:/PH/SRCLIB/PP5/BASIS/ARCHIVE/H/portdef.h_v   1.1   21 Sep 2005 11:07:20   mne  $
*
* $Log:   K:/PH/SRCLIB/PP5/BASIS/ARCHIVE/H/portdef.h_v  $
 *
 *    Rev 1.1   21 Sep 2005 11:07:20   mne
 * SERIAL MAILBUFFER SIZE now 60
*
*
********************************************************************
*/

#ifndef __PORTDEF_H
#define __PORTDEF_H
/****************************************************************************
*                              Include files                                *
****************************************************************************/

/****************************************************************************
*                             Macro definitions                             *
*****************************************************************************/


#define RING_DETECT_INIT()  { TONE_CTRL1_REG = GATESRC_RINGING_VBAT3 | \
                              CLKSRC_144KHZ | TIMER_RELOAD_DIV1 | MCT_INT ; \
                              SET_CT_INT_PRIO(1); }



#define DSR (0)  /* (MiscReadLatch & DSRInActive)*/
#define DCD (0)  /* (MiscReadLatch & DCDInActive)*/





#define I2C_SCL0_port       P2_DATA_REG
#define I2C_SCL0_dir        P2_DIR_REG
#define I2C_SCL0_bit        0
#define I2C_SCL0_high       SET_PORT2(I2C_SCL0_bit)
#define I2C_SCL0_low        CLR_PORT2(I2C_SCL0_bit)

#define I2C_SDA0_port       P2_DATA_REG
#define I2C_SDA0_dir        P2_DIR_REG
#define I2C_SDA0_bit        1
#define I2C_SDA0_high       SET_PORT2(I2C_SDA0_bit)
#define I2C_SDA0_low        CLR_PORT2(I2C_SDA0_bit)
#define I2C_SDA0_port_get   GET_PORT2(I2C_SDA0_bit)




#define POWER_LED_port               P1_IN_OUT_DATA_REG
#define POWER_LED_dir                P1_DIR_REG
#define POWER_LED_bit                5


#define POWER_LED_port_active        CLR_PORT1( POWER_LED_bit )
#define POWER_LED_port_inactive      SET_PORT1( POWER_LED_bit )
#define POWER_LED_port_get           GET_PORT1( POWER_LED_bit )
#define INIT_POWER_LED_PORT          OUTPUT_PORT( POWER_LED_dir, POWER_LED_bit ); POWER_LED_port_inactive



#define HOOK_port                   P1_IN_OUT_DATA_REG
#define HOOK_dir                    P1_DIR_REG
#define HOOK_bit                    1
#define HOOK_port_active            SET_PORT1( HOOK_bit )
#define HOOK_port_inactive          CLR_PORT1( HOOK_bit )
#define INIT_HOOK_PORT              OUTPUT_PORT( HOOK_dir, HOOK_bit ); HOOK_port_inactive



#define HOOK_LED_port               P1_IN_OUT_DATA_REG
#define HOOK_LED_dir                P1_DIR_REG
#define HOOK_LED_bit                4
#define HOOK_LED_port_active        CLR_PORT1( HOOK_LED_bit )
#define HOOK_LED_port_inactive      SET_PORT1( HOOK_LED_bit )
#define HOOK_LED_port_get           GET_PORT1( HOOK_LED_bit )
#define INIT_HOOK_LED_PORT          OUTPUT_PORT( HOOK_LED_dir, HOOK_LED_bit ); HOOK_LED_port_inactive


#define CHARGE_port                   P1_IN_OUT_DATA_REG
#define CHARGE_dir                    P1_DIR_REG
#define CHARGE_bit                    1
#define CHARGE_port_active            SET_PORT1( CHARGE_bit )
#define CHARGE_port_inactive          CLR_PORT1( CHARGE_bit )
#define INIT_VHARGE_PORT              OUTPUT_PORT( CHARGE_dir, CHARGE_bit ); CHARGE_port_inactive



#define CHARGE_LED_port               P1_IN_OUT_DATA_REG
#define CHARGE_LED_dir                P1_DIR_REG
#define CHARGE_LED_bit                3
#define CHARGE_LED_port_active        CLR_PORT1( CHARGE_LED_bit )
#define CHARGE_LED_port_inactive      SET_PORT1( CHARGE_LED_bit )
#define CHARGE_LED_port_get           GET_PORT1( CHARGE_LED_bit )
#define INIT_CHARGE_LED_PORT          OUTPUT_PORT( CHARGE_LED_dir, CHARGE_LED_bit ); CHARGE_LED_port_inactive



#define LOWIMPEDANS_port            P1_IN_OUT_DATA_reg
#define LOWIMPEDANS_dir             P1_DIR_REG
#define LOWIMPEDANS_bit             2
#define LOWIMPEDANS_port_active     SET_PORT1( LOWIMPEDANS_bit )
#define LOWIMPEDANS_port_inactive   CLR_PORT1( LOWIMPEDANS_bit )
#define INIT_LOWIMPEDANS_PORT       OUTPUT_PORT( LOWIMPEDANS_dir, LOWIMPEDANS_bit ); LOWIMPEDANS_port_inactive



#define PULSE_USED_port             P2_IN_OUT_DATA_reg
#define PULSE_USED_dir              P2_DIR_REG
#define PULSE_USED_bit              3
#define PULSE_USED_port_get         GET_PORT0( PULSE_USED_bit )
#define PULSE_CIRCUIT_PRESSENT      !PULSE_USED_port_get  /* External pull down if pressent*/
#define INIT_PULSE_USED_PORT        INPUT_PORT(PULSE_USED_dir,PULSE_USED_bit);


#define LINE_SENSE_adc              ADC0
#define LINE_SENSE_dir              P2_DIR_REG
#define LINE_SENSE_bit              2
#define INIT_LINE_SENSE_PORT        INPUT_PORT(LINE_SENSE_dir,PULSE_USED_bit);








#define CAS_TEST_port               P2_IN_OUT_DATA_REG
#define CAS_TEST_dir                P2_DIR_REG
#define CAS_TEST_bit                0
#define CAS_TEST_port_active        SET_PORT1( CAS_TEST_bit )
#define CAS_TEST_port_inactive      CLR_PORT1( CAS_TEST_bit )
#define INIT_CAS_TEST_PORT          OUTPUT_PORT( CAS_TEST_dir, CAS_TEST_bit ); CAS_TEST_port_inactive







#define CRADLE_LED_port               P1_IN_OUT_DATA_REG
#define CRADLE_LED_dir                P1_DIR_REG
#define CRADLE_LED_bit                3
#define CRADLE_LED_port_active        SET_PORT1( CRADLE_LED_bit )
#define CRADLE_LED_port_inactive      CLR_PORT1( CRADLE_LED_bit )
#define INIT_CRADDLE_LED_PORT         OUTPUT_PORT( CRADLE_LED_dir, CRADLE_LED_bit ); CRADLE_LED_port_inactive

#define SERIAL_IN_adc                 ADC2





#define PAGE_BUTTON_port               P1_IN_OUT_DATA_REG
#define PAGE_BUTTON_dir                P1_DIR_REG
#define PAGE_BUTTON_bit                0
#define PAGE_BUTTON_port_get           GET_PORT1( PAGE_BUTTON_bit )
#define PAGE_BUTTON_pressed            !PAGE_BUTTON_port_get  /* Low when pressed*/
#define INIT_PAGE_BUTTON               INPUT_PORT(PAGE_BUTTON_dir,PAGE_BUTTON_bit);







#define QUADRATUR_TUNE        0   /* 1 = enabled*/

#define RSSI_BIT            0x01

#define SAMP_BIT            0x02
#define SAMP_REVERSED       0x01   /* active low*/

#define PLL_ON_BIT          0x04
#define PLLSW_BIT_REVERSED  0x01 /* active low*/

#define RF_ON_BIT           0x08
#define RFSW_REVERSED       0x00   /* active high*/

#define PA_ON_BIT           0x10
#define PASW_REVERSED       0x00   /* active high*/

#define TRSW_BIT            0x20
#define TRSW_REVERSED       0x00   /* active high*/

#define ANT_REVERSED        0x01   /* active low*/
#define ANT2_BIT            0x40
#define ANT1_BIT            0x80
#endif




