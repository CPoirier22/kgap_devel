#include "../../../include/common/include/print_status.h"
#include "../../../include/common/include/bitsdef.h"

extern void SendPPStatusInd(BYTE statusType,BYTE data[], BYTE data_length);
extern void serprintf232(char *msg);
extern void sendTestResponse(char * bytes, char length);

extern void enter_binary_mode();
extern void leave_binary_mode();

void sendMsfAtCmd(char cmd)
{
	BYTE data[1];
	data[0] = cmd;
	SendPPStatusInd(0x12,data,1);
}

typedef enum
{
	AT_IDLE,
	AT_DIAL_REQ,
	AT_BINARY,
	AT_BINARY_TERMINATED
} AT_STATE;

AT_STATE state = AT_IDLE;
BYTE AT_echo = 0;

void at_echo(char received_char){
    if(AT_echo){
        char echo[2];
        echo[0] = received_char;
        echo[1] = '\0';
        serprintf232(echo);
    }
}

void at_data_from_msf(char command,UByte * data, UByte length)
{
	_sprintf_(StatusString,"at handler.msf: %x",command);
	PrintStatus(0,StatusString);
	switch (command)
	{
		case 'a':
		case 'A':/*answer*/
		{
			if (state == AT_DIAL_REQ)
			{
				state = AT_BINARY;
				enter_binary_mode();
				serprintf232("\r\nCONNECT\r\n");
			}
		}break;

		case 'd':
		case 'D':/*dial*/
		{
			if (state == AT_IDLE)
			{
				serprintf232("\r\nRING\r\n");
				state = AT_DIAL_REQ;
			}
		}break;

		case 'h':
		case 'H':/*hangup*/
		{
			if (state == AT_BINARY)
			{
			    sendMsfAtCmd('H');
				leave_binary_mode();
				state = AT_IDLE;
			}
		}break;

		case 'b':
		case 'B':/*binary*/
		{
			if (state == AT_BINARY)
			{
				sendTestResponse((char*)data,length);
			}
		}break;
	}
}

void at_data_from_rs232(char command,UByte * data, UByte length)
{
	_sprintf_(StatusString,"at handler.232: %x",command);
	PrintStatus(0,StatusString);

	switch (command)
	{
		case 'A':/*answer*/
		{
			if (state == AT_DIAL_REQ)
			{
				state = AT_BINARY;
				sendMsfAtCmd('a');
				enter_binary_mode();
				serprintf232("\r\nOK\r\n");
			}
		}break;

		case 'd':
		case 'D':/*dial*/
		{
			if (state == AT_IDLE)
			{
			    sendMsfAtCmd('d');
				state = AT_DIAL_REQ;
			}
		}break;

		case 'h':
		case 'H':/*hangup*/
		{
			if (state == AT_BINARY_TERMINATED)
			{
				state = AT_IDLE;
				sendMsfAtCmd('h');
				serprintf232("\r\nOK\r\n");
			}
		}break;

		case 'b':
		case 'B':/*binary*/
		{
			if (state == AT_BINARY)
			{
				int cnt;
				char result[255];
				result[0] = 'b';

				for (cnt=0;cnt<length;cnt++)
					result[cnt+1] = data[cnt];

				SendPPStatusInd(0x12,(BYTE*)result,length+1);
			}
		}break;

		case 's':/*status*/
		{
			_sprintf_(StatusString,"State: %x",state);
			serprintf232(StatusString);
		}break;

		case '+':/*leave binary*/
		{
			if (state == AT_BINARY)
			{
				state = AT_BINARY_TERMINATED;
				serprintf232("\r\nOK\r\n");
			}
		}break;

	    case 'O':/*Open binary data again*/
        {
            if (state == AT_BINARY_TERMINATED) {
                state = AT_BINARY;
                enter_binary_mode();
            }
        }
        break;

        case 'E':/*Echo*/
        {
            AT_echo = *data - 0x30; /*Convert from ascii*/
            serprintf232("\r\nOK\r\n");
        }
        break;
	}
}
