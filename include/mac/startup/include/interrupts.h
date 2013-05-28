#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

typedef  void (*InterruptHandler) (void);

void init_interrupt_handling(void);
void set_interrupt_handler(unsigned short id, InterruptHandler);
InterruptHandler get_interrupt_handler(unsigned short id);

#define NUMBEROFINTERRUPTS 31

#endif /*INTERRUPTS_H_*/
