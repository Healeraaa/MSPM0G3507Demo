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
#include "PWM.h"
#include "ADC.h"
#include "DMA.h"
#include "DAC.h"

// ===== 用户定义的初始化入口 =====
void System_Init(void)
{
    SYSCFG_DL_initPower();
    SysClock_init();   // 用户自定义的时钟配置函数，设置 MCLK、HSCLK 等
    LED_Init();        // 配置 LED 输出 GPIO
    Key_Init();        // 配置按键输入 GPIO
    PWM0_init();
    Timer0_init();     // 包含定时器的时钟配置、模式设置、启动等
    UART0_init();      // 包含波特率配置、中断设置等
    ADC0_init();
    DMA_init();
    DAC_init();
    WDT_init();        // 设置溢出时间、中断响应等
    OLED_Init();       // OLED 显示驱动初始化（建议延后）
    Delay_ms(200);     // 具体时间视硬件情况而定
}
