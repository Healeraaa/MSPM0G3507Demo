#include "ti_msp_dl_config.h"
#include "Timer.h"
#include "Delay.h"

/*
 * TIMER_0 时钟配置结构体（100kHz）
 */
static  DL_TimerA_ClockConfig gTIMER_0ClockConfig = {
    .clockSel = DL_TIMER_CLOCK_BUSCLK,
    .divideRatio = DL_TIMER_CLOCK_DIVIDE_8,
    .prescale = 99U,
};

/*
 * TIMER_0 定时器配置结构体，周期为 500ms，向上计数，初始不启动
 */
static  DL_TimerA_TimerConfig gTIMER_0TimerConfig = {
    .period     = TIMER_0_INST_LOAD_VALUE,
    .timerMode  = DL_TIMER_TIMER_MODE_PERIODIC,
    .startTimer = DL_TIMER_STOP,
};


/**
 * @brief    定时器0初始化，可设置分频参数
 * @param    divide   时钟分频系数，取值为DL_TIMER_CLOCK_DIVIDE_x枚举值之一：
 *                    - DL_TIMER_CLOCK_DIVIDE_1
 *                    - DL_TIMER_CLOCK_DIVIDE_2
 *                    - DL_TIMER_CLOCK_DIVIDE_4
 *                    - DL_TIMER_CLOCK_DIVIDE_8
 *                    - DL_TIMER_CLOCK_DIVIDE_16
 *                    - DL_TIMER_CLOCK_DIVIDE_32
 *                    - DL_TIMER_CLOCK_DIVIDE_64
 *                    - DL_TIMER_CLOCK_DIVIDE_128
 * @param    prescale 预分频系数（如99，实际分频为prescale+1）
 * @param    period   定时器周期计数值
 * @retval   无
 */
void Timer0_init(DL_TIMER_CLOCK_DIVIDE divide, uint32_t prescale, uint32_t period)
{
    gTIMER_0ClockConfig.divideRatio = divide;
    gTIMER_0ClockConfig.prescale = prescale;
    gTIMER_0TimerConfig.period = period;

    DL_TimerA_setClockConfig(TIMER_0_INST, (DL_TimerA_ClockConfig *)&gTIMER_0ClockConfig);
    DL_TimerA_initTimerMode(TIMER_0_INST, (DL_TimerA_TimerConfig *)&gTIMER_0TimerConfig);
    DL_TimerA_enableInterrupt(TIMER_0_INST, DL_TIMERA_INTERRUPT_ZERO_EVENT);
    DL_TimerA_enableClock(TIMER_0_INST);

    NVIC_EnableIRQ(TIMER_0_INST_INT_IRQN);
    DL_TimerA_startCounter(TIMER_0_INST);
}