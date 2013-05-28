/*
 ********************************************************************
 *
 * Module:     RS232_L2.h
 * Contents:   Containing the defines and prototyping for RS232_L2.c
 * Author:     KIRK telecom / KEH
 * Copyright   KIRK telecom A/S. All rights reserved.
 *
 * $Header:   K:/PH/141005xx/Xx/Basis/Archive/H/RS232_L2.h_v   1.0   Nov 19 2003 11:07:56   on  $
 *
 * $Log:   K:/PH/141005xx/Xx/Basis/Archive/H/RS232_L2.h_v  $
 *
 *    Rev 1.0   Nov 19 2003 11:07:56   on
 * Initial version of IP 600
 *
 *********************************************************************/
/** include files **/
#include "../../../common/include/bitsdef.h"


#ifndef UART_TX_BUFFERSIZE
  #define UART_TX_BUFFERSIZE  0x4000
#endif
#ifndef UART_RX_BUFFERSIZE
  #define UART_RX_BUFFERSIZE  0x400
#endif

#define  STX              0x02   /* Start transmission*/
#define  DLE              0x10   /**/
#define  DLE_MSB_BYTE     0x0100
#define  RS               0x1E   /* record seperator*/
#define  ETX              0x03   /* end transmission*/
#define  NDU_START_INDEX  0      /* Start of NDU relative to end of length field*/



#define LENGTH_FIELD_SIZE   2    /* size of Length field in packet*/
#define DST_SRC_SIZE  4          /* size of source/dest type/num fields in packet*/
#define MAX_NDU_LENGTH 128       /* Max length of NDU*/

#define CHK_SUM_SIZE  1          /* size of checksum field in packet*/

#define UART_RX_IRQ_PRIORITET 7
#define UART_TX_IRQ_PRIORITET 7

extern BYTE UartTxBuffer[UART_TX_BUFFERSIZE];
extern BYTE UartRxBuffer[UART_RX_BUFFERSIZE];
extern WORD UartTxRdPtr;
extern WORD UartTxWrPtr;

extern void InitRS232(void);
extern void RS232_SendByte(unsigned char data);
extern void CopyToUartTxBuffer(UByte * buffer, unsigned int length);
extern void CopyByteToUartTxBuffer(UByte buffer);
extern void flushUartTxBuffer();
extern void uart_sendbyte(char data);
extern void uart_sendstring(void);
extern int uart_getbyte(char *data);
extern void setTransmitCompletedHandler(void (*handler)(void));
extern void clearUARTReceiveBuffer(void);

