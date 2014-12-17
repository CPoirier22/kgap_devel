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
 * $History:: hex_to_decimal_sn_conv.c										  $	*
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
#include "../../../../../../include/common/include/map_480_gcc.h"
#include "../../../../../api/include/pp/pp_msf_functions.h"
#include "../../../../../api/include/pp/pp_msf_callback.h"
#include "../../../../../../include/hlkgap/common/include/aformat.h"

#include "wentworth_pp.h"
#include "wentworth_fp.h"
#include "fppp_common.h"

void ConvertIpeiToSN(PPIDType user, char SerialNumber[17], IPEIType Hex_SN)
{
	unsigned long first_part = 0;
	unsigned long second_part = 0;

	// 0x xx xm mm mm    where x is the vendor number and m is the serial number

	first_part += (((unsigned long)Hex_SN[0] & 0x0F) << 12);	// 0000 xxxx
	first_part += (((unsigned long)Hex_SN[1] & 0xFF) << 4);		// xxxx xxxx
	first_part += (((unsigned long)Hex_SN[2] & 0xF0) >> 4);		// xxxx 0000

	second_part += (((unsigned long)Hex_SN[2] & 0x0F) << 16);	// 0000 xxxx
	second_part += (((unsigned long)Hex_SN[3] & 0xFF) << 8);	// xxxx xxxx
	second_part += (((unsigned long)Hex_SN[4] & 0xFF));			// xxxx xxxx

	unsigned long num = first_part;
	unsigned long test, power = 0;
	int count, i;

	for (i = 0; i < 4; i++)
	{
		switch(i)
		{
			case 0: power = 10000; break;
			case 1: power = 1000; break;
			case 2: power = 100; break;
			case 3: power = 10; break;
		}

		test = 0;
		count = 0;

		while (num >= test) {
			if ((test + power) > num)
			{
				num -= test;
				test += power;
			}
			else
			{
				test += power;
				count++;
			}
		}

		SerialNumber[i] = (unsigned char)(count + 48);
	}

	SerialNumber[4] = (unsigned char)(num + 48);

	SerialNumber[5] = ' ';

	num = second_part;

	for (i = 6; i < 12; i++)
	{
		switch(i)
		{
			case 6:  power = 1000000; break;
			case 7:  power = 100000; break;
			case 8:  power = 10000; break;
			case 9:  power = 1000; break;
			case 10: power = 100; break;
			case 11: power = 10; break;
		}
		test = 0;
		count = 0;
		while (num >= test) {
			if ((test + power) > num)
			{
				num -= test;
				test += power;
			}
			else
			{
				test += power;
				count++;
			}
		}
		SerialNumber[i] = (unsigned char)(count + 48);
	}
	SerialNumber[12] = (unsigned char)(num + 48);

	SerialNumber[13] = ' ';

	if (getRunMode()) // FP
	{
		if ((base_station).ListenOnly[user] == 0x01)
		{
			SerialNumber[14] = 'L';
			SerialNumber[15] = 'O';
		}
		else
		{
			SerialNumber[14] = ' ';
			SerialNumber[15] = ' ';
		}
	}
	else
	{
		if (headset.SystemMode == LISTEN_ONLY_MODE)
		{
			SerialNumber[14] = 'L';
			SerialNumber[15] = 'O';
		}
		else
		{
			SerialNumber[14] = ' ';
			SerialNumber[15] = ' ';
		}
	}

	SerialNumber[16] = '\0';

	if (!(getRunMode())) // PP
	{
		char * tmp = StatusString;
		tmp = StringPrint(tmp, "***** Headset SN = ");
		tmp = StringPrint(tmp, SerialNumber);
		tmp = StringPrint(tmp, " *****");
		PrintStatus(0, StatusString);
	}
}

void ConvertHexSNtoAriSN(IPEIType Hex_SN, char SerialNumber[11])
{
	char * ptr;
	int i;
	BOOLEAN AfterFirstDigit = FALSE;
	unsigned long long int combined_hex_SN = 0, count, test, power = 0;

	combined_hex_SN += (unsigned long long int)Hex_SN[4];
	combined_hex_SN += (unsigned long long int)Hex_SN[3] << 8;
	combined_hex_SN += (unsigned long long int)Hex_SN[2] << 16;
	combined_hex_SN += (unsigned long long int)Hex_SN[1] << 24;
	if (Hex_SN[0] == 0x01)
		combined_hex_SN += (unsigned long long int)0x01 << 32;

	for (i = 0; i < 9; i++)
	{
		switch(i)
		{
		    case 0: power = 1000000000; break;
		    case 1: power = 100000000; break;
		    case 2: power = 10000000; break;
		    case 3: power = 1000000; break;
		    case 4: power = 100000; break;
			case 5: power = 10000; break;
			case 6: power = 1000; break;
			case 7: power = 100; break;
			case 8: power = 10; break;
		}

		test = 0;
		count = 0;

		while (combined_hex_SN >= test)
		{
			if ((test + power) > combined_hex_SN)
			{
				combined_hex_SN -= test;
				test += power;
			}
			else
			{
				test += power;
				count++;
			}
		}

		switch (count)
		{
			case 1: SerialNumber[i] = '1'; AfterFirstDigit = TRUE; break;
			case 2: SerialNumber[i] = '2'; AfterFirstDigit = TRUE; break;
			case 3: SerialNumber[i] = '3'; AfterFirstDigit = TRUE; break;
			case 4: SerialNumber[i] = '4'; AfterFirstDigit = TRUE; break;
			case 5: SerialNumber[i] = '5'; AfterFirstDigit = TRUE; break;
			case 6: SerialNumber[i] = '6'; AfterFirstDigit = TRUE; break;
			case 7: SerialNumber[i] = '7'; AfterFirstDigit = TRUE; break;
			case 8: SerialNumber[i] = '8'; AfterFirstDigit = TRUE; break;
			case 9: SerialNumber[i] = '9'; AfterFirstDigit = TRUE; break;
		}

		if (count == 0 && AfterFirstDigit)
		{
			SerialNumber[i] = '0';
		}
	}

	switch (combined_hex_SN)
	{
		case 0: SerialNumber[9] = '0'; break;
		case 1: SerialNumber[9] = '1'; break;
		case 2: SerialNumber[9] = '2'; break;
		case 3: SerialNumber[9] = '3'; break;
		case 4: SerialNumber[9] = '4'; break;
		case 5: SerialNumber[9] = '5'; break;
		case 6: SerialNumber[9] = '6'; break;
		case 7: SerialNumber[9] = '7'; break;
		case 8: SerialNumber[9] = '8'; break;
		case 9: SerialNumber[9] = '9'; break;
	}

	SerialNumber[10] = '\0';

	ptr = StringPrint(StatusString, "***** BaseStation ARI = ");
	ptr = StringPrint(ptr, SerialNumber);
	ptr = StringPrint(ptr, " *****");
	PrintStatus(0, StatusString);
}
