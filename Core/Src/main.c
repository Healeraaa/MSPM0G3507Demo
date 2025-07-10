#include "main.h"

uint8_t gEchoData = 0;

int main(void)
{
    uint8_t Key_Num = 0;
    System_Init();

    OLED_ShowString(1, 1, "Hello World");
    // LED2_ON();
    PWM0_Set(70);
    DAC_Set(3000);
    while (1)
    {
        // OLED_ShowString(1,1,"Hello");
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
        //     // LED2_OFF();
        //     LED3_OFF();
        //     LED4_OFF();
        // }
        // // LED2_Turn();
        // // LED3_Turn();
        // // LED4_Turn();
        // // DL_UART_Main_transmitData(UART_0_INST, 0xA5);
        // printf("Hello!\r\n");


        // printf("Start AD Convert!\r\n");
        // ADC_DMA_Convert();
        // for(uint16_t i = 0;i < ADC_SAMPLE_SIZE;i++)
        // {
        //     printf("%d is %d\r\n",i,ADCValue[i]);
        // }

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

void TIMER_0_INST_IRQHandler(void)
{
    // 读取并判断当前 TimerG 模块产生了哪一个中断源（通过中断索引标识符）
    switch (DL_TimerA_getPendingInterrupt(TIMER_0_INST))
    {

    case DL_TIMERA_IIDX_ZERO: // 定时器溢出中断
        LED2_Turn();
        break;

    default:
        break;
    }
}
