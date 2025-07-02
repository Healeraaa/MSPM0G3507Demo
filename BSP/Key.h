#ifndef __KEY_H
#define __KEY_H

#include "stdint.h"

#define KEY_NUM 5            // 按键数量
#define KEY_DEBOUNCE_TICKS 2 // 1*WWDT周期 = 消抖时间

// 按键检测状态枚举，用于状态机控制流程
typedef enum
{
    KEY_STATE_IDLE,            // 空闲状态，等待按键按下
    KEY_STATE_DEBOUNCE_PRESS,  // 检测到按下，开始第一次消抖
    KEY_STATE_WAIT_RELEASE,    // 按下确认后，等待松开
    KEY_STATE_DEBOUNCE_RELEASE // 松开后进行第二次消抖
} KeyState;

// 按键结构体
typedef struct
{
    KeyState state;
    uint8_t FiltCounter;
    uint8_t flag;    // 是否产生有效事件
    uint32_t pinMux; // 引脚掩码
    GPIO_Regs *port; // 引脚所属 GPIO 端口
    uint32_t pins;    // 引脚所在的Pin
} KeyInfo;



void Key_Init(void);
void Key_Update(void);
uint8_t Key_GetNum(void);

#endif
