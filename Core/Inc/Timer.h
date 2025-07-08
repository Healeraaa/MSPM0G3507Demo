#ifndef __TIMER_H
#define __TIMER_H

#define TIMER_0_INST TIMA0
#define TIMER_0_INST_IRQHandler TIMA0_IRQHandler
#define TIMER_0_INST_INT_IRQN TIMA0_INT_IRQn
#define TIMER_0_INST_LOAD_VALUE (49999U)


void Timer0_init(void);

#endif


