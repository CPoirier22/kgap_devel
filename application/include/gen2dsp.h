#ifndef gen2dsp_HEADER_INCLUDED
#define gen2dsp_HEADER_INCLUDED

/* ========================== LABEL definitions =============================== */

#define DSPRAMSEG_START    0x10900
#define DSPCODESTARTOFFSET 0x0000
#define DSPSTACK_START     0x11000
/*
 ********************************************************************************************
 * INTERRUPTS
 ********************************************************************************************
 */
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

#define ringtone_Buffer1_INT       INT2
#define ringtone_Buffer2_INT       INT3

   #ifdef GDSP_ASM

                    public _DSPDATA_START
                    public _DSPDATA_END
                    public _DSPCODE_START
                    public _DSPCODE_END

                    public _ADPCM_LOOP_DSPCODE_START

					public audioplayback
					public counter_event_ptr
					public counter_count
					public PowDetOut
/*
 ********************************************************************************************
 * ADPCM LOOP
 ********************************************************************************************
 */
                    public adpcm_Ear_Stage1
                    public adpcm_Ear_Stage1_START
                    public adpcm_Ear_Stage1_in_ptr
                    public adpcm_Ear_Stage1_c0
                    public adpcm_Ear_Stage1_c1
                    public adpcm_Ear_Stage1_c2
                    public adpcm_Ear_Stage1_c3
                    public adpcm_Ear_Stage1_c4
                    public adpcm_Ear_Stage1_in_att
                    public adpcm_Ear_Stage1_outgains
                    public adpcm_Ear_Stage1_z1
                    public adpcm_Ear_Stage1_z1o
                    public adpcm_Ear_Stage1_z2
                    public adpcm_Ear_Stage1_z2o
                    public adpcm_Ear_Stage1_out
                    public adpcm_Ear_Stage2
                    public adpcm_Ear_Stage2_START
                    public adpcm_Ear_Stage2_in_ptr
                    public adpcm_Ear_Stage2_c0
                    public adpcm_Ear_Stage2_c1
                    public adpcm_Ear_Stage2_c2
                    public adpcm_Ear_Stage2_c3
                    public adpcm_Ear_Stage2_c4
                    public adpcm_Ear_Stage2_in_att
                    public adpcm_Ear_Stage2_outgains
                    public adpcm_Ear_Stage2_z1
                    public adpcm_Ear_Stage2_z1o
                    public adpcm_Ear_Stage2_z2
                    public adpcm_Ear_Stage2_z2o
                    public adpcm_Ear_Stage2_out
                    public adpcm_Ear_Stage3
                    public adpcm_Ear_Stage3_START
                    public adpcm_Ear_Stage3_in_ptr
                    public adpcm_Ear_Stage3_c0
                    public adpcm_Ear_Stage3_c1
                    public adpcm_Ear_Stage3_c2
                    public adpcm_Ear_Stage3_c3
                    public adpcm_Ear_Stage3_c4
                    public adpcm_Ear_Stage3_in_att
                    public adpcm_Ear_Stage3_outgains
                    public adpcm_Ear_Stage3_z1
                    public adpcm_Ear_Stage3_z1o
                    public adpcm_Ear_Stage3_z2
                    public adpcm_Ear_Stage3_z2o
                    public adpcm_Ear_Stage3_out
                    public adpcm_Mic_filter
                    public adpcm_Mic_filter_START
                    public adpcm_Mic_filter_in_ptr
                    public adpcm_Mic_filter_c0
                    public adpcm_Mic_filter_c1
                    public adpcm_Mic_filter_c2
                    public adpcm_Mic_filter_c3
                    public adpcm_Mic_filter_c4
                    public adpcm_Mic_filter_in_att
                    public adpcm_Mic_filter_outgains
                    public adpcm_Mic_filter_z1
                    public adpcm_Mic_filter_z1o
                    public adpcm_Mic_filter_z2
                    public adpcm_Mic_filter_z2o
                    public adpcm_Mic_filter_out
                    public adpcm_SampleDelay
                    public adpcm_SampleDelay_START
                    public adpcm_SampleDelay_mode
                    public adpcm_SampleDelay_in_ptr
                    public adpcm_SampleDelay_out_ptr
                    public adpcm_SampleDelay_buffer_size
                    public adpcm_SampleDelay_buffer_ptr
                    public adpcm_SampleDelay_read_idx
                    public adpcm_SampleDelay_write_idx
                    public adpcm_SampleDelay_buffer_irq_size
                    public adpcm_SampleDelay_irq
                    public adpcm_SampleDelay_out
                    public adpcm_SampleDelay_taps
                    public adpcm_Constant1_START
                    public adpcm_Constant1_VALUE
                    public adpcm_Constant2_START
                    public adpcm_Constant2_VALUE
                    public adpcm_Constant3_START
                    public adpcm_Constant3_VALUE
                    public adpcm_Ear_Filt_InputAtt_START
                    public adpcm_Ear_Filt_InputAtt_VALUE
                    public adpcm_multinx1_START
                    public adpcm_multinx1_VALUE
                    public adpcm_Ear_att
                    public adpcm_Ear_att_START
                    public adpcm_Ear_att_in1_ptr
                    public adpcm_Ear_att_in2_ptr
                    public adpcm_Ear_att_in3_ptr
                    public adpcm_Ear_att_in1_atten
                    public adpcm_Ear_att_out
                    public adpcm_summator
                    public adpcm_summator_START
                    public adpcm_summator_in1_ptr
                    public adpcm_summator_in2_ptr
                    public adpcm_summator_in3_ptr
                    public adpcm_summator_in1_atten
                    public adpcm_summator_out
                    public adpcm_ADPCM_source
                    public adpcm_ADPCM_source_START
                    public adpcm_ADPCM_source_b0_nr_bits1
                    public adpcm_ADPCM_source_b0_nr_bits2
                    public adpcm_ADPCM_source_b0_nr_bits3
                    public adpcm_ADPCM_source_b0_swap_mode
                    public adpcm_ADPCM_source_b0_out_val
                    public adpcm_ADPCM_source_b0_out_bits
                    public adpcm_ADPCM_source_b0_buf_ptr
                    public adpcm_ADPCM_source_b0_buf_start
                    public adpcm_ADPCM_source_b0_buf_end
                    public adpcm_ADPCM_source_b0_flip_irq
                    public adpcm_ADPCM_source_b0_buffer_out1
                    public adpcm_ADPCM_source_b0_buffer_out2
                    public adpcm_ADPCM_source_g0_in1_ptr
                    public adpcm_ADPCM_source_g0_mode
                    public adpcm_ADPCM_source_g0_out1
                    public adpcm_ADPCM_source_g0_sr1
                    public adpcm_ADPCM_source_g0_a2r
                    public adpcm_ADPCM_source_g0_a1r
                    public adpcm_ADPCM_source_g0_dq0
                    public adpcm_ADPCM_source_g0_dq1
                    public adpcm_ADPCM_source_g0_dq2
                    public adpcm_ADPCM_source_g0_dq3
                    public adpcm_ADPCM_source_g0_dq4
                    public adpcm_ADPCM_source_g0_dq5
                    public adpcm_ADPCM_source_g0_br0
                    public adpcm_ADPCM_source_g0_br1
                    public adpcm_ADPCM_source_g0_br2
                    public adpcm_ADPCM_source_g0_br3
                    public adpcm_ADPCM_source_g0_br4
                    public adpcm_ADPCM_source_g0_br5
                    public adpcm_ADPCM_source_g0_dmsp
                    public adpcm_ADPCM_source_g0_dmlp
                    public adpcm_ADPCM_source_g0_apr
                    public adpcm_ADPCM_source_g0_yup
                    public adpcm_ADPCM_source_g0_ylp_lsb
                    public adpcm_ADPCM_source_g0_ylp_msb
                    public adpcm_ADPCM_source_g0_tdr
                    public adpcm_ADPCM_source_g0_pk0
                    public adpcm_ADPCM_source_g0_pk1
                    public adpcm_ADPCM_source_g0_sr0
                    public adpcm_ADPCM_source_g0_intlv_ptr
                    public adpcm_ADPCM_source_b1_nr_bits1
                    public adpcm_ADPCM_source_b1_nr_bits2
                    public adpcm_ADPCM_source_b1_nr_bits3
                    public adpcm_ADPCM_source_b1_swap_mode
                    public adpcm_ADPCM_source_b1_out_val
                    public adpcm_ADPCM_source_b1_out_bits
                    public adpcm_ADPCM_source_b1_buf_ptr
                    public adpcm_ADPCM_source_b1_buf_start
                    public adpcm_ADPCM_source_b1_buf_end
                    public adpcm_ADPCM_source_b1_flip_irq
                    public adpcm_ADPCM_source_b1_buffer_out1
                    public adpcm_ADPCM_source_b1_buffer_out2
                    public adpcm_ADPCM_source_g1_in1_ptr
                    public adpcm_ADPCM_source_g1_mode
                    public adpcm_ADPCM_source_g1_out1
                    public adpcm_ADPCM_source_g1_sr1
                    public adpcm_ADPCM_source_g1_a2r
                    public adpcm_ADPCM_source_g1_a1r
                    public adpcm_ADPCM_source_g1_dq0
                    public adpcm_ADPCM_source_g1_dq1
                    public adpcm_ADPCM_source_g1_dq2
                    public adpcm_ADPCM_source_g1_dq3
                    public adpcm_ADPCM_source_g1_dq4
                    public adpcm_ADPCM_source_g1_dq5
                    public adpcm_ADPCM_source_g1_br0
                    public adpcm_ADPCM_source_g1_br1
                    public adpcm_ADPCM_source_g1_br2
                    public adpcm_ADPCM_source_g1_br3
                    public adpcm_ADPCM_source_g1_br4
                    public adpcm_ADPCM_source_g1_br5
                    public adpcm_ADPCM_source_g1_dmsp
                    public adpcm_ADPCM_source_g1_dmlp
                    public adpcm_ADPCM_source_g1_apr
                    public adpcm_ADPCM_source_g1_yup
                    public adpcm_ADPCM_source_g1_ylp_lsb
                    public adpcm_ADPCM_source_g1_ylp_msb
                    public adpcm_ADPCM_source_g1_tdr
                    public adpcm_ADPCM_source_g1_pk0
                    public adpcm_ADPCM_source_g1_pk1
                    public adpcm_ADPCM_source_g1_sr0
                    public adpcm_ADPCM_source_g1_intlv_ptr
                    public adpcm_CODEC_Source
                    public adpcm_CODEC_Source_START
                    public adpcm_CODEC_Source_srcstart
                    public adpcm_CODEC_Source_srcend
                    public adpcm_CODEC_Source_destliststart
                    public adpcm_CODEC_Source_src_ptr1
                    public adpcm_CODEC_Source_src_ptr2
                    public adpcm_CODEC_Source_CODECMicGainSRC
                    public adpcm_CODEC_Source_CODECDataInSRC
                    public adpcm_ADPCM_Dest
                    public adpcm_ADPCM_Dest_START
                    public adpcm_ADPCM_Dest_g0_in1_ptr
                    public adpcm_ADPCM_Dest_g0_mode
                    public adpcm_ADPCM_Dest_g0_out1
                    public adpcm_ADPCM_Dest_g0_sr1
                    public adpcm_ADPCM_Dest_g0_a2r
                    public adpcm_ADPCM_Dest_g0_a1r
                    public adpcm_ADPCM_Dest_g0_dq0
                    public adpcm_ADPCM_Dest_g0_dq1
                    public adpcm_ADPCM_Dest_g0_dq2
                    public adpcm_ADPCM_Dest_g0_dq3
                    public adpcm_ADPCM_Dest_g0_dq4
                    public adpcm_ADPCM_Dest_g0_dq5
                    public adpcm_ADPCM_Dest_g0_br0
                    public adpcm_ADPCM_Dest_g0_br1
                    public adpcm_ADPCM_Dest_g0_br2
                    public adpcm_ADPCM_Dest_g0_br3
                    public adpcm_ADPCM_Dest_g0_br4
                    public adpcm_ADPCM_Dest_g0_br5
                    public adpcm_ADPCM_Dest_g0_dmsp
                    public adpcm_ADPCM_Dest_g0_dmlp
                    public adpcm_ADPCM_Dest_g0_apr
                    public adpcm_ADPCM_Dest_g0_yup
                    public adpcm_ADPCM_Dest_g0_ylp_lsb
                    public adpcm_ADPCM_Dest_g0_ylp_msb
                    public adpcm_ADPCM_Dest_g0_tdr
                    public adpcm_ADPCM_Dest_g0_pk0
                    public adpcm_ADPCM_Dest_g0_pk1
                    public adpcm_ADPCM_Dest_g0_sr0
                    public adpcm_ADPCM_Dest_g0_intlv_ptr
                    public adpcm_ADPCM_Dest_b0_in_ptr1
                    public adpcm_ADPCM_Dest_b0_in_ptr2
                    public adpcm_ADPCM_Dest_b0_nr_bits1
                    public adpcm_ADPCM_Dest_b0_nr_bits2
                    public adpcm_ADPCM_Dest_b0_nr_bits3
                    public adpcm_ADPCM_Dest_b0_swap_mode
                    public adpcm_ADPCM_Dest_b0_new_val
                    public adpcm_ADPCM_Dest_b0_new_bits
                    public adpcm_ADPCM_Dest_b0_buf_ptr
                    public adpcm_ADPCM_Dest_b0_buf_start
                    public adpcm_ADPCM_Dest_b0_buf_end
                    public adpcm_ADPCM_Dest_b0_flip_irq
                    public adpcm_ADPCM_Dest_g1_in1_ptr
                    public adpcm_ADPCM_Dest_g1_mode
                    public adpcm_ADPCM_Dest_g1_out1
                    public adpcm_ADPCM_Dest_g1_sr1
                    public adpcm_ADPCM_Dest_g1_a2r
                    public adpcm_ADPCM_Dest_g1_a1r
                    public adpcm_ADPCM_Dest_g1_dq0
                    public adpcm_ADPCM_Dest_g1_dq1
                    public adpcm_ADPCM_Dest_g1_dq2
                    public adpcm_ADPCM_Dest_g1_dq3
                    public adpcm_ADPCM_Dest_g1_dq4
                    public adpcm_ADPCM_Dest_g1_dq5
                    public adpcm_ADPCM_Dest_g1_br0
                    public adpcm_ADPCM_Dest_g1_br1
                    public adpcm_ADPCM_Dest_g1_br2
                    public adpcm_ADPCM_Dest_g1_br3
                    public adpcm_ADPCM_Dest_g1_br4
                    public adpcm_ADPCM_Dest_g1_br5
                    public adpcm_ADPCM_Dest_g1_dmsp
                    public adpcm_ADPCM_Dest_g1_dmlp
                    public adpcm_ADPCM_Dest_g1_apr
                    public adpcm_ADPCM_Dest_g1_yup
                    public adpcm_ADPCM_Dest_g1_ylp_lsb
                    public adpcm_ADPCM_Dest_g1_ylp_msb
                    public adpcm_ADPCM_Dest_g1_tdr
                    public adpcm_ADPCM_Dest_g1_pk0
                    public adpcm_ADPCM_Dest_g1_pk1
                    public adpcm_ADPCM_Dest_g1_sr0
                    public adpcm_ADPCM_Dest_g1_intlv_ptr
                    public adpcm_ADPCM_Dest_b1_in_ptr1
                    public adpcm_ADPCM_Dest_b1_in_ptr2
                    public adpcm_ADPCM_Dest_b1_nr_bits1
                    public adpcm_ADPCM_Dest_b1_nr_bits2
                    public adpcm_ADPCM_Dest_b1_nr_bits3
                    public adpcm_ADPCM_Dest_b1_swap_mode
                    public adpcm_ADPCM_Dest_b1_new_val
                    public adpcm_ADPCM_Dest_b1_new_bits
                    public adpcm_ADPCM_Dest_b1_buf_ptr
                    public adpcm_ADPCM_Dest_b1_buf_start
                    public adpcm_ADPCM_Dest_b1_buf_end
                    public adpcm_ADPCM_Dest_b1_flip_irq
                    public adpcm_CODEC_Dest
                    public adpcm_CODEC_Dest_START
                    public adpcm_CODEC_Dest_srcliststart
                    public adpcm_CODEC_Dest_srclistend
                    public adpcm_CODEC_Dest_destliststart
                    public adpcm_CODEC_Dest_CODECMicGainOutSRC
                    public adpcm_CODEC_Dest_CODECDataOutSRC
                    public adpcm_CODEC_Dest_CODECMicGainOutDEST
                    public adpcm_CODEC_Dest_CODECDataOutDEST

   #else  /* GDSP_ASM */
                    extern WORD _DSPDATA_START;
                    extern WORD _DSPDATA_END;
                    extern WORD _DSPCODE_START;
                    extern WORD _DSPCODE_END;

                    extern WORD _ADPCM_LOOP_DSPCODE_START;

					extern WORD audioplayback;
					extern WORD counter_event_ptr;
					extern WORD counter_count;
					extern WORD PowDetOut;

/*
 ********************************************************************************************
 * ADPCM LOOP
 ********************************************************************************************
 */
                    extern WORD adpcm_Ear_Stage1;
                    extern WORD adpcm_Ear_Stage1_START;
                    extern WORD adpcm_Ear_Stage1_in_ptr;
                    extern WORD adpcm_Ear_Stage1_c0;
                    extern WORD adpcm_Ear_Stage1_c1;
                    extern WORD adpcm_Ear_Stage1_c2;
                    extern WORD adpcm_Ear_Stage1_c3;
                    extern WORD adpcm_Ear_Stage1_c4;
                    extern WORD adpcm_Ear_Stage1_in_att;
                    extern WORD adpcm_Ear_Stage1_outgains;
                    extern WORD adpcm_Ear_Stage1_z1;
                    extern WORD adpcm_Ear_Stage1_z1o;
                    extern WORD adpcm_Ear_Stage1_z2;
                    extern WORD adpcm_Ear_Stage1_z2o;
                    extern WORD adpcm_Ear_Stage1_out;
                    extern WORD adpcm_Ear_Stage2;
                    extern WORD adpcm_Ear_Stage2_START;
                    extern WORD adpcm_Ear_Stage2_in_ptr;
                    extern WORD adpcm_Ear_Stage2_c0;
                    extern WORD adpcm_Ear_Stage2_c1;
                    extern WORD adpcm_Ear_Stage2_c2;
                    extern WORD adpcm_Ear_Stage2_c3;
                    extern WORD adpcm_Ear_Stage2_c4;
                    extern WORD adpcm_Ear_Stage2_in_att;
                    extern WORD adpcm_Ear_Stage2_outgains;
                    extern WORD adpcm_Ear_Stage2_z1;
                    extern WORD adpcm_Ear_Stage2_z1o;
                    extern WORD adpcm_Ear_Stage2_z2;
                    extern WORD adpcm_Ear_Stage2_z2o;
                    extern WORD adpcm_Ear_Stage2_out;
                    extern WORD adpcm_Ear_Stage3;
                    extern WORD adpcm_Ear_Stage3_START;
                    extern WORD adpcm_Ear_Stage3_in_ptr;
                    extern WORD adpcm_Ear_Stage3_c0;
                    extern WORD adpcm_Ear_Stage3_c1;
                    extern WORD adpcm_Ear_Stage3_c2;
                    extern WORD adpcm_Ear_Stage3_c3;
                    extern WORD adpcm_Ear_Stage3_c4;
                    extern WORD adpcm_Ear_Stage3_in_att;
                    extern WORD adpcm_Ear_Stage3_outgains;
                    extern WORD adpcm_Ear_Stage3_z1;
                    extern WORD adpcm_Ear_Stage3_z1o;
                    extern WORD adpcm_Ear_Stage3_z2;
                    extern WORD adpcm_Ear_Stage3_z2o;
                    extern WORD adpcm_Ear_Stage3_out;
                    extern WORD adpcm_Mic_filter;
                    extern WORD adpcm_Mic_filter_START;
                    extern WORD adpcm_Mic_filter_in_ptr;
                    extern WORD adpcm_Mic_filter_c0;
                    extern WORD adpcm_Mic_filter_c1;
                    extern WORD adpcm_Mic_filter_c2;
                    extern WORD adpcm_Mic_filter_c3;
                    extern WORD adpcm_Mic_filter_c4;
                    extern WORD adpcm_Mic_filter_in_att;
                    extern WORD adpcm_Mic_filter_outgains;
                    extern WORD adpcm_Mic_filter_z1;
                    extern WORD adpcm_Mic_filter_z1o;
                    extern WORD adpcm_Mic_filter_z2;
                    extern WORD adpcm_Mic_filter_z2o;
                    extern WORD adpcm_Mic_filter_out;
                    extern WORD adpcm_SampleDelay;
                    extern WORD adpcm_SampleDelay_START;
                    extern WORD adpcm_SampleDelay_mode;
                    extern WORD adpcm_SampleDelay_in_ptr;
                    extern WORD adpcm_SampleDelay_out_ptr;
                    extern WORD adpcm_SampleDelay_buffer_size;
                    extern WORD adpcm_SampleDelay_buffer_ptr;
                    extern WORD adpcm_SampleDelay_read_idx;
                    extern WORD adpcm_SampleDelay_write_idx;
                    extern WORD adpcm_SampleDelay_buffer_irq_size;
                    extern WORD adpcm_SampleDelay_irq;
                    extern WORD adpcm_SampleDelay_out;
                    extern WORD adpcm_SampleDelay_taps;
                    extern WORD adpcm_Constant1_START;
                    extern WORD adpcm_Constant1_VALUE;
                    extern WORD adpcm_Constant2_START;
                    extern WORD adpcm_Constant2_VALUE;
                    extern WORD adpcm_Constant3_START;
                    extern WORD adpcm_Constant3_VALUE;
                    extern WORD adpcm_Ear_Filt_InputAtt_START;
                    extern WORD adpcm_Ear_Filt_InputAtt_VALUE;
                    extern WORD adpcm_multinx1_START;
                    extern WORD adpcm_multinx1_VALUE;
                    extern WORD adpcm_Ear_att;
                    extern WORD adpcm_Ear_att_START;
                    extern WORD adpcm_Ear_att_in1_ptr;
                    extern WORD adpcm_Ear_att_in2_ptr;
                    extern WORD adpcm_Ear_att_in3_ptr;
                    extern WORD adpcm_Ear_att_in1_atten;
                    extern WORD adpcm_Ear_att_out;
                    extern WORD adpcm_summator;
                    extern WORD adpcm_summator_START;
                    extern WORD adpcm_summator_in1_ptr;
                    extern WORD adpcm_summator_in2_ptr;
                    extern WORD adpcm_summator_in3_ptr;
                    extern WORD adpcm_summator_in1_atten;
                    extern WORD adpcm_summator_out;
                    extern WORD adpcm_ADPCM_source;
                    extern WORD adpcm_ADPCM_source_START;
                    extern WORD adpcm_ADPCM_source_b0_nr_bits1;
                    extern WORD adpcm_ADPCM_source_b0_nr_bits2;
                    extern WORD adpcm_ADPCM_source_b0_nr_bits3;
                    extern WORD adpcm_ADPCM_source_b0_swap_mode;
                    extern WORD adpcm_ADPCM_source_b0_out_val;
                    extern WORD adpcm_ADPCM_source_b0_out_bits;
                    extern WORD adpcm_ADPCM_source_b0_buf_ptr;
                    extern WORD adpcm_ADPCM_source_b0_buf_start;
                    extern WORD adpcm_ADPCM_source_b0_buf_end;
                    extern WORD adpcm_ADPCM_source_b0_flip_irq;
                    extern WORD adpcm_ADPCM_source_b0_buffer_out1;
                    extern WORD adpcm_ADPCM_source_b0_buffer_out2;
                    extern WORD adpcm_ADPCM_source_g0_in1_ptr;
                    extern WORD adpcm_ADPCM_source_g0_mode;
                    extern WORD adpcm_ADPCM_source_g0_out1;
                    extern WORD adpcm_ADPCM_source_g0_sr1;
                    extern WORD adpcm_ADPCM_source_g0_a2r;
                    extern WORD adpcm_ADPCM_source_g0_a1r;
                    extern WORD adpcm_ADPCM_source_g0_dq0;
                    extern WORD adpcm_ADPCM_source_g0_dq1;
                    extern WORD adpcm_ADPCM_source_g0_dq2;
                    extern WORD adpcm_ADPCM_source_g0_dq3;
                    extern WORD adpcm_ADPCM_source_g0_dq4;
                    extern WORD adpcm_ADPCM_source_g0_dq5;
                    extern WORD adpcm_ADPCM_source_g0_br0;
                    extern WORD adpcm_ADPCM_source_g0_br1;
                    extern WORD adpcm_ADPCM_source_g0_br2;
                    extern WORD adpcm_ADPCM_source_g0_br3;
                    extern WORD adpcm_ADPCM_source_g0_br4;
                    extern WORD adpcm_ADPCM_source_g0_br5;
                    extern WORD adpcm_ADPCM_source_g0_dmsp;
                    extern WORD adpcm_ADPCM_source_g0_dmlp;
                    extern WORD adpcm_ADPCM_source_g0_apr;
                    extern WORD adpcm_ADPCM_source_g0_yup;
                    extern WORD adpcm_ADPCM_source_g0_ylp_lsb;
                    extern WORD adpcm_ADPCM_source_g0_ylp_msb;
                    extern WORD adpcm_ADPCM_source_g0_tdr;
                    extern WORD adpcm_ADPCM_source_g0_pk0;
                    extern WORD adpcm_ADPCM_source_g0_pk1;
                    extern WORD adpcm_ADPCM_source_g0_sr0;
                    extern WORD adpcm_ADPCM_source_g0_intlv_ptr;
                    extern WORD adpcm_ADPCM_source_b1_nr_bits1;
                    extern WORD adpcm_ADPCM_source_b1_nr_bits2;
                    extern WORD adpcm_ADPCM_source_b1_nr_bits3;
                    extern WORD adpcm_ADPCM_source_b1_swap_mode;
                    extern WORD adpcm_ADPCM_source_b1_out_val;
                    extern WORD adpcm_ADPCM_source_b1_out_bits;
                    extern WORD adpcm_ADPCM_source_b1_buf_ptr;
                    extern WORD adpcm_ADPCM_source_b1_buf_start;
                    extern WORD adpcm_ADPCM_source_b1_buf_end;
                    extern WORD adpcm_ADPCM_source_b1_flip_irq;
                    extern WORD adpcm_ADPCM_source_b1_buffer_out1;
                    extern WORD adpcm_ADPCM_source_b1_buffer_out2;
                    extern WORD adpcm_ADPCM_source_g1_in1_ptr;
                    extern WORD adpcm_ADPCM_source_g1_mode;
                    extern WORD adpcm_ADPCM_source_g1_out1;
                    extern WORD adpcm_ADPCM_source_g1_sr1;
                    extern WORD adpcm_ADPCM_source_g1_a2r;
                    extern WORD adpcm_ADPCM_source_g1_a1r;
                    extern WORD adpcm_ADPCM_source_g1_dq0;
                    extern WORD adpcm_ADPCM_source_g1_dq1;
                    extern WORD adpcm_ADPCM_source_g1_dq2;
                    extern WORD adpcm_ADPCM_source_g1_dq3;
                    extern WORD adpcm_ADPCM_source_g1_dq4;
                    extern WORD adpcm_ADPCM_source_g1_dq5;
                    extern WORD adpcm_ADPCM_source_g1_br0;
                    extern WORD adpcm_ADPCM_source_g1_br1;
                    extern WORD adpcm_ADPCM_source_g1_br2;
                    extern WORD adpcm_ADPCM_source_g1_br3;
                    extern WORD adpcm_ADPCM_source_g1_br4;
                    extern WORD adpcm_ADPCM_source_g1_br5;
                    extern WORD adpcm_ADPCM_source_g1_dmsp;
                    extern WORD adpcm_ADPCM_source_g1_dmlp;
                    extern WORD adpcm_ADPCM_source_g1_apr;
                    extern WORD adpcm_ADPCM_source_g1_yup;
                    extern WORD adpcm_ADPCM_source_g1_ylp_lsb;
                    extern WORD adpcm_ADPCM_source_g1_ylp_msb;
                    extern WORD adpcm_ADPCM_source_g1_tdr;
                    extern WORD adpcm_ADPCM_source_g1_pk0;
                    extern WORD adpcm_ADPCM_source_g1_pk1;
                    extern WORD adpcm_ADPCM_source_g1_sr0;
                    extern WORD adpcm_ADPCM_source_g1_intlv_ptr;
                    extern WORD adpcm_CODEC_Source;
                    extern WORD adpcm_CODEC_Source_START;
                    extern WORD adpcm_CODEC_Source_srcstart;
                    extern WORD adpcm_CODEC_Source_srcend;
                    extern WORD adpcm_CODEC_Source_destliststart;
                    extern WORD adpcm_CODEC_Source_src_ptr1;
                    extern WORD adpcm_CODEC_Source_src_ptr2;
                    extern WORD adpcm_CODEC_Source_CODECMicGainSRC;
                    extern WORD adpcm_CODEC_Source_CODECDataInSRC;
                    extern WORD adpcm_ADPCM_Dest;
                    extern WORD adpcm_ADPCM_Dest_START;
                    extern WORD adpcm_ADPCM_Dest_g0_in1_ptr;
                    extern WORD adpcm_ADPCM_Dest_g0_mode;
                    extern WORD adpcm_ADPCM_Dest_g0_out1;
                    extern WORD adpcm_ADPCM_Dest_g0_sr1;
                    extern WORD adpcm_ADPCM_Dest_g0_a2r;
                    extern WORD adpcm_ADPCM_Dest_g0_a1r;
                    extern WORD adpcm_ADPCM_Dest_g0_dq0;
                    extern WORD adpcm_ADPCM_Dest_g0_dq1;
                    extern WORD adpcm_ADPCM_Dest_g0_dq2;
                    extern WORD adpcm_ADPCM_Dest_g0_dq3;
                    extern WORD adpcm_ADPCM_Dest_g0_dq4;
                    extern WORD adpcm_ADPCM_Dest_g0_dq5;
                    extern WORD adpcm_ADPCM_Dest_g0_br0;
                    extern WORD adpcm_ADPCM_Dest_g0_br1;
                    extern WORD adpcm_ADPCM_Dest_g0_br2;
                    extern WORD adpcm_ADPCM_Dest_g0_br3;
                    extern WORD adpcm_ADPCM_Dest_g0_br4;
                    extern WORD adpcm_ADPCM_Dest_g0_br5;
                    extern WORD adpcm_ADPCM_Dest_g0_dmsp;
                    extern WORD adpcm_ADPCM_Dest_g0_dmlp;
                    extern WORD adpcm_ADPCM_Dest_g0_apr;
                    extern WORD adpcm_ADPCM_Dest_g0_yup;
                    extern WORD adpcm_ADPCM_Dest_g0_ylp_lsb;
                    extern WORD adpcm_ADPCM_Dest_g0_ylp_msb;
                    extern WORD adpcm_ADPCM_Dest_g0_tdr;
                    extern WORD adpcm_ADPCM_Dest_g0_pk0;
                    extern WORD adpcm_ADPCM_Dest_g0_pk1;
                    extern WORD adpcm_ADPCM_Dest_g0_sr0;
                    extern WORD adpcm_ADPCM_Dest_g0_intlv_ptr;
                    extern WORD adpcm_ADPCM_Dest_b0_in_ptr1;
                    extern WORD adpcm_ADPCM_Dest_b0_in_ptr2;
                    extern WORD adpcm_ADPCM_Dest_b0_nr_bits1;
                    extern WORD adpcm_ADPCM_Dest_b0_nr_bits2;
                    extern WORD adpcm_ADPCM_Dest_b0_nr_bits3;
                    extern WORD adpcm_ADPCM_Dest_b0_swap_mode;
                    extern WORD adpcm_ADPCM_Dest_b0_new_val;
                    extern WORD adpcm_ADPCM_Dest_b0_new_bits;
                    extern WORD adpcm_ADPCM_Dest_b0_buf_ptr;
                    extern WORD adpcm_ADPCM_Dest_b0_buf_start;
                    extern WORD adpcm_ADPCM_Dest_b0_buf_end;
                    extern WORD adpcm_ADPCM_Dest_b0_flip_irq;
                    extern WORD adpcm_ADPCM_Dest_g1_in1_ptr;
                    extern WORD adpcm_ADPCM_Dest_g1_mode;
                    extern WORD adpcm_ADPCM_Dest_g1_out1;
                    extern WORD adpcm_ADPCM_Dest_g1_sr1;
                    extern WORD adpcm_ADPCM_Dest_g1_a2r;
                    extern WORD adpcm_ADPCM_Dest_g1_a1r;
                    extern WORD adpcm_ADPCM_Dest_g1_dq0;
                    extern WORD adpcm_ADPCM_Dest_g1_dq1;
                    extern WORD adpcm_ADPCM_Dest_g1_dq2;
                    extern WORD adpcm_ADPCM_Dest_g1_dq3;
                    extern WORD adpcm_ADPCM_Dest_g1_dq4;
                    extern WORD adpcm_ADPCM_Dest_g1_dq5;
                    extern WORD adpcm_ADPCM_Dest_g1_br0;
                    extern WORD adpcm_ADPCM_Dest_g1_br1;
                    extern WORD adpcm_ADPCM_Dest_g1_br2;
                    extern WORD adpcm_ADPCM_Dest_g1_br3;
                    extern WORD adpcm_ADPCM_Dest_g1_br4;
                    extern WORD adpcm_ADPCM_Dest_g1_br5;
                    extern WORD adpcm_ADPCM_Dest_g1_dmsp;
                    extern WORD adpcm_ADPCM_Dest_g1_dmlp;
                    extern WORD adpcm_ADPCM_Dest_g1_apr;
                    extern WORD adpcm_ADPCM_Dest_g1_yup;
                    extern WORD adpcm_ADPCM_Dest_g1_ylp_lsb;
                    extern WORD adpcm_ADPCM_Dest_g1_ylp_msb;
                    extern WORD adpcm_ADPCM_Dest_g1_tdr;
                    extern WORD adpcm_ADPCM_Dest_g1_pk0;
                    extern WORD adpcm_ADPCM_Dest_g1_pk1;
                    extern WORD adpcm_ADPCM_Dest_g1_sr0;
                    extern WORD adpcm_ADPCM_Dest_g1_intlv_ptr;
                    extern WORD adpcm_ADPCM_Dest_b1_in_ptr1;
                    extern WORD adpcm_ADPCM_Dest_b1_in_ptr2;
                    extern WORD adpcm_ADPCM_Dest_b1_nr_bits1;
                    extern WORD adpcm_ADPCM_Dest_b1_nr_bits2;
                    extern WORD adpcm_ADPCM_Dest_b1_nr_bits3;
                    extern WORD adpcm_ADPCM_Dest_b1_swap_mode;
                    extern WORD adpcm_ADPCM_Dest_b1_new_val;
                    extern WORD adpcm_ADPCM_Dest_b1_new_bits;
                    extern WORD adpcm_ADPCM_Dest_b1_buf_ptr;
                    extern WORD adpcm_ADPCM_Dest_b1_buf_start;
                    extern WORD adpcm_ADPCM_Dest_b1_buf_end;
                    extern WORD adpcm_ADPCM_Dest_b1_flip_irq;
                    extern WORD adpcm_CODEC_Dest;
                    extern WORD adpcm_CODEC_Dest_START;
                    extern WORD adpcm_CODEC_Dest_srcliststart;
                    extern WORD adpcm_CODEC_Dest_srclistend;
                    extern WORD adpcm_CODEC_Dest_destliststart;
                    extern WORD adpcm_CODEC_Dest_CODECMicGainOutSRC;
                    extern WORD adpcm_CODEC_Dest_CODECDataOutSRC;
                    extern WORD adpcm_CODEC_Dest_CODECMicGainOutDEST;
                    extern WORD adpcm_CODEC_Dest_CODECDataOutDEST;
   #endif /* GDSP_ASM */
#endif    /* gen2dsp_HEADER_INCLUDED */
