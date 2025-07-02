#include "ti_msp_dl_config.h"
#include "Key.h"

static KeyInfo Keys[KEY_NUM] = {
	{KEY_STATE_IDLE, 0, 0, IOMUX_PINCM26, GPIOB, DL_GPIO_PIN_9},
	{KEY_STATE_IDLE, 0, 0, IOMUX_PINCM31, GPIOB, DL_GPIO_PIN_14},
	{KEY_STATE_IDLE, 0, 0, IOMUX_PINCM14, GPIOA, DL_GPIO_PIN_7}, // KEY3
	{KEY_STATE_IDLE, 0, 0, IOMUX_PINCM3, GPIOA, DL_GPIO_PIN_28}, // KEY2
	{KEY_STATE_IDLE, 0, 0, IOMUX_PINCM6, GPIOA, DL_GPIO_PIN_31}, // KEY1
};

/**
 * 函    数：按键引脚初始化
 * 参    数：无
 * 返 回 值：无
 */
void Key_GPIO_Init(void)
{
	for (int i = 0; i < KEY_NUM; i++)
	{
		DL_GPIO_initDigitalInputFeatures(
			Keys[i].pinMux, // GPIO 端口
			DL_GPIO_INVERSION_DISABLE,
			DL_GPIO_RESISTOR_PULL_UP, // 上拉电阻
			DL_GPIO_HYSTERESIS_DISABLE,
			DL_GPIO_WAKEUP_DISABLE);
	}
}

void Key_Init(void)
{
	for (int i = 0; i < KEY_NUM; i++)
	{
		Keys[i].state = KEY_STATE_IDLE;
		Keys[i].FiltCounter = 0;
		Keys[i].flag = 0;
	}
	Key_GPIO_Init();
}

void Key_Update(void)
{
	for (int i = 0; i < KEY_NUM; i++)
	{
		// uint8_t pinVal = DL_GPIO_readPins(Keys[i].port, Keys[i].pins); // 0代表按下
		uint8_t pinVal = (DL_GPIO_readPins(Keys[i].port, Keys[i].pins)) ? 1 : 0;
		switch (Keys[i].state)
		{
		case KEY_STATE_IDLE:
			if (pinVal == 0)
			{
				Keys[i].FiltCounter = 0;
				Keys[i].state = KEY_STATE_DEBOUNCE_PRESS;
			}
			break;

		case KEY_STATE_DEBOUNCE_PRESS:
			if (pinVal == 0)
			{
				if (++Keys[i].FiltCounter >= KEY_DEBOUNCE_TICKS)
				{
					Keys[i].state = KEY_STATE_WAIT_RELEASE;
					Keys[i].flag = 1; // 记录有效按键事件
				}
			}
			else
			{
				Keys[i].state = KEY_STATE_IDLE;
			}
			break;

		case KEY_STATE_WAIT_RELEASE:
			if (pinVal)
			{
				Keys[i].FiltCounter = 0;
				Keys[i].state = KEY_STATE_DEBOUNCE_RELEASE;
			}
			break;

		case KEY_STATE_DEBOUNCE_RELEASE:
			if (pinVal)
			{
				if (++Keys[i].FiltCounter >= KEY_DEBOUNCE_TICKS)
				{
					Keys[i].state = KEY_STATE_IDLE;
				}
			}
			else
			{
				Keys[i].state = KEY_STATE_WAIT_RELEASE;
			}
			break;
		}
	}
}

/**
 * 函    数：按键获取键码
 * 参    数：无
 * 返 回 值：按下按键的键码值，范围：0~2，返回0代表没有按键按下
 * 注意事项：此函数是阻塞式操作，当按键按住不放时，函数会卡住，直到按键松手
 */

// 非阻塞获取，在看门狗中进行按键检测更新
uint8_t Key_GetNum(void)
{
	for (int i = 0; i < KEY_NUM; i++)
	{
		if (Keys[i].flag)
		{
			Keys[i].flag = 0;
			return i + 1; // 返回按键编号（1~3）
		}
	}
	return 0; // 没有按键事件
}
// 阻塞式按键检测

// uint8_t Key_GetNum(void)
// {
// 	uint8_t KeyNum = 0;								 // 定义变量，默认键码值为0
// 	if (DL_GPIO_readPins(GPIOB, DL_GPIO_PIN_9) == 0) // 读输入寄存器的状态，如果为0，则代表按键1按下
// 	{
// 		delay_cycles(160000); // 延时消抖
// 		while (DL_GPIO_readPins(GPIOB, DL_GPIO_PIN_9) == 1)
// 			;				  // 等待按键松手
// 		delay_cycles(160000); // 延时消抖
// 		KeyNum = 1;			  // 置键码为1
// 	}
// 	else if (DL_GPIO_readPins(GPIOB, DL_GPIO_PIN_14) == 0) // 读输入寄存器的状态，如果为0，则代表按键1按下
// 	{
// 		delay_cycles(160000); // 延时消抖
// 		while (DL_GPIO_readPins(GPIOB, DL_GPIO_PIN_14) == 1)
// 			;				  // 等待按键松手
// 		delay_cycles(160000); // 延时消抖
// 		KeyNum = 2;			  // 置键码为1
// 	}
// 	else if (DL_GPIO_readPins(GPIOA, DL_GPIO_PIN_7) == 0) // 读输入寄存器的状态，如果为0，则代表按键1按下
// 	{
// 		delay_cycles(160000); // 延时消抖
// 		while (DL_GPIO_readPins(GPIOA, DL_GPIO_PIN_7) == 1)
// 			;				  // 等待按键松手
// 		delay_cycles(160000); // 延时消抖
// 		KeyNum = 3;			  // 置键码为1
// 	}
// 	else if (DL_GPIO_readPins(GPIOA, DL_GPIO_PIN_28) == 0) // 读输入寄存器的状态，如果为0，则代表按键1按下
// 	{
// 		delay_cycles(160000); // 延时消抖
// 		while (DL_GPIO_readPins(GPIOA, DL_GPIO_PIN_28) == 1)
// 			;				  // 等待按键松手
// 		delay_cycles(160000); // 延时消抖
// 		KeyNum = 4;			  // 置键码为1
// 	}
// 	else if (DL_GPIO_readPins(GPIOA, DL_GPIO_PIN_31) == 0) // 读输入寄存器的状态，如果为0，则代表按键1按下
// 	{
// 		delay_cycles(160000); // 延时消抖
// 		while (DL_GPIO_readPins(GPIOA, DL_GPIO_PIN_31) == 1)
// 			;				  // 等待按键松手
// 		delay_cycles(160000); // 延时消抖
// 		KeyNum = 5;			  // 置键码为1
// 	}

// 	else
// 	{
// 		KeyNum = 0;
// 	}

// 	return KeyNum; // 返回键码值，如果没有按键按下，所有if都不成立，则键码为默认值0
// }
