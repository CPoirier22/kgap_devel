#include "gdsp_local_config.h"         // User h-file for defining where to get opcodes from
#include "gdsp_all_inits.h"

const unsigned short custom_backgroundtrigger[] =
{
  GDSP_INIT_CTRL_PTR | 1,
  GDSP_INIT_CTRL_DEFAULT | 1,
  16,
  GDSP_INIT_CTRL_END    // End of Init structure
};
gdsp_custom_backgroundtrigger* p_custom_backgroundtrigger;

const unsigned short paec[] =
{
  GDSP_INIT_CTRL_PTR     | 2,
  GDSP_INIT_CTRL_REL_PTR | 1,
  70,                                  // out_ptr
  GDSP_INIT_CTRL_CONST_PTR | 1,
  _CFFT_TWIDDLE_128,                   // twiddle_ptr
  GDSP_INIT_CTRL_DEFAULT | 1,
  0x0080,                              // twiddle_size
  GDSP_INIT_CTRL_REL_PTR | 1,
  72,                                  // window_ptr
  GDSP_INIT_CTRL_DEFAULT | 1,
  0x0080,                              // window_size
  GDSP_INIT_CTRL_REL_PTR | 10,
  71,                                  // fftbuf_spkr_ptr
  71,                                  // fftbuf_mic_ptr
  80,                                  // paecband_ptr
  73,                                  // xpow_ptr
  74,                                  // ypow_ptr
  75,                                  // ccxx_ptr
  76,                                  // ccxy_ptr
  77,                                  // ccyy_ptr
  78,                                  // cc_ptr
  79,                                  // cc_af_ptr
  GDSP_INIT_CTRL_DEFAULT | (824+20-64-63),//+10+30+2), (-64: window array; -63: 3 paecband arrays)
  0x0080,                              // fftsize
  0x0040,                              // framesize
  0x8000,                              // fftscale
  0x8000,                              // ifftscale
  0x0000,                              // fftmode
  0x000C,                              // npart
  0x41BF,                              // mode   0x41BF SETS ALL NOISE STUFF OFF, 0x47FF ALL ON,
  0x0004,                              // delaycompspecs
  0x00C8,                              // ibuf_size
  0x0000,                              // ibuf_idx
  0x00C8,                              // obuf_size
  0x0000,                              // obuf_idx
  0x0000,                              // init
  0x0001,                              // noiseestgainshft
  0x0000,                              // noiseestspkgainshft
  0x000F,                              // dtdcount_init
  0x0002,                              // gamma
  0x0106,                              // cctc
  0x2000,                              // beta
  0x0900,                              // attlimit				- default: 0x0100  my val 0x0401, 0x0900
  0x0CCC,                              // dtdthr
  0x6CCC,                              // dtdthr2
  0x0666,                              // dtdthr3
  0x036A,                              // dtdsmooth
  0x0000,                              // dtddecay
  0x2000,                              // dtdwgain_full_thr
  0x3333,                              // dtdwgain_part_thr
  0x000D,                              // noiseest1
  0x020C,                              // noiseest2
  0x0006,                              // noiseest3
  0x7FFF,                              // noiseattlimit			- default: 0x2879  my val 0x7FFF
  0x6666,                              // nsuppsmtra
  0x0EA1,                              // nsuppsmsta
  0xC000,                              // nsstathr
  0x0148,                              // retainnoisethr1div
 //settings from version 15
//  0x0050,                              // attlimitthr1div		- default: 0x0CCD my val 0x0050 DEFS FROM AN-162 appenA 0x3000 	0x0147 0x2FFF  0x0050
//  0x0001,                              // smooththr				- default: 0x6000 my val 0x0001 DEFS FROM AN-162 appenA 0x7000 	0x2FFF 0x07FF  0x2FFF
//  0x1000,                              // smoothdef				- default: 0x6000 my val 0x05FF DEFS FROM AN-162 appenA 0x5000 	0x0250 0x07FF
//  0x0200,                              // smoothlow				- default: 0x0666 my val 0x0200 DEFS FROM AN-162 appenA 0x0333 	0x0666 0x0333  0x0333
//  0x7FFF,                              // smoothtop				- default: 0x7600 my val 0x7FFF DEFS FROM AN-162 appenA 0x7600 	0x7FFF 0x7600  0x7600
//settings Dave and Carl derived
  0x0147,                              // attlimitthr1div		- default: 0x0CCD my val 0x0050 DEFS FROM AN-162 appenA 0x3000 	0x0147 0x2FFF  0x0050
  0x2FFF,                              // smooththr				- default: 0x6000 my val 0x0001 DEFS FROM AN-162 appenA 0x7000 	0x2FFF 0x07FF  0x2FFF
  0x1000,                              // smoothdef				- default: 0x6000 my val 0x05FF DEFS FROM AN-162 appenA 0x5000 	0x0250 0x07FF
  0x0666,                              // smoothlow				- default: 0x0666 my val 0x0200 DEFS FROM AN-162 appenA 0x0333 	0x0666 0x0333  0x0333
  0x7600,                              // smoothtop				- default: 0x7600 my val 0x7FFF DEFS FROM AN-162 appenA 0x7600 	0x7FFF 0x7600  0x7600
 //default settings
//  0x0CCD,                              // attlimitthr1div		- default: 0x0CCD my val 0x0050 DEFS FROM AN-162 appenA 0x3000 	0x0147 0x2FFF  0x0050
//  0x278A,                              // smooththr				- default: 0x6000 my val 0x0001 DEFS FROM AN-162 appenA 0x7000 	0x2FFF 0x07FF  0x2FFF
//  0x7FFF,                              // smoothdef				- default: 0x6000 my val 0x05FF DEFS FROM AN-162 appenA 0x5000 	0x0250 0x07FF
//  0x0A00,                              // smoothlow				- default: 0x0666 my val 0x0200 DEFS FROM AN-162 appenA 0x0333 	0x0666 0x0333  0x0333
//  0x7FFF,                              // smoothtop				- default: 0x7600 my val 0x7FFF DEFS FROM AN-162 appenA 0x7600 	0x7FFF 0x7600  0x7600
  0x0001,                              // winitial
  0x000F,                              // dtdcount
  0x0000,                              // wdelay
  0x0000,                              // wdelay_af
  0x0000,                              // wgain
  0x0000,                              // wgain_af
  0x0001,                              // erlenum
  0x0001,                              // erleden
  0x0000,                              // mse
  0x0000,                              // mse_af
  0x0001,                              // msenrm
  0x0000,                              // bandshift_ptr
  0x0000,                              // extra_shift
  0x000E,                              // intshift_maxnorm
  0x0000,                              // mic_shift_ptr
  0x0000,                              // spk_shift_ptr
  0x0000,                              // dummy for 32 bit alignment
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,   // cmplx_buf
//  0x0192,0x04B6,0x07D9,0x0AFB,0x0E1C,0x113A,0x1455,0x176E,0x1A82,0x1D93,0x209F,0x23A6,0x26A8,0x29A3,0x2C99,0x2F87,0x326E,0x354D,0x3824,0x3AF2,0x3DB8,0x4073,0x4325,0x45CD,0x4869,0x4AFB,0x4D81,0x4FFB,0x5268,0x54C9,0x571D,0x5964,// window 0-31
//  0x5B9C,0x5DC7,0x5FE3,0x61F0,0x63EE,0x65DD,0x67BC,0x698B,0x6B4A,0x6CF8,0x6E96,0x7022,0x719D,0x7307,0x745F,0x75A5,0x76D8,0x77FA,0x7909,0x7A05,0x7AEE,0x7BC5,0x7C88,0x7D39,0x7DD5,0x7E5F,0x7ED5,0x7F37,0x7F86,0x7FC1,0x7FE9,0x7FFD,// window 32-63
  //  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,   // window
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,   // xpow
  0,0,0,0,0,0,0,0,0,0,0,0,             // ypow
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,   // ccxx
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,   // ccxy
  0,0,0,0,0,0,0,0,0,0,0,0,             // ccyy
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,   // cc
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,   // cc_af
  //init,var_y ,var_e ,vareaf,w     ,w_af  ,attlim,attlim,nattli,nsvars,nsdeci,nsstat,noisee,noise2,noispk,ypowes,ypowaf,partms,partaf,partms,dtdcou
  0x0002,0x0001,0x0001,0x0001,0x04CC,0x04CC,0x0900,0x0900,0x7FFF,0x0001,0x0001,0x0001,0x0100,0x0001,0x0100,0x0001,0x0001,0x0000,0x0000,0x0000,0x000F,   // paec_subband_1
  0x0004,0x0001,0x0001,0x0001,0x04CC,0x04CC,0x0900,0x0900,0x7FFF,0x0001,0x0001,0x0001,0x0100,0x0001,0x0100,0x0001,0x0001,0x0000,0x0000,0x0000,0x000F,   // paec_subband_2
  0x0006,0x0001,0x0001,0x0001,0x04CC,0x04CC,0x0900,0x0900,0x7FFF,0x0001,0x0001,0x0001,0x0100,0x0001,0x0100,0x0001,0x0001,0x0000,0x0000,0x0000,0x000F,   // paec_subband_3
  0x0008,0x0001,0x0001,0x0001,0x04CC,0x04CC,0x0900,0x0900,0x7FFF,0x0001,0x0001,0x0001,0x0100,0x0001,0x0100,0x0001,0x0001,0x0000,0x0000,0x0000,0x000F,   // paec_subband_4
  0x000A,0x0001,0x0001,0x0001,0x04CC,0x04CC,0x0900,0x0900,0x7FFF,0x0001,0x0001,0x0001,0x0100,0x0001,0x0100,0x0001,0x0001,0x0000,0x0000,0x0000,0x000F,   // paec_subband_5
  0x000E,0x0001,0x0001,0x0001,0x04CC,0x04CC,0x0900,0x0900,0x7FFF,0x0001,0x0001,0x0001,0x0100,0x0001,0x0100,0x0001,0x0001,0x0000,0x0000,0x0000,0x000F,   // paec_subband_6
  0x0013,0x0001,0x0001,0x0001,0x04CC,0x04CC,0x0900,0x0900,0x7FFF,0x0001,0x0001,0x0001,0x0100,0x0001,0x0100,0x0001,0x0001,0x0000,0x0000,0x0000,0x000F,   // paec_subband_7
  0x001A,0x0001,0x0001,0x0001,0x04CC,0x04CC,0x0900,0x0900,0x7FFF,0x0001,0x0001,0x0001,0x0100,0x0001,0x0100,0x0001,0x0001,0x0000,0x0000,0x0000,0x000F,   // paec_subband_8
  0x0022,0x0001,0x0001,0x0001,0x04CC,0x04CC,0x0900,0x0900,0x7FFF,0x0001,0x0001,0x0001,0x0100,0x0001,0x0100,0x0001,0x0001,0x0000,0x0000,0x0000,0x000F,   // paec_subband_9
  0x002D,0x0001,0x0001,0x0001,0x04CC,0x04CC,0x0900,0x0900,0x7FFF,0x0001,0x0001,0x0001,0x0100,0x0001,0x0100,0x0001,0x0001,0x0000,0x0000,0x0000,0x000F,   // paec_subband_10
  0x0036,0x0001,0x0001,0x0001,0x04CC,0x04CC,0x0900,0x0900,0x7FFF,0x0001,0x0001,0x0001,0x0100,0x0001,0x0100,0x0001,0x0001,0x0000,0x0000,0x0000,0x000F,   // paec_subband_11
  0x0041,0x0001,0x0001,0x0001,0x04CC,0x04CC,0x0900,0x0900,0x7FFF,0x0001,0x0001,0x0001,0x0100,0x0001,0x0100,0x0001,0x0001,0x0000,0x0000,0x0000,0x000F,   // paec_subband_12
//  0x0000,0x0001,0x0001,0x0001,0x04CC,0x04CC,0x0900,0x0900,0x7FFF,0x0001,0x0001,0x0001,0x0100,0x0001,0x0100,0x0001,0x0001,0x0000,0x0000,0x0000,0x000F,   // paec_subband_13
//  0x0000,0x0001,0x0001,0x0001,0x04CC,0x04CC,0x0900,0x0900,0x7FFF,0x0001,0x0001,0x0001,0x0100,0x0001,0x0100,0x0001,0x0001,0x0000,0x0000,0x0000,0x000F,   // paec_subband_14
//  0x0000,0x0001,0x0001,0x0001,0x04CC,0x04CC,0x0900,0x0900,0x7FFF,0x0001,0x0001,0x0001,0x0100,0x0001,0x0100,0x0001,0x0001,0x0000,0x0000,0x0000,0x000F,   // paec_subband_15
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, // bandshift
  GDSP_INIT_CTRL_END                   // End of Init structure
};
const unsigned short paec_code[6] =
{
  CALL_INSTR, PAEC,
  LDO_INSTR, 0,
  IRQ_INSTR, PAEC_INT
};
gdsp_paec* p_paec;

const unsigned short out_buffer[] =
{
  GDSP_INIT_CTRL_DEFAULT | 2,
  0x0000,//0x0002,                              // mode
  0,                                   // in_ptr
  GDSP_INIT_CTRL_REL_PTR | 1,
  9,                                   // out_ptr
  GDSP_INIT_CTRL_DEFAULT | 1,
  0x0C8,//0x000C,                              // buffer_size
  GDSP_INIT_CTRL_REL_PTR | 1,
  10,                                  // buffer_ptr
  GDSP_INIT_CTRL_DEFAULT | 5,
  0x0040,                              // read_idx FFTsize-framesize
  0x007F,                              // write_idx
  0x00C6,                              // buffer_irq_size
  0,                                   // irq
  0,                                   // out
  GDSP_INIT_CTRL_ZERO | 200,           //GDSP_INIT_CTRL_ZERO | 12,            // taps
  GDSP_INIT_CTRL_END                   // End of Init structure
};
const unsigned short out_buffer_code[8] =
{
  CALL_INSTR, CBUFFER,
  LDO_INSTR, 0,
  LDC_INSTR, 0,
  CIRQ_INSTR, OUT_BUFFER_INT
};
gdsp_playbackbuffer_12* p_out_buffer;

const unsigned short delayline_buffer[] =
{
    GDSP_INIT_CTRL_DEFAULT | 1,
    0x0003,                              // mode
    GDSP_INIT_CTRL_PTR     | 1,
    GDSP_INIT_CTRL_REL_PTR | 1,
    9,                                   // out_ptr
    GDSP_INIT_CTRL_DEFAULT | 1,
    0x0230,                              // buffer_size
    GDSP_INIT_CTRL_REL_PTR | 1,
    10,                                  // buffer_ptr
    GDSP_INIT_CTRL_DEFAULT | 5,
    1,                                   // read_idx
    0,                                   // write_idx
    0x7FFF,                              // buffer_irq_size
    0,                                   // irq
    0,                                   // out
    GDSP_INIT_CTRL_ZERO | (560),         // taps[560]
    GDSP_INIT_CTRL_END                   // End of Init structure
};

const unsigned short delayline_buffer_code[4] =
{
  CALL_INSTR, CBUFFER,
  LDO_INSTR, 0,
};
gdsp_delayline_560* p_delayline_buffer;

const unsigned short mic_buffer[] =
{
  GDSP_INIT_CTRL_DEFAULT | 1,
  0x0001,                              // mode
  GDSP_INIT_CTRL_PTR     | 1,
  GDSP_INIT_CTRL_DEFAULT | 2,
  0,                                   // out_ptr
  0x00C8,                              // buffer_size
  GDSP_INIT_CTRL_REL_PTR | 1,
  10,                                  // buffer_ptr
  GDSP_INIT_CTRL_DEFAULT | 5,
  0x0041,                              // read_idx
  0x0040,                              // write_idx fftsize-framesize
  0x00C6,                              // buffer_irq_size
  0,                                   // irq
  0,                                   // out
  GDSP_INIT_CTRL_ZERO | 200,           // taps
  GDSP_INIT_CTRL_END                   // End of Init structure
};
const unsigned short mic_buffer_code[8] =
{
  CALL_INSTR, CBUFFER,
  LDO_INSTR, 0,
  LDC_INSTR, 0,
  CIRQ_INSTR, MIC_BUFFER_INT
};
gdsp_recordbuffer_128* p_mic_buffer;

const unsigned short spkr_buffer[] =
{
  GDSP_INIT_CTRL_DEFAULT | 1,
  0x0001,                              // mode
  GDSP_INIT_CTRL_PTR     | 1,
  GDSP_INIT_CTRL_DEFAULT | 2,
  0,                                   // out_ptr
  0x00C8,                              // buffer_size
  GDSP_INIT_CTRL_REL_PTR | 1,
  10,                                  // buffer_ptr
  GDSP_INIT_CTRL_DEFAULT | 5,
  0x0041,                              // read_idx
  0x0040,                              // write_idx
  0x00C6,                              // buffer_irq_size
  0,                                   // irq
  0,                                   // out
  GDSP_INIT_CTRL_ZERO | 200,           // taps
  GDSP_INIT_CTRL_END                   // End of Init structure
};
const unsigned short spkr_buffer_code[8] =
{
  CALL_INSTR, CBUFFER,
  LDO_INSTR, 0,
  LDC_INSTR, 0,
  CIRQ_INSTR, SPKR_BUFFER_INT
};
gdsp_recordbuffer_128* p_spkr_buffer;

const unsigned short g726decoder[] = 
{
  GDSP_INIT_CTRL_DEFAULT | 12,
  0x0004,                              // b_nr_bits1
  0x0000,                              // b_nr_bits2
  0x0008,                              // b_nr_bits3
  0x6000,                              // b_swap_mode
  0x0000,                              // b_out_val
  0x0000,                              // b_out_bits
  0xBFCD   /* DSP_RAM_IN0_REG */,      // b_buf_ptr
  0xBFCD   /* DSP_RAM_IN0_REG */,      // b_buf_start
  0xBFCD   /* DSP_RAM_IN0_REG */,      // b_buf_end
  0x0000,                              // b_flip_irq
  0x0000,                              // b_buffer_out1
  0x0000,                              // b_buffer_out2
  GDSP_INIT_CTRL_REL_PTR | 1,
  10,                                  // g_in1_ptr
  GDSP_INIT_CTRL_DEFAULT | 27,
  0x8102,                              // g_mode
  0x0000,                              // g_out1
  0x0020,                              // g_sr1
  0x0000,                              // g_a2r
  0x0000,                              // g_a1r
  0x0020,0x0020,0x0020,0x0020,0x0020,0x0020,   // g_dq
  0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,   // g_br
  0x0000,                              // g_dmsp
  0x0000,                              // g_dmlp
  0x0000,                              // g_apr
  0x0220,                              // g_yup
  0x0000,                              // g_ylp_lsb
  0x0220,                              // g_ylp_msb
  0x0000,                              // g_tdr
  0x0000,                              // g_pk0
  0x0000,                              // g_pk1
  0x0020,                              // g_sr0
  GDSP_INIT_CTRL_CONST_PTR | 1,
  _G726_TBL_INTLV,                     // g_intlv_ptr
  GDSP_INIT_CTRL_END                   // End of Init structure
};
const unsigned short g726decoder_code[8] = 
{
  CALL_INSTR, BUF_UNPACK,
  LDO_INSTR, 0,
  CALL_INSTR, G726,
  LDO_INSTR, 12
};

const unsigned short g726encoder[] = 
{
  GDSP_INIT_CTRL_PTR     | 1,
  GDSP_INIT_CTRL_DEFAULT | 27,
  0x0002,                              // g_mode
  0x0000,                              // g_out1
  0x0020,                              // g_sr1
  0x0000,                              // g_a2r
  0x0000,                              // g_a1r
  0x0020,0x0020,0x0020,0x0020,0x0020,0x0020,   // g_dq
  0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,   // g_br
  0x0000,                              // g_dmsp
  0x0000,                              // g_dmlp
  0x0000,                              // g_apr
  0x0220,                              // g_yup
  0x0000,                              // g_ylp_lsb
  0x0220,                              // g_ylp_msb
  0x0000,                              // g_tdr
  0x0000,                              // g_pk0
  0x0000,                              // g_pk1
  0x0020,                              // g_sr0
  GDSP_INIT_CTRL_CONST_PTR | 1,
  _G726_TBL_INTLV,                     // g_intlv_ptr
  GDSP_INIT_CTRL_REL_PTR | 1,
  2,                                   // b_in_ptr1
  GDSP_INIT_CTRL_DEFAULT | 11,
  0x0000,                              // b_in_ptr2
  0x0004,                              // b_nr_bits1
  0x0000,                              // b_nr_bits2
  0x0008,                              // b_nr_bits3
  0x6000,                              // b_swap_mode
  0x0000,                              // b_new_val
  0x0000,                              // b_new_bits
  0xBFC9   /* DSP_RAM_OUT0_REG */,     // b_buf_ptr
  0xBFC9   /* DSP_RAM_OUT0_REG */,     // b_buf_start
  0xBFC9   /* DSP_RAM_OUT0_REG */,     // b_buf_end
  0x0000,                              // b_flip_irq
  GDSP_INIT_CTRL_END                   // End of Init structure
};
const unsigned short g726encoder_code[8] = 
{
  CALL_INSTR, G726,
  LDO_INSTR, 0,
  CALL_INSTR, BUF_PACK,
  LDO_INSTR, 29
};

const unsigned short gendspclassddestination[] = 
{
  GDSP_INIT_CTRL_PTR     | 2,
  GDSP_INIT_CTRL_DEFAULT | 1,
  _DSP_CLASSD_REG,                     // deststart
  GDSP_INIT_CTRL_END                   // End of Init structure
};
const unsigned short gendspclassddestination_code[4] = 
{
  CALL_INSTR, COPYB2B,
  LDO_INSTR, 0
};
gdsp_classddestinations* p_gendspclassddestination;

const unsigned short gendspcodecdestinations[] = 
{
  GDSP_INIT_CTRL_REL_PTR | 3,
  3,                                   // srcliststart
  4,                                   // srclistend
  5,                                   // destliststart
  GDSP_INIT_CTRL_PTR     | 2,
  GDSP_INIT_CTRL_DEFAULT | 2,
  _DSP_CODEC_MIC_GAIN_REG,             // CODECMicGainOutDEST
  _DSP_CODEC_OUT_REG,                  // CODECDataOutDEST
  GDSP_INIT_CTRL_END                   // End of Init structure
};
const unsigned short gendspcodecdestinations_code[4] = 
{
  CALL_INSTR, COPYP2P,
  LDO_INSTR, 0
};
gdsp_codecdestinations* p_gendspcodecdestinations;

const unsigned short gendspcodecsource[] = 
{
  GDSP_INIT_CTRL_REL_PTR | 3,
  3,                                   // srcstart
  4,                                   // srcend
  5,                                   // destliststart
  GDSP_INIT_CTRL_DEFAULT | 4,
  _DSP_CODEC_MIC_GAIN_REG,             // src_ptr1
  _DSP_CODEC_IN_REG,                   // src_ptr2
  0,                                   // CODECMicGainSRC
  0,                                   // CODECDataInSRC
  GDSP_INIT_CTRL_END                   // End of Init structure
};
const unsigned short gendspcodecsource_code[4] = 
{
  CALL_INSTR, COPYP2B,
  LDO_INSTR, 0
};
gdsp_codecsource* p_gendspcodecsource;

const unsigned short gendspgainconstant[] = 
{
  GDSP_INIT_CTRL_DEFAULT | 1,
  0x0000,                              // VALUE
  GDSP_INIT_CTRL_END                   // End of Init structure
};
gdsp_constant* p_gendspgainconstant_pp;
gdsp_constant* p_gendspgainconstant_fp;
gdsp_constant* p_gendspgainconstant_encoder;

const unsigned short gain[] = 
{
  GDSP_INIT_CTRL_PTR     | 1,
  GDSP_INIT_CTRL_DEFAULT | 4,
  0x78D7,                              // pre_attn
  0x0000,                              // shift
  0x78D7,                              // post_attn
  0,                                   // out
  GDSP_INIT_CTRL_END                   // End of Init structure
};
const unsigned short gain_code[4] = 
{
  CALL_INSTR, DSCRTGAIN,
  LDO_INSTR, 0
};
gdsp_gain* p_gain_encoder_pp;
gdsp_gain* p_gain_decoder_pp;
gdsp_gain* p_gain_spkr_pp;
gdsp_gain* p_gain_spkr_fp;
gdsp_gain* p_gain_inbound;

const unsigned short law2lin[] = 
{
  GDSP_INIT_CTRL_PTR     | 1,
  GDSP_INIT_CTRL_DEFAULT | 2,
  0x8000,                              // lawb
  0,                                   // linear_out
  GDSP_INIT_CTRL_END                   // End of Init structure
};
const unsigned short law2lin_code[4] =
{
  CALL_INSTR, LAW2LIN,
  LDO_INSTR, 0
};
gdsp_lawlin* p_law2lin;

const unsigned short dynmixer_pp[] =
{
  GDSP_INIT_CTRL_REL_PTR | 2,
  6,                                   // ptr_ptr
  13,                                  // w_ptr
  GDSP_INIT_CTRL_DEFAULT | 4,
  0x0007,                              // n
  0x7FFF,                              // attn
  0,                                   // temp
  0,                                   // out
  GDSP_INIT_CTRL_PTR     | 7,
  GDSP_INIT_CTRL_DEFAULT | 7,
  MIXER_ATTEN, MIXER_ATTEN,			   // weights
  MIXER_ATTEN, MIXER_ATTEN,
  MIXER_ATTEN, 0x7FFF, 0x7FFF,
  GDSP_INIT_CTRL_END                   // End of Init structure
};
const unsigned short dynmixer_post[] =
{
  GDSP_INIT_CTRL_REL_PTR | 2,
  6,                                   // ptr_ptr
  13,                                  // w_ptr
  GDSP_INIT_CTRL_DEFAULT | 4,
  0x0007,                              // n
  0x7FFF,                              // attn
  0,                                   // temp
  0,                                   // out
  GDSP_INIT_CTRL_PTR     | 7,
  GDSP_INIT_CTRL_DEFAULT | 7,
  MIXER6_ATTEN, MIXER6_ATTEN,		   // weights
  MIXER6_ATTEN, MIXER6_ATTEN,
  MIXER6_ATTEN, MIXER6_ATTEN, 0x7FFF,
  GDSP_INIT_CTRL_END                   // End of Init structure
};
const unsigned short dynmixer_pcm[] =
{
  GDSP_INIT_CTRL_REL_PTR | 2,
  6,                                   // ptr_ptr
  13,                                  // w_ptr
  GDSP_INIT_CTRL_DEFAULT | 4,
  0x0007,                              // n
  0x7FFF,                              // attn
  0,                                   // temp
  0,                                   // out
  GDSP_INIT_CTRL_PTR     | 7,
  GDSP_INIT_CTRL_DEFAULT | 7,
  MIXER_ATTEN, MIXER_ATTEN,			   // weights
  MIXER_ATTEN, MIXER_ATTEN,
  MIXER_ATTEN, MIXER_ATTEN, 0x7FFF,
  GDSP_INIT_CTRL_END                   // End of Init structure
};
const unsigned short dynmixer_code[4] =
{
  CALL_INSTR, MIXER,
  LDO_INSTR, 0
};
gdsp_mixer* p_dynmixer0;
gdsp_mixer* p_dynmixer1;
gdsp_mixer* p_dynmixer2;
gdsp_mixer* p_dynmixer3;
gdsp_mixer* p_dynmixer4;
gdsp_mixer* p_dynmixer5;
gdsp_mixer* p_dynmixer6;
gdsp_mixer* p_dynmixer7;

const unsigned short gendsppcmmasterdestinations[] =
{
  GDSP_INIT_CTRL_REL_PTR | 2,
  3,                                   // srcliststart
  6,                                   // srclistend
  GDSP_INIT_CTRL_DEFAULT | 1,
  _DSP_PCM_OUT0_REG,                   // deststart
  GDSP_INIT_CTRL_PTR     | 4,
  GDSP_INIT_CTRL_END                   // End of Init structure
};
const unsigned short gendsppcmmasterdestinations_code[4] =
{
  CALL_INSTR, COPYP2B,
  LDO_INSTR, 0
};
gdsp_pcmmasterdestinations* p_gendsppcmmasterdestinations;

const unsigned short gendsppcmsource[] =
{
  GDSP_INIT_CTRL_DEFAULT | 2,
  _DSP_PCM_IN0_REG,                    // srcstart
  _DSP_PCM_IN3_REG,                    // srcend
  GDSP_INIT_CTRL_REL_PTR | 1,
  3,                                   // destliststart
  GDSP_INIT_CTRL_DEFAULT | 4,
  0,                                   // PCM0InSRC
  0,                                   // PCM1InSRC
  0,                                   // PCM2InSRC
  0,                                   // PCM3InSRC
  GDSP_INIT_CTRL_END                   // End of Init structure
};
const unsigned short gendsppcmsource_code[4] =
{
  CALL_INSTR, COPYB2B,
  LDO_INSTR, 0
};
gdsp_pcmsource* p_gendsppcmsource;

const unsigned short playbackbuffer[] = 
{
  GDSP_INIT_CTRL_DEFAULT | 2,
  0x0000,                              // mode
  0,                                   // in_ptr
  GDSP_INIT_CTRL_REL_PTR | 1,
  9,                                   // out_ptr
  GDSP_INIT_CTRL_DEFAULT | 1,
  0x0012,                              // buffer_size
  GDSP_INIT_CTRL_REL_PTR | 1,
  10,                                  // buffer_ptr
  GDSP_INIT_CTRL_DEFAULT | 5,
  0x0000,                              // read_idx
  0x000F,                              // write_idx
  0x0010,                              // buffer_irq_size
  0,                                   // irq
  0,                                   // out
  GDSP_INIT_CTRL_ZERO | 18,            // taps
  GDSP_INIT_CTRL_END                   // End of Init structure
};
const unsigned short playbackbuffer_code[8] = 
{
  CALL_INSTR, CBUFFER,
  LDO_INSTR, 0,
  LDC_INSTR, 0,
  CIRQ_INSTR, PLAYBACKBUFFER_INT
};
gdsp_playbackbuffer_18* p_playbackbuffer;

const unsigned short summator[] =
{
  GDSP_INIT_CTRL_PTR     | 3,
  GDSP_INIT_CTRL_DEFAULT | 2,
  0x0000,							   // in1_atten: set to disabled in the beginning
  0,                                   // out
  GDSP_INIT_CTRL_END                   // End of Init structure
};
const unsigned short summator_code[4] =
{
  CALL_INSTR, SUMM,
  LDO_INSTR, 0
};
gdsp_summator* p_summator;
//gdsp_summator* p_summator_2;

const unsigned short tonegen[] = 
{
  GDSP_INIT_CTRL_DEFAULT | 29,
  0x0F9E,                              // timerpreset1
  0x031F,                              // timerpreset2
  0x30FC,                              // argsin1_1
  0x7643,                              // argcos1_1
  0x4000,                              // t1att_1
  0x5A83,                              // argsin2_1
  0x5A83,                              // argcos2_1
  0x0000,                              // t2att_1
  0x7643,                              // argsin3_1
  0x30FC,                              // argcos3_1
  0x0000,                              // t3att_1
  0,0,0,                               // cosi
  0x8000,0x8000,0x8000,                // sini
  0,                                   // timer1
  0,                                   // timer2
  0,                                   // argsin1_2
  0,                                   // argcos1_2
  0,                                   // t1att_2
  0,                                   // argsin2_2
  0,                                   // argcos2_2
  0,                                   // t2att_2
  0,                                   // argsin3_2
  0,                                   // argcos3_2
  0,                                   // t3att_2
  0,                                   // tone_out
  GDSP_INIT_CTRL_END                   // End of Init structure
};
const unsigned short tonegen_code[4] = 
{
  CALL_INSTR, TONEGEN,
  LDO_INSTR, 0
};
gdsp_tonegen* p_tonegen;

// FP Blocks

const unsigned short g726decoder1[] =
{
  GDSP_INIT_CTRL_DEFAULT | 12,
  0x0004,                              /* b_nr_bits1*/
  0x0000,                              /* b_nr_bits2*/
  0x0010,                              /* b_nr_bits3*/
  0x6000,                              /* b_swap_mode*/
  0x0000,                              /* b_out_val*/
  0x0000,                              /* b_out_bits*/
  0xBFCD   /* DSP_RAM_IN0_REG */,      /* b_buf_ptr*/
  0xBFCD   /* DSP_RAM_IN0_REG */,      /* b_buf_start*/
  0xBFCD   /* DSP_RAM_IN0_REG */,      /* b_buf_end*/
  0x0000,                              /* b_flip_irq*/
  0x0000,                              /* b_buffer_out1*/
  0x0000,                              /* b_buffer_out2*/
  GDSP_INIT_CTRL_REL_PTR | 1,
  10,                                  /* g_in1_ptr*/
  GDSP_INIT_CTRL_DEFAULT | 27,
  0x8102,                              /* g_mode*/
  0x0000,                              /* g_out1*/
  0x0020,                              /* g_sr1*/
  0x0000,                              /* g_a2r*/
  0x0000,                              /* g_a1r*/
  0x0020,0x0020,0x0020,0x0020,0x0020,0x0020,   /* g_dq*/
  0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,   /* g_br*/
  0x0000,                              /* g_dmsp*/
  0x0000,                              /* g_dmlp*/
  0x0000,                              /* g_apr*/
  0x0220,                              /* g_yup*/
  0x0000,                              /* g_ylp_lsb*/
  0x0220,                              /* g_ylp_msb*/
  0x0000,                              /* g_tdr*/
  0x0000,                              /* g_pk0*/
  0x0000,                              /* g_pk1*/
  0x0020,                              /* g_sr0*/
  GDSP_INIT_CTRL_CONST_PTR | 1,
  _G726_TBL_INTLV,                     /* g_intlv_ptr*/
  GDSP_INIT_CTRL_END                   /* End of Init structure*/
};
const unsigned short g726decoder1_code[8] =
{
  CALL_INSTR, BUF_UNPACK,
  LDO_INSTR, 0,
  CALL_INSTR, G726,
  LDO_INSTR, 12
};
gdsp_adpcmnbdecoder* p_g726decoder_pp;
gdsp_adpcmnbencoder* p_g726encoder_pp;
gdsp_adpcmnbdecoder* p_g726decoder[6];
gdsp_adpcmnbencoder* p_g726encoder[6];

const unsigned short g726encoder1[] =
{
  GDSP_INIT_CTRL_PTR     | 1,
  GDSP_INIT_CTRL_DEFAULT | 27,
  0x0002,                              /* g_mode*/
  0x0000,                              /* g_out1*/
  0x0020,                              /* g_sr1*/
  0x0000,                              /* g_a2r*/
  0x0000,                              /* g_a1r*/
  0x0020,0x0020,0x0020,0x0020,0x0020,0x0020,   /* g_dq*/
  0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,   /* g_br*/
  0x0000,                              /* g_dmsp*/
  0x0000,                              /* g_dmlp*/
  0x0000,                              /* g_apr*/
  0x0220,                              /* g_yup*/
  0x0000,                              /* g_ylp_lsb*/
  0x0220,                              /* g_ylp_msb*/
  0x0000,                              /* g_tdr*/
  0x0000,                              /* g_pk0*/
  0x0000,                              /* g_pk1*/
  0x0020,                              /* g_sr0*/
  GDSP_INIT_CTRL_CONST_PTR | 1,
  _G726_TBL_INTLV,                     /* g_intlv_ptr*/
  GDSP_INIT_CTRL_REL_PTR | 1,
  2,                                   /* b_in_ptr1*/
  GDSP_INIT_CTRL_DEFAULT | 11,
  0x0000,                              /* b_in_ptr2*/
  0x0004,                              /* b_nr_bits1*/
  0x0000,                              /* b_nr_bits2*/
  0x0010,                              /* b_nr_bits3*/
  0x6000,                              /* b_swap_mode*/
  0x0000,                              /* b_new_val*/
  0x0000,                              /* b_new_bits*/
  0xBFC9   /* DSP_RAM_OUT0_REG */,     /* b_buf_ptr*/
  0xBFC9   /* DSP_RAM_OUT0_REG */,     /* b_buf_start*/
  0xBFC9   /* DSP_RAM_OUT0_REG */,     /* b_buf_end*/
  0x0000,                              /* b_flip_irq*/
  GDSP_INIT_CTRL_END                   /* End of Init structure*/
};
const unsigned short g726encoder1_code[8] =
{
  CALL_INSTR, G726,
  LDO_INSTR, 0,
  CALL_INSTR, BUF_PACK,
  LDO_INSTR, 29
};

const unsigned short g726decoder2[] =
{
  GDSP_INIT_CTRL_DEFAULT | 12,
  0x0004,                              /* b_nr_bits1*/
  0x0000,                              /* b_nr_bits2*/
  0x0010,                              /* b_nr_bits3*/
  0x6000,                              /* b_swap_mode*/
  0x0000,                              /* b_out_val*/
  0x0000,                              /* b_out_bits*/
  0xBFCD   /* DSP_RAM_IN0_REG */,      /* b_buf_ptr*/
  0xBFCD   /* DSP_RAM_IN0_REG */,      /* b_buf_start*/
  0xBFCD   /* DSP_RAM_IN0_REG */,      /* b_buf_end*/
  0x0000,                              /* b_flip_irq*/
  0x0000,                              /* b_buffer_out1*/
  0x0000,                              /* b_buffer_out2*/
  GDSP_INIT_CTRL_REL_PTR | 1,
  10,                                  /* g_in1_ptr*/
  GDSP_INIT_CTRL_DEFAULT | 27,
  0x8102,                              /* g_mode*/
  0x0000,                              /* g_out1*/
  0x0020,                              /* g_sr1*/
  0x0000,                              /* g_a2r*/
  0x0000,                              /* g_a1r*/
  0x0020,0x0020,0x0020,0x0020,0x0020,0x0020,   /* g_dq*/
  0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,   /* g_br*/
  0x0000,                              /* g_dmsp*/
  0x0000,                              /* g_dmlp*/
  0x0000,                              /* g_apr*/
  0x0220,                              /* g_yup*/
  0x0000,                              /* g_ylp_lsb*/
  0x0220,                              /* g_ylp_msb*/
  0x0000,                              /* g_tdr*/
  0x0000,                              /* g_pk0*/
  0x0000,                              /* g_pk1*/
  0x0020,                              /* g_sr0*/
  GDSP_INIT_CTRL_CONST_PTR | 1,
  _G726_TBL_INTLV,                     /* g_intlv_ptr*/
  GDSP_INIT_CTRL_END                   /* End of Init structure*/
};
const unsigned short g726decoder2_code[8] =
{
  CALL_INSTR, BUF_UNPACK,
  LDO_INSTR, 0,
  CALL_INSTR, G726,
  LDO_INSTR, 12
};

const unsigned short g726encoder2[] =
{
  GDSP_INIT_CTRL_PTR     | 1,
  GDSP_INIT_CTRL_DEFAULT | 27,
  0x0002,                              /* g_mode*/
  0x0000,                              /* g_out1*/
  0x0020,                              /* g_sr1*/
  0x0000,                              /* g_a2r*/
  0x0000,                              /* g_a1r*/
  0x0020,0x0020,0x0020,0x0020,0x0020,0x0020,   /* g_dq*/
  0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,   /* g_br*/
  0x0000,                              /* g_dmsp*/
  0x0000,                              /* g_dmlp*/
  0x0000,                              /* g_apr*/
  0x0220,                              /* g_yup*/
  0x0000,                              /* g_ylp_lsb*/
  0x0220,                              /* g_ylp_msb*/
  0x0000,                              /* g_tdr*/
  0x0000,                              /* g_pk0*/
  0x0000,                              /* g_pk1*/
  0x0020,                              /* g_sr0*/
  GDSP_INIT_CTRL_CONST_PTR | 1,
  _G726_TBL_INTLV,                     /* g_intlv_ptr*/
  GDSP_INIT_CTRL_REL_PTR | 1,
  2,                                   /* b_in_ptr1*/
  GDSP_INIT_CTRL_DEFAULT | 11,
  0x0000,                              /* b_in_ptr2*/
  0x0004,                              /* b_nr_bits1*/
  0x0000,                              /* b_nr_bits2*/
  0x0010,                              /* b_nr_bits3*/
  0x6000,                              /* b_swap_mode*/
  0x0000,                              /* b_new_val*/
  0x0000,                              /* b_new_bits*/
  0xBFC9   /* DSP_RAM_OUT0_REG */,     /* b_buf_ptr*/
  0xBFC9   /* DSP_RAM_OUT0_REG */,     /* b_buf_start*/
  0xBFC9   /* DSP_RAM_OUT0_REG */,     /* b_buf_end*/
  0x0000,                              /* b_flip_irq*/
  GDSP_INIT_CTRL_END                   /* End of Init structure*/
};
const unsigned short g726encoder2_code[8] =
{
  CALL_INSTR, G726,
  LDO_INSTR, 0,
  CALL_INSTR, BUF_PACK,
  LDO_INSTR, 29
};

const unsigned short g726decoder3[] =
{
  GDSP_INIT_CTRL_DEFAULT | 12,
  0x0004,                              /* b_nr_bits1*/
  0x0000,                              /* b_nr_bits2*/
  0x0010,                              /* b_nr_bits3*/
  0x6000,                              /* b_swap_mode*/
  0x0000,                              /* b_out_val*/
  0x0000,                              /* b_out_bits*/
  0xBFCD   /* DSP_RAM_IN0_REG */,      /* b_buf_ptr*/
  0xBFCD   /* DSP_RAM_IN0_REG */,      /* b_buf_start*/
  0xBFCD   /* DSP_RAM_IN0_REG */,      /* b_buf_end*/
  0x0000,                              /* b_flip_irq*/
  0x0000,                              /* b_buffer_out1*/
  0x0000,                              /* b_buffer_out2*/
  GDSP_INIT_CTRL_REL_PTR | 1,
  10,                                  /* g_in1_ptr*/
  GDSP_INIT_CTRL_DEFAULT | 27,
  0x8102,                              /* g_mode*/
  0x0000,                              /* g_out1*/
  0x0020,                              /* g_sr1*/
  0x0000,                              /* g_a2r*/
  0x0000,                              /* g_a1r*/
  0x0020,0x0020,0x0020,0x0020,0x0020,0x0020,   /* g_dq*/
  0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,   /* g_br*/
  0x0000,                              /* g_dmsp*/
  0x0000,                              /* g_dmlp*/
  0x0000,                              /* g_apr*/
  0x0220,                              /* g_yup*/
  0x0000,                              /* g_ylp_lsb*/
  0x0220,                              /* g_ylp_msb*/
  0x0000,                              /* g_tdr*/
  0x0000,                              /* g_pk0*/
  0x0000,                              /* g_pk1*/
  0x0020,                              /* g_sr0*/
  GDSP_INIT_CTRL_CONST_PTR | 1,
  _G726_TBL_INTLV,                     /* g_intlv_ptr*/
  GDSP_INIT_CTRL_END                   /* End of Init structure*/
};
const unsigned short g726decoder3_code[8] =
{
  CALL_INSTR, BUF_UNPACK,
  LDO_INSTR, 0,
  CALL_INSTR, G726,
  LDO_INSTR, 12
};

const unsigned short g726encoder3[] =
{
  GDSP_INIT_CTRL_PTR     | 1,
  GDSP_INIT_CTRL_DEFAULT | 27,
  0x0002,                              /* g_mode*/
  0x0000,                              /* g_out1*/
  0x0020,                              /* g_sr1*/
  0x0000,                              /* g_a2r*/
  0x0000,                              /* g_a1r*/
  0x0020,0x0020,0x0020,0x0020,0x0020,0x0020,   /* g_dq*/
  0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,   /* g_br*/
  0x0000,                              /* g_dmsp*/
  0x0000,                              /* g_dmlp*/
  0x0000,                              /* g_apr*/
  0x0220,                              /* g_yup*/
  0x0000,                              /* g_ylp_lsb*/
  0x0220,                              /* g_ylp_msb*/
  0x0000,                              /* g_tdr*/
  0x0000,                              /* g_pk0*/
  0x0000,                              /* g_pk1*/
  0x0020,                              /* g_sr0*/
  GDSP_INIT_CTRL_CONST_PTR | 1,
  _G726_TBL_INTLV,                     /* g_intlv_ptr*/
  GDSP_INIT_CTRL_REL_PTR | 1,
  2,                                   /* b_in_ptr1*/
  GDSP_INIT_CTRL_DEFAULT | 11,
  0x0000,                              /* b_in_ptr2*/
  0x0004,                              /* b_nr_bits1*/
  0x0000,                              /* b_nr_bits2*/
  0x0010,                              /* b_nr_bits3*/
  0x6000,                              /* b_swap_mode*/
  0x0000,                              /* b_new_val*/
  0x0000,                              /* b_new_bits*/
  0xBFC9   /* DSP_RAM_OUT0_REG */,     /* b_buf_ptr*/
  0xBFC9   /* DSP_RAM_OUT0_REG */,     /* b_buf_start*/
  0xBFC9   /* DSP_RAM_OUT0_REG */,     /* b_buf_end*/
  0x0000,                              /* b_flip_irq*/
  GDSP_INIT_CTRL_END                   /* End of Init structure*/
};
const unsigned short g726encoder3_code[8] =
{
  CALL_INSTR, G726,
  LDO_INSTR, 0,
  CALL_INSTR, BUF_PACK,
  LDO_INSTR, 29
};

const unsigned short g726decoder4[] =
{
  GDSP_INIT_CTRL_DEFAULT | 12,
  0x0004,                              /* b_nr_bits1*/
  0x0000,                              /* b_nr_bits2*/
  0x0010,                              /* b_nr_bits3*/
  0x6000,                              /* b_swap_mode*/
  0x0000,                              /* b_out_val*/
  0x0000,                              /* b_out_bits*/
  0xBFCD   /* DSP_RAM_IN0_REG */,      /* b_buf_ptr*/
  0xBFCD   /* DSP_RAM_IN0_REG */,      /* b_buf_start*/
  0xBFCD   /* DSP_RAM_IN0_REG */,      /* b_buf_end*/
  0x0000,                              /* b_flip_irq*/
  0x0000,                              /* b_buffer_out1*/
  0x0000,                              /* b_buffer_out2*/
  GDSP_INIT_CTRL_REL_PTR | 1,
  10,                                  /* g_in1_ptr*/
  GDSP_INIT_CTRL_DEFAULT | 27,
  0x8102,                              /* g_mode*/
  0x0000,                              /* g_out1*/
  0x0020,                              /* g_sr1*/
  0x0000,                              /* g_a2r*/
  0x0000,                              /* g_a1r*/
  0x0020,0x0020,0x0020,0x0020,0x0020,0x0020,   /* g_dq*/
  0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,   /* g_br*/
  0x0000,                              /* g_dmsp*/
  0x0000,                              /* g_dmlp*/
  0x0000,                              /* g_apr*/
  0x0220,                              /* g_yup*/
  0x0000,                              /* g_ylp_lsb*/
  0x0220,                              /* g_ylp_msb*/
  0x0000,                              /* g_tdr*/
  0x0000,                              /* g_pk0*/
  0x0000,                              /* g_pk1*/
  0x0020,                              /* g_sr0*/
  GDSP_INIT_CTRL_CONST_PTR | 1,
  _G726_TBL_INTLV,                     /* g_intlv_ptr*/
  GDSP_INIT_CTRL_END                   /* End of Init structure*/
};
const unsigned short g726decoder4_code[8] =
{
  CALL_INSTR, BUF_UNPACK,
  LDO_INSTR, 0,
  CALL_INSTR, G726,
  LDO_INSTR, 12
};

const unsigned short g726encoder4[] =
{
  GDSP_INIT_CTRL_PTR     | 1,
  GDSP_INIT_CTRL_DEFAULT | 27,
  0x0002,                              /* g_mode*/
  0x0000,                              /* g_out1*/
  0x0020,                              /* g_sr1*/
  0x0000,                              /* g_a2r*/
  0x0000,                              /* g_a1r*/
  0x0020,0x0020,0x0020,0x0020,0x0020,0x0020,   /* g_dq*/
  0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,   /* g_br*/
  0x0000,                              /* g_dmsp*/
  0x0000,                              /* g_dmlp*/
  0x0000,                              /* g_apr*/
  0x0220,                              /* g_yup*/
  0x0000,                              /* g_ylp_lsb*/
  0x0220,                              /* g_ylp_msb*/
  0x0000,                              /* g_tdr*/
  0x0000,                              /* g_pk0*/
  0x0000,                              /* g_pk1*/
  0x0020,                              /* g_sr0*/
  GDSP_INIT_CTRL_CONST_PTR | 1,
  _G726_TBL_INTLV,                     /* g_intlv_ptr*/
  GDSP_INIT_CTRL_REL_PTR | 1,
  2,                                   /* b_in_ptr1*/
  GDSP_INIT_CTRL_DEFAULT | 11,
  0x0000,                              /* b_in_ptr2*/
  0x0004,                              /* b_nr_bits1*/
  0x0000,                              /* b_nr_bits2*/
  0x0010,                              /* b_nr_bits3*/
  0x6000,                              /* b_swap_mode*/
  0x0000,                              /* b_new_val*/
  0x0000,                              /* b_new_bits*/
  0xBFC9   /* DSP_RAM_OUT0_REG */,     /* b_buf_ptr*/
  0xBFC9   /* DSP_RAM_OUT0_REG */,     /* b_buf_start*/
  0xBFC9   /* DSP_RAM_OUT0_REG */,     /* b_buf_end*/
  0x0000,                              /* b_flip_irq*/
  GDSP_INIT_CTRL_END                   /* End of Init structure*/
};
const unsigned short g726encoder4_code[8] =
{
  CALL_INSTR, G726,
  LDO_INSTR, 0,
  CALL_INSTR, BUF_PACK,
  LDO_INSTR, 29
};

const unsigned short g726decoder5[] =
{
  GDSP_INIT_CTRL_DEFAULT | 12,
  0x0004,                              /* b_nr_bits1*/
  0x0000,                              /* b_nr_bits2*/
  0x0010,                              /* b_nr_bits3*/
  0x6000,                              /* b_swap_mode*/
  0x0000,                              /* b_out_val*/
  0x0000,                              /* b_out_bits*/
  0xBFCD   /* DSP_RAM_IN0_REG */,      /* b_buf_ptr*/
  0xBFCD   /* DSP_RAM_IN0_REG */,      /* b_buf_start*/
  0xBFCD   /* DSP_RAM_IN0_REG */,      /* b_buf_end*/
  0x0000,                              /* b_flip_irq*/
  0x0000,                              /* b_buffer_out1*/
  0x0000,                              /* b_buffer_out2*/
  GDSP_INIT_CTRL_REL_PTR | 1,
  10,                                  /* g_in1_ptr*/
  GDSP_INIT_CTRL_DEFAULT | 27,
  0x8102,                              /* g_mode*/
  0x0000,                              /* g_out1*/
  0x0020,                              /* g_sr1*/
  0x0000,                              /* g_a2r*/
  0x0000,                              /* g_a1r*/
  0x0020,0x0020,0x0020,0x0020,0x0020,0x0020,   /* g_dq*/
  0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,   /* g_br*/
  0x0000,                              /* g_dmsp*/
  0x0000,                              /* g_dmlp*/
  0x0000,                              /* g_apr*/
  0x0220,                              /* g_yup*/
  0x0000,                              /* g_ylp_lsb*/
  0x0220,                              /* g_ylp_msb*/
  0x0000,                              /* g_tdr*/
  0x0000,                              /* g_pk0*/
  0x0000,                              /* g_pk1*/
  0x0020,                              /* g_sr0*/
  GDSP_INIT_CTRL_CONST_PTR | 1,
  _G726_TBL_INTLV,                     /* g_intlv_ptr*/
  GDSP_INIT_CTRL_END                   /* End of Init structure*/
};
const unsigned short g726decoder5_code[8] =
{
  CALL_INSTR, BUF_UNPACK,
  LDO_INSTR, 0,
  CALL_INSTR, G726,
  LDO_INSTR, 12
};

const unsigned short g726encoder5[] =
{
  GDSP_INIT_CTRL_PTR     | 1,
  GDSP_INIT_CTRL_DEFAULT | 27,
  0x0002,                              /* g_mode*/
  0x0000,                              /* g_out1*/
  0x0020,                              /* g_sr1*/
  0x0000,                              /* g_a2r*/
  0x0000,                              /* g_a1r*/
  0x0020,0x0020,0x0020,0x0020,0x0020,0x0020,   /* g_dq*/
  0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,   /* g_br*/
  0x0000,                              /* g_dmsp*/
  0x0000,                              /* g_dmlp*/
  0x0000,                              /* g_apr*/
  0x0220,                              /* g_yup*/
  0x0000,                              /* g_ylp_lsb*/
  0x0220,                              /* g_ylp_msb*/
  0x0000,                              /* g_tdr*/
  0x0000,                              /* g_pk0*/
  0x0000,                              /* g_pk1*/
  0x0020,                              /* g_sr0*/
  GDSP_INIT_CTRL_CONST_PTR | 1,
  _G726_TBL_INTLV,                     /* g_intlv_ptr*/
  GDSP_INIT_CTRL_REL_PTR | 1,
  2,                                   /* b_in_ptr1*/
  GDSP_INIT_CTRL_DEFAULT | 11,
  0x0000,                              /* b_in_ptr2*/
  0x0004,                              /* b_nr_bits1*/
  0x0000,                              /* b_nr_bits2*/
  0x0010,                              /* b_nr_bits3*/
  0x6000,                              /* b_swap_mode*/
  0x0000,                              /* b_new_val*/
  0x0000,                              /* b_new_bits*/
  0xBFC9   /* DSP_RAM_OUT0_REG */,     /* b_buf_ptr*/
  0xBFC9   /* DSP_RAM_OUT0_REG */,     /* b_buf_start*/
  0xBFC9   /* DSP_RAM_OUT0_REG */,     /* b_buf_end*/
  0x0000,                              /* b_flip_irq*/
  GDSP_INIT_CTRL_END                   /* End of Init structure*/
};
const unsigned short g726encoder5_code[8] =
{
  CALL_INSTR, G726,
  LDO_INSTR, 0,
  CALL_INSTR, BUF_PACK,
  LDO_INSTR, 29
};
const unsigned short g726decoder6[] =
{
  GDSP_INIT_CTRL_DEFAULT | 12,
  0x0004,                              /* b_nr_bits1*/
  0x0000,                              /* b_nr_bits2*/
  0x0010,                              /* b_nr_bits3*/
  0x6000,                              /* b_swap_mode*/
  0x0000,                              /* b_out_val*/
  0x0000,                              /* b_out_bits*/
  0xBFCD   /* DSP_RAM_IN0_REG */,      /* b_buf_ptr*/
  0xBFCD   /* DSP_RAM_IN0_REG */,      /* b_buf_start*/
  0xBFCD   /* DSP_RAM_IN0_REG */,      /* b_buf_end*/
  0x0000,                              /* b_flip_irq*/
  0x0000,                              /* b_buffer_out1*/
  0x0000,                              /* b_buffer_out2*/
  GDSP_INIT_CTRL_REL_PTR | 1,
  10,                                  /* g_in1_ptr*/
  GDSP_INIT_CTRL_DEFAULT | 27,
  0x8102,                              /* g_mode*/
  0x0000,                              /* g_out1*/
  0x0020,                              /* g_sr1*/
  0x0000,                              /* g_a2r*/
  0x0000,                              /* g_a1r*/
  0x0020,0x0020,0x0020,0x0020,0x0020,0x0020,   /* g_dq*/
  0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,   /* g_br*/
  0x0000,                              /* g_dmsp*/
  0x0000,                              /* g_dmlp*/
  0x0000,                              /* g_apr*/
  0x0220,                              /* g_yup*/
  0x0000,                              /* g_ylp_lsb*/
  0x0220,                              /* g_ylp_msb*/
  0x0000,                              /* g_tdr*/
  0x0000,                              /* g_pk0*/
  0x0000,                              /* g_pk1*/
  0x0020,                              /* g_sr0*/
  GDSP_INIT_CTRL_CONST_PTR | 1,
  _G726_TBL_INTLV,                     /* g_intlv_ptr*/
  GDSP_INIT_CTRL_END                   /* End of Init structure*/
};
const unsigned short g726decoder6_code[8] =
{
  CALL_INSTR, BUF_UNPACK,
  LDO_INSTR, 0,
  CALL_INSTR, G726,
  LDO_INSTR, 12
};

const unsigned short g726encoder6[] =
{
  GDSP_INIT_CTRL_PTR     | 1,
  GDSP_INIT_CTRL_DEFAULT | 27,
  0x0002,                              /* g_mode*/
  0x0000,                              /* g_out1*/
  0x0020,                              /* g_sr1*/
  0x0000,                              /* g_a2r*/
  0x0000,                              /* g_a1r*/
  0x0020,0x0020,0x0020,0x0020,0x0020,0x0020,   /* g_dq*/
  0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,   /* g_br*/
  0x0000,                              /* g_dmsp*/
  0x0000,                              /* g_dmlp*/
  0x0000,                              /* g_apr*/
  0x0220,                              /* g_yup*/
  0x0000,                              /* g_ylp_lsb*/
  0x0220,                              /* g_ylp_msb*/
  0x0000,                              /* g_tdr*/
  0x0000,                              /* g_pk0*/
  0x0000,                              /* g_pk1*/
  0x0020,                              /* g_sr0*/
  GDSP_INIT_CTRL_CONST_PTR | 1,
  _G726_TBL_INTLV,                     /* g_intlv_ptr*/
  GDSP_INIT_CTRL_REL_PTR | 1,
  2,                                   /* b_in_ptr1*/
  GDSP_INIT_CTRL_DEFAULT | 11,
  0x0000,                              /* b_in_ptr2*/
  0x0004,                              /* b_nr_bits1*/
  0x0000,                              /* b_nr_bits2*/
  0x0010,                              /* b_nr_bits3*/
  0x6000,                              /* b_swap_mode*/
  0x0000,                              /* b_new_val*/
  0x0000,                              /* b_new_bits*/
  0xBFC9   /* DSP_RAM_OUT0_REG */,     /* b_buf_ptr*/
  0xBFC9   /* DSP_RAM_OUT0_REG */,     /* b_buf_start*/
  0xBFC9   /* DSP_RAM_OUT0_REG */,     /* b_buf_end*/
  0x0000,                              /* b_flip_irq*/
  GDSP_INIT_CTRL_END                   /* End of Init structure*/
};
const unsigned short g726encoder6_code[8] =
{
  CALL_INSTR, G726,
  LDO_INSTR, 0,
  CALL_INSTR, BUF_PACK,
  LDO_INSTR, 29
};

const unsigned short conference[] =
{
  GDSP_INIT_CTRL_PTR     | 4,
  GDSP_INIT_CTRL_DEFAULT | 8,
  0x1EB8,                              /* atten_c1         0.24=0x1EB8  0.50=0x3FFF  0.74 = 0x5EB8  1.00=0x7FFF	*/
  0x1EB8,                              /* atten_c2	*/
  0x1EB8,                              /* atten_c3	*/
  0x7FFF,                              /* atten_c4	*/
  0,                                   /* out1      */
  0,                                   /* out2      */
  0,                                   /* out3      */
  0,                                   /* out4      */
  GDSP_INIT_CTRL_END                   /* End of Init structure */
};
const unsigned short conference_code[4] =
{
  CALL_INSTR, CONF,
  LDO_INSTR, 0
};
gdsp_conference* p_conference;

const unsigned short copySpeechBuffer1[] =
{
  GDSP_INIT_CTRL_ZERO | 39,
  GDSP_INIT_CTRL_END           /* End of Init structure*/
};

const unsigned short copySpeechBuffer1_code[58] =
{
  CALL_INSTR, INC,
  LDO_INSTR, 0,
  CIRQ_INSTR, DURATIONCOUNTER_INT,
  LDC_INSTR, 2,
  NOP_INSTR, JCAR9_INSTR | 46,
  CALL_INSTR, COPYB2B,
  LDO_INSTR, 3,
  CALL_INSTR, COPYB2B,
  LDO_INSTR, 6,
  CALL_INSTR, COPYB2B,
  LDO_INSTR, 9,
  CALL_INSTR, COPYB2B,
  LDO_INSTR, 12,
  CALL_INSTR, COPYB2B,
  LDO_INSTR, 15,
  CALL_INSTR, COPYB2B,
  LDO_INSTR, 18,
  CALL_INSTR, COPYB2B,
  LDO_INSTR, 21,
  CALL_INSTR, COPYB2B,
  LDO_INSTR, 24,
  CALL_INSTR, COPYB2B,
  LDO_INSTR, 27,
  CALL_INSTR, COPYB2B,
  LDO_INSTR, 30,
  CALL_INSTR, COPYB2B,
  LDO_INSTR, 33,
  CALL_INSTR, COPYB2B,
  LDO_INSTR, 36
};
copySpeecBuffers* p_copySpeechBuffer1;

const unsigned short clearPointers1[] =
{
  GDSP_INIT_CTRL_ZERO | 34,
  GDSP_INIT_CTRL_END           /* End of Init structure*/
};

const unsigned short clearPointers1_code[12] =
{
  CALL_INSTR, INC,
  LDO_INSTR, 0,
  LDC_INSTR, 2,
  NOP_INSTR, JCAR9_INSTR | 0x2,
  CALL_INSTR, COPYP2P,
  LDO_INSTR, 3
};
clearPointers* p_clearPointers1;

const unsigned short stopcopyconstant[] =
{
  GDSP_INIT_CTRL_DEFAULT | 1,
  0x8000,                              /* VALUE*/
  GDSP_INIT_CTRL_END                   /* End of Init structure*/
};
gdsp_constant* p_stopcopyconstant;

const unsigned short dataArea0[] =
{
  GDSP_INIT_CTRL_ZERO | 20,    /* taps*/
  GDSP_INIT_CTRL_END           /* End of Init structure*/
};
dataArea_40* p_dataArea0;

const unsigned short dataArea2[] =
{
  GDSP_INIT_CTRL_ZERO | 20,    /* taps*/
  GDSP_INIT_CTRL_END           /* End of Init structure*/
};
dataArea_40* p_dataArea2;

const unsigned short dataArea4[] =
{
  GDSP_INIT_CTRL_ZERO | 20,    /* taps*/
  GDSP_INIT_CTRL_END           /* End of Init structure*/
};
dataArea_40* p_dataArea4;

const unsigned short dataArea6[] =
{
  GDSP_INIT_CTRL_ZERO | 20,    /* taps*/
  GDSP_INIT_CTRL_END           /* End of Init structure*/
};
dataArea_40* p_dataArea6;

const unsigned short dataArea8[] =
{
  GDSP_INIT_CTRL_ZERO | 20,    /* taps*/
  GDSP_INIT_CTRL_END           /* End of Init structure*/
};
dataArea_40* p_dataArea8;

const unsigned short dataArea10[] =
{
  GDSP_INIT_CTRL_ZERO | 20,    /* taps*/
  GDSP_INIT_CTRL_END           /* End of Init structure*/
};
dataArea_40* p_dataArea10;

const unsigned short dataArea12[] =
{
  GDSP_INIT_CTRL_ZERO | 20,    /* taps*/
  GDSP_INIT_CTRL_END           /* End of Init structure*/
};
dataArea_40* p_dataArea12;

const unsigned short dataArea14[] =
{
  GDSP_INIT_CTRL_ZERO | 20,    /* taps*/
  GDSP_INIT_CTRL_END           /* End of Init structure*/
};
dataArea_40* p_dataArea14;

const unsigned short dataArea16[] =
{
  GDSP_INIT_CTRL_ZERO | 20,    /* taps*/
  GDSP_INIT_CTRL_END           /* End of Init structure*/
};
dataArea_40* p_dataArea16;

const unsigned short dataArea18[] =
{
  GDSP_INIT_CTRL_ZERO | 20,    /* taps*/
  GDSP_INIT_CTRL_END           /* End of Init structure*/
};
dataArea_40* p_dataArea18;

const unsigned short dataArea20[] =
{
  GDSP_INIT_CTRL_ZERO | 20,    /* taps*/
  GDSP_INIT_CTRL_END           /* End of Init structure*/
};
dataArea_40* p_dataArea20;

const unsigned short dataArea22[] =
{
  GDSP_INIT_CTRL_ZERO | 20,    /* taps*/
  GDSP_INIT_CTRL_END           /* End of Init structure*/
};
dataArea_40* p_dataArea22;

/*#ifndef GDSP_NO_DEBUG_PTR_ARRAY
#pragma object_attribute=__root
const DspPtrs_t DspBlockPtr = {
    &p_g726decoder,
    &p_g726encoder,
    &p_gendspclassddestination,
    &p_gendspcodecdestinations,
    &p_gendspcodecsource,
    &p_gendspgainconstant,
    &p_gendspgainconstant_encoder,
    &p_gain,
    &p_law2lin,
    &p_dynmixer,
    &p_playbackbuffer,
    &p_tonegen,
    &p_dataArea1,
    &p_dataArea2,
};
#endif
*/
