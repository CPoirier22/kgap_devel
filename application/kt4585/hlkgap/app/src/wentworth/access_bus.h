/********************************************************************************
 * 																				*
 *		Wentworth Technology Inc												*
 *		77 Industrial Park Road, Unit 201										*
 *		Saco, Maine, USA 04072													*
 *		+1 207-571-9744															*
 *		www.wentworthtechnology.com												*
 *		copyright 2014															*
 *																				*
 ********************************************************************************
 * $History:: access_bus.h													  $	*
 *																				*
 * Initial Revision																*
 ********************************************************************************
 */
#ifndef ACCESS_BUS_H_
#define ACCESS_BUS_H_

//	P2[6] = SET_RTC (RTC/PCM mux pass through control) = RTC (HI) or PCM pass though (LO)
#define BASE_RTC_ON					P2_SET_DATA_REG = Px_6_SET
#define BASE_PCM_ON					P2_RESET_DATA_REG = Px_6_RESET

// access bus registers for communication with RTC
#define RTC							0x68									// 1101000 is 7-bit address
#define ACCESS1_CTRL_REG			*((volatile unsigned short*)0xFF4922)	// ACCESS bus 1 Control register
#define ACCESS1_IN_OUT_REG			*((volatile unsigned short*)0xFF4920)	// ACCESS bus 1 Receive/Transmit register
#define ACCESS1_CLEAR_INT_REG		*((volatile unsigned short*)0xFF4924)	// ACCESS bus 1 Clear Interrupt register

void SetupAccess1Bus(void);
void SetupPCMBus(void);
void WriteAccess1(UByte device_addr, UByte register_addr, UByte write_data);
UByte ReadAccess1(UByte device_addr, UByte register_addr);

#endif /* ACCESS_BUS_H_ */
