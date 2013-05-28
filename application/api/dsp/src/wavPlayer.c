#include "../../../../include/common/include/bitsdef.h"
#include "../../../../include/common/include/rtxdef.h"
#include "../../include/common/flash_sound.h"
#include "../../include/DSPSignalHandler.h"
#include "../../../../include/os/include/mailprim.h"
#include "../../../../include/machlinterface/include/application_mac_tunnel.h"

static int sound_index = 2;
static int sound_length = 2;
static UByte requestPlaying = 0;
static UByte playing = 0;
static char * sound_src = 0;
static unsigned char silent[4] = {0x00,0x02,0xff,0xff};

extern void PutInterruptMail(uint8 Element);
extern void DeliverInterruptMail(uint8 TaskId);
extern void sendAppToMac(UByte key, UByte action);
extern void sendMacToAPP(UByte key, UByte action);
extern void enableAudio();

extern BYTE CONTROLLERTASK;
extern UByte dspStarted;
extern WORD audioplayback;

static __data24 uint16* dsp_int_reg = (uint16*) DSP_INT_REG_ADDR;

static char * getWavPointer(UByte sound_to_play)
{
    switch (sound_to_play)
    {
        case sound_num_0:
            return  (char *)wav_num_0;
        case sound_num_1:
            return  (char *)wav_num_1;
        case sound_num_2:
            return  (char *)wav_num_2;
        case sound_num_3:
            return  (char *)wav_num_3;
        case sound_num_4:
            return  (char *)wav_num_4;
        case sound_num_5:
            return  (char *)wav_num_5;
        case sound_num_6:
            return  (char *)wav_num_6;
        case sound_num_7:
            return  (char *)wav_num_7;
        case sound_num_8:
            return  (char *)wav_num_8;
        case sound_num_9:
            return  (char *)wav_num_9;
        default:
            return  (char *)silent;

    };
}

void handle_playsound(UByte sound_to_play)
{
    if (playing == 0)
    {
        sound_src = getWavPointer(sound_to_play);
        requestPlaying = 1;
        sound_index = 2;
        sound_length = (sound_src[0]<<8)+sound_src[1];
        sendMacToAPP(0xfe,00);
    }
    else
    {
        sendMacToAPP(0xfe,01);
    }
}

void wavPlayer(void)
{
    #ifndef GCCCOMPILE
    if (requestPlaying)
    {
        playing = 1;
        requestPlaying = 0;
    }
    else if (playing)
    {
        if (sound_index<sound_length)
        {
            /* UByte* tmp = (UByte* )DSP_PARAM(audioplayback);*/
            /* tmp[0] = (sound_src[sound_index]<<8)+sound_src[sound_index];*/
            /* sound_index++;*/
        }
        else
        {
            playing = 0;
            PutInterruptMail(MAC_APPLICATION_TUNNEL);
            PutInterruptMail(0xfe);
            PutInterruptMail(2);
            DeliverInterruptMail(CONTROLLERTASK);
        }
    }

    #endif
    *dsp_int_reg = 0x01;
    CLEAR_PENDING_DSP_INTERRUPT;
}

void playsound(UByte sound)
{
    #ifndef GCCCOMPILE
    sendAppToMac(APP_TO_MAC_PLAY_SOUND,sound);
    #endif
}

void common_playsound(UByte sound_to_play)
{
    if (!dspStarted)
    {
        enableAudio();
    }
    playsound(sound_to_play);
}

