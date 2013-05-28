#ifndef GDSP_REGISTERDEFS_H_INCLUDED
#define GDSP_REGISTERDEFS_H_INCLUDED

#define _DSP_MAIN_SYNC0_REG             (0x00BFC0)  /* DSP main counter outputs selection register 0 */
#define _DSP_MAIN_SYNC1_REG             (0x00BFC1)  /* DSP main counter outputs selection register 1 */
#define _DSP_MAIN_CNT_REG               (0x00BFC2)  /* DSP main counter and reload register */
#define _DSP_ADC0S_REG                  (0x00BFC3)  /* ADC0 Input 2's Complement register */
#define _DSP_ADC1S_REG                  (0x00BFC4)  /* ADC1 Input 2's Complement register */
#define _DSP_CLASSD_REG                 (0x00BFC5)  /* CLASSD Output output data register */
#define _DSP_CODEC_MIC_GAIN_REG         (0x00BFC6)  /* CODEC MIC GAIN register */
#define _DSP_CODEC_OUT_REG              (0x00BFC7)  /* CODEC DATA register */
#define _DSP_CODEC_IN_REG               (0x00BFC8)  /* CODEC DATA register */
#define _DSP_RAM_OUT0_REG               (0x00BFC9)  /* Shared RAM 1 or 2 output register 0 */
#define _DSP_RAM_OUT1_REG               (0x00BFCA)  /* Shared RAM 1 or 2 output register 1 */
#define _DSP_RAM_OUT2_REG               (0x00BFCB)  /* Shared RAM 1 or 2 output register 2 */
#define _DSP_RAM_OUT3_REG               (0x00BFCC)  /* Shared RAM 1 or 2 output register 3 */
#define _DSP_RAM_IN0_REG                (0x00BFCD)  /* Shared RAM 1 or 2 input register 0 */
#define _DSP_RAM_IN1_REG                (0x00BFCE)  /* Shared RAM 1 or 2 input register 1 */
#define _DSP_RAM_IN2_REG                (0x00BFCF)  /* Shared RAM 1 or 2 input register 2 */
#define _DSP_RAM_IN3_REG                (0x00BFD0)  /* Shared RAM 1 or 2 input register 3 */
#define _DSP_ZCROSS1_OUT_REG            (0x00BFD1)  /* ZERO CROSSING 1 output register */
#define _DSP_ZCROSS2_OUT_REG            (0x00BFD2)  /* ZERO CROSSING 2 output register */
#define _DSP_PCM_OUT0_REG               (0x00BFD3)  /* PCM channel 0 output register */
#define _DSP_PCM_OUT1_REG               (0x00BFD4)  /* PCM channel 1 output register */
#define _DSP_PCM_OUT2_REG               (0x00BFD5)  /* PCM channel 2 output register */
#define _DSP_PCM_OUT3_REG               (0x00BFD6)  /* PCM channel 3 output register */
#define _DSP_PCM_IN0_REG                (0x00BFD7)  /* PCM channel 0 input register */
#define _DSP_PCM_IN1_REG                (0x00BFD8)  /* PCM channel 1 input register */
#define _DSP_PCM_IN2_REG                (0x00BFD9)  /* PCM channel 2 input register */
#define _DSP_PCM_IN3_REG                (0x00BFDA)  /* PCM channel 3 input register */
#define _DSP_PCM_CTRL_REG               (0x00BFDB)  /* PCM Control register */
#define _DSP_PHASE_INFO_REG             (0x00BFDC)  /* Phase information between PCM FSC 8/16/32 and main counter 8/16/32 kHz */
#define _DSP_VQI_REG                    (0x00BFDD)  /* BMC VQI register */
#define _DSP_MAIN_CTRL_REG              (0x00BFDE)  /* DSP Main counter control and preset value */
#define _DSP_CLASSD_BUZZOFF_REG         (0x00BFDF)  /* CLASSD Buzzer on/off controller, bit 15 */
#define _DSP_CTRL_REG                   (0x00BFE8)  /* DSP1 control register */
#define _DSP_PC_REG                     (0x00BFE9)  /* DSP1 Programma counter */
#define _DSP_PC_START_REG               (0x00BFEA)  /* DSP1 Programma counter start */
#define _DSP_IRQ_START_REG              (0x00BFEB)  /* DSP1 Interrupt vector start */
#define _DSP_INT_REG                    (0x00BFEC)  /* DSP1 to CR16 interrupt vector */
#define _DSP_INT_MASK_REG               (0x00BFED)  /* DSP1 to CR16 interrupt vector maks */
#define _DSP_INT_PRIO1_REG              (0x00BFEE)  /* DSP1 Interrupt source mux 1 register */
#define _DSP_INT_PRIO2_REG              (0x00BFEF)  /* DSP1 Interrupt source mux 2 register */
#define _DSP_OVERFLOW_REG               (0x00BFF0)  /* DSP1 to CR16 overflow register */
#define _DBG_IREG                       (0x00BFF8)  /* DSP1 JTAG instruction register */
#define _DBG_INOUT_REG_LSW              (0x00BFFA)  /*  */
#define _DBG_INOUT_REG_MSW              (0x00BFFB)  /*  */

#endif
