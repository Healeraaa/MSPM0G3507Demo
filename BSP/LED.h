#ifndef __LED_H
#define __LED_H

#define LED_PORT                               (GPIOB)
/* Defines for LED2: GPIOB.6 with pinCMx 25 on package pin 60 */
#define LED2_PIN                                       (DL_GPIO_PIN_6)
#define LED2_IOMUX                                     (IOMUX_PINCM23)
/* Defines for LED3: GPIOB.7 with pinCMx 26 on package pin 61 */
#define LED3_PIN                                       (DL_GPIO_PIN_7)
#define LED3_IOMUX                                     (IOMUX_PINCM24)
/* Defines for LED4: GPIOB.8 with pinCMx 26 on package pin 61 */
#define LED4_PIN                                       (DL_GPIO_PIN_8)
#define LED4_IOMUX                                     (IOMUX_PINCM25)

void LED_Init(void);
void LED2_ON(void);
void LED2_OFF(void);
void LED2_Turn(void);
void LED3_ON(void);
void LED3_OFF(void);
void LED3_Turn(void);
void LED4_ON(void);
void LED4_OFF(void);
void LED4_Turn(void);

#endif


