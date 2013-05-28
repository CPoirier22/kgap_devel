#ifndef _GEN2DSP_14450_INCLUDED
#define _GEN2DSP_14450_INCLUDED

#define _DSP_CLASSD_REG                         (0x00BFC5)  /* CLASSD Output output data register */
#define _DSP_CODEC_MIC_GAIN_REG                 (0x00BFC6)  /* CODEC MIC GAIN register */
#define _DSP_CODEC_OUT_REG                      (0x00BFC7)  /* CODEC DATA register */
#define _DSP_CODEC_IN_REG                       (0x00BFC8)  /* CODEC DATA register */
#define _DSP_RAM_OUT0_REG                       (0x00BFC9)  /* Shared RAM 1 or 2 output register 0 */
#define _DSP_RAM_OUT1_REG                       (0x00BFCA)  /* Shared RAM 1 or 2 output register 1 */
#define _DSP_RAM_IN0_REG                        (0x00BFCD)  /* Shared RAM 1 or 2 input register 0 */
#define _DSP_RAM_IN1_REG                        (0x00BFCE)  /* Shared RAM 1 or 2 input register 1 */
#define _DSP_ZCROSS1_OUT_REG                    (0x00BFD1)  /* Shared RAM 1 or 2 input register 1 */

/* DSP Interrupt vectors*/
#define INT1          0x0001
#define INT2          0x0002
#define INT3          0x0004
#define INT4          0x0008
#define INT5          0x0010
#define INT6          0x0020
#define INT7          0x0040
#define INT8          0x0080
#define INT9          0x0100
#define INT10         0x0200
#define INT11         0x0400
#define INT12         0x0800
#define INT13         0x1000
#define INT14         0x2000
#define INT15         0x4000
#define INT16         0x8000
#define OVERFLOW      0xffff

#endif
