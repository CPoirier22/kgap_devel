#include "../../../../../../include/common/include/_stddef.h"
#include "../../../../../../include/common/include/glibc.h"
#include "../../../../../../include/common/include/rtxdef.h"
#include "../../../../../../include/common/include/print_status.h"
#include "../../../../../../include/common/include/map_480_gcc.h"
#include "../../../../../../include/hlkgap/dduos/include/dduos.h"
#include "../../../../../../include/os/include/os_timer.h"
#include "../../../../../../include/mac/driver/include/dip_instructions.h"
#include "../../../../../../include/mac/eeprom/include/fnvm.h"
#include "../../../../../../include/mac/driver/include/bmcdef6.h"
#include "../../../../../../include/mac/startup/include/pp/bmc_prg.h"
#include "../../../../../../include/application/util/include/bits.h"
#include "../../../../../api/include/DSPSignalHandler.h"
#include "../../../../../../include//os/include/tasks.h"
#include "gdsp_functionmanager_api.h"
#include "gdsp_driver_functions_api.h"
#include "gdsp_local_defines.h" // contains DSP_SEGMENT_SIZE
#include "../sound/sound.h"
#include "gdsp_all_inits.h"
#include "../wentworth/wentworth_pp.h"
#include "../wentworth/wentworth_fp.h"
#include "../wentworth/afe.h"

#define HM_Filler_D2 0xD2 // hopefully a filler
extern void PPID2PMID(PMIDType * PMID, PPIDType PPID);
extern UByte getSpeechBufferIndex(BYTE Pmid[3]);
extern void PutInterruptMail(uint8 Element);
extern void DeliverInterruptMail(uint8 TaskId);
extern void DeleteBuffer(void * BufferPointer);
extern UByte getRunMode(void);
extern UByte general_eeprom_read_req(WORD address, UByte length, PPIDType ppid);
extern void ExecOneBmcInstructionPP(WORD Instruc);

extern UByte WENTWORTHTASK;
extern UByte DIAGTIMERSEQTASK1TIMER;

unsigned char current_melody;

static __data24 uint16* dsp_main_sync0_reg = (uint16*) DSP_MAIN_SYNC0_REG_ADDR;
static __data24 uint16* dsp_main_sync1_reg = (uint16*) DSP_MAIN_SYNC1_REG_ADDR;
static __data24 uint16* dsp_main_ctrl_reg = (uint16*) DSP_MAIN_CTRL_REG_ADDR;
static __data24 uint16* dsp_main_cnt_reg = (uint16*) DSP_MAIN_CNT_REG_ADDR;
static __data24 uint16* dsp_int_mask_reg = (uint16*) DSP_INT_MASK_REG_ADDR;
static __data24 uint16* dsp_ctrl_reg = (uint16*) DSP_CTRL_REG_ADDR;
static __data24 uint16* dsp_int_prio1_reg = (uint16*) DSP_INT_PRIO1_REG_ADDR;
static __data24 uint16* dsp_int_prio2_reg = (uint16*) DSP_INT_PRIO2_REG_ADDR;
static __data24 uint16* dsp_int_reg = (uint16*) DSP_INT_REG_ADDR;

static unsigned char playbackActive = 0;
static unsigned char dspStarted = 0;
static int sound_index = 2;
static int sound_length = 2;
static char * sound_src = 0;
static int initialized = 0;
void StartDSP();
static void StopDSP();

/*================================== TYPES ===================================*/
typedef enum
{
  AMP_LSR = 0x01, AMP_MIC = 0x02, AMP_CLASSD = 0x04
} amplifiers_t;
extern WORD muteController;
UByte copyBufferCounter = 0;
extern copySpeecBuffers* p_copySpeechBuffer1;
extern clearPointers* p_clearPointers1;
//unsigned int hm_mutecontroller = 0;

// if muteController & (1<<1)  then the PP (index 0) has radio interference and wants to mute this channel
// if muteController & (1<<3)  then the PP (index 1) has radio interference and wants to mute this channel
// if muteController & (1<<5)  then the PP (index 2) has radio interference and wants to mute this channel
// if muteController & (1<<7)  then the PP (index 3) has radio interference and wants to mute this channel
// if muteController & (1<<9)  then the PP (index 4) has radio interference and wants to mute this channel
// if muteController & (1<<11) then the PP (index 5) has radio interference and wants to mute this channel
// also check if any headsets are in PAGE mode, if so, continue to mute those channels to post speaker
void MuteBy()
{
  // this function can be optimized with a for-loop or similar
  // however for clarity this is exposed for each PP

  // channel 0
  if (muteController & (1 << 1))
  {
    //p_dynmixer0->weights[0] = 0x0000;
    p_dynmixer1->weights[0] = 0x0000;
    p_dynmixer2->weights[0] = 0x0000;
    p_dynmixer3->weights[0] = 0x0000;
    p_dynmixer4->weights[0] = 0x0000;
    p_dynmixer5->weights[0] = 0x0000;
    p_dynmixer6->weights[0] = 0x0000;
    p_dynmixer7->weights[0] = 0x0000;
    p_dynmixer8->weights[0] = 0x0000;
    p_dynmixer9->weights[0] = 0x0000;
  }
  else
  {
	//p_dynmixer0->weights[0] = ((base_station).LaneForChannel[0] == (base_station).LaneForChannel[0] ? (base_station).CurrentInboundVolumeMixerAtten : 0x0000);
	p_dynmixer1->weights[0] = ((base_station).LaneForChannel[0] == (base_station).LaneForChannel[1] ? (base_station).CurrentInboundVolumeMixerAtten : 0x0000);
	p_dynmixer2->weights[0] = ((base_station).LaneForChannel[0] == (base_station).LaneForChannel[2] ? (base_station).CurrentInboundVolumeMixerAtten : 0x0000);
	p_dynmixer3->weights[0] = ((base_station).LaneForChannel[0] == (base_station).LaneForChannel[3] ? (base_station).CurrentInboundVolumeMixerAtten : 0x0000);
	p_dynmixer4->weights[0] = ((base_station).LaneForChannel[0] == (base_station).LaneForChannel[4] ? (base_station).CurrentInboundVolumeMixerAtten : 0x0000);
	p_dynmixer5->weights[0] = ((base_station).LaneForChannel[0] == (base_station).LaneForChannel[5] ? (base_station).CurrentInboundVolumeMixerAtten : 0x0000);
	p_dynmixer6->weights[0] = (((base_station).LaneForChannel[0] != (base_station).DualBase) || (base_station).PageMode[0] ? 0x0000 : MIXER6_ATTEN);
	p_dynmixer7->weights[0] =  ((base_station).LaneForChannel[0] != (base_station).DualBase ? 0x0000 : (base_station).CurrentInboundVolumeMixerAtten);
	p_dynmixer8->weights[0] = (((base_station).LaneForChannel[0] == (base_station).DualBase) || (base_station).PageMode[0] ? 0x0000 : MIXER6_ATTEN);
	p_dynmixer9->weights[0] =  ((base_station).LaneForChannel[0] != (base_station).DualBase ? (base_station).CurrentInboundVolumeMixerAtten : 0x0000);
  }
  // channel 1
  if (muteController & (1 << 3))
  {
    p_dynmixer0->weights[0] = 0x0000;
    //p_dynmixer1->weights[0] = 0x0000;
    p_dynmixer2->weights[1] = 0x0000;
    p_dynmixer3->weights[1] = 0x0000;
    p_dynmixer4->weights[1] = 0x0000;
    p_dynmixer5->weights[1] = 0x0000;
    p_dynmixer6->weights[1] = 0x0000;
    p_dynmixer7->weights[1] = 0x0000;
    p_dynmixer8->weights[1] = 0x0000;
    p_dynmixer9->weights[1] = 0x0000;
  }
  else
  {
    p_dynmixer0->weights[0] = ((base_station).LaneForChannel[1] == (base_station).LaneForChannel[0] ? (base_station).CurrentInboundVolumeMixerAtten : 0x0000);
    //p_dynmixer1->weights[0] = ((base_station).LaneForChannel[1] == (base_station).LaneForChannel[1] ? (base_station).CurrentInboundVolumeMixerAtten : 0x0000);
    p_dynmixer2->weights[1] = ((base_station).LaneForChannel[1] == (base_station).LaneForChannel[2] ? (base_station).CurrentInboundVolumeMixerAtten : 0x0000);
    p_dynmixer3->weights[1] = ((base_station).LaneForChannel[1] == (base_station).LaneForChannel[3] ? (base_station).CurrentInboundVolumeMixerAtten : 0x0000);
    p_dynmixer4->weights[1] = ((base_station).LaneForChannel[1] == (base_station).LaneForChannel[4] ? (base_station).CurrentInboundVolumeMixerAtten : 0x0000);
    p_dynmixer5->weights[1] = ((base_station).LaneForChannel[1] == (base_station).LaneForChannel[5] ? (base_station).CurrentInboundVolumeMixerAtten : 0x0000);
	p_dynmixer6->weights[1] = (((base_station).LaneForChannel[1] != (base_station).DualBase) || (base_station).PageMode[1] ? 0x0000 : MIXER6_ATTEN);
	p_dynmixer7->weights[1] =  ((base_station).LaneForChannel[1] != (base_station).DualBase ? 0x0000 : (base_station).CurrentInboundVolumeMixerAtten);
	p_dynmixer8->weights[1] = (((base_station).LaneForChannel[1] == (base_station).DualBase) || (base_station).PageMode[1] ? 0x0000 : MIXER6_ATTEN);
	p_dynmixer9->weights[1] =  ((base_station).LaneForChannel[1] != (base_station).DualBase ? (base_station).CurrentInboundVolumeMixerAtten : 0x0000);
  }
  // channel 2
  if (muteController & (1 << 5))
  {
    p_dynmixer0->weights[1] = 0x0000;
    p_dynmixer1->weights[1] = 0x0000;
    //p_dynmixer2->weights[1] = 0x0000;
    p_dynmixer3->weights[2] = 0x0000;
    p_dynmixer4->weights[2] = 0x0000;
    p_dynmixer5->weights[2] = 0x0000;
    p_dynmixer6->weights[2] = 0x0000;
    p_dynmixer7->weights[2] = 0x0000;
    p_dynmixer8->weights[2] = 0x0000;
    p_dynmixer9->weights[2] = 0x0000;
  }
  else
  {
    p_dynmixer0->weights[1] = ((base_station).LaneForChannel[2] == (base_station).LaneForChannel[0] ? (base_station).CurrentInboundVolumeMixerAtten : 0x0000);
    p_dynmixer1->weights[1] = ((base_station).LaneForChannel[2] == (base_station).LaneForChannel[1] ? (base_station).CurrentInboundVolumeMixerAtten : 0x0000);
    //p_dynmixer2->weights[1] = ((base_station).LaneForChannel[2] == (base_station).LaneForChannel[2] ? (base_station).CurrentInboundVolumeMixerAtten : 0x0000);
    p_dynmixer3->weights[2] = ((base_station).LaneForChannel[2] == (base_station).LaneForChannel[3] ? (base_station).CurrentInboundVolumeMixerAtten : 0x0000);
    p_dynmixer4->weights[2] = ((base_station).LaneForChannel[2] == (base_station).LaneForChannel[4] ? (base_station).CurrentInboundVolumeMixerAtten : 0x0000);
    p_dynmixer5->weights[2] = ((base_station).LaneForChannel[2] == (base_station).LaneForChannel[5] ? (base_station).CurrentInboundVolumeMixerAtten : 0x0000);
	p_dynmixer6->weights[2] = (((base_station).LaneForChannel[2] != (base_station).DualBase) || (base_station).PageMode[2] ? 0x0000 : MIXER6_ATTEN);
	p_dynmixer7->weights[2] =  ((base_station).LaneForChannel[2] != (base_station).DualBase ? 0x0000 : (base_station).CurrentInboundVolumeMixerAtten);
	p_dynmixer8->weights[2] = (((base_station).LaneForChannel[2] == (base_station).DualBase) || (base_station).PageMode[2] ? 0x0000 : MIXER6_ATTEN);
	p_dynmixer9->weights[2] =  ((base_station).LaneForChannel[2] != (base_station).DualBase ? (base_station).CurrentInboundVolumeMixerAtten : 0x0000);
  }
  // channel 3
  if (muteController & (1 << 7))
  {
    p_dynmixer0->weights[2] = 0x0000;
    p_dynmixer1->weights[2] = 0x0000;
    p_dynmixer2->weights[2] = 0x0000;
    //p_dynmixer3->weights[2] = 0x0000;
    p_dynmixer4->weights[3] = 0x0000;
    p_dynmixer5->weights[3] = 0x0000;
    p_dynmixer6->weights[3] = 0x0000;
    p_dynmixer7->weights[3] = 0x0000;
    p_dynmixer8->weights[3] = 0x0000;
    p_dynmixer9->weights[3] = 0x0000;
  }
  else
  {
    p_dynmixer0->weights[2] = ((base_station).LaneForChannel[3] == (base_station).LaneForChannel[0] ? (base_station).CurrentInboundVolumeMixerAtten : 0x0000);
    p_dynmixer1->weights[2] = ((base_station).LaneForChannel[3] == (base_station).LaneForChannel[1] ? (base_station).CurrentInboundVolumeMixerAtten : 0x0000);
    p_dynmixer2->weights[2] = ((base_station).LaneForChannel[3] == (base_station).LaneForChannel[2] ? (base_station).CurrentInboundVolumeMixerAtten : 0x0000);
    //p_dynmixer3->weights[2] = ((base_station).LaneForChannel[3] == (base_station).LaneForChannel[3] ? (base_station).CurrentInboundVolumeMixerAtten : 0x0000);
    p_dynmixer4->weights[3] = ((base_station).LaneForChannel[3] == (base_station).LaneForChannel[4] ? (base_station).CurrentInboundVolumeMixerAtten : 0x0000);
    p_dynmixer5->weights[3] = ((base_station).LaneForChannel[3] == (base_station).LaneForChannel[5] ? (base_station).CurrentInboundVolumeMixerAtten : 0x0000);
	p_dynmixer6->weights[3] = (((base_station).LaneForChannel[3] != (base_station).DualBase) || (base_station).PageMode[3] ? 0x0000 : MIXER6_ATTEN);
	p_dynmixer7->weights[3] =  ((base_station).LaneForChannel[3] != (base_station).DualBase ? 0x0000 : (base_station).CurrentInboundVolumeMixerAtten);
	p_dynmixer8->weights[3] = (((base_station).LaneForChannel[3] == (base_station).DualBase) || (base_station).PageMode[3] ? 0x0000 : MIXER6_ATTEN);
	p_dynmixer9->weights[3] =  ((base_station).LaneForChannel[3] != (base_station).DualBase ? (base_station).CurrentInboundVolumeMixerAtten : 0x0000);
  }
  // channel 4
  if (muteController & (1 << 9))
  {
    p_dynmixer0->weights[3] = 0x0000;
    p_dynmixer1->weights[3] = 0x0000;
    p_dynmixer2->weights[3] = 0x0000;
    p_dynmixer3->weights[3] = 0x0000;
    //p_dynmixer4->weights[3] = 0x0000;
    p_dynmixer5->weights[4] = 0x0000;
    p_dynmixer6->weights[4] = 0x0000;
    p_dynmixer7->weights[4] = 0x0000;
    p_dynmixer8->weights[4] = 0x0000;
    p_dynmixer9->weights[4] = 0x0000;
  }
  else
  {
    p_dynmixer0->weights[3] = ((base_station).LaneForChannel[4] == (base_station).LaneForChannel[0] ? (base_station).CurrentInboundVolumeMixerAtten : 0x0000);
    p_dynmixer1->weights[3] = ((base_station).LaneForChannel[4] == (base_station).LaneForChannel[1] ? (base_station).CurrentInboundVolumeMixerAtten : 0x0000);
    p_dynmixer2->weights[3] = ((base_station).LaneForChannel[4] == (base_station).LaneForChannel[2] ? (base_station).CurrentInboundVolumeMixerAtten : 0x0000);
    p_dynmixer3->weights[3] = ((base_station).LaneForChannel[4] == (base_station).LaneForChannel[3] ? (base_station).CurrentInboundVolumeMixerAtten : 0x0000);
    //p_dynmixer4->weights[3] = ((base_station).LaneForChannel[4] == (base_station).LaneForChannel[4] ? (base_station).CurrentInboundVolumeMixerAtten : 0x0000);
    p_dynmixer5->weights[4] = ((base_station).LaneForChannel[4] == (base_station).LaneForChannel[5] ? (base_station).CurrentInboundVolumeMixerAtten : 0x0000);
	p_dynmixer6->weights[4] = (((base_station).LaneForChannel[4] != (base_station).DualBase) || (base_station).PageMode[4] ? 0x0000 : MIXER6_ATTEN);
	p_dynmixer7->weights[4] =  ((base_station).LaneForChannel[4] != (base_station).DualBase ? 0x0000 : (base_station).CurrentInboundVolumeMixerAtten);
	p_dynmixer8->weights[4] = (((base_station).LaneForChannel[4] == (base_station).DualBase) || (base_station).PageMode[4] ? 0x0000 : MIXER6_ATTEN);
	p_dynmixer9->weights[4] =  ((base_station).LaneForChannel[4] != (base_station).DualBase ? (base_station).CurrentInboundVolumeMixerAtten : 0x0000);
  }
  // channel 5
  if (muteController & (1 << 11))
  {
    p_dynmixer0->weights[4] = 0x0000;
    p_dynmixer1->weights[4] = 0x0000;
    p_dynmixer2->weights[4] = 0x0000;
    p_dynmixer3->weights[4] = 0x0000;
    p_dynmixer4->weights[4] = 0x0000;
    //p_dynmixer5->weights[4] = 0x0000;
    p_dynmixer6->weights[5] = 0x0000;
    p_dynmixer7->weights[5] = 0x0000;
    p_dynmixer8->weights[5] = 0x0000;
    p_dynmixer9->weights[5] = 0x0000;
  }
  else
  {
    p_dynmixer0->weights[4] = ((base_station).LaneForChannel[5] == (base_station).LaneForChannel[0] ? (base_station).CurrentInboundVolumeMixerAtten : 0x0000);
    p_dynmixer1->weights[4] = ((base_station).LaneForChannel[5] == (base_station).LaneForChannel[1] ? (base_station).CurrentInboundVolumeMixerAtten : 0x0000);
    p_dynmixer2->weights[4] = ((base_station).LaneForChannel[5] == (base_station).LaneForChannel[2] ? (base_station).CurrentInboundVolumeMixerAtten : 0x0000);
    p_dynmixer3->weights[4] = ((base_station).LaneForChannel[5] == (base_station).LaneForChannel[3] ? (base_station).CurrentInboundVolumeMixerAtten : 0x0000);
    p_dynmixer4->weights[4] = ((base_station).LaneForChannel[5] == (base_station).LaneForChannel[4] ? (base_station).CurrentInboundVolumeMixerAtten : 0x0000);
    //p_dynmixer5->weights[4] = ((base_station).LaneForChannel[5] == (base_station).LaneForChannel[5] ? (base_station).CurrentInboundVolumeMixerAtten : 0x0000);
	p_dynmixer6->weights[5] = (((base_station).LaneForChannel[5] != (base_station).DualBase) || (base_station).PageMode[5] ? 0x0000 : MIXER6_ATTEN);
	p_dynmixer7->weights[5] =  ((base_station).LaneForChannel[5] != (base_station).DualBase ? 0x0000 : (base_station).CurrentInboundVolumeMixerAtten);
	p_dynmixer8->weights[5] = (((base_station).LaneForChannel[5] == (base_station).DualBase) || (base_station).PageMode[5] ? 0x0000 : MIXER6_ATTEN);
	p_dynmixer9->weights[5] =  ((base_station).LaneForChannel[5] != (base_station).DualBase ? (base_station).CurrentInboundVolumeMixerAtten : 0x0000);
  }

  muteController = 0xAAAA; // make MAC layer unmute if speechbuffer CRC is ok, else always mute e.g. reverse burden of audio ok proof
}

void CopySpeechBufferInterrupt(WORD intvec)
{
  if (copyBufferCounter)
  {
    if (--copyBufferCounter == 0)
    {
      MuteBy(); // Always before we set the copy condition
      p_copySpeechBuffer1->copycondition = 0x0000;
      p_clearPointers1->clearcondition = 0x0000;
    }
  }
  DSP_INT_REG |= DURATIONCOUNTER_INT;
  CLEAR_PENDING_DSP_INTERRUPT;
}

#define MUTE_DELAY 1
UByte BMCMuteLevel = 0;
UByte BMCMuteCnt = MUTE_DELAY;

extern gdsp_summator* p_summator;

void setMuteLevel(UByte level)
{
//char *ptr;
//ptr = StringPrint(StatusString, "********************   setMuteLevel[");
//ptr = StrPrintDecByte(ptr, level);
//ptr = StringPrint(ptr, "]  ************");
//PrintStatus(0, StatusString);
  switch(level)
  {
	case 0: p_summator->in1_atten = 0x7FFF; break;	/*   0db */
	case 1: p_summator->in1_atten = 0x5999; break;	/*  -3db */
	case 2: p_summator->in1_atten = 0x3FFF; break;	/*  -6db */
	case 3: p_summator->in1_atten = 0x2CCC; break;	/*  -9db */
	case 4: p_summator->in1_atten = 0x1FFF; break;	/* -12db */
	case 5: p_summator->in1_atten = 0x1666; break;	/* -15db */
	case 6: p_summator->in1_atten = 0x0FFF; break;	/* -18db */
	case 7: p_summator->in1_atten = 0x0B85; break;	/* -21db */
	case 8: p_summator->in1_atten = 0x0000; break;	/*  mute */
  }
}

void ReduceActualVolume(BYTE ForcedMute)
{
  if (ForcedMute)
  {
	setMuteLevel(BMCMuteLevel = 8);
	return;
  }
  if (BMCMuteLevel < 8)
  {
	if (BMCMuteCnt)
	{
	  BMCMuteCnt--;
	}
	else
	{
	  BMCMuteCnt = MUTE_DELAY;
	  BMCMuteLevel++;
	  setMuteLevel(BMCMuteLevel);
	}
  }
}

void IncreaseToNormVolumePP(void)
{
  if (BMCMuteLevel)
  {
	if (BMCMuteCnt)
	{
	  BMCMuteCnt--;
	}
	else
	{
	  BMCMuteCnt = MUTE_DELAY;
	  BMCMuteLevel--;
	  setMuteLevel(BMCMuteLevel);
	}
  }
}

extern void UnMuteTransmitter(void);
unsigned voice_active = 0;
void StateStopDSP(void)
{
  if ((!voice_active) && (!playbackActive))
    StopDSP();
  else
  {
    if (voice_active)
      PrintStatus(0,"Don't stop DSP as voice is active");
    if (playbackActive)
      PrintStatus(0,"Don't stop DSP as playback is active");
  }
}

void PlayFinished(void)
{
  playbackActive = 0;
  AFEDisconnectPlaybackPP();
  StateStopDSP();
  PrintStatus(0,"PlaybackPP finished");
}

void SetMicGain(unsigned char value)
{
  char *ptr;
  value = value & 0x0F;
  ptr = StringPrint(StatusString, "SetMICGain[");
  ptr = StrPrintHexByte(ptr, value);
  ptr = StringPrint(ptr, "]");
  PrintStatus(0, StatusString);
  CODEC_MIC_REG &= ~(0x0F << 4);
  CODEC_MIC_REG |= value << 4; // Set Mic Gain
}

// 0 to 7  where 0 is -12dB and 7 is +2dB
// LSR gain == -12 + (vol_val * 2)
void SetLSRGain(unsigned int vol_val)
{
  char *ptr;
  ptr = StringPrint(StatusString, "SetLSRGain[");
  ptr = StrPrintHexByte(ptr, vol_val);
  ptr = StringPrint(ptr, "]");
  PrintStatus(0, StatusString);
  CODEC_LSR_REG &= ~(0x07 << 6); // First clear the LSRATT bits; +2dB
  // set gain - remember gain is reversed e.g. vol_val of 7 is +2dB and vol_val of 0 is -12 dB

  switch (vol_val)
  {
    case 0:
      CODEC_LSR_REG |= (0x07 << 6);		// -12dB
      break;
    case 1:
      CODEC_LSR_REG |= (0x06 << 6);		// -10dB
      break;
    case 2:
      CODEC_LSR_REG |= (0x05 << 6);		// -8dB
      break;
    case 3:
      CODEC_LSR_REG |= (0x04 << 6);		// -6dB
      break;
    case 4:
      CODEC_LSR_REG |= (0x03 << 6);		// -4dB
      break;
    case 5:
      CODEC_LSR_REG |= (0x02 << 6);		// -2dB
      break;
    case 6:
      CODEC_LSR_REG |= (0x01 << 6);		// 0dB
      break;
      // no reason for 7 as this has already been set in the beginning
  }
}

void StartCODEC(uint8 amps)
{
  WORD i;
  CODEC_TONE_REG |= CID_PR_DIS;
  CODEC_VREF_REG = VREF_INIT | (1 << 3);	/* vrefs on*/

  for (i = 0; i < 10000; i++)
    ;										/* 100us delay */

  CODEC_VREF_REG = (1 << 3);				/* vrefs on*/

  if ((amps & AMP_MIC) == AMP_MIC)
  {
	  CODEC_MIC_REG &= ~(MIC_PD | MIC_MUTE | MICH_ON);
  }
  else
  {
	CODEC_MIC_REG |= MIC_PD;
  }

  if ((amps & AMP_LSR) == AMP_LSR)
  {
    CODEC_LSR_REG = (3 << 6) | (2 << 3) | (2 << 0);							/* enable -4dB; LSRN LSRP differential */
  }
  else
  {
    CODEC_LSR_REG = (1 << 6) | LSRN_PD | (2 << 3) | LSRP_PD | (2 << 0);		/* enable 0dB; LSRN LSRP differential; LSRN_PD, LSRP_PD */
  }

  if ((amps & AMP_CLASSD) == AMP_CLASSD)
  {
    CLASSD_CTRL_REG &= ~CLASSD_PD;
    CLASSD_CTRL_REG |= (CLASSD_POPEN | CLASSD_MOPEN);
    CLASSD_CTRL_REG &= ~(CLASSD_VOUT); // 4V max on eval kit, unless external supply is active
  }
  else
  {
    CLASSD_CTRL_REG |= CLASSD_PD;
    CLASSD_CTRL_REG &= ~(CLASSD_POPEN | CLASSD_MOPEN);
  }

  CODEC_ADDA_REG = AD_DITH_OFF | DA_DITH_OFF | (2 << 4) | (2 << 2);		/* enable AD/DA */

  CLK_CODEC_REG |= (0x1000 | 0x2000 | 0x0800 | 0x0400);		// 0x3C00 = CLK_DA_CLASSD_EN, CLK_DA_LSR_EN, CLK_AD_EN, CLK_MAIN_EN

  if (FP_EepromInRam.FP_PP_Select == 0)
  {
    UnMuteTransmitter();
  }
}

void StartAdpcmPP(void)
{
  ExecOneBmcInstructionPP((BK_A << 8) | ((SPEECHBUFFER1_OFS & 0x0700) >> 3)); // set bank for ADPCM
  ExecOneBmcInstructionPP((WORD) (A_NORM << 8));
  PrintStatus(0, "Started ADPCM module");
}

void StopRingingMelody(void)
{
  p_playbackbuffer->mode = 0x0000; // stops the playback buffer
  sound_src = getWavPointer(0xFF); // this gives the default silence
  sound_index = 2;
  sound_length = (sound_src[0] << 8) + sound_src[1];
  AFEDisconnectPlaybackPP();// disconnect audio from playback
}

void EnableDSPForTonegeneratorPP(void)
{
  SignalType *s;
  PrintStatus(0, "EnableDSPForTonegeneratorPP");
  NewSignal(sizeof(SignalType), (void**) &s);
  SendSignal(s, DSP_PROCESS_ID, HMSETUPAUDIO_EVENT, 0);
}

void PlaySoundPP(unsigned char index)
{
  AFEConnectPlaybackPP();				// connect audio from playback
  if (index == sound_vehicle_detect_100ms)
  {
    switch (headset.GainSpkrVolume + 2)				// adjust summator to play VD beeps -2dB quieter:
    {												// in2_ptr dB = (InboundVol x -2) - 15.1
	  case -5: p_gendspgainconstant_pp->value = 0x1680; break;	// -15.1dB (Inbound Volume = 0)
	  case -3: p_gendspgainconstant_pp->value = 0x11DF; break;	// -17.1dB (Inbound Volume = 1)
	  case -1: p_gendspgainconstant_pp->value = 0x0E32; break;	// -19.1dB (Inbound Volume = 2)
	  case  1: p_gendspgainconstant_pp->value = 0x0B46; break;	// -21.1dB (Inbound Volume = 3)
	  case  3: p_gendspgainconstant_pp->value = 0x08F5; break;	// -23.1dB (Inbound Volume = 4)
	  case  5: p_gendspgainconstant_pp->value = 0x071D; break;	// -25.1dB (Inbound Volume = 5)
	  case  7: p_gendspgainconstant_pp->value = 0x05A6; break;	// -27.1dB (Inbound Volume = 6)
	  case  9: p_gendspgainconstant_pp->value = 0x047D; break;	// -29.1dB (Inbound Volume = 7)
	  case 11: p_gendspgainconstant_pp->value = 0x0390; break;	// -31.1dB (Inbound Volume = 8)
	  case 13: p_gendspgainconstant_pp->value = 0x02D5; break;	// -33.1dB (Inbound Volume = 9)
    }
  }
  sound_src = getWavPointer(index);		// first we find out which melody to play
  sound_index = 2;
  sound_length = (sound_src[0] << 8) + sound_src[1];
  p_playbackbuffer->mode = 0x0002;
  playbackActive = 1;
  if (!dspStarted)
  {
    SignalType *s;
    NewSignal(sizeof(SignalType), (void**) &s);
    SendSignal(s, DSP_PROCESS_ID, HMSETUPAUDIO_EVENT, 0);
  }
  else
  {
    DSP_INT_MASK_REG |= PLAYBACKBUFFER_INT; // re-enable playback buffer interrupt
  }
}

void PlaySoundFP(unsigned char index)
{
  GdspStart((unsigned short*)p_playbackbuffer);
  GdspStart((unsigned short*)p_law2lin);
  sound_src = getWavPointer(index);             // first we find out which melody to play
  sound_index = 2;
  sound_length = (sound_src[0] << 8) + sound_src[1];
  p_playbackbuffer->mode = 0x0002;
  playbackActive = 1;
  if (!dspStarted)
  {
    SignalType *s;
    NewSignal(sizeof(SignalType), (void**) &s);
    SendSignal(s, DSP_PROCESS_ID, HMSETUPAUDIO_EVENT, 0);
    DSP_INT_MASK_REG |= PLAYBACKBUFFER_INT; // re-enable playback buffer interrupt
  }
  else
  {
    DSP_INT_MASK_REG |= PLAYBACKBUFFER_INT; // re-enable playback buffer interrupt
  }
  PrintStatus(0,"PlaySoundFP started");
}

void PlayRingingMelody(int sound_index)
{
  PlaySoundPP(sound_index);
}

void PlaybackInt(WORD intvec)
{
  int f;
  // when interrupt, then mode is 0x8002, because playbackbuffer
  // loads the conditional register from the first address "LDC_INSTR, 0" in this block
  p_playbackbuffer->mode = 0x0002;
  p_playbackbuffer->irq = 0;// no need to use
  p_playbackbuffer->read_idx = 0;
  p_playbackbuffer->write_idx = 15;
  for (f = 0; (f < 16) && (sound_index < sound_length); f++)
    p_playbackbuffer->taps[f] = sound_src[sound_index++] << 8; // remember to shift to high byte
  p_playbackbuffer->buffer_irq_size = f - 1;//15;
  if (sound_index >= sound_length) // did we reach the end of the sound buffer?
  {
    if (WENTWORTHTASK!=0xFF) // (-1) Important if we by chance forget to start this task, then the application will hang
    {
      PutInterruptMail(HM_Filler_D2);
      PutInterruptMail(1);// melody finished - remember to convert to some kind of enum
      DeliverInterruptMail(WENTWORTHTASK);
    }
    DSP_INT_MASK_REG &= ~(PLAYBACKBUFFER_INT); // Only disable PLAYBACKBUFFER_INT
    p_playbackbuffer->mode = 0x0000;
  }
  SetWord(dsp_int_reg,PLAYBACKBUFFER_INT);
  CLEAR_PENDING_DSP_INTERRUPT;
}

void PlaybackIntFP(WORD intvec)
{
  int f;
  // when interrupt, then mode is 0x8002, because playbackbuffer
  // loads the conditional register from the first address "LDC_INSTR, 0" in this block
  p_playbackbuffer->mode = 0x0002;
  p_playbackbuffer->irq = 0;// no need to use
  p_playbackbuffer->read_idx = 0;
  p_playbackbuffer->write_idx = 15;
  for (f = 0; (f < 16) && (sound_index < sound_length); f++)
    p_playbackbuffer->taps[f] = sound_src[sound_index++] << 8; // remember to shift to high byte
  p_playbackbuffer->buffer_irq_size = f - 1;//15;
  if (sound_index >= sound_length) // did we reach the end of the sound buffer?
  {
    if (WENTWORTHTASK!=0xFF) // (-1) Important if we by chance forget to start this task, then the application will hang
    {
      PutInterruptMail(HM_Filler_D2);
      PutInterruptMail(1);// melody finished - remember to convert to some kind of enum
      DeliverInterruptMail(WENTWORTHTASK);
    }
    DSP_INT_MASK_REG &= ~(PLAYBACKBUFFER_INT); // Only disable PLAYBACKBUFFER_INT
    p_playbackbuffer->mode = 0x0000;
  }
  SetWord(dsp_int_reg,PLAYBACKBUFFER_INT);
  CLEAR_PENDING_DSP_INTERRUPT;
}

void OutbufferInt(WORD intvec)
{
  SetWord(dsp_int_reg,OUT_BUFFER_INT);
  CLEAR_PENDING_DSP_INTERRUPT;
}

//extern unsigned char mic_tone_detected;
void ToneDetectInt(WORD intvec)
{
  //	mic_tone_detected=1;
  CLEAR_PENDING_DSP_INTERRUPT;
}

/*
 * Continuously checks PCM[3] for a change.  Changes are noted and sent out to be handled.
 *
 * Idea is that the normal state of the bus is 0x0000.
 * The initiator sends a command for about 4ms.
 * Currently there is no handshaking/acknowledgment.
 *
 */
void PCMBusCmdInt(WORD intvec)
{
  // snoop incoming FP to FP commands on PCM[3]
  if ((p_pcm_buffer->taps[17] == 0x0000) && ((base_station).LastPCMCmdRx == 0x0000))
  {
  }
  else if (p_pcm_buffer->taps[17] && (p_pcm_buffer->taps[17] != 0xFFFF) && (p_pcm_buffer->taps[17] != (base_station).LastPCMCmdRx))
  {
	(base_station).LastPCMCmdRx = p_pcm_buffer->taps[17];
	// send mail to handle received command here ...
	PutInterruptMail(PCM_ind);
	PutInterruptMail((base_station).LastPCMCmdRx >> 8);
	PutInterruptMail((base_station).LastPCMCmdRx & 0x00FF);
	DeliverInterruptMail(WENTWORTHTASK);
//char *ptr;
//ptr = StringPrint(StatusString, "pcm:=");
//ptr = StrPrintHexWord(ptr, p_pcm_buffer->taps[0]);
//ptr = StringPrint(ptr, " ");
//ptr = StrPrintHexWord(ptr, p_pcm_buffer->taps[8]);
//ptr = StringPrint(ptr, " ");
//ptr = StrPrintHexWord(ptr, p_pcm_buffer->taps[16]);
//ptr = StringPrint(ptr, " ");
//ptr = StrPrintHexWord(ptr, p_pcm_buffer->taps[17]);
//ptr = StringPrint(ptr, " ");
//ptr = StrPrintHexWord(ptr, p_pcm_buffer->taps[18]);
//ptr = StringPrint(ptr, " ");
////ptr = StrPrintHexWord(ptr, p_pcm_buffer->read_idx);
////ptr = StringPrint(ptr, ", write=");
////ptr = StrPrintHexWord(ptr, p_pcm_buffer->write_idx);
////ptr = StringPrint(ptr, ", buffer_ptr=");
////ptr = StrPrintHexWord(ptr, p_pcm_buffer->buffer_ptr);
////ptr = StringPrint(ptr, ", buffer_irq_size=");
////ptr = StrPrintHexWord(ptr, p_pcm_buffer->buffer_irq_size);
////ptr = StringPrint(ptr, ", irq=");
////ptr = StrPrintHexWord(ptr, p_pcm_buffer->irq);
////ptr = StringPrint(ptr, " ");
//PrintStatus(0, StatusString);
  }
  else if ((p_pcm_buffer->taps[17] == 0x0000) && ((base_station).LastPCMCmdRx != 0x0000))
  {
	(base_station).LastPCMCmdRx = 0x0000;
  }
  CLEAR_PENDING_DSP_INTERRUPT;
}

void StartDSP(void)
{
  WORD i;
  CLK_AMBA_REG |= MCRAM1_EN;
  SetWord(dsp_ctrl_reg, 0x0000); // Switch off DSP
  for (i = 0; i < 1000; i++)
    ;
  PrintStatus(0, "StartDSP");
  // Activate program start
  CLK_DSP_REG = 9; // Gen2DSP clock divider enabled, DSP_EN starts Gen2DSP

  SetBits(dsp_ctrl_reg, DSP_CLK_EN, 1); // Gen2DSP clock disabled after WTF execution. Wakes up on SYNC event

  SetBits(dsp_main_sync0_reg, RAMIN0_SYNC,0);
  // G.726 @ 8 kHz
  SetBits(dsp_main_sync0_reg, RAMOUT0_SYNC,0); // G.726 @ 8 kHz

  SetWord(dsp_main_sync1_reg,0); // clear entire register, AD_SYNC,DA_LSR_SYNC,DSP_SYNC1,DA_CLASSD_SYNC,ADC_SYNC,PCM_SYNC etc.
  SetBits(dsp_main_sync1_reg, DSP_SYNC0,0); // 8KHZ strobe to SYNC0

  //  ----- Important ----
  SetWord(dsp_int_prio1_reg, 0x0077); // DSP_INT0_PRIO = DSP_SYNC0
  SetWord(dsp_int_prio2_reg, 0x0776);
  //  ----- Important ----

  SetWord(dsp_int_mask_reg, 0x0000);
  if (!getRunMode()) // PP
    GdspHookVector(PLAYBACKBUFFER_INT, PlaybackInt, DSP1); // hook up playback interrupt handler
  else
  {
    GdspHookVector(DURATIONCOUNTER_INT, CopySpeechBufferInterrupt, DSP1); // hook up playback interrupt handler
    GdspHookVector(PCM_BUFFER_INT, PCMBusCmdInt, DSP1); // hook up PCM[3] command interrupt handler
  }
  DSP_INT_MASK_REG = 0; // GetHookVector enables the mask, but if we do that, the duration interrupt crashes

  // Activate program end
  SetWord(dsp_ctrl_reg, 0x0004);

  // Switch on DSP & DSP clock
  SetBits(dsp_main_cnt_reg , DSP_MAIN_REL, 0x8F);
  SetBits(dsp_main_ctrl_reg, DSP_MAIN_CTRL, 0); // DSP main counter in reset.
  SetBits(dsp_main_ctrl_reg, DSP_MAIN_CTRL, 1); // DSP main counter out of reset, free running
  if (!getRunMode()) // PP
  {
    SetWord(dsp_int_reg,PLAYBACKBUFFER_INT);
    SetWord(dsp_int_mask_reg, PLAYBACKBUFFER_INT);
  }
  else
  {
    DSP_INT_REG |= (DURATIONCOUNTER_INT);
    DSP_INT_REG |= (PCM_BUFFER_INT);
  }
  CLEAR_PENDING_DSP_INTERRUPT;

  dspStarted = 1;
}

void EnableSpeechbufferInterrupt(void)
{
//  PrintStatus(0,"EnableSpeechbufferInterrupt");
  DSP_INT_REG |= (DURATIONCOUNTER_INT | PLAYBACKBUFFER_INT);
  DSP_INT_REG |= PCM_BUFFER_INT;
  DSP_INT_MASK_REG |= (DURATIONCOUNTER_INT); // For some reason this need to be enabled a little bit later otherwise it crashes
  DSP_INT_MASK_REG |= PCM_BUFFER_INT;
  p_pcm_buffer->mode = 0x0001;
//  P2_MODE_REG |= (1 << 13); // EnAble DSP WTF output
//  PrintStatus(0,"leaving EnableSpeechbufferInterrupt ... ");
}

void CheckDSP(void)
{
  char *ptr;
  if (DSP_OVERFLOW_REG & (INT_OVERFLOW))// | WTF_OVERFLOW)) // This was unexpected
  {
    if (DSP_OVERFLOW_REG & INT_OVERFLOW)
      PrintStatus(0, "---DSP INT OVERFLOW----");
    DSP_OVERFLOW_REG |= (INT_OVERFLOW+WTF_OVERFLOW);
    // lets find out the DSP running frequency
    ptr = StringPrint(StatusString, "[");
    ptr = StrPrintHexWord(ptr, CLK_DSP_REG);
    ptr = StringPrint(ptr, ",");
    ptr = StrPrintHexWord(ptr, CLK_PLL_CTRL_REG);
    ptr = StringPrint(ptr, ",");
    ptr = StrPrintHexWord(ptr, CLK_XTAL_CTRL_REG);
    ptr = StringPrint(ptr, ",");
    ptr = StrPrintHexWord(ptr, CLK_PLL_DIV_REG);
    ptr = StringPrint(ptr, "]");
    PrintStatus(0, StatusString);
  }
}
static void StopDSP()
{
   /*  char *ptr;
   ptr = StringPrint(StatusString, "DSP_OVERFLOW_REG[");
   ptr = StrPrintHexWord(ptr, DSP_OVERFLOW_REG);
   ptr = StringPrint(ptr, "]");
   PrintStatus(0, StatusString);*/
  // It may not be the correct place, but try test for DSP overflow - during this voice/melody session
  CheckDSP();
  SetWord(dsp_ctrl_reg, 0x0000); // Switch off DSP
  if (!getRunMode()) // PP
    SetWord(dsp_int_reg,PLAYBACKBUFFER_INT); // in case it was active
  else
    SetWord(dsp_int_reg,DURATIONCOUNTER_INT); // in case it was active
  SetWord(dsp_int_mask_reg, 0x0000); // remove all in interrupt mask

  CODEC_ADDA_REG |= DA_PD | AD_PD;
  CODEC_MIC_REG |= MIC_PD;

  CODEC_LSR_REG |= LSRP_PD | LSRN_PD;

  CODEC_VREF_REG = 0;
  /*CODEC_VREF_REG = REFINT_PD;
   CODEC_VREF_REG |= AGND_LSR_PD;
   CODEC_VREF_REG |= BIAS_PD;
   CODEC_VREF_REG |= VREF_BG_PD;
   CODEC_VREF_REG |= AMP1V5_PD;
   CODEC_VREF_REG |= VREF_FILT_PD;
   CODEC_VREF_REG |= VREF_PD; //0x03F7;
   */CODEC_VREF_REG |= VREF_INIT;
  CODEC_VREF_REG |= (1 << 3);

  /*    CODEC_VREF_REG = REFINT_PD | AGND_LSR_PD | BIAS_PD | VREF_BG_PD | AMP1V5_PD | VREF_INIT | (1 << 3) | VREF_FILT_PD | VREF_PD; //0x03F7;
   */CLASSD_CTRL_REG |= CLASSD_PD;
  CLASSD_CTRL_REG &= ~(CLASSD_POPEN | CLASSD_MOPEN);

  //CLK_AMBA_REG &= ~MCRAM1_EN;
  PrintStatus(0, "StopDSP");
  dspStarted = 0;
}
extern UByte DSPTASKTIMER;
extern ProcessIdType DSP_PROCESS_ID;
extern int gen2dsp_init(void);

void DSPSignalHandlerPP(SignalType *signal)
{
  switch (signal->Event)
  {
    case INITIALIZE_EVENT:
    {
//      PrintStatus(0, "DSPSignalHandlerPP.INITIALIZE_EVENT");
      if (initialized == 0)
      {
        if (gen2dsp_init() == GDSP_NO_SUCCESS)
          PrintStatus(0, "gen2dsp_init() failed!!");
        else
          PrintStatus(0, "gen2dsp_init() success!!");
        initialized = 1;
      }
      StopDSP();
    }
      break;
    case HMSETUPAUDIO_EVENT: // Used by PlaySoundPP/PlaySoundFP - just start everything
    {
      if (!dspStarted)
      {
//        PrintStatus(0, "DSPSignalHandlerPP.HMSETUPAUDIO_EVENT");
        StartAdpcmPP();
        StartCODEC(AMP_LSR);						// PP uses only the LSR amp, MIC comes from BC5 via PCM bus
        SetLSRGain(7);								// set up LSR gain
        StartDSP();
      }
      else
        DSP_INT_MASK_REG |= PLAYBACKBUFFER_INT; // re-enable playback buffer interrupt
    }
      break;
    case SETUPAUDIO_EVENT: // Used for voice
    {
//      PrintStatus(0, "DSPSignalHandlerPP.SETUPAUDIO_EVENT");
      if (!dspStarted) // reinitialize all Audio paths and setup
      {
        SignalType *s;
        NewSignal(sizeof(SignalType), (void**) &s);
        SendSignal(s, DSP_PROCESS_ID, STARTADPCM_EVENT, 0);
        AFEConnectAudioPathPP();
      }
      else // everything is started - just open for voice
      {
    	AFEConnectAudioPathPP();
        voice_active = 1;
      }
      AFEDisableMicPathPP();															// disable MIC; CB controls MIC
      AFESetVolume(headset.GainVolume);													// set up MIC gain
      AFESetGainInboundVolumePP(headset.GainSpkrVolume + (headset.SpeakerVolume - 8));	// set up post decoder gain
      AFESetGainSpkrVolumePP(12 + headset.SpkrVolOffset);								// set up pre-LSR gain
    }
      break;
    case STARTADPCM_EVENT:
    {
//      PrintStatus(0, "DSPSignalHandlerPP.STARTADPCM_EVENT");
      SignalType *s;
      NewSignal(sizeof(SignalType), (void**) &s);
      SendSignal(s, DSP_PROCESS_ID, STARTCODEC_EVENT, 0);
      StartAdpcmPP();
      voice_active = 1;
    }
      break;
    case STARTCODEC_EVENT:
    {
//      PrintStatus(0, "DSPSignalHandlerPP.STARTCODEC_EVENT");
      SignalType *s;
      NewSignal(sizeof(SignalType), (void**) &s);
      SendSignal(s, DSP_PROCESS_ID, STARTDSP_EVENT, 0);
      StartCODEC(AMP_LSR);							// PP uses only the LSR amp, MIC comes from BC5 via PCM bus
      SetLSRGain(7);								// set up LSR gain

      // CRP: using this as a "delayed" area to do start up stuff ...

	  P2_SET_DATA_REG = Px_7_SET;					// set DECT P2[7] to be driven HI (BC5 RESETN) to bring BC5 up
      PrintStatus(0, "**** DSPSignalHandler: BC5 RESETN is HI");

      general_eeprom_read_req(0x00, 5, 0);			// once we're connected to the base, read this PP IPEI
      PrintStatus(0, "RED");
      TurnOnRedLED;
      OSStartTimer(DIAGTIMERSEQTASK1TIMER, 75);		// wait to make sure DSP is started
    }
      break;
    case STARTDSP_EVENT:
    {
        if (!dspStarted)
        StartDSP();
      else
        DSP_INT_MASK_REG |= PLAYBACKBUFFER_INT; // re-enable playback buffer interrupt
    }
      break;
    case STOPAUDIO_EVENT:
    {
      voice_active = 0;
      StateStopDSP();
    }
      break;
    case TIME_OUT_EVENT:
    {
    }
      break;
  }
  DeleteBuffer(signal);
}

void DSPSignalHandlerFP(SignalType *signal)
{
  switch (signal->Event)
  {
    case INITIALIZE_EVENT:
    {
      SignalType *s;
      if (initialized == 0)
      {
        if (gen2dsp_init() == GDSP_NO_SUCCESS)
          PrintStatus(0, "gen2dsp_init() failed!!");
        else
          PrintStatus(0, "gen2dsp_init() success!!");
        initialized = 1;
      }
      StopDSP();
      NewSignal(sizeof(SignalType), (void**) &s);
       SendSignal(s, DSP_PROCESS_ID, SETUPAUDIO_EVENT, 0);
      //SendSignal(s, DSP_PROCESS_ID, STARTDSP_EVENT,0);

    }
      break;
    case HMSETUPAUDIO_EVENT: // doesn't matter
      break;
    case SETUPAUDIO_EVENT: // Used for voice
    {
      SignalType *s;
      NewSignal(sizeof(SignalType), (void**) &s);
      SendSignal(s, DSP_PROCESS_ID, STARTADPCM_EVENT, 0);
    }
      break;
    case STARTADPCM_EVENT:
    {
      SignalType *s;
      NewSignal(sizeof(SignalType), (void**) &s);
      SendSignal(s, DSP_PROCESS_ID, STARTCODEC_EVENT, 0);
    }
      break;
    case STARTCODEC_EVENT:
    {
//      PrintStatus(0, "DSPSignalHandlerFP.STARTCODEC_EVENT");
      SignalType *s;
      NewSignal(sizeof(SignalType), (void**) &s);
      SendSignal(s, DSP_PROCESS_ID, STARTDSP_EVENT, 0);
      StartCODEC(AMP_LSR | AMP_MIC);											// using both the LSR and MIC amps
	  AFESetGainInboundVolumeFP(NORMAL_INBOUND);								// inbound range in 2dB steps (vol x 2 = dB change applied)
	  AFESetGainSpkrVolumeFP(5);												// outbound range in 2dB steps (vol x 2 = dB change applied)
      AFESetCodecMicGain(0);													// 0dB to +30dB range in 2dB steps (0x00 = 0 x 2 = 0dB)
      AFEDisablePostMicPath();													// post MIC comes up muted by disabling DECT MIC input
   	  GRILL_SPEAKER_OFF;														// grill speaker comes up muted
   	  MENU_SPKR_AMP_OFF;														// post speaker comes up muted (enables GREET audio path in to DECT MICP/N)
      CODEC_LSR_REG = (1 << 6) | (2 << 3) | (2 << 0);							// +2dB to -12dB range in 2dB steps (1 = +2 - (1 x 2) = 0dB); LSRN LSRP differential

      // CRP: using this as a "delayed" area to do start up stuff ...

    }
      break;
    case STARTDSP_EVENT:
    {
      if (!dspStarted)
        StartDSP();
    }
      break;
    case STOPAUDIO_EVENT:
    {
      StateStopDSP();
    }
      break;
    case TIME_OUT_EVENT:
    {
    }
    break;
  }
  DeleteBuffer(signal);
}

void DSPSignalHandler(SignalType *signal)
{
  if (getRunMode()) // FP
    DSPSignalHandlerFP(signal);
  else
    DSPSignalHandlerPP(signal);
}

// Polycom function - can we delete these ?
void dspDebug()
{
}

void playback()
{
}

void playsound(UByte sound)
{
}

void handle_playsound(UByte sound_to_play)
{
}

void common_playsound(UByte sound_to_play)
{
}

void wavPlayer(void)
{
}
