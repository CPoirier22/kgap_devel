#ifndef RS232_HW_COMMON_H_
#define RS232_HW_COMMON_H_

extern BYTE UartTxBuffer[UART_TX_BUFFERSIZE];
extern WORD UartTxRdPtr;
extern WORD UartTxWrPtr;
extern BYTE TxActive;
extern void (*UARTTransmitCompleted)(void);

void setTransmitCompletedHandler(void (*handler)(void));
void uart_sendstring();
void serprintf232TRAP(char *msg);
void serprintf232(char *fmt);
void sendTestResponse(char * bytes, char length);

#endif /*RS232_HW_COMMON_H_*/
