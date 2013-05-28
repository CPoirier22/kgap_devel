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
* $History:: sound.h                                                          $ *
*                                                                               *
* Initial Revision                                                              *
*********************************************************************************
*/
#ifndef SOUND_H_
#define SOUND_H_
#include "sounds_wav.h"

enum sounds {
    sound_on,
    sound_off,
    sound_beep,
    sound_double_beep,
    sound_volume_ascending,
    sound_volume_descending,
    sound_ring_once,
    sound_donkey,
    sound_z_low_battery,
    sound_z_out_of_range,
    sound_z_searching,
    sound_z_listen_only,
    sound_z_headset_registered,
    sound_z_headset_not_registered,
    sound_z_headset_on,
    sound_z_headset_off,
    sound_z_headset_connected,
    sound_z_base_not_found,
    sound_vehicle_detect,
    sound_vehicle_detect_100ms,
    sound_vehicle_detect_250ms,
    sound_AHFmode,
    sound_HFmode,
    sound_LISTENmode,
    sound_max,
    sound_min,
    sound_PAGEmode,
    sound_PTTmode,
    sound_STmode
};

char * getWavPointer(unsigned char index_to_wav);

#endif /*SOUND_H_*/
