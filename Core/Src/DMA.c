#include "ti_msp_dl_config.h"
#include "DMA.h"
#include "Delay.h"

/* DMA通道0配置结构 */
static const DL_DMA_Config gDMA_CH0Config = {
    .transferMode   = DL_DMA_FULL_CH_REPEAT_SINGLE_TRANSFER_MODE, // 全通道重复单次传输模式
    .extendedMode   = DL_DMA_NORMAL_MODE,       // 普通模式（非扩展模式）
    .destIncrement  = DL_DMA_ADDR_INCREMENT,    // 目标地址递增（用于存储到数组）
    .srcIncrement   = DL_DMA_ADDR_UNCHANGED,    // 源地址不变（ADC结果寄存器固定）
    .destWidth      = DL_DMA_WIDTH_HALF_WORD,   // 目标数据宽度：16位（半字）
    .srcWidth       = DL_DMA_WIDTH_HALF_WORD,   // 源数据宽度：16位（半字）
    .trigger        = ADC12_0_INST_DMA_TRIGGER, // 触发源为ADC12_0的DMA触发
    .triggerType    = DL_DMA_TRIGGER_TYPE_EXTERNAL, // 外部触发类型
};

/* DMA通道0初始化函数 */
SYSCONFIG_WEAK void SYSCFG_DL_DMA_CH0_init(void)
{
    // 初始化DMA通道0
    DL_DMA_initChannel(DMA,                    // DMA控制器实例
                       DMA_CH0_CHAN_ID,        // 通道ID（通道0）
                       (DL_DMA_Config *) &gDMA_CH0Config); // 使用上述配置
}

/* DMA模块初始化入口函数 */
void DMA_init(void)
{
    // 调用通道0初始化（可扩展为多通道初始化）
    SYSCFG_DL_DMA_CH0_init();
}