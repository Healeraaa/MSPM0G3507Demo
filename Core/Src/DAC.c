#include "ti_msp_dl_config.h"
#include "DAC.h"
#include "Delay.h"

/***************** DAC12配置 *****************/
static const DL_DAC12_Config gDAC12Config = {
    .outputEnable              = DL_DAC12_OUTPUT_ENABLED,      // 使能输出
    .resolution                = DL_DAC12_RESOLUTION_12BIT,    // 12位分辨率
    .representation            = DL_DAC12_REPRESENTATION_BINARY, // 二进制表示
    .voltageReferenceSource    = DL_DAC12_VREF_SOURCE_VDDA_VSSA, // VDDA参考
    .amplifierSetting          = DL_DAC12_AMP_ON,              // 使能内部输出放大器（增强驱动能力）
    .fifoEnable                = DL_DAC12_FIFO_ENABLED,        // 启用FIFO
    .fifoTriggerSource         = DL_DAC12_FIFO_TRIGGER_SAMPLETIMER, // 采样定时器触发
    .dmaTriggerEnable          = DL_DAC12_DMA_TRIGGER_DISABLED,// 禁用DMA触发
    .dmaTriggerThreshold       = DL_DAC12_FIFO_THRESHOLD_ONE_QTR_EMPTY, // 1/4空阈值
    .sampleTimeGeneratorEnable = DL_DAC12_SAMPLETIMER_ENABLE,  // 使能采样定时器
    .sampleRate                = DL_DAC12_SAMPLES_PER_SECOND_16K, // 16K采样率
};
/* DAC初始化函数 */
void DAC_init(void)
{
    // DL_GPIO_setAnalogInternalResistor(GPIO_DAC12_IOMUX_OUT, DL_GPIO_RESISTOR_NONE);
    DL_DAC12_init(DAC0, &gDAC12Config);// 初始化DAC
    // DL_DAC12_enableInterrupt(DAC0, DL_DAC12_INTERRUPT_FIFO_TWO_QTRS_EMPTY);// 使能FIFO四分之一空中断
    DL_DAC12_enable(DAC0); // 使能DAC
    // NVIC_EnableIRQ(DAC12_INT_IRQN);
}

void DAC_Set(uint16_t data)
{
    DL_DAC12_output12(DAC0, data);
}

// void DAC12_IRQHandler(void)
// {
//     switch (DL_DAC12_getPendingInterrupt(DAC0)) {
//         case DL_DAC12_IIDX_FIFO_1_2_EMPTY:
//             DL_DAC12_output12(DAC0, 2048);
//             // if (gCounter >= OUTPUT_SIGNAL_SIZE) {
//             //     gCounter = 0;
//             // }
//             break;
//         default:

//             break;
//     }
// }
