#ifndef __KEY_H
#define __KEY_H

#include "stdint.h"



/* Port definition for Pin Group GPIO_SWITCHES */
#define Key_PORT                         (GPIOB)
#define Key_Pin                         (DL_GPIO_PIN_21)
#define Key_IOMUX                        (IOMUX_PINCM49)

void Key_Init(void);
uint8_t Key_GetNum(void);

#endif
