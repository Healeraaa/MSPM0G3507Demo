#include "ti_msp_dl_config.h"
#include "Timer.h"
#include "Delay.h"

/*
 * TIMER_0 时钟配置结构体（100kHz）
 */
static const DL_TimerA_ClockConfig gTIMER_0ClockConfig = {
    .clockSel = DL_TIMER_CLOCK_BUSCLK,
    .divideRatio = DL_TIMER_CLOCK_DIVIDE_8,
    .prescale = 99U,
};

/*
 * TIMER_0 定时器配置结构体，周期为 500ms，向上计数，初始不启动
 */
static const DL_TimerA_TimerConfig gTIMER_0TimerConfig = {
    .period     = TIMER_0_INST_LOAD_VALUE,
    .timerMode  = DL_TIMER_TIMER_MODE_PERIODIC,
    .startTimer = DL_TIMER_STOP,
};

/*
 * 定时器初始化
 */
void Timer0_init(void)
{
  // DL_TimerA_reset(TIMA0);
  // DL_TimerA_enablePower(TIMA0);
  DL_TimerA_setClockConfig(TIMER_0_INST, (DL_TimerA_ClockConfig *)&gTIMER_0ClockConfig);
  DL_TimerA_initTimerMode(TIMER_0_INST, (DL_TimerA_TimerConfig *)&gTIMER_0TimerConfig);
  DL_TimerA_enableInterrupt(TIMER_0_INST, DL_TIMERA_INTERRUPT_ZERO_EVENT);
  DL_TimerA_enableClock(TIMER_0_INST);

  NVIC_EnableIRQ(TIMER_0_INST_INT_IRQN);
  DL_TimerA_startCounter(TIMER_0_INST);
}


