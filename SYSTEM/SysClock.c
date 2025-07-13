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

/**
 * @brief  初始化系统主时钟及相关时钟源 初始化系统时钟为80MHz
 *
 * 本函数用于初始化MCU的系统主时钟（MCLK）及其相关的时钟源，包括高频晶振（HFXT）、系统锁相环（SYSPLL）、
 * 内部系统振荡器（SYSOSC）、超低功耗时钟（ULPCLK）和多功能外设时钟（MFPCLK）等。通过配置分频、时钟源选择、
 * 复位阈值、Flash等待周期等参数，确保系统主时钟稳定可靠，并等待所有关键时钟源进入“GOOD”状态后再退出。
 *
 * @note  若后续启用外部低频晶振（LFXT），内部LFOSC会自动关闭且无法重新打开，除非执行一次完整的引导复位（BOOTRST）。
 */
void SysClock_init(void) // 初始化系统主时钟及相关时钟源
{
  // DL_GPIO_reset(GPIOA);
  // DL_GPIO_enablePower(GPIOA);
  // delay_cycles(POWER_STARTUP_DELAY);

  DL_GPIO_initPeripheralAnalogFunction(GPIO_HFXIN_IOMUX);    // 配置高频晶振引脚为模拟功能
  DL_GPIO_initPeripheralAnalogFunction(GPIO_HFXOUT_IOMUX);

  DL_SYSCTL_setBORThreshold(DL_SYSCTL_BOR_THRESHOLD_LEVEL_0); // 设置掉电复位阈值
  DL_SYSCTL_setFlashWaitState(DL_SYSCTL_FLASH_WAIT_STATE_2);  // 设置Flash等待周期
  DL_SYSCTL_setSYSOSCFreq(DL_SYSCTL_SYSOSC_FREQ_BASE);        // 设置内部振荡器频率
  DL_SYSCTL_disableHFXT();                                    // 禁用高频晶振
  DL_SYSCTL_disableSYSPLL();                                  // 禁用PLL
  DL_SYSCTL_setHFCLKSourceHFXTParams(DL_SYSCTL_HFXT_RANGE_32_48_MHZ, 100, true); // 配置高频晶振参数
  DL_SYSCTL_configSYSPLL((DL_SYSCTL_SYSPLLConfig *)&gSYSPLLConfig);              // 配置PLL
  DL_SYSCTL_setULPCLKDivider(DL_SYSCTL_ULPCLK_DIV_2);         // 设置超低功耗时钟分频
  DL_SYSCTL_enableMFPCLK();                                   // 使能多功能外设时钟
  DL_SYSCTL_setMFPCLKSource(DL_SYSCTL_MFPCLK_SOURCE_SYSOSC);  // 设置MFP时钟源
  DL_SYSCTL_setMCLKSource(SYSOSC, HSCLK, DL_SYSCTL_HSCLK_SOURCE_SYSPLL); // 设置主时钟来源

  // 等待所有关键时钟源稳定
  while ((DL_SYSCTL_getClockStatus() & (DL_SYSCTL_CLK_STATUS_SYSPLL_GOOD |
                                        DL_SYSCTL_CLK_STATUS_HFCLK_GOOD |
                                        DL_SYSCTL_CLK_STATUS_HSCLK_GOOD |
                                        DL_SYSCTL_CLK_STATUS_LFOSC_GOOD)) != (DL_SYSCTL_CLK_STATUS_SYSPLL_GOOD |
                                                                              DL_SYSCTL_CLK_STATUS_HFCLK_GOOD |
                                                                              DL_SYSCTL_CLK_STATUS_HSCLK_GOOD |
                                                                              DL_SYSCTL_CLK_STATUS_LFOSC_GOOD))
  {
    // 等待时钟稳定
    // 注意：启用LFXT后LFOSC会自动关闭，需复位才能重新开启
  }
}
