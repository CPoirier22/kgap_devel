#ifndef _L2_H_
#define _L2_H_

#include "../../../common/include/bitsdef.h"
#ifndef L2_PACKET_SIZE
#define L2_PACKET_SIZE 255
#endif
#define L2_BUFFER_SIZE_RECV (L2_PACKET_SIZE)

#define STX 0x02
#define DLE 0x10
#define ETX 0x03


typedef enum
{ DLE_ERROR,                    /* DLE is followed by a value different from STX,ETX or DLE*/
  L2_RX_OVERFLOW,               /* L2 RX buffer Overflow*/
  L2_TX_OVERFLOW,               /* L2 TX Buffer is overflow*/
  CHSUM_ERROR,                  /* Error in the caculated/received packet checksum*/
  LENGTH_FIELD_ERROR,           /* Length field in packet to long/short*/
  MISSING_START,                /* The first characters must be a DLE STX sequence*/
  LAST_L2_ERROR                 /* Must always be the last number in enum!!*/
} L2ErrorEnum;

typedef enum
{
    L2_SYNC_STATE = 0,
    L2_WAIT_STX_STATE,
    L2_RECV_STATE,
    L2_DLE_STATE,
    L2_WAIT_TEST_CMD_PREFIX2,
    L2_WAIT_TEST_CMD_PREFIX3,
    L2_WAIT_TEST_CMD_TASKID,
    L2_WAIT_TEST_CMD_COUNT,
    L2_WAIT_TEST_CMD,
    L2_WAIT_AT_CMD_PREFIX2,
    L2_WAIT_AT_CMD_ACTION,
    L2_WAIT_ATA_NEWLINE,
    L2_WAIT_ATH_NEWLINE,
    L2_WAIT_ATD_NEWLINE,
    L2_WAIT_ATO_NEWLINE,
    L2_WAIT_ATE_DATA,
    L2_WAIT_ATE_NEWLINE,
    L2_BINARY_MODE,
    L2_LEAVE_BINARY_1,
    L2_LEAVE_BINARY_2,
    L2_INIT_STATE
} l2_state_t;

typedef struct
{
    unsigned long RXSignal_cnt;   /* Total number of signals received on L2*/
    unsigned long RXData_cnt;     /* Total number of data bytes received on L2 (excl. DLE, STX, ETX & Bytestuffing)*/
    unsigned long RXBuffer_cnt;   /* Total number of bytes received on L2*/
    unsigned long TXSignal_cnt;   /* Total number of signals sent on L2*/
    unsigned long TXData_cnt;     /* Total number of data bytes sent on L2 (excl. DLE, STX, ETX & Bytestuffing)*/
    unsigned long TXBuffer_cnt;   /* Total number of bytes sent on L2*/
}
L2ControlType;

typedef void (*l2_callback_t) (UByte * buffer, unsigned int length);
typedef void (*l2_callback_tx) (UByte buffer, unsigned int length, int sendIndex);
typedef void (*l2_test_cmd_callback) (UByte task_id, UByte count, UByte* cmd);

#define HISTORY_SIZE 12

typedef struct
{
    unsigned long L2Errors[LAST_L2_ERROR];        /* array containing summized errortypes*/
    L2ControlType L2Control;      /* Control and RX signal buffers*/
    l2_state_t l2_state;
    UByte l2_recv_buffer[L2_BUFFER_SIZE_RECV];
    UByte *l2_recv_buffer_ptr;
    l2_callback_t receive_callback;
    l2_callback_tx send_callback;
    l2_test_cmd_callback receive_test_cmd_callback;

    char history[HISTORY_SIZE];
    int historyTop;
    int send_index;
    UByte task_id;
    UByte count;
}
L2Channel;

L2Channel* l2_init(l2_callback_t receive_callback, l2_callback_tx send_callback, l2_test_cmd_callback send_cmd, int sendindex, void (*trace)(char));
void l2_recv(L2Channel*channel,UByte * buffer, unsigned int length);
void l2_send(L2Channel * channel, UByte (*getNextByte)(void), unsigned int length);
#endif
