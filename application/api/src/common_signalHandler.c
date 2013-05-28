#include "../include/fp/fp_api.h"
#include "../include/common/common_general_callback.h"
#include "../include/common/common_general_functions.h"
#include "../../../include/hlkgap/other/include/pp/nvm.h"
#include "../../../include/machlinterface/include/maclink.h"
#include "../../../include/machlinterface/include/application_mac_tunnel.h"

extern void ee_result_received();
extern void DeleteBuffer(void * BufferPointer);

UByte common_signalHander(SignalType * TheSignal)
{
	 switch (TheSignal->Event)
	    {
			case EE_PRIMITIVE:
			{
				switch (TheSignal->SubEvent)
				{
					case EE_READ_DATA_cfm:
					{
						ee_result_received();
						DeleteBuffer(TheSignal);
						return 1;
					};
				}
			}break;
	    };
	return 0;
}

extern MACLink macLink;

void sendAppToMac(UByte key, UByte action)
{
    KeyIndType k;
    k.Primitive = MAC_APPLICATION_TUNNEL;
    k.Key = key;
    k.Key_action = action;
    macLink.sendMailToMac((MailType *) &k, sizeof(KeyIndType), 0, 0, 23);
}
