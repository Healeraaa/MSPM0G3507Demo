#include "ti_msp_dl_config.h"
#include "LED.h"
#include "Key.h"
#include "WDT.h"
#include "OLED.h"
/* This results in approximately 0.5s of delay assuming 32MHz CPU_CLK */
#define DELAY (16000000)

int main(void)
{
    uint8_t Key_Num = 0;
    /* Power on GPIO, initialize pins as digital outputs */
    SYSCFG_DL_init();
    LED_Init();
    Key_Init();
    WDT_init();
    OLED_Init();
    delay_cycles(1600000);
    OLED_ShowString(1,1,"Hello");
    while (1)
    {
        OLED_ShowString(1,1,"Hello");
        // Key_Num = Key_GetNum();
        // if (Key_Num == 1)
        // {
        //     LED2_ON();
        // }
        // else if (Key_Num == 2)
        // {
        //     LED3_ON();
        // }
        // else if (Key_Num == 3)
        // {
        //     LED4_ON();
        // }
        // else if (Key_Num == 4)
        // {
        //     LED2_ON();
        //     LED3_ON();
        // }
        // else if (Key_Num == 5)
        // {
        //     LED3_ON();
        //     LED4_ON();
        // }
        // else
        // {
        //     LED2_OFF();
        //     LED3_OFF();
        //     LED4_OFF();
        // }
        delay_cycles(1600000);
    }

}


void GROUP0_IRQHandler(void)
{
    switch (DL_Interrupt_getPendingGroup(DL_INTERRUPT_GROUP_0))
    {
    case DL_INTERRUPT_GROUP0_IIDX_WWDT0:
        if (DL_WWDT_getPendingInterrupt(WWDT0))
        {
            Key_Update(); // 在看门狗中断里定期调用
            DL_WWDT_clearInterruptStatus(WWDT0);//清除中断标志位
        }
    default:
        break;
    }
}