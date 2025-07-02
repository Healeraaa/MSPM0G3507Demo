#include "ti_msp_dl_config.h"
#include "LED.h"

/**
  * 函    数：LED初始化
  * 参    数：无
  * 返 回 值：无
  */
void LED_Init(void)
{
	// 配置为 GPIO 输出模式
	DL_GPIO_initDigitalOutput(LED2_IOMUX);
  DL_GPIO_initDigitalOutput(LED3_IOMUX);
  DL_GPIO_initDigitalOutput(LED4_IOMUX);
	// 拉低输出电平
	DL_GPIO_clearPins(LED_PORT, LED2_PIN | LED3_PIN | LED4_PIN );
	// 使能输出模式
	DL_GPIO_enableOutput(LED_PORT, LED2_PIN | LED3_PIN | LED4_PIN);

}

/**
  * 函    数：LED1开启
  * 参    数：无
  * 返 回 值：无
  */
void LED2_ON(void)
{
	DL_GPIO_setPins(LED_PORT, LED2_PIN );
}

/**
  * 函    数：LED1关闭
  * 参    数：无
  * 返 回 值：无
  */
void LED2_OFF(void)
{
	DL_GPIO_clearPins(LED_PORT, LED2_PIN );
}

/**
  * 函    数：LED1状态翻转
  * 参    数：无
  * 返 回 值：无
  */
void LED2_Turn(void)
{
	DL_GPIO_togglePins(LED_PORT, LED2_PIN );
}

  /*
  * 函    数:LED3开启
  * 参    数：无
  * 返 回 值：无
  */
void LED3_ON(void)
{
	DL_GPIO_setPins(LED_PORT, LED3_PIN );
}

/**
  * 函    数：LED3关闭
  * 参    数：无
  * 返 回 值：无
  */
void LED3_OFF(void)
{
	DL_GPIO_clearPins(LED_PORT, LED3_PIN );
}

/**
  * 函    数：LED3状态翻转
  * 参    数：无
  * 返 回 值：无
  */
void LED3_Turn(void)
{
	DL_GPIO_togglePins(LED_PORT, LED3_PIN );
}




void LED4_ON(void)
{
	DL_GPIO_setPins(LED_PORT, LED4_PIN );
}


void LED4_OFF(void)
{
	DL_GPIO_clearPins(LED_PORT, LED4_PIN );
}


void LED4_Turn(void)
{
	DL_GPIO_togglePins(LED_PORT, LED4_PIN );
}