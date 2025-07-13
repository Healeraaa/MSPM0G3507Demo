#ifndef __SYSCLOCK_H
#define __SYSCLOCK_H

#define GPIO_HFXT_PORT GPIOA  // 高频晶振使用的端口
#define GPIO_HFXIN_PIN DL_GPIO_PIN_5
#define GPIO_HFXIN_IOMUX (IOMUX_PINCM10)
#define GPIO_HFXOUT_PIN DL_GPIO_PIN_6
#define GPIO_HFXOUT_IOMUX (IOMUX_PINCM11)

#define CPUCLK_FREQ 80000000 // 主系统时钟频率 80 MHz
#define BUSCLK_FREQ 40000000 // 主系统时钟频率（Hz）

void SysClock_init(void);

#endif
