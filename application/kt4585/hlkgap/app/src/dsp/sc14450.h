#ifndef _IO14450_INCLUDED
#define _IO14450_INCLUDED
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
 *
 *-----------------------------------------------------------------------------
 *
 * File:      sc14450.h
 * Purpose:   
 * Created:   20-10-2006			 
 * By:        GW					    
 * Country:   The Netherlands
 *
 *
 */


#ifdef __IAR_SYSTEMS_ICC__
	#define MODEL               1
	#define __far
#else
	#define MODEL               4
#endif

/*========================== USER DEFINED CONSTANTS =========================*/

#define MAX_DOG_TIME        0x00FF

/*==============================================================
 * SC14450 Programmable Peripheral Assigment PID values
 * Datasheet V0.43 October 11
 * 17-nov-2006 PORT_PULL_UP, PULL_DOWN corrected
 ===============================================================*/

#define SetPort(PORT, IO_CONFIG, PID) SetWord(PORT, IO_CONFIG <<8 | PID); 

/*----------------------------*/
/*  IO configurations         */
/*----------------------------*/
#define PORT_INPUT          0
#define PORT_PULL_UP        1
#define PORT_PULL_DOWN      2
#define PORT_OUTPUT         3

/*----------------------------*/
/*  PIDs                      */
/*----------------------------*/
#define PID_port            0	
#define PID_CLK100          1	
#define PID_PID_TDOD        2
#define PID_BXTAL           3	
#define PID_PWM0            4	
#define PID_PWM1            5	
#define PID_ECZ1            6	
#define PID_ECZ2            7	
#define PID_PLL2_CLK        8	
#define PID_WTF_IN1         9	
#define PID_WTF_IN2         10	
#define PID_UTX             11	
#define PID_URX             12	
#define PID_SDA1            13	
#define PID_SCL1            14	
#define PID_SDA2            15	
#define PID_SCL2            16	
#define PID_SPI1_DOUT       17	
#define PID_SPI1_DIN        18	
#define PID_SPI1_CLK        19	
#define PID_SPI1_EN         20	
#define PID_SPI2_DOUT       21	
#define PID_SPI2_DIN        22	
#define PID_SPI2_CLK        23	
#define PID_PCM_DO          24	
#define PID_PCM_CLK         25	
#define PID_PCM_FSC         26	
#define PID_PCM_DI          27	
#define PID_AD13            28	
#define PID_AD14            28	
#define PID_AD15            28	
#define PID_AD16            28	
#define PID_AD17            28	
#define PID_AD18            28	
#define PID_AD19            28	
#define PID_AD20            28	
#define PID_AD21            28	
#define PID_AD22            28	
#define PID_AD23            28	
#define PID_SDCKE           29
#define PID_SDCLK           30	
#define PID_SF_ADV          31	
#define PID_BE0n            32	
#define PID_BE1n            33	
#define PID_READY           34	
#define PID_INT0n           35	
#define PID_INT1n           36	
#define PID_INT2n           37	
#define PID_INT3n           38	
#define PID_INT4n           39	
#define PID_INT5n           40	
#define PID_INT6n           41	
#define PID_INT7n           42	
#define PID_INT8n           43	
#define PID_ACS0            44	
#define PID_ACS1            45	
#define PID_ACS2            46	
#define PID_ACS3            47	
#define PID_ACS4            48	
#define PID_PD1             49	
#define PID_PD2             50	
#define PID_PD3             51	
#define PID_PD4             52	
#define PID_PD5             53	
#define PID_PAOUTp          63	
#define PID_PAOUTn          63	
#define PID_ADC0            63	
#define PID_ADC1            63	
#define PID_ADC2            63	

/*======================= Start of automatic generated code =================*/

/*
 * This file is generated from Meta file "Output\SC14450.meta"
 * With version number: 
 * On Sep 25 2006 15:30:17
 */




#define NMI_INT             (MODEL* 1)  /* Non maskable interrupt from DIP <VNMI> and Watchdog timer */
#define SVC_TRAP            (MODEL* 5)  /* Supervisor Call Trap */
#define DVZ_TRAP            (MODEL* 6)  /* Divide by zero Trap */
#define FLG_TRAP            (MODEL* 7)  /* Flag Trap */
#define BPT_TRAP            (MODEL* 8)  /* Breakpoint Trap */
#define TRC_TRAP            (MODEL* 9)  /* Trace Trap */
#define UND_TRAP            (MODEL*10)  /* Undefined Instruction Trap */
#define IAD_TRAP            (MODEL*12)  /* Illegal address Trap */
#define DBG_TRAP            (MODEL*14)  /* Debug Trap */
#define ISE_INT             (MODEL*15)  /* In System Emulator Interrupt caused by ISE pin or SDI */
#define ACCESS12_INT        (MODEL*16)  /* Access bus 1 and 2 interrupt */
#define KEYB_INT            (MODEL*17)  /* Keyboard Interrupt or vectored level/edge interrupt */
#define RESERVED_INT        (MODEL*18)  /* Reserved */
#define CT_CLASSD_INT       (MODEL*19)  /* Capture timer 1,2 interrupt or CLASSD clipping interrupt */
#define UART_RI_INT         (MODEL*20)  /* UART RI interrupt */
#define UART_TI_INT         (MODEL*21)  /* UART TI interrupt */
#define SPI1_AD_INT         (MODEL*22)  /* SPI 1 or ADC Interrupt */
#define TIM0_INT            (MODEL*23)  /* Timer 0 interrupt */
#define TIM1_INT            (MODEL*24)  /* Timer 1 interrupt */
#define CLK100_INT          (MODEL*25)  /* CLK100 interrupt  */
#define DIP_INT             (MODEL*26)  /* DIP Interrupt */
#define USB_INT             (MODEL*27)  /* USB Interrupt */
#define SPI2_INT            (MODEL*28)  /* SPI 2 interrupt */
#define DSP1_INT            (MODEL*29)  /* Gen2DSP 1 Interrupt */
#define DSP2_INT            (MODEL*30)  /* Gen2DSP 2 Interrupt */




#define RAM_START                               (0x000000)  /*  */
#define RAM_END                                 (0x005FFF)  /*  */
#define RAM_ADM_START                           (0x008000)  /*  */
#define RAM_ADM_END                             (0x009FFF)  /*  */
#define SHARED_RAM1_START                       (0x010000)  /*  */
#define SHARED_RAM1_END                         (0x012FFF)  /*  */
#define SHARED_RAM2_START                       (0x018000)  /*  */
#define SHARED_RAM2_END                         (0x01BFFF)  /*  */
#define PROGRAM_START                           (0x0F0000)  /*  */
#define PROGRAM_END                             (0xFEEFFF)  /*  */
#define BOOT_ROM_START                          (0xFEF000)  /*  */
#define BOOT_ROM_END                            (0xFEF7FF)  /*  */
#define EBI_SDCONR_REG                          (0xFF0000)  /* SDRAM Configuration register */
#define EBI_SDTMG0R_REG                         (0xFF0004)  /* SDRAM Timing register 0 */
#define EBI_SDTMG1R_REG                         (0xFF0008)  /* SDRAM Timing register 1 */
#define EBI_SDCTLR_REG                          (0xFF000C)  /* SDRAM Control register */
#define EBI_SDREFR_REG                          (0xFF0010)  /* SDRAM Refresh register */
#define EBI_ACS0_LOW_REG                        (0xFF0014)  /* Chip select 0 base address register */
#define EBI_ACS1_LOW_REG                        (0xFF0018)  /* Chip select 1 base address register */
#define EBI_ACS2_LOW_REG                        (0xFF001C)  /* Chip select 2 base address register */
#define EBI_ACS3_LOW_REG                        (0xFF0020)  /* Chip select 3 base address register */
#define EBI_ACS4_LOW_REG                        (0xFF0024)  /* Chip select 4 base address register */
#define EBI_ACS0_CTRL_REG                       (0xFF0054)  /* Chip select 0 control register */
#define EBI_ACS1_CTRL_REG                       (0xFF0058)  /* Chip select 1 control register */
#define EBI_ACS2_CTRL_REG                       (0xFF005C)  /* Chip select 2 control register */
#define EBI_ACS3_CTRL_REG                       (0xFF0060)  /* Chip select 3 control register */
#define EBI_ACS4_CTRL_REG                       (0xFF0064)  /* Chip select 4 control register */
#define EBI_SMTMGR_SET0_REG                     (0xFF0094)  /* Static memory Timing register Set 0 */
#define EBI_SMTMGR_SET1_REG                     (0xFF0098)  /* Static memory Timing register Set 1 */
#define EBI_SMTMGR_SET2_REG                     (0xFF009C)  /* Static memory Timing register Set 2 */
#define EBI_FLASH_TRPDR_REG                     (0xFF00A0)  /* FLASH Timing Register */
#define EBI_SMCTLR_REG                          (0xFF00A4)  /* Static memory Control register */
#define EBI_SDEXN_MODE_REG                      (0xFF00AC)  /* Mobile SDRAM Extende mode register */
#define CLK_AMBA_REG                            (0xFF4000)  /* HCLK, PCLK, divider and clock gates */
#define CLK_CODEC_DIV_REG                       (0xFF4002)  /* Codec divider register */
#define CLK_CODEC_REG                           (0xFF4004)  /* Codec clock selection register */
#define CLK_DSP_REG                             (0xFF4006)  /* DSP clock selection register */
#define CLK_FREQ_TRIM_REG                       (0xFF400A)  /* Xtal frequency trimming register. */
#define CLK_PER_DIV_REG                         (0xFF400C)  /* Peripheral divider register for 2,1, 1/2, 1/4 MHz clocks */
#define CLK_PER10_DIV_REG                       (0xFF400E)  /* Peripheral divider register for 20, 10 MHz clocks */
#define CLK_PLL1_CTRL_REG                       (0xFF4010)  /* PLL1 control register */
#define CLK_PLL1_DIV_REG                        (0xFF4012)  /* PLL1 divider register */
#define CLK_PLL2_CTRL_REG                       (0xFF4014)  /* PLL2 control register */
#define CLK_PLL2_DIV_REG                        (0xFF4016)  /* PLL2 divider register */
#define CLK_XTAL_CTRL_REG                       (0xFF4018)  /* Crystal control register */
#define CLK_AUX_REG                             (0xFF401A)  /* Auxiliary clock control register */
#define DMA0_A_STARTL_REG                       (0xFF4400)  /* Start address Low A of DMA channel 0 */
#define DMA0_A_STARTH_REG                       (0xFF4402)  /* Start address Low A of DMA channel 0 */
#define DMA0_B_STARTL_REG                       (0xFF4404)  /* Start address Low B of DMA channel 0 */
#define DMA0_B_STARTH_REG                       (0xFF4406)  /* Start address High B of DMA channel 0 */
#define DMA0_INT_REG                            (0xFF4408)  /* DMA receive interrupt register channel 0 */
#define DMA0_LEN_REG                            (0xFF440A)  /* DMA receive length register channel 0 */
#define DMA0_CTRL_REG                           (0xFF440C)  /* Control register for the DMA channel 0 */
#define DMA0_IDX_REG                            (0xFF440E)  /* Internal Index register for the DMA channel 0 */
#define DMA1_A_STARTL_REG                       (0xFF4410)  /* Start address Low A of DMA channel 1 */
#define DMA1_A_STARTH_REG                       (0xFF4412)  /* Start address High A of DMA channel 1 */
#define DMA1_B_STARTL_REG                       (0xFF4414)  /* Start address Low B of DMA channel 1 */
#define DMA1_B_STARTH_REG                       (0xFF4416)  /* Start address High B of DMA channel 1 */
#define DMA1_INT_REG                            (0xFF4418)  /* DMA receive interrupt register channel 1 */
#define DMA1_LEN_REG                            (0xFF441A)  /* DMA receive length register channel 1 */
#define DMA1_CTRL_REG                           (0xFF441C)  /* Control register for the DMA channel 1 */
#define DMA1_IDX_REG                            (0xFF441E)  /* Internal Index register for the DMA channel 1 */
#define DMA2_A_STARTL_REG                       (0xFF4420)  /* Start address Low A of DMA channel 2 */
#define DMA2_A_STARTH_REG                       (0xFF4422)  /* Start address High A of DMA channel 2 */
#define DMA2_B_STARTL_REG                       (0xFF4424)  /* Start address Low B of DMA channel 2 */
#define DMA2_B_STARTH_REG                       (0xFF4426)  /* Start address High B of DMA channel 2 */
#define DMA2_INT_REG                            (0xFF4428)  /* DMA receive interrupt register channel 2 */
#define DMA2_LEN_REG                            (0xFF442A)  /* DMA receive length register channel 2 */
#define DMA2_CTRL_REG                           (0xFF442C)  /* Control register for the DMA channel 2 */
#define DMA2_IDX_REG                            (0xFF442E)  /* Internal Index register for the DMA channel 2 */
#define DMA3_A_STARTL_REG                       (0xFF4430)  /* Start address Low A of DMA channel 3 */
#define DMA3_A_STARTH_REG                       (0xFF4432)  /* Start address High A of DMA channel 3 */
#define DMA3_B_STARTL_REG                       (0xFF4434)  /* Start address Low B of DMA channel 3 */
#define DMA3_B_STARTH_REG                       (0xFF4436)  /* Start address High B of DMA channel 3 */
#define DMA3_INT_REG                            (0xFF4438)  /* DMA receive interrupt register channel 3 */
#define DMA3_LEN_REG                            (0xFF443A)  /* DMA receive length register channel 3 */
#define DMA3_CTRL_REG                           (0xFF443C)  /* Control register for the DMA channel 3 */
#define DMA3_IDX_REG                            (0xFF443E)  /* Internal Index register for the DMA channel 3 */
#define TEST_ENV_REG                            (0xFF4800)  /* CR16C boot mode control register */
#define TEST_CTRL_REG                           (0xFF4802)  /* Test control register */
#define TEST_CTRL2_REG                          (0xFF4804)  /* Test control register 2 */
#define BANDGAP_REG                             (0xFF4810)  /* Bandgap register */
#define BAT_CTRL_REG                            (0xFF4812)  /* Power management control register */
#define BAT_CTRL2_REG                           (0xFF4814)  /* Power charge control register */
#define BAT_STATUS_REG                          (0xFF4816)  /* Power status register */
#define BAT_SOC_HIGH_REG                        (0xFF4818)  /* Power state of charge counter (high)  */
#define BAT_SOC_LOW_REG                         (0xFF481A)  /* Power state of charge counter (low) */
#define CP_CTRL_REG                             (0xFF481C)  /* Charge pump for LEDs control register. */
#define P0_DATA_REG                             (0xFF4830)  /* P0 Data input /out register */
#define P0_SET_DATA_REG                         (0xFF4832)  /* P0 Set port pins register */
#define P0_RESET_DATA_REG                       (0xFF4834)  /* P0 Reset port pins register */
#define P0_00_MODE_REG                          (0xFF4840)  /* P0y Mode Register */
#define P0_01_MODE_REG                          (0xFF4842)  /* P0y Mode Register */
#define P0_02_MODE_REG                          (0xFF4844)  /* P0y Mode Register */
#define P0_03_MODE_REG                          (0xFF4846)  /* P0y Mode Register */
#define P0_04_MODE_REG                          (0xFF4848)  /* P0y Mode Register */
#define P0_05_MODE_REG                          (0xFF484A)  /* P0y Mode Register */
#define P0_06_MODE_REG                          (0xFF484C)  /* P0y Mode Register */
#define P0_07_MODE_REG                          (0xFF484E)  /* P0y Mode Register */
#define P0_08_MODE_REG                          (0xFF4850)  /* P0y Mode Register */
#define P0_09_MODE_REG                          (0xFF4852)  /* P0y Mode Register */
#define P0_10_MODE_REG                          (0xFF4854)  /* P0y Mode Register */
#define P0_11_MODE_REG                          (0xFF4856)  /* P0y Mode Register */
#define P0_12_MODE_REG                          (0xFF4858)  /* P0y Mode Register */
#define P0_13_MODE_REG                          (0xFF485A)  /* P0y Mode Register */
#define P0_14_MODE_REG                          (0xFF485C)  /* P0y Mode Register */
#define P0_15_MODE_REG                          (0xFF485E)  /* P0y Mode Register */
#define P1_DATA_REG                             (0xFF4860)  /* P1 Data input /out register */
#define P1_SET_DATA_REG                         (0xFF4862)  /* P1 Set port pins register */
#define P1_RESET_DATA_REG                       (0xFF4864)  /* P1 Reset port pins register */
#define P1_00_MODE_REG                          (0xFF4870)  /* P1y Mode Register */
#define P1_01_MODE_REG                          (0xFF4872)  /* P1y Mode Register */
#define P1_02_MODE_REG                          (0xFF4874)  /* P1y Mode Register */
#define P1_03_MODE_REG                          (0xFF4876)  /* P1y Mode Register */
#define P1_04_MODE_REG                          (0xFF4878)  /* P1y Mode Register */
#define P1_05_MODE_REG                          (0xFF487A)  /* P1y Mode Register */
#define P1_06_MODE_REG                          (0xFF487C)  /* P1y Mode Register */
#define P1_07_MODE_REG                          (0xFF487E)  /* P1y Mode Register */
#define P1_08_MODE_REG                          (0xFF4880)  /* P1y Mode Register */
#define P1_09_MODE_REG                          (0xFF4882)  /* P1y Mode Register */
#define P1_10_MODE_REG                          (0xFF4884)  /* P1y Mode Register */
#define P1_11_MODE_REG                          (0xFF4886)  /* P1y Mode Register */
#define P1_12_MODE_REG                          (0xFF4888)  /* P1y Mode Register */
#define P1_13_MODE_REG                          (0xFF488A)  /* P1y Mode Register */
#define P1_14_MODE_REG                          (0xFF488C)  /* P1y Mode Register */
#define P1_15_MODE_REG                          (0xFF488E)  /* P1y Mode Register */
#define P2_DATA_REG                             (0xFF4890)  /* P2 Data input /out register */
#define P2_SET_DATA_REG                         (0xFF4892)  /* P2 Set port pins register */
#define P2_RESET_DATA_REG                       (0xFF4894)  /* P2 Reset port pins register */
#define P2_00_MODE_REG                          (0xFF48A0)  /* P2y Mode Register */
#define P2_01_MODE_REG                          (0xFF48A2)  /* P2y Mode Register */
#define P2_04_MODE_REG                          (0xFF48A8)  /* P2y Mode Register */
#define P2_05_MODE_REG                          (0xFF48AA)  /* P2y Mode Register */
#define P2_06_MODE_REG                          (0xFF48AC)  /* P2y Mode Register */
#define P2_07_MODE_REG                          (0xFF48AE)  /* P2y Mode Register */
#define P2_08_MODE_REG                          (0xFF48B0)  /* P2y Mode Register */
#define P2_09_MODE_REG                          (0xFF48B2)  /* P2y Mode Register */
#define P2_10_MODE_REG                          (0xFF48B4)  /* P2y Mode Register */
#define UART_CTRL_REG                           (0xFF4900)  /* UART control register */
#define UART_RX_TX_REG                          (0xFF4902)  /* UART data transmit/receive register */
#define UART_CLEAR_TX_INT_REG                   (0xFF4904)  /* UART clear transmit interrupt */
#define UART_CLEAR_RX_INT_REG                   (0xFF4906)  /* UART clear receive interrupt */
#define UART_ERROR_REG                          (0xFF4908)  /* UART Parity error register */
#define ACCESS1_IN_OUT_REG                      (0xFF4920)  /* ACCESS bus 1 receive/transmit register */
#define ACCESS1_CTRL_REG                        (0xFF4922)  /* ACCESS bus 1 Control register */
#define ACCESS1_CLEAR_INT_REG                   (0xFF4924)  /* Clear ACCESS bus 1 interrupt */
#define ACCESS2_IN_OUT_REG                      (0xFF4930)  /* ACCESS bus 2 receive/transmit register */
#define ACCESS2_CTRL_REG                        (0xFF4932)  /* ACCESS bus 2 Control register */
#define ACCESS2_CLEAR_INT_REG                   (0xFF4934)  /* Clear ACCESS bus 2 interrupt */
#define SPI1_CTRL_REG                           (0xFF4940)  /* SPI 1 control register */
#define SPI1_RX_TX_REG0                         (0xFF4942)  /* SPI 1 RX/TX register0 */
#define SPI1_RX_TX_REG1                         (0xFF4944)  /* SPI 1 RX/TX register1 */
#define SPI1_CLEAR_INT_REG                      (0xFF4946)  /* SPI 1 clear interrupt register */
#define SPI2_CTRL_REG                           (0xFF4950)  /* SPI 2 control register */
#define SPI2_RX_TX_REG0                         (0xFF4952)  /* SPI 2 RX/TX register0 */
#define SPI2_RX_TX_REG1                         (0xFF4954)  /* SPI 2 RX/TX register1 */
#define SPI2_CLEAR_INT_REG                      (0xFF4956)  /* SPI 2 clear interrupt register */
#define AD_CTRL_REG                             (0xFF4960)  /* ADC control register  */
#define AD_CTRL1_REG                            (0xFF4962)  /* ADC control register 1  */
#define AD_CLEAR_INT_REG                        (0xFF4964)  /* Clears ADC interrupt if set in AD_CTRL_REG  */
#define ADC0_REG                                (0xFF4966)  /* ADC0 value */
#define ADC1_REG                                (0xFF4968)  /* ADC1 value */
#define TIMER_CTRL_REG                          (0xFF4970)  /* Timers control registers */
#define TIMER0_ON_REG                           (0xFF4972)  /* Timers 0 on control registers */
#define TIMER0_RELOAD_M_REG                     (0xFF4974)  /*  */
#define TIMER0_RELOAD_N_REG                     (0xFF4976)  /*  */
#define TIMER1_RELOAD_M_REG                     (0xFF4978)  /*  */
#define TIMER1_RELOAD_N_REG                     (0xFF497A)  /*  */
#define TIMER2_DUTY_REG                         (0xFF497C)  /* Timer2 duty cycle  */
#define TIMER2_PRSC_REG                         (0xFF497E)  /* Timer2 frequency prescaler  */
#define TONE_CTRL1_REG                          (0xFF4990)  /* Capture timer control register 1 */
#define TONE_COUNTER1_REG                       (0xFF4992)  /* Capture timer Counter 1 */
#define TONE_LATCH1_REG                         (0xFF4994)  /* Capture timer Latch 1 */
#define TONE_CLEAR_INT1_REG                     (0xFF4996)  /* Clears CT1 interrupt and TONE_LATCH1_REG */
#define TONE_CTRL2_REG                          (0xFF4998)  /* Capture timer control register 2  */
#define TONE_COUNTER2_REG                       (0xFF499A)  /* Capture timer Counter 2 */
#define TONE_LATCH2_REG                         (0xFF499C)  /* Capture timer Latch 2 */
#define TONE_CLEAR_INT2_REG                     (0xFF499E)  /* Clears CT2 interrupt and TONE_LATCH2_REG */
#define KEY_GP_INT_REG                          (0xFF49B0)  /* General purpose interrupts for KEYB_INT */
#define KEY_BOARD_INT_REG                       (0xFF49B2)  /* Keyboard interrupt enable register */
#define KEY_DEBOUNCE_REG                        (0xFF49B4)  /* Keyboard debounce and auto key generation timer */
#define KEY_STATUS_REG                          (0xFF49B6)  /* Keyboard interrupt status. */
#define WATCHDOG_REG                            (0xFF4C00)  /* Watchdog preset value. */
#define SET_FREEZE_REG                          (0xFF5000)  /* Freeze watchdog, timer1 and DIP during debugging */
#define RESET_FREEZE_REG                        (0xFF5002)  /* Release watchdog, timer1 and DIP during debugging after setting in freeze mode */
#define DEBUG_REG                               (0xFF5004)  /* DEBUG_REG for boot program control and debug control */
#define CACHE_CTRL_REG                          (0xFF5006)  /* Cache control register */
#define CACHE_LEN0_REG                          (0xFF5008)  /* Cache length register 0 */
#define CACHE_START0_REG                        (0xFF500A)  /* Cache start register 0, can be used for iCache and dCache */
#define CACHE_LEN1_REG                          (0xFF500C)  /* Cache length register 1 */
#define CACHE_START1_REG                        (0xFF500E)  /* Cache start register 1, can be used for iCache and dCache */
#define CACHE_STATUS_REG                        (0xFF5010)  /* Cache status register */
#define SET_INT_PENDING_REG                     (0xFF5400)  /* Set interrupt pending register */
#define RESET_INT_PENDING_REG                   (0xFF5402)  /* Reset interrupt pending register */
#define INT0_PRIORITY_REG                       (0xFF5404)  /* Interrupt priority register 0 */
#define INT1_PRIORITY_REG                       (0xFF5406)  /* Interrupt priority register 1 */
#define INT2_PRIORITY_REG                       (0xFF5408)  /* Interrupt priority register 2 */
#define INT3_PRIORITY_REG                       (0xFF540A)  /* Interrupt priority register 2 */
#define PC_START_REG                            (0xFF540C)  /* CR16 startup address */
#define CODEC_MIC_REG                           (0xFF5800)  /* Codec microphone control register  */
#define CODEC_LSR_REG                           (0xFF5802)  /* Codec loudspeaker control register  */
#define CODEC_VREF_REG                          (0xFF5804)  /* Codec vref control register  */
#define CODEC_TONE_REG                          (0xFF5806)  /* Codec CID control register  */
#define CODEC_ADDA_REG                          (0xFF5808)  /* Codec ad/da control register  */
#define CODEC_OFFSET1_REG                       (0xFF580A)  /* Codec offset error and compensation register  */
#define CODEC_TEST_CTRL_REG                     (0xFF580C)  /* Codec test control register codec  */
#define CODEC_OFFSET2_REG                       (0xFF580E)  /* Codec offset compensation register  */
#define CLASSD_CTRL_REG                         (0xFF5C00)  /* Class D control register */
#define CLASSD_CLEAR_INT_REG                    (0xFF5C02)  /* Class D Clear interrupt register */
#define CLASSD_BUZZER_REG                       (0xFF5C04)  /* Class D buzzer register */
#define CLASSD_TEST_REG                         (0xFF5C06)  /* Class D test register */
#define CLASSD_NR_REG                           (0xFF5C08)  /* Class D noise reduction register */
#define DIP_STACK_REG                           (0xFF6000)  /* DIP Stack pointer. (read only). The DIP stack is 4 deep  */
#define DIP_PC_REG                              (0xFF6002)  /* DIP program counter */
#define DIP_STATUS_REG                          (0xFF6004)  /* DIP Status register, */
#define DIP_CTRL_REG                            (0xFF6006)  /* DIP Control register1  */
#define DIP_STATUS1_REG                         (0xFF6008)  /* DIP Status register1, */
#define DIP_CTRL1_REG                           (0xFF600A)  /* DIP Control register, clears DIP_INT if read */
#define DIP_SLOT_NUMBER_REG                     (0xFF600C)  /* DIP slot number register, returns the current slot number */
#define DIP_CTRL2_REG                           (0xFF600E)  /* DIP Control register 2 (debug status information) */
#define DIP_USB_PHASE_REG                       (0xFF6010)  /* Phase between SLOTZERO and USB SOF */
#define DIP_MOD_SEL_REG                         (0xFF6012)  /* DIP Modulo counters selection */
#define DIP_MOD_VAL_REG                         (0xFF6014)  /* DIP Modulo values selection */
#define BMC_CTRL_REG                            (0xFF6400)  /* BMC control register */
#define BMC_CTRL2_REG                           (0xFF6402)  /* BMC control register 2 */
#define BMC_TX_SFIELDL_REG                      (0xFF6404)  /* BMC Tx S field register Low */
#define BMC_TX_SFIELDH_REG                      (0xFF6406)  /* BMC Tx S field register High */
#define BMC_RX_SFIELDL_REG                      (0xFF6408)  /* BMC Rx S field register Low */
#define BMC_RX_SFIELDH_REG                      (0xFF640A)  /* BMC Rx S field register High */
#define USB_MCTRL_REG                           (0xFF6800)  /* Main Control Register) */
#define USB_XCVDIAG_REG                         (0xFF6802)  /* Transceiver diagnostic Register (for test purpose only) */
#define USB_TCR_REG                             (0xFF6804)  /* Transceiver configuration Register */
#define USB_UTR_REG                             (0xFF6806)  /* USB test Register (for test purpose only) */
#define USB_FAR_REG                             (0xFF6808)  /* Function Address Register */
#define USB_NFSR_REG                            (0xFF680A)  /* Node Functional State Register */
#define USB_MAEV_REG                            (0xFF680C)  /* Main Event Register */
#define USB_MAMSK_REG                           (0xFF680E)  /* Main Mask Register */
#define USB_ALTEV_REG                           (0xFF6810)  /* Alternate Event Register */
#define USB_ALTMSK_REG                          (0xFF6812)  /* Alternate Mask Register */
#define USB_TXEV_REG                            (0xFF6814)  /* Transmit Event Register */
#define USB_TXMSK_REG                           (0xFF6816)  /* Transmit Mask Register */
#define USB_RXEV_REG                            (0xFF6818)  /* Receive Event Register */
#define USB_RXMSK_REG                           (0xFF681A)  /* Receive Mask Register */
#define USB_NAKEV_REG                           (0xFF681C)  /* NAK Event Register */
#define USB_NAKMSK_REG                          (0xFF681E)  /* NAK Mask Register */
#define USB_FWEV_REG                            (0xFF6820)  /* FIFO Warning Event Register */
#define USB_FWMSK_REG                           (0xFF6822)  /* FIFO Warning Mask Register */
#define USB_FNH_REG                             (0xFF6824)  /* Frame Number High Byte Register */
#define USB_FNL_REG                             (0xFF6826)  /* Frame Number Low Byte Register */
#define USB_RESERVED_28_TO_3C                   (0xFF6828)  /* Reserved for USB */
#define USB_UX20CDR_REG                         (0xFF683E)  /* Transceiver 2.0 Configuration and Diagnostics Register (for test purpose only) */
#define USB_EPC0_REG                            (0xFF6840)  /* Endpoint Control 0 Register */
#define USB_TXD0_REG                            (0xFF6842)  /* Transmit Data 0 Register */
#define USB_TXS0_REG                            (0xFF6844)  /* Transmit Status 0 Register */
#define USB_TXC0_REG                            (0xFF6846)  /* Transmit command 0 Register */
#define USB_EP0_NAK_REG                         (0xFF6848)  /* EP0 INNAK and OUTNAK Register */
#define USB_RXD0_REG                            (0xFF684A)  /* Receive Data 0 Register */
#define USB_RXS0_REG                            (0xFF684C)  /* Receive Status 0 Register */
#define USB_RXC0_REG                            (0xFF684E)  /* Receive Command 0 Register */
#define USB_EPC1_REG                            (0xFF6850)  /* Endpoint Control Register 1 */
#define USB_TXD1_REG                            (0xFF6852)  /* Transmit Data Register 1 */
#define USB_TXS1_REG                            (0xFF6854)  /* Transmit Status Register 1 */
#define USB_TXC1_REG                            (0xFF6856)  /* Transmit Command Register 1 */
#define USB_EPC2_REG                            (0xFF6858)  /* Endpoint Control Register 2 */
#define USB_RXD1_REG                            (0xFF685A)  /* Receive Data Register,1 */
#define USB_RXS1_REG                            (0xFF685C)  /* Receive Status Register 1 */
#define USB_RXC1_REG                            (0xFF685E)  /* Receive Command Register 1 */
#define USB_EPC3_REG                            (0xFF6860)  /* Endpoint Control Register 3 */
#define USB_TXD2_REG                            (0xFF6862)  /* Transmit Data Register 2 */
#define USB_TXS2_REG                            (0xFF6864)  /* Transmit Status Register 2 */
#define USB_TXC2_REG                            (0xFF6866)  /* Transmit Command Register 2 */
#define USB_EPC4_REG                            (0xFF6868)  /* Endpoint Control Register 4 */
#define USB_RXD2_REG                            (0xFF686A)  /* Receive Data Register 2 */
#define USB_RXS2_REG                            (0xFF686C)  /* Receive Status Register 2 */
#define USB_RXC2_REG                            (0xFF686E)  /* Receive Command Register 2 */
#define USB_EPC5_REG                            (0xFF6870)  /* Endpoint Control Register 5 */
#define USB_TXD3_REG                            (0xFF6872)  /* Transmit Data Register 3 */
#define USB_TXS3_REG                            (0xFF6874)  /* Transmit Status Register 3 */
#define USB_TXC3_REG                            (0xFF6876)  /* Transmit Command Register 3 */
#define USB_EPC6_REG                            (0xFF6878)  /* Endpoint Control Register 6 */
#define USB_RXD3_REG                            (0xFF687A)  /* Receive Data Register 3 */
#define USB_RXS3_REG                            (0xFF687C)  /* Receive Status Register 3 */
#define USB_RXC3_REG                            (0xFF687E)  /* Receive Command Register 3 */
#define CCU_CRC_LOW_REG                         (0xFF6C00)  /* CCU MSB result */
#define CCU_CRC_HIGH_REG                        (0xFF6C02)  /* CCU LSB result */
#define CCU_IN_REG                              (0xFF6C04)  /* CCU Input */
#define CCU_MODE_REG                            (0xFF6C06)  /* CCU mode */
#define CHIP_ID1_REG                            (0xFFFBF8)  /* Chip identification register 1 */
#define CHIP_ID2_REG                            (0xFFFBF9)  /* Chip identification register 2 */
#define CHIP_ID3_REG                            (0xFFFBFA)  /* Chip identification register 3 */
#define CHIP_MEM_SIZE_REG                       (0xFFFBFB)  /* Chip memory size register */
#define CHIP_REVISION_REG                       (0xFFFBFC)  /* Chip revision registers (Corresponds to Chip Marking) */
#define CHIP_LAYOUT_REG                         (0xFFFBFD)  /* Chip layout version register */
#define CHIP_FOUNDRY_REG                        (0xFFFBFE)  /* Chip Foundry register */
#define INT_ACK_CR16_START                      (0xFFFC00)  /*  */
#define INT_ACK_CR16_END                        (0xFFFFFF)  /*  */
#define DIP_RAM_START                           (0x1000000)  /*  */
#define DIP_RAM_END                             (0x10001FF)  /*  */
#define DIP_RAM_2_START                         (0x1000200)  /*  */
#define DIP_RAM_2_END                           (0x10003FF)  /*  */
#define SHARED_ROM1_START                       (0x1020000)  /*  */
#define SHARED_ROM1_END                         (0x10207FF)  /*  */
#define DSP_MAIN_SYNC0_REG                      (0x1027F80)  /* DSP main counter outputs selection register 0 */
#define DSP_MAIN_SYNC1_REG                      (0x1027F82)  /* DSP main counter outputs selection register 1 */
#define DSP_MAIN_CNT_REG                        (0x1027F84)  /* DSP main counter and reload register */
#define DSP_ADC0S_REG                           (0x1027F86)  /* ADC0 Input 2's Complement register */
#define DSP_ADC1S_REG                           (0x1027F88)  /* ADC1 Input 2's Complement register */
#define DSP_CLASSD_REG                          (0x1027F8A)  /* CLASSD Output output data register */
#define DSP_CODEC_MIC_GAIN_REG                  (0x1027F8C)  /* CODEC MIC GAIN register */
#define DSP_CODEC_OUT_REG                       (0x1027F8E)  /* CODEC DATA register */
#define DSP_CODEC_IN_REG                        (0x1027F90)  /* CODEC DATA register */
#define DSP_RAM_OUT0_REG                        (0x1027F92)  /* Shared RAM 1 or 2 output register 0 */
#define DSP_RAM_OUT1_REG                        (0x1027F94)  /* Shared RAM 1 or 2 output register 1 */
#define DSP_RAM_OUT2_REG                        (0x1027F96)  /* Shared RAM 1 or 2 output register 2 */
#define DSP_RAM_OUT3_REG                        (0x1027F98)  /* Shared RAM 1 or 2 output register 3 */
#define DSP_RAM_IN0_REG                         (0x1027F9A)  /* Shared RAM 1 or 2 input register 0 */
#define DSP_RAM_IN1_REG                         (0x1027F9C)  /* Shared RAM 1 or 2 input register 1 */
#define DSP_RAM_IN2_REG                         (0x1027F9E)  /* Shared RAM 1 or 2 input register 2 */
#define DSP_RAM_IN3_REG                         (0x1027FA0)  /* Shared RAM 1 or 2 input register 3 */
#define DSP_ZCROSS1_OUT_REG                     (0x1027FA2)  /* ZERO CROSSING 1 output register */
#define DSP_ZCROSS2_OUT_REG                     (0x1027FA4)  /* ZERO CROSSING 2 output register */
#define DSP_PCM_OUT0_REG                        (0x1027FA6)  /* PCM channel 0 output register */
#define DSP_PCM_OUT1_REG                        (0x1027FA8)  /* PCM channel 1 output register */
#define DSP_PCM_OUT2_REG                        (0x1027FAA)  /* PCM channel 2 output register */
#define DSP_PCM_OUT3_REG                        (0x1027FAC)  /* PCM channel 3 output register */
#define DSP_PCM_IN0_REG                         (0x1027FAE)  /* PCM channel 0 input register */
#define DSP_PCM_IN1_REG                         (0x1027FB0)  /* PCM channel 1 input register */
#define DSP_PCM_IN2_REG                         (0x1027FB2)  /* PCM channel 2 input register */
#define DSP_PCM_IN3_REG                         (0x1027FB4)  /* PCM channel 3 input register */
#define DSP_PCM_CTRL_REG                        (0x1027FB6)  /* PCM Control register */
#define DSP_PHASE_INFO_REG                      (0x1027FB8)  /* Phase information between PCM FSC 8/16/32 and main counter 8/16/32 kHz */
#define DSP_VQI_REG                             (0x1027FBA)  /* BMC VQI register */
#define DSP_MAIN_CTRL_REG                       (0x1027FBC)  /* DSP Main counter control and preset value */
#define DSP_CLASSD_BUZZOFF_REG                  (0x1027FBE)  /* CLASSD Buzzer on/off controller, bit 15 */
#define DSP1_CTRL_REG                           (0x1027FD0)  /* DSP1 control register */
#define DSP1_PC_REG                             (0x1027FD2)  /* DSP1 Programma counter */
#define DSP1_PC_START_REG                       (0x1027FD4)  /* DSP1 Programma counter start */
#define DSP1_IRQ_START_REG                      (0x1027FD6)  /* DSP1 Interrupt vector start */
#define DSP1_INT_REG                            (0x1027FD8)  /* DSP1 to CR16 interrupt vector */
#define DSP1_INT_MASK_REG                       (0x1027FDA)  /* DSP1 to CR16 interrupt vector maks */
#define DSP1_INT_PRIO1_REG                      (0x1027FDC)  /* DSP1 Interrupt source mux 1 register */
#define DSP1_INT_PRIO2_REG                      (0x1027FDE)  /* DSP1 Interrupt source mux 2 register */
#define DSP1_OVERFLOW_REG                       (0x1027FE0)  /* DSP1 to CR16 overflow register */
#define DBG1_IREG                               (0x1027FF0)  /* DSP1 JTAG instruction register */
#define DBG1_INOUT_REG_LSW                      (0x1027FF4)  /*  */
#define DBG1_INOUT_REG_MSW                      (0x1027FF6)  /*  */
#define SHARED_ROM2_START                       (0x1028000)  /*  */
#define SHARED_ROM2_END                         (0x102BFFF)  /*  */
#define DSP2_CTRL_REG                           (0x102FFD0)  /* DSP2 control register */
#define DSP2_PC_REG                             (0x102FFD2)  /* DSP2 Programma counter */
#define DSP2_PC_START_REG                       (0x102FFD4)  /* DSP2 Programma counter start */
#define DSP2_IRQ_START_REG                      (0x102FFD6)  /* DSP2 Interrupt vector start */
#define DSP2_INT_REG                            (0x102FFD8)  /* DSP2 to CR16 interrupt vector */
#define DSP2_INT_MASK_REG                       (0x102FFDA)  /* DSP2 to CR16 interrupt vector maks */
#define DSP2_INT_PRIO1_REG                      (0x102FFDC)  /* DSP2 Interrupt source mux 1 register */
#define DSP2_INT_PRIO2_REG                      (0x102FFDE)  /* DSP2 Interrupt source mux 2 register */
#define DSP2_OVERFLOW_REG                       (0x102FFE0)  /* DSP2 to CR16 overflow register */
#define DBG2_IREG                               (0x102FFF0)  /* DSP2 JTAG instruction register */
#define DBG2_INOUT_REG_LSW                      (0x102FFF4)  /*  */
#define DBG2_INOUT_REG_MSW                      (0x102FFF6)  /*  */
#define DSP_MC_RAM1_START                       (0x1030000)  /*  */
#define DSP_MC_RAM1_END                         (0x1033FFF)  /*  */
#define DSP_MC_RAM2_START                       (0x1034000)  /*  */
#define DSP_MC_RAM2_END                         (0x1037FFF)  /*  */
#define DSP_MC_ROM1_START                       (0x1040000)  /*  */
#define DSP_MC_ROM1_END                         (0x1047FFF)  /*  */
#define DSP_MC_ROM2_START                       (0x1060000)  /*  */
#define DSP_MC_ROM2_END                         (0x107FFFF)  /*  */




/*====================================================*/
struct __ACCESS1_CTRL_REG
/*====================================================*/
{
    WORD BITFLD_EN_ACCESS_BUS                      : 1;
    WORD BITFLD_ACKn                               : 1;
    WORD BITFLD_SCL_VAL                            : 1;
    WORD BITFLD_SDA_VAL                            : 1;
    WORD BITFLD_ACCESS_INT                         : 1;
    WORD BITFLD_EN_ACCESS_INT                      : 1;
    WORD BITFLD_SCL_OD                             : 1;
    WORD BITFLD_SDA_OD                             : 1;
    WORD BITFLD_SCK_NUM                            : 1;
    WORD BITFLD_SCK_SEL                            : 2;
};

#define EN_ACCESS_BUS                      (0x0001)
#define ACKn                               (0x0002)
#define SCL_VAL                            (0x0004)
#define SDA_VAL                            (0x0008)
#define ACCESS_INT                         (0x0010)
#define EN_ACCESS_INT                      (0x0020)
#define SCL_OD                             (0x0040)
#define SDA_OD                             (0x0080)
#define SCK_NUM                            (0x0100)
#define SCK_SEL                            (0x0600)


/*====================================================*/
struct __ACCESS2_CTRL_REG
/*====================================================*/
{
    WORD BITFLD_EN_ACCESS_BUS                      : 1;
    WORD BITFLD_ACKn                               : 1;
    WORD BITFLD_SCL_VAL                            : 1;
    WORD BITFLD_SDA_VAL                            : 1;
    WORD BITFLD_ACCESS_INT                         : 1;
    WORD BITFLD_EN_ACCESS_INT                      : 1;
    WORD BITFLD_SCL_OD                             : 1;
    WORD BITFLD_SDA_OD                             : 1;
    WORD BITFLD_SCK_NUM                            : 1;
    WORD BITFLD_SCK_SEL                            : 2;
};

#define EN_ACCESS_BUS                      (0x0001)
#define ACKn                               (0x0002)
#define SCL_VAL                            (0x0004)
#define SDA_VAL                            (0x0008)
#define ACCESS_INT                         (0x0010)
#define EN_ACCESS_INT                      (0x0020)
#define SCL_OD                             (0x0040)
#define SDA_OD                             (0x0080)
#define SCK_NUM                            (0x0100)
#define SCK_SEL                            (0x0600)


/*====================================================*/
struct __AD_CTRL_REG
/*====================================================*/
{
    WORD BITFLD_ADC_START                          : 1;
    WORD BITFLD_ADC_AUTO                           : 1;
    WORD BITFLD_ADC_ALT                            : 1;
    WORD BITFLD_ADC_IN_3_0                         : 4;
    WORD BITFLD_ADC_TEST                           : 4;
    WORD BITFLD_ADC_INT                            : 1;
    WORD BITFLD_ADC_MINT                           : 1;
    WORD                                           : 1;
    WORD BITFLD_ADC0_PR_DIS                        : 1;
    WORD BITFLD_ADC1_PR_DIS                        : 1;
};

#define ADC_START                          (0x0001)
#define ADC_AUTO                           (0x0002)
#define ADC_ALT                            (0x0004)
#define ADC_IN_3_0                         (0x0078)
#define ADC_TEST                           (0x0780)
#define ADC_INT                            (0x0800)
#define ADC_MINT                           (0x1000)
#define ADC0_PR_DIS                        (0x4000)
#define ADC1_PR_DIS                        (0x8000)


/*====================================================*/
struct __AD_CTRL1_REG
/*====================================================*/
{
    WORD BITFLD_ADC_IN_3_0_1                       : 4;
};

#define ADC_IN_3_0_1                       (0x000F)


/*====================================================*/
struct __ADC0_REG
/*====================================================*/
{
    WORD BITFLD_ADC0_VAL                           : 10;
};

#define ADC0_VAL                           (0x03FF)


/*====================================================*/
struct __ADC1_REG
/*====================================================*/
{
    WORD BITFLD_ADC1_VAL                           : 10;
};

#define ADC1_VAL                           (0x03FF)


/*====================================================*/
struct __BANDGAP_REG
/*====================================================*/
{
    WORD BITFLD_BANDGAP_VI                         : 4;
    WORD BITFLD_BANDGAP_VIT                        : 2;
    WORD BITFLD_BANDGAP_I                          : 3;
};

#define BANDGAP_VI                         (0x000F)
#define BANDGAP_VIT                        (0x0030)
#define BANDGAP_I                          (0x01C0)


/*====================================================*/
struct __BAT_CTRL_REG
/*====================================================*/
{
    WORD BITFLD_REG_ON                             : 1;
    WORD BITFLD_LDO1_ON                            : 1;
    WORD BITFLD_DC_ON                              : 1;
    WORD BITFLD_LDO1_LEVEL                         : 3;
    WORD BITFLD_DC_MODE                            : 2;
    WORD BITFLD_DC_VOUT                            : 3;
    WORD BITFLD_DC_HYST                            : 1;
    WORD BITFLD_DC_IMAX                            : 1;
    WORD BITFLD_DC_FREQ                            : 2;
    WORD BITFLD_DC_CLK_SEL                         : 1;
};

#define REG_ON                             (0x0001)
#define LDO1_ON                            (0x0002)
#define DC_ON                              (0x0004)
#define LDO1_LEVEL                         (0x0038)
#define DC_MODE                            (0x00C0)
#define DC_VOUT                            (0x0700)
#define DC_HYST                            (0x0800)
#define DC_IMAX                            (0x1000)
#define DC_FREQ                            (0x6000)
#define DC_CLK_SEL                         (0x8000)


/*====================================================*/
struct __BAT_CTRL2_REG
/*====================================================*/
{
    WORD BITFLD_CHARGE_LEVEL                       : 5;
    WORD BITFLD_CHARGE_ON                          : 1;
    WORD BITFLD_NTC_DISABLE                        : 1;
    WORD                                           : 3;
    WORD BITFLD_CHARGE_CUR                         : 3;
    WORD BITFLD_SOC_ON                             : 1;
    WORD BITFLD_SOC_CAL                            : 1;
    WORD BITFLD_SOC_TEST                           : 1;
};

#define CHARGE_LEVEL                       (0x001F)
#define CHARGE_ON                          (0x0020)
#define NTC_DISABLE                        (0x0040)
#define CHARGE_CUR                         (0x1C00)
#define SOC_ON                             (0x2000)
#define SOC_CAL                            (0x4000)
#define SOC_TEST                           (0x8000)


/*====================================================*/
struct __BAT_STATUS_REG
/*====================================================*/
{
    WORD BITFLD_VBAT3_STS                          : 1;
    WORD BITFLD_PON_STS                            : 1;
    WORD BITFLD_CHARGE_STS                         : 1;
    WORD BITFLD_CHARGE_I_LIMIT                     : 1;
    WORD BITFLD_TWO_CELL_STS                       : 1;
    WORD BITFLD_VBUS_OK                            : 1;
};

#define VBAT3_STS                          (0x0001)
#define PON_STS                            (0x0002)
#define CHARGE_STS                         (0x0004)
#define CHARGE_I_LIMIT                     (0x0008)
#define TWO_CELL_STS                       (0x0010)
#define VBUS_OK                            (0x0020)


/*====================================================*/
struct __BMC_CTRL_REG
/*====================================================*/
{
    WORD                                           : 4;
    WORD BITFLD_GAUSS_REF                          : 1;
    WORD BITFLD_RSSI_RANGE                         : 1;
    WORD BITFLD_RSSI_TDO                           : 1;
    WORD                                           : 1;
    WORD BITFLD_SIO_PD                             : 1;
    WORD                                           : 4;
    WORD BITFLD_BCNT_INH                           : 1;
};

#define GAUSS_REF                          (0x0010)
#define RSSI_RANGE                         (0x0020)
#define RSSI_TDO                           (0x0040)
#define SIO_PD                             (0x0100)
#define BCNT_INH                           (0x2000)


/*====================================================*/
struct __BMC_CTRL2_REG
/*====================================================*/
{
    WORD BITFLD_DAC_TEST                           : 3;
    WORD BITFLD_RCV_CTL                            : 5;
};

#define DAC_TEST                           (0x0007)
#define RCV_CTL                            (0x00F8)


/*====================================================*/
struct __CACHE_CTRL_REG
/*====================================================*/
{
    WORD BITFLD_CACHE_SIZE                         : 3;
    WORD BITFLD_CACHE_TEST                         : 1;
    WORD BITFLD_CACHE_MODE                         : 2;
    WORD BITFLD_CACHE_LOCK                         : 1;
    WORD BITFLD_CACHE_PAR                          : 1;
    WORD BITFLD_ICACHE_B_SIZE                      : 1;
    WORD BITFLD_ICACHE_PF_EN                       : 1;
    WORD BITFLD_DCACHE_B_SIZE                      : 1;
    WORD BITFLD_DCACHE_PF_EN                       : 1;
    WORD BITFLD_TRACE_SIZE                         : 2;
    WORD BITFLD_TRACE_CTRL                         : 1;
    WORD BITFLD_TRACE_MODE                         : 1;
};

#define CACHE_SIZE                         (0x0007)
#define CACHE_TEST                         (0x0008)
#define CACHE_MODE                         (0x0030)
#define CACHE_LOCK                         (0x0040)
#define CACHE_PAR                          (0x0080)
#define ICACHE_B_SIZE                      (0x0100)
#define ICACHE_PF_EN                       (0x0200)
#define DCACHE_B_SIZE                      (0x0400)
#define DCACHE_PF_EN                       (0x0800)
#define TRACE_SIZE                         (0x3000)
#define TRACE_CTRL                         (0x4000)
#define TRACE_MODE                         (0x8000)


/*====================================================*/
struct __CACHE_LEN0_REG
/*====================================================*/
{
    WORD BITFLD_CACHE_LEN0                         : 9;
};

#define CACHE_LEN0                         (0x01FF)


/*====================================================*/
struct __CACHE_START0_REG
/*====================================================*/
{
    WORD BITFLD_CACHE_START0                       : 9;
};

#define CACHE_START0                       (0x01FF)


/*====================================================*/
struct __CACHE_LEN1_REG
/*====================================================*/
{
    WORD BITFLD_CACHE_LEN1                         : 9;
};

#define CACHE_LEN1                         (0x01FF)


/*====================================================*/
struct __CACHE_START1_REG
/*====================================================*/
{
    WORD BITFLD_CACHE_START1                       : 9;
};

#define CACHE_START1                       (0x01FF)


/*====================================================*/
struct __CACHE_STATUS_REG
/*====================================================*/
{
    WORD BITFLD_TRACE_IDX                          : 10;
    WORD BITFLD_ICACHE_HIT                         : 1;
    WORD BITFLD_DCACHE_HIT                         : 1;
    WORD BITFLD_CACHE_TOUCH                        : 1;
    WORD BITFLD_TRACE_TOUCH                        : 1;
    WORD BITFLD_reserved                           : 2;
};

#define TRACE_IDX                          (0x03FF)
#define ICACHE_HIT                         (0x0400)
#define DCACHE_HIT                         (0x0800)
#define CACHE_TOUCH                        (0x1000)
#define TRACE_TOUCH                        (0x2000)
#define reserved                           (0xC000)


/*====================================================*/
struct __CCU_MODE_REG
/*====================================================*/
{
    WORD BITFLD_CCU_MODE                           : 2;
    WORD BITFLD_CCU_BIT_SWAP                       : 1;
    WORD BITFLD_CCU_BYTE_SWAP                      : 1;
};

#define CCU_MODE                           (0x0003)
#define CCU_BIT_SWAP                       (0x0004)
#define CCU_BYTE_SWAP                      (0x0008)


/*====================================================*/
struct __CHIP_REVISION_REG
/*====================================================*/
{
    WORD                                           : 4;
    WORD BITFLD_REVISION_ID                        : 4;
};

#define REVISION_ID                        (0x00F0)


/*====================================================*/
struct __CLASSD_BUZZER_REG
/*====================================================*/
{
    WORD BITFLD_CLASSD_BUZ_GAIN                    : 4;
    WORD BITFLD_CLASSD_BUZ_MODE                    : 1;
};

#define CLASSD_BUZ_GAIN                    (0x000F)
#define CLASSD_BUZ_MODE                    (0x0010)


/*====================================================*/
struct __CLASSD_CTRL_REG
/*====================================================*/
{
    WORD BITFLD_CLASSD_PD                          : 1;
    WORD BITFLD_CLASSD_PROT                        : 1;
    WORD BITFLD_CLASSD_VOUT                        : 2;
    WORD BITFLD_CLASSD_CLIP                        : 3;
    WORD BITFLD_CLASSD_INT_BIT                     : 1;
    WORD BITFLD_CLASSD_DITH_D                      : 2;
    WORD BITFLD_CLASSD_DITH_A                      : 2;
    WORD BITFLD_CLASSD_MODE                        : 1;
    WORD BITFLD_CLASSD_MINT                        : 1;
    WORD BITFLD_CLASSD_MOPEN                       : 1;
    WORD BITFLD_CLASSD_POPEN                       : 1;
};

#define CLASSD_PD                          (0x0001)
#define CLASSD_PROT                        (0x0002)
#define CLASSD_VOUT                        (0x000C)
#define CLASSD_CLIP                        (0x0070)
#define CLASSD_INT_BIT                     (0x0080)
#define CLASSD_DITH_D                      (0x0300)
#define CLASSD_DITH_A                      (0x0C00)
#define CLASSD_MODE                        (0x1000)
#define CLASSD_MINT                        (0x2000)
#define CLASSD_MOPEN                       (0x4000)
#define CLASSD_POPEN                       (0x8000)


/*====================================================*/
struct __CLASSD_TEST_REG
/*====================================================*/
{
    WORD BITFLD_CLASSD_SWITCH                      : 1;
    WORD BITFLD_CLASSD_RST_D                       : 1;
    WORD BITFLD_CLASSD_RST_A                       : 1;
    WORD BITFLD_CLASSD_FORCE                       : 1;
    WORD BITFLD_CLASSD_DIG_MUTE                    : 1;
    WORD BITFLD_CLASSD_ANA_TEST                    : 3;
};

#define CLASSD_SWITCH                      (0x0001)
#define CLASSD_RST_D                       (0x0002)
#define CLASSD_RST_A                       (0x0004)
#define CLASSD_FORCE                       (0x0008)
#define CLASSD_DIG_MUTE                    (0x0010)
#define CLASSD_ANA_TEST                    (0x00E0)


/*====================================================*/
struct __CLASSD_NR_REG
/*====================================================*/
{
    WORD BITFLD_CLASSD_NR_ACTIVE                   : 1;
    WORD BITFLD_CLASSD_NR_LVL                      : 3;
    WORD BITFLD_CLASSD_NR_TON                      : 4;
    WORD BITFLD_CLASSD_NR_HYST                     : 2;
    WORD BITFLD_CLASSD_NR_ZERO                     : 2;
};

#define CLASSD_NR_ACTIVE                   (0x0001)
#define CLASSD_NR_LVL                      (0x000E)
#define CLASSD_NR_TON                      (0x00F0)
#define CLASSD_NR_HYST                     (0x0300)
#define CLASSD_NR_ZERO                     (0x0C00)


/*====================================================*/
struct __CLK_AMBA_REG
/*====================================================*/
{
    WORD BITFLD_HCLK_DIV                           : 3;
    WORD BITFLD_PCLK_DIV                           : 2;
    WORD BITFLD_SRAM1_EN                           : 1;
    WORD BITFLD_SRAM2_EN                           : 1;
    WORD BITFLD_MCRAM1_EN                          : 1;
    WORD BITFLD_MCRAM2_EN                          : 1;
    WORD BITFLD_HCLK_PRE                           : 1;
};

#define HCLK_DIV                           (0x0007)
#define PCLK_DIV                           (0x0018)
#define SRAM1_EN                           (0x0020)
#define SRAM2_EN                           (0x0040)
#define MCRAM1_EN                          (0x0080)
#define MCRAM2_EN                          (0x0100)
#define HCLK_PRE                           (0x0200)


/*====================================================*/
struct __CLK_AUX_REG
/*====================================================*/
{
    WORD BITFLD_BXTAL_DIV                          : 3;
    WORD BITFLD_BXTAL_EN                           : 2;
    WORD BITFLD_OWI_DIV                            : 2;
    WORD BITFLD_OWI_SEL                            : 1;
    WORD BITFLD_XDIV                               : 1;
    WORD BITFLD_USB_TST_CLK                        : 1;
};

#define BXTAL_DIV                          (0x0007)
#define BXTAL_EN                           (0x0018)
#define OWI_DIV                            (0x0060)
#define OWI_SEL                            (0x0080)
#define XDIV                               (0x0100)
#define USB_TST_CLK                        (0x0200)


/*====================================================*/
struct __CLK_CODEC_DIV_REG
/*====================================================*/
{
    WORD BITFLD_CODEC_DIV                          : 7;
    WORD BITFLD_CODEC_CLK_SEL                      : 2;
};

#define CODEC_DIV                          (0x007F)
#define CODEC_CLK_SEL                      (0x0180)


/*====================================================*/
struct __CLK_CODEC_REG
/*====================================================*/
{
    WORD BITFLD_CLK_MAIN_SEL                       : 2;
    WORD BITFLD_CLK_AD_SEL                         : 2;
    WORD BITFLD_CLK_DA_CLASSD_SEL                  : 2;
    WORD BITFLD_CLK_DA_LSR_SEL                     : 2;
    WORD BITFLD_CLK_PCM_SEL                        : 2;
};

#define CLK_MAIN_SEL                       (0x0003)
#define CLK_AD_SEL                         (0x000C)
#define CLK_DA_CLASSD_SEL                  (0x0030)
#define CLK_DA_LSR_SEL                     (0x00C0)
#define CLK_PCM_SEL                        (0x0300)


/*====================================================*/
struct __CLK_DSP_REG
/*====================================================*/
{
    WORD BITFLD_CLK_DSP1_DIV                       : 3;
    WORD BITFLD_CLK_DSP1_EN                        : 1;
    WORD BITFLD_CLK_DSP2_DIV                       : 3;
    WORD BITFLD_CLK_DSP2_EN                        : 1;
};

#define CLK_DSP1_DIV                       (0x0007)
#define CLK_DSP1_EN                        (0x0008)
#define CLK_DSP2_DIV                       (0x0070)
#define CLK_DSP2_EN                        (0x0080)


/*====================================================*/
struct __CLK_FREQ_TRIM_REG
/*====================================================*/
{
    WORD BITFLD_FINE_ADJ                           : 5;
    WORD BITFLD_COARSE_ADJ                         : 3;
    WORD BITFLD_CL_SEL                             : 1;
    WORD BITFLD_OSC_OK                             : 1;
};

#define FINE_ADJ                           (0x001F)
#define COARSE_ADJ                         (0x00E0)
#define CL_SEL                             (0x0100)
#define OSC_OK                             (0x0200)


/*====================================================*/
struct __CLK_PER_DIV_REG
/*====================================================*/
{
    WORD BITFLD_PER_DIV                            : 7;
    WORD BITFLD_PER_CLK_SEL                        : 2;
};

#define PER_DIV                            (0x007F)
#define PER_CLK_SEL                        (0x0180)


/*====================================================*/
struct __CLK_PER10_DIV_REG
/*====================================================*/
{
    WORD BITFLD_PER10_DIV                          : 3;
    WORD BITFLD_PER10_CLK_SEL                      : 2;
    WORD BITFLD_PER20_DIV                          : 3;
};

#define PER10_DIV                          (0x0007)
#define PER10_CLK_SEL                      (0x0018)
#define PER20_DIV                          (0x00E0)


/*====================================================*/
struct __CLK_PLL1_CTRL_REG
/*====================================================*/
{
    WORD BITFLD_TESTMODE_SEL                       : 1;
    WORD BITFLD_CP_ON                              : 1;
    WORD BITFLD_PLL1_OUT_DIV                       : 1;
    WORD BITFLD_PLL_CLK_SEL                        : 1;
    WORD BITFLD_VCO_ON                             : 1;
    WORD                                           : 1;
    WORD BITFLD_HF_SEL                             : 1;
    WORD BITFLD_PLL_DIP_DIV                        : 4;
    WORD BITFLD_DYN_SW                             : 1;
};

#define TESTMODE_SEL                       (0x0001)
#define CP_ON                              (0x0002)
#define PLL1_OUT_DIV                       (0x0004)
#define PLL_CLK_SEL                        (0x0008)
#define VCO_ON                             (0x0010)
#define HF_SEL                             (0x0040)
#define PLL_DIP_DIV                        (0x0780)
#define DYN_SW                             (0x0800)


/*====================================================*/
struct __CLK_PLL1_DIV_REG
/*====================================================*/
{
    WORD BITFLD_XD1                                : 2;
    WORD BITFLD_VD1                                : 3;
};

#define XD1                                (0x0003)
#define VD1                                (0x001C)


/*====================================================*/
struct __CLK_PLL2_DIV_REG
/*====================================================*/
{
    WORD BITFLD_XD                                 : 7;
    WORD BITFLD_DIV2                               : 1;
    WORD BITFLD_DIV1                               : 1;
    WORD BITFLD_VD                                 : 4;
    WORD BITFLD_DIV4                               : 1;
    WORD BITFLD_DIV3                               : 1;
    WORD BITFLD_DIV5                               : 1;
};

#define XD                                 (0x007F)
#define DIV2                               (0x0080)
#define DIV1                               (0x0100)
#define VD                                 (0x1E00)
#define DIV4                               (0x2000)
#define DIV3                               (0x4000)
#define DIV5                               (0x8000)


/*====================================================*/
struct __CLK_XTAL_CTRL_REG
/*====================================================*/
{
    WORD BITFLD_LDO_XTAL_ON                        : 1;
    WORD BITFLD_XTAL_SUPPLY                        : 1;
    WORD BITFLD_AVD_XTAL_OK                        : 1;
    WORD BITFLD_LDO_RFCLK_ON                       : 2;
    WORD BITFLD_RFCLK_SUPPLY                       : 1;
    WORD BITFLD_LDO_RFCLK_OK                       : 1;
    WORD BITFLD_XTAL_EXTRA_CV                      : 1;
};

#define LDO_XTAL_ON                        (0x0001)
#define XTAL_SUPPLY                        (0x0002)
#define AVD_XTAL_OK                        (0x0004)
#define LDO_RFCLK_ON                       (0x0018)
#define RFCLK_SUPPLY                       (0x0020)
#define LDO_RFCLK_OK                       (0x0040)
#define XTAL_EXTRA_CV                      (0x0080)


/*====================================================*/
struct __CODEC_ADDA_REG
/*====================================================*/
{
    WORD BITFLD_DA_PD                              : 1;
    WORD BITFLD_AD_PD                              : 1;
    WORD BITFLD_DA_CADJ                            : 2;
    WORD BITFLD_AD_CADJ                            : 2;
    WORD BITFLD_DA_DITH_OFF                        : 1;
    WORD BITFLD_AD_DITH_OFF                        : 1;
    WORD BITFLD_DA_HBW                             : 1;
    WORD BITFLD_LPF_PD                             : 1;
    WORD BITFLD_LPF_BW                             : 3;
    WORD BITFLD_ADC_VREF_LSR                       : 2;
    WORD BITFLD_AUTO_SYNC                          : 1;
};

#define DA_PD                              (0x0001)
#define AD_PD                              (0x0002)
#define DA_CADJ                            (0x000C)
#define AD_CADJ                            (0x0030)
#define DA_DITH_OFF                        (0x0040)
#define AD_DITH_OFF                        (0x0080)
#define DA_HBW                             (0x0100)
#define LPF_PD                             (0x0200)
#define LPF_BW                             (0x1C00)
#define ADC_VREF_LSR                       (0x6000)
#define AUTO_SYNC                          (0x8000)


/*====================================================*/
struct __CODEC_LSR_REG
/*====================================================*/
{
    WORD BITFLD_LSRP_MODE                          : 2;
    WORD BITFLD_LSRP_PD                            : 1;
    WORD BITFLD_LSRN_MODE                          : 2;
    WORD BITFLD_LSRN_PD                            : 1;
    WORD BITFLD_LSRATT                             : 3;
    WORD BITFLD_LSREN_SE                           : 1;
};

#define LSRP_MODE                          (0x0003)
#define LSRP_PD                            (0x0004)
#define LSRN_MODE                          (0x0018)
#define LSRN_PD                            (0x0020)
#define LSRATT                             (0x01C0)
#define LSREN_SE                           (0x0200)


/*====================================================*/
struct __CODEC_MIC_REG
/*====================================================*/
{
    WORD BITFLD_MIC_MODE                           : 2;
    WORD BITFLD_MIC_PD                             : 1;
    WORD BITFLD_MIC_MUTE                           : 1;
    WORD BITFLD_MIC_GAIN                           : 4;
    WORD BITFLD_MIC_OFFCOM_SG                      : 1;
    WORD BITFLD_MIC_OFFCOM_ON                      : 1;
    WORD BITFLD_DSP_CTRL                           : 1;
    WORD BITFLD_MICH_ON                            : 1;
    WORD BITFLD_MIC_CADJ                           : 2;
};

#define MIC_MODE                           (0x0003)
#define MIC_PD                             (0x0004)
#define MIC_MUTE                           (0x0008)
#define MIC_GAIN                           (0x00F0)
#define MIC_OFFCOM_SG                      (0x0100)
#define MIC_OFFCOM_ON                      (0x0200)
#define DSP_CTRL                           (0x0400)
#define MICH_ON                            (0x0800)
#define MIC_CADJ                           (0x3000)


/*====================================================*/
struct __CODEC_TEST_CTRL_REG
/*====================================================*/
{
    WORD BITFLD_TCR                                : 12;
    WORD BITFLD_COR_ON                             : 1;
    WORD BITFLD_COR_STAT                           : 1;
};

#define TCR                                (0x0FFF)
#define COR_ON                             (0x1000)
#define COR_STAT                           (0x2000)


/*====================================================*/
struct __CODEC_TONE_REG
/*====================================================*/
{
    WORD BITFLD_CID_PD                             : 1;
    WORD BITFLD_CID_PR_DIS                         : 1;
    WORD BITFLD_RNG_CMP_PD                         : 1;
};

#define CID_PD                             (0x0001)
#define CID_PR_DIS                         (0x0002)
#define RNG_CMP_PD                         (0x0004)


/*====================================================*/
struct __CODEC_VREF_REG
/*====================================================*/
{
    WORD BITFLD_VREF_PD                            : 1;
    WORD                                           : 1;
    WORD BITFLD_VREF_FILT_CADJ                     : 16;
    WORD BITFLD_VREF_INIT                          : 1;
    WORD BITFLD_AMP1V5_PD                          : 1;
    WORD BITFLD_VREF_BG_PD                         : 1;
    WORD BITFLD_BIAS_PD                            : 1;
    WORD BITFLD_AGND_LSR_PD                        : 1;
    WORD BITFLD_REFINT_PD                          : 1;
};

#define VREF_PD                            (0x0001)
#define VREF_FILT_CADJ                     (0x80000000)
#define VREF_INIT                          (0x0010)
#define AMP1V5_PD                          (0x0020)
#define VREF_BG_PD                         (0x0040)
#define BIAS_PD                            (0x0080)
#define AGND_LSR_PD                        (0x0100)
#define REFINT_PD                          (0x0200)


/*====================================================*/
struct __CP_CTRL_REG
/*====================================================*/
{
    WORD BITFLD_CP_EN                              : 2;
    WORD BITFLD_CP_LEVEL                           : 2;
    WORD BITFLD_CP_PWM                             : 1;
    WORD BITFLD_CP_FREQ                            : 1;
    WORD BITFLD_CP_PARALLEL                        : 1;
    WORD BITFLD_CP_EXTRA                           : 1;
    WORD BITFLD_CP_MODE                            : 1;
    WORD                                           : 3;
    WORD BITFLD_CP_TEST_ADC1                       : 1;
    WORD BITFLD_CP_TEST_ADC2                       : 1;
};

#define CP_EN                              (0x0003)
#define CP_LEVEL                           (0x000C)
#define CP_PWM                             (0x0010)
#define CP_FREQ                            (0x0020)
#define CP_PARALLEL                        (0x0040)
#define CP_EXTRA                           (0x0080)
#define CP_MODE                            (0x0100)
#define CP_TEST_ADC1                       (0x1000)
#define CP_TEST_ADC2                       (0x2000)


/*====================================================*/
struct __DEBUG_REG
/*====================================================*/
{
    WORD BITFLD_CLK100_EDGE                        : 1;
    WORD BITFLD_CLK100_NEG                         : 1;
    WORD BITFLD_CLK100_POS                         : 1;
    WORD BITFLD_CLK100_SRC                         : 1;
    WORD BITFLD_ENV_B01                            : 1;
    WORD                                           : 2;
    WORD BITFLD_SW_RESET                           : 1;
};

#define CLK100_EDGE                        (0x0001)
#define CLK100_NEG                         (0x0002)
#define CLK100_POS                         (0x0004)
#define CLK100_SRC                         (0x0008)
#define ENV_B01                            (0x0010)
#define SW_RESET                           (0x0080)


/*====================================================*/
struct __DIP_PC_REG
/*====================================================*/
{
    WORD BITFLD_DIP_PC                             : 8;
    WORD BITFLD_DIP_BANK                           : 1;
};

#define DIP_PC                             (0x00FF)
#define DIP_BANK                           (0x0100)


/*====================================================*/
struct __DIP_STATUS_REG
/*====================================================*/
{
    WORD BITFLD_DIP_INT_VEC                        : 4;
    WORD BITFLD_PD1_INT                            : 1;
    WORD BITFLD_DIP_BRK_INT                        : 1;
    WORD BITFLD_PRESCALER                          : 1;
    WORD BITFLD_URST                               : 1;
};

#define DIP_INT_VEC                        (0x000F)
#define PD1_INT                            (0x0010)
#define DIP_BRK_INT                        (0x0020)
#define PRESCALER                          (0x0040)
#define URST                               (0x0080)


/*====================================================*/
struct __DIP_CTRL_REG
/*====================================================*/
{
    WORD BITFLD_DIP_INT_VEC                        : 4;
    WORD BITFLD_PD1_INT                            : 1;
    WORD BITFLD_DIP_BRK_INT                        : 1;
    WORD BITFLD_PRESCALER                          : 1;
    WORD BITFLD_URST                               : 1;
};

#define DIP_INT_VEC                        (0x000F)
#define PD1_INT                            (0x0010)
#define DIP_BRK_INT                        (0x0020)
#define PRESCALER                          (0x0040)
#define URST                               (0x0080)


/*====================================================*/
struct __DIP_CTRL1_REG
/*====================================================*/
{
    WORD BITFLD_DIP_VNMI_VEC                       : 4;
};

#define DIP_VNMI_VEC                       (0x000F)


/*====================================================*/
struct __DIP_STATUS1_REG
/*====================================================*/
{
    WORD BITFLD_DIP_VNMI_VEC                       : 4;
};

#define DIP_VNMI_VEC                       (0x000F)


/*====================================================*/
struct __DIP_CTRL2_REG
/*====================================================*/
{
    WORD BITFLD_DBUF                               : 1;
    WORD BITFLD_PRE_ACT                            : 1;
    WORD BITFLD_BRK_PRE_OVR                        : 1;
    WORD                                           : 1;
    WORD BITFLD_PD1_INT                            : 1;
    WORD BITFLD_DIP_BRK                            : 1;
    WORD                                           : 1;
    WORD BITFLD_EN_8DIV9                           : 1;
    WORD BITFLD_SLOTCNT_RES                        : 1;
};

#define DBUF                               (0x0001)
#define PRE_ACT                            (0x0002)
#define BRK_PRE_OVR                        (0x0004)
#define PD1_INT                            (0x0010)
#define DIP_BRK                            (0x0020)
#define EN_8DIV9                           (0x0080)
#define SLOTCNT_RES                        (0x0100)


/*====================================================*/
struct __DIP_MOD_SEL_REG
/*====================================================*/
{
    WORD BITFLD_ARMOD0                             : 1;
    WORD BITFLD_ARMOD1                             : 1;
    WORD BITFLD_ARMOD2                             : 1;
    WORD BITFLD_ARMOD3                             : 1;
    WORD BITFLD_AWMOD0                             : 1;
    WORD BITFLD_AWMOD1                             : 1;
    WORD BITFLD_AWMOD2                             : 1;
    WORD BITFLD_AWMOD3                             : 1;
};

#define ARMOD0                             (0x0001)
#define ARMOD1                             (0x0002)
#define ARMOD2                             (0x0004)
#define ARMOD3                             (0x0008)
#define AWMOD0                             (0x0010)
#define AWMOD1                             (0x0020)
#define AWMOD2                             (0x0040)
#define AWMOD3                             (0x0080)


/*====================================================*/
struct __DIP_SLOT_NUMBER_REG
/*====================================================*/
{
    WORD BITFLD_SLOT_CNTER                         : 5;
};

#define SLOT_CNTER                         (0x001F)


/*====================================================*/
struct __DIP_USB_PHASE_REG
/*====================================================*/
{
    WORD BITFLD_DIP_USB_PHASE                      : 13;
};

#define DIP_USB_PHASE                      (0x1FFF)


/*====================================================*/
struct __DMA0_A_STARTH_REG
/*====================================================*/
{
    WORD BITFLD_DMAx_A_STARTH                      : 9;
};

#define DMAx_A_STARTH                      (0x01FF)


/*====================================================*/
struct __DMA1_A_STARTH_REG
/*====================================================*/
{
    WORD BITFLD_DMAx_A_STARTH                      : 9;
};

#define DMAx_A_STARTH                      (0x01FF)


/*====================================================*/
struct __DMA2_A_STARTH_REG
/*====================================================*/
{
    WORD BITFLD_DMAx_A_STARTH                      : 9;
};

#define DMAx_A_STARTH                      (0x01FF)


/*====================================================*/
struct __DMA3_A_STARTH_REG
/*====================================================*/
{
    WORD BITFLD_DMAx_A_STARTH                      : 9;
};

#define DMAx_A_STARTH                      (0x01FF)


/*====================================================*/
struct __DMA0_B_STARTH_REG
/*====================================================*/
{
    WORD BITFLD_DMAx_B_STARTH                      : 9;
};

#define DMAx_B_STARTH                      (0x01FF)


/*====================================================*/
struct __DMA1_B_STARTH_REG
/*====================================================*/
{
    WORD BITFLD_DMAx_B_STARTH                      : 9;
};

#define DMAx_B_STARTH                      (0x01FF)


/*====================================================*/
struct __DMA2_B_STARTH_REG
/*====================================================*/
{
    WORD BITFLD_DMAx_B_STARTH                      : 9;
};

#define DMAx_B_STARTH                      (0x01FF)


/*====================================================*/
struct __DMA3_B_STARTH_REG
/*====================================================*/
{
    WORD BITFLD_DMAx_B_STARTH                      : 9;
};

#define DMAx_B_STARTH                      (0x01FF)


/*====================================================*/
struct __DMA0_CTRL_REG
/*====================================================*/
{
    WORD BITFLD_DMA_ON                             : 1;
    WORD BITFLD_BW                                 : 2;
    WORD BITFLD_DINT_MODE                          : 1;
    WORD BITFLD_DREQ_MODE                          : 1;
    WORD BITFLD_BINC                               : 1;
    WORD BITFLD_AINC                               : 1;
    WORD BITFLD_CIRCULAR                           : 1;
    WORD BITFLD_DMA_PRIO                           : 2;
};

#define DMA_ON                             (0x0001)
#define BW                                 (0x0006)
#define DINT_MODE                          (0x0008)
#define DREQ_MODE                          (0x0010)
#define BINC                               (0x0020)
#define AINC                               (0x0040)
#define CIRCULAR                           (0x0080)
#define DMA_PRIO                           (0x0300)


/*====================================================*/
struct __DMA1_CTRL_REG
/*====================================================*/
{
    WORD BITFLD_DMA_ON                             : 1;
    WORD BITFLD_BW                                 : 2;
    WORD BITFLD_DINT_MODE                          : 1;
    WORD BITFLD_DREQ_MODE                          : 1;
    WORD BITFLD_BINC                               : 1;
    WORD BITFLD_AINC                               : 1;
    WORD BITFLD_CIRCULAR                           : 1;
    WORD BITFLD_DMA_PRIO                           : 2;
};

#define DMA_ON                             (0x0001)
#define BW                                 (0x0006)
#define DINT_MODE                          (0x0008)
#define DREQ_MODE                          (0x0010)
#define BINC                               (0x0020)
#define AINC                               (0x0040)
#define CIRCULAR                           (0x0080)
#define DMA_PRIO                           (0x0300)


/*====================================================*/
struct __DMA2_CTRL_REG
/*====================================================*/
{
    WORD BITFLD_DMA_ON                             : 1;
    WORD BITFLD_BW                                 : 2;
    WORD BITFLD_DINT_MODE                          : 1;
    WORD BITFLD_DREQ_MODE                          : 1;
    WORD BITFLD_BINC                               : 1;
    WORD BITFLD_AINC                               : 1;
    WORD BITFLD_CIRCULAR                           : 1;
    WORD BITFLD_DMA_PRIO                           : 2;
};

#define DMA_ON                             (0x0001)
#define BW                                 (0x0006)
#define DINT_MODE                          (0x0008)
#define DREQ_MODE                          (0x0010)
#define BINC                               (0x0020)
#define AINC                               (0x0040)
#define CIRCULAR                           (0x0080)
#define DMA_PRIO                           (0x0300)


/*====================================================*/
struct __DMA3_CTRL_REG
/*====================================================*/
{
    WORD BITFLD_DMA_ON                             : 1;
    WORD BITFLD_BW                                 : 2;
    WORD BITFLD_DINT_MODE                          : 1;
    WORD BITFLD_DREQ_MODE                          : 1;
    WORD BITFLD_BINC                               : 1;
    WORD BITFLD_AINC                               : 1;
    WORD BITFLD_CIRCULAR                           : 1;
    WORD BITFLD_DMA_PRIO                           : 2;
};

#define DMA_ON                             (0x0001)
#define BW                                 (0x0006)
#define DINT_MODE                          (0x0008)
#define DREQ_MODE                          (0x0010)
#define BINC                               (0x0020)
#define AINC                               (0x0040)
#define CIRCULAR                           (0x0080)
#define DMA_PRIO                           (0x0300)


/*====================================================*/
struct __DSP_CLASSD_BUZZOFF_REG
/*====================================================*/
{
    WORD                                           : 15;
    WORD BITFLD_BUZZOFF                            : 1;
};

#define BUZZOFF                            (0x8000)


/*====================================================*/
struct __DSP_CODEC_MIC_GAIN_REG
/*====================================================*/
{
    WORD                                           : 12;
    WORD BITFLD_DSP_MIC_GAIN                       : 4;
};

#define DSP_MIC_GAIN                       (0xF000)


/*====================================================*/
struct __DSP1_CTRL_REG
/*====================================================*/
{
    WORD                                           : 2;
    WORD BITFLD_DSP_EN                             : 1;
    WORD BITFLD_DSP_CLK_EN                         : 1;
    WORD BITFLD_DSP_CR16_INT                       : 1;
    WORD                                           : 3;
    WORD BITFLD_DBG_EN                             : 1;
};

#define DSP_EN                             (0x0004)
#define DSP_CLK_EN                         (0x0008)
#define DSP_CR16_INT                       (0x0010)
#define DBG_EN                             (0x0100)


/*====================================================*/
struct __DSP2_CTRL_REG
/*====================================================*/
{
    WORD                                           : 2;
    WORD BITFLD_DSP_EN                             : 1;
    WORD BITFLD_DSP_CLK_EN                         : 1;
    WORD BITFLD_DSP_CR16_INT                       : 1;
    WORD                                           : 3;
    WORD BITFLD_DBG_EN                             : 1;
};

#define DSP_EN                             (0x0004)
#define DSP_CLK_EN                         (0x0008)
#define DSP_CR16_INT                       (0x0010)
#define DBG_EN                             (0x0100)


/*====================================================*/
struct __DSP1_INT_PRIO1_REG
/*====================================================*/
{
    WORD BITFLD_DSP_INT2_PRIO                      : 3;
    WORD                                           : 1;
    WORD BITFLD_DSP_INT1_PRIO                      : 3;
    WORD                                           : 1;
    WORD BITFLD_DSP_INT0_PRIO                      : 3;
};

#define DSP_INT2_PRIO                      (0x0007)
#define DSP_INT1_PRIO                      (0x0070)
#define DSP_INT0_PRIO                      (0x0700)


/*====================================================*/
struct __DSP2_INT_PRIO1_REG
/*====================================================*/
{
    WORD BITFLD_DSP_INT2_PRIO                      : 3;
    WORD                                           : 1;
    WORD BITFLD_DSP_INT1_PRIO                      : 3;
    WORD                                           : 1;
    WORD BITFLD_DSP_INT0_PRIO                      : 3;
};

#define DSP_INT2_PRIO                      (0x0007)
#define DSP_INT1_PRIO                      (0x0070)
#define DSP_INT0_PRIO                      (0x0700)


/*====================================================*/
struct __DSP1_INT_PRIO2_REG
/*====================================================*/
{
    WORD BITFLD_DSP_INT5_PRIO                      : 3;
    WORD                                           : 1;
    WORD BITFLD_DSP_INT4_PRIO                      : 3;
    WORD                                           : 1;
    WORD BITFLD_DSP_INT3_PRIO                      : 3;
};

#define DSP_INT5_PRIO                      (0x0007)
#define DSP_INT4_PRIO                      (0x0070)
#define DSP_INT3_PRIO                      (0x0700)


/*====================================================*/
struct __DSP2_INT_PRIO2_REG
/*====================================================*/
{
    WORD BITFLD_DSP_INT5_PRIO                      : 3;
    WORD                                           : 1;
    WORD BITFLD_DSP_INT4_PRIO                      : 3;
    WORD                                           : 1;
    WORD BITFLD_DSP_INT3_PRIO                      : 3;
};

#define DSP_INT5_PRIO                      (0x0007)
#define DSP_INT4_PRIO                      (0x0070)
#define DSP_INT3_PRIO                      (0x0700)


/*====================================================*/
struct __DSP1_IRQ_START_REG
/*====================================================*/
{
    WORD                                           : 4;
    WORD BITFLD_DSPx_IRQ_START                     : 12;
};

#define DSPx_IRQ_START                     (0xFFF0)


/*====================================================*/
struct __DSP2_IRQ_START_REG
/*====================================================*/
{
    WORD                                           : 4;
    WORD BITFLD_DSPx_IRQ_START                     : 12;
};

#define DSPx_IRQ_START                     (0xFFF0)


/*====================================================*/
struct __DSP_MAIN_SYNC0_REG
/*====================================================*/
{
    WORD BITFLD_RAMIN0_SYNC                        : 2;
    WORD BITFLD_RAMIN1_SYNC                        : 2;
    WORD BITFLD_RAMIN2_SYNC                        : 2;
    WORD BITFLD_RAMIN3_SYNC                        : 2;
    WORD BITFLD_RAMOUT0_SYNC                       : 2;
    WORD BITFLD_RAMOUT1_SYNC                       : 2;
    WORD BITFLD_RAMOUT2_SYNC                       : 2;
    WORD BITFLD_RAMOUT3_SYNC                       : 2;
};

#define RAMIN0_SYNC                        (0x0003)
#define RAMIN1_SYNC                        (0x000C)
#define RAMIN2_SYNC                        (0x0030)
#define RAMIN3_SYNC                        (0x00C0)
#define RAMOUT0_SYNC                       (0x0300)
#define RAMOUT1_SYNC                       (0x0C00)
#define RAMOUT2_SYNC                       (0x3000)
#define RAMOUT3_SYNC                       (0xC000)


/*====================================================*/
struct __DSP_MAIN_SYNC1_REG
/*====================================================*/
{
    WORD BITFLD_DSP_SYNC0                          : 2;
    WORD BITFLD_DSP_SYNC1                          : 2;
    WORD BITFLD_DSP_SYNC2                          : 2;
    WORD BITFLD_AD_SYNC                            : 2;
    WORD BITFLD_DA_CLASSD_SYNC                     : 2;
    WORD BITFLD_DA_LSR_SYNC                        : 2;
    WORD BITFLD_ADC_SYNC                           : 2;
    WORD BITFLD_PCM_SYNC                           : 2;
};

#define DSP_SYNC0                          (0x0003)
#define DSP_SYNC1                          (0x000C)
#define DSP_SYNC2                          (0x0030)
#define AD_SYNC                            (0x00C0)
#define DA_CLASSD_SYNC                     (0x0300)
#define DA_LSR_SYNC                        (0x0C00)
#define ADC_SYNC                           (0x3000)
#define PCM_SYNC                           (0xC000)


/*====================================================*/
struct __DSP_MAIN_CTRL_REG
/*====================================================*/
{
    WORD BITFLD_DSP_MAIN_PRESET                    : 8;
    WORD BITFLD_DSP_MAIN_CTRL                      : 2;
};

#define DSP_MAIN_PRESET                    (0x00FF)
#define DSP_MAIN_CTRL                      (0x0300)


/*====================================================*/
struct __DSP1_OVERFLOW_REG
/*====================================================*/
{
    WORD BITFLD_INT_OVERFLOW                       : 6;
    WORD BITFLD_WTF_OVERFLOW                       : 1;
    WORD BITFLD_IRQ_OVERFLOW                       : 1;
    WORD BITFLD_M_INT_OVERFLOW                     : 6;
    WORD BITFLD_M_WTF_OVERFLOW                     : 1;
    WORD BITFLD_M_IRQ_OVERFLOW                     : 1;
};

#define INT_OVERFLOW                       (0x003F)
#define WTF_OVERFLOW                       (0x0040)
#define IRQ_OVERFLOW                       (0x0080)
#define M_INT_OVERFLOW                     (0x3F00)
#define M_WTF_OVERFLOW                     (0x4000)
#define M_IRQ_OVERFLOW                     (0x8000)


/*====================================================*/
struct __DSP2_OVERFLOW_REG
/*====================================================*/
{
    WORD BITFLD_INT_OVERFLOW                       : 6;
    WORD BITFLD_WTF_OVERFLOW                       : 1;
    WORD BITFLD_IRQ_OVERFLOW                       : 1;
    WORD BITFLD_M_INT_OVERFLOW                     : 6;
    WORD BITFLD_M_WTF_OVERFLOW                     : 1;
    WORD BITFLD_M_IRQ_OVERFLOW                     : 1;
};

#define INT_OVERFLOW                       (0x003F)
#define WTF_OVERFLOW                       (0x0040)
#define IRQ_OVERFLOW                       (0x0080)
#define M_INT_OVERFLOW                     (0x3F00)
#define M_WTF_OVERFLOW                     (0x4000)
#define M_IRQ_OVERFLOW                     (0x8000)


/*====================================================*/
struct __DSP_PCM_CTRL_REG
/*====================================================*/
{
    WORD BITFLD_PCM_EN                             : 1;
    WORD BITFLD_PCM_MASTER                         : 1;
    WORD BITFLD_DSP_PCM_SYNC                       : 1;
    WORD BITFLD_PCM_FSC0LEN                        : 2;
    WORD BITFLD_PCM_FSC0DEL                        : 1;
    WORD BITFLD_PCM_PPOD                           : 1;
};

#define PCM_EN                             (0x0001)
#define PCM_MASTER                         (0x0002)
#define DSP_PCM_SYNC                       (0x0004)
#define PCM_FSC0LEN                        (0x0018)
#define PCM_FSC0DEL                        (0x0020)
#define PCM_PPOD                           (0x0040)


/*====================================================*/
struct __DSP_VQI_REG
/*====================================================*/
{
    WORD BITFLD_BVQI_ON                            : 4;
};

#define BVQI_ON                            (0x000F)


/*====================================================*/
struct __DSP_ZCROSS1_OUT_REG
/*====================================================*/
{
    WORD BITFLD_DSP_ZCROSSx                        : 1;
};

#define DSP_ZCROSSx                        (0x8000)


/*====================================================*/
struct __DSP_ZCROSS2_OUT_REG
/*====================================================*/
{
    WORD BITFLD_DSP_ZCROSSx                        : 1;
};

#define DSP_ZCROSSx                        (0x8000)


/*====================================================*/
struct __EBI_SDCONR_REG
/*====================================================*/
{
    WORD BITFLD_Unused                             : 3;
    WORD BITFLD_S_BANK_ADDR_WIDTH                  : 2;
    WORD BITFLD_S_ROW_ADDR_WIDTH                   : 4;
    WORD BITFLD_S_COL_ADDR_WIDTH                   : 4;
    WORD BITFLD_S_DATA_WIDTH                       : 2;
};

#define Unused                             (0x0007)
#define S_BANK_ADDR_WIDTH                  (0x0018)
#define S_ROW_ADDR_WIDTH                   (0x01E0)
#define S_COL_ADDR_WIDTH                   (0x1E00)
#define S_DATA_WIDTH                       (0x6000)


/*====================================================*/
struct __EBI_SDTMG0R_REG
/*====================================================*/
{
    WORD BITFLD_CAS_LATENCY                        : 2;
    WORD BITFLD_T_RAS_MIN                          : 4;
    WORD BITFLD_T_RCD                              : 3;
    WORD BITFLD_T_RP                               : 3;
    WORD BITFLD_T_WRSD                             : 2;
    WORD BITFLD_T_RCAR                             : 4;
    WORD BITFLD_T_XSR                              : 4;
    WORD BITFLD_T_RCSD                             : 4;
    WORD BITFLD_CAS_LATENCY_H                      : 1;
    WORD BITFLD_T_XSR_H                            : 5;
};

#define CAS_LATENCY                        (0x0003)
#define T_RAS_MIN                          (0x003C)
#define T_RCD                              (0x01C0)
#define T_RP                               (0x0E00)
#define T_WRSD                             (0x3000)
#define T_RCAR                             (0x3C000)
#define T_XSR                              (0x3C0000)
#define T_RCSD                             (0x3C00000)
#define CAS_LATENCY_H                      (0x4000000)
#define T_XSR_H                            (0xF8000000)


/*====================================================*/
struct __EBI_SDTMG1R_REG
/*====================================================*/
{
    WORD BITFLD_T_INIT                             : 16;
    WORD BITFLD_NUM_INIT_REF                       : 4;
};

#define T_INIT                             (0xFFFF)
#define NUM_INIT_REF                       (0xF0000)


/*====================================================*/
struct __EBI_SDCTLR_REG
/*====================================================*/
{
    WORD BITFLD_INITIALIZE                         : 1;
    WORD BITFLD_SR_OR_DP_MODE                      : 1;
    WORD BITFLD_POWER_DOWN_MODE                    : 1;
    WORD BITFLD_PRECHARGE_ALGO                     : 1;
    WORD BITFLD_FULL_REFRESH_BEFORE_SR             : 1;
    WORD BITFLD_FULL_REFRESH_AFTER_SR              : 1;
    WORD BITFLD_READ_PIPE                          : 3;
    WORD BITFLD_SET_MODE_REG                       : 1;
    WORD                                           : 1;
    WORD BITFLD_SELF_REFRESH_STATUS                : 1;
    WORD BITFLD_NUM_OPEN_BANKS                     : 5;
    WORD BITFLD_S_RD_READY_MODE                    : 1;
};

#define INITIALIZE                         (0x0001)
#define SR_OR_DP_MODE                      (0x0002)
#define POWER_DOWN_MODE                    (0x0004)
#define PRECHARGE_ALGO                     (0x0008)
#define FULL_REFRESH_BEFORE_SR             (0x0010)
#define FULL_REFRESH_AFTER_SR              (0x0020)
#define READ_PIPE                          (0x01C0)
#define SET_MODE_REG                       (0x0200)
#define SELF_REFRESH_STATUS                (0x0800)
#define NUM_OPEN_BANKS                     (0x1F000)
#define S_RD_READY_MODE                    (0x20000)


/*====================================================*/
struct __EBI_SDREFR_REG
/*====================================================*/
{
    WORD BITFLD_T_REF                              : 16;
    WORD BITFLD_READ_PIPE_CLK                      : 3;
    WORD BITFLD_ACS3_IOEXP                         : 1;
    WORD BITFLD_READ_PIPE_MUX                      : 3;
    WORD BITFLD_GPO                                : 1;
    WORD BITFLD_GPI                                : 8;
};

#define T_REF                              (0xFFFF)
#define READ_PIPE_CLK                      (0x70000)
#define ACS3_IOEXP                         (0x80000)
#define READ_PIPE_MUX                      (0x700000)
#define GPO                                (0x800000)
#define GPI                                (0xFF000000)


/*====================================================*/
struct __EBI_ACS0_LOW_REG
/*====================================================*/
{
    WORD                                           : 11;
    WORD BITFLD_EBI_RES                            : 5;
    WORD BITFLD_CS_BASE                            : 16;
};

#define EBI_RES                            (0xF800)
#define CS_BASE                            (0xFFFF0000)


/*====================================================*/
struct __EBI_ACS1_LOW_REG
/*====================================================*/
{
    WORD                                           : 11;
    WORD BITFLD_EBI_RES                            : 5;
    WORD BITFLD_CS_BASE                            : 16;
};

#define EBI_RES                            (0xF800)
#define CS_BASE                            (0xFFFF0000)


/*====================================================*/
struct __EBI_ACS2_LOW_REG
/*====================================================*/
{
    WORD                                           : 11;
    WORD BITFLD_EBI_RES                            : 5;
    WORD BITFLD_CS_BASE                            : 16;
};

#define EBI_RES                            (0xF800)
#define CS_BASE                            (0xFFFF0000)


/*====================================================*/
struct __EBI_ACS3_LOW_REG
/*====================================================*/
{
    WORD                                           : 11;
    WORD BITFLD_EBI_RES                            : 5;
    WORD BITFLD_CS_BASE                            : 16;
};

#define EBI_RES                            (0xF800)
#define CS_BASE                            (0xFFFF0000)


/*====================================================*/
struct __EBI_ACS4_LOW_REG
/*====================================================*/
{
    WORD                                           : 11;
    WORD BITFLD_EBI_RES                            : 5;
    WORD BITFLD_CS_BASE                            : 16;
};

#define EBI_RES                            (0xF800)
#define CS_BASE                            (0xFFFF0000)


/*====================================================*/
struct __EBI_ACS0_CTRL_REG
/*====================================================*/
{
    WORD BITFLD_MEM_SIZE                           : 5;
    WORD BITFLD_MEM_TYPE                           : 3;
    WORD BITFLD_REG_SELECT                         : 3;
};

#define MEM_SIZE                           (0x001F)
#define MEM_TYPE                           (0x00E0)
#define REG_SELECT                         (0x0700)


/*====================================================*/
struct __EBI_ACS1_CTRL_REG
/*====================================================*/
{
    WORD BITFLD_MEM_SIZE                           : 5;
    WORD BITFLD_MEM_TYPE                           : 3;
    WORD BITFLD_REG_SELECT                         : 3;
};

#define MEM_SIZE                           (0x001F)
#define MEM_TYPE                           (0x00E0)
#define REG_SELECT                         (0x0700)


/*====================================================*/
struct __EBI_ACS2_CTRL_REG
/*====================================================*/
{
    WORD BITFLD_MEM_SIZE                           : 5;
    WORD BITFLD_MEM_TYPE                           : 3;
    WORD BITFLD_REG_SELECT                         : 3;
};

#define MEM_SIZE                           (0x001F)
#define MEM_TYPE                           (0x00E0)
#define REG_SELECT                         (0x0700)


/*====================================================*/
struct __EBI_ACS3_CTRL_REG
/*====================================================*/
{
    WORD BITFLD_MEM_SIZE                           : 5;
    WORD BITFLD_MEM_TYPE                           : 3;
    WORD BITFLD_REG_SELECT                         : 3;
};

#define MEM_SIZE                           (0x001F)
#define MEM_TYPE                           (0x00E0)
#define REG_SELECT                         (0x0700)


/*====================================================*/
struct __EBI_ACS4_CTRL_REG
/*====================================================*/
{
    WORD BITFLD_MEM_SIZE                           : 5;
    WORD BITFLD_MEM_TYPE                           : 3;
    WORD BITFLD_REG_SELECT                         : 3;
};

#define MEM_SIZE                           (0x001F)
#define MEM_TYPE                           (0x00E0)
#define REG_SELECT                         (0x0700)


/*====================================================*/
struct __EBI_SMTMGR_SET0_REG
/*====================================================*/
{
    WORD BITFLD_T_RC                               : 6;
    WORD BITFLD_T_AS                               : 2;
    WORD BITFLD_T_WR                               : 2;
    WORD BITFLD_T_WP                               : 6;
    WORD BITFLD_T_BTA                              : 3;
    WORD BITFLD_T_PRC                              : 4;
    WORD BITFLD_PAGE_MODE                          : 1;
    WORD BITFLD_PAGE_SIZE                          : 2;
    WORD BITFLD_READY_MODE                         : 1;
    WORD BITFLD_LOW_FREQ_SYNC                      : 1;
    WORD BITFLD_SM_READ_PIPE                       : 2;
};

#define T_RC                               (0x003F)
#define T_AS                               (0x00C0)
#define T_WR                               (0x0300)
#define T_WP                               (0xFC00)
#define T_BTA                              (0x70000)
#define T_PRC                              (0x780000)
#define PAGE_MODE                          (0x800000)
#define PAGE_SIZE                          (0x3000000)
#define READY_MODE                         (0x4000000)
#define LOW_FREQ_SYNC                      (0x8000000)
#define SM_READ_PIPE                       (0x30000000)


/*====================================================*/
struct __EBI_SMTMGR_SET1_REG
/*====================================================*/
{
    WORD BITFLD_T_RC                               : 6;
    WORD BITFLD_T_AS                               : 2;
    WORD BITFLD_T_WR                               : 2;
    WORD BITFLD_T_WP                               : 6;
    WORD BITFLD_T_BTA                              : 3;
    WORD BITFLD_T_PRC                              : 4;
    WORD BITFLD_PAGE_MODE                          : 1;
    WORD BITFLD_PAGE_SIZE                          : 2;
    WORD BITFLD_READY_MODE                         : 1;
    WORD BITFLD_LOW_FREQ_SYNC                      : 1;
    WORD BITFLD_SM_READ_PIPE                       : 2;
};

#define T_RC                               (0x003F)
#define T_AS                               (0x00C0)
#define T_WR                               (0x0300)
#define T_WP                               (0xFC00)
#define T_BTA                              (0x70000)
#define T_PRC                              (0x780000)
#define PAGE_MODE                          (0x800000)
#define PAGE_SIZE                          (0x3000000)
#define READY_MODE                         (0x4000000)
#define LOW_FREQ_SYNC                      (0x8000000)
#define SM_READ_PIPE                       (0x30000000)


/*====================================================*/
struct __EBI_SMTMGR_SET2_REG
/*====================================================*/
{
    WORD BITFLD_T_RC                               : 6;
    WORD BITFLD_T_AS                               : 2;
    WORD BITFLD_T_WR                               : 2;
    WORD BITFLD_T_WP                               : 6;
    WORD BITFLD_T_BTA                              : 3;
    WORD BITFLD_T_PRC                              : 4;
    WORD BITFLD_PAGE_MODE                          : 1;
    WORD BITFLD_PAGE_SIZE                          : 2;
    WORD BITFLD_READY_MODE                         : 1;
    WORD BITFLD_LOW_FREQ_SYNC                      : 1;
    WORD BITFLD_SM_READ_PIPE                       : 2;
};

#define T_RC                               (0x003F)
#define T_AS                               (0x00C0)
#define T_WR                               (0x0300)
#define T_WP                               (0xFC00)
#define T_BTA                              (0x70000)
#define T_PRC                              (0x780000)
#define PAGE_MODE                          (0x800000)
#define PAGE_SIZE                          (0x3000000)
#define READY_MODE                         (0x4000000)
#define LOW_FREQ_SYNC                      (0x8000000)
#define SM_READ_PIPE                       (0x30000000)


/*====================================================*/
struct __EBI_FLASH_TRPDR_REG
/*====================================================*/
{
    WORD BITFLD_T_RPD                              : 12;
};

#define T_RPD                              (0x0FFF)


/*====================================================*/
struct __EBI_SMCTLR_REG
/*====================================================*/
{
    WORD BITFLD_sSM_RP_N                           : 1;
    WORD BITFLD_WP_N                               : 3;
    WORD                                           : 3;
    WORD BITFLD_SM_DATA_WIDTH_SET0                 : 3;
    WORD BITFLD_SM_DATA_WIDTH_SET1                 : 3;
    WORD BITFLD_SM_DATA_WIDTH_SET2                 : 3;
};

#define sSM_RP_N                           (0x0001)
#define WP_N                               (0x000E)
#define SM_DATA_WIDTH_SET0                 (0x0380)
#define SM_DATA_WIDTH_SET1                 (0x1C00)
#define SM_DATA_WIDTH_SET2                 (0xE000)


/*====================================================*/
struct __INT0_PRIORITY_REG
/*====================================================*/
{
    WORD BITFLD_SPI2_INT_PRIO                      : 3;
    WORD                                           : 1;
    WORD BITFLD_DSP1_INT_PRIO                      : 3;
    WORD                                           : 1;
    WORD BITFLD_DSP2_INT_PRIO                      : 3;
};

#define SPI2_INT_PRIO                      (0x0007)
#define DSP1_INT_PRIO                      (0x0070)
#define DSP2_INT_PRIO                      (0x0700)


/*====================================================*/
struct __INT1_PRIORITY_REG
/*====================================================*/
{
    WORD BITFLD_TIM1_INT_PRIO                      : 3;
    WORD                                           : 1;
    WORD BITFLD_CLK100_INT_PRIO                    : 3;
    WORD                                           : 1;
    WORD BITFLD_DIP_INT_PRIO                       : 3;
    WORD                                           : 1;
    WORD BITFLD_USB_INT_PRIO                       : 3;
};

#define TIM1_INT_PRIO                      (0x0007)
#define CLK100_INT_PRIO                    (0x0070)
#define DIP_INT_PRIO                       (0x0700)
#define USB_INT_PRIO                       (0x7000)


/*====================================================*/
struct __INT2_PRIORITY_REG
/*====================================================*/
{
    WORD BITFLD_UART_RI_INT_PRIO                   : 3;
    WORD                                           : 1;
    WORD BITFLD_UART_TI_INT_PRIO                   : 3;
    WORD                                           : 1;
    WORD BITFLD_SPI1_AD_INT_PRIO                   : 3;
    WORD                                           : 1;
    WORD BITFLD_TIM0_INT_PRIO                      : 3;
};

#define UART_RI_INT_PRIO                   (0x0007)
#define UART_TI_INT_PRIO                   (0x0070)
#define SPI1_AD_INT_PRIO                   (0x0700)
#define TIM0_INT_PRIO                      (0x7000)


/*====================================================*/
struct __INT3_PRIORITY_REG
/*====================================================*/
{
    WORD BITFLD_ACCESS_INT_PRIO                    : 3;
    WORD                                           : 1;
    WORD BITFLD_KEYB_INT_PRIO                      : 3;
    WORD                                           : 1;
    WORD BITFLD_RESERVED_INT_PRIO                  : 3;
    WORD                                           : 1;
    WORD BITFLD_CT_CLASSD_INT_PRIO                 : 3;
};

#define ACCESS_INT_PRIO                    (0x0007)
#define KEYB_INT_PRIO                      (0x0070)
#define RESERVED_INT_PRIO                  (0x0700)
#define CT_CLASSD_INT_PRIO                 (0x7000)


/*====================================================*/
struct __KEY_GP_INT_REG
/*====================================================*/
{
    WORD BITFLD_INT6_CTRL                          : 3;
    WORD BITFLD_INT7_CTRL                          : 3;
    WORD BITFLD_INT8_CTRL                          : 3;
    WORD BITFLD_DREQ1_CTRL                         : 1;
};

#define INT6_CTRL                          (0x0007)
#define INT7_CTRL                          (0x0038)
#define INT8_CTRL                          (0x01C0)
#define DREQ1_CTRL                         (0x0200)


/*====================================================*/
struct __KEY_BOARD_INT_REG
/*====================================================*/
{
    WORD BITFLD_INT0_EN                            : 1;
    WORD BITFLD_INT1_EN                            : 1;
    WORD BITFLD_INT2_EN                            : 1;
    WORD BITFLD_INT3_EN                            : 1;
    WORD BITFLD_INT4_EN                            : 1;
    WORD BITFLD_INT5_EN                            : 1;
    WORD BITFLD_INT_PON_EN                         : 1;
    WORD BITFLD_INT_CHARGE_EN                      : 1;
    WORD BITFLD_CHARGE_CTRL                        : 1;
    WORD BITFLD_PON_CTRL                           : 1;
    WORD BITFLD_KEY_LEVEL                          : 1;
    WORD BITFLD_KEY_REL                            : 1;
};

#define INT0_EN                            (0x0001)
#define INT1_EN                            (0x0002)
#define INT2_EN                            (0x0004)
#define INT3_EN                            (0x0008)
#define INT4_EN                            (0x0010)
#define INT5_EN                            (0x0020)
#define INT_PON_EN                         (0x0040)
#define INT_CHARGE_EN                      (0x0080)
#define CHARGE_CTRL                        (0x0100)
#define PON_CTRL                           (0x0200)
#define KEY_LEVEL                          (0x0400)
#define KEY_REL                            (0x0800)


/*====================================================*/
struct __KEY_DEBOUNCE_REG
/*====================================================*/
{
    WORD BITFLD_DEBOUNCE                           : 6;
    WORD BITFLD_KEY_REPEAT                         : 6;
};

#define DEBOUNCE                           (0x003F)
#define KEY_REPEAT                         (0x0FC0)


/*====================================================*/
struct __KEY_STATUS_REG
/*====================================================*/
{
    WORD BITFLD_KEY_STATUS                         : 4;
};

#define KEY_STATUS                         (0x000F)


/*====================================================*/
struct __PC_START_REG
/*====================================================*/
{
    WORD BITFLD_PC_START10                         : 2;
    WORD BITFLD_PC_START                           : 14;
};

#define PC_START10                         (0x0003)
#define PC_START                           (0xFFFC)


/*====================================================*/
struct __P0_00_MODE_REG
/*====================================================*/
{
    WORD BITFLD_PID                                : 6;
    WORD                                           : 2;
    WORD BITFLD_PUPD                               : 2;
};

#define PID                                (0x003F)
#define PUPD                               (0x0300)


/*====================================================*/
struct __P0_01_MODE_REG
/*====================================================*/
{
    WORD BITFLD_PID                                : 6;
    WORD                                           : 2;
    WORD BITFLD_PUPD                               : 2;
};

#define PID                                (0x003F)
#define PUPD                               (0x0300)


/*====================================================*/
struct __P0_02_MODE_REG
/*====================================================*/
{
    WORD BITFLD_PID                                : 6;
    WORD                                           : 2;
    WORD BITFLD_PUPD                               : 2;
};

#define PID                                (0x003F)
#define PUPD                               (0x0300)


/*====================================================*/
struct __P0_03_MODE_REG
/*====================================================*/
{
    WORD BITFLD_PID                                : 6;
    WORD                                           : 2;
    WORD BITFLD_PUPD                               : 2;
};

#define PID                                (0x003F)
#define PUPD                               (0x0300)


/*====================================================*/
struct __P0_04_MODE_REG
/*====================================================*/
{
    WORD BITFLD_PID                                : 6;
    WORD                                           : 2;
    WORD BITFLD_PUPD                               : 2;
};

#define PID                                (0x003F)
#define PUPD                               (0x0300)


/*====================================================*/
struct __P0_05_MODE_REG
/*====================================================*/
{
    WORD BITFLD_PID                                : 6;
    WORD                                           : 2;
    WORD BITFLD_PUPD                               : 2;
};

#define PID                                (0x003F)
#define PUPD                               (0x0300)


/*====================================================*/
struct __P0_06_MODE_REG
/*====================================================*/
{
    WORD BITFLD_PID                                : 6;
    WORD                                           : 2;
    WORD BITFLD_PUPD                               : 2;
};

#define PID                                (0x003F)
#define PUPD                               (0x0300)


/*====================================================*/
struct __P0_07_MODE_REG
/*====================================================*/
{
    WORD BITFLD_PID                                : 6;
    WORD                                           : 2;
    WORD BITFLD_PUPD                               : 2;
};

#define PID                                (0x003F)
#define PUPD                               (0x0300)


/*====================================================*/
struct __P0_08_MODE_REG
/*====================================================*/
{
    WORD BITFLD_PID                                : 6;
    WORD                                           : 2;
    WORD BITFLD_PUPD                               : 2;
};

#define PID                                (0x003F)
#define PUPD                               (0x0300)


/*====================================================*/
struct __P0_09_MODE_REG
/*====================================================*/
{
    WORD BITFLD_PID                                : 6;
    WORD                                           : 2;
    WORD BITFLD_PUPD                               : 2;
};

#define PID                                (0x003F)
#define PUPD                               (0x0300)


/*====================================================*/
struct __P0_10_MODE_REG
/*====================================================*/
{
    WORD BITFLD_PID                                : 6;
    WORD                                           : 2;
    WORD BITFLD_PUPD                               : 2;
};

#define PID                                (0x003F)
#define PUPD                               (0x0300)


/*====================================================*/
struct __P0_11_MODE_REG
/*====================================================*/
{
    WORD BITFLD_PID                                : 6;
    WORD                                           : 2;
    WORD BITFLD_PUPD                               : 2;
};

#define PID                                (0x003F)
#define PUPD                               (0x0300)


/*====================================================*/
struct __P0_12_MODE_REG
/*====================================================*/
{
    WORD BITFLD_PID                                : 6;
    WORD                                           : 2;
    WORD BITFLD_PUPD                               : 2;
};

#define PID                                (0x003F)
#define PUPD                               (0x0300)


/*====================================================*/
struct __P0_13_MODE_REG
/*====================================================*/
{
    WORD BITFLD_PID                                : 6;
    WORD                                           : 2;
    WORD BITFLD_PUPD                               : 2;
};

#define PID                                (0x003F)
#define PUPD                               (0x0300)


/*====================================================*/
struct __P0_14_MODE_REG
/*====================================================*/
{
    WORD BITFLD_PID                                : 6;
    WORD                                           : 2;
    WORD BITFLD_PUPD                               : 2;
};

#define PID                                (0x003F)
#define PUPD                               (0x0300)


/*====================================================*/
struct __P0_15_MODE_REG
/*====================================================*/
{
    WORD BITFLD_PID                                : 6;
    WORD                                           : 2;
    WORD BITFLD_PUPD                               : 2;
};

#define PID                                (0x003F)
#define PUPD                               (0x0300)


/*====================================================*/
struct __P1_DATA_REG
/*====================================================*/
{
    WORD BITFLD_P1_DATA                            : 14;
};

#define P1_DATA                            (0x3FFF)


/*====================================================*/
struct __P1_SET_DATA_REG
/*====================================================*/
{
    WORD BITFLD_P1_SET                             : 14;
};

#define P1_SET                             (0x3FFF)


/*====================================================*/
struct __P1_RESET_DATA_REG
/*====================================================*/
{
    WORD BITFLD_P1_SET                             : 14;
};

#define P1_SET                             (0x3FFF)


/*====================================================*/
struct __P1_00_MODE_REG
/*====================================================*/
{
    WORD BITFLD_PID                                : 6;
    WORD                                           : 2;
    WORD BITFLD_PUPD                               : 2;
};

#define PID                                (0x003F)
#define PUPD                               (0x0300)


/*====================================================*/
struct __P1_01_MODE_REG
/*====================================================*/
{
    WORD BITFLD_PID                                : 6;
    WORD                                           : 2;
    WORD BITFLD_PUPD                               : 2;
};

#define PID                                (0x003F)
#define PUPD                               (0x0300)


/*====================================================*/
struct __P1_02_MODE_REG
/*====================================================*/
{
    WORD BITFLD_PID                                : 6;
    WORD                                           : 2;
    WORD BITFLD_PUPD                               : 2;
};

#define PID                                (0x003F)
#define PUPD                               (0x0300)


/*====================================================*/
struct __P1_03_MODE_REG
/*====================================================*/
{
    WORD BITFLD_PID                                : 6;
    WORD                                           : 2;
    WORD BITFLD_PUPD                               : 2;
};

#define PID                                (0x003F)
#define PUPD                               (0x0300)


/*====================================================*/
struct __P1_04_MODE_REG
/*====================================================*/
{
    WORD BITFLD_PID                                : 6;
    WORD                                           : 2;
    WORD BITFLD_PUPD                               : 2;
};

#define PID                                (0x003F)
#define PUPD                               (0x0300)


/*====================================================*/
struct __P1_05_MODE_REG
/*====================================================*/
{
    WORD BITFLD_PID                                : 6;
    WORD                                           : 2;
    WORD BITFLD_PUPD                               : 2;
};

#define PID                                (0x003F)
#define PUPD                               (0x0300)


/*====================================================*/
struct __P1_06_MODE_REG
/*====================================================*/
{
    WORD BITFLD_PID                                : 6;
    WORD                                           : 2;
    WORD BITFLD_PUPD                               : 2;
};

#define PID                                (0x003F)
#define PUPD                               (0x0300)


/*====================================================*/
struct __P1_07_MODE_REG
/*====================================================*/
{
    WORD BITFLD_PID                                : 6;
    WORD                                           : 2;
    WORD BITFLD_PUPD                               : 2;
};

#define PID                                (0x003F)
#define PUPD                               (0x0300)


/*====================================================*/
struct __P1_08_MODE_REG
/*====================================================*/
{
    WORD BITFLD_PID                                : 6;
    WORD                                           : 2;
    WORD BITFLD_PUPD                               : 2;
};

#define PID                                (0x003F)
#define PUPD                               (0x0300)


/*====================================================*/
struct __P1_09_MODE_REG
/*====================================================*/
{
    WORD BITFLD_PID                                : 6;
    WORD                                           : 2;
    WORD BITFLD_PUPD                               : 2;
};

#define PID                                (0x003F)
#define PUPD                               (0x0300)


/*====================================================*/
struct __P1_10_MODE_REG
/*====================================================*/
{
    WORD BITFLD_PID                                : 6;
    WORD                                           : 2;
    WORD BITFLD_PUPD                               : 2;
};

#define PID                                (0x003F)
#define PUPD                               (0x0300)


/*====================================================*/
struct __P1_11_MODE_REG
/*====================================================*/
{
    WORD BITFLD_PID                                : 6;
    WORD                                           : 2;
    WORD BITFLD_PUPD                               : 2;
};

#define PID                                (0x003F)
#define PUPD                               (0x0300)


/*====================================================*/
struct __P1_12_MODE_REG
/*====================================================*/
{
    WORD BITFLD_PID                                : 6;
    WORD                                           : 2;
    WORD BITFLD_PUPD                               : 2;
};

#define PID                                (0x003F)
#define PUPD                               (0x0300)


/*====================================================*/
struct __P1_13_MODE_REG
/*====================================================*/
{
    WORD BITFLD_PID                                : 6;
    WORD                                           : 2;
    WORD BITFLD_PUPD                               : 2;
};

#define PID                                (0x003F)
#define PUPD                               (0x0300)


/*====================================================*/
struct __P1_14_MODE_REG
/*====================================================*/
{
    WORD BITFLD_PID                                : 6;
    WORD                                           : 2;
    WORD BITFLD_PUPD                               : 2;
};

#define PID                                (0x003F)
#define PUPD                               (0x0300)


/*====================================================*/
struct __P1_15_MODE_REG
/*====================================================*/
{
    WORD BITFLD_PID                                : 6;
    WORD                                           : 2;
    WORD BITFLD_PUPD                               : 2;
};

#define PID                                (0x003F)
#define PUPD                               (0x0300)


/*====================================================*/
struct __P2_DATA_REG
/*====================================================*/
{
    WORD BITFLD_P2_DATA                            : 12;
};

#define P2_DATA                            (0x0FFF)


/*====================================================*/
struct __P2_SET_DATA_REG
/*====================================================*/
{
    WORD BITFLD_P2_SET                             : 12;
};

#define P2_SET                             (0x0FFF)


/*====================================================*/
struct __P2_RESET_DATA_REG
/*====================================================*/
{
    WORD BITFLD_P2_SET                             : 12;
};

#define P2_SET                             (0x0FFF)


/*====================================================*/
struct __P2_00_MODE_REG
/*====================================================*/
{
    WORD BITFLD_PID                                : 6;
    WORD                                           : 2;
    WORD BITFLD_PUPD                               : 2;
};

#define PID                                (0x003F)
#define PUPD                               (0x0300)


/*====================================================*/
struct __P2_01_MODE_REG
/*====================================================*/
{
    WORD BITFLD_PID                                : 6;
    WORD                                           : 2;
    WORD BITFLD_PUPD                               : 2;
};

#define PID                                (0x003F)
#define PUPD                               (0x0300)


/*====================================================*/
struct __P2_04_MODE_REG
/*====================================================*/
{
    WORD BITFLD_PID                                : 6;
    WORD                                           : 2;
    WORD BITFLD_PUPD                               : 2;
};

#define PID                                (0x003F)
#define PUPD                               (0x0300)


/*====================================================*/
struct __P2_05_MODE_REG
/*====================================================*/
{
    WORD BITFLD_PID                                : 6;
    WORD                                           : 2;
    WORD BITFLD_PUPD                               : 2;
};

#define PID                                (0x003F)
#define PUPD                               (0x0300)


/*====================================================*/
struct __P2_06_MODE_REG
/*====================================================*/
{
    WORD BITFLD_PID                                : 6;
    WORD                                           : 2;
    WORD BITFLD_PUPD                               : 2;
};

#define PID                                (0x003F)
#define PUPD                               (0x0300)


/*====================================================*/
struct __P2_07_MODE_REG
/*====================================================*/
{
    WORD BITFLD_PID                                : 6;
    WORD                                           : 2;
    WORD BITFLD_PUPD                               : 2;
};

#define PID                                (0x003F)
#define PUPD                               (0x0300)


/*====================================================*/
struct __P2_08_MODE_REG
/*====================================================*/
{
    WORD BITFLD_PID                                : 6;
    WORD                                           : 2;
    WORD BITFLD_PUPD                               : 2;
};

#define PID                                (0x003F)
#define PUPD                               (0x0300)


/*====================================================*/
struct __P2_09_MODE_REG
/*====================================================*/
{
    WORD BITFLD_PID                                : 6;
    WORD                                           : 2;
    WORD BITFLD_PUPD                               : 2;
};

#define PID                                (0x003F)
#define PUPD                               (0x0300)


/*====================================================*/
struct __P2_10_MODE_REG
/*====================================================*/
{
    WORD BITFLD_PID                                : 6;
    WORD                                           : 2;
    WORD BITFLD_PUPD                               : 2;
};

#define PID                                (0x003F)
#define PUPD                               (0x0300)


/*====================================================*/
struct __RESET_FREEZE_REG
/*====================================================*/
{
    WORD BITFLD_FRZ_DIP                            : 1;
    WORD BITFLD_FRZ_TIM0                           : 1;
    WORD BITFLD_FRZ_TIM1                           : 1;
    WORD BITFLD_FRZ_WDOG                           : 1;
    WORD BITFLD_FRZ_DMA0                           : 1;
    WORD BITFLD_FRZ_DMA1                           : 1;
    WORD BITFLD_FRZ_DMA2                           : 1;
    WORD BITFLD_FRZ_DMA3                           : 1;
    WORD BITFLD_FRZ_USB                            : 1;
};

#define FRZ_DIP                            (0x0001)
#define FRZ_TIM0                           (0x0002)
#define FRZ_TIM1                           (0x0004)
#define FRZ_WDOG                           (0x0008)
#define FRZ_DMA0                           (0x0010)
#define FRZ_DMA1                           (0x0020)
#define FRZ_DMA2                           (0x0040)
#define FRZ_DMA3                           (0x0080)
#define FRZ_USB                            (0x0100)


/*====================================================*/
struct __RESET_INT_PENDING_REG
/*====================================================*/
{
    WORD BITFLD_ACCESS_INT_PEND                    : 1;
    WORD BITFLD_KEYB_INT_PEND                      : 1;
    WORD BITFLD_RESERVED_INT_PEND                  : 1;
    WORD BITFLD_CT_CLASSD_INT_PEND                 : 1;
    WORD BITFLD_UART_RI_INT_PEND                   : 1;
    WORD BITFLD_UART_TI_INT_PEND                   : 1;
    WORD BITFLD_SPI1_AD_INT_PEND                   : 1;
    WORD BITFLD_TIM0_INT_PEND                      : 1;
    WORD BITFLD_TIM1_INT_PEND                      : 1;
    WORD BITFLD_CLK100_INT_PEND                    : 1;
    WORD BITFLD_DIP_INT_PEND                       : 1;
    WORD BITFLD_USB_INT_PEND                       : 1;
    WORD BITFLD_SPI2_INT_PEND                      : 1;
    WORD BITFLD_DSP1_INT_PEND                      : 1;
    WORD BITFLD_DSP2_INT_PEND                      : 1;
};

#define ACCESS_INT_PEND                    (0x0001)
#define KEYB_INT_PEND                      (0x0002)
#define RESERVED_INT_PEND                  (0x0004)
#define CT_CLASSD_INT_PEND                 (0x0008)
#define UART_RI_INT_PEND                   (0x0010)
#define UART_TI_INT_PEND                   (0x0020)
#define SPI1_AD_INT_PEND                   (0x0040)
#define TIM0_INT_PEND                      (0x0080)
#define TIM1_INT_PEND                      (0x0100)
#define CLK100_INT_PEND                    (0x0200)
#define DIP_INT_PEND                       (0x0400)
#define USB_INT_PEND                       (0x0800)
#define SPI2_INT_PEND                      (0x1000)
#define DSP1_INT_PEND                      (0x2000)
#define DSP2_INT_PEND                      (0x4000)


/*====================================================*/
struct __SET_FREEZE_REG
/*====================================================*/
{
    WORD BITFLD_FRZ_DIP                            : 1;
    WORD BITFLD_FRZ_TIM0                           : 1;
    WORD BITFLD_FRZ_TIM1                           : 1;
    WORD BITFLD_FRZ_WDOG                           : 1;
    WORD BITFLD_FRZ_DMA0                           : 1;
    WORD BITFLD_FRZ_DMA1                           : 1;
    WORD BITFLD_FRZ_DMA2                           : 1;
    WORD BITFLD_FRZ_DMA3                           : 1;
    WORD BITFLD_FRZ_USB                            : 1;
};

#define FRZ_DIP                            (0x0001)
#define FRZ_TIM0                           (0x0002)
#define FRZ_TIM1                           (0x0004)
#define FRZ_WDOG                           (0x0008)
#define FRZ_DMA0                           (0x0010)
#define FRZ_DMA1                           (0x0020)
#define FRZ_DMA2                           (0x0040)
#define FRZ_DMA3                           (0x0080)
#define FRZ_USB                            (0x0100)


/*====================================================*/
struct __SET_INT_PENDING_REG
/*====================================================*/
{
    WORD BITFLD_ACCESS_INT_PEND                    : 1;
    WORD BITFLD_KEYB_INT_PEND                      : 1;
    WORD BITFLD_RESERVED_INT_PEND                  : 1;
    WORD BITFLD_CT_CLASSD_INT_PEND                 : 1;
    WORD BITFLD_UART_RI_INT_PEND                   : 1;
    WORD BITFLD_UART_TI_INT_PEND                   : 1;
    WORD BITFLD_SPI1_AD_INT_PEND                   : 1;
    WORD BITFLD_TIM0_INT_PEND                      : 1;
    WORD BITFLD_TIM1_INT_PEND                      : 1;
    WORD BITFLD_CLK100_INT_PEND                    : 1;
    WORD BITFLD_DIP_INT_PEND                       : 1;
    WORD BITFLD_USB_INT_PEND                       : 1;
    WORD BITFLD_SPI2_INT_PEND                      : 1;
    WORD BITFLD_DSP1_INT_PEND                      : 1;
    WORD BITFLD_DSP2_INT_PEND                      : 1;
};

#define ACCESS_INT_PEND                    (0x0001)
#define KEYB_INT_PEND                      (0x0002)
#define RESERVED_INT_PEND                  (0x0004)
#define CT_CLASSD_INT_PEND                 (0x0008)
#define UART_RI_INT_PEND                   (0x0010)
#define UART_TI_INT_PEND                   (0x0020)
#define SPI1_AD_INT_PEND                   (0x0040)
#define TIM0_INT_PEND                      (0x0080)
#define TIM1_INT_PEND                      (0x0100)
#define CLK100_INT_PEND                    (0x0200)
#define DIP_INT_PEND                       (0x0400)
#define USB_INT_PEND                       (0x0800)
#define SPI2_INT_PEND                      (0x1000)
#define DSP1_INT_PEND                      (0x2000)
#define DSP2_INT_PEND                      (0x4000)


/*====================================================*/
struct __SPI1_CTRL_REG
/*====================================================*/
{
    WORD BITFLD_SPI_ON                             : 1;
    WORD BITFLD_SPI_PHA                            : 1;
    WORD BITFLD_SPI_POL                            : 1;
    WORD BITFLD_SPI_CLK                            : 2;
    WORD BITFLD_SPI_DO                             : 1;
    WORD BITFLD_SPI_SMN                            : 1;
    WORD BITFLD_SPI_WORD                           : 2;
    WORD BITFLD_SPI_RST                            : 1;
    WORD BITFLD_SPI_FORCE_DO                       : 1;
    WORD BITFLD_SPI_TXH                            : 1;
    WORD BITFLD_SPI_DI                             : 1;
    WORD BITFLD_SPI_INT_BIT                        : 1;
    WORD BITFLD_SPI_MINT                           : 1;
    WORD BITFLD_SPI_EN_CTRL                        : 1;
};

#define SPI_ON                             (0x0001)
#define SPI_PHA                            (0x0002)
#define SPI_POL                            (0x0004)
#define SPI_CLK                            (0x0018)
#define SPI_DO                             (0x0020)
#define SPI_SMN                            (0x0040)
#define SPI_WORD                           (0x0180)
#define SPI_RST                            (0x0200)
#define SPI_FORCE_DO                       (0x0400)
#define SPI_TXH                            (0x0800)
#define SPI_DI                             (0x1000)
#define SPI_INT_BIT                        (0x2000)
#define SPI_MINT                           (0x4000)
#define SPI_EN_CTRL                        (0x8000)


/*====================================================*/
struct __SPI2_CTRL_REG
/*====================================================*/
{
    WORD BITFLD_SPI_ON                             : 1;
    WORD BITFLD_SPI_PHA                            : 1;
    WORD BITFLD_SPI_POL                            : 1;
    WORD BITFLD_SPI_CLK                            : 2;
    WORD BITFLD_SPI_DO                             : 1;
    WORD BITFLD_SPI_SMN                            : 1;
    WORD BITFLD_SPI_WORD                           : 2;
    WORD BITFLD_SPI_RST                            : 1;
    WORD BITFLD_SPI_FORCE_DO                       : 1;
    WORD BITFLD_SPI_TXH                            : 1;
    WORD BITFLD_SPI_DI                             : 1;
    WORD BITFLD_SPI_INT_BIT                        : 1;
    WORD BITFLD_SPI_MINT                           : 1;
    WORD BITFLD_SPI_EN_CTRL                        : 1;
};

#define SPI_ON                             (0x0001)
#define SPI_PHA                            (0x0002)
#define SPI_POL                            (0x0004)
#define SPI_CLK                            (0x0018)
#define SPI_DO                             (0x0020)
#define SPI_SMN                            (0x0040)
#define SPI_WORD                           (0x0180)
#define SPI_RST                            (0x0200)
#define SPI_FORCE_DO                       (0x0400)
#define SPI_TXH                            (0x0800)
#define SPI_DI                             (0x1000)
#define SPI_INT_BIT                        (0x2000)
#define SPI_MINT                           (0x4000)
#define SPI_EN_CTRL                        (0x8000)


/*====================================================*/
struct __TIMER_CTRL_REG
/*====================================================*/
{
    WORD BITFLD_TIM0_CTRL                          : 1;
    WORD BITFLD_TIM1_CTRL                          : 1;
    WORD BITFLD_CLK_CTRL0                          : 1;
    WORD BITFLD_CLK_CTRL1                          : 1;
    WORD BITFLD_WDOG_CTRL                          : 1;
    WORD BITFLD_TIM1_MODE                          : 1;
    WORD BITFLD_CLK_DIV8                           : 1;
    WORD BITFLD_TIM2_CTRL                          : 1;
};

#define TIM0_CTRL                          (0x0001)
#define TIM1_CTRL                          (0x0002)
#define CLK_CTRL0                          (0x0004)
#define CLK_CTRL1                          (0x0008)
#define WDOG_CTRL                          (0x0010)
#define TIM1_MODE                          (0x0020)
#define CLK_DIV8                           (0x0040)
#define TIM2_CTRL                          (0x0080)


/*====================================================*/
struct __TEST_ENV_REG
/*====================================================*/
{
    WORD BITFLD_BOOT                               : 1;
    WORD BITFLD_AD3_1                              : 3;
    WORD BITFLD_ENV_SDI                            : 1;
    WORD BITFLD_ENV_REG7_5                         : 3;
};

#define BOOT                               (0x0001)
#define AD3_1                              (0x000E)
#define ENV_SDI                            (0x0010)
#define ENV_REG7_5                         (0x00E0)


/*====================================================*/
struct __TONE_CTRL1_REG
/*====================================================*/
{
    WORD BITFLD_GATESRC1                           : 2;
    WORD BITFLD_CLKSRC1                            : 2;
    WORD BITFLD_TIMER_RELOAD1                      : 4;
    WORD BITFLD_CT1_INT                            : 1;
    WORD BITFLD_MCT1_INT                           : 1;
    WORD BITFLD_GATE_EDGE1                         : 1;
};

#define GATESRC1                           (0x0003)
#define CLKSRC1                            (0x000C)
#define TIMER_RELOAD1                      (0x00F0)
#define CT1_INT                            (0x0100)
#define MCT1_INT                           (0x0200)
#define GATE_EDGE1                         (0x0400)


/*====================================================*/
struct __TONE_CTRL2_REG
/*====================================================*/
{
    WORD BITFLD_GATESRC2                           : 2;
    WORD BITFLD_CLKSRC2                            : 2;
    WORD BITFLD_TIMER_RELOAD2                      : 4;
    WORD BITFLD_CT2_INT                            : 1;
    WORD BITFLD_MCT2_INT                           : 1;
    WORD BITFLD_GATE_EDGE2                         : 1;
};

#define GATESRC2                           (0x0003)
#define CLKSRC2                            (0x000C)
#define TIMER_RELOAD2                      (0x00F0)
#define CT2_INT                            (0x0100)
#define MCT2_INT                           (0x0200)
#define GATE_EDGE2                         (0x0400)


/*====================================================*/
struct __UART_CTRL_REG
/*====================================================*/
{
    WORD BITFLD_UART_REN                           : 1;
    WORD BITFLD_UART_TEN                           : 1;
    WORD BITFLD_BAUDRATE                           : 3;
    WORD BITFLD_TI                                 : 1;
    WORD BITFLD_RI                                 : 1;
    WORD BITFLD_UART_MODE                          : 1;
    WORD BITFLD_IRDA_EN                            : 1;
    WORD BITFLD_INV_URX                            : 1;
    WORD BITFLD_INV_UTX                            : 1;
};

#define UART_REN                           (0x0001)
#define UART_TEN                           (0x0002)
#define BAUDRATE                           (0x001C)
#define TI                                 (0x0020)
#define RI                                 (0x0040)
#define UART_MODE                          (0x0080)
#define IRDA_EN                            (0x0100)
#define INV_URX                            (0x0200)
#define INV_UTX                            (0x0400)


/*====================================================*/
struct __UART_ERROR_REG
/*====================================================*/
{
    WORD BITFLD_PAR_STATUS                         : 1;
    WORD BITFLD_DMA_PARITY_ERROR                   : 1;
};

#define PAR_STATUS                         (0x0001)
#define DMA_PARITY_ERROR                   (0x0002)


/*====================================================*/
struct __USB_ALTEV_REG
/*====================================================*/
{
    WORD                                           : 3;
    WORD BITFLD_USB_EOP                            : 1;
    WORD BITFLD_USB_SD3                            : 1;
    WORD BITFLD_USB_SD5                            : 1;
    WORD BITFLD_USB_RESET                          : 1;
    WORD BITFLD_USB_RESUME                         : 1;
};

#define USB_EOP                            (0x0008)
#define USB_SD3                            (0x0010)
#define USB_SD5                            (0x0020)
#define USB_RESET                          (0x0040)
#define USB_RESUME                         (0x0080)


/*====================================================*/
struct __USB_ALTMSK_REG
/*====================================================*/
{
    WORD                                           : 3;
    WORD BITFLD_USB_M_EOP                          : 1;
    WORD BITFLD_USB_M_SD3                          : 1;
    WORD BITFLD_USB_M_SD5                          : 1;
    WORD BITFLD_USB_M_RESET                        : 1;
    WORD BITFLD_USB_M_RESUME                       : 1;
};

#define USB_M_EOP                          (0x0008)
#define USB_M_SD3                          (0x0010)
#define USB_M_SD5                          (0x0020)
#define USB_M_RESET                        (0x0040)
#define USB_M_RESUME                       (0x0080)


/*====================================================*/
struct __USB_EP0_NAK_REG
/*====================================================*/
{
    WORD BITFLD_USB_EP0_INNAK                      : 1;
    WORD BITFLD_USB_EP0_OUTNAK                     : 1;
};

#define USB_EP0_INNAK                      (0x0001)
#define USB_EP0_OUTNAK                     (0x0002)


/*====================================================*/
struct __USB_EPC0_REG
/*====================================================*/
{
    WORD BITFLD_USB_EP                             : 4;
    WORD                                           : 2;
    WORD BITFLD_USB_DEF                            : 1;
    WORD BITFLD_USB_STALL                          : 1;
};

#define USB_EP                             (0x000F)
#define USB_DEF                            (0x0040)
#define USB_STALL                          (0x0080)


/*====================================================*/
struct __USB_EPC1_REG
/*====================================================*/
{
    WORD BITFLD_USB_EP                             : 4;
    WORD BITFLD_USB_EP_EN                          : 1;
    WORD BITFLD_USB_ISO                            : 1;
    WORD                                           : 1;
    WORD BITFLD_USB_STALL                          : 1;
};

#define USB_EP                             (0x000F)
#define USB_EP_EN                          (0x0010)
#define USB_ISO                            (0x0020)
#define USB_STALL                          (0x0080)


/*====================================================*/
struct __USB_EPC2_REG
/*====================================================*/
{
    WORD BITFLD_USB_EP                             : 4;
    WORD BITFLD_USB_EP_EN                          : 1;
    WORD BITFLD_USB_ISO                            : 1;
    WORD                                           : 1;
    WORD BITFLD_USB_STALL                          : 1;
};

#define USB_EP                             (0x000F)
#define USB_EP_EN                          (0x0010)
#define USB_ISO                            (0x0020)
#define USB_STALL                          (0x0080)


/*====================================================*/
struct __USB_EPC3_REG
/*====================================================*/
{
    WORD BITFLD_USB_EP                             : 4;
    WORD BITFLD_USB_EP_EN                          : 1;
    WORD BITFLD_USB_ISO                            : 1;
    WORD                                           : 1;
    WORD BITFLD_USB_STALL                          : 1;
};

#define USB_EP                             (0x000F)
#define USB_EP_EN                          (0x0010)
#define USB_ISO                            (0x0020)
#define USB_STALL                          (0x0080)


/*====================================================*/
struct __USB_EPC4_REG
/*====================================================*/
{
    WORD BITFLD_USB_EP                             : 4;
    WORD BITFLD_USB_EP_EN                          : 1;
    WORD BITFLD_USB_ISO                            : 1;
    WORD                                           : 1;
    WORD BITFLD_USB_STALL                          : 1;
};

#define USB_EP                             (0x000F)
#define USB_EP_EN                          (0x0010)
#define USB_ISO                            (0x0020)
#define USB_STALL                          (0x0080)


/*====================================================*/
struct __USB_EPC5_REG
/*====================================================*/
{
    WORD BITFLD_USB_EP                             : 4;
    WORD BITFLD_USB_EP_EN                          : 1;
    WORD BITFLD_USB_ISO                            : 1;
    WORD                                           : 1;
    WORD BITFLD_USB_STALL                          : 1;
};

#define USB_EP                             (0x000F)
#define USB_EP_EN                          (0x0010)
#define USB_ISO                            (0x0020)
#define USB_STALL                          (0x0080)


/*====================================================*/
struct __USB_EPC6_REG
/*====================================================*/
{
    WORD BITFLD_USB_EP                             : 4;
    WORD BITFLD_USB_EP_EN                          : 1;
    WORD BITFLD_USB_ISO                            : 1;
    WORD                                           : 1;
    WORD BITFLD_USB_STALL                          : 1;
};

#define USB_EP                             (0x000F)
#define USB_EP_EN                          (0x0010)
#define USB_ISO                            (0x0020)
#define USB_STALL                          (0x0080)


/*====================================================*/
struct __USB_FAR_REG
/*====================================================*/
{
    WORD BITFLD_USB_AD                             : 7;
    WORD BITFLD_USB_AD_EN                          : 1;
};

#define USB_AD                             (0x007F)
#define USB_AD_EN                          (0x0080)


/*====================================================*/
struct __USB_FNH_REG
/*====================================================*/
{
    WORD BITFLD_USB_FN_10_8                        : 3;
    WORD                                           : 2;
    WORD BITFLD_USB_RFC                            : 1;
    WORD BITFLD_USB_UL                             : 1;
    WORD BITFLD_USB_MF                             : 1;
};

#define USB_FN_10_8                        (0x0007)
#define USB_RFC                            (0x0020)
#define USB_UL                             (0x0040)
#define USB_MF                             (0x0080)


/*====================================================*/
struct __USB_FWEV_REG
/*====================================================*/
{
    WORD BITFLD_USB_TXWARN31                       : 3;
    WORD                                           : 1;
    WORD BITFLD_USB_RXWARN31                       : 3;
};

#define USB_TXWARN31                       (0x0007)
#define USB_RXWARN31                       (0x0070)


/*====================================================*/
struct __USB_FWMSK_REG
/*====================================================*/
{
    WORD BITFLD_USB_M_TXWARN31                     : 4;
    WORD                                           : 1;
    WORD BITFLD_USB_M_RXWARN31                     : 3;
};

#define USB_M_TXWARN31                     (0x000F)
#define USB_M_RXWARN31                     (0x0070)


/*====================================================*/
struct __USB_MCTRL_REG
/*====================================================*/
{
    WORD BITFLD_USBEN                              : 1;
    WORD BITFLD_USB_DBG                            : 1;
    WORD                                           : 1;
    WORD BITFLD_USB_NAT                            : 1;
    WORD BITFLD_LSMODE                             : 1;
};

#define USBEN                              (0x0001)
#define USB_DBG                            (0x0002)
#define USB_NAT                            (0x0008)
#define LSMODE                             (0x0010)


/*====================================================*/
struct __USB_MAEV_REG
/*====================================================*/
{
    WORD BITFLD_USB_WARN                           : 1;
    WORD BITFLD_USB_ALT                            : 1;
    WORD BITFLD_USB_TX_EV                          : 1;
    WORD BITFLD_USB_FRAME                          : 1;
    WORD BITFLD_USB_NAK                            : 1;
    WORD BITFLD_USB_ULD                            : 1;
    WORD BITFLD_USB_RX_EV                          : 1;
    WORD BITFLD_USB_INTR                           : 1;
    WORD BITFLD_USB_EP0_TX                         : 1;
    WORD BITFLD_USB_EP0_RX                         : 1;
    WORD BITFLD_USB_EP0_NAK                        : 1;
};

#define USB_WARN                           (0x0001)
#define USB_ALT                            (0x0002)
#define USB_TX_EV                          (0x0004)
#define USB_FRAME                          (0x0008)
#define USB_NAK                            (0x0010)
#define USB_ULD                            (0x0020)
#define USB_RX_EV                          (0x0040)
#define USB_INTR                           (0x0080)
#define USB_EP0_TX                         (0x0100)
#define USB_EP0_RX                         (0x0200)
#define USB_EP0_NAK                        (0x0400)


/*====================================================*/
struct __USB_MAMSK_REG
/*====================================================*/
{
    WORD BITFLD_USB_M_WARN                         : 1;
    WORD BITFLD_USB_M_ALT                          : 1;
    WORD BITFLD_USB_M_TX_EV                        : 1;
    WORD BITFLD_USB_M_FRAME                        : 1;
    WORD BITFLD_USB_M_NAK                          : 1;
    WORD BITFLD_USB_M_ULD                          : 1;
    WORD BITFLD_USB_M_RX_EV                        : 1;
    WORD BITFLD_USB_M_INTR                         : 1;
    WORD BITFLD_USB_M_EP0_TX                       : 1;
    WORD BITFLD_USB_M_EP0_RX                       : 1;
    WORD BITFLD_USB_M_EP0_NAK                      : 1;
};

#define USB_M_WARN                         (0x0001)
#define USB_M_ALT                          (0x0002)
#define USB_M_TX_EV                        (0x0004)
#define USB_M_FRAME                        (0x0008)
#define USB_M_NAK                          (0x0010)
#define USB_M_ULD                          (0x0020)
#define USB_M_RX_EV                        (0x0040)
#define USB_M_INTR                         (0x0080)
#define USB_M_EP0_TX                       (0x0100)
#define USB_M_EP0_RX                       (0x0200)
#define USB_M_EP0_NAK                      (0x0400)


/*====================================================*/
struct __USB_NFSR_REG
/*====================================================*/
{
    WORD BITFLD_USB_NFS                            : 2;
};

#define USB_NFS                            (0x0003)


/*====================================================*/
struct __USB_NAKEV_REG
/*====================================================*/
{
    WORD BITFLD_USB_IN31                           : 3;
    WORD                                           : 1;
    WORD BITFLD_USB_OUT31                          : 3;
};

#define USB_IN31                           (0x0007)
#define USB_OUT31                          (0x0070)


/*====================================================*/
struct __USB_NAKMSK_REG
/*====================================================*/
{
    WORD BITFLD_USB_M_IN31                         : 3;
    WORD                                           : 1;
    WORD BITFLD_USB_M_OUT31                        : 3;
};

#define USB_M_IN31                         (0x0007)
#define USB_M_OUT31                        (0x0070)


/*====================================================*/
struct __USB_RXC0_REG
/*====================================================*/
{
    WORD BITFLD_USB_RX_EN                          : 1;
    WORD BITFLD_USB_IGN_OUT                        : 1;
    WORD BITFLD_USB_IGN_SETUP                      : 1;
    WORD BITFLD_USB_FLUSH                          : 1;
};

#define USB_RX_EN                          (0x0001)
#define USB_IGN_OUT                        (0x0002)
#define USB_IGN_SETUP                      (0x0004)
#define USB_FLUSH                          (0x0008)


/*====================================================*/
struct __USB_RXC1_REG
/*====================================================*/
{
    WORD BITFLD_USB_RX_EN                          : 1;
    WORD                                           : 1;
    WORD BITFLD_USB_IGN_SETUP                      : 1;
    WORD BITFLD_USB_FLUSH                          : 1;
    WORD                                           : 1;
    WORD BITFLD_USB_RFWL                           : 2;
};

#define USB_RX_EN                          (0x0001)
#define USB_IGN_SETUP                      (0x0004)
#define USB_FLUSH                          (0x0008)
#define USB_RFWL                           (0x0060)


/*====================================================*/
struct __USB_RXC2_REG
/*====================================================*/
{
    WORD BITFLD_USB_RX_EN                          : 1;
    WORD                                           : 1;
    WORD BITFLD_USB_IGN_SETUP                      : 1;
    WORD BITFLD_USB_FLUSH                          : 1;
    WORD                                           : 1;
    WORD BITFLD_USB_RFWL                           : 2;
};

#define USB_RX_EN                          (0x0001)
#define USB_IGN_SETUP                      (0x0004)
#define USB_FLUSH                          (0x0008)
#define USB_RFWL                           (0x0060)


/*====================================================*/
struct __USB_RXC3_REG
/*====================================================*/
{
    WORD BITFLD_USB_RX_EN                          : 1;
    WORD                                           : 1;
    WORD BITFLD_USB_IGN_SETUP                      : 1;
    WORD BITFLD_USB_FLUSH                          : 1;
    WORD                                           : 1;
    WORD BITFLD_USB_RFWL                           : 2;
};

#define USB_RX_EN                          (0x0001)
#define USB_IGN_SETUP                      (0x0004)
#define USB_FLUSH                          (0x0008)
#define USB_RFWL                           (0x0060)


/*====================================================*/
struct __USB_RXS0_REG
/*====================================================*/
{
    WORD BITFLD_USB_RCOUNT                         : 4;
    WORD BITFLD_USB_RX_LAST                        : 1;
    WORD BITFLD_USB_TOGGLE_RX0                     : 1;
    WORD BITFLD_USB_SETUP                          : 1;
};

#define USB_RCOUNT                         (0x000F)
#define USB_RX_LAST                        (0x0010)
#define USB_TOGGLE_RX0                     (0x0020)
#define USB_SETUP                          (0x0040)


/*====================================================*/
struct __USB_RXS1_REG
/*====================================================*/
{
    WORD BITFLD_USB_RCOUNT                         : 4;
    WORD BITFLD_USB_RX_LAST                        : 1;
    WORD BITFLD_USB_TOGGLE_RX                      : 1;
    WORD BITFLD_USB_SETUP                          : 1;
    WORD BITFLD_USB_RX_ERR                         : 1;
};

#define USB_RCOUNT                         (0x000F)
#define USB_RX_LAST                        (0x0010)
#define USB_TOGGLE_RX                      (0x0020)
#define USB_SETUP                          (0x0040)
#define USB_RX_ERR                         (0x0080)


/*====================================================*/
struct __USB_RXS2_REG
/*====================================================*/
{
    WORD BITFLD_USB_RCOUNT                         : 4;
    WORD BITFLD_USB_RX_LAST                        : 1;
    WORD BITFLD_USB_TOGGLE_RX                      : 1;
    WORD BITFLD_USB_SETUP                          : 1;
    WORD BITFLD_USB_RX_ERR                         : 1;
};

#define USB_RCOUNT                         (0x000F)
#define USB_RX_LAST                        (0x0010)
#define USB_TOGGLE_RX                      (0x0020)
#define USB_SETUP                          (0x0040)
#define USB_RX_ERR                         (0x0080)


/*====================================================*/
struct __USB_RXS3_REG
/*====================================================*/
{
    WORD BITFLD_USB_RCOUNT                         : 4;
    WORD BITFLD_USB_RX_LAST                        : 1;
    WORD BITFLD_USB_TOGGLE_RX                      : 1;
    WORD BITFLD_USB_SETUP                          : 1;
    WORD BITFLD_USB_RX_ERR                         : 1;
};

#define USB_RCOUNT                         (0x000F)
#define USB_RX_LAST                        (0x0010)
#define USB_TOGGLE_RX                      (0x0020)
#define USB_SETUP                          (0x0040)
#define USB_RX_ERR                         (0x0080)


/*====================================================*/
struct __USB_RXEV_REG
/*====================================================*/
{
    WORD BITFLD_USB_RXFIFO31                       : 3;
    WORD                                           : 1;
    WORD BITFLD_USB_RXOVRRN31                      : 3;
};

#define USB_RXFIFO31                       (0x0007)
#define USB_RXOVRRN31                      (0x0070)


/*====================================================*/
struct __USB_RXMSK_REG
/*====================================================*/
{
    WORD BITFLD_USB_M_RXFIFO31                     : 3;
    WORD                                           : 1;
    WORD BITFLD_USB_M_RXOVRRN31                    : 3;
};

#define USB_M_RXFIFO31                     (0x0007)
#define USB_M_RXOVRRN31                    (0x0070)


/*====================================================*/
struct __USB_TCR_REG
/*====================================================*/
{
    WORD BITFLD_USB_CADJ                           : 5;
    WORD BITFLD_USB_VADJ                           : 3;
};

#define USB_CADJ                           (0x001F)
#define USB_VADJ                           (0x00E0)


/*====================================================*/
struct __USB_TXC0_REG
/*====================================================*/
{
    WORD BITFLD_USB_TX_EN                          : 1;
    WORD                                           : 1;
    WORD BITFLD_USB_TOGGLE_TX0                     : 1;
    WORD BITFLD_USB_FLUSH                          : 1;
    WORD BITFLD_USB_IGN_IN                         : 1;
};

#define USB_TX_EN                          (0x0001)
#define USB_TOGGLE_TX0                     (0x0004)
#define USB_FLUSH                          (0x0008)
#define USB_IGN_IN                         (0x0010)


/*====================================================*/
struct __USB_TXEV_REG
/*====================================================*/
{
    WORD BITFLD_USB_TXFIFO31                       : 3;
    WORD                                           : 1;
    WORD BITFLD_USB_TXUDRRN31                      : 3;
};

#define USB_TXFIFO31                       (0x0007)
#define USB_TXUDRRN31                      (0x0070)


/*====================================================*/
struct __USB_TXMSK_REG
/*====================================================*/
{
    WORD BITFLD_USB_M_TXFIFO31                     : 3;
    WORD                                           : 1;
    WORD BITFLD_USB_M_TXUDRRN31                    : 3;
};

#define USB_M_TXFIFO31                     (0x0007)
#define USB_M_TXUDRRN31                    (0x0070)


/*====================================================*/
struct __USB_TXC1_REG
/*====================================================*/
{
    WORD BITFLD_USB_TX_EN                          : 1;
    WORD BITFLD_USB_LAST                           : 1;
    WORD BITFLD_USB_TOGGLE_TX                      : 1;
    WORD BITFLD_USB_FLUSH                          : 1;
    WORD BITFLD_USB_RFF                            : 1;
    WORD BITFLD_USB_TFWL                           : 2;
    WORD BITFLD_USB_IGN_ISOMSK                     : 1;
};

#define USB_TX_EN                          (0x0001)
#define USB_LAST                           (0x0002)
#define USB_TOGGLE_TX                      (0x0004)
#define USB_FLUSH                          (0x0008)
#define USB_RFF                            (0x0010)
#define USB_TFWL                           (0x0060)
#define USB_IGN_ISOMSK                     (0x0080)


/*====================================================*/
struct __USB_TXC2_REG
/*====================================================*/
{
    WORD BITFLD_USB_TX_EN                          : 1;
    WORD BITFLD_USB_LAST                           : 1;
    WORD BITFLD_USB_TOGGLE_TX                      : 1;
    WORD BITFLD_USB_FLUSH                          : 1;
    WORD BITFLD_USB_RFF                            : 1;
    WORD BITFLD_USB_TFWL                           : 2;
    WORD BITFLD_USB_IGN_ISOMSK                     : 1;
};

#define USB_TX_EN                          (0x0001)
#define USB_LAST                           (0x0002)
#define USB_TOGGLE_TX                      (0x0004)
#define USB_FLUSH                          (0x0008)
#define USB_RFF                            (0x0010)
#define USB_TFWL                           (0x0060)
#define USB_IGN_ISOMSK                     (0x0080)


/*====================================================*/
struct __USB_TXC3_REG
/*====================================================*/
{
    WORD BITFLD_USB_TX_EN                          : 1;
    WORD BITFLD_USB_LAST                           : 1;
    WORD BITFLD_USB_TOGGLE_TX                      : 1;
    WORD BITFLD_USB_FLUSH                          : 1;
    WORD BITFLD_USB_RFF                            : 1;
    WORD BITFLD_USB_TFWL                           : 2;
    WORD BITFLD_USB_IGN_ISOMSK                     : 1;
};

#define USB_TX_EN                          (0x0001)
#define USB_LAST                           (0x0002)
#define USB_TOGGLE_TX                      (0x0004)
#define USB_FLUSH                          (0x0008)
#define USB_RFF                            (0x0010)
#define USB_TFWL                           (0x0060)
#define USB_IGN_ISOMSK                     (0x0080)


/*====================================================*/
struct __USB_TXS0_REG
/*====================================================*/
{
    WORD BITFLD_USB_TCOUNT                         : 5;
    WORD BITFLD_USB_TX_DONE                        : 1;
    WORD BITFLD_USB_ACK_STAT                       : 1;
};

#define USB_TCOUNT                         (0x001F)
#define USB_TX_DONE                        (0x0020)
#define USB_ACK_STAT                       (0x0040)


/*====================================================*/
struct __USB_TXS1_REG
/*====================================================*/
{
    WORD BITFLD_USB_TCOUNT                         : 5;
    WORD BITFLD_USB_TX_DONE                        : 1;
    WORD BITFLD_USB_ACK_STAT                       : 1;
    WORD BITFLD_USB_TX_URUN                        : 1;
};

#define USB_TCOUNT                         (0x001F)
#define USB_TX_DONE                        (0x0020)
#define USB_ACK_STAT                       (0x0040)
#define USB_TX_URUN                        (0x0080)


/*====================================================*/
struct __USB_TXS2_REG
/*====================================================*/
{
    WORD BITFLD_USB_TCOUNT                         : 5;
    WORD BITFLD_USB_TX_DONE                        : 1;
    WORD BITFLD_USB_ACK_STAT                       : 1;
    WORD BITFLD_USB_TX_URUN                        : 1;
};

#define USB_TCOUNT                         (0x001F)
#define USB_TX_DONE                        (0x0020)
#define USB_ACK_STAT                       (0x0040)
#define USB_TX_URUN                        (0x0080)


/*====================================================*/
struct __USB_TXS3_REG
/*====================================================*/
{
    WORD BITFLD_USB_TCOUNT                         : 5;
    WORD BITFLD_USB_TX_DONE                        : 1;
    WORD BITFLD_USB_ACK_STAT                       : 1;
    WORD BITFLD_USB_TX_URUN                        : 1;
};

#define USB_TCOUNT                         (0x001F)
#define USB_TX_DONE                        (0x0020)
#define USB_ACK_STAT                       (0x0040)
#define USB_TX_URUN                        (0x0080)


/*====================================================*/
struct __USB_UTR_REG
/*====================================================*/
{
    WORD BITFLD_USB_UTR_RES                        : 5;
    WORD BITFLD_USB_SF                             : 1;
    WORD BITFLD_USB_NCRC                           : 1;
    WORD BITFLD_USB_DIAG                           : 1;
};

#define USB_UTR_RES                        (0x001F)
#define USB_SF                             (0x0020)
#define USB_NCRC                           (0x0040)
#define USB_DIAG                           (0x0080)


/*====================================================*/
struct __USB_UX20CDR_REG
/*====================================================*/
{
    WORD BITFLD_RPU_SSPROTEN                       : 1;
    WORD BITFLD_RPU_RCDELAY                        : 1;
    WORD BITFLD_RPU_TEST_SW1DM                     : 1;
    WORD                                           : 1;
    WORD BITFLD_RPU_TEST_EN                        : 1;
    WORD BITFLD_RPU_TEST_SW1                       : 1;
    WORD BITFLD_RPU_TEST_SW2                       : 1;
    WORD BITFLD_RPU_TEST7                          : 1;
};

#define RPU_SSPROTEN                       (0x0001)
#define RPU_RCDELAY                        (0x0002)
#define RPU_TEST_SW1DM                     (0x0004)
#define RPU_TEST_EN                        (0x0010)
#define RPU_TEST_SW1                       (0x0020)
#define RPU_TEST_SW2                       (0x0040)
#define RPU_TEST7                          (0x0080)


/*====================================================*/
struct __USB_XCVDIAG_REG
/*====================================================*/
{
    WORD BITFLD_USB_XCV_TEST                       : 1;
    WORD BITFLD_USB_XCV_TXp                        : 1;
    WORD BITFLD_USB_XCV_TXn                        : 1;
    WORD BITFLD_USB_XCV_TXEN                       : 1;
    WORD                                           : 1;
    WORD BITFLD_USB_RCV                            : 1;
    WORD BITFLD_USB_VMIN                           : 1;
    WORD BITFLD_USB_VPIN                           : 1;
};

#define USB_XCV_TEST                       (0x0001)
#define USB_XCV_TXp                        (0x0002)
#define USB_XCV_TXn                        (0x0004)
#define USB_XCV_TXEN                       (0x0008)
#define USB_RCV                            (0x0020)
#define USB_VMIN                           (0x0040)
#define USB_VPIN                           (0x0080)


#ifdef __IAR_SYSTEMS_ICC__

/*
 * Extern declarations of all peripheral registers above 16 Mbyte
 * Note that such a pointer has to be declared somewhere,
 * before it can be used.in the application.
 */

extern const __data24 uint16* dsp_main_sync0_reg;
extern const __data24 uint16* dsp_main_sync1_reg; 
extern const __data24 uint16* dsp_main_cnt_reg;
extern const __data24 uint16* dsp_adcos;
extern const __data24 uint16* dsp_adcis;
extern const __data24 uint16* dsp_classd_reg;
extern const __data24 uint16* dsp_codec_mic_gain_reg;
extern const __data24 uint16* dsp_codec_out_reg;
extern const __data24 uint16* dsp_codec_in_reg;
extern const __data24 uint16* dsp_ram_out0_reg;
extern const __data24 uint16* dsp_ram_out1_reg;
extern const __data24 uint16* dsp_ram_out2_reg;
extern const __data24 uint16* dsp_ram_out3_reg;
extern const __data24 uint16* dsp_ram_in0_reg;
extern const __data24 uint16* dsp_ram_in1_reg;
extern const __data24 uint16* dsp_ram_in2_reg;
extern const __data24 uint16* dsp_ram_in3_reg;
extern const __data24 uint16* dsp_zcross1_out_reg;
extern const __data24 uint16* dsp_zcross2_out_reg;
extern const __data24 uint16* dsp_pcm_out_reg;     
extern const __data24 uint16* dsp_pcm_out_reg;    
extern const __data24 uint16* dsp_pcm_out_reg;    
extern const __data24 uint16* dsp_pcm_out_reg;    
extern const __data24 uint16* dsp_pcm_in0_reg;     
extern const __data24 uint16* dsp_pcm_in1_reg;    
extern const __data24 uint16* dsp_pcm_in2_reg;    
extern const __data24 uint16* dsp_pcm_in3_reg;    
extern const __data24 uint16* dsp_pcm_ctrl_reg;    
extern const __data24 uint16* dsp_phase_info_reg;    
extern const __data24 uint16* dsp_vqi_reg;    
extern const __data24 uint16* dsp_main_ctrl_reg;
extern const __data24 uint16* dsp_classd_buzzoff_reg;       
extern const __data24 uint16* dsp1_ctrl_reg;       
extern const __data24 uint16* dsp1_pc_reg;    
extern const __data24 uint16* dsp1_pc_start_reg;    
extern const __data24 uint16* dsp1_irq_start_reg;  
extern const __data24 uint16* dsp1_int_reg;        
extern const __data24 uint16* dsp1_int_mask_reg;   
extern const __data24 uint16* dsp1_int_prio1_reg;   
extern const __data24 uint16* dsp1_int_prio2_reg;   
extern const __data24 uint16* dsp1_overflow_reg;
extern const __data24 uint16* dsp1_ctrl_reg;
extern const __data24 uint16* dsp2_pc_reg;    
extern const __data24 uint16* dsp2_pc_start_reg;    
extern const __data24 uint16* dsp2_int_reg;        
extern const __data24 uint16* dsp2_int_mask_reg;   
extern const __data24 uint16* dsp2_int_prio1_reg;   
extern const __data24 uint16* dsp2_int_prio2_reg;   
extern const __data24 uint16* dsp2_overflow_reg;   
extern const __data24 uint16* dbg1_ireg;   
extern const __data24 uint16* dbg1_inout_reg_lsw;   
extern const __data24 uint16* dbg1_inout_reg_msw;   
extern const __data24 uint16* dbg2_ireg;   
extern const __data24 uint16* dbg2_inout_reg_lsw;   
extern const __data24 uint16* dbg2_inout_reg_msw;   

#endif


/*
 * Missing bit field definitions for GPIO registers
 * This is not done in the datasheet to avoid very long tables
 * that contain no extra information.
 */


#define __GPIO_DATA_REG        __GPIO_BITFIELD_REG
#define __GPIO_DIR_REG         __GPIO_BITFIELD_REG
#define __GPIO_PUPD_REG        __GPIO_BITFIELD_REG
#define __GPIO_INT_EN_REG      __GPIO_BITFIELD_REG

/*====================================================*/
struct __GPIO_BITFIELD_REG
/*====================================================*/
{
    WORD BITFLD_GPIO_0                        : 1;
    WORD BITFLD_GPIO_1                        : 1;
    WORD BITFLD_GPIO_2                        : 1;
    WORD BITFLD_GPIO_3                        : 1;
    WORD BITFLD_GPIO_4                        : 1;
    WORD BITFLD_GPIO_5                        : 1;
    WORD BITFLD_GPIO_6                        : 1;
    WORD BITFLD_GPIO_7                        : 1;
    WORD BITFLD_GPIO_8                        : 1;
    WORD BITFLD_GPIO_9                        : 1;
    WORD BITFLD_GPIO_10                       : 1;
    WORD BITFLD_GPIO_11                       : 1;
    WORD BITFLD_GPIO_12                       : 1;
    WORD BITFLD_GPIO_13                       : 1;
    WORD BITFLD_GPIO_14                       : 1;
    WORD BITFLD_GPIO_15                       : 1;
};

#define GPIO_0                        (0x0001)
#define GPIO_1                        (0x0002)
#define GPIO_2                        (0x0004)
#define GPIO_3                        (0x0008)
#define GPIO_4                        (0x0010)
#define GPIO_5                        (0x0020)
#define GPIO_6                        (0x0040)
#define GPIO_7                        (0x0080)
#define GPIO_8                        (0x0100)
#define GPIO_9                        (0x0200)
#define GPIO_10                       (0x0400)
#define GPIO_11                       (0x0800)
#define GPIO_12                       (0x1000)
#define GPIO_13                       (0x2000)
#define GPIO_14                       (0x4000)
#define GPIO_15                       (0x8000)

#define SHIF(a) ((a)&0x0001?0: (a)&0x0002?1: (a)&0x0004?2: (a)&0x0008?3:\
                 (a)&0x0010?4: (a)&0x0020?5: (a)&0x0040?6: (a)&0x0080?7:\
                 (a)&0x0100?8: (a)&0x0200?9: (a)&0x0400?10:(a)&0x0800?11:\
                 (a)&0x1000?12:(a)&0x2000?13:(a)&0x4000?14: 15)

#define DSHIF(a)((a)&0x00000001?0: (a)&0x00000002?1: (a)&0x00000004?2: (a)&0x00000008?3:\
                 (a)&0x00000010?4: (a)&0x00000020?5: (a)&0x00000040?6: (a)&0x00000080?7:\
                 (a)&0x00000100?8: (a)&0x00000200?9: (a)&0x00000400?10:(a)&0x00000800?11:\
                 (a)&0x00001000?12:(a)&0x00002000?13:(a)&0x00004000?14:(a)&0x00008000?15:\
                 (a)&0x00010000?16:(a)&0x00020000?17:(a)&0x00040000?18:(a)&0x00080000?19:\
                 (a)&0x00100000?20:(a)&0x00200000?21:(a)&0x00400000?22:(a)&0x00800000?23:\
                 (a)&0x01000000?24:(a)&0x02000000?25:(a)&0x04000000?26:(a)&0x08000000?27:\
                 (a)&0x10000000?28:(a)&0x20000000?29:(a)&0x40000000?30: 31)

#ifdef IO_BY_FUNCTION_CALLS
    WORD fc_get_word(BYTE* a);
    WORD fc_get_bits(BYTE* a, WORD msk);
    void fc_set_word(BYTE* a, WORD v);
    void fc_set_bits(BYTE* a, WORD msh, WORD v);

    void fc_set_PSR_I_bit(void);
    void fc_reset_PSR_I_bit(void);
    void fc_enable_interrupt(void);
    void fc_disable_interrupt(void);
    void fc_wait(void);

    #define GetByte(a)  	fc_get_byte((BYTE*)a)
    #define GetWord(a)  	fc_get_word((BYTE*)a)
    #define GetBits(a,f)	fc_get_bits((BYTE*)a,f) 
    #define SetByte(a,d)	fc_set_byte((BYTE*)a,d)    
    #define SetWord(a,d)	fc_set_word((BYTE*)a,d)
    #define SetBits(a,f,d)	fc_set_bits((BYTE*)a,f,d)
#else
    #define GetByte(a)  	(* ( __far volatile BYTE*)(a) )
    #define GetWord(a)  	(* ( __far volatile WORD*)(a) )
    #define GetDword(a)  	(* ( __far volatile DWORD*)(a) )
    #define GetBits(a,f)	(( ( __far volatile struct __##a *)(a))->BITFLD_##f )
    #define GetDbits(a,f)	(( ( __far volatile struct __##a *)(a))->BITFLD_##f ) 
    #define SetByte(a,d)	(* ( __far volatile BYTE*)(a)=(d) )
    #define SetWord(a,d)	(* ( __far volatile WORD*)(a)=(d) )
    #define SetDword(a,d)	(* ( __far volatile DWORD*)(a)=(d) )
    #define SetBits(a,f,d)	( SetWord( a, (GetWord(a)&((WORD)~f)) | ((d)<<SHIF(f)) ))
    #define SetDbits(a,f,d)	( SetDword(a, (GetDword(a)&((DWORD)~f)) | (((DWORD)d)<<DSHIF(f)) ))
#endif
#endif
