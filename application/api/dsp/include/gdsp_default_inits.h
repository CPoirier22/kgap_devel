#ifndef GDSP_GDSP_DEFAULT_INITS_CINITS_H
#define GDSP_GDSP_DEFAULT_INITS_CINITS_H
#include "gdsp_local_config.h" /* User h-file for defining where to get type definitions from*/
#include "gdsp_default_structdefs.h"

extern const unsigned short default_absolute[];

extern const unsigned short default_absolute_code[4];
extern gdsp_default_absolutevalue* p_default_absolute;

extern const unsigned short default_adcsource[];

extern const unsigned short default_adcsource_code[4];
extern gdsp_default_adcsource* p_default_adcsource;

extern const unsigned short default_adpcmdestinations[];

extern const unsigned short default_adpcmdestinations_code[16];
extern gdsp_default_adpcmdestinations* p_default_adpcmdestinations;

extern const unsigned short default_g726decoder[];

extern const unsigned short default_g726decoder_code[8];
extern gdsp_default_adpcmnbdecoder* p_default_g726decoder;

extern const unsigned short default_g726encoder[];

extern const unsigned short default_g726encoder_code[8];
extern gdsp_default_adpcmnbencoder* p_default_g726encoder;

extern const unsigned short default_g726vqidecoder[];

extern const unsigned short default_g726vqidecoder_code[8];
extern gdsp_default_adpcmnbvqidecoder* p_default_g726vqidecoder;

extern const unsigned short default_adpcmsource[];

extern const unsigned short default_adpcmsource_code[16];
extern gdsp_default_adpcmsource* p_default_adpcmsource;

extern const unsigned short default_g722decoder[];

extern const unsigned short default_g722decoder_code[20];
extern gdsp_default_adpcmwbdecoder* p_default_g722decoder;

extern const unsigned short default_g722encoder[];

extern const unsigned short default_g722encoder_code[20];
extern gdsp_default_adpcmwbencoder* p_default_g722encoder;

extern const unsigned short default_acousticechocanceller2[];

extern const unsigned short default_acousticechocanceller2_code[4];
extern gdsp_default_aec_512* p_default_acousticechocanceller2;

extern const unsigned short default_acousticechocanceller2withmu[];

extern const unsigned short default_acousticechocanceller2withmu_code[8];
extern gdsp_default_aecwithmuinput_512* p_default_acousticechocanceller2withmu;

extern const unsigned short default_agcblock[];

extern const unsigned short default_agcblock_code[4];
extern gdsp_default_agc* p_default_agcblock;

extern const unsigned short default_analogagc[];

extern const unsigned short default_analogagc_code[4];
extern gdsp_default_analogagc* p_default_analogagc;

extern const unsigned short default_logicand[];

extern const unsigned short default_logicand_code[4];
extern gdsp_default_and* p_default_logicand;

extern const unsigned short default_biquadfilter[];

extern const unsigned short default_biquadfilter_code[4];
extern gdsp_default_biquadfilter* p_default_biquadfilter;

extern const unsigned short default_casdetector[];

extern const unsigned short default_casdetector_code[8];
extern gdsp_default_casdetector* p_default_casdetector;

extern const unsigned short default_casdetectorv2[];

extern const unsigned short default_casdetectorv2_code[8];
extern gdsp_default_casdetectorsplitinput* p_default_casdetectorv2;

extern const unsigned short default_classddestination[];

extern const unsigned short default_classddestination_code[4];
extern gdsp_default_classddestinations* p_default_classddestination;

extern const unsigned short default_codecdestinations[];

extern const unsigned short default_codecdestinations_code[4];
extern gdsp_default_codecdestinations* p_default_codecdestinations;

extern const unsigned short default_codecsource[];

extern const unsigned short default_codecsource_code[4];
extern gdsp_default_codecsource* p_default_codecsource;

extern const unsigned short default_conference[];

extern const unsigned short default_conference_code[4];
extern gdsp_default_conference* p_default_conference;

extern const unsigned short default_gendspconstant[];

extern gdsp_default_constant* p_default_gendspconstant;

extern const unsigned short default_decrement[];

extern const unsigned short default_decrement_code[4];
extern gdsp_default_decrement* p_default_decrement;

extern const unsigned short default_delayline[];

extern const unsigned short default_delayline_code[4];
extern gdsp_default_delayline_120* p_default_delayline;

extern const unsigned short default_division[];

extern const unsigned short default_division_code[4];
extern gdsp_default_division* p_default_division;

extern const unsigned short default_dtmfdetector[];

extern const unsigned short default_dtmfdetector_code[8];
extern gdsp_default_dtmfdetector* p_default_dtmfdetector;

extern const unsigned short default_dtmfrudetector[];

extern const unsigned short default_dtmfrudetector_code[8];
extern gdsp_default_dtmfrudetector* p_default_dtmfrudetector;

extern const unsigned short default_durationcounter[];

extern const unsigned short default_durationcounter_code[8];
extern gdsp_default_durationcounter* p_default_durationcounter;

extern const unsigned short default_echocancellation[];

extern const unsigned short default_echocancellation_code[4];
extern gdsp_default_echocancellation_64* p_default_echocancellation;

extern const unsigned short default_echocancellationwithmuinput[];

extern const unsigned short default_echocancellationwithmuinput_code[8];
extern gdsp_default_echocancellationwithmuinput_40* p_default_echocancellationwithmuinput;

extern const unsigned short default_edgedetector21[];

extern const unsigned short default_edgedetector21_code[8];
extern gdsp_default_edgedetector* p_default_edgedetector21;

extern const unsigned short default_eventcounter[];

extern const unsigned short default_eventcounter_code[8];
extern gdsp_default_eventcounter* p_default_eventcounter;

extern const unsigned short default_exponent[];

extern const unsigned short default_exponent_code[4];
extern gdsp_default_exponent* p_default_exponent;

extern const unsigned short default_fft[];

extern const unsigned short default_fft_code[4];
extern gdsp_default_fft* p_default_fft;

extern const unsigned short default_fmoperator[];

extern const unsigned short default_fmoperator_code[4];
extern gdsp_default_fmoperator* p_default_fmoperator;

extern const unsigned short default_fskdecoder[];

extern const unsigned short default_fskdecoder_code[8];
extern gdsp_default_fskclipdecoder* p_default_fskdecoder;

extern const unsigned short default_fskgen[];

extern const unsigned short default_fskgen_code[8];
extern gdsp_default_fskgen_258* p_default_fskgen;

extern const unsigned short default_gain[];

extern const unsigned short default_gain_code[4];
extern gdsp_default_gain* p_default_gain;

extern const unsigned short default_hagcblock[];

extern const unsigned short default_hagcblock_code[4];
extern gdsp_default_hagc* p_default_hagcblock;

extern const unsigned short default_handsfree[];

extern const unsigned short default_handsfree_code[4];
extern gdsp_default_handsfree* p_default_handsfree;

extern const unsigned short default_ifft[];

extern const unsigned short default_ifft_code[4];
extern gdsp_default_ifft* p_default_ifft;

extern const unsigned short default_increment[];

extern const unsigned short default_increment_code[4];
extern gdsp_default_increment* p_default_increment;

extern const unsigned short default_integerdivision[];

extern const unsigned short default_integerdivision_code[4];
extern gdsp_default_integerdivision* p_default_integerdivision;

extern const unsigned short default_interpolator[];

extern const unsigned short default_interpolator_code[4];
extern gdsp_default_interpolator_2000* p_default_interpolator;

extern const unsigned short default_law2lin[];

extern const unsigned short default_law2lin_code[4];
extern gdsp_default_lawlin* p_default_law2lin;

extern const unsigned short default_lin2log[];

extern const unsigned short default_lin2log_code[4];
extern gdsp_default_lineairtolog* p_default_lin2log;

extern const unsigned short default_lin2law[];

extern const unsigned short default_lin2law_code[4];
extern gdsp_default_linlaw* p_default_lin2law;

extern const unsigned short default_log2lin[];

extern const unsigned short default_log2lin_code[4];
extern gdsp_default_logtolineair* p_default_log2lin;

extern const unsigned short default_midisynth[];

extern const unsigned short default_midisynth_code[4];
extern gdsp_default_midisynth* p_default_midisynth;

extern const unsigned short default_minmax[];

extern const unsigned short default_minmax_code[4];
extern gdsp_default_minmax* p_default_minmax;

extern const unsigned short default_dynmixer[];

extern const unsigned short default_dynmixer_code[4];
extern gdsp_default_mixer* p_default_dynmixer;

extern const unsigned short default_monitor[];

extern const unsigned short default_monitor_code[4];
extern gdsp_default_monitor* p_default_monitor;

extern const unsigned short default_nibbleshiftleft[];

extern const unsigned short default_nibbleshiftleft_code[4];
extern gdsp_default_nibbleshiftleft* p_default_nibbleshiftleft;

extern const unsigned short default_nibbleshiftright[];

extern const unsigned short default_nibbleshiftright_code[4];
extern gdsp_default_nibbleshiftright* p_default_nibbleshiftright;

extern const unsigned short default_normalization[];

extern const unsigned short default_normalization_code[4];
extern gdsp_default_norm* p_default_normalization;

extern const unsigned short default_logicor[];

extern const unsigned short default_logicor_code[4];
extern gdsp_default_or* p_default_logicor;

extern const unsigned short default_paec[];

extern const unsigned short default_paec_code[4];
extern gdsp_default_paec* p_default_paec;

extern const unsigned short default_pcmmasterdestinations[];

extern const unsigned short default_pcmmasterdestinations_code[4];
extern gdsp_default_pcmmasterdestinations* p_default_pcmmasterdestinations;

extern const unsigned short default_pcmsource[];

extern const unsigned short default_pcmsource_code[4];
extern gdsp_default_pcmsource* p_default_pcmsource;

extern const unsigned short default_playbackbuffer[];

extern const unsigned short default_playbackbuffer_code[8];
extern gdsp_default_playbackbuffer_12* p_default_playbackbuffer;

extern const unsigned short default_powerleveldetector[];

extern const unsigned short default_powerleveldetector_code[4];
extern gdsp_default_plevdet* p_default_powerleveldetector;

extern const unsigned short default_noiseleveldetector[];

extern const unsigned short default_noiseleveldetector_code[4];
extern gdsp_default_pnlevdet* p_default_noiseleveldetector;

extern const unsigned short default_polynomial[];

extern const unsigned short default_polynomial_code[4];
extern gdsp_default_polynomial* p_default_polynomial;

extern const unsigned short default_programmablefirfilter[];

extern const unsigned short default_programmablefirfilter_code[4];
extern gdsp_default_programmablefirfilter_42* p_default_programmablefirfilter;

extern const unsigned short default_recordbuffer[];

extern const unsigned short default_recordbuffer_code[8];
extern gdsp_default_recordbuffer_128* p_default_recordbuffer;

extern const unsigned short default_rfft[];

extern const unsigned short default_rfft_code[4];
extern gdsp_default_rfft* p_default_rfft;

extern const unsigned short default_rfifilter[];

extern const unsigned short default_rfifilter_code[4];
extern gdsp_default_rfinoisecanceller_80* p_default_rfifilter;

extern const unsigned short default_rifft[];

extern const unsigned short default_rifft_code[4];
extern gdsp_default_rifft* p_default_rifft;

extern const unsigned short default_noisegenerator[];

extern const unsigned short default_noisegenerator_code[4];
extern gdsp_default_rndgen* p_default_noisegenerator;

extern const unsigned short default_shift[];

extern const unsigned short default_shift_code[4];
extern gdsp_default_shift* p_default_shift;

extern const unsigned short default_singletonedetector[];

extern const unsigned short default_singletonedetector_code[8];
extern gdsp_default_singletonedetector* p_default_singletonedetector;

extern const unsigned short default_subtract[];

extern const unsigned short default_subtract_code[4];
extern gdsp_default_subtractor* p_default_subtract;

extern const unsigned short default_summator[];

extern const unsigned short default_summator_code[4];
extern gdsp_default_summator* p_default_summator;

extern const unsigned short default_suppressor[];

extern const unsigned short default_suppressor_code[4];
extern gdsp_default_suppressor* p_default_suppressor;

extern const unsigned short default_svcdecoderblock[];

extern const unsigned short default_svcdecoderblock_code[6];
extern gdsp_default_svcdecoder* p_default_svcdecoderblock;

extern const unsigned short default_svcencoderblock[];

extern const unsigned short default_svcencoderblock_code[6];
extern gdsp_default_svcencoder* p_default_svcencoderblock;

extern const unsigned short default_tonedetector[];

extern const unsigned short default_tonedetector_code[4];
extern gdsp_default_tonedetector* p_default_tonedetector;

extern const unsigned short default_tonegen[];

extern const unsigned short default_tonegen_code[4];
extern gdsp_default_tonegen* p_default_tonegen;

extern const unsigned short default_widebandenhancer[];

extern const unsigned short default_widebandenhancer_code[4];
extern gdsp_default_widebandenhancer_99* p_default_widebandenhancer;

extern const unsigned short default_logicxor[];

extern const unsigned short default_logicxor_code[4];
extern gdsp_default_xor* p_default_logicxor;

extern const unsigned short default_zerocrossdetector[];

extern const unsigned short default_zerocrossdetector_code[4];
extern gdsp_default_zerocrossdetector* p_default_zerocrossdetector;

extern const unsigned short default_zerocrossingdestinations[];

extern const unsigned short default_zerocrossingdestinations_code[4];
extern gdsp_default_zerocrossingdestinations* p_default_zerocrossingdestinations;

#endif                         /* GDSP_CINITS_H */
