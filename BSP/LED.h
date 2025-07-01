#ifndef __LED_H
#define __LED_H

#define LED_PORT                               (GPIOB)
#define LED_PIN                                (DL_GPIO_PIN_14)
#define LED_IOMUX                              (IOMUX_PINCM31)

void LED_Init(void);
void LED_ON(void);
void LED_OFF(void);
void LED_Turn(void);


#endif
