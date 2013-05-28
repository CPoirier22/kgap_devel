#include "gdsp_functionmanager_api.h"       
#include "gdsp_registerdef.h"
//#include "sc144xx/gdsp_registerdef.h"

#define CASDETECTOR_INT         DEFAULT_CASDETECTOR_INT
#define CASDETECTORV2_INT       DEFAULT_CASDETECTORV2_INT
#define DTMFDETECTOR_INT        DEFAULT_DTMFDETECTOR_INT
#define DTMFRUDETECTOR_INT      DEFAULT_DTMFRUDETECTOR_INT
#define DURATIONCOUNTER_INT     DEFAULT_DURATIONCOUNTER_INT
#define EDGEDETECTOR21_INT      DEFAULT_EDGEDETECTOR21_INT
#define EVENTCOUNTER_INT        DEFAULT_EVENTCOUNTER_INT
#define FSKDECODER_INT          DEFAULT_FSKDECODER_INT
#define PLAYBACKBUFFER_INT      DEFAULT_PLAYBACKBUFFER_INT
#define RECORDBUFFER_INT        DEFAULT_RECORDBUFFER_INT
#define SINGLETONEDETECTOR_INT  DEFAULT_SINGLETONEDETECTOR_INT
#define FSKGEN_INT              DEFAULT_FSKGEN_INT
#define SVC_ENC_INT             DEFAULT_SVC_ENC_INT
#define SVC_DEC_INT             DEFAULT_SVC_DEC_INT
//#define DEFAULT_SVC_DEC_INT             (0x1<<13) last in gdsp_functionmanagerdefs.h
#define OUT_BUFFER_INT          (0x1<<14)
#define PAEC_INT                (0x1<<15)
#define MIC_BUFFER_INT          DEFAULT_RECORDBUFFER_INT
#define SPKR_BUFFER_INT         DEFAULT_RECORDBUFFER_INT
#define PCM_BUFFER_INT      	DEFAULT_RECORDBUFFER_INT
