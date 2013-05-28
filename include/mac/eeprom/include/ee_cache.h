#ifndef EE_CACHE_H_
#define EE_CACHE_H_

void init_ee_cache(void);
void ReadEEbytes(WORD EEaddress, BYTE *DataPtr, WORD EEsize);
BYTE ReadEEPrombyte(WORD EEaddress);
void WriteEEcache(WORD EEaddress, BYTE EEsize, BYTE *EEdata);
void ReadEEPromData(UByte * DestinPtr, EEPromAdressCodeType AddrCode);
Boolean WriteEEPromData(UByte * srcPtr, EEPromAdressCodeType AddrCode);
void ee_cache_timeout(void);

#endif /*EE_CACHE_H_*/
