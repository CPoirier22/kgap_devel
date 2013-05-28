#ifndef GDSP_GDSP_ALL_INITS_CINITS_H
#define GDSP_GDSP_ALL_INITS_CINITS_H
#include "gdsp_local_config.h" // User h-file for defining where to get type definitions from
#include "gdsp_all_structdefs.h"
#include "gdsp_local_defines.h" // User h-file for defining where to get type definitions from

extern const unsigned short g726decoder[];
extern const unsigned short g726decoder_code[8];
extern gdsp_adpcmnbdecoder* p_g726decoder_pp;

extern const unsigned short g726encoder[];
extern const unsigned short g726encoder_code[8];
extern gdsp_adpcmnbencoder* p_g726encoder_pp;

extern gdsp_adpcmnbdecoder* p_g726decoder[6];
extern gdsp_adpcmnbencoder* p_g726encoder[6];

extern const unsigned short gendspclassddestination[];
extern const unsigned short gendspclassddestination_code[4];
extern gdsp_classddestinations* p_gendspclassddestination;

extern const unsigned short gendspcodecdestinations[];
extern const unsigned short gendspcodecdestinations_code[4];
extern gdsp_codecdestinations* p_gendspcodecdestinations;

extern const unsigned short gendspcodecsource[];
extern const unsigned short gendspcodecsource_code[4];
extern gdsp_codecsource* p_gendspcodecsource;

extern const unsigned short gendsppcmmasterdestinations[];
extern const unsigned short gendsppcmmasterdestinations_code[4];
extern gdsp_pcmmasterdestinations* p_gendsppcmmasterdestinations;

extern const unsigned short gendsppcmsource[];
extern const unsigned short gendsppcmsource_code[4];
extern gdsp_pcmsource* p_gendsppcmsource;

extern const unsigned short gendspgainconstant[];
extern gdsp_constant* p_gendspgainconstant_pp;
extern gdsp_constant* p_gendspgainconstant_fp;
extern gdsp_constant* p_gendspgainconstant_encoder;
extern gdsp_constant* p_gendsp_pcm_command_out;

extern const unsigned short dtmfdetector[];
extern const unsigned short dtmfdetector_code[8];
extern gdsp_dtmfdetector* p_dtmfdetector;

extern const unsigned short gain[];
extern const unsigned short gain_code[4];
extern gdsp_gain* p_gain_encoder_pp;
extern gdsp_gain* p_gain_decoder_pp;
extern gdsp_gain* p_gain_spkr_pp;
extern gdsp_gain* p_gain_spkr_fp;
extern gdsp_gain* p_gain_inbound;

extern const unsigned short law2lin[];
extern const unsigned short law2lin_code[4];
extern gdsp_lawlin* p_law2lin;

extern const unsigned short dynmixer_pp[];
extern const unsigned short dynmixer_post[];
extern const unsigned short dynmixer_pcm[];
extern const unsigned short dynmixer_code[4];
extern gdsp_mixer* p_dynmixer0;
extern gdsp_mixer* p_dynmixer1;
extern gdsp_mixer* p_dynmixer2;
extern gdsp_mixer* p_dynmixer3;
extern gdsp_mixer* p_dynmixer4;
extern gdsp_mixer* p_dynmixer5;
extern gdsp_mixer* p_dynmixer6;
extern gdsp_mixer* p_dynmixer7;

extern const unsigned short playbackbuffer[];
extern const unsigned short playbackbuffer_code[8];
extern gdsp_playbackbuffer_18* p_playbackbuffer;

extern const unsigned short pcm_buffer[];
extern const unsigned short pcm_buffer_code[8];
extern gdsp_recordbuffer_18* p_pcm_buffer;

extern const unsigned short singletonedetector[];
extern const unsigned short singletonedetector_code[8];
extern gdsp_singletonedetector* p_singletonedetector;

extern const unsigned short summator[];
extern const unsigned short summator_code[4];
extern gdsp_summator* p_summator;

extern const unsigned short tonegen[];
extern const unsigned short tonegen_code[4];
extern gdsp_tonegen* p_tonegen;

extern const unsigned short g726decoder1[];
extern const unsigned short g726decoder1_code[8];

extern const unsigned short g726encoder1[];
extern const unsigned short g726encoder1_code[8];

extern const unsigned short g726decoder2[];
extern const unsigned short g726decoder2_code[8];

extern const unsigned short g726encoder2[];
extern const unsigned short g726encoder2_code[8];

extern const unsigned short g726decoder3[];
extern const unsigned short g726decoder3_code[8];

extern const unsigned short g726encoder3[];
extern const unsigned short g726encoder3_code[8];

extern const unsigned short g726decoder4[];
extern const unsigned short g726decoder4_code[8];

extern const unsigned short g726encoder4[];
extern const unsigned short g726encoder4_code[8];

extern const unsigned short g726decoder5[];
extern const unsigned short g726decoder5_code[8];

extern const unsigned short g726encoder5[];
extern const unsigned short g726encoder5_code[8];

extern const unsigned short g726decoder6[];
extern const unsigned short g726decoder6_code[8];

extern const unsigned short g726encoder6[];
extern const unsigned short g726encoder6_code[8];

extern const unsigned short gendspgainconstant[];

extern gdsp_constant* p_stopcopyconstant;
extern const unsigned short stopcopyconstant[];

extern const unsigned short gendspconstant[];
extern gdsp_constant* p_gendspconstant;

extern const unsigned short gendspconstant3[];
extern gdsp_constant* p_gendspconstant3;

extern const unsigned short durationcounter[];
extern const unsigned short durationcounter_code[8];
extern gdsp_durationcounter* p_durationcounter;

extern const unsigned short copySpeechBuffer1[];
extern const unsigned short copySpeechBuffer1_code[58];
extern copySpeecBuffers* p_copySpeechBuffer1;

extern const unsigned short clearPointers1[];
extern const unsigned short clearPointers1_code[12];
extern clearPointers* p_clearPointers1;

extern const unsigned short dataArea0[];
extern dataArea_40* p_dataArea0;

extern const unsigned short dataArea2[];
extern dataArea_40* p_dataArea2;

extern const unsigned short dataArea4[];
extern dataArea_40* p_dataArea4;

extern const unsigned short dataArea6[];
extern dataArea_40* p_dataArea6;

extern const unsigned short dataArea8[];
extern dataArea_40* p_dataArea8;

extern const unsigned short dataArea10[];
extern dataArea_40* p_dataArea10;

extern const unsigned short dataArea12[];
extern dataArea_40* p_dataArea12;

extern const unsigned short dataArea14[];
extern dataArea_40* p_dataArea14;

extern const unsigned short dataArea16[];
extern dataArea_40* p_dataArea16;

extern const unsigned short dataArea18[];
extern dataArea_40* p_dataArea18;

extern const unsigned short dataArea20[];
extern dataArea_40* p_dataArea20;

extern const unsigned short dataArea22[];
extern dataArea_40* p_dataArea22;

extern const unsigned short conference[];
extern const unsigned short conference_code[4];
extern gdsp_conference* p_conference;

#endif                         // GDSP_CINITS_H 
