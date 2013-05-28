#include "../include/kt4585app_interface.h"
#include "../include/kt4585app_pp_app.h"
#include "../../../include/machlinterface/include/maclink.h"
#include "../../../include/machlinterface/include/application_mac_tunnel.h"
#include "../../../include/os/include/maildef.h"
#include "../../../include/os/include/mailprim.h"
#include "../../../include/mac/eeprom/include/fnvm.h"
#include "../mac/include/hsaudio.h"
#include "../mac/include/hwinterface.h"

extern MACLink macLink;
extern PP_EepromInRamType PP_EepromInRam;
extern void activateVoicePlayback();
extern void (*peltor_pp_statefunction)(SignalType * signal);
extern void PrintStatus(UByte StatusMessageLevel, char *msg);
extern void RestartHandset(void);

extern void conf_ResetWatchdogTimer(void);
extern void BusyWait1000(void);

void refreshVox(void)
{
}
void refreshVolume(void)
{
}
void refreshMic(void)
{
}

UByte activeInConf(void)
{
    return 1;
}

void vox_cmd(UByte action)
{
}

void switch_runmode(UByte newmode)
{
}

void signal_strength_controller(UByte q, UByte rssi, UByte rssi_ucomp)
{
}

void vox_handler(WORD powerlevel)
{
}

void sendAppToMac(UByte key, UByte action)
{
    KeyIndType k;
    k.Primitive = MAC_APPLICATION_TUNNEL;
    k.Key = key;
    k.Key_action = action;
    macLink.sendMailToMac((MailType *) &k, sizeof(KeyIndType), 0, 0, 23);
}

extern BYTE HLCapabilities[2];
extern BYTE allowSubscription;

void hw_TurnOnDSP()
{
    if (peltor_mode == peltor_pp) {
        HWinterfaceReqType hwreq;
        hwreq.Primitive = HW_interface_req;
        hwreq.CtrlCmd = TurnOnDSP_req;
        hwreq.CtrlValue = 0;
        macLink.sendMailToMac((MailType *) &hwreq, sizeof(HWinterfaceReqType), 0, 0, 7);
    } else {
        HWinterfaceReqType hwreq;
        hwreq.Primitive = HW_interface_req;
        hwreq.CtrlCmd = TurnOnDSP_req;
        hwreq.CtrlValue = 2;
        macLink.sendMailToMac((MailType *) &hwreq, sizeof(HWinterfaceReqType), 0, 0, 8);
    }
}

void audio_open()
{
    AudioCtrlReqType audioReq;
    audioReq.Primitive = AUDIOCTRL_req;
    audioReq.CtrlCmd = OPENAUDIO_cmd;
    audioReq.CtrlValue = 0; /*not used*/
    macLink.sendMailToMac((MailType *) &audioReq, sizeof(AudioCtrlReqType), 0, 0, 10);
}

void hw_ActivateHS()
{
    HWinterfaceReqType hwreq;
    hwreq.Primitive = HW_interface_req;
    hwreq.CtrlCmd = ActivateHS_req;
    hwreq.CtrlValue = 0;/*not used.*/
    macLink.sendMailToMac((MailType *) &hwreq, sizeof(HWinterfaceReqType), 0, 0, 4);
    _sprintf_(StatusString, "hw_ActivateHS");
    PrintStatus(0, StatusString);
}

void hw_InternalSpeaker(Boolean activated)
{
    HWinterfaceReqType hwreq;
    hwreq.Primitive = HW_interface_req;
    hwreq.CtrlCmd = InternalSpeaker_req;
    hwreq.CtrlValue = activated;
    macLink.sendMailToMac((MailType *) &hwreq, sizeof(HWinterfaceReqType), 0, 0, 6);
}

void hw_RequestLsrMicGain()
{
    HWinterfaceReqType hwreq;
    hwreq.Primitive = HW_interface_req;
    hwreq.CtrlCmd = RequestLsrMicGain_req;
    hwreq.CtrlValue = 0;
    macLink.sendMailToMac((MailType *) &hwreq, sizeof(HWinterfaceReqType), 0, 0, 5);
}

void audio_stop_inband_tone()
{
    AudioCtrlReqType audioReq;
    audioReq.Primitive = AUDIOCTRL_req;
    audioReq.CtrlCmd = STOPINBANDTONE_cmd;
    audioReq.CtrlValue = 0; /*not used*/
    macLink.sendMailToMac((MailType *) &audioReq, sizeof(AudioCtrlReqType), 0, 0, 18);
}

void audio_rx_unmute()
{
    AudioCtrlReqType audioReq;
    audioReq.Primitive = AUDIOCTRL_req;
    audioReq.CtrlCmd = RXUNMUTE_cmd;
    audioReq.CtrlValue = 0; /*not used*/
    macLink.sendMailToMac((MailType *) &audioReq, sizeof(AudioCtrlReqType), 0, 0, 12);
}

void audio_tx_unmute()
{
    if (peltor_mode == peltor_fp) {
        ;
    } else {
        AudioCtrlReqType audioReq;
        audioReq.Primitive = AUDIOCTRL_req;
        audioReq.CtrlCmd = TXUNMUTE_cmd;
        audioReq.CtrlValue = 0; /*not used*/
        macLink.sendMailToMac((MailType *) &audioReq, sizeof(AudioCtrlReqType), 0, 0, 13);
    }
}

void setMic(int index)
{
    HWinterfaceReqType hwreq;
    hwreq.Primitive = HW_interface_req;
    hwreq.CtrlCmd = MIC_cmd;
    hwreq.CtrlValue = index;
    macLink.sendMailToMac((MailType *) &hwreq, sizeof(HWinterfaceReqType), 0, 0, 20);
}

void setVolume(int index)
{
    AudioCtrlReqType audioReq;
    audioReq.Primitive = AUDIOCTRL_req;

    audioReq.CtrlCmd = RXVOLUMEN_cmd + index;
    audioReq.CtrlValue = peltor_mode; /*not used*/

    macLink.sendMailToMac((MailType *) &audioReq, sizeof(AudioCtrlReqType), 0, 0, 19);
}

void set_sound_user_active(UByte user)
{
    hw_TurnOnDSP();
    audio_open();
    hw_ActivateHS();
    hw_InternalSpeaker(TRUE);

    hw_RequestLsrMicGain();

    audio_stop_inband_tone();
    audio_tx_unmute();
    audio_rx_unmute();
    setMic(2);
    setVolume(3);
}
