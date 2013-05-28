#ifndef HARDWARE_H_
#define HARDWARE_H_

#include "rtxdef.h"
#include "_stddef.h"

extern uint16 getDIPCtrlReg(void);
extern void clearPendingDipInterrupt(void);
extern void setPendingDipInterrupt(void);
extern void setDipInterruptPriority(uint8 priority);
extern uint16 getDIPStatusReg(void);
extern void Init_GenDSP(void);
extern void GotoDIPLabel_PP(WORD DIPLabel);
extern void restartDIP(uint16 dummy);
extern uint16 getPositionDataLatch(void);
extern void InitialControlBmc(void);
extern void PutBmcInstrFP(BYTE cmd, WORD param, BYTE id);
extern void DisableBmcInterrupt(void);
extern void intr_b_PutCtrlCommandProc(uint16 w16Instruction, BYTE id);
extern void setP2ResetOutputDataReg(uint16 val);
extern void setP2SetOutputDataReg(uint16 val);
extern void initDAC(void);
extern void enableClk100Interrupt(void);
extern void DspCfgInit(void);
extern void PutBmcInstrPP(BYTE Opcode, WORD data);
extern void waitForDIPLabel(WORD label);
extern void loadDIPPP(void);
extern void turnOnMicAmp(void);
extern void SetCodecGain_Lsr_reg(BYTE Value, WORD Codec_Lsr);
extern void disableHF(void);
extern uint16 getDIPStatus1Reg(void);
extern void clearPendingTimerInterrupt(void);
extern uint8 getRSSIVal();

extern WORD BmcCtrlRamIndexFP;

#define MICMUTE 0x02

#endif /*HARDWARE_H_*/
