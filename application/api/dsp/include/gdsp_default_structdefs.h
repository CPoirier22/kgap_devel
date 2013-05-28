#ifndef GDSP_DEFAULT_INITS_TYPEDEF_H
#define GDSP_DEFAULT_INITS_TYPEDEF_H

typedef struct
{
  unsigned short in_ptr;               /* Input*/
  unsigned short out;                  /* Absolute value output*/
} gdsp_default_absolutevalue;

typedef struct
{
  unsigned short srcliststart;         /* */
  unsigned short srclistend;           /* */
  unsigned short deststart;            /* */
  unsigned short adcs0copy;            /* */
  unsigned short adcs1copy;            /* */
} gdsp_default_adcsource;

typedef struct
{
  unsigned short g0_in1_ptr;           /* */
  unsigned short g0_mode;              /* */
  unsigned short g0_out1;              /* */
  unsigned short g0_sr1;               /* */
  unsigned short g0_a2r;               /* */
  unsigned short g0_a1r;               /* */
  unsigned short g0_dq0;               /* */
  unsigned short g0_dq1;               /* */
  unsigned short g0_dq2;               /* */
  unsigned short g0_dq3;               /* */
  unsigned short g0_dq4;               /* */
  unsigned short g0_dq5;               /* */
  unsigned short g0_br0;               /* */
  unsigned short g0_br1;               /* */
  unsigned short g0_br2;               /* */
  unsigned short g0_br3;               /* */
  unsigned short g0_br4;               /* */
  unsigned short g0_br5;               /* */
  unsigned short g0_dmsp;              /* */
  unsigned short g0_dmlp;              /* */
  unsigned short g0_apr;               /* */
  unsigned short g0_yup;               /* */
  unsigned short g0_ylp_lsb;           /* */
  unsigned short g0_ylp_msb;           /* */
  unsigned short g0_tdr;               /* */
  unsigned short g0_pk0;               /* */
  unsigned short g0_pk1;               /* */
  unsigned short g0_sr0;               /* */
  unsigned short g0_intlv_ptr;         /* */
  unsigned short b0_in_ptr1;           /* */
  unsigned short b0_in_ptr2;           /* */
  unsigned short b0_nr_bits1;          /* */
  unsigned short b0_nr_bits2;          /* */
  unsigned short b0_nr_bits3;          /* */
  unsigned short b0_swap_mode;         /* */
  unsigned short b0_new_val;           /* */
  unsigned short b0_new_bits;          /* */
  unsigned short b0_buf_ptr;           /* */
  unsigned short b0_buf_start;         /* */
  unsigned short b0_buf_end;           /* */
  unsigned short b0_flip_irq;          /* */
  unsigned short g1_in1_ptr;           /* */
  unsigned short g1_mode;              /* */
  unsigned short g1_out1;              /* */
  unsigned short g1_sr1;               /* */
  unsigned short g1_a2r;               /* */
  unsigned short g1_a1r;               /* */
  unsigned short g1_dq0;               /* */
  unsigned short g1_dq1;               /* */
  unsigned short g1_dq2;               /* */
  unsigned short g1_dq3;               /* */
  unsigned short g1_dq4;               /* */
  unsigned short g1_dq5;               /* */
  unsigned short g1_br0;               /* */
  unsigned short g1_br1;               /* */
  unsigned short g1_br2;               /* */
  unsigned short g1_br3;               /* */
  unsigned short g1_br4;               /* */
  unsigned short g1_br5;               /* */
  unsigned short g1_dmsp;              /* */
  unsigned short g1_dmlp;              /* */
  unsigned short g1_apr;               /* */
  unsigned short g1_yup;               /* */
  unsigned short g1_ylp_lsb;           /* */
  unsigned short g1_ylp_msb;           /* */
  unsigned short g1_tdr;               /* */
  unsigned short g1_pk0;               /* */
  unsigned short g1_pk1;               /* */
  unsigned short g1_sr0;               /* */
  unsigned short g1_intlv_ptr;         /* */
  unsigned short b1_in_ptr1;           /* */
  unsigned short b1_in_ptr2;           /* */
  unsigned short b1_nr_bits1;          /* */
  unsigned short b1_nr_bits2;          /* */
  unsigned short b1_nr_bits3;          /* */
  unsigned short b1_swap_mode;         /* */
  unsigned short b1_new_val;           /* */
  unsigned short b1_new_bits;          /* */
  unsigned short b1_buf_ptr;           /* */
  unsigned short b1_buf_start;         /* */
  unsigned short b1_buf_end;           /* */
  unsigned short b1_flip_irq;          /* */
} gdsp_default_adpcmdestinations;

typedef struct
{
  unsigned short b_nr_bits1;           /* */
  unsigned short b_nr_bits2;           /* */
  unsigned short b_nr_bits3;           /* */
  unsigned short b_swap_mode;          /* */
  unsigned short b_out_val;            /* */
  unsigned short b_out_bits;           /* */
  unsigned short b_buf_ptr;            /* */
  unsigned short b_buf_start;          /* */
  unsigned short b_buf_end;            /* */
  unsigned short b_flip_irq;           /* */
  unsigned short b_buffer_out1;        /* */
  unsigned short b_buffer_out2;        /* */
  unsigned short g_in1_ptr;            /* */
  unsigned short g_mode;               /* */
  unsigned short g_out1;               /* */
  unsigned short g_sr1;                /* */
  unsigned short g_a2r;                /* */
  unsigned short g_a1r;                /* */
  unsigned short g_dq[6];              /* */
  unsigned short g_br[6];              /* */
  unsigned short g_dmsp;               /* */
  unsigned short g_dmlp;               /* */
  unsigned short g_apr;                /* */
  unsigned short g_yup;                /* */
  unsigned short g_ylp_lsb;            /* */
  unsigned short g_ylp_msb;            /* */
  unsigned short g_tdr;                /* */
  unsigned short g_pk0;                /* */
  unsigned short g_pk1;                /* */
  unsigned short g_sr0;                /* */
  unsigned short g_intlv_ptr;          /* */
} gdsp_default_adpcmnbdecoder;

typedef struct
{
  unsigned short g_in1_ptr;            /* */
  unsigned short g_mode;               /* */
  unsigned short g_out1;               /* */
  unsigned short g_sr1;                /* */
  unsigned short g_a2r;                /* */
  unsigned short g_a1r;                /* */
  unsigned short g_dq[6];              /* */
  unsigned short g_br[6];              /* */
  unsigned short g_dmsp;               /* */
  unsigned short g_dmlp;               /* */
  unsigned short g_apr;                /* */
  unsigned short g_yup;                /* */
  unsigned short g_ylp_lsb;            /* */
  unsigned short g_ylp_msb;            /* */
  unsigned short g_tdr;                /* */
  unsigned short g_pk0;                /* */
  unsigned short g_pk1;                /* */
  unsigned short g_sr0;                /* */
  unsigned short g_intlv_ptr;          /* */
  unsigned short b_in_ptr1;            /* */
  unsigned short b_in_ptr2;            /* */
  unsigned short b_nr_bits1;           /* */
  unsigned short b_nr_bits2;           /* */
  unsigned short b_nr_bits3;           /* */
  unsigned short b_swap_mode;          /* */
  unsigned short b_new_val;            /* */
  unsigned short b_new_bits;           /* */
  unsigned short b_buf_ptr;            /* */
  unsigned short b_buf_start;          /* */
  unsigned short b_buf_end;            /* */
  unsigned short b_flip_irq;           /* */
} gdsp_default_adpcmnbencoder;

typedef struct
{
  unsigned short b_nr_bits1;           /* */
  unsigned short b_nr_bits2;           /* */
  unsigned short b_nr_bits3;           /* */
  unsigned short b_swap_mode;          /* */
  unsigned short b_out_val;            /* */
  unsigned short b_out_bits;           /* */
  unsigned short b_buf_ptr;            /* */
  unsigned short b_buf_start;          /* */
  unsigned short b_buf_end;            /* */
  unsigned short b_flip_irq;           /* */
  unsigned short b_buffer_out1;        /* */
  unsigned short b_buffer_out2;        /* */
  unsigned short g_in1_ptr;            /* */
  unsigned short g_mode;               /* */
  unsigned short g_out1;               /* */
  unsigned short g_sr1;                /* */
  unsigned short g_a2r;                /* */
  unsigned short g_a1r;                /* */
  unsigned short g_dq[6];              /* */
  unsigned short g_br[6];              /* */
  unsigned short g_dmsp;               /* */
  unsigned short g_dmlp;               /* */
  unsigned short g_apr;                /* */
  unsigned short g_yup;                /* */
  unsigned short g_ylp_lsb;            /* */
  unsigned short g_ylp_msb;            /* */
  unsigned short g_tdr;                /* */
  unsigned short g_pk0;                /* */
  unsigned short g_pk1;                /* */
  unsigned short g_sr0;                /* */
  unsigned short reserved[11];         /* */
  unsigned short g_intlv_ptr;          /* */
} gdsp_default_adpcmnbvqidecoder;

typedef struct
{
  unsigned short b0_nr_bits1;          /* */
  unsigned short b0_nr_bits2;          /* */
  unsigned short b0_nr_bits3;          /* */
  unsigned short b0_swap_mode;         /* */
  unsigned short b0_out_val;           /* */
  unsigned short b0_out_bits;          /* */
  unsigned short b0_buf_ptr;           /* */
  unsigned short b0_buf_start;         /* */
  unsigned short b0_buf_end;           /* */
  unsigned short b0_flip_irq;          /* */
  unsigned short b0_buffer_out1;       /* */
  unsigned short b0_buffer_out2;       /* */
  unsigned short g0_in1_ptr;           /* */
  unsigned short g0_mode;              /* */
  unsigned short g0_out1;              /* */
  unsigned short g0_sr1;               /* */
  unsigned short g0_a2r;               /* */
  unsigned short g0_a1r;               /* */
  unsigned short g0_dq0;               /* */
  unsigned short g0_dq1;               /* */
  unsigned short g0_dq2;               /* */
  unsigned short g0_dq3;               /* */
  unsigned short g0_dq4;               /* */
  unsigned short g0_dq5;               /* */
  unsigned short g0_br0;               /* */
  unsigned short g0_br1;               /* */
  unsigned short g0_br2;               /* */
  unsigned short g0_br3;               /* */
  unsigned short g0_br4;               /* */
  unsigned short g0_br5;               /* */
  unsigned short g0_dmsp;              /* */
  unsigned short g0_dmlp;              /* */
  unsigned short g0_apr;               /* */
  unsigned short g0_yup;               /* */
  unsigned short g0_ylp_lsb;           /* */
  unsigned short g0_ylp_msb;           /* */
  unsigned short g0_tdr;               /* */
  unsigned short g0_pk0;               /* */
  unsigned short g0_pk1;               /* */
  unsigned short g0_sr0;               /* */
  unsigned short g0_intlv_ptr;         /* */
  unsigned short b1_nr_bits1;          /* */
  unsigned short b1_nr_bits2;          /* */
  unsigned short b1_nr_bits3;          /* */
  unsigned short b1_swap_mode;         /* */
  unsigned short b1_out_val;           /* */
  unsigned short b1_out_bits;          /* */
  unsigned short b1_buf_ptr;           /* */
  unsigned short b1_buf_start;         /* */
  unsigned short b1_buf_end;           /* */
  unsigned short b1_flip_irq;          /* */
  unsigned short b1_buffer_out1;       /* */
  unsigned short b1_buffer_out2;       /* */
  unsigned short g1_in1_ptr;           /* */
  unsigned short g1_mode;              /* */
  unsigned short g1_out1;              /* */
  unsigned short g1_sr1;               /* */
  unsigned short g1_a2r;               /* */
  unsigned short g1_a1r;               /* */
  unsigned short g1_dq0;               /* */
  unsigned short g1_dq1;               /* */
  unsigned short g1_dq2;               /* */
  unsigned short g1_dq3;               /* */
  unsigned short g1_dq4;               /* */
  unsigned short g1_dq5;               /* */
  unsigned short g1_br0;               /* */
  unsigned short g1_br1;               /* */
  unsigned short g1_br2;               /* */
  unsigned short g1_br3;               /* */
  unsigned short g1_br4;               /* */
  unsigned short g1_br5;               /* */
  unsigned short g1_dmsp;              /* */
  unsigned short g1_dmlp;              /* */
  unsigned short g1_apr;               /* */
  unsigned short g1_yup;               /* */
  unsigned short g1_ylp_lsb;           /* */
  unsigned short g1_ylp_msb;           /* */
  unsigned short g1_tdr;               /* */
  unsigned short g1_pk0;               /* */
  unsigned short g1_pk1;               /* */
  unsigned short g1_sr0;               /* */
  unsigned short g1_intlv_ptr;         /* */
} gdsp_default_adpcmsource;

typedef struct
{
  unsigned short c_mode;               /* Buffer mode set to PLAYBACK operation*/
  unsigned short c_in_ptr;             /* input is not used in playback mode*/
  unsigned short c_out_ptr;            /* Output pointer*/
  unsigned short c_buffer_size;        /* buffer 2 samples for G722 processing*/
  unsigned short c_buffer_ptr;         /* Location of Playback buffer taps*/
  unsigned short c_read_idx;           /* Read index in buffer*/
  unsigned short c_write_idx;          /* Write index in buffer*/
  unsigned short c_buffer_irq_size;    /* Generate IRQ flag every 2nd sample*/
  unsigned short c_irq;                /* Generate IRQ flag every 2nd sample*/
  unsigned short c_out;                /* Playback output*/
  unsigned short s_in_ptr;             /* Shift input*/
  unsigned short s_shval_ptr;          /* Pointer to shift value*/
  unsigned short s_out;                /* Shift output*/
  unsigned short s_shval;              /* Shift value*/
  unsigned short b_nr_bits1;           /* */
  unsigned short b_nr_bits2;           /* */
  unsigned short b_nr_bits3;           /* */
  unsigned short b_swap_mode;          /* */
  unsigned short b_out_val;            /* */
  unsigned short b_out_bits;           /* */
  unsigned short b_buf_ptr;            /* */
  unsigned short b_buf_start;          /* */
  unsigned short b_buf_end;            /* */
  unsigned short b_flip_irq;           /* */
  unsigned short b_buffer_out1;        /* */
  unsigned short b_buffer_out2;        /* */
  unsigned short g_in1_ptr;            /* */
  unsigned short g_in2_ptr;            /* */
  unsigned short g_out1;               /* */
  unsigned short g_out2;               /* */
  unsigned short g_detl;               /* */
  unsigned short g_dl[7];              /* */
  unsigned short g_nbl;                /* */
  unsigned short g_pl[3];              /* */
  unsigned short g_szl;                /* */
  unsigned short g_rl[3];              /* */
  unsigned short g_al[3];              /* */
  unsigned short g_bl[7];              /* */
  unsigned short g_sl;                 /* */
  unsigned short g_spl;                /* */
  unsigned short g_deth;               /* */
  unsigned short g_dh[7];              /* */
  unsigned short g_nbh;                /* */
  unsigned short g_ph[3];              /* */
  unsigned short g_szh;                /* */
  unsigned short g_rh[3];              /* */
  unsigned short g_ah[3];              /* */
  unsigned short g_bh[7];              /* */
  unsigned short g_sh;                 /* */
  unsigned short g_sph;                /* */
  unsigned short d_ptr[24];            /* */
  unsigned short index_offset;         /* */
  unsigned short invqal_ptr;           /* */
  unsigned short invqah_ptr;           /* */
  unsigned short logscal_ptr;          /* */
  unsigned short logscah_ptr;          /* */
  unsigned short scalel_ptr;           /* */
  unsigned short invqbl_ptr;           /* */
  unsigned short h_ptr;                /* */
} gdsp_default_adpcmwbdecoder;

typedef struct
{
  unsigned short s_in_ptr;             /* Shift input*/
  unsigned short s_shval_ptr;          /* Pointer to shift value*/
  unsigned short s_out;                /* Shift output*/
  unsigned short s_shval;              /* Shift value*/
  unsigned short c_mode;               /* Buffer mode set to RECORD operation*/
  unsigned short c_in_ptr;             /* Delay Line input*/
  unsigned short c_out_ptr;            /* Output pointer*/
  unsigned short c_buffer_size;        /* buffer 2 samples for G722 processing*/
  unsigned short c_buffer_ptr;         /* Location of Record buffer taps*/
  unsigned short c_read_idx;           /* Read index in buffer*/
  unsigned short c_write_idx;          /* Write index in buffer*/
  unsigned short c_buffer_irq_size;    /* Generate IRQ flag every 2nd sample*/
  unsigned short c_irq;                /* Generate IRQ flag every 2nd sample*/
  unsigned short c_taps[2];            /* Taps buffer*/
  unsigned short g_in1_ptr;            /* */
  unsigned short g_in2_ptr;            /* */
  unsigned short g_out1;               /* */
  unsigned short g_out2;               /* */
  unsigned short g_detl;               /* */
  unsigned short g_dl[7];              /* */
  unsigned short g_nbl;                /* */
  unsigned short g_pl[3];              /* */
  unsigned short g_szl;                /* */
  unsigned short g_rl[3];              /* */
  unsigned short g_al[3];              /* */
  unsigned short g_bl[7];              /* */
  unsigned short g_sl;                 /* */
  unsigned short g_spl;                /* */
  unsigned short g_deth;               /* */
  unsigned short g_dh[7];              /* */
  unsigned short g_nbh;                /* */
  unsigned short g_ph[3];              /* */
  unsigned short g_szh;                /* */
  unsigned short g_rh[3];              /* */
  unsigned short g_ah[3];              /* */
  unsigned short g_bh[7];              /* */
  unsigned short g_sh;                 /* */
  unsigned short g_sph;                /* */
  unsigned short d_ptr[24];            /* */
  unsigned short index_offset;         /* */
  unsigned short quantl_ptr;           /* */
  unsigned short misil_ptr;            /* */
  unsigned short invqal_ptr;           /* */
  unsigned short invqah_ptr;           /* */
  unsigned short logscal_ptr;          /* */
  unsigned short logscah_ptr;          /* */
  unsigned short scalel_ptr;           /* */
  unsigned short h_ptr;                /* */
  unsigned short b_in_ptr1;            /* */
  unsigned short b_in_ptr2;            /* */
  unsigned short b_nr_bits1;           /* */
  unsigned short b_nr_bits2;           /* */
  unsigned short b_nr_bits3;           /* */
  unsigned short b_swap_mode;          /* */
  unsigned short b_new_val;            /* */
  unsigned short b_new_bits;           /* */
  unsigned short b_buf_ptr;            /* */
  unsigned short b_buf_start;          /* */
  unsigned short b_buf_end;            /* */
  unsigned short b_flip_irq;           /* */
} gdsp_default_adpcmwbencoder;

typedef struct
{
  unsigned short ec_bypassin_ptr;      /* Echo canceller bypass input (not used)*/
  unsigned short hf_bypassin_ptr;      /* Handsfree bypass input*/
  unsigned short sw_rxin_ptr;          /* AECP Rx Input*/
  unsigned short sw_txin_ptr;          /* AECP Tx Input*/
  unsigned short bypass_enable;        /* En/Disable for Echo Canceller bypass in MSB (not used)*/
  unsigned short gains;                /* AEC internal gains settings mode word*/
  unsigned short nr_taps;              /* 0.015625 FIR filter taps*/
  unsigned short rcv_att;              /* Echo Canceller input attenuation 0.99996948242188 dB*/
  unsigned short tx_lev_offset;        /* Echo Canceller Tx level-offset 0.000976*/
  unsigned short rat0;                 /* mu0 <> Freeze decision ratio 0.05*/
  unsigned short rat2;                 /* mu0 <> mu1/mu2/mu3 decision ratio 0.25*/
  unsigned short tl1;                  /* mu0 <> mu1 decision level 0.0078125*/
  unsigned short tl2;                  /* mu1 <> mu2 decision level 0.125*/
  unsigned short tl3;                  /* mu2 <> mu3 decision level 0.25*/
  unsigned short tl4;                  /* VAD freeze level 0.01*/
  unsigned short u0_0;                 /* Mu0_0 = 0.00122: Update speed in double-talk mode, set 0*/
  unsigned short u0_1;                 /* Mu0_0 = 0.00122: Update speed in double-talk mode, set 1*/
  unsigned short u1_0;                 /* Mu1_0 = 0.0078: Update speed in single-talk mode, small signals, set 0*/
  unsigned short u1_1;                 /* Mu1_1 = 0.0078: Update speed in single-talk mode, small signals, set 1*/
  unsigned short u2_0;                 /* Mu2_0 = 0.00195: Update speed in single-talk mode, medium signals, set 0*/
  unsigned short u2_1;                 /* Mu2_1 = 0.00195: Update speed in single-talk mode, medium signals, set 1*/
  unsigned short u3_0;                 /* Mu3_0 = 0.00123: Update speed in single-talk mode, large signals, set 0*/
  unsigned short u3_1;                 /* Mu3_1 = 0.00123: Update speed in single-talk mode, large signals, set 1*/
  unsigned short dummyparams1[10];     /* The HFREE-AGC is disabled in the AEC, these parameters not used*/
  unsigned short codhigain;            /* HFree IO-gains mode word. Must be fixed to 0x0000.*/
  unsigned short codlogain;            /* HFree IO-gains mode word. Must be fixed to 0x0000.*/
  unsigned short dummyparams2[4];      /* The HFREE-AGC is disabled in the AEC, these parameters not used*/
  unsigned short idlecntini;           /* HFREE Switch to IDLE mode predelay 0.015625*/
  unsigned short idlecntini2;          /* HFREE Scalefactor for switch-to-idle attack/decay-time*/
  unsigned short idleratio;            /* HFREE Ratio -1 determines switch from IDLE to RX/TX*/
  unsigned short noisemargin;          /* SNR -1 for voice activity detection*/
  unsigned short offrx;                /* Absolute RX noise-floor 328/32768 VAD*/
  unsigned short offtx;                /* Absolute TX noise-floor 328/32768 VAD*/
  unsigned short parx_fall;            /* Power detector of signal to speaker, decay 0.01555*/
  unsigned short parx_rise;            /* Power detector of signal to speaker, attack 0.0311*/
  unsigned short patx_fall;            /* Power detector of signal from mic, decay 0.01555*/
  unsigned short patx_rise;            /* Power detector of signal from mic, attack 0.0311*/
  unsigned short plrx_fall;            /* Power detector of signal from line, decay 0.01555*/
  unsigned short plrx_rise;            /* Power detector of signal from line, attack 0.0311*/
  unsigned short plrx_scale;           /* Scale-factor 0.74989420933246 PLRX/PLTX ratio*/
  unsigned short plrx_scale2;          /* Scale-factor 0.99996948242188 PLRX/PATX ratio*/
  unsigned short pltx_fall;            /* Power detector of signal to line, decay 0.01555*/
  unsigned short pltx_rise;            /* Power detector of signal to line, attack 0.0311*/
  unsigned short pnrx_cntini;          /* Noise level detector of signal from line, counter init value*/
  unsigned short pnrx_fall;            /* Noise level detector of signal from line, decay 0.0011865*/
  unsigned short pnrx_max;             /* Noise level detector of signal from line, clip level 0.01*/
  unsigned short pnrx_rise;            /* Noise level detector of signal from line, attack 0.97617270573399*/
  unsigned short pntx_cntini;          /* Noise level detector of signal from mic, counter init value*/
  unsigned short pntx_fall;            /* Noise level detector of signal from mic, decay 0.0011865*/
  unsigned short pntx_max;             /* Noise level detector of signal from mic, clip level 0.01*/
  unsigned short pntx_rise;            /* Noise level detector of signal from mic, attack 0.97617270573399*/
  unsigned short prxaec_in_fall;       /* Power detector of signal from line, decay 0.01555*/
  unsigned short prxaec_in_rise;       /* Power detector of signal from line, attack 0.0311*/
  unsigned short prxaec_out_fall;      /* Power detector of signal to mic, decay 0.01555*/
  unsigned short prxaec_out_rise;      /* Power detector of signal to mic, attack 0.0311*/
  unsigned short ptxaec_out_fall;      /* Power detector of signal to line, decay 0.01555*/
  unsigned short ptxaec_out_rise;      /* Power detector of signal to line, attack 0.0311*/
  unsigned short rxout_att;            /* Rx Output gain mantissa 0.99996948242188*/
  unsigned short rxout_gain_shl;       /* Rx Output gain base 0 (powers of 2 in msb's)*/
  unsigned short rxratio;              /* Ratio -0.1 PARX/PATX determines switch Rx to TX mode*/
  unsigned short rxtxcntini;           /* HFREE RX <> TX switch predelay*/
  unsigned short switch_bypass;        /* En/Disable for HFREE bypass in MSB (not used)*/
  unsigned short swrxin_att;           /* Rx Input gain mantissa 0.99996948242188*/
  unsigned short swrxin_gain_shl;      /* Rx Input gain 0 base (powers of 2 in msb's)*/
  unsigned short swtxin_att;           /* Tx Input gain mantissa 0.99996948242188*/
  unsigned short swtxin_gain_shl;      /* Tx Input gain 0 base (powers of 2 in msb's)*/
  unsigned short supmin;               /* Smallest suppression factor 0.014125375446228 (max suppression level)*/
  unsigned short supmin_attaecp_fall;   /* Convergence Min-Estimator decay rate 0.98855309465694 dB/ms*/
  unsigned short supmin_attaecp_idle;   /* Convergence Estimator Freeze mode decay rate 0.99995682746147 dB/ms*/
  unsigned short supmin_attaecp_margin;   /* Convergence Min-Estimator to Input ratio 0.50118723362727 dB*/
  unsigned short supmin_attaecp_min;   /* Convergence Min-Estimator floor 0.014125375446228*/
  unsigned short supmin_attaecp_rise;   /* Convergence Min-Estimator attack rate %s dB/ms*/
  unsigned short suptidleoff;          /* Suppressor attack time (IDLE -> RX/TX)*/
  unsigned short suptidleon;           /* Suppressor decay time  (RX/TX -> IDLE)*/
  unsigned short suptoff;              /* Suppressor attack time  (RX <> TX)*/
  unsigned short supton;               /* Suppressor release time  (RX <> TX)*/
  unsigned short txout_att;            /* Tx Output gain mantissa 0.99996948242188*/
  unsigned short txout_gain_shl;       /* Tx Output gain base 0 (powers of 2 in msb's)*/
  unsigned short txratio;              /* Ratio -1 PLRX/PLTX determines switch TX to RX mode*/
  unsigned short vad_bypass;           /* En/Disable for VAD bypass in MSB (not used)*/
  unsigned short vad_select;           /* Selection for alternate VAD in MSB (not used)*/
  unsigned short peak_fall;            /* Convergence Max-Estimator decay rate -0.042254764882759 dB/ms*/
  unsigned short peak_ratio;           /* Convergence Max-Estimator to Input ratio -0.66834391756861 dB*/
  unsigned short coef_ptr;             /* Start of coefficients buffer (directly after param-block)*/
  unsigned short taps_ptr;             /* Start of taps buffer (directly after coefficients-buffer)*/
  unsigned short patx_ptr;             /* Input for PATX power-detector to internal HFREE*/
  unsigned short plrx_ptr;             /* Input for PLRX power-detector to internal HFREE*/
  unsigned short err;                  /* Echo Canceller error signal*/
  unsigned short out;                  /* Echo Canceller output signal (to HFREE)*/
  unsigned short tri_start1;           /* Start location of canceller 0 taps-buffer  (must be right behind EC1 buffer, bfr size is always 32 taps)*/
  unsigned short tri_start2;           /* Start location of canceller 1 taps-buffer*/
  unsigned short dummystates1[4];      /* The HFREE-AGC is disabled in the AEC, these parameters are not used*/
  unsigned short atrx;                 /* Working value line-attn (init 0.1188502227437 = (1 + Supmin)/2 )*/
  unsigned short attx;                 /* Working value mic-attn (init 0.1188502227437= (1 + Supmin)/2 )*/
  unsigned short cgain;                /* Working value (init 0)*/
  unsigned short dummystates2[2];      /* The HFREE-AGC is disabled in the AEC, these parameters are not used*/
  unsigned short idlecnt;              /* Working value idle-counter*/
  unsigned short parxin;               /* Working value PARX*/
  unsigned short patxin;               /* Working value PATX*/
  unsigned short plrxin;               /* Working value PLRX*/
  unsigned short pltxin;               /* Working value PLTX*/
  unsigned short pnrx_cnt;             /* Working value PNRX noise counter*/
  unsigned short pnrxin;               /* Working value PNRX*/
  unsigned short pntx_cnt;             /* Working value PTRX noise counter*/
  unsigned short pntxin;               /* Working value PNTX*/
  unsigned short prx_gamma_fall;       /* AEC decay rate*/
  unsigned short prx_gamma_rise;       /* AEC attack rate*/
  unsigned short ptxaec_in;            /* Working value PTX*/
  unsigned short ptxaec_out;           /* Working value PTX*/
  unsigned short ptxaec_out_exp;       /* Enhanced precision Working value PTX: exponent*/
  unsigned short ptxaec_out_man;       /* Enhanced precision Working value PTX: mantissa*/
  unsigned short prxaec_out;           /* Working value PRX*/
  unsigned short rxaec_out;            /* Unamplified Rx Output (to speaker)*/
  unsigned short rxtxcnt;              /* Working value rx/tx predelay counter*/
  unsigned short sprx;                 /* Working value line speech activity detection*/
  unsigned short sptx;                 /* Working value mic speech activity detection*/
  unsigned short sw_rxin_scale;        /* Working value amplified RX input*/
  unsigned short sw_txin_scale;        /* Working value amplified TX input*/
  unsigned short supmin_attaecp;       /* Working value Min-Estimator level*/
  unsigned short supmin_attaecppeak;   /* Working value Max-Estimator level*/
  unsigned short supmin_aec;           /* Working value actual suppression level*/
  unsigned short supmin_man;           /* Working value mantissa actual suppression level*/
  unsigned short txmode;               /* RX/TX mode indication (<0:TX, >=0:RX)*/
  unsigned short txout;                /* Unamplified Output to line*/
  unsigned short rx_out;               /* Rx Output (to speaker)*/
  unsigned short tx_out;               /* Tx Output (to Line)*/
  unsigned short ci[512];              /* Echo Canceller 0+1 coeff-buffer: 512 coefficients*/
  unsigned short tri[512];             /* Echo Canceller 0+1 taps-buffer: 512 taps*/
} gdsp_default_aec_512;

typedef struct
{
  unsigned short copy_srcstart;        /* */
  unsigned short copy_srcend;          /* */
  unsigned short copy_deststart;       /* */
  unsigned short copy_mu_src1;         /* Fetch new mu value*/
  unsigned short copy_mu_src2;         /* Fetch new mu value*/
  unsigned short copy_mu_src3;         /* Fetch new mu value*/
  unsigned short copy_mu_src4;         /* Fetch new mu value*/
  unsigned short copy_mu_dest1;        /* Store at AECu0_0*/
  unsigned short copy_mu_dest2;        /* And store at AECu0_1*/
  unsigned short copy_mu_dest3;        /* And store at AECu1_0*/
  unsigned short copy_mu_dest4;        /* And store at AECu1_1*/
  unsigned short ec_bypassin_ptr;      /* Echo canceller bypass input (not used)*/
  unsigned short hf_bypassin_ptr;      /* Handsfree bypass input*/
  unsigned short sw_rxin_ptr;          /* AECP Rx Input*/
  unsigned short sw_txin_ptr;          /* AECP Tx Input*/
  unsigned short bypass_enable;        /* En/Disable for Echo Canceller bypass in MSB (not used)*/
  unsigned short gains;                /* AEC internal gains settings mode word*/
  unsigned short nr_taps;              /* 0.015625 FIR filter taps*/
  unsigned short rcv_att;              /* Echo Canceller input attenuation 0.99996948242188 dB*/
  unsigned short tx_lev_offset;        /* Echo Canceller Tx level-offset -0.005*/
  unsigned short rat0;                 /* mu0 <> Freeze decision ratio 0.01*/
  unsigned short rat2;                 /* mu0 <> mu1/mu2/mu3 decision ratio 0.99996*/
  unsigned short tl1;                  /* mu0 <> mu1 decision level 0.0625*/
  unsigned short tl2;                  /* mu1 <> mu2 decision level 0.125*/
  unsigned short tl3;                  /* mu2 <> mu3 decision level 0.33*/
  unsigned short tl4;                  /* VAD freeze level 0.01*/
  unsigned short u0_0;                 /* Mu0_0 = 0.00122: Update speed in double-talk mode, set 0*/
  unsigned short u0_1;                 /* Mu0_0 = 0.00122: Update speed in double-talk mode, set 1*/
  unsigned short u1_0;                 /* Mu1_0 = 0.01: Update speed in single-talk mode, small signals, set 0*/
  unsigned short u1_1;                 /* Mu1_1 = 0.01: Update speed in single-talk mode, small signals, set 1*/
  unsigned short u2_0;                 /* Mu2_0 = 0.1: Update speed in single-talk mode, medium signals, set 0*/
  unsigned short u2_1;                 /* Mu2_1 = 0.1: Update speed in single-talk mode, medium signals, set 1*/
  unsigned short u3_0;                 /* Mu3_0 = 0.00123: Update speed in single-talk mode, large signals, set 0*/
  unsigned short u3_1;                 /* Mu3_1 = 0.00123: Update speed in single-talk mode, large signals, set 1*/
  unsigned short dummyparams1[10];     /* The HFREE-AGC is disabled in the AEC, these parameters not used*/
  unsigned short codhigain;            /* HFree IO-gains mode word. Must be fixed to 0x0000.*/
  unsigned short codlogain;            /* HFree IO-gains mode word. Must be fixed to 0x0000.*/
  unsigned short dummyparams2[4];      /* The HFREE-AGC is disabled in the AEC, these parameters not used*/
  unsigned short idlecntini;           /* HFREE Switch to IDLE mode predelay 0.06103515625*/
  unsigned short idlecntini2;          /* HFREE Scalefactor for switch-to-idle attack/decay-time*/
  unsigned short idleratio;            /* HFREE Ratio -1 determines switch from IDLE to RX/TX*/
  unsigned short noisemargin;          /* SNR -0.70794578438414 for voice activity detection*/
  unsigned short offrx;                /* Absolute RX noise-floor .0045 VAD*/
  unsigned short offtx;                /* Absolute TX noise-floor .01 VAD*/
  unsigned short parx_fall;            /* Power detector of signal to speaker, decay 0.05*/
  unsigned short parx_rise;            /* Power detector of signal to speaker, attack 0.001*/
  unsigned short patx_fall;            /* Power detector of signal from mic, decay 0.05*/
  unsigned short patx_rise;            /* Power detector of signal from mic, attack 0.001*/
  unsigned short plrx_fall;            /* Power detector of signal from line, decay 0.05*/
  unsigned short plrx_rise;            /* Power detector of signal from line, attack 0.001*/
  unsigned short plrx_scale;           /* Scale-factor 0.99996948242188 PLRX/PLTX ratio*/
  unsigned short plrx_scale2;          /* Scale-factor 0.3981071705535 PLRX/PATX ratio*/
  unsigned short pltx_fall;            /* Power detector of signal to line, decay 0.05*/
  unsigned short pltx_rise;            /* Power detector of signal to line, attack 0.001*/
  unsigned short pnrx_cntini;          /* Noise level detector of signal from line, counter init value*/
  unsigned short pnrx_fall;            /* Noise level detector of signal from line, decay 0.004*/
  unsigned short pnrx_max;             /* Noise level detector of signal from line, clip level 0.0032*/
  unsigned short pnrx_rise;            /* Noise level detector of signal from line, attack 0.98734043051534*/
  unsigned short pntx_cntini;          /* Noise level detector of signal from mic, counter init value*/
  unsigned short pntx_fall;            /* Noise level detector of signal from mic, decay 0.004*/
  unsigned short pntx_max;             /* Noise level detector of signal from mic, clip level 0.0032*/
  unsigned short pntx_rise;            /* Noise level detector of signal from mic, attack 0.98734043051534*/
  unsigned short prxaec_in_fall;       /* Power detector of signal from line, decay 0.05*/
  unsigned short prxaec_in_rise;       /* Power detector of signal from line, attack 0.001*/
  unsigned short prxaec_out_fall;      /* Power detector of signal to mic, decay 0.05*/
  unsigned short prxaec_out_rise;      /* Power detector of signal to mic, attack 0.001*/
  unsigned short ptxaec_out_fall;      /* Power detector of signal to line, decay 0.05*/
  unsigned short ptxaec_out_rise;      /* Power detector of signal to line, attack 0.001*/
  unsigned short rxout_att;            /* Rx Output gain mantissa 0.99996948242188*/
  unsigned short rxout_gain_shl;       /* Rx Output gain base 0 (powers of 2 in msb's)*/
  unsigned short rxratio;              /* Ratio -0.3981071705535 PARX/PATX determines switch Rx to TX mode*/
  unsigned short rxtxcntini;           /* HFREE RX <> TX switch predelay*/
  unsigned short switch_bypass;        /* En/Disable for HFREE bypass in MSB (not used)*/
  unsigned short swrxin_att;           /* Rx Input gain mantissa 0.99996948242188*/
  unsigned short swrxin_gain_shl;      /* Rx Input gain 0 base (powers of 2 in msb's)*/
  unsigned short swtxin_att;           /* Tx Input gain mantissa 0.99996948242188*/
  unsigned short swtxin_gain_shl;      /* Tx Input gain 0 base (powers of 2 in msb's)*/
  unsigned short supmin;               /* Smallest suppression factor 0.019952623149689 (max suppression level)*/
  unsigned short supmin_attaecp_fall;   /* Convergence Min-Estimator decay rate 0.98855309465694 dB/ms*/
  unsigned short supmin_attaecp_idle;   /* Convergence Estimator Freeze mode decay rate 0.99998560894672 dB/ms*/
  unsigned short supmin_attaecp_margin;   /* Convergence Min-Estimator to Input ratio 0.63095734448019 dB*/
  unsigned short supmin_attaecp_min;   /* Convergence Min-Estimator floor 0.019952623149689*/
  unsigned short supmin_attaecp_rise;   /* Convergence Min-Estimator attack rate %s dB/ms*/
  unsigned short suptidleoff;          /* Suppressor attack time (IDLE -> RX/TX)*/
  unsigned short suptidleon;           /* Suppressor decay time  (RX/TX -> IDLE)*/
  unsigned short suptoff;              /* Suppressor attack time  (RX <> TX)*/
  unsigned short supton;               /* Suppressor release time  (RX <> TX)*/
  unsigned short txout_att;            /* Tx Output gain mantissa 0.99996948242188*/
  unsigned short txout_gain_shl;       /* Tx Output gain base 0 (powers of 2 in msb's)*/
  unsigned short txratio;              /* Ratio -1 PLRX/PLTX determines switch TX to RX mode*/
  unsigned short vad_bypass;           /* En/Disable for VAD bypass in MSB (not used)*/
  unsigned short vad_select;           /* Selection for alternate VAD in MSB (not used)*/
  unsigned short peak_fall;            /* Convergence Max-Estimator decay rate -0.042254764882759 dB/ms*/
  unsigned short peak_ratio;           /* Convergence Max-Estimator to Input ratio -0.63095734448019 dB*/
  unsigned short coef_ptr;             /* Start of coefficients buffer (directly after param-block)*/
  unsigned short taps_ptr;             /* Start of taps buffer (directly after coefficients-buffer)*/
  unsigned short patx_ptr;             /* Input for PATX power-detector to internal HFREE*/
  unsigned short plrx_ptr;             /* Input for PLRX power-detector to internal HFREE*/
  unsigned short err;                  /* Echo Canceller error signal*/
  unsigned short out;                  /* Echo Canceller output signal (to HFREE)*/
  unsigned short tri_start1;           /* Start location of canceller 0 taps-buffer  (must be right behind EC1 buffer, bfr size is always 32 taps)*/
  unsigned short tri_start2;           /* Start location of canceller 1 taps-buffer*/
  unsigned short dummystates1[4];      /* The HFREE-AGC is disabled in the AEC, these parameters are not used*/
  unsigned short atrx;                 /* Working value line-attn (init 0.14125375446228 = (1 + Supmin)/2 )*/
  unsigned short attx;                 /* Working value mic-attn (init 0.14125375446228= (1 + Supmin)/2 )*/
  unsigned short cgain;                /* Working value (init 0)*/
  unsigned short dummystates2[2];      /* The HFREE-AGC is disabled in the AEC, these parameters are not used*/
  unsigned short idlecnt;              /* Working value idle-counter*/
  unsigned short parxin;               /* Working value PARX*/
  unsigned short patxin;               /* Working value PATX*/
  unsigned short plrxin;               /* Working value PLRX*/
  unsigned short pltxin;               /* Working value PLTX*/
  unsigned short pnrx_cnt;             /* Working value PNRX noise counter*/
  unsigned short pnrxin;               /* Working value PNRX*/
  unsigned short pntx_cnt;             /* Working value PTRX noise counter*/
  unsigned short pntxin;               /* Working value PNTX*/
  unsigned short prx_gamma_fall;       /* AEC decay rate*/
  unsigned short prx_gamma_rise;       /* AEC attack rate*/
  unsigned short prxaec_in;            /* Working value PRX*/
  unsigned short prxaec_out;           /* Working value PRX*/
  unsigned short prxaec_out_exp;       /* Enhanced precision Working value PRX: exponent*/
  unsigned short prxaec_out_man;       /* Enhanced precision Working value PRX: mantissa*/
  unsigned short ptxaec_out;           /* Working value PTX*/
  unsigned short rxaec_out;            /* Unamplified Rx Output (to speaker)*/
  unsigned short rxtxcnt;              /* Working value rx/tx predelay counter*/
  unsigned short sprx;                 /* Working value line speech activity detection*/
  unsigned short sptx;                 /* Working value mic speech activity detection*/
  unsigned short sw_rxin_scale;        /* Working value amplified RX input*/
  unsigned short sw_txin_scale;        /* Working value amplified TX input*/
  unsigned short supmin_attaecp;       /* Working value Min-Estimator level*/
  unsigned short supmin_attaecppeak;   /* Working value Max-Estimator level*/
  unsigned short supmin_aec;           /* Working value actual suppression level*/
  unsigned short supmin_man;           /* Working value mantissa actual suppression level*/
  unsigned short txmode;               /* RX/TX mode indication (<0:TX, >=0:RX)*/
  unsigned short txout;                /* Unamplified Output to line*/
  unsigned short rx_out;               /* Rx Output (to speaker)*/
  unsigned short tx_out;               /* Tx Output (to Line)*/
  unsigned short ci[512];              /* Echo Canceller 0+1 coeff-buffer: 512 coefficients*/
  unsigned short tri[512];             /* Echo Canceller 0+1 taps-buffer: 512 taps*/
} gdsp_default_aecwithmuinput_512;

typedef struct
{
  unsigned short outlvl_ptr;           /* AGC Pdet level input*/
  unsigned short in_ptr;               /* AGC signal input*/
  unsigned short threshold;            /* AGC activation threshold 0.2*/
  unsigned short rbetaoff;             /* AGC Decay time 63*/
  unsigned short rbetaon;              /* AGC Attack time 63*/
  unsigned short out_scale;            /* AGC Output gain ctrl word 0*/
  unsigned short attn;                 /* Actual AGC attn factor (init 0)*/
  unsigned short out;                  /* Gain-corrected output*/
} gdsp_default_agc;

typedef struct
{
  unsigned short in_ptr;               /* CODEC Signal Power level input*/
  unsigned short gaindec;              /* Gain decrement step -10/32768 for CODEC Gain*/
  unsigned short gaininc;              /* Gain increment step 10/32768 for CODEC Gain*/
  unsigned short lvlmax;               /* Threshold 0.55 for decrementing MIC Gain*/
  unsigned short lvlmin;               /* Threshold 0.5 for decrementing MIC Gain*/
  unsigned short micmax;               /* Maximum bound .6 for MIC Gain*/
  unsigned short micmin;               /* Minimum bound 0.3 for MIC Gain*/
  unsigned short micgain;              /* MIC Gain value (copy to CODEC_MIC_GAIN register)*/
} gdsp_default_analogagc;

typedef struct
{
  unsigned short in1_ptr;              /* AND input 1*/
  unsigned short in2_ptr;              /* AND input 2*/
  unsigned short out;                  /* AND output*/
} gdsp_default_and;

typedef struct
{
  unsigned short in_ptr;               /* Filter input*/
  unsigned short c0;                   /* 1st coefficient of array [0.495945558  0.986737445 0.495945558 -0.987816298 -0.503172367]*/
  unsigned short c1;                   /* 2nd coefficient of array [0.495945558  0.986737445 0.495945558 -0.987816298 -0.503172367]*/
  unsigned short c2;                   /* 3rd coefficient of array [0.495945558  0.986737445 0.495945558 -0.987816298 -0.503172367]*/
  unsigned short c3;                   /* 4th coefficient of array [0.495945558  0.986737445 0.495945558 -0.987816298 -0.503172367]*/
  unsigned short c4;                   /* 5th coefficient of array [0.495945558  0.986737445 0.495945558 -0.987816298 -0.503172367]*/
  unsigned short in_att;               /* Input attenuation factor .5*/
  unsigned short outgains;             /* Output-gain 6 dB*/
  unsigned short z1;                   /* filter tap*/
  unsigned short z1o;                  /* filter tap*/
  unsigned short z2;                   /* filter tap*/
  unsigned short z2o;                  /* filter tap*/
  unsigned short out;                  /* Filter output*/
} gdsp_default_biquadfilter;

typedef struct
{
  unsigned short in_ptr;               /* CAS Detector input*/
  unsigned short argsin_l;             /* Sine constant for CAS lo-tone: 2130Hz*/
  unsigned short argcos_l;             /* Cosine constant for CAS lo-tone: 2130Hz*/
  unsigned short argsin_h;             /* Sine constant for CAS lo-tone: 2750Hz*/
  unsigned short argcos_h;             /* Cosine constant for CAS lo-tone: 2750Hz*/
  unsigned short cspeed;               /* Correlation convergence speed-factor 1365/32768   % 0x0555*/
  unsigned short levtcnst;             /* Timeconstant 0.0625 for lo- and hi-level detection*/
  unsigned short bglevtcnst;           /* Timeconstant 0.0625 for background detection*/
  unsigned short bglevstepsz;          /* Step factor 0.25 for background level detection*/
  unsigned short scale_thresh;         /* Scaling factor 0.25 % In-band SNR) for level treshold*/
  unsigned short min_thresh;           /* Minimum treshold level 0.005218506 % -46.65 dBD*/
  unsigned short maxtwist;             /* Maximum allowed twist lo/hi 0.45 % Signal degradation limit (ratio-limit of min and max level)*/
  unsigned short levmmtwist;           /* Max twist of min/max of same tone 0.40*/
  unsigned short cnt_mint;             /* Minimum Counter Length (0.060*8000)/32768 % 60ms*/
  unsigned short cnt_maxt;             /* Maximum Counter Length (.087*8000)/32768  % 87ms*/
  unsigned short cnt_diff;             /* Difference between low/high count (.016*8000)/32768 % 16ms*/
  unsigned short cnt_startmm;          /* Record dmax/dmin after counter 50/32768*/
  unsigned short magnitude0p34;        /* Magintude multiplication constant  .339996*/
  unsigned short sin_low;              /* Working value 'sin' internal lo-tone generator (init -1)*/
  unsigned short cos_low;              /* Working value 'cos' internal lo-tone generator*/
  unsigned short sin_high;             /* Working value 'sin' internal hi-tone generator (init -1)*/
  unsigned short cos_high;             /* Working value 'cos' internal hi-tone generator*/
  unsigned short corr_sinl;            /* Sine correlation coef for lo-tone*/
  unsigned short corr_cosl;            /* Cosine correlation coef for lo-tone*/
  unsigned short corr_sinh;            /* Sine correlation coef for hi-tone*/
  unsigned short corr_cosh;            /* Cosine correlation coef for hi-tone*/
  unsigned short avglev_l;             /* Actual level lo-tone*/
  unsigned short avglev_h;             /* Actual level hi-tone*/
  unsigned short avgbglev;             /* Actual background level*/
  unsigned short levmax_l;             /* Max level lo-tone*/
  unsigned short levmin_l;             /* Min level lo-tone*/
  unsigned short levmax_h;             /* Max level hi-tone*/
  unsigned short levmin_h;             /* Min level hi-tone*/
  unsigned short levdevmax_l;          /* Max level lo-tone derivative*/
  unsigned short levdevmax_h;          /* Min level hi-tone derivative*/
  unsigned short count_l;              /* Counter for lo-tone detection*/
  unsigned short count_h;              /* Counter for hi-tone detection*/
  unsigned short casd_out;             /* CAS Tone Detection output*/
} gdsp_default_casdetector;

typedef struct
{
  unsigned short in_l_ptr;             /* CAS Detector low tone input*/
  unsigned short in_h_ptr;             /* CAS Detector high tone input*/
  unsigned short argsin_l;             /* Sine constant for CAS lo-tone: 2130Hz*/
  unsigned short argcos_l;             /* Cosine constant for CAS lo-tone: 2130Hz*/
  unsigned short argsin_h;             /* Sine constant for CAS lo-tone: 2750Hz*/
  unsigned short argcos_h;             /* Cosine constant for CAS lo-tone: 2750Hz*/
  unsigned short cspeed;               /* Correlation convergence speed-factor 1365/32768   % 0x0555*/
  unsigned short levtcnst;             /* Timeconstant 0.0625 for lo- and hi-level detection*/
  unsigned short bglevtcnst;           /* Timeconstant 0.0625 for background detection*/
  unsigned short bglevstepsz;          /* Step factor 0.25 for background level detection*/
  unsigned short scale_thresh;         /* Scaling factor 0.25 % In-band SNR) for level treshold*/
  unsigned short min_thresh;           /* Minimum treshold level 0.005218506 % -46.65 dBD*/
  unsigned short maxtwist;             /* Maximum allowed twist lo/hi 0.45 % Signal degradation limit (ratio-limit of min and max level)*/
  unsigned short levmmtwist;           /* Max twist of min/max of same tone 0.40*/
  unsigned short cnt_mint;             /* Minimum Counter Length (0.060*8000)/32768 % 60ms*/
  unsigned short cnt_maxt;             /* Maximum Counter Length (.087*8000)/32768  % 87ms*/
  unsigned short cnt_diff;             /* Difference between low/high count (.016*8000)/32768 % 16ms*/
  unsigned short cnt_startmm;          /* Record dmax/dmin after counter 50/32768*/
  unsigned short magnitude0p34;        /* Magintude multiplication constant  .339996*/
  unsigned short sin_low;              /* Working value 'sin' internal lo-tone generator (init 0.989990234375)*/
  unsigned short cos_low;              /* Working value 'cos' internal lo-tone generator*/
  unsigned short sin_high;             /* Working value 'sin' internal hi-tone generator (init 0.989990234375)*/
  unsigned short cos_high;             /* Working value 'cos' internal hi-tone generator*/
  unsigned short corr_sinl;            /* Sine correlation coef for lo-tone*/
  unsigned short corr_cosl;            /* Cosine correlation coef for lo-tone*/
  unsigned short corr_sinh;            /* Sine correlation coef for hi-tone*/
  unsigned short corr_cosh;            /* Cosine correlation coef for hi-tone*/
  unsigned short avglev_l;             /* Actual level lo-tone*/
  unsigned short avglev_h;             /* Actual level hi-tone*/
  unsigned short avgbglev;             /* Actual background level*/
  unsigned short levmax_l;             /* Max level lo-tone*/
  unsigned short levmin_l;             /* Min level lo-tone*/
  unsigned short levmax_h;             /* Max level hi-tone*/
  unsigned short levmin_h;             /* Min level hi-tone*/
  unsigned short levdevmax_l;          /* Max level lo-tone derivative*/
  unsigned short levdevmax_h;          /* Min level hi-tone derivative*/
  unsigned short count_l;              /* Counter for lo-tone detection*/
  unsigned short count_h;              /* Counter for hi-tone detection*/
  unsigned short casd_out;             /* CAS Tone Detection output*/
} gdsp_default_casdetectorsplitinput;

typedef struct
{
  unsigned short srcliststart;         /* */
  unsigned short srclistend;           /* */
  unsigned short deststart;            /* */
} gdsp_default_classddestinations;

typedef struct
{
  unsigned short srcliststart;         /* */
  unsigned short srclistend;           /* */
  unsigned short destliststart;        /* */
  unsigned short codecmicgainoutsrc;   /* */
  unsigned short codecdataoutsrc;      /* */
  unsigned short codecmicgainoutdest;   /* */
  unsigned short codecdataoutdest;     /* */
} gdsp_default_codecdestinations;

typedef struct
{
  unsigned short srcstart;             /* */
  unsigned short srcend;               /* */
  unsigned short destliststart;        /* */
  unsigned short src_ptr1;             /* Src1: CODEC_MIC_GAIN_REG*/
  unsigned short src_ptr2;             /* Src2: CODEC_DATA_REG*/
  unsigned short codecmicgainsrc;      /* Temporary copy of CODEC_MIC_GAIN_REG*/
  unsigned short codecdatainsrc;       /* Temporary copy of CODEC_DATA_IN_REG*/
} gdsp_default_codecsource;

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
} gdsp_default_conference;

typedef struct
{
  unsigned short value;                /* Constant Value 32767/32768*/
} gdsp_default_constant;

typedef struct
{
  unsigned short in_ptr;               /* Incrementer input*/
  unsigned short out;                  /* Incrementer output*/
} gdsp_default_decrement;

typedef struct
{
  unsigned short mode;                 /* Buffer mode set to PLAYBACK operation*/
  unsigned short in_ptr;               /* Delay Line input*/
  unsigned short out_ptr;              /* Output pointer*/
  unsigned short buffer_size;          /* Delay line of 120 taps*/
  unsigned short buffer_ptr;           /* Start of Delay Line taps buffer*/
  unsigned short read_idx;             /* Read index in buffer*/
  unsigned short write_idx;            /* Write index in buffer*/
  unsigned short buffer_irq_size;      /* Never generate IRQ in Delay-mode*/
  unsigned short irq;                  /* Never generate IRQ in delay line mode*/
  unsigned short out;                  /* Delay Line Output*/
  unsigned short taps[120];            /* Delay Line taps buffer*/
} gdsp_default_delayline_120;

typedef struct
{
  unsigned short num_ptr;              /* Input*/
  unsigned short den_ptr;              /* Input*/
  unsigned short out;                  /* Division output*/
} gdsp_default_division;

typedef struct
{
  unsigned short in_ptr;               /* DTMF signal input*/
  unsigned short argsc[16];            /* ARGSIN and ARGCOS values for internal tone generation*/
  unsigned short attack;               /* Power Detection attack time/rate*/
  unsigned short cspeed;               /* Detector adaptation mu factor*/
  unsigned short max_fac1;             /* Signal to inband interferer ratio*/
  unsigned short max_fac2;             /* Signal to inband interferer peakhold ratio*/
  unsigned short levinp_fac;           /* Signal to Noise Ratio*/
  unsigned short min_inplev;           /* DTMF Signal level threshold*/
  unsigned short char_time;            /* Symbol Detector ON time*/
  unsigned short cease_time;           /* Symbol Detector OFF time*/
  unsigned short max_dur_diff;         /* Maximum symbol duration difference between hi and lo frequency*/
  unsigned short grpcnt_ini;           /* Symbol Detection predelay (after burst detection)*/
  unsigned short diffmax_fax;          /* Burst detection (derivative) activation threshold*/
  unsigned short sincos[16];           /* Sine/cosine generators working values*/
  unsigned short corr[16];             /* DTMF Correlation coefficients*/
  unsigned short lev_inp;              /* Input signal powerlevel*/
  unsigned short lev_err;              /* Level of DTMF Error signal for dectector adaptation loop (total outband signal power)*/
  unsigned short low_index;            /* Low Frequency index working value*/
  unsigned short low_timer;            /* Low Frequency Symbol timer*/
  unsigned short low_scndmax;          /* Low Frequency group second indband correlation maximum*/
  unsigned short high_index;           /* High Frequency index working value*/
  unsigned short high_timer;           /* High Frequency Symbol timer*/
  unsigned short high_scndmax;         /* High Frequency group second indband correlation maximum*/
  unsigned short signal_timer;         /* DTMF Signal presence timer*/
  unsigned short silence_timer;        /* DTMF Signal pause timer*/
  unsigned short last_code;            /* Detected DTMF Lo/Hi Frequency Index register*/
  unsigned short dtmf_err;             /* Actual Error-signal for correlation*/
  unsigned short dummy3;               /* Dummy parameter (unused)*/
  unsigned short index_cnt;            /* Working value low index*/
  unsigned short index_cur;            /* Working value high index*/
  unsigned short prev_max2;            /* Peakhold of 2nd max for both groups*/
  unsigned short adapt_timer;          /* DTMF Burst Detection predelay counter*/
  unsigned short diff_max;             /* Derivative peak-hold for burst detection*/
  unsigned short index_out;            /* IRQ Flag in MSB when successful DTMF detected*/
} gdsp_default_dtmfdetector;

typedef struct
{
  unsigned short dtmf_in;              /* Russia Caller ID Detector signal Input*/
  unsigned short argsc[12];            /* ARGSIN and ARGCOS values for internal tone generation (12 parameters)*/
  unsigned short attack;               /* Power Detection attack time/rate*/
  unsigned short cspeed;               /* Detector adaptation mu factor*/
  unsigned short max_fac1;             /* Max Twist*/
  unsigned short max_fac2;             /* Inband Signal to Noise Ratio - peakhold threshold*/
  unsigned short levinp_fac;           /* Outband SNR threshold to activate detection*/
  unsigned short min_inplev;           /* Signal level threshold (avoids intial false detections)*/
  unsigned short grpcnt_ini;           /* Symbol Detection predelay (after burst detection)*/
  unsigned short stepon;               /* Step value for detection ON timer (value must be negative integer)*/
  unsigned short stepoff;              /* Step value for detection OFF timer (value must be positive integer)*/
  unsigned short sincos[12];           /* Internal Tone generators working values: 6*(Sine,cosine)*/
  unsigned short corr[12];             /* DTMFRU Correlation coefficients: 6*(corrsin,corrcos)*/
  unsigned short lev_inp;              /* Input signal power level*/
  unsigned short lev_err;              /* Level of input signal without cancelled tones*/
  unsigned short signal_timer;         /* RCID Symbol presence timer*/
  unsigned short dtmf_err;             /* Input signal without cancelled tones (residual signal)*/
  unsigned short last_code;            /* Detected RCID symbol index*/
  unsigned short index_cnt;            /* DTMF index working value*/
  unsigned short index1_cur;           /* DTMF tone 1 index working value*/
  unsigned short index2_cur;           /* DTMF tone 2 index working value*/
  unsigned short max1;                 /* First Strongest correlation result*/
  unsigned short max2;                 /* Second strongest correlation result*/
  unsigned short max3;                 /* Third strongest correlation result*/
  unsigned short hysteresis;           /* Counter for the input level-dtmf error*/
  unsigned short cli_timer;            /* Carrier Detect timer*/
  unsigned short index_out;            /* MSB signals new valid DTMF symbol detection*/
  unsigned short hyst_irq;             /* MSB signals carrier detection (active for 1 frame)*/
} gdsp_default_dtmfrudetector;

typedef struct
{
  unsigned short event_ptr;            /* Event input (negative value activates counter)*/
  unsigned short cntstep;              /* Counter step value*/
  unsigned short saturate;             /* Saturate (-1) or Wrap (0) counter*/
  unsigned short cnt_upb;              /* Highest counter value (upper bound)*/
  unsigned short cnt_lwb;              /* Lowest counter value (lower bound)*/
  unsigned short irqval;               /* Counter interrupt flag*/
  unsigned short reset_ptr;            /* Counter reset register*/
  unsigned short count;                /* Actual counter value*/
  unsigned short irq_out;              /* Counter IRQ Flag*/
  unsigned short cntr_activate_val;    /* Reset input*/
} gdsp_default_durationcounter;

typedef struct
{
  unsigned short prxin_ptr;            /* LEC output-power level input*/
  unsigned short ptxin_ptr;            /* LEC input-power level input*/
  unsigned short rxin_ptr;             /* Line input*/
  unsigned short txin_ptr;             /* Mic input input*/
  unsigned short gains;                /* Internal/Output gains register*/
  unsigned short nr_taps;              /* 64 FIR filter taps*/
  unsigned short rxin_atten;           /* Input attenuation 6 dB*/
  unsigned short c1;                   /* Tx level-offset 0.000488*/
  unsigned short ci_ptr;               /* Buffer for 64 Filter-coeeficients is reserved at the end of this param-block*/
  unsigned short rat0;                 /* mu0 <> Freeze decision ratio 0.0488*/
  unsigned short rat2;                 /* mu0 <> mu1/mu2/mu3 decision ratio 0.25*/
  unsigned short tl1;                  /* mu0 <> mu1 decision level 0.000977*/
  unsigned short tl2;                  /* mu1 <> mu2 decision level 0.125*/
  unsigned short tl3;                  /* mu2 <> mu3 decision level 0.25*/
  unsigned short tri_ptr;              /* Buffer for 64 filter-taps reserved behind coefficients-memory*/
  unsigned short u0;                   /* Mu0 = 0.001953: Update speed in double-talk mode*/
  unsigned short u1;                   /* Mu1 = 0.125: Update speed in single-talk mode, small signals*/
  unsigned short u2;                   /* Mu2 = 0.03251: Update speed in single-talk mode, medium signals*/
  unsigned short u3;                   /* Mu3 = 0: Update speed in single-talk mode, large signals*/
  unsigned short err;                  /* Error feedback signal (init 0)*/
  unsigned short tri_start;            /* taps-pointer value (init to start of taps-buffer)*/
  unsigned short rx_out;               /* LEC Output*/
  unsigned short ec_coeff_bfr[64];     /* LEC Filter Coefficients Buffer of 64 WORDS*/
  unsigned short ec_taps_bfr[64];      /* LEC Filter Taps Buffer of 64 WORDS*/
} gdsp_default_echocancellation_64;

typedef struct
{
  unsigned short mucopy_srcb;          /* */
  unsigned short mucopy_srce;          /* */
  unsigned short mucopy_dest;          /* */
  unsigned short mucopy_srcptr;        /* Source of mu parameter*/
  unsigned short mucopy_destptr;       /* Mu input-parameter will be copied to the u0 parameter*/
  unsigned short prxin_ptr;            /* LEC output-power level input*/
  unsigned short ptxin_ptr;            /* LEC input-power level input*/
  unsigned short rxin_ptr;             /* Line input*/
  unsigned short txin_ptr;             /* Mic input input*/
  unsigned short gains;                /* Internal/Output gains register*/
  unsigned short nr_taps;              /* 40 FIR filter taps*/
  unsigned short rxin_atten;           /* Input attenuation 0 dB*/
  unsigned short c1;                   /* Tx level-offset 0*/
  unsigned short ci_ptr;               /* Buffer for 40 Filter-coeeficients is reserved at the end of this param-block*/
  unsigned short rat0;                 /* mu0 <> Freeze decision ratio 0.04*/
  unsigned short rat2;                 /* mu0 <> mu1/mu2/mu3 decision ratio 0*/
  unsigned short tl1;                  /* mu0 <> mu1 decision level 32767/32768 (don't care if rat2 = 0)*/
  unsigned short tl2;                  /* mu1 <> mu2 decision level 32767/32768 (don't care if rat2 = 0)*/
  unsigned short tl3;                  /* mu2 <> mu3 decision level 32767/32768 (don't care if rat2 = 0)*/
  unsigned short tri_ptr;              /* Buffer for 40 filter-taps reserved behind coefficients-memory*/
  unsigned short u0;                   /* Mu0 = 0: Update speed in double-talk mode*/
  unsigned short u1;                   /* Mu1 = 0: Update speed in single-talk mode (don't care if ratn2 = 0)*/
  unsigned short u2;                   /* Mu2 = 0: Update speed in single-talk mode (don't care if ratn2 = 0)*/
  unsigned short u3;                   /* Mu3 = 0: Update speed in single-talk mode (don't care if ratn2 = 0)*/
  unsigned short err;                  /* Error feedback signal (init 0)*/
  unsigned short tri_start;            /* taps-pointer value (init to start of taps-buffer)*/
  unsigned short rx_out;               /* LEC Output*/
  unsigned short ec_coeff_bfr[40];     /* LEC Filter Coefficients Buffer of 40 WORDS*/
  unsigned short ec_taps_bfr[40];      /* LEC Filter Taps Buffer of 40 WORDS*/
} gdsp_default_echocancellationwithmuinput_40;

typedef struct
{
  unsigned short in_ptr;               /* Edge-detector input*/
  unsigned short edge;                 /* rising-edge Detector*/
  unsigned short mask;                 /* Edge Detector sensitivity mask '0100000000000000'*/
  unsigned short delay;                /* Edge-detector delay element*/
  unsigned short out;                  /* Output value of the edge-detector (edge occured when output <0)*/
} gdsp_default_edgedetector;

typedef struct
{
  unsigned short event_ptr;            /* Event input (negative value activates counter)*/
  unsigned short cntstep;              /* Counter step value*/
  unsigned short saturate;             /* Saturate (-1) or Wrap (0) counter*/
  unsigned short cnt_upb;              /* Highest counter value (upper bound)*/
  unsigned short cnt_lwb;              /* Lowest counter value (lower bound)*/
  unsigned short irqval;               /* Counter interrupt flag*/
  unsigned short reset_ptr;            /* Counter reset register*/
  unsigned short count;                /* Actual counter value*/
  unsigned short irq_out;              /* Counter IRQ Flag*/
} gdsp_default_eventcounter;

typedef struct
{
  unsigned short in_ptr;               /* Input*/
  unsigned short norm_out;             /* Exponent output*/
} gdsp_default_exponent;

typedef struct
{
  unsigned short fftin_ptr;            /* */
  unsigned short size;                 /* */
  unsigned short scale;                /* */
  unsigned short mode;                 /* */
  unsigned short twiddle_ptr;          /* */
  unsigned short twiddle_size;         /* */
  unsigned short window_ptr;           /* */
  unsigned short window_size;          /* */
  unsigned short fftout_ptr;           /* */
  unsigned short fft_coefs_bfr[256];   /* */
} gdsp_default_fft;

typedef struct
{
  unsigned short input_ptr;            /* FM Operator phase input*/
  unsigned short cospars_ptr;          /* Pointer to sine/cosine working values*/
  unsigned short atten_ptr;            /* Gain control input*/
  unsigned short attack_r;             /* Attack time 1 ms.*/
  unsigned short decay_r;              /* Decay time 10 ms.*/
  unsigned short sustain_r;            /* Sustain decay time 10000 ms.*/
  unsigned short sustain_l;            /* Sustain level 0.5.*/
  unsigned short modindex;             /* Modulation Index 10.*/
  unsigned short w;                    /* (angular) Generator frequency 1000 Hz.*/
  unsigned short waveform;             /* Generator waveform and offset compensation.*/
  unsigned short output;               /* Generator output.*/
  unsigned short amplitude_msb;        /* Volume envelope msb (init to -1)*/
  unsigned short amplitude_lsb;        /* Volume envelope lsb*/
  unsigned short arg;                  /* working value frequency/phase calculation*/
  unsigned short cospars[4];           /* working values frequency/phase calculation*/
} gdsp_default_fmoperator;

typedef struct
{
  unsigned short fskin;                /* FSK signal input*/
  unsigned short attackcd;             /* Attack rate carrier detection*/
  unsigned short decaycd;              /* Decay rate carrier detection*/
  unsigned short diffpulse_fac;        /* Percentage of derivative above thershold to trigger start of cd*/
  unsigned short sublev_fac;           /* Max Twist-level*/
  unsigned short adaptmin_fac;         /* SNR threshold*/
  unsigned short threshmin;            /* adaptive threshold init-value (min-value)*/
  unsigned short detstart;             /* cdcounter init value; initial derivative estimation time before starting actual carrier detection*/
  unsigned short cadstepon;            /* Carrier ON Detection counter step*/
  unsigned short cadstepoff;           /* Carrier OFF Detection counter step*/
  unsigned short dropout_cur;          /* Maximum dropout counter time*/
  unsigned short dropout_tot;          /* Maximum total dropout counter time*/
  unsigned short attackrb;             /* Attack rate rawbit detection*/
  unsigned short decayrb;              /* Decay rate rawbit detection*/
  unsigned short levstep;              /* Step value for level adjustment (Twist compensation)*/
  unsigned short avgscale;             /* Level averaging factor*/
  unsigned short symbolfreq;           /* Reference symbol frequency for baudrate compensation*/
  unsigned short adjustwidth;          /* Slice adjustment threshold*/
  unsigned short adjustspeed;          /* Slice adjustment step*/
  unsigned short equalbit;             /* No. of equal FSK bits that will force a resync of the bit slicer*/
  unsigned short chsz_deton;           /* No. of CHSZ bits for valid CHSZ detection*/
  unsigned short mark_deton;           /* No. of MARK bits for valid MARK detection*/
  unsigned short mext_deton;           /* No. of stuffed MARK bits for MEXT timeout detection*/
  unsigned short sync_delay;           /* Predelay before restarting CLIP detection after dropout*/
  unsigned short err_cnt_init;         /* Max. no of allowed errors during CHSZ and MARK detection*/
  unsigned short tones[32];            /* MARK and SPACE samples for 1300Hz and 2100Hz*/
  unsigned short bfskin[8];            /* Correlation Buffer*/
  unsigned short corr_mark;            /* MARK Correlation value */
  unsigned short corr_space;           /* SPACE Correlation value */
  unsigned short avtot[2];             /* Average MARK and SPACE correlations*/
  unsigned short cadcnt;               /* Carrier Detection Counter*/
  unsigned short carrier_detect;       /* Carrier presence*/
  unsigned short rawbit;               /* Current raw bit*/
  unsigned short rawbit_signs;         /* Signs of previous rawbits*/
  unsigned short avgsumlev;            /* Average level of (Pmark + Pspace)*/
  unsigned short avgsublev;            /* Average level of abs(Pmark-Pspace)*/
  unsigned short maxlevdiff;           /* Maximum level of derivative*/
  unsigned short levdiff;              /* Derivative calculation delay tap*/
  unsigned short adapt_thresh;         /* Adaptive carrier threshold*/
  unsigned short freeze_thrs;          /* Carrier threshold adaptation freeze/unfreeze*/
  unsigned short dropout_cur_cnt;      /* Current Dropout time counter*/
  unsigned short dropout_tot_cnt;      /* Total Dropout time counter*/
  unsigned short sync_cnt;             /* Baudrate counter*/
  unsigned short equalbit_cnt;         /* Resync timer for slicer on long strings of equal FSK bits*/
  unsigned short lastrawbit;           /* rawbit delay tap*/
  unsigned short boolsync;             /* Baudrecovery resync*/
  unsigned short cidec_state;          /* CLIP state machine state*/
  unsigned short chsz_cnt_reg;         /* CHSZ bit counter*/
  unsigned short mark_cnt_reg;         /* MARK bit counter*/
  unsigned short mext_cnt_reg;         /* stuffed MARK bit counter*/
  unsigned short sync_bit;             /* Previous FSK symbol*/
  unsigned short data_byte;            /* FSK Data recovery working value*/
  unsigned short cidec_bit_cnt;        /* FSK symbol counter for data-recovery*/
  unsigned short cidec_error;          /* FSK CLIP error register*/
  unsigned short data_out;             /* FSK Data byte output (MSB signals new data)*/
  unsigned short chsz_err_cnt;         /* CHSZ bit error counter*/
  unsigned short mark_err_cnt;         /* MARK bit error counter*/
} gdsp_default_fskclipdecoder;

typedef struct
{
  unsigned short status;               /* FSK Generator status / control register*/
  unsigned short chszlen;              /* FSKGen transmits 300 CHSZ bits*/
  unsigned short marklen;              /* FSKGen transmits 150 MARK bits*/
  unsigned short mextlen;              /* FSKGen transmits 4 MEXT bits between data-packages*/
  unsigned short pmarklen;             /* FSKGen concludes transmission with 100 PMRK bits*/
  unsigned short symbollen;            /* FSKGen concludes transmission with 100 PMRK bits*/
  unsigned short argcos0;              /* Corrected ARGCOS value for 2100Hz ('0' symbol)*/
  unsigned short argsin0;              /* Corrected ARGSIN value for 2100Hz ('0' symbol)*/
  unsigned short argcos1;              /* Corrected ARGCOS value for 1300Hz ('1' symbol)*/
  unsigned short argsin1;              /* Corrected ARGSIN value for 1300Hz ('1' symbol)*/
  unsigned short msglen;               /* CR16 must write message & message length to FSK parameter block*/
  unsigned short gain_p;               /* FSKGen signal output amplitude 32767/32768*/
  unsigned short msgadr;               /* Pointer to FSK Message buffer (data must be written by CR16. MSG buffer is fixed to the end of the FSKGen parameter block.*/
  unsigned short fsk_out;              /* FSK Generator output*/
  unsigned short sin_n;                /* Sine working value (init -1)*/
  unsigned short cos_n;                /* Cosine working value (init 0)*/
  unsigned short samplecount;          /* FSK sample counter working value (init 0)*/
  unsigned short bitcount;             /* FSK symbol counter working value (init 0)*/
  unsigned short byteval;              /* FSK data counter working value (init 0)*/
  unsigned short state;                /* FSKGen internal state (init 0)*/
  unsigned short fskg_data[258];       /* FSKGen message buffer (258 characters is max. message incl. header and checksum; the user can make this shorter)*/
} gdsp_default_fskgen_258;

typedef struct
{
  unsigned short in_ptr;               /* Gain signal input*/
  unsigned short pre_attn;             /* preattenuation factor*/
  unsigned short shift;                /* preattenuation factor*/
  unsigned short post_attn;            /* preattenuation factor*/
  unsigned short out;                  /* Amplified/attenuated utput. Total gain: 1*/
} gdsp_default_gain;

typedef struct
{
  unsigned short in_ptr;               /* Audio input*/
  unsigned short level_ptr;            /* Output power feedback input for PlevDet*/
  unsigned short max_thresh;           /* Max threshold 0.35; AGC factor decays*/
  unsigned short min_thresh;           /* Min threshold 0.25; AGC factor attacks*/
  unsigned short toff_scale;           /* AGC attack-slope sample-interval 0+1 samples*/
  unsigned short ton_scale;            /* AGC decay-slope sample-interval 0+1 samples*/
  unsigned short clip;                 /* AGC range (max attn 0.25)*/
  unsigned short toff;                 /* AGC attack 0.0072215287952972*/
  unsigned short ton;                  /* AGC decay 0.99283024777684*/
  unsigned short offcnt;               /* AGC Attack working value*/
  unsigned short oncnt;                /* AGC Decay working value*/
  unsigned short atten;                /* AGC actual attn value (one-time init to 0.25)*/
  unsigned short out;                  /* AGC Signal output*/
} gdsp_default_hagc;

typedef struct
{
  unsigned short pa_rxin_ptr;          /* Power input of signal to speaker*/
  unsigned short pa_txin_ptr;          /* Power input of signal from mic*/
  unsigned short pl_rxin_ptr;          /* Power input of signal from line*/
  unsigned short pl_txin_ptr;          /* Power input of signal to line*/
  unsigned short pn_rxin_ptr;          /* Noise level input of signal from line*/
  unsigned short pn_txin_ptr;          /* Noise level input of signal from mic*/
  unsigned short sw_rxin_ptr;          /* input signal from line*/
  unsigned short sw_txin_ptr;          /* Input signal from mic*/
  unsigned short agcrxmax;             /* Min line-AGC attn 3.1622776601684e-005*/
  unsigned short agcrxmin;             /* Max line-AGC attn 0.99996948242188*/
  unsigned short agctxmax;             /* Max mic-AGC attn 3.1622776601684e-005*/
  unsigned short agctxmin;             /* Min mic-AGC attn 0.99996948242188*/
  unsigned short agcoffcntini;         /* Scalefactor 0xFFFF for AGC rise time*/
  unsigned short agconcntini;          /* Scalefactor 0xFFFF for AGC fall-time*/
  unsigned short agcrxclip;            /* Absolute range of RX AGC 0.99996948242188*/
  unsigned short agctoff;              /* AGC Decay time-constant 0.014495208068736*/
  unsigned short agcton;               /* AGC Attack time-constant 0.98571190090062*/
  unsigned short agctxclip;            /* Absolute range of TX AGC 0.99996948242188*/
  unsigned short codhigain;            /* HFREE Input/Output Gain control word*/
  unsigned short codlogain;            /* HFREE Input/Output Gain control word*/
  unsigned short divagctoff;           /* AGC Decay time-constant*/
  unsigned short divagcton;            /* AGC Attack time-constant*/
  unsigned short idlecntini;           /* HFREE Switch to IDLE mode predelay 0.00244140625*/
  unsigned short idlecntini2;          /* HFREE Scalefactor for switch-to-idle attack/decay-time*/
  unsigned short idleratio;            /* HFREE Ratio -1 determines switch from IDLE to RX/TX*/
  unsigned short noisemargin;          /* SNR -1 for voice activity detection*/
  unsigned short offrx;                /* Absolute RX noise-floor 256/32768 VAD*/
  unsigned short offtx;                /* Absolute TX noise-floor 256/32768 VAD*/
  unsigned short plrxscale;            /* Scale-factor 0.74989420933246 PLRX/PLTX ratio*/
  unsigned short plrxscale2;           /* Scale-factor 0.99996948242188 PLRX/PATX ratio*/
  unsigned short rxratio;              /* Ratio -0.1 PARX/PATX determines switch Rx to TX mode*/
  unsigned short rxtxcntini;           /* HFREE RX <> TX switch predelay*/
  unsigned short supmin;               /* Smallest suppression factor 0.031622776601684 (max suppression level)*/
  unsigned short suptidleoff;          /* Suppressor attack time (IDLE -> RX/TX)*/
  unsigned short suptidleon;           /* Suppressor decay time  (RX/TX -> IDLE)*/
  unsigned short suptoff;              /* Suppressor attack time  (RX <> TX)*/
  unsigned short supton;               /* Suppressor release time  (RX <> TX)*/
  unsigned short txratio;              /* Ratio -1 PLRX/PLTX determines switch TX to RX mode*/
  unsigned short agcrx;                /* Working value line-AGC (fixed initval 32767/32768)*/
  unsigned short agctx;                /* Working value mic-AGC (fixed initval 32767/32768)*/
  unsigned short agcoffcnt;            /* Working value AGC (init 0)*/
  unsigned short agconcnt;             /* Working value AGC (init 0)*/
  unsigned short atrx;                 /* Working value line-attn (init 0.51581138830084)*/
  unsigned short attx;                 /* Working value mic-attn (init 0.51581138830084)*/
  unsigned short cgain;                /* Working value (init 0)*/
  unsigned short divagcrx;             /* Working value*/
  unsigned short divagctx;             /* Working value*/
  unsigned short idlecnt;              /* Working value idle-counter*/
  unsigned short rxtxcnt;              /* Working value rx/tx predelay counter*/
  unsigned short sprx;                 /* Working value line speech activity detection*/
  unsigned short sptx;                 /* Working value mic speech activity detection*/
  unsigned short txmode;               /* RX/TX mode indication (<0:TX, >=0:RX)*/
  unsigned short rx_out;               /* Output to speaker*/
  unsigned short tx_out;               /* Output to line*/
} gdsp_default_handsfree;

typedef struct
{
  unsigned short fftin_ptr;            /* */
  unsigned short size;                 /* */
  unsigned short scale;                /* */
  unsigned short mode;                 /* */
  unsigned short twiddle_ptr;          /* */
  unsigned short twiddle_size;         /* */
  unsigned short window_ptr;           /* */
  unsigned short window_size;          /* */
  unsigned short fftout_ptr;           /* */
  unsigned short ifft_out_bfr[128];    /* */
} gdsp_default_ifft;

typedef struct
{
  unsigned short in_ptr;               /* Incrementer input*/
  unsigned short out;                  /* Incrementer output*/
} gdsp_default_increment;

typedef struct
{
  unsigned short num_ptr;              /* Input*/
  unsigned short den_ptr;              /* Input*/
  unsigned short quot;                 /* Division quotient output*/
  unsigned short remain;               /* Division remainder output*/
} gdsp_default_integerdivision;

typedef struct
{
  unsigned short numerator;            /* Numerator Value Parameter*/
  unsigned short denominator;          /* Denomenator Value Parameter*/
  unsigned short cnum;                 /* CNumerator Value Parameter*/
  unsigned short cnumshift;            /* CNumeratorshift Value Parameter*/
  unsigned short interp_phase;         /* Interpolator state*/
  unsigned short output;               /* Interpolator output*/
  unsigned short bufferend_ptr;        /* End address of buffer*/
  unsigned short looppoint_ptr;        /* Loop Point Position Parameter*/
  unsigned short bufferpos_ptr;        /* Buffer Position Parameter*/
  unsigned short lastsample;           /* Left side sample in interpolation interval*/
  unsigned short rightsample;          /* Right side sample in interpolation interval*/
  unsigned short dummy;                /* Dummy location for use with DBLLAW2LIN*/
  unsigned short bufferdata[2000];     /* PCM data for INTERP*/
} gdsp_default_interpolator_2000;

typedef struct
{
  unsigned short lawin_ptr;            /* A/Mu law coded input signal*/
  unsigned short lawb;                 /* Input format -1*/
  unsigned short linear_out;           /* Linear coded output signal*/
} gdsp_default_lawlin;

typedef struct
{
  unsigned short in_ptr;               /* input*/
  unsigned short attn;                 /* Array Size Parameter*/
  unsigned short shiftval;             /* Array Size Parameter*/
  unsigned short c0;                   /* Coefficient 0 Parameter*/
  unsigned short c1;                   /* Coefficient 1 Parameter*/
  unsigned short c2;                   /* Coefficient 2 Parameter*/
  unsigned short c3;                   /* Coefficient 3 Parameter*/
  unsigned short c4;                   /* Coefficient 4 Parameter*/
  unsigned short out;                  /* Lin to log output*/
} gdsp_default_lineairtolog;

typedef struct
{
  unsigned short linin_ptr;            /* Linear coded input signal*/
  unsigned short lawb;                 /* Output format -1*/
  unsigned short law_out;              /* A?Mu law coded output signal*/
} gdsp_default_linlaw;

typedef struct
{
  unsigned short in_ptr;               /* input*/
  unsigned short attn;                 /* Array Size Parameter*/
  unsigned short shiftval;             /* Array Size Parameter*/
  unsigned short c0;                   /* Coefficient 0 Parameter*/
  unsigned short c1;                   /* Coefficient 1 Parameter*/
  unsigned short c2;                   /* Coefficient 2 Parameter*/
  unsigned short c3;                   /* Coefficient 3 Parameter*/
  unsigned short c4;                   /* Coefficient 4 Parameter*/
  unsigned short out;                  /* log to lin output*/
} gdsp_default_logtolineair;

typedef struct
{
  unsigned short nr_lfos;              /* Number of LFOs*/
  unsigned short lfo_start_ptr;        /* Pointer to start of LFO data RAM instances*/
  unsigned short nr_fm_mels;           /* Number of FM melodic operators*/
  unsigned short fm_mel_start_ptr;     /* Pointer to start of FM melodic data RAM instances*/
  unsigned short rndgen_start_ptr;     /* Pointer to the rndgen data RAM instance*/
  unsigned short nr_fm_percs;          /* Number of FM percussion operators*/
  unsigned short fm_perc_start_ptr;    /* Pointer to start of FM percussion data RAM instances*/
  unsigned short nr_wtbls;             /* Number of wavetable voices*/
  unsigned short wtbl_start_ptr;       /* Pointer to start of wavetable data RAM instances*/
  unsigned short mixer_start_ptr;      /* Pointer to start of mixer RAM table*/
  unsigned short timer_start_ptr;      /* Pointer to start of timer data RAM*/
  unsigned short timer_irq_vector;     /* IRQ vector generated towards CR16 when timer expires*/
  unsigned short irq_out;              /* This is used for simulations and debugging*/
  unsigned short lfo[2];               /* lfo*/
  unsigned short fm_mel[24];           /* fm_mel*/
  unsigned short rndgen[3];            /* Actual RNDGEN instance*/
  unsigned short fm_perc[8];           /* fm_perc*/
  unsigned short wtbl[12];             /* wtbl*/
  unsigned short mixer[50];            /* Actual Mixer RAM instance*/
  unsigned short timer[2];             /* Actual Timer RAM instance*/
} gdsp_default_midisynth;

typedef struct
{
  unsigned short in_ptr;               /* input*/
  unsigned short arraysize;            /* Array Size Parameter*/
  unsigned short min_out;              /* Minimum Value output*/
  unsigned short max_out;              /* Maximum Value output*/
  unsigned short absmin_out;           /* Absolute Minimum Value output*/
  unsigned short absmax_out;           /* Absolute Maximum Value output*/
} gdsp_default_minmax;

typedef struct
{
  unsigned short ptr_ptr;              /* Pointer to list of 4 input pointers*/
  unsigned short w_ptr;                /* Pointer to list of 4 weight factors*/
  unsigned short n;                    /* process n input channels.*/
  unsigned short attn;                 /* Output attenuation factor 0.5*/
  unsigned short temp;                 /* working value*/
  unsigned short out;                  /* mixer output*/
  unsigned short inputs[4];            /* inputs*/
  unsigned short weights[4];           /* channel weights*/
} gdsp_default_mixer;

typedef struct
{
  unsigned short in01_ptr;             /* Mapped to bit 0*/
  unsigned short in02_ptr;             /* Mapped to bit 1*/
  unsigned short in03_ptr;             /* Mapped to bit 2*/
  unsigned short in04_ptr;             /* Mapped to bit 3*/
  unsigned short in05_ptr;             /* Mapped to bit 4*/
  unsigned short in06_ptr;             /* Mapped to bit 5*/
  unsigned short in07_ptr;             /* Mapped to bit 6*/
  unsigned short in08_ptr;             /* Mapped to bit 7*/
  unsigned short in09_ptr;             /* Mapped to bit 8*/
  unsigned short in10_ptr;             /* Mapped to bit 9*/
  unsigned short in11_ptr;             /* Mapped to bit 10*/
  unsigned short in12_ptr;             /* Mapped to bit 11*/
  unsigned short in13_ptr;             /* Mapped to bit 12*/
  unsigned short in14_ptr;             /* Mapped to bit 13*/
  unsigned short in15_ptr;             /* Mapped to bit 14*/
  unsigned short in16_ptr;             /* Mapped to bit 15*/
  unsigned short out;                  /* Monitor output*/
} gdsp_default_monitor;

typedef struct
{
  unsigned short in1_ptr;              /* Nibble Shift left input 1*/
  unsigned short in2_ptr;              /* Nibble Shift left input 2*/
  unsigned short out1;                 /* Nibble Shift left output 1*/
  unsigned short out2;                 /* Nibble Shift left output 2*/
} gdsp_default_nibbleshiftleft;

typedef struct
{
  unsigned short in1_ptr;              /* Nibble Shift right input 1*/
  unsigned short in2_ptr;              /* Nibble Shift right input 2*/
  unsigned short out1;                 /* Nibble Shift right output 1*/
  unsigned short out2;                 /* Nibble Shift right output 2*/
} gdsp_default_nibbleshiftright;

typedef struct
{
  unsigned short in_ptr;               /* input*/
  unsigned short buff_out;             /* Normalized buffer output*/
  unsigned short arraysize;            /* Array Size Parameter*/
  unsigned short shiftval;             /* Shift Value output*/
  unsigned short normdata_out[16];     /* Normalised Data Output Parameter*/
} gdsp_default_norm;

typedef struct
{
  unsigned short in1_ptr;              /* OR input 1*/
  unsigned short in2_ptr;              /* OR input 2*/
  unsigned short out;                  /* OR output*/
} gdsp_default_or;

typedef struct
{
  unsigned short spkr_ptr;             /* Pointer to speaker input array*/
  unsigned short mic_ptr;              /* Pointer to microphone input array*/
  unsigned short out_ptr;              /* Pointer to output array*/
  unsigned short twiddle_ptr;          /* Pointer to twiddle table (ROM)*/
  unsigned short twiddle_size;         /* Size of twiddle table*/
  unsigned short window_ptr;           /* Pointer to window table(ROM)*/
  unsigned short window_size;          /* Size of window table*/
  unsigned short fftbuf_spkr_ptr;      /* Pointer to complex FFT buffer of speaker signal*/
  unsigned short fftbuf_mic_ptr;       /* Pointer to complex FFT buffer of microphone signal*/
  unsigned short paecband_ptr;         /* Pointer to band states structure*/
  unsigned short xpow_ptr;             /* Pointer to array of speaker power spectrum coeffs*/
  unsigned short ypow_ptr;             /* Pointer to array of mic power spectrum coeffs*/
  unsigned short ccxx_ptr;             /* Pointer to array of speaker auto correlation coeffs*/
  unsigned short ccxy_ptr;             /* Pointer to array of speaker and mic auto correlation coeffs*/
  unsigned short ccyy_ptr;             /* Pointer to array of mic auto correlation coeffs*/
  unsigned short cc_ptr;               /* Pointer to array of Wiener-coefficients (active gain filter) for spectral substraction*/
  unsigned short cc_af_ptr;            /* Pointer to array of Wiener-coefficients (adapting gain filter) for spectral substraction*/
  unsigned short fftsize;              /* Size of FFT (128)*/
  unsigned short framesize;            /* Size of input frame (64)*/
  unsigned short fftscale;             /* FFT scale factor*/
  unsigned short ifftscale;            /* iFFT scale factor*/
  unsigned short fftmode;              /* FFT mode*/
  unsigned short npart;                /* Number of frequency bands*/
  unsigned short mode;                 /* Mode word*/
  unsigned short delaycompspecs;       /* Maximum expected delay of early echo in number of input frames*/
  unsigned short ibuf_size;            /* Input buffer size*/
  unsigned short ibuf_idx;             /* Input buffer read-index (one index for both input buffers)*/
  unsigned short obuf_size;            /* Output buffer size*/
  unsigned short obuf_idx;             /* Output buffer read index*/
  unsigned short init;                 /* Number of frames with initial 'fast' convergence time constants, multiplied with -1*/
  unsigned short noiseestgainshft;     /* Tx noise level estimation scaling factor*/
  unsigned short noiseestspkgainshft;   /* Rx noise level estimation scaling factor*/
  unsigned short dtdcount_init;        /* Double talk detection counter init value. Value is number of frames the DTD conditions must be true before adapting filter is copied to the active filter*/
  unsigned short gamma;                /* Scalling parameter of the echo removal filter*/
  unsigned short cctc;                 /* Time constant for the coloration effect filter (cross correlation and auto correlations)*/
  unsigned short beta;                 /* Gain given to echo estimate to avoid under-estimation*/
  unsigned short attlimit;             /* Attenuation Limit*/
  unsigned short dtdthr;               /* Doubletalk Detector absolute MSE threshold (foreground filter)*/
  unsigned short dtdthr2;              /* Doubletalk Detector relative MSE threshold (foreground filter vs background filter)*/
  unsigned short dtdthr3;              /* Doubletalk Detector 2nd relative MSE threshold*/
  unsigned short dtdsmooth;            /* Doubletalk Detector statistics estimation time constant*/
  unsigned short dtddecay;             /* Doubletalk Detector coloration effect filter update speed*/
  unsigned short dtdwgain_full_thr;    /* Doubletalk Detector absolute full band prediction gain threshold*/
  unsigned short dtdwgain_part_thr;    /* Doubletalk Detector absolute subband prediction gain threshold*/
  unsigned short noiseest1;            /* Noise Suppression attack time constant for noise level estimation*/
  unsigned short noiseest2;            /* Noise Suppression release time constant for noise level estimation*/
  unsigned short noiseest3;            /* Noise Suppression paramter*/
  unsigned short noiseattlimit;        /* Noise Suppression attenuation factor*/
  unsigned short nsuppsmtra;           /* Noise Suppression time constant for transient noise suppression gain smoothing*/
  unsigned short nsuppsmsta;           /* Noise Suppression time constant for stationary noise suppression gain smoothing*/
  unsigned short nsstathr;             /* Noise Suppression stationarity threshold*/
  unsigned short retainnoisethr1div;   /* Rx noise retaining threshold*/
  unsigned short attlimitthr1div;      /* Attenuation limit minimum threshold*/
  unsigned short smooththr;            /* Gain Filter Smoothing control threshold*/
  unsigned short smoothdef;            /* Gain Filter Smoothing control Rx mode time constant*/
  unsigned short smoothlow;            /* Gain Filter Smoothing control Doubletalk mode time constant 1. Controls suppression time of room echo tail*/
  unsigned short smoothtop;            /* Gain Filter Smoothing control Doubletalk mode time constant 2. Controls capture of early room echoes*/
  unsigned short winitial;             /* Flag indicating use of initial or steady state parameters*/
  unsigned short dtdcount;             /* Doubletalk Detection counter*/
  unsigned short wdelay;               /* Estimated echo path delay for foreground filter*/
  unsigned short wdelay_af;            /* Estimated echo path delay for background filter*/
  unsigned short wgain;                /* Prediction gain of foreground filter*/
  unsigned short wgain_af;             /* Prediction gain of background filter*/
  unsigned short erlenum;              /* ERLE estimation numerator*/
  unsigned short erleden;              /* ERLE estimation denominator*/
  unsigned short mse;                  /* Mean Square error of foreground filter*/
  unsigned short mse_af;               /* Mean Square error of background filter*/
  unsigned short msenrm;               /* Normalisation value for MSE estimation*/
  unsigned short spkr_buf[148];        /* Speaker input buffer array*/
  unsigned short mic_buf[148];         /* Microphone input buffer array*/
  unsigned short out_buf[148];         /* PAEC output buffer array*/
  unsigned short cmplx_buf[130];       /* Complex FFT buffer*/
  unsigned short window[64];           /* Window table*/
  unsigned short xpow[48];             /* Rx Signal Power spectrum array (with history)*/
  unsigned short ypow[12];             /* Tx Signal Power spectrum*/
  unsigned short ccxx[48];             /* Rx auto-correlation coefficients array (with history)*/
  unsigned short ccxy[48];             /* Rx and Tx cross-correlation coefficients array*/
  unsigned short ccyy[12];             /* Tx auto-correlation coefficients array*/
  unsigned short cc[48];               /* Gainfilter coefficients array (foreground filter)*/
  unsigned short cc_af[48];            /* Gainfilter coefficients array (background filter)*/
  unsigned short paec_subband_1[21];   /* PAEC subband 1*/
  unsigned short paec_subband_2[21];   /* PAEC subband 2*/
  unsigned short paec_subband_3[21];   /* PAEC subband 3*/
  unsigned short paec_subband_4[21];   /* PAEC subband 4*/
  unsigned short paec_subband_5[21];   /* PAEC subband 5*/
  unsigned short paec_subband_6[21];   /* PAEC subband 6*/
  unsigned short paec_subband_7[21];   /* PAEC subband 7*/
  unsigned short paec_subband_8[21];   /* PAEC subband 8*/
  unsigned short paec_subband_9[21];   /* PAEC subband 9*/
  unsigned short paec_subband_10[21];  /* PAEC subband 10*/
  unsigned short paec_subband_11[21];  /* PAEC subband 11*/
  unsigned short paec_subband_12[21];  /* PAEC subband 12*/
  unsigned short paec_subband_13[21];  /* PAEC subband 13*/
  unsigned short paec_subband_14[21];  /* PAEC subband 14*/
  unsigned short paec_subband_15[21];  /* PAEC subband 15*/
} gdsp_default_paec;

typedef struct
{
  unsigned short srcliststart;         /* */
  unsigned short srclistend;           /* */
  unsigned short deststart;            /* */
  unsigned short scrptr0;              /* */
  unsigned short scrptr1;              /* */
  unsigned short scrptr2;              /* */
  unsigned short scrptr3;              /* */
} gdsp_default_pcmmasterdestinations;

typedef struct
{
  unsigned short srcstart;             /* */
  unsigned short srcend;               /* */
  unsigned short destliststart;        /* */
  unsigned short pcm0insrc;            /* Temporary copy of DSP_PCM_IN0_REG*/
  unsigned short pcm1insrc;            /* Temporary copy of DSP_PCM_IN1_REG*/
  unsigned short pcm2insrc;            /* Temporary copy of DSP_PCM_IN2_REG*/
  unsigned short pcm3insrc;            /* Temporary copy of DSP_PCM_IN3_REG*/
} gdsp_default_pcmsource;

typedef struct
{
  unsigned short mode;                 /* Buffer mode set to Playback operation*/
  unsigned short in_ptr;               /* Buffer input (don't care in playback mode; input comes from CR16)*/
  unsigned short out_ptr;              /* Output pointer*/
  unsigned short buffer_size;          /* Buffer size 12 taps*/
  unsigned short buffer_ptr;           /* Start of buffer*/
  unsigned short read_idx;             /* Read index in buffer*/
  unsigned short write_idx;            /* Write index in buffer*/
  unsigned short buffer_irq_size;      /* IRQ flag set after %s samples (CR16 clears)*/
  unsigned short irq;                  /* IRQ output signals 'buffer empty'*/
  unsigned short out;                  /* Playback buffer Output*/
  unsigned short taps[12];             /* Buffer Elements*/
} gdsp_default_playbackbuffer_12;

typedef struct
{
  unsigned short in_ptr;               /* Input signal*/
  unsigned short fall;                 /* Detector decay time 0.007s.*/
  unsigned short rise;                 /* Detector attack time 0.004s.*/
  unsigned short out;                  /* Output: Power level of input signal*/
} gdsp_default_plevdet;

typedef struct
{
  unsigned short in_ptr;               /* Input signal*/
  unsigned short cntini;               /* Noise counter init value 0*/
  unsigned short fall;                 /* Noise detector decay time 0.004s.*/
  unsigned short max;                  /* Noise detector saturates at 256/32768*/
  unsigned short rise;                 /* Noise detector attack time 0.300s.*/
  unsigned short cnt;                  /* Noise counter working value*/
  unsigned short out;                  /* output: Background noise level of input signal*/
} gdsp_default_pnlevdet;

typedef struct
{
  unsigned short in_ptr;               /* in_ptr*/
  unsigned short coef[8];              /* Polynomial coefficients*/
  unsigned short out;                  /* Polynomial output*/
} gdsp_default_polynomial;

typedef struct
{
  unsigned short in_ptr;               /* Filter input*/
  unsigned short delayline_ptr;        /* location of taps buffer*/
  unsigned short coeffs_ptr;           /* location of filter coefficients buffer*/
  unsigned short out;                  /* FIR filter output*/
  unsigned short ntaps;                /* Number of FIR Filter taps (must be even!)*/
  unsigned short offset;               /* Index in taps/coeffs buffer*/
  unsigned short coeffsbfr[42];        /* Coefficients buffer*/
  unsigned short tapsbfr[42];          /* Taps buffer*/
} gdsp_default_programmablefirfilter_42;

typedef struct
{
  unsigned short mode;                 /* Buffer mode set to Record operation*/
  unsigned short in_ptr;               /* Buffer input*/
  unsigned short out_ptr;              /* Output pointer (don't care for record mode)*/
  unsigned short buffer_size;          /* Buffer size 128 taps*/
  unsigned short buffer_ptr;           /* Start of buffer*/
  unsigned short read_idx;             /* Read index in buffer*/
  unsigned short write_idx;            /* Write index in buffer*/
  unsigned short buffer_irq_size;      /* IRQ flag set after %s samples (CR16 clears)*/
  unsigned short irq;                  /* IRQ output signals 'buffer full'*/
  unsigned short out;                  /* Playback buffer Output*/
  unsigned short taps[128];            /* Buffer Elements*/
} gdsp_default_recordbuffer_128;

typedef struct
{
  unsigned short in_inptr;             /* Pointer to input-buffer (30 words encoded data)*/
  unsigned short out_ptr;              /* Pointer to output-buffer (240 words linear samples)*/
  unsigned short size;                 /* Size of RFFT*/
  unsigned short scale;                /* Scale factor in butterfly*/
  unsigned short buffer_size;          /* Size of circular buffer input*/
  unsigned short buffer_idx;           /* index in circular input buffer*/
  unsigned short frame_size;           /* Size of input frame*/
  unsigned short twiddle_ptr;          /* Pointer to twiddle table*/
  unsigned short twiddle_size;         /* Size of twiddle table*/
  unsigned short window_ptr;           /* Pointer to window table*/
  unsigned short window_size;          /* Size of window table*/
  unsigned short rfft_out_bfr[512];    /* */
} gdsp_default_rfft;

typedef struct
{
  unsigned short sample_ptr;           /* RFI Canceller input*/
  unsigned short silence_ptr;          /* Input for optional external silence detection (don't care if sil_det_select = 0x8000)*/
  unsigned short last_sample_ptr;      /* Location of circular sample-buffer for running avg calculation*/
  unsigned short average_ptr;          /* Location of running averaged frame buffer*/
  unsigned short last_average_ptr;     /* Location of reference averaged frame buffer*/
  unsigned short sil_det_select;       /* Internal or External Silence detection selector*/
  unsigned short average_sum_min;      /* Minimum deviation limit for silence detection*/
  unsigned short alpha_high;           /* Update speed during detected signal presence*/
  unsigned short alpha_low;            /* Update speed during detected silence*/
  unsigned short alpha_max_change;     /* Alpha switch rate*/
  unsigned short framelength;          /* Number of samples between repetitions of RFI noise*/
  unsigned short limit_diff_sum;       /* Deviation margin for silence detection (~SNR)*/
  unsigned short internal1;            /* internal parameter*/
  unsigned short internal2;            /* internal parameter*/
  unsigned short internal3;            /* internal parameter*/
  unsigned short internal4;            /* internal parameter*/
  unsigned short output;               /* Output of RFI canceller*/
  unsigned short silence_out;          /* Output of internal silence detector*/
  unsigned short average_sum;          /* sum of averages (threshold for silence detection*/
  unsigned short average_flag;         /* average_last buffer update flag*/
  unsigned short alpha;                /* actual mean frame update speed*/
  unsigned short average_sum_temp;     /* average_last buffer update flag*/
  unsigned short diff_sum_msb;         /* msb of variance calculation (enhanced precision)*/
  unsigned short diff_sum_lsb;         /* lsb of variance calculation  (enhanced precision)*/
  unsigned short internal5;            /* internal parameter*/
  unsigned short limit_frame_sample_sum;   /* Silence detection signal threshold*/
  unsigned short frame_sample_sum_msb;   /* msb of signal presence level  (enhanced precision)*/
  unsigned short frame_sample_sum_lsb;   /* lsb of signal presence level  (enhanced precision)*/
  unsigned short internal6;            /* internal parameter*/
  unsigned short internal7;            /* internal parameter*/
  unsigned short last_sample_bfr[80];   /* */
  unsigned short average_bfr[80];      /* */
  unsigned short last_average_bfr[80];   /* */
} gdsp_default_rfinoisecanceller_80;

typedef struct
{
  unsigned short in_inptr;             /* Pointer to input-buffer (30 words encoded data)*/
  unsigned short out_ptr;              /* Pointer to output-buffer (240 words linear samples)*/
  unsigned short size;                 /* Size of RFFT*/
  unsigned short scale;                /* Scale factor in butterfly*/
  unsigned short buffer_size;          /* Size of circular buffer input*/
  unsigned short buffer_idx;           /* index in circular input buffer*/
  unsigned short frame_size;           /* Size of input frame*/
  unsigned short twiddle_ptr;          /* Pointer to twiddle table*/
  unsigned short twiddle_size;         /* Size of twiddle table*/
  unsigned short window_ptr;           /* Pointer to window table*/
  unsigned short window_size;          /* Size of window table*/
  unsigned short out_bfr[512];         /* */
} gdsp_default_rifft;

typedef struct
{
  unsigned short rnd_ia;               /* */
  unsigned short rnd_ic;               /* */
  unsigned short seed;                 /* */
} gdsp_default_rndgen;

typedef struct
{
  unsigned short in_ptr;               /* Input*/
  unsigned short shval_ptr;            /* Shift value input*/
  unsigned short out;                  /* Shift output*/
} gdsp_default_shift;

typedef struct
{
  unsigned short tdetin;               /* Single Tone Detector Input*/
  unsigned short argsc1;               /* Corrected argcosinus value for the single tone detection*/
  unsigned short argsc2;               /* Corrected argsinus value for the single tone detection*/
  unsigned short attack;               /* Coeff averaging attack-rate 1/32 dB/ms*/
  unsigned short cspeed;               /* Correlation coefficients update-speed 1/64*/
  unsigned short levinp_fac;           /* Outband SNR threshold to activate detection*/
  unsigned short min_corramp;          /* Signal level threshold (avoids intial false detections)*/
  unsigned short stepon;               /* Step value for detection ON timer*/
  unsigned short stepoff;              /* Step value for detection OFF timer*/
  unsigned short sincos[2];            /* Sine/cosine generators working values*/
  unsigned short corr[2];              /* Tone Correlation coefficients sin_n, cos_n*/
  unsigned short lev_inp;              /* Input signal powerlevel*/
  unsigned short lev_err;              /* Level of error signal dectector adaptation loop (total outband signal power)*/
  unsigned short err;                  /* Error signal*/
  unsigned short cnt_out;              /* Tone presence timer*/
  unsigned short corr_amp;             /* Error signal*/
  unsigned short hysterese;            /* IRQ Flag in MSB when successful single tone detected*/
  unsigned short hyst_irq;             /* Detection irq. flag (sign, active for one frame)*/
} gdsp_default_singletonedetector;

typedef struct
{
  unsigned short in1_ptr;              /* Subtractor Input signal a*/
  unsigned short in2_ptr;              /* Subtractor Input signal b*/
  unsigned short out;                  /* Subtractor output signal 1*/
} gdsp_default_subtractor;

typedef struct
{
  unsigned short in1_ptr;              /* Input signal 1*/
  unsigned short in2_ptr;              /* Input signal 2*/
  unsigned short in3_ptr;              /* Attenuation factor input for MULTIN3*/
  unsigned short in1_atten;            /* Attenuates MULTIN1 with 0.5*/
  unsigned short out;                  /* Summator output*/
} gdsp_default_summator;

typedef struct
{
  unsigned short pnlev_tx_ptr;         /* Transmit (mic) noise level input*/
  unsigned short plev_rx_ptr;          /* Receive (line) signal level input*/
  unsigned short plev_tx_ptr;          /* Transmit (mic) signal level input*/
  unsigned short rx_in_ptr;            /* Receive (line) signal level input*/
  unsigned short centclip_att;         /* Centre-clipper attenuation factor 0.251*/
  unsigned short centclip;             /* Centre-clipper threshold level 0.005*/
  unsigned short c2_thresh;            /* Transmit (mic) level threshold 0.05*/
  unsigned short cntrini;              /* Suppressor OFF delay time 0.064s*/
  unsigned short cntrmin;              /* Suppressor OFF thresshold 0.75*/
  unsigned short off;                  /* Suppressor OFF attenuation 0.0015637654489758*/
  unsigned short on;                   /* Suppressor ON attenuation 18*/
  unsigned short ratio1;               /* Suppressor switch ration 0.5*/
  unsigned short rbetaoff;             /* Suppressor switch ON switch-rate 40/1000*/
  unsigned short rbetaon;              /* Suppressor switch OFF switch-rate 40/1000*/
  unsigned short cntr;                 /* Suppressor actual switch-counter value*/
  unsigned short sup;                  /* Suppressor actual attenuation value*/
  unsigned short rx_out;               /* Suppressor Receive (line) output*/
} gdsp_default_suppressor;

typedef struct
{
  unsigned short dec_in_ptr;           /* Pointer to input-buffer (30 words encoded data)*/
  unsigned short dec_out_ptr;          /* Pointer to output-buffer (240 words linear samples)*/
  unsigned short dec_init;             /* Initialisation state*/
  unsigned short pf_enable;            /* Enable Post-filter (MSB)*/
  unsigned short channel_state[205];   /* Channel State decoder*/
  unsigned short linbuf[240];          /* Decoded Linear Data output-buffer*/
  unsigned short combuf[30];           /* SVC Compressed Data input-buffer*/
} gdsp_default_svcdecoder;

typedef struct
{
  unsigned short enc_in_inptr;         /* Pointer to input-buffer (240 words linear samples)*/
  unsigned short enc_out_ptr;          /* Pointer to output-buffer (30 words encoded data)*/
  unsigned short enc_init;             /* Initialisation state*/
  unsigned short vad_enable;           /* Enable VAD (MSB)*/
  unsigned short hpf_enable;           /* Enable Prefilter (MSB)*/
  unsigned short parameters[7];        /* SVC parameters*/
  unsigned short channel_state[729];   /* SVC Encoder Channel State information*/
  unsigned short combuf[30];           /* SVC Compressed Data output-buffer*/
} gdsp_default_svcencoder;

typedef struct
{
  unsigned short in_ptr;               /* Tone detector Input*/
  unsigned short attack;               /* Coeff averaging attack-rate 0.004 dB/ms*/
  unsigned short casstepoff;           /* CAS Detection off counter-step 0.015*/
  unsigned short casstepon;            /* CAS Detection on counter-step 0.02*/
  unsigned short castreshld;           /* CAS Detection threshold 0.01*/
  unsigned short cspeed;               /* Correlation coefficients update-speed 1/64*/
  unsigned short decay;                /* Coeff averaging decay-rate 0.040 dB/ms*/
  unsigned short dtrstepoff;           /* DTMF Detection off counter-step 0.015*/
  unsigned short dtrstepon;            /* DTMF Detection on counter-step 0.02*/
  unsigned short ststepoff;            /* Single Tone Detection off counter-step 0.015*/
  unsigned short ststepon;             /* Single Tone Detection on counter-step 0.02*/
  unsigned short sttreshld;            /* Single tone Detection threshold 0.1*/
  unsigned short taverage;             /* Division factor 0.5 for sum-of-coeffs*/
  unsigned short treshld;              /* DTMF Detection threshold 0.002*/
  unsigned short argsin1;              /* Corrected argsin value for 697Hz tone detection (DTMFlow1)*/
  unsigned short argcos1;              /* Corrected argcos value for 697Hz tone detection (DTMFlow1)*/
  unsigned short argsin2;              /* Corrected argsin value for 770Hz tone detection (DTMFlow2)*/
  unsigned short argcos2;              /* Corrected argcos value for 770Hz tone detection (DTMFlow2)*/
  unsigned short argsin3;              /* Corrected argsin value for 852Hz tone detection (DTMFlow3)*/
  unsigned short argcos3;              /* Corrected argcos value for 852Hz tone detection (DTMFlow3)*/
  unsigned short argsin4;              /* Corrected argsin value for 941Hz tone detection (DTMFlow4)*/
  unsigned short argcos4;              /* Corrected argcos value for 941Hz tone detection (DTMFlow4)*/
  unsigned short argsin5;              /* Corrected argsin value for 2130Hz tone detection (CASlow)*/
  unsigned short argcos5;              /* Corrected argcos value for 2130Hz tone detection (CASlow)*/
  unsigned short argsin6;              /* Corrected argsin value for 1209Hz tone detection (DTMFhi1)*/
  unsigned short argcos6;              /* Corrected argcos value for 1209Hz tone detection (DTMFhi1)*/
  unsigned short argsin7;              /* Corrected argsin value for 1336Hz tone detection (DTMFhi2)*/
  unsigned short argcos7;              /* Corrected argcos value for 1336Hz tone detection (DTMFhi2)*/
  unsigned short argsin8;              /* Corrected argsin value for 1477Hz tone detection (DTMFhi3)*/
  unsigned short argcos8;              /* Corrected argcos value for 1477Hz tone detection (DTMFhi3)*/
  unsigned short argsin9;              /* Corrected argsin value for 1633Hz tone detection (DTMFhi4)*/
  unsigned short argcos9;              /* Corrected argcos value for 1633Hz tone detection (DTMFhi4)*/
  unsigned short argsin10;             /* Corrected argsin value for 2750Hz tone detection (CAShi)*/
  unsigned short argcos10;             /* Corrected argcos value for 2750Hz tone detection (CAShi)*/
  unsigned short argsin11;             /* Corrected argsin value for 1800Hz tone detection (Singletone)*/
  unsigned short argcos11;             /* Corrected argcos value for 1800Hz tone detection (Singletone)*/
  unsigned short cascnt;               /* CAS Detection counter (init -1)*/
  unsigned short casint;               /* CAS Detection flag (init 0.875)*/
  unsigned short indexprev;            /* Detected DTMF tone-combination status-register*/
  unsigned short reccnt;               /* DTMF Detection counter (init -1)*/
  unsigned short recint;               /* DTMF Detection flag (init 0.875)*/
  unsigned short stcnt;                /* Single Tone Detection counter (init -1)*/
  unsigned short stint;                /* Single Tone Detection flag (init 0.875)*/
  unsigned short ccregs[22];           /* Tone correlation coefficients (scor1,ccor1 ... scor11,ccor11)*/
  unsigned short tregs[22];            /* Internal tone-generators working registers (sin1,cos1 ... sin11,cos11)*/
  unsigned short avlevlow;             /* dynamic detection-threshold DTMFlow group*/
  unsigned short avlevhigh;            /* dynamic detection-threshold DTMFhi group*/
  unsigned short totsub_out;           /* Filter Output*/
} gdsp_default_tonedetector;

typedef struct
{
  unsigned short timerpreset1;         /* Tones ON for 0.5s.*/
  unsigned short timerpreset2;         /* Tones OFF for .1s.*/
  unsigned short argsin1_1;            /* Tone1 Corrected argsin value for 500Hz*/
  unsigned short argcos1_1;            /* Tone1 Corrected argcos value for 500Hz*/
  unsigned short t1att_1;              /* Tone1 amplitude 0.5*/
  unsigned short argsin2_1;            /* Tone2 Corrected argsin value for 1000Hz*/
  unsigned short argcos2_1;            /* Tone2 Corrected argcos value for 1000Hz*/
  unsigned short t2att_1;              /* Tone2 amplitude 0*/
  unsigned short argsin3_1;            /* Tone3 Corrected argsin value for 1500Hz*/
  unsigned short argcos3_1;            /* Tone3 Corrected argcos value for 1500Hz*/
  unsigned short t3att_1;              /* Tone3 amplitude 0*/
  unsigned short cosi[3];              /* Tone cosine outputs*/
  unsigned short sini[3];              /* Tone sine outputs (initialised to -1)*/
  unsigned short timer1;               /* Timer1 actual value*/
  unsigned short timer2;               /* Timer2 actual value*/
  unsigned short argsin1_2;            /* Working sin-value tone1*/
  unsigned short argcos1_2;            /* Working cos-value tone1*/
  unsigned short t1att_2;              /* Working attn-value tone1*/
  unsigned short argsin2_2;            /* Working sin-value tone2*/
  unsigned short argcos2_2;            /* Working cos-value tone2*/
  unsigned short t2att_2;              /* Working attn-value tone2*/
  unsigned short argsin3_2;            /* Working sin-value tone3*/
  unsigned short argcos3_2;            /* Working cos-value tone3*/
  unsigned short t3att_2;              /* Working attn-value tone3*/
  unsigned short tone_out;             /* Tones output*/
} gdsp_default_tonegen;

typedef struct
{
  unsigned short in_ptr;               /* Wideband Enhancer 8kHz input*/
  unsigned short out;                  /* Wideband Enhancer 16kHz output*/
  unsigned short ntaps1;               /* number of taps in anti-aliasing filter*/
  unsigned short coef1ptr;             /* Pointer to anti-aliasing filter coefficients buffer*/
  unsigned short dl1ptr;               /* Pointer to anti-aliasing filter taps buffer*/
  unsigned short oddeven;              /* state indicating odd or even 16kHz sample frame*/
  unsigned short idx1;                 /* Index in anti-aliasing filter taps/coeffs buffer*/
  unsigned short argsin_1;             /* argsin value for 3000 Hz carrier tone generation*/
  unsigned short argsin_2;             /* argcos value for carrier 3000 Hz tone generation*/
  unsigned short tone_1;               /* working value for carrier 3000 Hz tone generation*/
  unsigned short tone_2;               /* working value for carrier 3000 Hz tone generation*/
  unsigned short atttone;              /* working value for carrier 3000 Hz tone generation*/
  unsigned short ntaps2;               /* number of taps in anti-aliasing filter*/
  unsigned short coef2ptr;             /* Pointer to modulation filter coefficients buffer*/
  unsigned short dl2ptr;               /* Pointer to modulation filter taps buffer*/
  unsigned short idx2;                 /* Index in modulation filter taps/coeffs buffer*/
  unsigned short dl3ptr;               /* Pointer to phase compensation delay line buffer*/
  unsigned short idx3;                 /* Index in phase delay line buffer*/
  unsigned short coef1[46];            /* Anti-aliasing filter coefficients buffer*/
  unsigned short coef2[50];            /* Modulation filter coefficients buffer*/
  unsigned short dl1_line[99];         /* Anti-aliasing filter taps buffer*/
  unsigned short dl2_line[99];         /* Modulation filter taps buffer*/
  unsigned short dl3_line[99];         /* Phase compensation delayline taps buffer*/
} gdsp_default_widebandenhancer_99;

typedef struct
{
  unsigned short in1_ptr;              /* XOR input 1*/
  unsigned short in2_ptr;              /* XOR input 2*/
  unsigned short out;                  /* XOR output*/
} gdsp_default_xor;

typedef struct
{
  unsigned short in_ptr;               /* Zero cross detector input*/
  unsigned short out;                  /* Output (init value 0.1 = detection threshold. sign-bit indicates 0-cross detected)*/
} gdsp_default_zerocrossdetector;

typedef struct
{
  unsigned short srcliststart;         /* */
  unsigned short srclistend;           /* */
  unsigned short deststart;            /* */
  unsigned short zcross1outsrc;        /* */
  unsigned short zcross2outsrc;        /* */
} gdsp_default_zerocrossingdestinations;
#endif
