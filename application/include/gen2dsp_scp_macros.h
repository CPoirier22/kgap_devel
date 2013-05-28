#ifndef _GEN2DSP_SCP_MACROS_H_
#define _GEN2DSP_SCP_MACROS_H_

#include "../include/gen2dsp.h"

/* Substitute for SCP instructions */
#define WTF                     dw 0xbfc2, 0x7fff
#define JPO(a)                  dw 0xf3be, ((a-_DSPCODE_START) >> 1) + DSPCODESTARTOFFSET
#define LDO(a)                  dw 0xff70, (((DSPRAMSEG_START + (a-_DSPDATA_START)) - 0x10000) >> 1)
/* #define LDO(a)                  dw 0xf390, (((DSPRAMSEG_START + (a-_DSPDATA_START)) - 0x10000) >> 1)*/
#define CALL(a)                 dw 0xf3bd, (2*a + 0x8000)
#define SKP(a)                  dw 0xff80, ((a-_DSPDATA_START+(DSPRAMSEG_START-0x10000)) >> 1), 0x7e50, 0x7fff, 0xba00
#define SKN(a)                  dw 0xff80, ((a-_DSPDATA_START+(DSPRAMSEG_START-0x10000)) >> 1), 0x7e40, 0x7fff, 0xba00
#define IRQ(a)                  dw 0xf3b6, (a)
#define NOP                     dw 0x7fff
#define BRU(a)                  dw 0xf3be, ((a-_DSPCODE_START) >> 1) + DSPCODESTARTOFFSET
#define LDC(a)                  dw 0xffbe, ((a-_DSPDATA_START+(DSPRAMSEG_START-0x10000)) >> 1)
#define CIRQ(a)                 dw 0xf3b6, (a)
#define JCA(a)                  dw 0xf3ba, ((a-_DSPCODE_START) >> 1) + DSPCODESTARTOFFSET
#define CONNECT_INPUT_PTR(a, y) (((DSPRAMSEG_START + (a-_DSPDATA_START)) - 0x10000) >> 1)

#endif
