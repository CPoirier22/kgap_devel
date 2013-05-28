#ifndef DISPATCH_H_
#define DISPATCH_H_
#include "../../dduos/include/dduos.h"

extern ProcessIdType MAC_PROCESS_ID;
extern ProcessIdType LLME_PROCESS_ID;
extern ProcessIdType MAC_LLME_PROCESS_ID;
extern ProcessIdType APPLICATION_PROCESS_ID_FP;
extern ProcessIdType APPLICATION_PROCESS_ID_PP;
extern ProcessIdType EE_PROCESS_ID;
extern ProcessIdType IWU_PROCESS_ID;
extern ProcessIdType CC_PROCESS_ID;
extern ProcessIdType MM_PROCESS_ID;
extern ProcessIdType LCE_PROCESS_ID;
extern ProcessIdType LAPC_PROCESS_ID;
extern ProcessIdType Lc_PROCESS_ID;
extern ProcessIdType Lb_PROCESS_ID;
extern ProcessIdType CCF_PROCESS_ID;
extern ProcessIdType APP_OM_PROCESS_ID;
extern ProcessIdType HL_ME_PROCESS_ID;
extern ProcessIdType CCF_LLME_PROCESS_ID;
extern ProcessIdType APP_CC_PROCESS_ID;
extern ProcessIdType APP_SS_PROCESS_ID;
extern ProcessIdType CISS_PROCESS_ID;
extern ProcessIdType GIM_PROCESS_ID;
extern ProcessIdType CALC_PROCESS_ID;
extern ProcessIdType APP_DB_PROCESS_ID;
extern ProcessIdType RESENDER_PROCESS_ID;


#define MAC_PRIMITIVE           5
#define LLME_PRIMITIVE          6
#define MAC_LLME_PRIMITIVE      7
#define APPLICATION_PRIMITIVE   8
#define EE_PRIMITIVE            9
#define IWU_PRIMITIVE           10
#define CC_PRIMITIVE            11
#define MM_PRIMITIVE            12
#define LCE_PRIMITIVE           13
#define LAPC_PRIMITIVE          14
#define Lc_PRIMITIVE            15
#define Lb_PRIMITIVE            16
#define CCF_PRIMITIVE           17
#define APP_OM_PRIMITIVE        18
#define HL_ME_PRIMITIVE         19
#define CCF_LLME_PRIMITIVE      20
#define APP_CC_PRIMITIVE        21
#define APP_SS_PRIMITIVE        22
#define CISS_PRIMITIVE          23
#define GIM_PRIMITIVE           24
#define NIF_PRIMITIVE           25
#define LED_PRIMITIVE           26
#define CALC_PRIMITIVE          27
#define BIF_PRIMITIVE           28
#define SIO_PRIMITIVE           29
#define APP_DB_PRIMITIVE        30
#define SCRIPT_PRIMITIVE        31

#endif /*DISPATCH_H_ */
