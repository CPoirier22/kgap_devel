#include "../../../include/common/include/bitsdef.h"
#include "../../api/include/common/common_structures.h"
#include "../../api/include/common/common_hardware_functions.h"
#include "../../api/include/pp/pp_subscription_functions.h"
#include "../../api/include/pp/pp_voice_functions.h"
#include "../../api/include/fp/fp_voice_functions.h"
#include "../../api/include/pp/pp_buffer_functions.h"
#include "../../api/include/fp/fp_buffer_functions.h"
#include "../../api/include/fp/fp_subscription_functions.h"
#include "../../api/include/fp/fp_msf_functions.h"
#include "../../api/include/fp/fp_module2module_functions.h"
#include "../../api/include/pp/pp_module2module_functions.h"
#include "../include/pp/pp_msf_functions.h"
#include "../../kt4585/hlkgap/app/src/wentworth/fppp_common.h"

/**
 * Definition of Version string for the version RPC
 */
#ifdef __IAR_SYSTEMS_ICC__
#define COMPILER_VER "IAR compiler "__VER__
#elif defined ( __GNUC__)
#define COMPILER_VER "GNUC "__VERSION__
#else
#define COMPILER_VER "Unknown compiler "
#endif
#define TIME " Compiled "__DATE__" "__TIME__

#define VERSION "[" FW_REV_STR COMPILER_VER TIME"]"

extern void sendEEDataCfm(BYTE NoOfBytes, BYTE* data);
extern void pp_connect_speech_buffer(void);
extern void fp_connect_speech_buffer(PMIDType pmid);
extern void CopyToUartTxBuffer(UByte * buffer, unsigned int length);

#define RETURN_CALLBACK			0x00
typedef enum
{
    search_for_bases = 0x00,
    stop_Search = 0x01,
    login_to_base = 0x02,
    get_ari_result = 0x03,
    delete_sub = 0x04,
    subscribe = 0x05,
    remove_subscription = 0x6,
    pp_call_user = 0x07,
    start_timer = 0x08,
    stop_timer = 0x09,
    fp_setup_format2 = 0x0a,
    fp_setup_format1 = 0x0b,
    pp_outg_msg = 0x0c,
    pp_send_ppstatus = 0x0d,
    fp_send_ppstatus_req = 0x0e,
    fp_call_user = 0x0f,
    pp_onhook = 0x10,
    pp_offhook = 0x11,
    fp_update_display = 0x12,
    pp_connect_cfm = 0x13,
    pp_setup_ind = 0x14,
    pp_send_key = 0x15,
    pp_send_release = 0x16,
    fp_release_req = 0x17,
    fp_disp_req = 0x18,
    fp_connect_res = 0x19,
    eeprom_write_req = 0x1a,
    eeprom_read_req = 0x1b,
    setup_spec1 = 0x1c,
    setup_spec2 = 0x1d,
    setup_spec3 = 0x1e,
    fp_lookup_ipei = 0x1f,
    fp_lookup_ppid = 0x20,
    pp_read_speech_buffer = 0x21,
    pp_write_speech_buffer = 0x22,
    pp_voice_send_key = 0x23,
    pp_con_speech_buffer = 0x24,
    fp_con_speech_buffer = 0x25,
    fp_read_speech_buffer = 0x26,
    fp_write_speech_buffer = 0x27,
    fp_voice_disconnect = 0x28,
    pp_send_m2m = 0x29,
    fp_send_m2m = 0x2a,
    gpio_set_out = 0x2b,
    gpio_reg_in = 0x2c,
    gpio_dereg_in = 0x2d,
    gpio_reg_out = 0x2e,
    version = 0x2f,
    temperature = 0x30,
    mutecopybuffer = 0x31,
    mutedspcopybuffer = 0x32,
    WT_debug = 0x33
} handle_gen_api_event_type;

static PPIDType getPPID(BYTE* data, BYTE start)
{
    PPIDType user = 0;
    user = user | (data[start] << 8);
    user = user | (data[start + 1]);
    if (user > MAX_PPID)
    {
        PrintStatus(0, "\n\nUnexpected large PPID\n\n");
    }
    return user;

}

static void reply(BYTE id, BYTE result)
{
    if (id > 0)
    {
        BYTE msg[4];
        msg[0] = RETURN_CALLBACK;
        msg[1] = 0;
        msg[2] = id;
        msg[3] = result;
        sendEEDataCfm(4, msg);
    }
}
static void replyData(BYTE id, BYTE length, BYTE* result)
{
    if (id > 0)
    {
        BYTE *msg;
        int i = 0;
        msg = mem_malloc(3 + length, 42);
        msg[0] = RETURN_CALLBACK;
        msg[1] = length;
        msg[2] = id;
        for (i = 0; i < length; i++)
        {
            msg[3 + i] = result[i];
        }
        sendEEDataCfm(3 + length, msg);
        mem_free(msg);
    }
}
extern void MuteDSPCopyBuffer(unsigned char mute);

void handle_gen_api_event(BYTE func_id, BYTE length, UByte* data)
{
    char* TOO_SHORT = "Mail too short";
    PrintStatus(0, "handle_gen_api_event");
    switch (func_id)
    {
        case search_for_bases:
        {
            UByte result;

            if (length < 1)
            {
                PrintStatus(0, TOO_SHORT);
                return;
            }

            result = pp_subscription_searchForBases();
            reply(data[0], result);
        }
        break;
        case stop_Search:
        {
            pp_subscription_stopSearch();
            break;
        }
        case login_to_base:
        {
            UByte result;
            if (length < 2)
            {
                PrintStatus(0, TOO_SHORT);
                return;
            }
            result = pp_subscription_loginToBase(data[1]);
            PrintStatus(0, "LoginToBase");
            reply(data[0], result);

            break;
        }
        case get_ari_result:
        {
            if (length < 2)
            {
                PrintStatus(0, TOO_SHORT);
                return;
            }
            pp_subscription_getAriResult(data[1]);
            break;
        }
        case delete_sub:
        {
            if (length < 2)
            {
                PrintStatus(0, TOO_SHORT);
                return;
            }
            pp_subscription_delete(data[1]);
            break;
        }
        case subscribe:
        {
            unsigned long l = 0;
            unsigned long d;
            UByte result;
            char* tmp;
            if (length < 24)
            {
                PrintStatus(0, TOO_SHORT);
                return;
            }

            d = data[20];
            l = l | (d << 24);
            d = data[21];
            l = l | (d << 16);
            d = data[22];
            l = l | (d << 8);
            l = l | (data[23]);
            tmp = StatusString;
            tmp = StringPrint(tmp, "Attempting to subscribe at ");
            tmp = StringPrint(tmp, (char*) &data[2]);
            PrintStatus(0, StatusString);

            result = pp_subscription_subscribe(data[1], (data[2] == 0) ? 0 : ((char*) &data[2]), (char*) &data[15], l);

            reply(data[0], result);
            break;
        }
        case remove_subscription:
        {
            UByte result;
            if (length < 3)
            {
                PrintStatus(0, TOO_SHORT);
                return;
            }

            result = fp_subscription_removeSubscription(getPPID(data, 1));
            reply(data[0], result);

            break;
        }
        case pp_call_user:
        {
            if (length < 2)
            {
                PrintStatus(0, TOO_SHORT);
                return;
            }
            PrintStatus(0, "pp_call_user");
            PrintStatus(0, (char*) &data[1]);
            pp_voice_call_user((char*) &data[1]);
        }
        break;
        case start_timer:
        {
            int time = 0;
            UByte result;
            PPIDType user;
            if (length < 7)
            {
                PrintStatus(0, TOO_SHORT);
                return;
            }
            PrintStatus(0, "Starting timer");
            user = getPPID(data, 1);
            time = time | data[4];
            time = time | (data[5] << 8);
            result = general_startTimer(user, data[3], &data[7], data[6], time);

            reply(data[0], result);
            break;
        }
        case stop_timer:
        {
            UByte result;
            PPIDType user;
            if (length < 3)
            {
                PrintStatus(0, TOO_SHORT);
                return;
            }
            user = getPPID(data, 1);

            result = general_stopTimer(user);
            PrintStatus(0, "Stopping timer");
            reply(data[0], result);
            break;
        }
        case pp_outg_msg:
        {
            int displayStart;
            int callBackStart;
            alertConstructiontType alert;
            int fixed_size = 7;
            if (length < 7)
            {
                PrintStatus(0, TOO_SHORT);
                return;
            }
            PrintStatus(0, "Sending outg msg");
            alert.alertPattern = (alertPatternType) data[4];
            alert.alertTimeout = data[5];
            alert.alertTone = (alertToneType) data[6];

            displayStart = fixed_size + strlen((char*) &data[fixed_size]) + 1;
            callBackStart = displayStart + strlen((char*) &data[displayStart]) + 1;
            PrintStatus(0, (char*) &data[fixed_size]);
            PrintStatus(0, (char*) &data[displayStart]);
            PrintStatus(0, (char*) &data[callBackStart]);
            pp_msf_send_outg_message_ind(data[1], data[2], alert, data[3], (char*) &data[fixed_size], (char*) &data[displayStart], (char*) &data[callBackStart]);
            break;
        }
        case fp_setup_format1:
        {
            UByte result;
            PPIDType user;
            PPIDType id;
            if (length < 7)
            {
                PrintStatus(0, TOO_SHORT);
                return;
            }
            user = getPPID(data, 1);
            id = getPPID(data, 4);
            PrintStatus(0, "fp_setup_format1");
            result = msf_setupreq_format1(user, data[3], (char*) &data[6], id);
            reply(data[0], result);
            break;
        }
        case fp_setup_format2:
        {
            alertConstructiontType alert;
            dateAndTimeType date;
            UByte result;
            PPIDType user;
            PPIDType id;
            if (length < 18)
            {
                PrintStatus(0, TOO_SHORT);
                return;
            }

            user = getPPID(data, 1);
            id = getPPID(data, 5);

            alert.alertPattern = (alertPatternType) data[8];
            alert.alertTimeout = data[9];
            alert.alertTone = (alertToneType) data[10];

            date.length = data[11];
            date.day = data[12];
            date.hour = data[13];
            date.month = data[14];
            date.second = data[15];
            date.year = data[16];

            result = msf_setupreq_format2(user, data[3], (char*) &data[17], id, data[4], data[5], alert, data[7], date);
            reply(data[0], result);

            break;
        }
        case pp_send_ppstatus:
        {
            UByte result;
            if (length < 3)
            {
                PrintStatus(0, TOO_SHORT);
                return;
            }

            result = pp_msf_send_ppstatus_ind(data[1], &data[3], data[2]);
            reply(data[0], result);
            break;
        }
        case fp_send_ppstatus_req:
        {
            UByte result;
            if (length < 5)
            {
                PrintStatus(0, TOO_SHORT);
                return;
            }

            result = msf_send_ppstatusReq(getPPID(data, 1), data[3], &data[5], data[4]);
            reply(data[0], result);

            break;
        }
        case fp_call_user:
        {
            UByte result;
            if (length < 5)
            {
                PrintStatus(0, TOO_SHORT);
                return;
            }

            result = voice_callUser(getPPID(data, 1), getPPID(data, 3));
            reply(data[0], result);

            break;
        }
        case pp_offhook:
        {
            UByte result;
            if (length < 1)
            {
                PrintStatus(0, TOO_SHORT);
                return;
            }
            result = pp_voice_offhook();
            reply(data[0], result);

            break;
        }
        case pp_onhook:
        {
            UByte result;
            if (length < 1)
            {
                PrintStatus(0, TOO_SHORT);
                return;
            }
            PrintStatus(0, "pp_onhook");

            result = pp_voice_onhook();
            reply(data[0], result);

            break;
        }
        case fp_update_display:
        {
            UByte result;
            if (length < 4)
            {
                PrintStatus(0, TOO_SHORT);
                return;
            }

            PrintStatus(0, "fp_update_display");
            result = voice_updateDisplay(getPPID(data, 1), (char*) &data[3]);
            reply(data[0], result);

            break;
        }
        case pp_connect_cfm:
        {
            UByte result;
            if (length < 1)
            {
                PrintStatus(0, TOO_SHORT);
                return;
            }

            result = pp_msf_send_connect_cfm();
            reply(data[0], result);

            break;
        }
        case pp_setup_ind:
        {
            UByte result;
            if (length < 2)
            {
                PrintStatus(0, TOO_SHORT);
                return;
            }
            PrintStatus(0, "pp_setup_ind");
            PrintStatus(0, (char*) data);
            result = pp_msf_send_setup_ind((char*) &data[1]);
            reply(data[0], result);

            break;
        }
        case pp_send_key:
        {
            UByte result;
            if (length < 2)
            {
                PrintStatus(0, TOO_SHORT);
                return;
            }

            result = pp_msf_send_keypad_ind(data[1]);
            reply(data[0], result);

            break;
        }
        case pp_send_release:
        {
            UByte result;
            if (length < 2)
            {
                PrintStatus(0, TOO_SHORT);
                return;
            }

            result = pp_msf_send_release_ind(data[1]);
            reply(data[0], result);

            break;
        }
        case fp_release_req:
        {
            UByte result;
            if (length < 4)
            {
                PrintStatus(0, TOO_SHORT);
                return;
            }

            result = msf_send_ReleaseReq(getPPID(data, 1), data[3]);
            reply(data[0], result);

            break;
        }
        case fp_disp_req:
        {
            BYTE callbackstart;
            if (length < 5)
            {
                PrintStatus(0, TOO_SHORT);
                return;
            }

            callbackstart = 4 + strlen((char*) &data[4]) + 1;
            PrintStatus(0, (char*) &data[4]);
            msf_send_DispReq((char*) &data[4], (char*) &data[callbackstart], getPPID(data, 1), data[3]);
            break;
        }
        case fp_connect_res:
        {
            UByte result;
            if (length < 3)
            {
                PrintStatus(0, TOO_SHORT);
                return;
            }

            result = msf_send_CONNECT_res(getPPID(data, 1));
            reply(data[0], result);

            break;
        }
        case eeprom_write_req:
        {
            UByte result;
            WORD addr = 0;
            if (length < 6)
            {
                PrintStatus(0, TOO_SHORT);
                return;
            }

            addr = addr | (data[1] << 8);
            addr = addr | data[2];

            result = general_eeprom_write_req(addr, &data[6], data[5], getPPID(data, 3));
            reply(data[0], result);

            break;
        }
        case eeprom_read_req:
        {
            UByte result;
            WORD addr = 0;
            if (length < 6)
            {
                PrintStatus(0, TOO_SHORT);
                return;
            }

            addr = addr | (data[1] << 8);
            addr = addr | data[2];

            result = general_eeprom_read_req(addr, data[5], getPPID(data, 3));
            reply(data[0], result);

            break;
        }
        case setup_spec1:
        {
            UByte result;
            if (length < 7)
            {
                PrintStatus(0, TOO_SHORT);
                return;
            }

            result = msf_help_generateSetupSpec1(data[1], data[2], data[3], data[4], data[5], (alertTypes) data[6]);
            reply(data[0], result);

            break;
        }
        case setup_spec2:
        {
            UByte result;
            if (length < 4)
            {
                PrintStatus(0, TOO_SHORT);
                return;
            }

            result = msf_help_generateSetupSpec2(data[1], data[2], data[3]);
            reply(data[0], result);

            break;
        }
        case setup_spec3:
        {
            UByte result;
            if (length < 6)
            {
                PrintStatus(0, TOO_SHORT);
                return;
            }

            result = msf_help_generateSetupSpec3((functionType) data[1], data[2], data[3], data[4], data[5]);
            reply(data[0], result);

            break;
        }
        case fp_lookup_ipei:
        {
            PPIDType result;
            BYTE msg[2];
            if (length < 1 + IPEISize)
            {
                PrintStatus(0, TOO_SHORT);
                return;
            }

            result = fp_subscription_lookupUserFromIpei(&data[1]);
            PrintStatus(0, "User looked up");
            msg[0] = ((result & 0xff00) >> 8);
            msg[1] = (result & 0x00ff);
            replyData(data[0], 2, msg);
            break;
        }
        case fp_lookup_ppid:
        {
            IPEIType result;
            if (length < 3)
            {
                PrintStatus(0, TOO_SHORT);
                return;
            }

            if (fp_subscription_lookupUserFromPPID(getPPID(data, 1), result))
            {
                replyData(data[0], IPEISize, result);
            }
            else
            {
                replyData(data[0], 0, 0);

            }
            break;

        }
        case pp_write_speech_buffer:
        {
            int i = 0;
            UByte* buffer;
            if (length < 2)
            {
                PrintStatus(0, TOO_SHORT);
                return;
            }

            PrintStatus(0, "pp_write_speech_buffer");
            if (data[1] > 40)
            {
                PrintStatus(0, "Too long buffer");
                break;
            }

            buffer = pp_get_speech_buffer(0);
            for (i = 0; i < data[1]; i++)
            {
                (buffer)[i] = data[2 + i];
                StatusString[i] = data[2 + i];
            }

            StatusString[data[1] + 2] = 0;
            PrintStatus(0, StatusString);
            break;
        }
        case pp_read_speech_buffer:
        {
            UByte* buffer;
            if (length < 1)
            {
                PrintStatus(0, TOO_SHORT);
                return;
            }

            buffer = pp_get_speech_buffer(1);
            PrintStatus(0, "pp_read_speech_buffer");
            replyData(data[0], 40, buffer);

            break;
        }
        case pp_voice_send_key:
        {
            UByte result;
            if (length < 2)
            {
                PrintStatus(0, TOO_SHORT);
                return;
            }

            result = pp_voice_sendKey(data[1]);
            reply(data[0], result);

            break;
        }
        case pp_con_speech_buffer:
        {

            pp_connect_speech_buffer();
            break;
        }
        case fp_con_speech_buffer:
        {
            PMIDType pmida;
            if (length < 3)
            {
                PrintStatus(0, TOO_SHORT);
                return;
            }

            PPID2PMID(&pmida, getPPID(data, 1));

            fp_connect_speech_buffer(pmida);
            break;
        }
        case fp_write_speech_buffer:
        {
            int i = 0;
            PMIDType pmida;
            UByte * buffer;
            if (length < 4)
            {
                PrintStatus(0, TOO_SHORT);
                return;
            }

            PPID2PMID(&pmida, getPPID(data, 1));
            PrintStatus(0, "fp_write_speech_buffer");
            if (data[3] > 40)
            {
                PrintStatus(0, "Too long buffer");
                break;
            }
            buffer = fp_get_speech_buffer(pmida, 0);
            for (i = 0; i < data[3]; i++)
            {
                (buffer)[i] = data[4 + i];
                StatusString[i] = data[4 + i];
            }
            StatusString[data[3] + 4] = 0;
            PrintStatus(0, StatusString);

            break;
        }
        case fp_read_speech_buffer:
        {
            UByte * buffer;
            PMIDType pmida;
            char * tmp;
            PPIDType ppid;
            if (length < 3)
            {
                PrintStatus(0, TOO_SHORT);
                return;
            }

            ppid = getPPID(data, 1);
            PPID2PMID(&pmida, ppid);

            tmp = StringPrint(StatusString, "fp_read_buffer: ");
            tmp = StrPrintHexAddr(tmp, ppid);
            PrintStatus(0, StatusString);

            PrintStatus(0, "fp_read_speech_buffer");
            buffer = fp_get_speech_buffer(pmida, 1);
            replyData(data[0], 40, buffer);

            break;
        }
        case fp_voice_disconnect:
        {
            UByte result;
            if (length < 3)
            {
                PrintStatus(0, TOO_SHORT);
                return;
            }

            PrintStatus(0, "fp_voice_disconnect");
            result = voice_disConnectUser(getPPID(data, 1));
            reply(data[0], result);
            break;
        }
        case pp_send_m2m:
        {
            UByte result;
            module2moduleData m2mdata;
            if (length < 4)
            {
                PrintStatus(0, TOO_SHORT);
                return;
            }

            PrintStatus(0, "pp_send_module2module");
            m2mdata[0] = data[1];
            m2mdata[1] = data[2];
            m2mdata[2] = data[3];
            result = pp_send_module2module(m2mdata);
            reply(data[0], result);
            break;
        }

        case fp_send_m2m:
        {
            UByte result;
            module2moduleData m2mdata;
            if (length < 6)
            {
                PrintStatus(0, TOO_SHORT);
                return;
            }

            PrintStatus(0, "fp_send_module2module");
            m2mdata[0] = data[3];
            m2mdata[1] = data[4];
            m2mdata[2] = data[5];
            result = fp_send_module2module(getPPID(data, 1), m2mdata);
            reply(data[0], result);
            break;
        }
        case gpio_set_out:
        {
            UByte result;
            if (length < 3)
            {
                PrintStatus(0, TOO_SHORT);
                return;
            }

            PrintStatus(0, "common_gpio_set_output_port");
            result = common_gpio_set_output_port(data[1], data[2]);
            reply(data[0], result);
            break;
        }
        case gpio_reg_in:
        {
            UByte result;
            if (length < 3)
            {
                PrintStatus(0, TOO_SHORT);
                return;
            }

            PrintStatus(0, "common_gpio_register_input_port");
            result = common_gpio_register_input_port(data[1], data[2]);
            reply(data[0], result);
            break;

        }
        case gpio_reg_out:
        {
            UByte result;
            if (length < 2)
            {
                PrintStatus(0, TOO_SHORT);
                return;
            }

            PrintStatus(0, "common_gpio_register_output_port");
            result = common_gpio_register_output_port(data[1]);
            reply(data[0], result);
            break;

        }
        case gpio_dereg_in:
        {
            UByte result;
            if (length < 2)
            {
                PrintStatus(0, TOO_SHORT);
                return;
            }

            PrintStatus(0, "common_gpio_deregister_input_port");
            result = common_gpio_deregister_input_port(data[1]);
            reply(data[0], result);
            break;

        }
        case version:
        {
            PrintStatus(0, VERSION);
            replyData(data[0], strlen(VERSION), (BYTE*) VERSION);

            break;
        }
        case temperature:
        {
            UByte result;
            if (length < 2)
            {
                PrintStatus(0, TOO_SHORT);
                return;
            }
            result = common_read_temperature(data[1]);
            reply(data[0], result);
            break;
        }
        case mutecopybuffer :
        {
        	PrintStatus(0, "MuteCopyBuffer");
        	MuteDSPCopyBuffer(data[1]);
        	reply(data[0], 1);
        	break;
        }
        case mutedspcopybuffer:
        {
//        	extern unsigned int hm_mutecontroller;
        	PrintStatus(0, "mutedspcopybuffer");
//        	hm_mutecontroller = data[1];
        	reply(data[0], 1);
        	break;
        }
        case WT_debug:
        {
        	char *ptr;
        	if (*((volatile unsigned char*)0xFFFBFD) == 0x11)
            	ptr = StringPrint(StatusString, "****      MODULE = ES6      *****\n\r");
        	else if (*((volatile unsigned char*)0xFFFBFD) == 0x12)
            	ptr = StringPrint(StatusString, "****      MODULE = ES7      *****\n\r");
        	else if (*((volatile unsigned char*)0xFFFBFD) == 0x13)
            	ptr = StringPrint(StatusString, "****      MODULE = ES8      *****\n\r");
        	else
            	ptr = StringPrint(StatusString, "****      MODULE VERSION IS UNKNOWN      *****\n\r");
            replyData(data[0], strlen(StatusString), (BYTE*) StatusString);
        	break;
        }
        default:
        {
            PrintStatus(0, "Unknown event");
            break;
        }
    }

}
