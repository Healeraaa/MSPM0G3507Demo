#include "ti_msp_dl_config.h"
#include "SysClock.h"
#include "Delay.h"

/* 系统锁相环(PLL)配置 */
static const DL_SYSCTL_SYSPLLConfig gSYSPLLConfig = {
    .inputFreq = DL_SYSCTL_SYSPLL_INPUT_FREQ_32_48_MHZ, // 输入频率范围
    .rDivClk2x = 1,                                     // CLK2X分频系数
    .rDivClk1 = 0,                                      // CLK1分频系数
    .rDivClk0 = 0,                                      // CLK0分频系数
    .enableCLK2x = DL_SYSCTL_SYSPLL_CLK2X_DISABLE,      // 禁用2倍时钟
    .enableCLK1 = DL_SYSCTL_SYSPLL_CLK1_DISABLE,        // 禁用CLK1
    .enableCLK0 = DL_SYSCTL_SYSPLL_CLK0_ENABLE,         // 启用CLK0
    .sysPLLMCLK = DL_SYSCTL_SYSPLL_MCLK_CLK0,           // 主时钟源选择
    .sysPLLRef = DL_SYSCTL_SYSPLL_REF_HFCLK,            // PLL参考时钟源
    .qDiv = 3,                                          // Q分频系数
    .pDiv = DL_SYSCTL_SYSPLL_PDIV_1                     // P分频系数
};

void SysClock_init(void)
{
  // DL_GPIO_reset(GPIOA);
  // DL_GPIO_enablePower(GPIOA);
  // delay_cycles(POWER_STARTUP_DELAY);

  // 配置高频晶振引脚为模拟功能
  DL_GPIO_initPeripheralAnalogFunction(GPIO_HFXIN_IOMUX);
  DL_GPIO_initPeripheralAnalogFunction(GPIO_HFXOUT_IOMUX);

  // 设置 BOR（Brown-Out Reset，掉电复位）阈值为最低等级（LEVEL_0）；电压低于此值时芯片自动复位
  DL_SYSCTL_setBORThreshold(DL_SYSCTL_BOR_THRESHOLD_LEVEL_0);
  // 设置 Flash 的等待周期为 2 个周期（适应高主频访问）
  DL_SYSCTL_setFlashWaitState(DL_SYSCTL_FLASH_WAIT_STATE_2);
  // 设置内部系统振荡器频率为默认基准频率（通常为 4 MHz）
  DL_SYSCTL_setSYSOSCFreq(DL_SYSCTL_SYSOSC_FREQ_BASE);
  // 禁用外部高频晶振（HFXT），初始化前应先关闭
  DL_SYSCTL_disableHFXT();
  // 禁用系统 PLL（锁相环），重新配置前必须关闭
  DL_SYSCTL_disableSYSPLL();
  // 配置 HFXT（高频晶振）参数：- 频率范围为 32–48MH - 超时周期数为 100（决定等待时长） - 启用 bypass 模式（true 表示绕过晶振电路，直接使用输入）
  DL_SYSCTL_setHFCLKSourceHFXTParams(DL_SYSCTL_HFXT_RANGE_32_48_MHZ, 100, true);
  // 配置 SYSPLL（锁相环）相关分频器、输入源等
  DL_SYSCTL_configSYSPLL((DL_SYSCTL_SYSPLLConfig *)&gSYSPLLConfig);
  // 设置 ULPCLK（超低功耗时钟）分频系数为 2
  DL_SYSCTL_setULPCLKDivider(DL_SYSCTL_ULPCLK_DIV_2);
  // 多功能外设时钟配置
  DL_SYSCTL_enableMFPCLK();                                  // 使能MFP时钟
  DL_SYSCTL_setMFPCLKSource(DL_SYSCTL_MFPCLK_SOURCE_SYSOSC); // 选择时钟源
  // 设置主时钟 MCLK 的来源为： SYSOSC（内部系统振荡器） → HSCLK → SYSPLL 输出
  DL_SYSCTL_setMCLKSource(SYSOSC, HSCLK, DL_SYSCTL_HSCLK_SOURCE_SYSPLL);
  // 轮询等待以下所有系统时钟源都进入“GOOD”（就绪）状态：
  // - SYSPLL（锁相环）
  // - HFCLK（高频主时钟，通常是 HFXT 或 SYSPLL 输出）
  // - HSCLK（高速度时钟，即 MCLK 经过分频后的结果）
  // - LFOSC（低频内部振荡器）
  while ((DL_SYSCTL_getClockStatus() & (DL_SYSCTL_CLK_STATUS_SYSPLL_GOOD |
                                        DL_SYSCTL_CLK_STATUS_HFCLK_GOOD |
                                        DL_SYSCTL_CLK_STATUS_HSCLK_GOOD |
                                        DL_SYSCTL_CLK_STATUS_LFOSC_GOOD)) != (DL_SYSCTL_CLK_STATUS_SYSPLL_GOOD |
                                                                              DL_SYSCTL_CLK_STATUS_HFCLK_GOOD |
                                                                              DL_SYSCTL_CLK_STATUS_HSCLK_GOOD |
                                                                              DL_SYSCTL_CLK_STATUS_LFOSC_GOOD))
  {
    // 等待直到所有时钟都稳定（否则系统时钟切换可能出错）

    //  注意：一旦启用 LFXT（外部低频晶振），内部 LFOSC 会自动关闭，
    // 且无法重新打开，除非执行一次完整的引导复位（BOOTRST）
  }
}
