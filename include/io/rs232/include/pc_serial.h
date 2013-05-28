#ifndef PC_SERIAL_H_
#define PC_SERIAL_H_

extern void close_handle(unsigned long hCom);
extern unsigned long create_file(const char* com_id);
extern int write_file(unsigned long hCom, unsigned char * buffer, unsigned int length);
extern void set_comm_mask(unsigned long hCom);
extern int read_file(unsigned long hCom, unsigned char * buffer, int buffer_size);
extern void sleepFor(int ms);
extern void beginThread(void (*func) (void *), void* arg);
extern void initLock(void);
extern void obtainLock(void);
extern void releaseLock(void);

#endif /*PC_SERIAL_H_*/
