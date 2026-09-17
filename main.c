#include "stm32f10x.h"
#include "SysTick.h"
#include "car.h" //[cite: 2]
#include "xunji.h"

int main(void)
{
    Car_Init(); //[cite: 1, 2]
    XunOff();
    Car_Stop(); // 初始保持静止[cite: 1, 2]
    Delay_ms(500);

    // 如果希望上电先处于暂停状态，按下按键再开始：
    // XunJi_Pause();

    while (1)
    {
        /* 示例：如果你有一个按键接在 PA8，可以通过按键切换暂停 */
        /*
        if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_8) == 0)
        {
            Delay_ms(20); // 按键消抖
            if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_8) == 0)
            {
                XunJi_TogglePause();
                while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_8) == 0); // 等待松手
            }
        }
        */

        XunJi();
    }
}