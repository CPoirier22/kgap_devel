#ifndef APPLICATION_MAC_TUNNEL_H_
#define APPLICATION_MAC_TUNNEL_H_

#define MAC_TO_APP_SET_SOUND_USER_INACTIVE  0xd2
/*#define MAC_TO_APP_SET_SOUND_USER_ACTIVE  	0xd3*/
#define MAC_TO_APP_VOX_MUTE_REQUEST			0xd4
#define APP_TO_MAC_SET_VOX_ACTIVE			0xd5
#define MAC_TO_APP_PLAY_SOUND				0xd6
#define APP_TO_MAC_PLAY_SOUND				0xd7
#define APP_TO_MAC_ALLOW_SUBSCRIPTION       0xd8
#define APP_TO_MAC_GPIO_REGISTER_INPUT      0xd9
#define APP_TO_MAC_GPIO_DEREGISTER_INPUT    0xda
#define APP_TO_MAC_GPIO_REGISTER_OUTPUT     0xdb
#define APP_TO_MAC_GPIO_SET_OUTPUT          0xdc
#define MAC_TO_APP_GPIO_INPUT_STATE_CHANGE  0xdd

#endif /*APPLICATION_MAC_TUNNEL_H_*/

