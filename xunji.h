#ifndef __XUNJI_H__
#define __XUNJI_H__

#include "stm32f10x.h"

/* 巡线传感器 GPIO 端口与引脚定义 */
#define XUNJI_GPIO_CLK       RCC_APB2Periph_GPIOB
#define XUNJI_PORT           GPIOB
#define XUNJI_LEFT_PIN       GPIO_Pin_0    // 左侧红外循迹传感器
#define XUNJI_RIGHT_PIN      GPIO_Pin_1    // 右侧红外循迹传感器

/* 函数声明 */
void XunOff(void);           // 巡线传感器引脚初始化
void XunJi(void);            // 循迹核心处理逻辑

/* 暂停控制接口 */
void XunJi_Pause(void);      // 暂停循迹并停车
void XunJi_Resume(void);     // 恢复循迹
void XunJi_TogglePause(void);// 切换 暂停/运行 状态
uint8_t XunJi_IsPaused(void);// 获取当前是否处于暂停状态 (1: 暂停, 0: 运行)

#endif /* __XUNJI_H__ */