#ifndef MAC_H_
#define MAC_H_

void mac_turnOnLed(void);
void mac_turnOffLed(void);
void requestDeviceRegister(DWORD address);
WORD getDeviceRegister(DWORD address);
void setDeviceRegister(DWORD address, WORD value);

#endif /* MAC_H_ */
