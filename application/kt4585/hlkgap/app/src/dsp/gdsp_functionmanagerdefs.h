#ifndef GDSP_FUNCTIONMANAGERDEFS_H_INCLUDED
#define GDSP_FUCNTIONMANAGERDEFS_H_INCLUDED

// project specific include -- Must be located somewhere in the include path
#include "gdsp_functionmanager_local_defs.h"

#ifndef MAX_NO_FM_CONTEXTS
  #define MAX_NO_FM_CONTEXTS (3)
#endif

#ifndef MAX_NO_FM_DSP_CORES
  #define MAX_NO_FM_DSP_CORES 1
#endif
 
 
#ifndef MAX_DSP1_BACKGROUND_BLOCKS
  #define MAX_DSP1_BACKGROUND_BLOCKS  0x50
#endif
#ifndef MAX_DSP1_8KHZ_BLOCKS
  #define MAX_DSP1_8KHZ_BLOCKS        0x50
#endif
#ifndef MAX_DSP1_16KHZ_BLOCKS
  #define MAX_DSP1_16KHZ_BLOCKS       0x50
#endif
#ifndef MAX_DSP1_32KHZ_BLOCKS
  #define MAX_DSP1_32KHZ_BLOCKS       0x00
#endif 
#ifndef MAX_DSP1_CR16INT_BLOCKS
  #define MAX_DSP1_CR16INT_BLOCKS     0x00
#endif 
#ifndef MAX_DSP1_DIPINT_BLOCKS
  #define MAX_DSP1_DIPINT_BLOCKS      0x00
#endif 
#ifndef MAX_DSP1_DSP2INT_BLOCKS
  #define MAX_DSP1_DSP2INT_BLOCKS     0x00
#endif


#ifndef MAX_DSP2_BACKGROUND_BLOCKS
  #define MAX_DSP2_BACKGROUND_BLOCKS  0x00
#endif
#ifndef MAX_DSP2_8KHZ_BLOCKS
  #define MAX_DSP2_8KHZ_BLOCKS        0x00
#endif
#ifndef MAX_DSP2_16KHZ_BLOCKS
  #define MAX_DSP2_16KHZ_BLOCKS       0x00
#endif
#ifndef MAX_DSP2_32KHZ_BLOCKS
  #define MAX_DSP2_32KHZ_BLOCKS       0x00
#endif 
#ifndef MAX_DSP2_CR16INT_BLOCKS
  #define MAX_DSP2_CR16INT_BLOCKS     0x00
#endif 
#ifndef MAX_DSP2_DIPINT_BLOCKS
  #define MAX_DSP2_DIPINT_BLOCKS      0x00
#endif 
#ifndef MAX_DSP2_DSP1INT_BLOCKS
  #define MAX_DSP2_DSP1INT_BLOCKS     0x00
#endif

#ifndef MAX_NO_FM_USER_FUNCTIONS
  #define MAX_NO_FM_USER_FUNCTIONS    0x03
#endif 

/* maximum number of administration blocks in the function manager*/
#define MAX_FM_ADMIN_BLOCKS (MAX_DSP1_BACKGROUND_BLOCKS+MAX_DSP1_8KHZ_BLOCKS+MAX_DSP1_16KHZ_BLOCKS+MAX_DSP2_BACKGROUND_BLOCKS+MAX_DSP2_8KHZ_BLOCKS+MAX_DSP2_16KHZ_BLOCKS)


// Minmumum code data size defines needed by the function manager for basic DSP code:
#define SIZEOF_DEFAULT_IRQ_JT_CODE   6
#define SIZEOF_CONTEXT_SAVE_CODE    37
#define SIZEOF_CONTEXT_RESTORE_CODE 16
#define IRQ_JT_ALIGN_WC             (16-SIZEOF_DEFAULT_IRQ_JT_CODE) // Worst case you need to align from byte address 0x1F equal to 16 words, but IRQ jumptable occupies SIZEOF_DEFAULT_IRQ_JT_CODE of the wasted words
#if (MAX_NO_FM_CONTEXTS > 1)
    #define SIZEOF_DSP_BACKGROUND_FMCODE 5+1+1+6
#else
  #define SIZEOF_DSP_BACKGROUND_FMCODE 1+1+1+6
#endif
#define SIZEOF_DSP_CONTEXT_FMCODE 7 

#define SIZEOF_DSP_FMDATA_BGRD 1
#define SIZEOF_DSP_FMDATA_CONTEXT 1

#define FMCODE_ALIGN_WC 1 // for the case that code needs to be 32 bit address aligned

#ifdef GDSP_FRAMEBASED_BACKGROUND_TASK
  #define SIZEOF_DSP_FRAMEBASED_FMCODE 8
  #define SIZEOF_DSP_FRAMEBASED_FMDATA 1
#else
  #define SIZEOF_DSP_FRAMEBASED_FMCODE 0 
  #define SIZEOF_DSP_FRAMEBASED_FMDATA 0
#endif


#define GDSP_MINIMUM_CONTEXT_CODE_SPACE (SIZEOF_CONTEXT_SAVE_CODE+SIZEOF_CONTEXT_RESTORE_CODE+SIZEOF_DSP_CONTEXT_FMCODE+FMCODE_ALIGN_WC)
#define GDSP_MINIMUM_BACKGRD_CODE_SPACE (SIZEOF_DEFAULT_IRQ_JT_CODE+IRQ_JT_ALIGN_WC+MAX_NO_FM_USER_FUNCTIONS+SIZEOF_DSP_BACKGROUND_FMCODE+SIZEOF_DSP_FRAMEBASED_FMCODE+FMCODE_ALIGN_WC)

#define GDSP_MINIMUM_BACKGRD_DATA_SPACE (SIZEOF_DSP_FRAMEBASED_FMDATA+SIZEOF_DSP_FMDATA_BGRD)

#define GDSP_MINIMUM_CONTEXT_DATA_SPACE (SIZEOF_DSP_FMDATA_CONTEXT)



#ifndef FM_ASSERT_ERROR
  #define FM_ASSERT_ERROR(x)
#endif

#define DEFAULT_CASDETECTOR_INT         (0x1<<0)
#define DEFAULT_CASDETECTORV2_INT       (0x1<<1)
#define DEFAULT_DTMFDETECTOR_INT        (0x1<<2)
#define DEFAULT_DTMFRUDETECTOR_INT      (0x1<<3)
#define DEFAULT_DURATIONCOUNTER_INT     (0x1<<4)
#define DEFAULT_EDGEDETECTOR21_INT      (0x1<<5)
#define DEFAULT_EVENTCOUNTER_INT        (0x1<<6)
#define DEFAULT_FSKDECODER_INT          (0x1<<7)
#define DEFAULT_FSKGEN_INT              (0x1<<8)
#define DEFAULT_PLAYBACKBUFFER_INT      (0x1<<9)
#define DEFAULT_RECORDBUFFER_INT        (0x1<<10)
#define DEFAULT_SINGLETONEDETECTOR_INT  (0x1<<11)
#define DEFAULT_SVC_ENC_INT             (0x1<<12)
#define DEFAULT_SVC_DEC_INT             (0x1<<13)


// Opcode of CALL,LDO, JSR, BRU, SKN, SKP, LLSO, LHSO, RTS, WTF and JPO instructions
// SCP Instructions
#define CALL_INSTR          0xF3BD
#define LDO_INSTR 	        0xF390
#define SDO_INSTR 	        0xF391
#define SP_INSTR            0xF397
#define LDC_INSTR           0xFFBE
#define CIRQ_INSTR          0xF3B4
#define IRQ_INSTR           0xF3B6

#define JADR9_INSTR         0xBC00
#define JADR9_2_INSTR       0xBE00
#define JCAR9_INSTR         0xBA00

#define WTF_INSTR           0xBFC2
#define NOP_INSTR           0x7FFF
#define JA_INSTR            0xF3BE
#define RTI_INSTR           0xBFFE

#define IM_INSTR            0xBF80  // | xxxxxx where xxxxxx os the value of the interrupt bit to unmask
#define ISR_ACK_INSTR       0xBF00  // | xxxxxx where xxxxxx os the value of the interrupt bit to ack
#define EI_INSTR            0xBFDD
#define DI_INSTR            0xBFDE
#define RTS_INSTR           0xBFFC


#define LOAD_D2_INSTR       0xF382
#define STORE_D2_INSTR      0xFF85
// wrong: Do not use --- #define SAVE_LR_INSTR       0xB73D
// wrong: Do not use --- #define RESTORE_LR_INSTR    0xB73C
#define CND_CMP_NEG         0x0000EFB0


/*
* JUMP table addresses
*/
#ifdef A2M6_FP
  #define _SHF_			1
  #define _BASE_ADDR_		0x8000

  #define ABS                     (( 0<<_SHF_)|_BASE_ADDR_)
  #define AEC                     (( 1<<_SHF_)|_BASE_ADDR_)
  #define AGC                     (( 2<<_SHF_)|_BASE_ADDR_)
  #define ANAGC                   (( 3<<_SHF_)|_BASE_ADDR_)
  #define ANDB                    (( 4<<_SHF_)|_BASE_ADDR_)
  #define BLKMINMAX               (( 5<<_SHF_)|_BASE_ADDR_)
  #define BLKNORM                 (( 6<<_SHF_)|_BASE_ADDR_)
  #define BUF_PACK                (( 7<<_SHF_)|_BASE_ADDR_)
  #define BUF_UNPACK              (( 8<<_SHF_)|_BASE_ADDR_)
  #define CASDET                  (( 9<<_SHF_)|_BASE_ADDR_)
  #define CASDET2                 ((10<<_SHF_)|_BASE_ADDR_)
  #define CBUFFER                 ((11<<_SHF_)|_BASE_ADDR_)
  #define CFFT                    ((12<<_SHF_)|_BASE_ADDR_)
  #define CONF                    ((13<<_SHF_)|_BASE_ADDR_)
  #define COPYB2B                 ((14<<_SHF_)|_BASE_ADDR_)
  #define COPYP2B                 ((15<<_SHF_)|_BASE_ADDR_)
  #define COPYP2P                 ((16<<_SHF_)|_BASE_ADDR_)
  #define COUNTER                 ((17<<_SHF_)|_BASE_ADDR_)
  #define DBLLAW2LIN              ((18<<_SHF_)|_BASE_ADDR_)
  #define DEC                     ((20<<_SHF_)|_BASE_ADDR_)
  #define DIVF                    ((21<<_SHF_)|_BASE_ADDR_)
  #define DIVI                    ((22<<_SHF_)|_BASE_ADDR_)
  #define DSCRTGAIN               ((23<<_SHF_)|_BASE_ADDR_)
  #define DTMFDET                 ((24<<_SHF_)|_BASE_ADDR_)
  #define DTMFRU                  ((25<<_SHF_)|_BASE_ADDR_)
  #define EDGEDET                 ((26<<_SHF_)|_BASE_ADDR_)
  #define EXP                     ((27<<_SHF_)|_BASE_ADDR_)
  #define FMOPERATOR              ((28<<_SHF_)|_BASE_ADDR_)
  #define FSKDECOD                ((29<<_SHF_)|_BASE_ADDR_)
  #define FSKGEN                  ((30<<_SHF_)|_BASE_ADDR_)
  #define G722_RX                 ((31<<_SHF_)|_BASE_ADDR_)
  #define G722_TX                 ((32<<_SHF_)|_BASE_ADDR_)
  #define G726                    ((33<<_SHF_)|_BASE_ADDR_)
  #define G726_VQI                ((34<<_SHF_)|_BASE_ADDR_)
  #define GETREVISION             ((35<<_SHF_)|_BASE_ADDR_)
  #define HAGC                    ((37<<_SHF_)|_BASE_ADDR_)
  #define HFREE                   ((38<<_SHF_)|_BASE_ADDR_)
  #define INC                     ((40<<_SHF_)|_BASE_ADDR_)
  #define INTERP                  ((41<<_SHF_)|_BASE_ADDR_)
  #define LAW2LIN                 ((42<<_SHF_)|_BASE_ADDR_)
  #define LEC                     ((43<<_SHF_)|_BASE_ADDR_)
  #define LIN2LAW                 ((44<<_SHF_)|_BASE_ADDR_)
  #define LIN2LOG                 ((45<<_SHF_)|_BASE_ADDR_)
  #define LOG2LIN                 ((46<<_SHF_)|_BASE_ADDR_)
  #define MIXER                   ((48<<_SHF_)|_BASE_ADDR_)
  #define MONITOR                 ((49<<_SHF_)|_BASE_ADDR_)
  #define NC100HZ                 ((50<<_SHF_)|_BASE_ADDR_)
  #define NSHL                    ((51<<_SHF_)|_BASE_ADDR_)
  #define NSHR                    ((52<<_SHF_)|_BASE_ADDR_)
  #define ORB                     ((53<<_SHF_)|_BASE_ADDR_)
  #define PFILT                   ((54<<_SHF_)|_BASE_ADDR_)
  #define PFIRFILT                ((55<<_SHF_)|_BASE_ADDR_)
  #define PLEVDET                 ((56<<_SHF_)|_BASE_ADDR_)
  #define PNLEVDET                ((57<<_SHF_)|_BASE_ADDR_)
  #define POLY                    ((58<<_SHF_)|_BASE_ADDR_)
  #define RNDGEN                  ((60<<_SHF_)|_BASE_ADDR_)
  #define SHIFT                   ((62<<_SHF_)|_BASE_ADDR_)
  #define SINGLETONEDET           ((63<<_SHF_)|_BASE_ADDR_)
  #define SUB	                    ((64<<_SHF_)|_BASE_ADDR_)
  #define SUMM                    ((65<<_SHF_)|_BASE_ADDR_)
  #define SUPP                    ((66<<_SHF_)|_BASE_ADDR_)
  #define TONEDET                 ((67<<_SHF_)|_BASE_ADDR_)
  #define TONEGEN                 ((68<<_SHF_)|_BASE_ADDR_)
  #define WINDOWADD               ((72<<_SHF_)|_BASE_ADDR_)
  #define XOR                     ((73<<_SHF_)|_BASE_ADDR_)
  #define ZCROSS                  ((75<<_SHF_)|_BASE_ADDR_)
  #define PAEC                    ((82<<_SHF_)|_BASE_ADDR_)
#elif defined(A2L_PP)
  #define _SHF_			1
  #define _BASE_ADDR_		0x8000

  #define ABS                     (( 0<<_SHF_)|_BASE_ADDR_)
  #define AEC                     (( 1<<_SHF_)|_BASE_ADDR_)
  #define AGC                     (( 2<<_SHF_)|_BASE_ADDR_)
  #define ANAGC                   (( 3<<_SHF_)|_BASE_ADDR_)
  #define ANDB                    (( 4<<_SHF_)|_BASE_ADDR_)
  #define BLKMINMAX               (( 5<<_SHF_)|_BASE_ADDR_)
  #define BLKNORM                 (( 6<<_SHF_)|_BASE_ADDR_)
  #define BUF_PACK                (( 7<<_SHF_)|_BASE_ADDR_)
  #define BUF_UNPACK              (( 8<<_SHF_)|_BASE_ADDR_)
  #define CBUFFER                 ((11<<_SHF_)|_BASE_ADDR_)
  #define CONF                    ((13<<_SHF_)|_BASE_ADDR_)
  #define COPYB2B                 ((14<<_SHF_)|_BASE_ADDR_)
  #define COPYP2B                 ((15<<_SHF_)|_BASE_ADDR_)
  #define COPYP2P                 ((16<<_SHF_)|_BASE_ADDR_)
  #define COUNTER                 ((17<<_SHF_)|_BASE_ADDR_)
  #define DBLLAW2LIN              ((18<<_SHF_)|_BASE_ADDR_)
  #define DEC                     ((20<<_SHF_)|_BASE_ADDR_)
  #define DIVF                    ((21<<_SHF_)|_BASE_ADDR_)
  #define DIVI                    ((22<<_SHF_)|_BASE_ADDR_)
  #define DSCRTGAIN               ((23<<_SHF_)|_BASE_ADDR_)
  #define EDGEDET                 ((26<<_SHF_)|_BASE_ADDR_)
  #define EXP                     ((27<<_SHF_)|_BASE_ADDR_)
  #define FMOPERATOR              ((28<<_SHF_)|_BASE_ADDR_)
  #define G722_RX                 ((31<<_SHF_)|_BASE_ADDR_)
  #define G722_TX                 ((32<<_SHF_)|_BASE_ADDR_)
  #define G726                    ((33<<_SHF_)|_BASE_ADDR_)
  #define G726_VQI                ((34<<_SHF_)|_BASE_ADDR_)
  #define GETREVISION             ((35<<_SHF_)|_BASE_ADDR_)
  #define HAGC                    ((37<<_SHF_)|_BASE_ADDR_)
  #define HFREE                   ((38<<_SHF_)|_BASE_ADDR_)
  #define INC                     ((40<<_SHF_)|_BASE_ADDR_)
  #define INTERP                  ((41<<_SHF_)|_BASE_ADDR_)
  #define LAW2LIN                 ((42<<_SHF_)|_BASE_ADDR_)
  #define LIN2LAW                 ((44<<_SHF_)|_BASE_ADDR_)
  #define LIN2LOG                 ((45<<_SHF_)|_BASE_ADDR_)
  #define LOG2LIN                 ((46<<_SHF_)|_BASE_ADDR_)
  #define MIXER                   ((48<<_SHF_)|_BASE_ADDR_)
  #define MONITOR                 ((49<<_SHF_)|_BASE_ADDR_)
  #define NC100HZ                 ((50<<_SHF_)|_BASE_ADDR_)
  #define NSHL                    ((51<<_SHF_)|_BASE_ADDR_)
  #define NSHR                    ((52<<_SHF_)|_BASE_ADDR_)
  #define ORB                     ((53<<_SHF_)|_BASE_ADDR_)
  #define PFILT                   ((54<<_SHF_)|_BASE_ADDR_)
  #define PFIRFILT                ((55<<_SHF_)|_BASE_ADDR_)
  #define PLEVDET                 ((56<<_SHF_)|_BASE_ADDR_)
  #define PNLEVDET                ((57<<_SHF_)|_BASE_ADDR_)
  #define POLY                    ((58<<_SHF_)|_BASE_ADDR_)
  #define RNDGEN                  ((60<<_SHF_)|_BASE_ADDR_)
  #define SHIFT                   ((62<<_SHF_)|_BASE_ADDR_)
  #define SINGLETONEDET           ((63<<_SHF_)|_BASE_ADDR_)
  #define SUB	                    ((64<<_SHF_)|_BASE_ADDR_)
  #define SUMM                    ((65<<_SHF_)|_BASE_ADDR_)
  #define SUPP                    ((66<<_SHF_)|_BASE_ADDR_)
  #define TONEDET                 ((67<<_SHF_)|_BASE_ADDR_)
  #define TONEGEN                 ((68<<_SHF_)|_BASE_ADDR_)
  #define WINDOWADD               ((72<<_SHF_)|_BASE_ADDR_)
  #define XOR                     ((73<<_SHF_)|_BASE_ADDR_)
  #define ZCROSS                  ((75<<_SHF_)|_BASE_ADDR_)
#elif defined(A50M80VE)
  // This is the full blown version with all algorithms and with DSP data ROM
  #define FM_DSP_DATA_ROM_AVAILABLE

  #define _SHF_			1
  #define _BASE_ADDR_		0x8000

  #define ABS                     (( 0<<_SHF_)|_BASE_ADDR_)
  #define AEC                     (( 1<<_SHF_)|_BASE_ADDR_)
  #define AGC                     (( 2<<_SHF_)|_BASE_ADDR_)
  #define ANAGC                   (( 3<<_SHF_)|_BASE_ADDR_)
  #define ANDB                    (( 4<<_SHF_)|_BASE_ADDR_)
  #define BLKMINMAX               (( 5<<_SHF_)|_BASE_ADDR_)
  #define BLKNORM                 (( 6<<_SHF_)|_BASE_ADDR_)
  #define BUF_PACK                (( 7<<_SHF_)|_BASE_ADDR_)
  #define BUF_UNPACK              (( 8<<_SHF_)|_BASE_ADDR_)
  #define CASDET                  (( 9<<_SHF_)|_BASE_ADDR_)
  #define CASDET2                 ((10<<_SHF_)|_BASE_ADDR_)
  #define CBUFFER                 ((11<<_SHF_)|_BASE_ADDR_)
  #define CFFT                    ((12<<_SHF_)|_BASE_ADDR_)
  #define CONF                    ((13<<_SHF_)|_BASE_ADDR_)
  #define COPYB2B                 ((14<<_SHF_)|_BASE_ADDR_)
  #define COPYP2B                 ((15<<_SHF_)|_BASE_ADDR_)
  #define COPYP2P                 ((16<<_SHF_)|_BASE_ADDR_)
  #define COUNTER                 ((17<<_SHF_)|_BASE_ADDR_)
  #define DBLLAW2LIN              ((18<<_SHF_)|_BASE_ADDR_)
  #define DCT                     ((19<<_SHF_)|_BASE_ADDR_)
  #define DEC                     ((20<<_SHF_)|_BASE_ADDR_)
  #define DIVF                    ((21<<_SHF_)|_BASE_ADDR_)
  #define DIVI                    ((22<<_SHF_)|_BASE_ADDR_)
  #define DSCRTGAIN               ((23<<_SHF_)|_BASE_ADDR_)
  #define DTMFDET                 ((24<<_SHF_)|_BASE_ADDR_)
  #define DTMFRU                  ((25<<_SHF_)|_BASE_ADDR_)
  #define EDGEDET                 ((26<<_SHF_)|_BASE_ADDR_)
  #define EXP                     ((27<<_SHF_)|_BASE_ADDR_)
  #define FMOPERATOR              ((28<<_SHF_)|_BASE_ADDR_)
  #define FSKDECOD                ((29<<_SHF_)|_BASE_ADDR_)
  #define FSKGEN                  ((30<<_SHF_)|_BASE_ADDR_)
  #define G722_RX                 ((31<<_SHF_)|_BASE_ADDR_)
  #define G722_TX                 ((32<<_SHF_)|_BASE_ADDR_)
  #define G726                    ((33<<_SHF_)|_BASE_ADDR_)
  #define G726_VQI                ((34<<_SHF_)|_BASE_ADDR_)
  #define GETREVISION             ((35<<_SHF_)|_BASE_ADDR_)
  #define GRAYSCALE               ((36<<_SHF_)|_BASE_ADDR_)
  #define HAGC                    ((37<<_SHF_)|_BASE_ADDR_)
  #define HFREE                   ((38<<_SHF_)|_BASE_ADDR_)
  #define IDCT                    ((39<<_SHF_)|_BASE_ADDR_)
  #define INC                     ((40<<_SHF_)|_BASE_ADDR_)
  #define INTERP                  ((41<<_SHF_)|_BASE_ADDR_)
  #define LAW2LIN                 ((42<<_SHF_)|_BASE_ADDR_)
  #define LEC                     ((43<<_SHF_)|_BASE_ADDR_)
  #define LIN2LAW                 ((44<<_SHF_)|_BASE_ADDR_)
  #define LIN2LOG                 ((45<<_SHF_)|_BASE_ADDR_)
  #define LOG2LIN                 ((46<<_SHF_)|_BASE_ADDR_)
  #define MATRIX3X3               ((47<<_SHF_)|_BASE_ADDR_)
  #define MIXER                   ((48<<_SHF_)|_BASE_ADDR_)
  #define MONITOR                 ((49<<_SHF_)|_BASE_ADDR_)
  #define NC100HZ                 ((50<<_SHF_)|_BASE_ADDR_)
  #define NSHL                    ((51<<_SHF_)|_BASE_ADDR_)
  #define NSHR                    ((52<<_SHF_)|_BASE_ADDR_)
  #define ORB                     ((53<<_SHF_)|_BASE_ADDR_)
  #define PFILT                   ((54<<_SHF_)|_BASE_ADDR_)
  #define PFIRFILT                ((55<<_SHF_)|_BASE_ADDR_)
  #define PLEVDET                 ((56<<_SHF_)|_BASE_ADDR_)
  #define PNLEVDET                ((57<<_SHF_)|_BASE_ADDR_)
  #define POLY                    ((58<<_SHF_)|_BASE_ADDR_)
  #define RGB2YCC                 ((59<<_SHF_)|_BASE_ADDR_)
  #define RNDGEN                  ((60<<_SHF_)|_BASE_ADDR_)
  #define RS_PARSYN               ((61<<_SHF_)|_BASE_ADDR_)
  #define SHIFT                   ((62<<_SHF_)|_BASE_ADDR_)
  #define SINGLETONEDET           ((63<<_SHF_)|_BASE_ADDR_)
  #define SUB	                  ((64<<_SHF_)|_BASE_ADDR_)
  #define SUMM                    ((65<<_SHF_)|_BASE_ADDR_)
  #define SUPP                    ((66<<_SHF_)|_BASE_ADDR_)
  #define TONEDET                 ((67<<_SHF_)|_BASE_ADDR_)
  #define TONEGEN                 ((68<<_SHF_)|_BASE_ADDR_)
  #define UPSAMPLE420             ((69<<_SHF_)|_BASE_ADDR_)
  #define UPSAMPLE422             ((70<<_SHF_)|_BASE_ADDR_)
  #define UPSAMPLE422V            ((71<<_SHF_)|_BASE_ADDR_)
  #define WINDOWADD               ((72<<_SHF_)|_BASE_ADDR_)
  #define XOR                     ((73<<_SHF_)|_BASE_ADDR_)
  #define YCC2RGB                 ((74<<_SHF_)|_BASE_ADDR_)
  #define ZCROSS                  ((75<<_SHF_)|_BASE_ADDR_)
  #define G729AB_ENC              ((76<<_SHF_)|_BASE_ADDR_)
  #define G729AB_DEC              ((77<<_SHF_)|_BASE_ADDR_)
  #define SVC_ENC                 ((79<<_SHF_)|_BASE_ADDR_)
  #define SVC_DEC                 ((80<<_SHF_)|_BASE_ADDR_)
  #define MIDI_SYNTH              ((81<<_SHF_)|_BASE_ADDR_)
  #define PAEC                    ((82<<_SHF_)|_BASE_ADDR_)
  #define IRQ_CONEXT_SAVE         ((83<<_SHF_)|_BASE_ADDR_)
  #define IRQ_CONEXT_RESTORE      ((84<<_SHF_)|_BASE_ADDR_)
  #define RFFT                    ((93<<_SHF_)|_BASE_ADDR_)
  #define RIFFT                   ((94<<_SHF_)|_BASE_ADDR_)
  #define RFFTD                   ((95<<_SHF_)|_BASE_ADDR_)
  #define RIFFTD                  ((96<<_SHF_)|_BASE_ADDR_)
  #define RESAMPLE                ((97<<_SHF_)|_BASE_ADDR_)
  #define POLYPHASE               ((98<<_SHF_)|_BASE_ADDR_)
  #define CBUFIRQ                 ((99<<_SHF_)|_BASE_ADDR_)
  #define WIDEBAND                ((100<<_SHF_)|_BASE_ADDR_)
#elif defined(ANF128VPN)
  // This is the full blown version with all algorithms and with DSP data ROM
  #define FM_DSP_DATA_ROM_AVAILABLE

  #define _SHF_			1
  #define _BASE_ADDR_		0x4000

  #define ABS                     (( 0<<_SHF_)|_BASE_ADDR_)
  #define AEC                     (( 1<<_SHF_)|_BASE_ADDR_)
  #define AGC                     (( 2<<_SHF_)|_BASE_ADDR_)
  #define ANAGC                   (( 3<<_SHF_)|_BASE_ADDR_)
  #define ANDB                    (( 4<<_SHF_)|_BASE_ADDR_)
  #define BLKMINMAX               (( 5<<_SHF_)|_BASE_ADDR_)
  #define BLKNORM                 (( 6<<_SHF_)|_BASE_ADDR_)
  #define BUF_PACK                (( 7<<_SHF_)|_BASE_ADDR_)
  #define BUF_UNPACK              (( 8<<_SHF_)|_BASE_ADDR_)
  #define CASDET                  (( 9<<_SHF_)|_BASE_ADDR_)
  #define CASDET2                 ((10<<_SHF_)|_BASE_ADDR_)
  #define CBUFFER                 ((11<<_SHF_)|_BASE_ADDR_)
  #define CFFT                    ((12<<_SHF_)|_BASE_ADDR_)
  #define CONF                    ((13<<_SHF_)|_BASE_ADDR_)
  #define COPYB2B                 ((14<<_SHF_)|_BASE_ADDR_)
  #define COPYP2B                 ((15<<_SHF_)|_BASE_ADDR_)
  #define COPYP2P                 ((16<<_SHF_)|_BASE_ADDR_)
  #define COUNTER                 ((17<<_SHF_)|_BASE_ADDR_)
  #define DBLLAW2LIN              ((18<<_SHF_)|_BASE_ADDR_)
  #define DCT                     ((19<<_SHF_)|_BASE_ADDR_)
  #define DEC                     ((20<<_SHF_)|_BASE_ADDR_)
  #define DIVF                    ((21<<_SHF_)|_BASE_ADDR_)
  #define DIVI                    ((22<<_SHF_)|_BASE_ADDR_)
  #define DSCRTGAIN               ((23<<_SHF_)|_BASE_ADDR_)
  #define DTMFDET                 ((24<<_SHF_)|_BASE_ADDR_)
  #define DTMFRU                  ((25<<_SHF_)|_BASE_ADDR_)
  #define EDGEDET                 ((26<<_SHF_)|_BASE_ADDR_)
  #define EXP                     ((27<<_SHF_)|_BASE_ADDR_)
  #define FMOPERATOR              ((28<<_SHF_)|_BASE_ADDR_)
  #define FSKDECOD                ((29<<_SHF_)|_BASE_ADDR_)
  #define FSKGEN                  ((30<<_SHF_)|_BASE_ADDR_)
  #define G722_RX                 ((31<<_SHF_)|_BASE_ADDR_)
  #define G722_TX                 ((32<<_SHF_)|_BASE_ADDR_)
  #define G726                    ((33<<_SHF_)|_BASE_ADDR_)
  #define G726_VQI                ((34<<_SHF_)|_BASE_ADDR_)
  #define GETREVISION             ((35<<_SHF_)|_BASE_ADDR_)
  #define GRAYSCALE               ((36<<_SHF_)|_BASE_ADDR_)
  #define HAGC                    ((37<<_SHF_)|_BASE_ADDR_)
  #define HFREE                   ((38<<_SHF_)|_BASE_ADDR_)
  #define IDCT                    ((39<<_SHF_)|_BASE_ADDR_)
  #define INC                     ((40<<_SHF_)|_BASE_ADDR_)
  #define INTERP                  ((41<<_SHF_)|_BASE_ADDR_)
  #define LAW2LIN                 ((42<<_SHF_)|_BASE_ADDR_)
  #define LEC                     ((43<<_SHF_)|_BASE_ADDR_)
  #define LIN2LAW                 ((44<<_SHF_)|_BASE_ADDR_)
  #define LIN2LOG                 ((45<<_SHF_)|_BASE_ADDR_)
  #define LOG2LIN                 ((46<<_SHF_)|_BASE_ADDR_)
  #define MATRIX3X3               ((47<<_SHF_)|_BASE_ADDR_)
  #define MIXER                   ((48<<_SHF_)|_BASE_ADDR_)
  #define MONITOR                 ((49<<_SHF_)|_BASE_ADDR_)
  #define NC100HZ                 ((50<<_SHF_)|_BASE_ADDR_)
  #define NSHL                    ((51<<_SHF_)|_BASE_ADDR_)
  #define NSHR                    ((52<<_SHF_)|_BASE_ADDR_)
  #define ORB                     ((53<<_SHF_)|_BASE_ADDR_)
  #define PFILT                   ((54<<_SHF_)|_BASE_ADDR_)
  #define PFIRFILT                ((55<<_SHF_)|_BASE_ADDR_)
  #define PLEVDET                 ((56<<_SHF_)|_BASE_ADDR_)
  #define PNLEVDET                ((57<<_SHF_)|_BASE_ADDR_)
  #define POLY                    ((58<<_SHF_)|_BASE_ADDR_)
  #define RGB2YCC                 ((59<<_SHF_)|_BASE_ADDR_)
  #define RNDGEN                  ((60<<_SHF_)|_BASE_ADDR_)
  #define RS_PARSYN               ((61<<_SHF_)|_BASE_ADDR_)
  #define SHIFT                   ((62<<_SHF_)|_BASE_ADDR_)
  #define SINGLETONEDET           ((63<<_SHF_)|_BASE_ADDR_)
  #define SUB	                  ((64<<_SHF_)|_BASE_ADDR_)
  #define SUMM                    ((65<<_SHF_)|_BASE_ADDR_)
  #define SUPP                    ((66<<_SHF_)|_BASE_ADDR_)
  #define TONEDET                 ((67<<_SHF_)|_BASE_ADDR_)
  #define TONEGEN                 ((68<<_SHF_)|_BASE_ADDR_)
  #define UPSAMPLE420             ((69<<_SHF_)|_BASE_ADDR_)
  #define UPSAMPLE422             ((70<<_SHF_)|_BASE_ADDR_)
  #define UPSAMPLE422V            ((71<<_SHF_)|_BASE_ADDR_)
  #define WINDOWADD               ((72<<_SHF_)|_BASE_ADDR_)
  #define XOR                     ((73<<_SHF_)|_BASE_ADDR_)
  #define YCC2RGB                 ((74<<_SHF_)|_BASE_ADDR_)
  #define ZCROSS                  ((75<<_SHF_)|_BASE_ADDR_)
  #define G729AB_ENC              ((76<<_SHF_)|_BASE_ADDR_)
  #define G729AB_DEC              ((77<<_SHF_)|_BASE_ADDR_)
  #define SVC_ENC                 ((79<<_SHF_)|_BASE_ADDR_)
  #define SVC_DEC                 ((80<<_SHF_)|_BASE_ADDR_)
  #define MIDI_SYNTH              ((81<<_SHF_)|_BASE_ADDR_)
  #define PAEC                    ((82<<_SHF_)|_BASE_ADDR_)
#else
  #error Specify your chip version
#endif

#define USER_FN_TO_INDEX(fn_nr) ((fn_nr<<_SHF_)|0x1) // Use uneven indecies as user function calls
#define INDEX_TO_USER_FN(index) (index>>_SHF_)


// ROM1/2 Data Table Addresses:
// The #ifndefs are there if the customer wants to use tables that are not in shared rom, or if version of the chip without shared ram is used. The new addresses can be defined in gdsp_functionmanager_local_defs.h

#ifndef _CFFT_TWIDDLE_128
  #define _CFFT_TWIDDLE_128			          0x8000 
#endif
#ifndef _CFFT_WINDOW_SINE128
  #define _CFFT_WINDOW_SINE128			      0x8100 
#endif
#ifndef _CFFT_WINDOW_TRIANGLE128
  #define _CFFT_WINDOW_TRIANGLE128	      0x8180 
#endif
#ifndef _DCT_QTABLE_ROM
  #define _DCT_QTABLE_ROM			            0x8200 
#endif
#ifndef _DCT_ZIGZAG_ADDR_PTR
  #define _DCT_ZIGZAG_ADDR_PTR		        0x8280 
#endif
#ifndef _G726_TBL_INTLV
  #define _G726_TBL_INTLV			            0x82C0
#endif
#ifndef _G722_TX_TBL_Q6M8
  #define _G722_TX_TBL_Q6M8			          0x82F0 
#endif
#ifndef _G722_TX_TBL_MISIL
  #define _G722_TX_TBL_MISIL			        0x830D	
#endif
#ifndef _G722_TX_TBL_QQ4M8
  #define _G722_TX_TBL_QQ4M8		          0x834D 
#endif
#ifndef _G722_RX_TBL_QQ2M8_NOTPADDED
  #define _G722_RX_TBL_QQ2M8_NOTPADDED    0x835D 
#endif
#ifndef _G722_TX_TBL_WL
  #define _G722_TX_TBL_WL				          0x8361 
#endif
#ifndef _G722_RX_TBL_WH_NONPADDED
  #define _G722_RX_TBL_WH_NONPADDED	      0x8371 
#endif
#ifndef _G722_TX_TBL_ILB
  #define _G722_TX_TBL_ILB			          0x8375 
#endif
#ifndef _G722_TX_TBL_H
  #define _G722_TX_TBL_H				          0x8395 
#endif
#ifndef _G722_RX_TBL_QQ6M8
  #define _G722_RX_TBL_QQ6M8			        0x83A1 
#endif


// Memory defines for Sc14480 / Sc14450
#define GDSP_FM_SHARED_RAM1_START       0x0010000
#define GDSP_FM_SHARED_RAM1_END         0x0017FFF

#define GDSP_FM_SHARED_RAM2_START       0x0018000
#define GDSP_FM_SHARED_RAM2_END         0x001FFFF

#define GDSP_FM_DSP_MC_RAM1_START       0x1030000
#define GDSP_FM_DSP_MC_RAM2_START       0x1034000


#define GDSP_FM_DSP1_PC_REG             (0x1027FD2)
#define GDSP_FM_DSP1_PC_START_REG       (0x1027FD4)


#define GDSP_FM_DSP2_PC_REG             (0x102FFD2)
#define GDSP_FM_DSP2_PC_START_REG       (0x102FFD4)
#define GDSP_FM_DSP_MAIN_CTRL_REG       (0x1027FBC)

#endif
