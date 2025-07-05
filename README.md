## 电源

所有用到外设的电源要在 `main` 函数最开始进行一次性上电。

```c
SYSCONFIG_WEAK void SYSCFG_DL_initPower(void)
{
    DL_GPIO_reset(GPIOA);
    DL_GPIO_reset(GPIOB);
    DL_WWDT_reset(WWDT0);        // 复位窗口看门狗 WWDT0 模块
    DL_UART_Main_reset(UART0);

    DL_GPIO_enablePower(GPIOA);
    DL_GPIO_enablePower(GPIOB);
    DL_WWDT_enablePower(WWDT0);  // 启用 WWDT0 电源
    DL_UART_Main_enablePower(UART0);

    delay_cycles(16);
}
