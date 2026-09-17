
#include "car.h"
#include "xunji.h"

int main(void)
{
    /* 1. 外设硬件初始化（注意：本工程无需单独调用 SysTick_Init） */
    Car_Init();
    XunOff();

    /* 2. 上电保护：开机先刹车静止 500ms */
    Car_Stop();
    Delay_ms(500);

    /* 3. 循迹主控制流：检测到终点时退出循环 */
    while (1)
    {
        if (XunJi() == 0)
        {
            Car_Stop();
            break; // 到达 T 字路口终点，退出巡线
        }
    }

    /* 4. 终点安全锁定：小车永久保持停车状态 */
    while (1)
    {
        Car_Stop();
        Delay_ms(200);
    }
}