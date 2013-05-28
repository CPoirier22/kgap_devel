#ifndef GDSP_CONF_INITS_TYPEDEF_H
#define GDSP_CONF_INITS_TYPEDEF_H
typedef struct
{
  unsigned short flag_ptr;               // pointer to the trigger flag
  unsigned short number_of_opcode_jumps; // number of SCP words to skip if flag is not set
} gdsp_custom_backgroundtrigger;

typedef struct
{
  unsigned short tx_rec_buf_buffer_ptr;
  unsigned short rx_rec_buf_buffer_ptr;
  unsigned short tx_rec_buf_writeidx_ptr;
  unsigned short rx_rec_buf_writeidx_ptr;
  unsigned short paec_ibuf_idx_ptr;
  unsigned short Framesize;
} gdsp_custom_paec_es7_fix;

typedef struct
{
  unsigned short  paec_data_ptr; // Pointer to PAEC data struct
  unsigned short  vadsm1; // Attact TC; equal to or larger than smoothtop
  unsigned short  vadsm2; // Decay TC; equal to or larger than smoothlow
  unsigned short  new_thresh; // Voice probability threshold
  unsigned short  xpow_thresh; // Voice band powerlevel threshold
  unsigned short  maxnorm_dflt; // default setting for PAEC param intshift_maxnorm
  unsigned short  bandshift_max; // max bandshift limit
  unsigned short  bandshift_min; // min bandshift limit
  unsigned short  wfevad; // Actual speech probability (state)
  unsigned short  detect; // Speech detected (0x8000) / not detected (0x0000)
  unsigned short  fevad[15]; // 12? Actual band speech probability (state)
} gdsp_custom_paec_vad;


typedef struct
{
  unsigned short b_nr_bits1;           // 
  unsigned short b_nr_bits2;           // 
  unsigned short b_nr_bits3;           // 
  unsigned short b_swap_mode;          // 
  unsigned short b_out_val;            // 
  unsigned short b_out_bits;           // 
  unsigned short b_buf_ptr;            // 
  unsigned short b_buf_start;          // 
  unsigned short b_buf_end;            // 
  unsigned short b_flip_irq;           // 
  unsigned short b_buffer_out1;        // 
  unsigned short b_buffer_out2;        // 
  unsigned short g_in1_ptr;            // 
  unsigned short g_mode;               // 
  unsigned short g_out1;               // 
  unsigned short g_sr1;                // 
  unsigned short g_a2r;                // 
  unsigned short g_a1r;                // 
  unsigned short g_dq[6];              // 
  unsigned short g_br[6];              // 
  unsigned short g_dmsp;               // 
  unsigned short g_dmlp;               // 
  unsigned short g_apr;                // 
  unsigned short g_yup;                // 
  unsigned short g_ylp_lsb;            // 
  unsigned short g_ylp_msb;            // 
  unsigned short g_tdr;                // 
  unsigned short g_pk0;                // 
  unsigned short g_pk1;                // 
  unsigned short g_sr0;                // 
  unsigned short g_intlv_ptr;          // 
} gdsp_adpcmnbdecoder;

typedef struct
{
  unsigned short g_in1_ptr;            // 
  unsigned short g_mode;               // 
  unsigned short g_out1;               // 
  unsigned short g_sr1;                // 
  unsigned short g_a2r;                // 
  unsigned short g_a1r;                // 
  unsigned short g_dq[6];              // 
  unsigned short g_br[6];              // 
  unsigned short g_dmsp;               // 
  unsigned short g_dmlp;               // 
  unsigned short g_apr;                // 
  unsigned short g_yup;                // 
  unsigned short g_ylp_lsb;            // 
  unsigned short g_ylp_msb;            // 
  unsigned short g_tdr;                // 
  unsigned short g_pk0;                // 
  unsigned short g_pk1;                // 
  unsigned short g_sr0;                // 
  unsigned short g_intlv_ptr;          // 
  unsigned short b_in_ptr1;            // 
  unsigned short b_in_ptr2;            // 
  unsigned short b_nr_bits1;           // 
  unsigned short b_nr_bits2;           // 
  unsigned short b_nr_bits3;           // 
  unsigned short b_swap_mode;          // 
  unsigned short b_new_val;            // 
  unsigned short b_new_bits;           // 
  unsigned short b_buf_ptr;            // 
  unsigned short b_buf_start;          // 
  unsigned short b_buf_end;            // 
  unsigned short b_flip_irq;           // 
} gdsp_adpcmnbencoder;

typedef struct
{
  unsigned short srcliststart;         // 
  unsigned short srclistend;           // 
  unsigned short deststart;            // 
} gdsp_classddestinations;

typedef struct
{
  unsigned short srcliststart;         // 
  unsigned short srclistend;           // 
  unsigned short destliststart;        // 
  unsigned short codecmicgainoutsrc;   // 
  unsigned short codecdataoutsrc;      // 
  unsigned short codecmicgainoutdest;   // 
  unsigned short codecdataoutdest;     // 
} gdsp_codecdestinations;

typedef struct
{
  unsigned short srcstart;             // 
  unsigned short srcend;               // 
  unsigned short destliststart;        // 
  unsigned short src_ptr1;             // Src1: CODEC_MIC_GAIN_REG
  unsigned short src_ptr2;             // Src2: CODEC_DATA_REG
  unsigned short codecmicgainsrc;      // Temporary copy of CODEC_MIC_GAIN_REG
  unsigned short codecdatainsrc;       // Temporary copy of CODEC_DATA_IN_REG
} gdsp_codecsource;

typedef struct
{
  unsigned short value;                // Constant Value 32767/32768
} gdsp_constant;

typedef struct
{
  unsigned short srcliststart;         //
  unsigned short srclistend;           //
  unsigned short deststart;            //
  unsigned short scrptr0;              //
  unsigned short scrptr1;              //
  unsigned short scrptr2;              //
  unsigned short scrptr3;              //
} gdsp_pcmmasterdestinations;

typedef struct
{
  unsigned short srcstart;             //
  unsigned short srcend;               //
  unsigned short destliststart;        //
  unsigned short pcm0insrc;            // Temporary copy of DSP_PCM_IN0_REG
  unsigned short pcm1insrc;            // Temporary copy of DSP_PCM_IN1_REG
  unsigned short pcm2insrc;            // Temporary copy of DSP_PCM_IN2_REG
  unsigned short pcm3insrc;            // Temporary copy of DSP_PCM_IN3_REG
} gdsp_pcmsource;

typedef struct
{
  unsigned short in_ptr;               // DTMF signal input
  unsigned short argsc[16];            // ARGSIN and ARGCOS values for internal tone generation
  unsigned short attack;               // Power Detection attack time/rate
  unsigned short cspeed;               // Detector adaptation mu factor
  unsigned short max_fac1;             // Signal to inband interferer ratio
  unsigned short max_fac2;             // Signal to inband interferer peakhold ratio
  unsigned short levinp_fac;           // Signal to Noise Ratio
  unsigned short min_inplev;           // DTMF Signal level threshold
  unsigned short char_time;            // Symbol Detector ON time
  unsigned short cease_time;           // Symbol Detector OFF time
  unsigned short max_dur_diff;         // Maximum symbol duration difference between hi and lo frequency
  unsigned short grpcnt_ini;           // Symbol Detection predelay (after burst detection)
  unsigned short diffmax_fax;          // Burst detection (derivative) activation threshold
  unsigned short sincos[16];           // Sine/cosine generators working values
  unsigned short corr[16];             // DTMF Correlation coefficients
  unsigned short lev_inp;              // Input signal powerlevel
  unsigned short lev_err;              // Level of DTMF Error signal for dectector adaptation loop (total outband signal power)
  unsigned short low_index;            // Low Frequency index working value
  unsigned short low_timer;            // Low Frequency Symbol timer
  unsigned short low_scndmax;          // Low Frequency group second indband correlation maximum
  unsigned short high_index;           // High Frequency index working value
  unsigned short high_timer;           // High Frequency Symbol timer
  unsigned short high_scndmax;         // High Frequency group second indband correlation maximum
  unsigned short signal_timer;         // DTMF Signal presence timer
  unsigned short silence_timer;        // DTMF Signal pause timer
  unsigned short last_code;            // Detected DTMF Lo/Hi Frequency Index register
  unsigned short dtmf_err;             // Actual Error-signal for correlation
  unsigned short dummy3;               // Dummy parameter (unused)
  unsigned short index_cnt;            // Working value low index
  unsigned short index_cur;            // Working value high index
  unsigned short prev_max2;            // Peakhold of 2nd max for both groups
  unsigned short adapt_timer;          // DTMF Burst Detection predelay counter
  unsigned short diff_max;             // Derivative peak-hold for burst detection
  unsigned short index_out;            // IRQ Flag in MSB when successful DTMF detected
} gdsp_dtmfdetector;

typedef struct
{
  unsigned short in_ptr;               // Gain signal input
  unsigned short pre_attn;             // preattenuation factor
  unsigned short shift;                // preattenuation factor
  unsigned short post_attn;            // preattenuation factor
  unsigned short out;                  // Amplified/attenuated utput. Total gain: -1
} gdsp_gain;

typedef struct
{
  unsigned short lawin_ptr;            // A/Mu law coded input signal
  unsigned short lawb;                 // Input format -1
  unsigned short linear_out;           // Linear coded output signal
} gdsp_lawlin;

#define MIXER_ATTEN		0x2636		   // used for setting default p_dynmixer attenuation at -10.5dB
#define MIXER6_ATTEN	0x1989		   // used after muting p_dynmixer6 during paging for -14dB

typedef struct
{
  unsigned short ptr_ptr;              // Pointer to list of 6 input pointers
  unsigned short w_ptr;                // Pointer to list of 6 weight factors
  unsigned short n;                    // process n input channels.
  unsigned short attn;                 // Output attenuation factor 0.5
  unsigned short temp;                 // working value
  unsigned short out;                  // mixer output
  unsigned short inputs[7];            // inputs
  unsigned short weights[7];           // channel weights
} gdsp_mixer;

typedef struct
{
  unsigned short spkr_ptr;             // Pointer to speaker input array
  unsigned short mic_ptr;              // Pointer to microphone input array
  unsigned short out_ptr;              // Pointer to output array
  unsigned short twiddle_ptr;          // Pointer to twiddle table (ROM)
  unsigned short twiddle_size;         // Size of twiddle table
  unsigned short window_ptr;           // Pointer to window table(ROM)
  unsigned short window_size;          // Size of window table
  unsigned short fftbuf_spkr_ptr;      // Pointer to complex FFT buffer of speaker signal
  unsigned short fftbuf_mic_ptr;       // Pointer to complex FFT buffer of microphone signal
  unsigned short paecband_ptr;         // Pointer to band states structure
  unsigned short xpow_ptr;             // Pointer to array of speaker power spectrum coeffs
  unsigned short ypow_ptr;             // Pointer to array of mic power spectrum coeffs
  unsigned short ccxx_ptr;             // Pointer to array of speaker auto correlation coeffs
  unsigned short ccxy_ptr;             // Pointer to array of speaker and mic auto correlation coeffs
  unsigned short ccyy_ptr;             // Pointer to array of mic auto correlation coeffs
  unsigned short cc_ptr;               // Pointer to array of Wiener-coefficients (active gain filter) for spectral substraction
  unsigned short cc_af_ptr;            // Pointer to array of Wiener-coefficients (adapting gain filter) for spectral substraction
  unsigned short fftsize;              // Size of FFT (128)
  unsigned short framesize;            // Size of input frame (64)
  unsigned short fftscale;             // FFT scale factor
  unsigned short ifftscale;            // iFFT scale factor
  unsigned short fftmode;              // FFT mode
  unsigned short npart;                // Number of frequency bands
  unsigned short mode;                 // Mode word
  unsigned short delaycompspecs;       // Maximum expected delay of early echo in number of input frames
  unsigned short ibuf_size;            // Input buffer size
  unsigned short ibuf_idx;             // Input buffer read-index (one index for both input buffers)
  unsigned short obuf_size;            // Output buffer size
  unsigned short obuf_idx;             // Output buffer read index
  unsigned short init;                 // Number of frames with initial 'fast' convergence time constants, multiplied with -1
  unsigned short noiseestgainshft;     // Tx noise level estimation scaling factor
  unsigned short noiseestspkgainshft;   // Rx noise level estimation scaling factor
  unsigned short dtdcount_init;        // Double talk detection counter init value. Value is number of frames the DTD conditions must be true before adapting filter is copied to the active filter
  unsigned short gamma;                // Scalling parameter of the echo removal filter
  unsigned short cctc;                 // Time constant for the coloration effect filter (cross correlation and auto correlations)
  unsigned short beta;                 // Gain given to echo estimate to avoid under-estimation
  unsigned short attlimit;             // Attenuation Limit
  unsigned short dtdthr;               // Doubletalk Detector absolute MSE threshold (foreground filter)
  unsigned short dtdthr2;              // Doubletalk Detector relative MSE threshold (foreground filter vs background filter)
  unsigned short dtdthr3;              // Doubletalk Detector 2nd relative MSE threshold
  unsigned short dtdsmooth;            // Doubletalk Detector statistics estimation time constant
  unsigned short dtddecay;             // Doubletalk Detector coloration effect filter update speed
  unsigned short dtdwgain_full_thr;    // Doubletalk Detector absolute full band prediction gain threshold
  unsigned short dtdwgain_part_thr;    // Doubletalk Detector absolute subband prediction gain threshold
  unsigned short noiseest1;            // Noise Suppression attack time constant for noise level estimation
  unsigned short noiseest2;            // Noise Suppression release time constant for noise level estimation
  unsigned short noiseest3;            // Noise Suppression paramter
  unsigned short noiseattlimit;        // Noise Suppression attenuation factor
  unsigned short nsuppsmtra;           // Noise Suppression time constant for transient noise suppression gain smoothing
  unsigned short nsuppsmsta;           // Noise Suppression time constant for stationary noise suppression gain smoothing
  unsigned short nsstathr;             // Noise Suppression stationarity threshold
  unsigned short retainnoisethr1div;   // Rx noise retaining threshold
  unsigned short attlimitthr1div;      // Attenuation limit minimum threshold
  unsigned short smooththr;            // Gain Filter Smoothing control threshold
  unsigned short smoothdef;            // Gain Filter Smoothing control Rx mode time constant
  unsigned short smoothlow;            // Gain Filter Smoothing control Doubletalk mode time constant 1. Controls suppression time of room echo tail
  unsigned short smoothtop;            // Gain Filter Smoothing control Doubletalk mode time constant 2. Controls capture of early room echoes
  unsigned short winitial;             // Flag indicating use of initial or steady state parameters
  unsigned short dtdcount;             // Doubletalk Detection counter
  unsigned short wdelay;               // Estimated echo path delay for foreground filter
  unsigned short wdelay_af;            // Estimated echo path delay for background filter
  unsigned short wgain;                // Prediction gain of foreground filter
  unsigned short wgain_af;             // Prediction gain of background filter
  unsigned short erlenum;              // ERLE estimation numerator
  unsigned short erleden;              // ERLE estimation denominator
  unsigned short mse;                  // Mean Square error of foreground filter
  unsigned short mse_af;               // Mean Square error of background filter
  unsigned short msenrm;               // Normalisation value for MSE estimation
  unsigned short bandshift_ptr;        // Pointer to bandshift[npart] array
  unsigned short extra_shift;          // Additional shift for internal scaling
  unsigned short intshift_maxnorm;     // Headroom for internal dynamic scaling (16 - no of bits)
  unsigned short mic_shift_ptr;        // Pointer to RFFTD scale value when using external FFTs
  unsigned short spk_shift_ptr;        // Pointer to RFFTD scale value when using external FFTs
  unsigned short dummy; // to align cmpl_buf to 32 bit
  // HM : Next parameters are state variables and can be moved as needed (spkr, mic and out buffers can be placed with their respective CBUFFERS instead - Table 68 AN-D-129
  //unsigned short spkr_buf[84];         // Speaker input buffer array
  //unsigned short mic_buf[84];          // Microphone input buffer array
  //unsigned short out_buf[84];          // PAEC output buffer array
  unsigned short cmplx_buf[130];        // Complex FFT buffer
//  unsigned short window[64];           // Window table
  unsigned short xpow[48];             // Rx Signal Power spectrum array (with history)
  unsigned short ypow[12];             // Tx Signal Power spectrum
  unsigned short ccxx[48];             // Rx auto-correlation coefficients array (with history)
  unsigned short ccxy[48];             // Rx and Tx cross-correlation coefficients array
  unsigned short ccyy[12];             // Tx auto-correlation coefficients array
  unsigned short cc[48];               // Gainfilter coefficients array (foreground filter)
  unsigned short cc_af[48];            // Gainfilter coefficients array (background filter)
  unsigned short paec_subband_1[21];   // PAEC subband 1
  unsigned short paec_subband_2[21];   // PAEC subband 2
  unsigned short paec_subband_3[21];   // PAEC subband 3
  unsigned short paec_subband_4[21];   // PAEC subband 4
  unsigned short paec_subband_5[21];   // PAEC subband 5
  unsigned short paec_subband_6[21];   // PAEC subband 6
  unsigned short paec_subband_7[21];   // PAEC subband 7
  unsigned short paec_subband_8[21];   // PAEC subband 8
  unsigned short paec_subband_9[21];   // PAEC subband 9
  unsigned short paec_subband_10[21];   // PAEC subband 10
  unsigned short paec_subband_11[21];   // PAEC subband 11
  unsigned short paec_subband_12[21];   // PAEC subband 12
//  unsigned short paec_subband_13[21];   // PAEC subband 13
//  unsigned short paec_subband_14[21];   // PAEC subband 14
//  unsigned short paec_subband_15[21];   // PAEC subband 15
  unsigned short bandshift[15];
} gdsp_paec;

typedef struct
{
  unsigned short mode;                 // Buffer mode set to Playback operation
  unsigned short in_ptr;               // Buffer input (don't care in playback mode; input comes from CR16)
  unsigned short out_ptr;              // Output pointer
  unsigned short buffer_size;          // Buffer size 12 taps
  unsigned short buffer_ptr;           // Start of buffer
  unsigned short read_idx;             // Read index in buffer
  unsigned short write_idx;            // Write index in buffer
  unsigned short buffer_irq_size;      // IRQ flag set after %s samples (CR16 clears)
  unsigned short irq;                  // IRQ output signals 'buffer empty'
  unsigned short out;                  // Playback buffer Output
  unsigned short taps[200];             //unsigned short taps[12];             // Buffer Elements
} gdsp_playbackbuffer_12;

typedef struct
{
  unsigned short mode;                 // Buffer mode set to Playback operation
  unsigned short in_ptr;               // Buffer input (don't care in playback mode; input comes from CR16)
  unsigned short out_ptr;              // Output pointer
  unsigned short buffer_size;          // Buffer size 12 taps
  unsigned short buffer_ptr;           // Start of buffer
  unsigned short read_idx;             // Read index in buffer
  unsigned short write_idx;            // Write index in buffer
  unsigned short buffer_irq_size;      // IRQ flag set after %s samples (CR16 clears)
  unsigned short irq;                  // IRQ output signals 'buffer empty'
  unsigned short out;                  // Playback buffer Output
  unsigned short taps[560];            // unsigned short taps[560];             // Buffer Elements
} gdsp_delayline_560;

typedef struct
{
  unsigned short mode;                 // Buffer mode set to Playback operation
  unsigned short in_ptr;               // Buffer input (don't care in playback mode; input comes from CR16)
  unsigned short out_ptr;              // Output pointer
  unsigned short buffer_size;          // Buffer size 18 taps
  unsigned short buffer_ptr;           // Start of buffer
  unsigned short read_idx;             // Read index in buffer
  unsigned short write_idx;            // Write index in buffer
  unsigned short buffer_irq_size;      // IRQ flag set after %s samples (CR16 clears)
  unsigned short irq;                  // IRQ output signals 'buffer empty'
  unsigned short out;                  // Playback buffer Output
  unsigned short taps[18];             // Buffer Elements
} gdsp_playbackbuffer_18;

typedef struct
{
  unsigned short in_ptr;               // Input signal
  unsigned short fall;                 // Detector decay time 0.007s.
  unsigned short rise;                 // Detector attack time 0.004s.
  unsigned short out;                  // Output: Power level of input signal
} gdsp_wt_plevdet;

typedef struct
{
  unsigned short in_ptr;               // Input signal
  unsigned short fall;                 // Detector decay time 0.007s.
  unsigned short rise;                 // Detector attack time 0.004s.
  unsigned short out;                  // Output: Power level of input signal
} gdsp_plevdet;

typedef struct
{
  unsigned short mode;                 // Buffer mode set to Record operation
  unsigned short in_ptr;               // Buffer input
  unsigned short out_ptr;              // Output pointer (don't care for record mode)
  unsigned short buffer_size;          // Buffer size 128 taps
  unsigned short buffer_ptr;           // Start of buffer
  unsigned short read_idx;             // Read index in buffer
  unsigned short write_idx;            // Write index in buffer
  unsigned short buffer_irq_size;      // IRQ flag set after %s samples (CR16 clears)
  unsigned short irq;                  // IRQ output signals 'buffer full'
  unsigned short out;                  // Playback buffer Output
  unsigned short taps[200];            // Buffer Elements
} gdsp_recordbuffer_128;

typedef struct
{
  unsigned short mode;                 // Buffer mode set to Record operation
  unsigned short in_ptr;               // Buffer input
  unsigned short out_ptr;              // Output pointer (don't care for record mode)
  unsigned short buffer_size;          // Buffer size 18 taps
  unsigned short buffer_ptr;           // Start of buffer
  unsigned short read_idx;             // Read index in buffer
  unsigned short write_idx;            // Write index in buffer
  unsigned short buffer_irq_size;      // IRQ flag set after %s samples (CR16 clears)
  unsigned short irq;                  // IRQ output signals 'buffer full'
  unsigned short out;                  // Playback buffer Output
  unsigned short taps[18];             // Buffer Elements
} gdsp_recordbuffer_18;

typedef struct
{
  unsigned short tdetin;               // Single Tone Detector Input
  unsigned short argsc1;               // Corrected argcosinus value for the single tone detection
  unsigned short argsc2;               // Corrected argsinus value for the single tone detection
  unsigned short attack;               // Coeff averaging attack-rate 1/32 dB/ms
  unsigned short cspeed;               // Correlation coefficients update-speed 1/64
  unsigned short levinp_fac;           // Outband SNR threshold to activate detection
  unsigned short min_corramp;          // Signal level threshold (avoids intial false detections)
  unsigned short stepon;               // Step value for detection ON timer
  unsigned short stepoff;              // Step value for detection OFF timer
  unsigned short sincos[2];            // Sine/cosine generators working values
  unsigned short corr[2];              // Tone Correlation coefficients sin_n, cos_n
  unsigned short lev_inp;              // Input signal powerlevel
  unsigned short lev_err;              // Level of error signal dectector adaptation loop (total outband signal power)
  unsigned short err;                  // Error signal
  unsigned short cnt_out;              // Tone presence timer
  unsigned short corr_amp;             // Error signal
  unsigned short hysterese;            // IRQ Flag in MSB when successful single tone detected
  unsigned short hyst_irq;             // Detection irq. flag (sign, active for one frame)
} gdsp_singletonedetector;

typedef struct
{
  unsigned short in1_ptr;              // Input signal 1
  unsigned short in2_ptr;              // Input signal 2
  unsigned short in3_ptr;              // Attenuation factor input for MULTIN3
  unsigned short in1_atten;            // Attenuates MULTIN1 with 1
  unsigned short out;                  // Summator output
} gdsp_summator;

typedef struct
{
  unsigned short timerpreset1;         // Tones ON for 0.5s.
  unsigned short timerpreset2;         // Tones OFF for .1s.
  unsigned short argsin1_1;            // Tone1 Corrected argsin value for 500Hz
  unsigned short argcos1_1;            // Tone1 Corrected argcos value for 500Hz
  unsigned short t1att_1;              // Tone1 amplitude 0.5
  unsigned short argsin2_1;            // Tone2 Corrected argsin value for 1000Hz
  unsigned short argcos2_1;            // Tone2 Corrected argcos value for 1000Hz
  unsigned short t2att_1;              // Tone2 amplitude 0
  unsigned short argsin3_1;            // Tone3 Corrected argsin value for 1500Hz
  unsigned short argcos3_1;            // Tone3 Corrected argcos value for 1500Hz
  unsigned short t3att_1;              // Tone3 amplitude 0
  unsigned short cosi[3];              // Tone cosine outputs
  unsigned short sini[3];              // Tone sine outputs (initialised to -1)
  unsigned short timer1;               // Timer1 actual value
  unsigned short timer2;               // Timer2 actual value
  unsigned short argsin1_2;            // Working sin-value tone1
  unsigned short argcos1_2;            // Working cos-value tone1
  unsigned short t1att_2;              // Working attn-value tone1
  unsigned short argsin2_2;            // Working sin-value tone2
  unsigned short argcos2_2;            // Working cos-value tone2
  unsigned short t2att_2;              // Working attn-value tone2
  unsigned short argsin3_2;            // Working sin-value tone3
  unsigned short argcos3_2;            // Working cos-value tone3
  unsigned short t3att_2;              // Working attn-value tone3
  unsigned short tone_out;             // Tones output
} gdsp_tonegen;

typedef struct
{
  unsigned short outlvl_ptr;           // AGC Pdet level input
  unsigned short in_ptr;               // AGC signal input
  unsigned short threshold;            // AGC activation threshold 0.2
  unsigned short rbetaoff;             // AGC Decay time 63
  unsigned short rbetaon;              // AGC Attack time 63
  unsigned short out_scale;            // AGC Output gain ctrl word 0
  unsigned short attn;                 // Actual AGC attn factor (init 0)
  unsigned short out;                  // Gain-corrected output
} gdsp_agc;

typedef struct
{
  unsigned short in_ptr;               // Audio input
  unsigned short level_ptr;            // Output power feedback input for PlevDet
  unsigned short max_thresh;           // Max threshold 0.35; AGC factor decays
  unsigned short min_thresh;           // Min threshold 0.25; AGC factor attacks
  unsigned short toff_scale;           // AGC attack-slope sample-interval 0+1 samples
  unsigned short ton_scale;            // AGC decay-slope sample-interval 0+1 samples
  unsigned short clip;                 // AGC range (max attn 0.25)
  unsigned short toff;                 // AGC attack 0.0072215287952972
  unsigned short ton;                  // AGC decay 0.99283024777684
  unsigned short offcnt;               // AGC Attack working value
  unsigned short oncnt;                // AGC Decay working value
  unsigned short atten;                // AGC actual attn value (one-time init to 0.25)
  unsigned short out;                  // AGC Signal output
} gdsp_wt_hagc;

typedef struct
{
  unsigned short taps[20];            /* Buffer Elements*/
} dataArea_40;

typedef struct
{
  unsigned short event_ptr;           /* Event input (negative value activates counter)*/
  unsigned short cntstep;             /* Counter step value*/
  unsigned short saturate;            /* Saturate (-1) or Wrap (0) counter*/
  unsigned short cnt_upb;             /* Highest counter value (upper bound)*/
  unsigned short cnt_lwb;             /* Lowest counter value (lower bound)*/
  unsigned short irqval;              /* Counter interrupt flag*/
  unsigned short reset_ptr;           /* Counter reset register*/
  unsigned short count;               /* Actual counter value*/
  unsigned short irq_out;             /* Counter IRQ Flag*/
  unsigned short cntr_activate_val;   /* Reset input*/
} gdsp_durationcounter;

typedef struct
{
  unsigned short inputToCounter;
  unsigned short counter;
  unsigned short copycondition;   /* Condition to check if it is ok to copy*/

  unsigned short data0start;      /* Temp data2 start*/
  unsigned short data0end;        /* Temp data2 end*/
  unsigned short SB0start;        /* Speechbuffer0 start*/
  unsigned short SB2start;        /* Speechbuffer1 start */
  unsigned short SB2end;          /* Speechbuffer1 end*/
  unsigned short data2start;      /* Temp data1 start*/

  unsigned short data4start;      /* Temp data2 start*/
  unsigned short data4end;        /* Temp data2 end*/
  unsigned short SB4start;        /* Speechbuffer0 start*/
  unsigned short SB6start;        /* Speechbuffer1 start */
  unsigned short SB6end;          /* Speechbuffer1 end*/
  unsigned short data6start;      /* Temp data1 start*/

  unsigned short data8start;      /* Temp data2 start*/
  unsigned short data8end;        /* Temp data2 end*/
  unsigned short SB8start;        /* Speechbuffer0 start*/
  unsigned short SB10start;        /* Speechbuffer1 start */
  unsigned short SB10end;          /* Speechbuffer1 end*/
  unsigned short data10start;      /* Temp data1 start*/

  unsigned short data12start;      /* Temp data2 start*/
  unsigned short data12end;        /* Temp data2 end*/
  unsigned short SB12start;        /* Speechbuffer0 start*/
  unsigned short SB14start;        /* Speechbuffer1 start */
  unsigned short SB14end;          /* Speechbuffer1 end*/
  unsigned short data14start;      /* Temp data1 start*/

  unsigned short data16start;      /* Temp data2 start*/
  unsigned short data16end;        /* Temp data2 end*/
  unsigned short SB16start;        /* Speechbuffer0 start*/
  unsigned short SB18start;        /* Speechbuffer1 start */
  unsigned short SB18end;          /* Speechbuffer1 end*/
  unsigned short data18start;      /* Temp data1 start*/

  unsigned short data20start;      /* Temp data2 start*/
  unsigned short data20end;        /* Temp data2 end*/
  unsigned short SB20start;        /* Speechbuffer0 start*/
  unsigned short SB22start;        /* Speechbuffer1 start */
  unsigned short SB22end;          /* Speechbuffer1 end*/
  unsigned short data22start;      /* Temp data1 start*/

} copySpeecBuffers;

typedef struct
{
  unsigned short inputToCounter;
  unsigned short counter;
  unsigned short clearcondition;    /* Condition to check if it is ok to clear*/
  unsigned short sourceStart;          /* Start of copyP2P*/
  unsigned short sourceEnd;
  unsigned short destinationBegin;
  unsigned short pointer1;        /* Stop copyValue*/
  unsigned short pointer2;        /* Stop copyValue*/
  unsigned short pointer3;        /* Decoder 1 start */
  unsigned short pointer4;        /* Encoder 1 start*/
  unsigned short pointer5;        /* Decoder 2 start */
  unsigned short pointer6;        /* Encoder 2 start*/
  unsigned short pointer7;        /* Decoder 3 start */
  unsigned short pointer8;        /* Encoder 3 start */
  unsigned short pointer9;        /* Decoder 4 start */
  unsigned short pointer10;       /* Encoder 4 start */
  unsigned short pointer11;       /* Decoder 5 start */
  unsigned short pointer12;       /* Encoder 5 start */
  unsigned short pointer13;       /* Decoder 6 start */
  unsigned short pointer14;       /* Encoder 6 start */

  unsigned short pointer1dest;    /* Copycondition*/
  unsigned short pointer2dest;    /* Clearcondition*/
  unsigned short pointer3dest;    /* Decoder 1 buf_Ptr*/
  unsigned short pointer4dest;    /* Encoder 1 buf_Ptr*/
  unsigned short pointer5dest;    /* Decoder 2 buf_Ptr*/
  unsigned short pointer6dest;    /* Encoder 2 buf_Ptr*/
  unsigned short pointer7dest;    /* Decoder 3 buf_Ptr*/
  unsigned short pointer8dest;    /* Encoder 3 buf_Ptr*/
  unsigned short pointer9dest;    /* Decoder 4 buf_Ptr*/
  unsigned short pointer10dest;   /* Encoder 4 buf_Ptr*/
  unsigned short pointer11dest;   /* Decoder 5 buf_Ptr*/
  unsigned short pointer12dest;   /* Encoder 5 buf_Ptr*/
  unsigned short pointer13dest;   /* Decoder 6 buf_Ptr*/
  unsigned short pointer14dest;   /* Encoder 6 buf_Ptr*/
} clearPointers;

typedef struct
{
  unsigned short in1_ptr;              /* Conference input line 1*/
  unsigned short in2_ptr;              /* Conference input line 2*/
  unsigned short in3_ptr;              /* Conference input line 3*/
  unsigned short in4_ptr;              /* Conference input line 4*/
  unsigned short atten_c1;             /* line 1 attenuation factor 0.24*/
  unsigned short atten_c2;             /* line 2 attenuation factor 0.24*/
  unsigned short atten_c3;             /* line 3 attenuation factor 0.24*/
  unsigned short atten_c4;             /* line 4 attenuation factor 0.24*/
  unsigned short out1;                 /* Conference output line 1*/
  unsigned short out2;                 /* Conference output line 2*/
  unsigned short out3;                 /* Conference output line 3*/
  unsigned short out4;                 /* Conference output line 4*/
} gdsp_conference;

#endif
