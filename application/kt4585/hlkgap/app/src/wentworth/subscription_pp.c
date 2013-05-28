/********************************************************************************
 *********************************************************************************
 *                                                                               *
 *     E ENEEEEEEEEEEEE             CCCC CCC         TTTTTTT TTTTTTTTTT          *
 *     E EEEEEEEEEEEEEE          CCCCC  C CCCC             T TTTTT               *
 *     E EEEE                   CCCCC    C CCCC            T TTTTT               *
 *     E EEEE                  CCCCC      C CCCC           T TTTTT               *
 *     E EEEE                 CCCCC                        T TTTTT               *
 *     E EEEEEEEEEEEEEE      CCCCC                         T TTTTT               *
 *     E EEEEEEEEEEEEEE      C CCCC                        T TTTTT               *
 *     E EEEE                 C CCCC                       T TTTTT               *
 *     E EEEE                  C CCCC      CCCCC           T TTTTT               *
 *     E EEEEEEEEEEEEEE         C CCCC   CCCCC             T TTTTT               *
 *     E EEEEEEEEEEEEEE  OO      C CCCCCCCC         OO     T TTTTT     OO        *
 *                       OO                         OO                 OO        *
 *                                                                               *
 *     Electronic Communication Technology A/S.                                  *
 *     Sintrupvej 23, DK-8220 Brabrand, Tel.: +45 87441230                       *
 *     Website: www.ect.dk                                                       *
 *                                                                               *
 *********************************************************************************
 * $History:: subscription_pp.c                                                $ *
 *                                                                               *
 * Initial Revision                                                              *
 *********************************************************************************
 */

#include "../../../../../api/include/pp/pp_subscription_callback.h"
#include "../../../../../api/include/pp/pp_subscription_functions.h"
#include "../../../../../../include/common/include/print_status.h"
#include "../../../../../../include/common/include/map_480_gcc.h"
#include "../../../../../include/eeplayout.h"
#include "wentworth_pp.h"
#include "fppp_common.h"
#include "../sound/sound.h"

static UByte sub_state = 0;
static unsigned char automatic_registration_in_progress = 0;
char BaseFilterChar[13]; // 12 digits and a terminating 0
static char ari_to_subscribe_on[5];
static unsigned char r_ari[5][5] = { { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF },
                                     { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF },
                                     { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF },
                                     { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF },
                                     { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF }  };

void BuildBaseFilterChar(unsigned char *packed, unsigned char *result)
{
  // of course this could be done smarter
  int i;
  result[0] = packed[0] >> 4;
  result[1] = packed[0] & 0xF;
  result[2] = packed[1] >> 4;
  result[3] = packed[1] & 0xF;
  result[4] = packed[2] >> 4;
  result[5] = packed[2] & 0xF;
  result[6] = packed[3] >> 4;
  result[7] = packed[3] & 0xF;
  result[8] = packed[4] >> 4;
  result[9] = packed[4] & 0xF;
  result[10] = packed[5] >> 4;
  result[11] = packed[5] & 0xF;
  result[12] = 0; // terminate string
  for (i = 0; i < 12; i++)
    if (result[i] < 10)
      result[i] += '0';
    else
      result[i] += 'A' - 10;
}

unsigned char CompBaseWithFilter(char *base, char*filter)
{
  // compare up to terminating zero on the base value
  unsigned char idx = 0;
  while ((base[idx] != 0) && (idx < 12))
  {
    if ((base[idx] != filter[idx]) && (filter[idx] != 'F'))
      return 0; // no match
    idx++;
  }
  return 1; // must be a match
}

unsigned long GetAccessCode(void)
{
  unsigned long temp;
  unsigned long temp1 = WENTWORTHeepromData.AccessCode[0];
  temp = temp1 << 24;
  temp1 = WENTWORTHeepromData.AccessCode[1];
  temp += (temp1 << 16);
  temp1 = WENTWORTHeepromData.AccessCode[2];
  temp += (temp1 << 8);
  temp1 = WENTWORTHeepromData.AccessCode[3];
  temp += temp1;
  return temp;
}


void pp_subscription_ariResult(char * readableAri, char * ari, UByte index)
{

}

void pp_subscription_deleted(UByte statusByte)
{
  PrintStatus(0, "Subscription deleted");
}
unsigned char base_locked=0;
extern void PlaySoundPP(unsigned char index);
extern void AFEDisableMicPathPP(void);

void pp_subscription_statusReceived(UByte status, UByte index)
{
  char* tmp = StatusString;
  tmp = StringPrint(tmp, "pp_subscription_statusReceived: ");
  tmp = StrPrintHexByte(tmp, status);
  PrintStatus(0, StatusString);
  switch (status)
  {
    case 0x00:
      if (headset.SystemMode != UNREGISTERED)
      {
//    	PrintStatus(0, "******  PP being unsubscribed *******");
    	headset.SystemMode = UNREGISTERED;
    	PlaySoundPP(sound_z_headset_not_registered);
        if (headset.TakingOrder)
        {
          general_startTimer(0, 0xA1, NULL, 0, 200);		// wait for wav to finish playing before playing double_beep
          AFEDisableMicPathPP();
        }
        if (headset.TakingOrder | headset.CarWaiting)
        {
      	  PrintStatus(0, "CB OFF / LED off");
      	  headset.TakingOrder = FALSE;
      	  headset.CarWaiting = FALSE;
      	  TurnOffYellowLED;							// turn off LED completely
      	  headset.GreenLEDisOn = FALSE;
      	  headset.RedLEDisOn = FALSE;
        }
      }
      break;
    case SS_Locked:
      {
        if (sub_state == 0 || sub_state == 3)
        {
          pp_subscription_searchForBases();
        }
      }
      break;
    case SS_Locked | SS_Subscripted:
    case SS_Subscripted:
      {
    	if (sub_state == 0)
    	{
          pp_subscription_loginToBase(1);
          sub_state = 2;
          // adding a 30 second timer; if base not found, force an auto subscription
          general_startTimer(0, 0x7B, NULL, 0, 3000);
    	}
      }
      break;
    case SS_LocRegSucceeded | SS_Subscripted: // lost lock
PrintStatus(0, "lost lock?");
      base_locked = 0;
      PlaySoundPP(sound_z_out_of_range);	// add 5 second timer for this message?
      headset.SystemMode = NOT_LOCKED;
      if (headset.TakingOrder)
      {
    	general_startTimer(0, 0xA1, NULL, 0, 200);	// wait for wav to finish playing before playing double_beep
    	AFEDisableMicPathPP();
      }
      if (headset.TakingOrder | headset.CarWaiting)
      {
    	PrintStatus(0, "CB OFF / LED off");
    	headset.TakingOrder = FALSE;
    	headset.CarWaiting = FALSE;
    	TurnOffYellowLED;							// turn off LED completely
    	headset.GreenLEDisOn = FALSE;
    	headset.RedLEDisOn = FALSE;
      }
      break;
    case SS_LocRegSucceeded | SS_Subscripted | SS_Locked:
PrintStatus(0, "locked!");
      base_locked = 1;
      //general_startTimer(0, 0x7C, NULL, 0, 300);/* try to reconnect call*/
      if (headset.PowerOnStatus >= 2)
      {
PrintStatus(0, "OOOOOOOO starting 0x16 timer from pp_subscription_statusReceived()");
	    PlaySoundPP(sound_z_headset_connected);
        general_startTimer(0, GET_SYSTEM_MODE, NULL, 0, 200);	// find out what mode we're in
      }
      break;
  }
}

unsigned char BaseAlreadyTried(char *ari)
{
  unsigned char f, i;
  for (f = 0; f < 5; f++)
    for (i = 0; i < 5; i++)
    {
      if (r_ari[f][i] != ari[i])
        break;
      else if (i == 4)
        return 1;
    }
  return 0;
}

unsigned char BaseFailed(char *ari)
{
  unsigned char f, i;
  for (f = 0; f < 5; f++)
    if (r_ari[f][0] == 0xFF)
      for (i = 0; i < 5; i++)
        r_ari[f][i] = ari[i];
  return 1;
}

void pp_subscription_baseFound(char * readableAri, char * ari)
{
  char *ptr;
  char *readari = NULL;
  int slen = strlen(readableAri);
  ptr = StringPrint(StatusString, "Base found:  ");
  ptr = StringPrint(ptr, readableAri);
  ptr = StringPrint(ptr, "-");
  PrintStatus(0, StatusString);
  readari = getReadableARI(WENTWORTHeepromData.BaseAri);
  if (memcmp(readari, readableAri, slen) == 0)
  {

    ptr = StringPrint(StatusString, "Trying to subscribe to:");
    ptr = StringPrint(ptr, readari);
    PrintStatus(0, StatusString);
    memcpy(ari_to_subscribe_on, ari, 5); // remember to save eeprom settings
    pp_subscription_subscribe(1, 0, ari, GetAccessCode());
    //pp_subscription_subscribe(1, 0, ari, 0xFFFF1111l);
    sub_state = 1;
    if (readari)
      mem_free(readari);
    readari = NULL;
  }
  else if ((WENTWORTHeepromData.BaseAri[0] == 0xFF) && (WENTWORTHeepromData.BaseAri[1] == 0xFF) && (WENTWORTHeepromData.BaseAri[2] == 0xFF) && (WENTWORTHeepromData.BaseAri[3] == 0xFF) && (WENTWORTHeepromData.BaseAri[4] == 0xFF))
  {
    if (readari)
      mem_free(readari);
    readari = NULL;
    // try to subscribe anyway
    memcpy(ari_to_subscribe_on, ari, 5); // remember to save eeprom settings
    if (BaseAlreadyTried(ari))
    {
      PrintStatus(0, "This base already tried - and failed");
    }
    else
    {
      readari = getReadableARI((UByte *)ari_to_subscribe_on);
      if (CompBaseWithFilter(readari, BaseFilterChar))
      {
        ptr = StringPrint(StatusString, "No base set - Trying to subscribe to:");
        ptr = StringPrint(ptr, readari);
        PrintStatus(0, StatusString);
        pp_subscription_subscribe(1, 0, ari, GetAccessCode());
        sub_state = 1; // maybe we should enter a new state?
        if (readari)
          mem_free(readari);
        readari = NULL;
      }
      else
      {
        ptr = StringPrint(StatusString, "No base set - looking for ");
        ptr = StringPrint(ptr, BaseFilterChar);
        /*               ptr = StrPrintHexByte(ptr, LGPeepromData.BaseFilter[0]);
         ptr = StrPrintHexByte(ptr, LGPeepromData.BaseFilter[1]);
         ptr = StrPrintHexByte(ptr, LGPeepromData.BaseFilter[2]);
         ptr = StrPrintHexByte(ptr, LGPeepromData.BaseFilter[3]);
         ptr = StrPrintHexByte(ptr, LGPeepromData.BaseFilter[4]);*/
        ptr = StringPrint(ptr, " (F is wildcard) - Found base:");
        ptr = StringPrint(ptr, readari);
        PrintStatus(0, StatusString);
        if (readari)
          mem_free(readari);
        readari = NULL;
      }
    }
  }
  else
  {
    ptr = StringPrint(StatusString, "Looking for:  ");
    readari = getReadableARI(WENTWORTHeepromData.BaseAri);
    ptr = StringPrint(ptr, readari);
    if (readari)
      mem_free(readari);
    readari = NULL;
    PrintStatus(0, StatusString);
  }
}

void pp_subscription_subscribeFinished(UByte status)
{
  if (status == 1)
  {
    PrintStatus(0, "Subscription failed (internal error), illegal ari selection");
  }
  else if (status == 2)
  {
    PrintStatus(0, "Subscription failed (external error, fp reject or communication error");
    //pp_subscription_subscribe(1, 0, ari_to_subscribe_on, 0xffffffff);
    pp_subscription_searchForBases();
    BaseFailed(ari_to_subscribe_on);
  }
  else if (status == 0)
  {
    PrintStatus(0, "Subscription successful");
  }
}

void StartAutomaticSubscription(void)
{
  // only start if subscribed, but still looking for base
  if (sub_state == 2)
  {
	  unsigned char f, i;
	  automatic_registration_in_progress = 1;
	  pp_subscription_delete(1);
	  memset(WENTWORTHeepromData.BaseAri, 0xFF, 5);
	  general_eeprom_write_req(EE_CUSTOMER_AREA, (UByte *) &(WENTWORTHeepromData.BaseAri[0]), sizeof(WENTWORTHEEpromStruct), 0);
	  sub_state = 0;
	  //pp_subscription_searchForBases();
	  for (f = 0; f < 5; f++)
		for (i = 0; i < 5; i++)
		  r_ari[f][i] = 0xFF;
  }
}

void pp_subscription_loginOk(char * standbyText)
{
  char* ptr;
  ptr = StringPrint(StatusString, "login ok, stbtxt: ");
  ptr = StringPrint(ptr, standbyText);
  PrintStatus(0, StatusString);
  sub_state = 0;

  if (WENTWORTHeepromData.action_after_logon == 0x01) /*send msf*/
  {
    general_startTimer(0, 0x20, NULL, 0, 500);
  }
  else if (WENTWORTHeepromData.action_after_logon == 0x02) /*call user enblock*/
  {
    general_startTimer(0, 0x21, NULL, 0, 500);
  }
  else if (WENTWORTHeepromData.action_after_logon == 0x08) /*call user enblock*/
  {
    general_startTimer(0, 0x22, NULL, 0, 500);
  }
  else if (WENTWORTHeepromData.action_after_logon == 0xFF) /*call user overlap*/
  {
    general_startTimer(0, 0x24, NULL, 0, 50);	// CRP: lowered this to decrease "registration" time
  }
  else if (WENTWORTHeepromData.action_after_logon == 0x04) /*count to ten using wav playback*/
  {
    general_startTimer(0, 0x23, NULL, 0, 500);
  }
  else if (WENTWORTHeepromData.action_after_logon == 0x05) /*Delete the subscription*/
  {
    general_startTimer(0, 0x26, NULL, 0, 500);
    sub_state = 3;
  }
  else if (WENTWORTHeepromData.action_after_logon == 0x06) /*initiate session*/
  {
    general_startTimer(0, 0x27, NULL, 0, 500);
  }
  else if (WENTWORTHeepromData.action_after_logon == 0x07) /*send pp status ind */
  {
    general_startTimer(0, 0x28, NULL, 0, 500);
  }
  else if (WENTWORTHeepromData.action_after_logon == 0x79) /*Delete the subscription*/
  {
    general_startTimer(0, 0x79, NULL, 0, 200);
  }
  else if (WENTWORTHeepromData.action_after_logon == 0x7B) /*Start Automatic Subscription*/
  {
    general_startTimer(0, 0x7B, NULL, 0, 1000); // 10 sec
  }
}

void ReadySubscription(void)
{
  memcpy(ari_to_subscribe_on, WENTWORTHeepromData.BaseAri, 5);
  BuildBaseFilterChar(WENTWORTHeepromData.BaseFilter, (UByte *)BaseFilterChar); // e.g. "000465FFFFFF" where F is wildcard
}
