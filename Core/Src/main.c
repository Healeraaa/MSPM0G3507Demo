#include "ti_msp_dl_config.h"
#include "LED.h"
#include "Key.h"
/* This results in approximately 0.5s of delay assuming 32MHz CPU_CLK */
#define DELAY (16000000)

int main(void)
{
    uint8_t Key_Num = 0;
    /* Power on GPIO, initialize pins as digital outputs */
    SYSCFG_DL_init();
    LED_Init();
    Key_Init();
    LED_ON();

    while (1) 
    {
        Key_Num = Key_GetNum();
        if(Key_Num == 1)
        {
            LED_ON();
        }
        else
        {
            LED_OFF();
        }
        // delay_cycles(DELAY);
    }
}
