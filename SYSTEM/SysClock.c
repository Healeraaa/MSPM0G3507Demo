#include "ti_msp_dl_config.h"
#include "SysClock.h"
#include "Delay.h"

// PLL 配置结构体：配置系统 PLL 输入频率、分频器、时钟源等
static const DL_SYSCTL_SYSPLLConfig gSYSPLLConfig = {
    .inputFreq = DL_SYSCTL_SYSPLL_INPUT_FREQ_32_48_MHZ,
    .rDivClk2x = 1,
    .rDivClk1 = 0,
    .rDivClk0 = 0,
    .enableCLK2x = DL_SYSCTL_SYSPLL_CLK2X_DISABLE,
    .enableCLK1 = DL_SYSCTL_SYSPLL_CLK1_DISABLE,
    .enableCLK0 = DL_SYSCTL_SYSPLL_CLK0_ENABLE,
    .sysPLLMCLK = DL_SYSCTL_SYSPLL_MCLK_CLK0,
    .sysPLLRef = DL_SYSCTL_SYSPLL_REF_HFCLK,
    .qDiv = 3,
    .pDiv = DL_SYSCTL_SYSPLL_PDIV_1};

void SysClock_init(void)
{
  // DL_GPIO_reset(GPIOA);
  // DL_GPIO_enablePower(GPIOA);
  // Power_Delay();

  // 配置高频晶振引脚为模拟功能
  DL_GPIO_initPeripheralAnalogFunction(GPIO_HFXIN_IOMUX);
  DL_GPIO_initPeripheralAnalogFunction(GPIO_HFXOUT_IOMUX);

  // 设置低功耗模式为 SLEEP0 模式
  DL_SYSCTL_setBORThreshold(DL_SYSCTL_BOR_THRESHOLD_LEVEL_0);
  // DL_SYSCTL_setFlashWaitState(DL_SYSCTL_FLASH_WAIT_STATE_2); // 配置 Flash 等待周期

  DL_SYSCTL_setSYSOSCFreq(DL_SYSCTL_SYSOSC_FREQ_BASE); // 设置系统振荡器频率
  DL_SYSCTL_disableHFXT();                             // 禁用外部高频晶振
  DL_SYSCTL_disableSYSPLL();                           // 禁用系统 PLL

  // 配置 HFXT 参数：范围32~48MHz，不启用 Bypass
  DL_SYSCTL_setHFCLKSourceHFXTParams(DL_SYSCTL_HFXT_RANGE_32_48_MHZ, 0, false);

  // 应用 PLL 配置
  DL_SYSCTL_configSYSPLL((DL_SYSCTL_SYSPLLConfig *)&gSYSPLLConfig);

  // 设置低功耗时钟 ULP 分频器为 2
  DL_SYSCTL_setULPCLKDivider(DL_SYSCTL_ULPCLK_DIV_2);

  // 设置主系统时钟来源为 SYSPLL
  DL_SYSCTL_setMCLKSource(SYSOSC, HSCLK, DL_SYSCTL_HSCLK_SOURCE_SYSPLL);
}
