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
* $History:: sound.c                                                          $ *
*                                                                               *
* Initial Revision                                                              *
*********************************************************************************
*/
#include "sound.h"
#include "../../../../../../include/common/include/print_status.h"

static char silent[4] = {0x00,0x02,0xff,0xff};

char * getWavPointer(unsigned char index_to_wav)
{
    switch (index_to_wav)
    {
        case sound_on:
            return  (char *)wav_on;
        case sound_off:
            return  (char *)wav_off;
        case sound_beep:
            return  (char *)wav_beep;
        case sound_double_beep:
            return  (char *)wav_double_beep;
        case sound_volume_ascending:
            return  (char *)wav_volume_ascending;
        case sound_volume_descending:
            return  (char *)wav_volume_descending;
        case sound_ring_once:
            return  (char *)wav_ring_once;
        case sound_donkey:
            return  (char *)wav_donkey;
        case sound_z_low_battery:
            return  (char *)wav_z_low_battery;
        case sound_z_out_of_range:
            return  (char *)wav_z_out_of_range;
        case sound_z_searching:
            return  (char *)wav_z_searching;
        case sound_z_listen_only:
            return  (char *)wav_z_listen_only;
        case sound_z_headset_registered:
            return  (char *)wav_z_headset_registered;
        case sound_z_headset_not_registered:
            return  (char *)wav_z_headset_not_registered;
        case sound_z_headset_on:
            return  (char *)wav_z_headset_on;
        case sound_z_headset_off:
            return  (char *)wav_z_headset_off;
        case sound_z_headset_connected:
            return  (char *)wav_z_headset_connected;
        case sound_z_base_not_found:
            return  (char *)wav_z_base_not_found;
        case sound_vehicle_detect:
            return  (char *)wav_vehicle_detect;
        case sound_vehicle_detect_100ms:
            return  (char *)wav_vehicle_detect_100ms;
        case sound_vehicle_detect_250ms:
            return  (char *)wav_vehicle_detect_250ms;
        case sound_AHFmode:
            return  (char *)wav_AHFmode;
        case sound_HFmode:
            return  (char *)wav_HFmode;
        case sound_LISTENmode:
            return  (char *)wav_LISTENmode;
        case sound_max:
            return  (char *)wav_max;
        case sound_min:
            return  (char *)wav_min;
        case sound_PAGEmode:
            return  (char *)wav_PAGEmode;
        case sound_PTTmode:
            return  (char *)wav_PTTmode;
        case sound_STmode:
            return  (char *)wav_STmode;
        default:
        	PrintStatus(0,"Default Silence");
            return  (char *)silent;
    };
}
