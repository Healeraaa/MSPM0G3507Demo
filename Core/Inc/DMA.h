#ifndef __DMA_H
#define __DMA_H


/* ==================== DMA 配置 ==================== */
#define DMA_CH0_CHAN_ID            (0)
#define ADC12_0_INST_DMA_TRIGGER   (DMA_ADC1_EVT_GEN_BD_TRIG)  // ADC → DMA 触发信号

void DMA_init(void);

#endif


