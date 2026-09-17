#include "xunji.h"
#include "car.h"
#include "SysTick.h"

// 传感器引脚初始化
void XunOff(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(XUNJI_GPIO_CLK, ENABLE);

    GPIO_InitStructure.GPIO_Pin   = XUNJI_LEFT_PIN | XUNJI_RIGHT_PIN;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU; // 内部上拉输入
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(XUNJI_PORT, &GPIO_InitStructure);

    GPIO_SetBits(XUNJI_PORT, XUNJI_LEFT_PIN | XUNJI_RIGHT_PIN);
}

/**
 * @brief  单步循迹逻辑处理
 * @note   标准红外模块特性：白底反光输出 0，黑线/虚空无反光输出 1
 * @retval 0: 到达 T 字路口终点已停下
 *         1: 正常巡线中
 */
uint8_t XunJi(void)
{
    // 起跑计数器：前 30 次循环（约 1 秒）不检测终点，防止刚放地上时手抖误判
    static uint16_t start_protect_count = 0;

    uint8_t left_val  = GPIO_ReadInputDataBit(XUNJI_PORT, XUNJI_LEFT_PIN);
    uint8_t right_val = GPIO_ReadInputDataBit(XUNJI_PORT, XUNJI_RIGHT_PIN);

    /* 1. T字路口终点检测：两边探头同时压到横向黑线 (1, 1) */
    if (left_val == 1 && right_val == 1)
    {
        if (start_protect_count >= 30) // 必须脱离起跑缓冲期后才判定终点
        {
            // 延时 30ms 进行二次确认消抖
            Delay_ms(30);
            left_val  = GPIO_ReadInputDataBit(XUNJI_PORT, XUNJI_LEFT_PIN);
            right_val = GPIO_ReadInputDataBit(XUNJI_PORT, XUNJI_RIGHT_PIN);

            if (left_val == 1 && right_val == 1)
            {
                Car_Stop(); // 确认为终点横向黑色胶带，停车
                return 0;   // 返回终点信号
            }
        }
    }

    if (start_protect_count < 30)
    {
        start_protect_count++;
    }

    /* 2. 偏左（右探头压黑线 1，左探头在白底 0）：向右修正 */
    if (left_val == 0 && right_val == 1)
    {
        Car_RotateRight();
        Delay_ms(25);
    }
    /* 3. 偏右（左探头压黑线 1，右探头在白底 0）：向左修正 */
    else if (left_val == 1 && right_val == 0)
    {
        Car_RotateLeft();
        Delay_ms(25);
    }
    /* 4. 正常居中（两侧均在白底 0，黑线在两探头之间）：全速直行 */
    else if (left_val == 0 && right_val == 0)
    {
        Car_MoveForward();
    }

    return 1; // 正常循迹中
}