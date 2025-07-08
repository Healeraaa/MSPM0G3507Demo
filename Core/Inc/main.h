#include "ti_msp_dl_config.h"
#include <stdio.h>
#include "LED.h"
#include "Key.h"
#include "WDT.h"
#include "OLED.h"
#include "Delay.h"
#include "SysClock.h"
#include "UART.h"
#include "Timer.h"

// ===== 用户定义的初始化入口 =====
void System_Init(void)
{
    // 1. 上电并复位 GPIO 基础模块
    DL_GPIO_reset(GPIOA);
    DL_GPIO_reset(GPIOB);
    DL_GPIO_enablePower(GPIOA);
    DL_GPIO_enablePower(GPIOB);

    // 2. 初始化系统时钟（SYSOSC / PLL）
    SysClock_init();   // 用户自定义的时钟配置函数，设置 MCLK、HSCLK 等

    // 3. 初始化 GPIO 相关外设
    LED_Init();        // 配置 LED 输出 GPIO
    Key_Init();        // 配置按键输入 GPIO

    // 4. 上电并初始化定时器模块（必须顺序正确）
    DL_TimerA_reset(TIMA0);
    DL_TimerA_enablePower(TIMA0);
    Timer0_init();     // 包含定时器的时钟配置、模式设置、启动等

    // 5. 上电并初始化 UART 串口
    DL_UART_Main_reset(UART0);
    DL_UART_Main_enablePower(UART0);
    UART0_init();      // 包含波特率配置、中断设置等

    // 6. 上电并初始化 ADC（若使用）
    // DL_ADC12_reset(ADC0);
    // DL_ADC12_enablePower(ADC0);
    // ADC0_init();       // 配置采样通道、触发源、中断等

    // 7. 上电并初始化 DAC（若使用）
    // DL_DAC_reset(DAC0);
    // DL_DAC_enablePower(DAC0);
    // DAC0_init();       // 配置输出通道、电压参考等

    // 8. 上电并初始化 DMA（若使用）
    // DL_DMA_reset(DMA);
    // DL_DMA_enablePower(DMA);
    // DMA_init();        // 通道配置、触发源、优先级等

    // 9. 上电并初始化 SPI（若使用）
    // DL_SPI_reset(SPI0);
    // DL_SPI_enablePower(SPI0);
    // SPI0_init();       // 模式选择、主从配置、波特率等

    // 10. 上电并初始化 I2C（若使用）
    // DL_I2C_reset(I2C0);
    // DL_I2C_enablePower(I2C0);
    // I2C0_init();       // 地址设置、时钟速率等

    // 11. 上电并初始化看门狗（若使用）
    DL_WWDT_reset(WWDT0);
    DL_WWDT_enablePower(WWDT0);
    WDT_init();        // 设置溢出时间、中断响应等

    // 12. OLED 初始化（依赖 GPIO 和 I2C/SPI）
    OLED_Init();       // OLED 显示驱动初始化（建议延后）

    // 13. 上电延时，确保外设稳定
    Delay_ms(200);     // 具体时间视硬件情况而定
}
