#ifndef __DAC_H
#define __DAC_H

/* DAC12配置 */
#define DAC12_IRQHandler DAC0_IRQHandler
#define DAC12_INT_IRQN (DAC0_INT_IRQn)
/* DAC输出引脚 */
#define GPIO_DAC12_OUT_PORT GPIOA
#define GPIO_DAC12_OUT_PIN DL_GPIO_PIN_15
#define GPIO_DAC12_IOMUX_OUT (IOMUX_PINCM37)
#define GPIO_DAC12_IOMUX_OUT_FUNC IOMUX_PINCM37_PF_UNCONNECTED  // 未连接功能



void DAC_init(void);
void DAC_Set(uint16_t data);

#endif


