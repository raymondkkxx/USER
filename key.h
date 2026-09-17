#ifndef __KEY_H__
#define __KEY_H__

#include "stm32f10x.h"

// GPIO 引脚定义：GPIOB Pin 0 和 Pin 1 
#define KEY_PORT          GPIOB
#define KEY_GPIO_CLK      RCC_APB2Periph_GPIOB

#define KEY_P20_FORWARD_PIN   GPIO_Pin_0   
#define KEY_P21_BACKWARD_PIN  GPIO_Pin_1   
// 按键返回值定义
#define KEY_NONE          0
#define KEY_FORWARD       1   // 前进按键触发
#define KEY_BACKWARD      2   // 后退按键触发

// 函数声明
void Key_Init(void);
uint8_t Key_Scan(void);

#endif /* __KEY_H__ */

