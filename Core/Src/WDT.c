#include "ti_msp_dl_config.h"
#include "WDT.h"
#include "Delay.h"

void WDT_init(void)
{


  /*
   * 初始化 WWDT0 的 Interval Timer 模式，设置如下：
   * - 看门狗时钟源频率 = LFCLK / 分频 = 32768 Hz / 1 = 32768 Hz
   * - 定时周期 = (分频 * 计数位数) / 32768 = 1 * 2^8 / 32768 ≈ 7.81 毫秒
   */
  DL_WWDT_initIntervalTimerMode(WWDT0,
                                DL_WWDT_CLOCK_DIVIDE_2,      // 分频系数：2
                                DL_WWDT_TIMER_PERIOD_8_BITS, // 计数器宽度：8 位
                                DL_WWDT_RUN_IN_SLEEP);       // 睡眠模式下仍然运行

  // 启用 WWDT0 的定时中断功能
  DL_WWDT_enableInterrupt(WWDT0);
  NVIC_SetPriority(WWDT0_INT_IRQn, 2);
  NVIC_EnableIRQ(WWDT0_INT_IRQn);
}