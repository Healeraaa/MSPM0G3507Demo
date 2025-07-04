#include "ti_msp_dl_config.h"
#include <stdio.h>
#include "LED.h"
#include "Key.h"
#include "WDT.h"
#include "OLED.h"
#include "Delay.h"
#include "SysClock.h"
#include "UART.h"

uint8_t gEchoData = 0;

int main(void)
{
    uint8_t Key_Num = 0;

    /* Power on GPIO, initialize pins as digital outputs */
    SYSCFG_DL_init();
    SysClock_init();
    LED_Init();
    Key_Init();
    WDT_init();
    OLED_Init();
    UART0_init();
    Delay_ms(500);

    // OLED_ShowString(1,1,"Hello");
    LED2_ON();
    while (1)
    {
        // OLED_ShowString(1,1,"Hello");
        Key_Num = Key_GetNum();
        if (Key_Num == 1)
        {
            LED2_ON();
        }
        else if (Key_Num == 2)
        {
            LED3_ON();
        }
        else if (Key_Num == 3)
        {
            LED4_ON();
        }
        else if (Key_Num == 4)
        {
            LED2_ON();
            LED3_ON();
        }
        else if (Key_Num == 5)
        {
            LED3_ON();
            LED4_ON();
        }
        else
        {
            LED2_OFF();
            LED3_OFF();
            LED4_OFF();         
        }
        // LED2_Turn();
        // LED3_Turn();
        // LED4_Turn();
        // DL_UART_Main_transmitData(UART_0_INST, 0xA5);
        printf("Hello\r\n");
        Delay_ms(500);
    }
}

void GROUP0_IRQHandler(void)
{
    switch (DL_Interrupt_getPendingGroup(DL_INTERRUPT_GROUP_0))
    {
    case DL_INTERRUPT_GROUP0_IIDX_WWDT0:
        if (DL_WWDT_getPendingInterrupt(WWDT0))
        {
            Key_Update();                        // 在看门狗中断里定期调用
            DL_WWDT_clearInterruptStatus(WWDT0); // 清除中断标志位
        }
    default:
        break;
    }
}

void UART_0_INST_IRQHandler(void)
{
    switch (DL_UART_Main_getPendingInterrupt(UART_0_INST))
    {
    case DL_UART_MAIN_IIDX_RX:
        gEchoData = DL_UART_Main_receiveData(UART_0_INST);
        DL_UART_Main_transmitData(UART_0_INST, gEchoData);
        break;
    default:
        break;
    }
}
