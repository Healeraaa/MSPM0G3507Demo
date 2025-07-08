## 电源
在 `main` 函数最开始,先单独上电时钟电源，因为其他外设配置需要时钟先配置好，之后一次性上电所有外设电源。上电顺序为：
1.SysClock_init();
2.SYSCFG_DL_initPower();


```c

void SysClock_init(void)
{
  DL_GPIO_reset(GPIOA);
  DL_GPIO_enablePower(GPIOA);
  delay_cycles(POWER_STARTUP_DELAY);

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

SYSCONFIG_WEAK void SYSCFG_DL_initPower(void)
{
    // DL_GPIO_reset(GPIOA);
    DL_GPIO_reset(GPIOB);
    DL_TimerA_reset(TIMA0);
    DL_WWDT_reset(WWDT0); // 复位窗口看门狗 WWDT0 模块
    DL_UART_Main_reset(UART0);

    // DL_GPIO_enablePower(GPIOA);
    DL_GPIO_enablePower(GPIOB);
    DL_TimerA_enablePower(TIMA0);
    DL_WWDT_enablePower(WWDT0); // 启用 WWDT0 电源
    DL_UART_Main_enablePower(UART0);

    delay_cycles(POWER_STARTUP_DELAY);
}

````


## 串口重定向方法

在 `UART.h` 中加入下面代码之后，即可将 `printf()` 重定向到 UART：

```c
int fputc(int _c, FILE *_fp) {
  DL_UART_Main_transmitDataBlocking(UART_0_INST, _c);
  return _c;
}
````


## Keil 设置方法

在 Keil 中打开：

```
Project → Options for Target → Target 标签页
```

✅ **勾选：Use MicroLIB**

这会启用简化的运行时库，自动定义必要的符号，如 `__use_two_region_memory` 和 `__initial_sp` 等。

---

## 报错处理

勾选 MicroLIB 后如果出现如下错误：

```
.\Objects\Project.axf: Error: L6218E: Undefined symbol __use_two_region_memory (referred from startup_mspm0g350x_uvision.o).
.\Objects\Project.axf: Error: L6218E: Undefined symbol __initial_sp (referred from entry2.o).
```

请参考以下链接中的处理方法：

🔗 [https://blog.csdn.net/qq\_62014938/article/details/125602277](https://blog.csdn.net/qq_62014938/article/details/125602277)

```

