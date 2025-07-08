#include "ti_msp_dl_config.h"
#include "Delay.h"
#include "SysClock.h"



/**
  * @brief  微秒级延时
  * @param  xus 延时时长
  * @retval 无
  */
void Delay_us(uint32_t xus)
{
	while(xus--)
	{
	delay_cycles(CPUCLK_FREQ/1000000);
	}
}

/**
  * @brief  毫秒级延时
  * @param  xms 延时时长
  * @retval 无
  */
void Delay_ms(uint32_t xms)
{
	while(xms--)
	{
		delay_cycles(CPUCLK_FREQ/1000);
	}
	
}
 
/**
  * @brief  秒级延时
  * @param  xs 延时时长
  * @retval 无
  */
void Delay_s(uint32_t xs)
{
	while (xs--)
	{
		delay_cycles(CPUCLK_FREQ);
	}
} 

// void Power_Delay(void)
// {
// 	delay_cycles(POWER_STARTUP_DELAY);
// }