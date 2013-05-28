#ifndef __PRINT_STATUS_H__
#define __PRINT_STATUS_H__

#include "../../common/include/bitsdef.h"

#define MAX_STATUS_MESSAGE_SIZE 0x0100
#define printfilter_printstatus_withoutheader 	1
#define printfilter_printstatus_withtheader 	2
#define printfilter_recording					4
#define printfilter_dduos_signals				8
#define printfilter_rtx_mails                   16
#define printfilter_call_status					32

extern char StatusString[MAX_STATUS_MESSAGE_SIZE];
extern UByte printfilter;

char *StringPrint(char *StringOut, char *StringIn);
char *StrPrintHexNibble(char *String, UByte Nibble);
char *StrPrintHexByte(char *String, UByte Byte);
char *StrPrintDecByte(char *String, UByte Byte);
char *StrPrintHexWord(char *String, WORD Word);
char *StrPrintHexAddr(char *String, unsigned long Addr);

extern void PrintStatus(UByte StatusMessageLevel, char *msg);
extern void (*PrintStatusCallback)(UByte StatusMessageLevel, char *msg);

#endif /**/
