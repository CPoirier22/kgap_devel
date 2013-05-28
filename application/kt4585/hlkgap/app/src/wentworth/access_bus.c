/********************************************************************************
 * 																				*
 *		Wentworth Technology Inc												*
 *		77 Industrial Park Road, Unit 201										*
 *		Saco, Maine, USA 04072													*
 *		+1 207-571-9744															*
 *		www.wentworthtechnology.com												*
 *		copyright 2013															*
 *																				*
 ********************************************************************************
 * $History:: access_bus.c													  $	*
 *																				*
 * Initial Revision																*
 ********************************************************************************
 */

#include "../../../../../../include/os/include/tasks.h"
#include "../../../../../../include/os/include/os.h"
#include "../../../../../../include/os/include/os_tasks.h"
#include "../../../../../../include/os/include/os_mail.h"
#include "../../../../../../include/os/include/intmail.h"
#include "../../../../../../include/os/include/os_timer.h"
#include "../../../../../../include/os/include/os_timers.h"
#include "../../../../../../include/os/include/mailprim.h"
#include "../../../../../../include/os/include/maildef.h"
#include "../../../../../../include/hlkgap/dduos/include/dduos.h"
#include "../../../../../../include/common/include/print_status.h"
#include "../../../../../../include/mac/startup/include/interrupts.h"
#include "../../../../../../include/hlkgap/common/include/aformat.h"
#include "../../../../../../include/common/include/map_480_gcc.h"
#include "../../../../../../include/hlkgap/app/include/apdbprim.h"
#include "../../../../../../include/common/include/glibc.h"
#include "../../../../../api/include/common/common_general_functions.h"
#include "../../../../../api/include/fp/fp_msf_functions.h"
#include "../dsp/gdsp_local_defines.h"
#include "access_bus.h"

static void usec_pause(unsigned int x)
{
    volatile unsigned int i;
    for (i = 0; i < x; i++)
    {
    	;
    }
}

void SetupAccess1Bus(void)
{
	P2_MODE_REG &= ~(P2_4_MODE | P2_3_MODE);		// clear the bits in question first
	P2_MODE_REG |= (P2_4_MODE & 0x0200);			// switch from PCM_DO to SCL1
	P2_MODE_REG |= (P2_3_MODE & 0x0080);			// switch from PCM_DI to SDA1
	P2_DIR_REG |= Px_4_DIR;							// enable SCL1 as an output
	P2_DIR_REG |= Px_3_DIR;							// enable SDA1 as an output

	ACCESS1_CTRL_REG |= (SDA_OD | SCL_OD);			// set SDA and SCL to open drain
	ACCESS1_CTRL_REG |= SCK_NUM;					// use 8 bits plus ACK
	ACCESS1_CTRL_REG |= EN_ACCESS_INT;				// enable access bus interrupt
}

void SetupPCMBus(void)
{
	P2_DIR_REG |=  Px_4_DIR;						// enable PCM_DO as an output
	P2_DIR_REG &= ~Px_3_DIR;						// enable PCM_DI as an input w/no pull resistor
	P2_MODE_REG &= ~(P2_4_MODE | P2_3_MODE);		// clear the bits in question first
	P2_MODE_REG |= (P2_4_MODE & 0x0100);			// switch from SCL1 back to PCM_DO
	P2_MODE_REG |= (P2_3_MODE & 0x0040);			// switch from SDA1 back to PCM_DI
}

void SendAccess1Start(void)
{
	ACCESS1_CTRL_REG |= (SDA_VAL | SCL_VAL);		/* 11  \                                 	*/
	ACCESS1_CTRL_REG &= ~SDA_VAL;					/* 01   > START                          	*/
	ACCESS1_CTRL_REG &= ~(SDA_VAL | SCL_VAL);		/* 00  /                                 	*/
	ACCESS1_CTRL_REG |= EN_ACCESS_BUS;				/* start the ACCESS bus                  	*/
}

void SendAccess1ReStart(void)
{
	ACCESS1_CTRL_REG &= ~EN_ACCESS_BUS;				/* disable the ACCESS bus to send RE-START  */
	ACCESS1_CTRL_REG &= ~(SDA_VAL | SCL_VAL);		/* 00  \                                 	*/
	ACCESS1_CTRL_REG |= SCL_VAL;					/* 01   > STOP                           	*/
	ACCESS1_CTRL_REG |= (SDA_VAL | SCL_VAL);		/* 11  \                                 	*/
	ACCESS1_CTRL_REG &= ~SDA_VAL;					/* 01   > START                          	*/
	ACCESS1_CTRL_REG &= ~(SDA_VAL | SCL_VAL);		/* 00  /                                 	*/
	ACCESS1_CTRL_REG |= EN_ACCESS_BUS;				/* start the ACCESS bus                  	*/
}

void SendAccess1Stop(void)
{
	ACCESS1_CTRL_REG &= ~EN_ACCESS_BUS;				/* disable the ACCESS bus to send STOP   	*/
	ACCESS1_CTRL_REG &= ~(SDA_VAL | SCL_VAL);		/* 00  \                                 	*/
	ACCESS1_CTRL_REG |= SCL_VAL;					/* 01   > STOP                           	*/
	ACCESS1_CTRL_REG |= (SDA_VAL | SCL_VAL);		/* 11  /                                 	*/
}

void WriteAccess1(UByte device_addr, UByte register_addr, UByte write_data)
{
	SendAccess1Start();

	ACCESS1_IN_OUT_REG = (device_addr << 1);		// RTC slave address w/nWRITE
	usec_pause(100);

	ACCESS1_IN_OUT_REG = register_addr;				// RTC register address
	usec_pause(100);

	ACCESS1_IN_OUT_REG = write_data;				// write data ...
	usec_pause(100);

	SendAccess1Stop();
}

UByte ReadAccess1(UByte device_addr, UByte register_addr)
{
	UByte read_data;

	SendAccess1Start();

	ACCESS1_IN_OUT_REG = (device_addr << 1);		// RTC slave address w/nWRITE
	usec_pause(100);

	ACCESS1_IN_OUT_REG = register_addr;				// RTC register address
	usec_pause(100);

	SendAccess1ReStart();

	ACCESS1_IN_OUT_REG = (device_addr << 1) + 1;	// RTC slave address w/READ
	usec_pause(100);

	ACCESS1_CLEAR_INT_REG = 1;

	ACCESS1_CTRL_REG |= ACKn;						// transmit No ACK on access bus
	usec_pause(100);

	read_data = ACCESS1_IN_OUT_REG;

//	char* ptr;
//	ptr = StringPrint(StatusString, "** read_data (addr ");
//	ptr = StrPrintDecByte(ptr, register_addr);
//	ptr = StringPrint(ptr, ") = 0x");
//	ptr = StrPrintHexByte(ptr, read_data);
//	ptr = StringPrint(ptr, " **");
//	PrintStatus(0, StatusString);

	SendAccess1Stop();

	return read_data;
}
