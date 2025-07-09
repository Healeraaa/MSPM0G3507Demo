#include "ti_msp_dl_config.h"
#include "ADC.h"
#include "DMA.h"
#include "Delay.h"

volatile bool ADC_DMA_FinishFlag;
uint16_t ADCValue[ADC_SAMPLE_SIZE];

/* ADC12_0 初始化配置 */
static const DL_ADC12_ClockConfig gADC12_0ClockConfig = {
    .clockSel = DL_ADC12_CLOCK_SYSOSC,               // 选择系统振荡器作为ADC时钟源
    .divideRatio = DL_ADC12_CLOCK_DIVIDE_1,          // 时钟1分频（不分频）
    .freqRange = DL_ADC12_CLOCK_FREQ_RANGE_24_TO_32, // 时钟频率范围24-32MHz
};

/* ADC12模块初始化函数 */
void ADC0_init(void)
{
  // 1. 配置ADC时钟
  DL_ADC12_setClockConfig(ADC12_0_INST, (DL_ADC12_ClockConfig *)&gADC12_0ClockConfig);

  // 2. 初始化单次采样模式
  DL_ADC12_initSingleSample(ADC12_0_INST,
                            DL_ADC12_REPEAT_MODE_ENABLED,             // 启用重复采样模式（连续转换）
                            DL_ADC12_SAMPLING_SOURCE_AUTO,            // 自动选择采样源
                            DL_ADC12_TRIG_SRC_SOFTWARE,               // 使用软件触发启动转换
                            DL_ADC12_SAMP_CONV_RES_12_BIT,            // 12位分辨率
                            DL_ADC12_SAMP_CONV_DATA_FORMAT_UNSIGNED); // 无符号数据格式

  // 3. 配置ADC内存转换寄存器0（ADCMEM0）
  DL_ADC12_configConversionMem(ADC12_0_INST, ADC12_0_ADCMEM_0,
                               DL_ADC12_INPUT_CHAN_7,                // 使用通道7作为模拟输入
                               DL_ADC12_REFERENCE_VOLTAGE_VDDA,      // 参考电压为VDDA（电源电压）
                               DL_ADC12_SAMPLE_TIMER_SOURCE_SCOMP0,  // 使用SCOMP0作为采样定时器源
                               DL_ADC12_AVERAGING_MODE_ENABLED,     // 禁用平均功能
                               DL_ADC12_BURN_OUT_SOURCE_DISABLED,    // 禁用烧毁电流源
                               DL_ADC12_TRIGGER_MODE_AUTO_NEXT,      // 自动步进到下一个转换（序列模式）
                               DL_ADC12_WINDOWS_COMP_MODE_DISABLED); // 禁用窗口比较模式

  // 4. 配置功耗模式
  DL_ADC12_setPowerDownMode(ADC12_0_INST, DL_ADC12_POWER_DOWN_MODE_MANUAL); // 手动断电模式

  // 5. 配置硬件平均参数（新增配置）
  DL_ADC12_configHwAverage(ADC12_0_INST,
      DL_ADC12_HW_AVG_NUM_ACC_16,          // 16次采样累加
      DL_ADC12_HW_AVG_DEN_DIV_BY_4);       // 结果除以4 → 等效4次采样平均

  // 6. 设置采样时间
  DL_ADC12_setSampleTime0(ADC12_0_INST, 2); // 设置采样时间参数为2个时钟周期

  // 7. DMA相关配置
  DL_ADC12_enableDMA(ADC12_0_INST);                                           // 启用ADC的DMA功能
  DL_ADC12_setDMASamplesCnt(ADC12_0_INST, 1);                                 // 设置每次DMA传输的样本数为1
  DL_ADC12_enableDMATrigger(ADC12_0_INST, (DL_ADC12_DMA_MEM0_RESULT_LOADED)); // MEM0结果加载时触发DMA

  // 8. 中断配置
  DL_ADC12_clearInterruptStatus(ADC12_0_INST, (DL_ADC12_INTERRUPT_DMA_DONE)); // 清除DMA完成中断标志
  DL_ADC12_enableInterrupt(ADC12_0_INST, (DL_ADC12_INTERRUPT_DMA_DONE));      // 使能DMA完成中断

  // 9. 启用ADC转换
  DL_ADC12_enableConversions(ADC12_0_INST);

  DL_DMA_setSrcAddr(DMA, DMA_CH0_CHAN_ID,
                    (uint32_t)DL_ADC12_getMemResultAddress(ADC12_0_INST, DL_ADC12_MEM_IDX_0));

  /* Setup interrupts on device */
  NVIC_EnableIRQ(ADC12_0_INST_INT_IRQN);

  ADC_DMA_FinishFlag = false;
}

void ADC_DMA_Convert(void)
{
  DL_DMA_disableChannel(DMA, DMA_CH0_CHAN_ID);
  DL_DMA_setDestAddr(DMA, DMA_CH0_CHAN_ID, (uint32_t)&ADCValue[0]);
  DL_DMA_setTransferSize(DMA, DMA_CH0_CHAN_ID, ADC_SAMPLE_SIZE);
  DL_DMA_enableChannel(DMA, DMA_CH0_CHAN_ID);
  DL_ADC12_enableDMA(ADC12_0_INST);
  DL_ADC12_startConversion(ADC12_0_INST);
  while (false == ADC_DMA_FinishFlag){}
  ADC_DMA_FinishFlag = false;
}

void ADC12_0_INST_IRQHandler(void)
{
    switch (DL_ADC12_getPendingInterrupt(ADC12_0_INST)) {
        case DL_ADC12_IIDX_DMA_DONE:
            ADC_DMA_FinishFlag = true;
            break;
        default:
            break;
    }
}