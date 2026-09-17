#include "stm32f10x.h"
#include "SysTick.h"
#include "car.h"
#include "xunji.h"

int main(void)
{
    // 1. 硬件初始化
    Car_Init();
    XunOff();

    // 2. 上电静止延时，留足时间把小车平稳放在起点
    Car_Stop();
    Delay_ms(800);

    // 3. 循迹运行，直到遇到终点
    while (1)
    {
        if (XunJi() == 0)
        {
            Car_Stop(); // 到达终点刹停
            break;
        }
    }

    // 4. 终点待机锁定
    while (1)
    {
        Car_Stop();
        Delay_ms(200);
    }
}