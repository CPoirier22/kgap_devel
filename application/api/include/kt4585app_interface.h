#ifndef PELTOR_INTERFACE_H_
#define PELTOR_INTERFACE_H_

#include "../../../include/common/include/bitsdef.h"

typedef struct
{
    int out_of_range;
    int abnormal_release;
    int failed_listen;
    int number_of_ptt_times;
}
PeltorStatusType;

extern PeltorStatusType peltorStatus;
extern void printPeltorStatus();

#define user_sound_playback 1
#define user_conference_listen 2
#define user_conference_ptt 4
#define user_emergency 8
#define user_audioloopback 16

#define peltor_fp 1
#define peltor_pp 0
extern UByte peltor_mode;
extern UByte old_sum_point;
extern UByte external_active;

extern short volumeIndex;
extern short voxIndex;
extern short micIndex;
extern UByte subscription_filter_off_mode;

#define fp_dsp_listen 10
#define fp_dsp_connect 9
#define fp_dsp_disconnect 11
#define fp_dsp_mute 21

/*peltor_interface.c includes*/
extern void hw_ActivateHS();
extern void hw_DeActivateHS();
extern void hw_RequestLsrMicGain();
extern void hw_InternalSpeaker(Boolean activated);
extern void hw_TurnOnDSP();
extern void hw_TurnOffDSP();

extern void switch_runmode(UByte newmode);
extern UByte isBoostActive();
extern void setboostmode(UByte mode);
extern void setVolume(int index);
extern void setVox(int index);
extern void setMic(int index);
extern void selectSumPoint(int index);
extern void push_to_talk(int index, UByte disableSum);
extern void leave_push_to_talk(int index);
extern void activate_external(UByte external);
extern void deactivate_external();
extern void activate_fp_emergency();
extern void deactivate_fp_emergency();
extern void audio_open();
extern void audio_close();
extern void audio_rx_unmute();
extern void audio_tx_unmute();
extern void audio_tx_softmute();
extern void audio_rx_mute();
extern void audio_tx_mute();
extern void audio_stop_inband_tone();
extern void set_sound_user_active(UByte user); /*set bit*/
extern void set_sound_user_inactive(UByte user);
extern void handle_allow_subscription(UByte allow);
extern void forceMicroPhoneActive(UByte active);


/*extern includes*/
extern void setRxSearchMode(BYTE newMode);
extern void clearConfInfo();
extern void RestartHandset();
extern UByte is_database_empty();
extern UByte is_all_users_subscribed();

#endif /*PELTOR_INTERFACE_H_*/
