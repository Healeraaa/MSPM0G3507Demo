#include "ti_msp_dl_config.h"
#include "Key.h"

/**
 * 函    数：按键初始化
 * 参    数：无
 * 返 回 值：无
 */
void Key_Init(void)
{
    //配置为输入模式，无电平反转，配置上拉电阻，不启用停滞功能，不用为低功耗唤醒
    DL_GPIO_initDigitalInputFeatures(   Key_IOMUX,
	                                    DL_GPIO_INVERSION_DISABLE, 
                                        DL_GPIO_RESISTOR_PULL_UP,
                                        DL_GPIO_HYSTERESIS_DISABLE, 
                                        DL_GPIO_WAKEUP_DISABLE);
}

/**
 * 函    数：按键获取键码
 * 参    数：无
 * 返 回 值：按下按键的键码值，范围：0~2，返回0代表没有按键按下
 * 注意事项：此函数是阻塞式操作，当按键按住不放时，函数会卡住，直到按键松手
 */
uint8_t Key_GetNum(void)
{
	uint8_t KeyNum = 0;								   // 定义变量，默认键码值为0
	if (DL_GPIO_readPins(Key_PORT, Key_Pin) == 0)  // 读输入寄存器的状态，如果为0，则代表按键1按下
	{
		delay_cycles(160000); // 延时消抖
		while (DL_GPIO_readPins(Key_PORT, Key_Pin) == 1);		  // 等待按键松手
		delay_cycles(160000);  // 延时消抖
		KeyNum = 1;	  // 置键码为1
	}
    else
    {
        KeyNum = 0;
    }

	return KeyNum; // 返回键码值，如果没有按键按下，所有if都不成立，则键码为默认值0
}
      