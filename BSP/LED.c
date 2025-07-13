#include "ti_msp_dl_config.h"
#include "LED.h"
#include "Delay.h"

/**
  * @brief    LED初始化
  * @param    无
  * @retval   无
  */
void LED_Init(void)
{
  // DL_GPIO_reset(LED_PORT);
  // DL_GPIO_enablePower(LED_PORT);
  // Power_Delay();
  DL_GPIO_initDigitalOutput(LED2_IOMUX);
  DL_GPIO_initDigitalOutput(LED3_IOMUX);
  DL_GPIO_initDigitalOutput(LED4_IOMUX);
  DL_GPIO_clearPins(LED_PORT, LED2_PIN | LED3_PIN | LED4_PIN );
  DL_GPIO_enableOutput(LED_PORT, LED2_PIN | LED3_PIN | LED4_PIN);
}

/**
  * @brief    LED2开启
  * @param    无
  * @retval   无
  */
void LED2_ON(void)
{
  DL_GPIO_setPins(LED_PORT, LED2_PIN );
}

/**
  * @brief    LED2关闭
  * @param    无
  * @retval   无
  */
void LED2_OFF(void)
{
  DL_GPIO_clearPins(LED_PORT, LED2_PIN );
}

/**
  * @brief    LED2状态翻转
  * @param    无
  * @retval   无
  */
void LED2_Turn(void)	
{
  DL_GPIO_togglePins(LED_PORT, LED2_PIN );
}

/**
  * @brief    LED3开启
  * @param    无
  * @retval   无
  */
void LED3_ON(void)
{
  DL_GPIO_setPins(LED_PORT, LED3_PIN );
}

/**
  * @brief    LED3关闭
  * @param    无
  * @retval   无
  */
void LED3_OFF(void)
{
  DL_GPIO_clearPins(LED_PORT, LED3_PIN );
}

/**
  * @brief    LED3状态翻转
  * @param    无
  * @retval   无
  */
void LED3_Turn(void)
{
  DL_GPIO_togglePins(LED_PORT, LED3_PIN );
}

/**
  * @brief    LED4开启
  * @param    无
  * @retval   无
  */
void LED4_ON(void)
{
  DL_GPIO_setPins(LED_PORT, LED4_PIN );
}

/**
  * @brief    LED4关闭
  * @param    无
  * @retval   无
  */
void LED4_OFF(void)
{
  DL_GPIO_clearPins(LED_PORT, LED4_PIN );
}

/**
  * @brief    LED4状态翻转
  * @param    无
  * @retval   无
  */
void LED4_Turn(void)
{
  DL_GPIO_togglePins(LED_PORT, LED4_PIN );
}