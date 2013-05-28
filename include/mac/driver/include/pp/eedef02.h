#ifndef __EEDEF_02_H
#define __EEDEF_02_H



#define EE_24C128


#ifdef EE_24C128
#define EE_SIZE     16384     /* 16k bytes EEPROM*/
#endif
#ifdef EE_24C64
#define EE_SIZE     8192     /* 8k bytes EEPROM*/
#endif




#define EE_WRITE_DELAY_LOOPCOUNT 5000   /*500*/
#define EE_PAGE_SIZE 16
#define EE_DEVICEADDRESS 0xA0 /* 1010 0000 = Device address for page 0 write.*/
#define EE_WRITE_TIME    (3*T10_MS) /* 20-30ms*/

#define EN_ACCESS2_INT  (1<<7)
#define EN_ACCESS_BUS2  (1<<0)
#define ACCESS2_INT (1<<5)


#endif
