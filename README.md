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

