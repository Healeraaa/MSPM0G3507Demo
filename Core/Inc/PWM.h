#ifndef __PWM_H
#define __PWM_H

/* ====== PWM_0 定义 ====== */
#define PWM_0_INST                     TIMG0                        // 使用的定时器模块
#define PWM_0_INST_IRQHandler          TIMG0_IRQHandler             // 中断函数名称
#define PWM_0_INST_INT_IRQN            (TIMG0_INT_IRQn)            // 中断号
#define PWM_0_INST_CLK_FREQ            50000                       // PWM 模块时钟频率，50kHz
#define PWM_0_Priod                    1000                        // PWM计数周期


// PWM 通道0使用的引脚（GPIOA.12）
#define GPIO_PWM_0_C0_PORT             GPIOA
#define GPIO_PWM_0_C0_PIN              DL_GPIO_PIN_12
#define GPIO_PWM_0_C0_IOMUX            (IOMUX_PINCM34)
#define GPIO_PWM_0_C0_IOMUX_FUNC       IOMUX_PINCM34_PF_TIMG0_CCP0 // 该引脚复用为定时器输出
#define GPIO_PWM_0_C0_IDX              DL_TIMER_CC_0_INDEX         // 通道索引号

void PWM0_init(void);
void PWM0_Set(uint8_t data);

#endif


