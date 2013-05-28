#ifndef DSPSIGNALHANDLER_H_
#define DSPSIGNALHANDLER_H_

#ifndef PCCOMPILE
#ifdef GCCCOMPILE
#include "../../../include/common/include/map_480_gcc.h"
#else
#include "../../../include/common/include/map_480.h"
#endif
#endif
#include "../../../include/hlkgap/dduos/include/dduos.h"

#define SETUPAUDIO_EVENT 100
#define STARTADPCM_EVENT 101
#define STARTCODEC_EVENT 102
#define STARTDSP_EVENT   103
#define STARTPCM_EVENT   104
#define STOPAUDIO_EVENT  105
#define HMSETUPAUDIO_EVENT 106 

extern ProcessIdType DSP_PROCESS_ID;

#ifndef GCCCOMPILE
#define DSP_PARAM(x) *((uint16*)(((&x - &_DSPDATA_START) << 1) + DSPRAMSEG_START))
#endif

#define CLR_DSP_INT_PENDING                0x2000
#define CLEAR_PENDING_DSP_INTERRUPT        RESET_INT_PENDING_REG = CLR_DSP_INT_PENDING

#endif /* DSPSIGNALHANDLER_H_ */
