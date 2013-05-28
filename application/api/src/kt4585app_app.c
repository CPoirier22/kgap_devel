#include "../include/kt4585app_pp_app.h"
#include "../mac/include/keys.h"
#include "../../../include/machlinterface/include/application_mac_tunnel.h"
#include "../../../include/hlkgap/common/include/aformat.h"
#include "../../../include/hlkgap/common/include/sformat.h"
#include "../../../include/hlkgap/iwu/include/pp/piwuprim.h"
#include "../../../include/common/include/glibc.h"

extern void *FindInfoElement(UByte InfoElementId, UByte * Message, int MessageLength);

extern void at_data_from_msf(char command,UByte * data, UByte length);

UByte at_msf_handler(SignalType * Signal)
{
    SsFacilityPrimType * SsFacilityPrim = (SsFacilityPrimType *) Signal;
    IwuToIwuType * IwuToIwuPtr;
    MsfSetupIEType * MsfSetupIE;
    StandByTxtIEType * StandByTxtIE;
    PPStatusInfoIEType * PPStatusInfoIE;


    IwuToIwuPtr = (IwuToIwuType *) FindInfoElement ( IwuToIwuId,getSsFacilityPrimTypeIE(SsFacilityPrim) - 2,
                  SsFacilityPrim->SignalHeader.SignalLength - sizeof(SsFacilityPrimType) + 2 );

    if (IwuToIwuPtr != NULL)
    {
        MsfSetupIE = (MsfSetupIEType *) FindInfoElement ( MsfSetupAPEIEId,getIwuToIwuSIE(IwuToIwuPtr) - 2,
                     SsFacilityPrim->SignalHeader.SignalLength - sizeof(SsFacilityPrimType) - sizeof(IwuToIwuType) + 2 );

        if (MsfSetupIE != NULL)
        {
        	PrintStatus(0,"MsfSetupIE");
        }
        StandByTxtIE = (StandByTxtIEType *) FindInfoElement ( StandByTxtAPEIEId,getIwuToIwuSIE(IwuToIwuPtr) - 2,
                       SsFacilityPrim->SignalHeader.SignalLength -
                       sizeof(SsFacilityPrimType) - sizeof(IwuToIwuType) + 2 );
        if (StandByTxtIE != NULL)
        {
        	PrintStatus(0,"StandByTxtIE");
        }

        PPStatusInfoIE = (PPStatusInfoIEType *) FindInfoElement(PPStatusInfoAPEIEId, getIwuToIwuSIE(IwuToIwuPtr) - 2,
                         SsFacilityPrim->SignalHeader.SignalLength - sizeof(SsFacilityPrimType) - sizeof(IwuToIwuType) + 2 );
        if (PPStatusInfoIE != NULL)
        {
			if (PPStatusInfoIE->StatusType == 0x11)
			{
				int databytes = PPStatusInfoIE->LengthOfContents-2;
				/*PrintStatus(0,"Message from pc application.....");*/
				if (databytes > 1)
				{
					at_data_from_msf(getPPStatusInfoIETypeIE(PPStatusInfoIE)[0],getPPStatusInfoIETypeIE(PPStatusInfoIE) + 1,databytes-1);
				}
				else if (databytes == 1)
				{
					at_data_from_msf(getPPStatusInfoIETypeIE(PPStatusInfoIE)[0],0,0);
				}
	            return 1;
			}

        }
    }

	return 0;
}

