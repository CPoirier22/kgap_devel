#include "../../include/common/common_general_functions.h"
#include "../../include/common/common_general_callback.h"
#include "../../../../include/hlkgap/other/include/pp/nvm.h"
#include "../../../../include/hlkgap/common/include/dispatch.h"
#include "../../../../include/common/include/glibc.h"

PPIDType last_eeprom_user = 0xffff;
extern void *_memcpy(void *DST, const void *SRC, unsigned int LENGTH);
extern void DeleteBuffer(void * BufferPointer);
static UByte ee_interface_blocked = 0;
static UByte * readBuffer = 0;
static UByte lastLength = 0;

void ee_result_received()
{
    if (readBuffer != 0) {
        if (getRunMode())
            fp_general_eeprom_read_res(1, last_eeprom_user, readBuffer, lastLength);
        else
            pp_general_eeprom_read_res(1, last_eeprom_user, readBuffer, lastLength);
        DeleteBuffer((void*) readBuffer);
        readBuffer = 0;
    } else {
        if (getRunMode())
            fp_general_eeprom_read_res(0, last_eeprom_user, 0, 0);
        else
            pp_general_eeprom_read_res(0, last_eeprom_user, 0, 0);
    }
    last_eeprom_user = 0xffff;
    ee_interface_blocked = 0;

}

UByte general_eeprom_write_req(WORD address, UByte * data, UByte length, PPIDType ppid)
{
    if (!ee_interface_blocked) {
        EeStoreDataReqType *EeStoreDataReq;

        NewSignal(sizeof(EeStoreDataReqType) + length, (void **) &EeStoreDataReq);
        _memcpy(getEeStoreDataReqTypeIE(EeStoreDataReq), data, length);
        EeStoreDataReq->DataTypes = EEDT_ANYADDRESS;
        EeStoreDataReq->SubsNo = 0;
        setAddressData(address, length);
        SendSignal((SignalType *) EeStoreDataReq, EE_PROCESS_ID, EE_PRIMITIVE, EE_STORE_DATA_req);
        last_eeprom_user = ppid;
        return 0;
    } else {
        return 1;
    }
}

extern Boolean NewBuffer(int BufferLength, void **BufferPointer/*, HeapNoType HeapCnt*/);

UByte general_eeprom_read_req(WORD address, UByte length, PPIDType ppid)
{
    if (!ee_interface_blocked) {
        EeReadDataReqType *EeReadDataReq;
        NewBuffer(length, (void**) &readBuffer);
        NewSignal(sizeof(EeReadDataReqType) + sizeof(void *), (void **) &EeReadDataReq);
        EeReadDataReq->ReturnTIPD = TIPD_APPLICATION;
        EeReadDataReq->DataTypes = EEDT_ANYADDRESS;
        getEeReadDataReqTypeDataPtr(EeReadDataReq)[0] = (void *) readBuffer;
        setAddressData(address, length);
        SendSignal((SignalType *) EeReadDataReq, EE_PROCESS_ID, EE_PRIMITIVE, EE_READ_DATA_req);
        last_eeprom_user = ppid;
        ee_interface_blocked = 1;
        lastLength = length;
        return 0;
    } else {
        return 1;
    }
}
