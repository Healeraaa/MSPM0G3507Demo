#ifndef __ADC_H
#define __ADC_H

/* ==================== ADC12 模块配置 ==================== */
#define ADC12_0_INST               ADC1
#define ADC12_0_INST_IRQHandler    ADC1_IRQHandler
#define ADC12_0_INST_INT_IRQN      (ADC1_INT_IRQn)

#define ADC12_0_ADCMEM_0           DL_ADC12_MEM_IDX_0
#define ADC12_0_ADCMEM_0_REF       DL_ADC12_REFERENCE_VOLTAGE_VDDA
#define ADC12_0_ADCMEM_0_REF_VOLTAGE_V 3.3

// ADC 输入通道 C7 对应的 GPIO 引脚（GPIOA.21）
#define GPIO_ADC12_0_C7_PORT       GPIOA
#define GPIO_ADC12_0_C7_PIN        DL_GPIO_PIN_21

// /* ==================== DMA 配置 ==================== */
// #define DMA_CH0_CHAN_ID            (0)
// #define ADC12_0_INST_DMA_TRIGGER   (DMA_ADC1_EVT_GEN_BD_TRIG)  // ADC → DMA 触发信号

#define ADC_SAMPLE_SIZE (64)




extern uint16_t ADCValue[ADC_SAMPLE_SIZE];

void ADC0_init(void);
void ADC_DMA_Convert(void);


#endif


