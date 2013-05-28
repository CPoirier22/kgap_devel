#ifndef PELTOR_PP_APP_H_
#define PELTOR_PP_APP_H_

#include "../../../include/os/include/maildef.h"
#include "../../../include/common/include/bitsdef.h"
#include "../../../include/hlkgap/iwu/include/pp/piwuprim.h"
#include "../../../include/hlkgap/dduos/include/dduos.h"
#include "../../../include/hlkgap/common/include/dispatch.h"
#include "../../../include/common/include/print_status.h"
#include "../../../include/mac/driver/include/pp/eeutil.h"
#include "../../../include/machlinterface/include/maclink.h"
#include "../../../include/machlinterface/include/kgaplink.h"
#include "../include/soundplayer.h"
#include "../include/flash_sound.h"
#include "../../include/common_application.h"

#define mode_double_click 0
#define wait_for_login_delay 2
#define ptt_double_click 3
#define emergency_timer 4
#define out_of_range_timer 5
#define join_conference 7
#define wait_for_location_req 8
#define wait_for_very_long_key_press 9
#define fp_start_sum_point 10
#define listen_to_conference 11
#define join_conference_open_audio 12
#define inform_user_with_search 14
#define listen_to_conferene_cfm 15
#define start_subscription 16
#define start_portable_part 17
#define start_search 18
#define delay_startup 19
#define call_user 20
#define emergency_time 3000 /*10ï¿½s of milliseconds*/
#define out_of_range_time_out 1000 /*10ï¿½s of milliseconds*/
#define out_of_range_detect_time_out 500 /*10ï¿½s of milliseconds*/
#define very_long_key_delay	1000 /*10ï¿½s of milliseconds*/
#define listen_to_conference_cfm_time_out 500 /*10ï¿½s of milliseconds*/


#define maxVolume 5
#define maxVox 7
#define maxMic 4

extern UByte activeSubscriptions_rfpis[12];/*6byte * 100 //rfpi + empty marker*/

#define access_login_not_allowed 1
extern UByte activeSubscriptions_access_filters[2];


/*void change_peltor_pp_statefunction(void (*new_peltor_pp_statefunction)(SignalType * signal), UByte event, UByte playsound);*/

void waiting_for_power_up(SignalType * signal);
void one_search_bases(SignalType * Signal);
void one_subscribe_with_0000(SignalType * Signal);
void three_select_base(SignalType * Signal);
void three_login_to_base(SignalType * Signal);

/*Util functions*/
extern int sprintf_function_name(char * tmp, void (*new_peltor_pp_statefunction)(SignalType * signal));
extern void debug_state_change(void (*new_peltor_pp_statefunction)(SignalType * signal));
extern void store_state_change(void (*new_peltor_pp_statefunction)(SignalType * signal));
extern void play_sound_state(void (*new_peltor_pp_statefunction)(SignalType * signal));
extern void startPeltorFPTimer(UByte subevent, int timeout_value);
extern void readUser(int index);
extern void disableSumPoint();
extern void fpstartsumpoint(UByte sumPoint);

/*All other extern functions*/
extern void start_pp(int sessionID);
extern WORD getSubs0StartAddr();
extern WORD getSUBSCRIPTION_SIZE();
extern MACLink macLink;
extern void CallForSubsSelect(BYTE SubscriptionNo, int sessionID);
extern void EnableConfCh(UByte sumpoint);
extern char *getReadableARI(UByte* rfpi);
extern void CallForSearchRFPI(SearchModeType SearchMode, int sessionID);
extern void CallForSubscription(UByte *rfpi, unsigned long Code_AC, int sessionID);
extern void SendSubsRemove(int sessionID);
extern void callUser_PP(char * number, int sessionId);
extern void TurnOffHandset();
extern void DeleteBuffer(void * BufferPointer);
extern void SendAlarmTelegram(UByte value);

#endif /*PELTOR_PP_APP_H_*/
