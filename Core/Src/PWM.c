#include "ti_msp_dl_config.h"
#include "PWM.h"
#include "Delay.h"


/*
 * PWM_0 初始化：基于 TimerG 模块配置 PWM 信号输出
 */
static const DL_TimerG_ClockConfig gPWM_0ClockConfig = {
    .clockSel = DL_TIMER_CLOCK_BUSCLK,
    .divideRatio = DL_TIMER_CLOCK_DIVIDE_8,
    .prescale = 99U};

static const DL_TimerG_PWMConfig gPWM_0Config = {
    .pwmMode = DL_TIMER_PWM_MODE_EDGE_ALIGN, // 边沿对齐模式
    .period = 1000,                          // 周期计数（对应占空比为 500）
    .isTimerWithFourCC = false,
    .startTimer = DL_TIMER_STOP};

void PWM0_init(void)
{
  // 配置 PWM 输出引脚功能并设置为输出
  DL_GPIO_initPeripheralOutputFunction(GPIO_PWM_0_C0_IOMUX, GPIO_PWM_0_C0_IOMUX_FUNC);
  DL_GPIO_enableOutput(GPIO_PWM_0_C0_PORT, GPIO_PWM_0_C0_PIN);

  DL_TimerG_setClockConfig(PWM_0_INST, (DL_TimerG_ClockConfig *)&gPWM_0ClockConfig);
  DL_TimerG_initPWMMode(PWM_0_INST, (DL_TimerG_PWMConfig *)&gPWM_0Config);

  // 设置 PWM 输出条件（常规设置）
  DL_TimerG_setCounterControl(PWM_0_INST, DL_TIMER_CZC_CCCTL0_ZCOND, DL_TIMER_CAC_CCCTL0_ACOND, DL_TIMER_CLC_CCCTL0_LCOND);
  DL_TimerG_setCaptureCompareOutCtl(PWM_0_INST, DL_TIMER_CC_OCTL_INIT_VAL_LOW, DL_TIMER_CC_OCTL_INV_OUT_DISABLED, DL_TIMER_CC_OCTL_SRC_FUNCVAL, DL_TIMERG_CAPTURE_COMPARE_0_INDEX);

  // 设置比较值与更新方式
  DL_TimerG_setCaptCompUpdateMethod(PWM_0_INST, DL_TIMER_CC_UPDATE_METHOD_IMMEDIATE, DL_TIMERG_CAPTURE_COMPARE_0_INDEX);
  DL_TimerG_setCaptureCompareValue(PWM_0_INST, PWM_0_Priod / 2, DL_TIMER_CC_0_INDEX); // 占空比为 50%

  DL_TimerG_enableClock(PWM_0_INST);
  DL_TimerG_setCCPDirection(PWM_0_INST, DL_TIMER_CC0_OUTPUT);

  DL_TimerG_startCounter(PWM_0_INST); // 启动PWM_0定时器
}

void PWM0_Set(uint8_t data)
{
  DL_Timer_setCaptureCompareValue(PWM_0_INST, (uint32_t)PWM_0_Priod * (100-data) / 100, DL_TIMER_CC_0_INDEX);
}