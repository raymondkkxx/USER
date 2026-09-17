#include "key.h"
#include "SysTick.h"

void Key_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(KEY_GPIO_CLK, ENABLE);

    // 配置 PB0(P20) 和 PB1(P21) 为上拉输入 (默认高电平，按下为低电平)
    GPIO_InitStructure.GPIO_Pin   = KEY_P20_FORWARD_PIN | KEY_P21_BACKWARD_PIN;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU; 
    GPIO_Init(KEY_PORT, &GPIO_InitStructure);
}

// 实时获取按键状态（不阻塞、不等待松手）
uint8_t Key_Scan(void)
{
    // 检测 P20 是否按下（低电平）
    if (GPIO_ReadInputDataBit(KEY_PORT, KEY_P20_FORWARD_PIN) == RESET)
    {
        return KEY_FORWARD;
    }
    // 检测 P21 是否按下（低电平）
    else if (GPIO_ReadInputDataBit(KEY_PORT, KEY_P21_BACKWARD_PIN) == RESET)
    {
        return KEY_BACKWARD;
    }

    return KEY_NONE; // 无按键按下
}