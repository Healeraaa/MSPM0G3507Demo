#include "ti_msp_dl_config.h"

SYSCONFIG_WEAK void SYSCFG_DL_initPower(void)
{
    DL_GPIO_reset(GPIOA);
    DL_GPIO_reset(GPIOB);
    DL_TimerA_reset(TIMA0);
    DL_TimerG_reset(TIMG0);
    DL_WWDT_reset(WWDT0); // 复位窗口看门狗 WWDT0 模块
    DL_UART_Main_reset(UART0);
    DL_ADC12_reset(ADC1);
    DL_ADC12_reset(ADC0);
    DL_DAC12_reset(DAC0);

    DL_GPIO_enablePower(GPIOA);
    DL_GPIO_enablePower(GPIOB);
    DL_TimerA_enablePower(TIMA0);
    DL_TimerG_enablePower(TIMG0);
    DL_WWDT_enablePower(WWDT0); // 启用 WWDT0 电源
    DL_UART_Main_enablePower(UART0);
    DL_ADC12_enablePower(ADC1);
    DL_ADC12_enablePower(ADC0);
    DL_DAC12_enablePower(DAC0);

    delay_cycles(POWER_STARTUP_DELAY);
}
