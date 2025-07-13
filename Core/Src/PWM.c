#include "ti_msp_dl_config.h"
#include "PWM.h"
#include "Delay.h"
#include "SysClock.h"

/*
 * PWM_0 初始化：基于 TimerG 模块配置 PWM 信号输出
 */
static  DL_TimerG_ClockConfig gPWM_0ClockConfig = {
    .clockSel = DL_TIMER_CLOCK_BUSCLK,
    .divideRatio = DL_TIMER_CLOCK_DIVIDE_8,
    .prescale = 99U};

static  DL_TimerG_PWMConfig gPWM_0Config = {
    .pwmMode = DL_TIMER_PWM_MODE_EDGE_ALIGN, // 边沿对齐模式
    .period = 1000,                          // 周期计数（对应占空比为 500）
    .isTimerWithFourCC = false,
    .startTimer = DL_TIMER_STOP};

/**
 * @brief    PWM0 初始化，可设置PWM频率和占空比;频率必须在gPWM_0ClockConfig.divideRatio和gPWM_0ClockConfig.prescale的限制内。
 * @param    freq_hz  期望PWM频率（Hz）
 * @param    duty     占空比（0~100，百分比）
 * @retval   无
 */
void PWM0_init(uint32_t freq_hz, uint8_t duty)
{
  uint32_t timer_clk = CPUCLK_FREQ / (gPWM_0ClockConfig.divideRatio +1)/ (gPWM_0ClockConfig.prescale + 1); // 计算定时器时钟
  uint32_t period = timer_clk / freq_hz / 2;
  uint32_t compare = (period * (100-duty)) / 100;

  // 配置 PWM 输出引脚功能并设置为输出
  DL_GPIO_initPeripheralOutputFunction(GPIO_PWM_0_C0_IOMUX, GPIO_PWM_0_C0_IOMUX_FUNC);
  DL_GPIO_enableOutput(GPIO_PWM_0_C0_PORT, GPIO_PWM_0_C0_PIN);

  DL_TimerG_setClockConfig(PWM_0_INST, (DL_TimerG_ClockConfig *)&gPWM_0ClockConfig);

  gPWM_0Config.period = period; // 更新周期
  DL_TimerG_initPWMMode(PWM_0_INST, &gPWM_0Config);

  // 设置 PWM 输出条件（常规设置）
  DL_TimerG_setCounterControl(PWM_0_INST, DL_TIMER_CZC_CCCTL0_ZCOND, DL_TIMER_CAC_CCCTL0_ACOND, DL_TIMER_CLC_CCCTL0_LCOND);
  DL_TimerG_setCaptureCompareOutCtl(PWM_0_INST, DL_TIMER_CC_OCTL_INIT_VAL_LOW, DL_TIMER_CC_OCTL_INV_OUT_DISABLED, DL_TIMER_CC_OCTL_SRC_FUNCVAL, DL_TIMERG_CAPTURE_COMPARE_0_INDEX);

  // 设置比较值与更新方式
  DL_TimerG_setCaptCompUpdateMethod(PWM_0_INST, DL_TIMER_CC_UPDATE_METHOD_IMMEDIATE, DL_TIMERG_CAPTURE_COMPARE_0_INDEX);
  DL_TimerG_setCaptureCompareValue(PWM_0_INST, compare, DL_TIMER_CC_0_INDEX);

  DL_TimerG_enableClock(PWM_0_INST);
  DL_TimerG_setCCPDirection(PWM_0_INST, DL_TIMER_CC0_OUTPUT);

  DL_TimerG_startCounter(PWM_0_INST); // 启动PWM_0
}

void PWM0_Set(uint8_t duty)
{
  DL_Timer_setCaptureCompareValue(PWM_0_INST, (uint32_t)gPWM_0Config.period * (100 - duty) / 100, DL_TIMER_CC_0_INDEX);
}