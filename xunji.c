#include <stdio.h>
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "SysTick.h"
#include "car.h"
#include "xunji.h"

// 暂停标志：1 表示暂停，0 表示运行
static uint8_t is_paused = 0;

void XunOff(void)
{
    GPIO_InitTypeDef h;
    RCC_APB2PeriphClockCmd(XUNJI_GPIO_CLK, ENABLE);
    h.GPIO_Pin   = XUNJI_LEFT_PIN | XUNJI_RIGHT_PIN;
    h.GPIO_Mode  = GPIO_Mode_IPU;
    h.GPIO_Speed = GPIO_Speed_50MHz;
    
    GPIO_Init(XUNJI_PORT, &h);

    GPIO_SetBits(XUNJI_PORT, XUNJI_LEFT_PIN | XUNJI_RIGHT_PIN);
}

// 外部控制函数：暂停
void XunJi_Pause(void)
{
    is_paused = 1;
    Car_Stop(); // 立即停车[cite: 1, 2]
}

// 外部控制函数：继续/启动
void XunJi_Resume(void)
{
    is_paused = 0;
}

// 外部控制函数：一键切换（常用于按键触发）
void XunJi_TogglePause(void)
{
    if (is_paused)
    {
        XunJi_Resume();
    }
    else
    {
        XunJi_Pause();
    }
}

// 获取当前运行状态
uint8_t XunJi_IsPaused(void)
{
    return is_paused;
}

void XunJi(void)
{
    // 如果处于暂停状态，保持停车并直接返回
    if (is_paused)
    {
        Car_Stop(); //[cite: 1, 2]
        return;
    }

    static uint8_t Lastturn = 0;
    static uint8_t Turnlefttime = 0;
    static uint8_t Turnrighttime = 0;

    uint8_t left_val  = GPIO_ReadInputDataBit(XUNJI_PORT, XUNJI_LEFT_PIN);
    uint8_t right_val = GPIO_ReadInputDataBit(XUNJI_PORT, XUNJI_RIGHT_PIN);

    // 两侧脱线（均为白色区域 1）
    if (left_val == 1 && right_val == 1)
    {
        Turnlefttime = 0;
        Turnrighttime = 0;

        if (Lastturn == 1)
        {
            Car_SpinAroundFront_Left(); //[cite: 1, 2]
            Delay_ms(150);
            Turnlefttime++;
        }
        else if (Lastturn == 2)
        {
            Car_SpinAroundFront_Right(); //[cite: 1, 2]
            Delay_ms(150);
            Turnrighttime++;
        }
        else if (Turnlefttime >= 3)
        {
            Car_RotateLeft(); //[cite: 1, 2]
            Delay_ms(50);
        }
        else if (Turnrighttime >= 3)
        {
            Car_RotateRight(); //[cite: 1, 2]
            Delay_ms(50);
        }
        else
        {
            Car_Stop(); //[cite: 1, 2]
        }
        return;
    }

    // 两侧检测到黑线（均为 0）：前进
    if (left_val == 0 && right_val == 0)
    {
        Car_MoveForward(); //[cite: 1, 2]
        Lastturn = 0;
        Turnlefttime = 0;
        Turnrighttime = 0;
    }
    // 偏右（左 0 右 1）：左转修正
    else if (left_val == 0 && right_val == 1)
    {
        Car_RotateLeft(); //[cite: 1, 2]
        Delay_ms(50);
        Lastturn = 1;
    }
    // 偏左（左 1 右 0）：右转修正
    else if (left_val == 1 && right_val == 0)
    {
        Car_RotateRight(); //[cite: 1, 2]
        Delay_ms(50);
        Lastturn = 2;
    }
}