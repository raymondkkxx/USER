#ifndef __CAR_H__
#define __CAR_H__

#include "stm32f10x.h"

// GPIO 引脚定义
#define MOTOR_PORT          GPIOA
#define MOTOR_GPIO_CLK      RCC_APB2Periph_GPIOA

#define MOTOR_A1_PIN        GPIO_Pin_0
#define MOTOR_A2_PIN        GPIO_Pin_1
#define MOTOR_B1_PIN        GPIO_Pin_2
#define MOTOR_B2_PIN        GPIO_Pin_3
#define MOTOR_C1_PIN        GPIO_Pin_4
#define MOTOR_C2_PIN        GPIO_Pin_5
#define MOTOR_D1_PIN        GPIO_Pin_6
#define MOTOR_D2_PIN        GPIO_Pin_7

// 初始化
void Car_Init(void);

// 单轮控制
void Motor_LF_Forward(void);
void Motor_LF_Backward(void);
void Motor_LF_Stop(void);

void Motor_RF_Forward(void);
void Motor_RF_Backward(void);
void Motor_RF_Stop(void);

void Motor_LR_Forward(void);
void Motor_LR_Backward(void);
void Motor_LR_Stop(void);

void Motor_RR_Forward(void);
void Motor_RR_Backward(void);
void Motor_RR_Stop(void);

// 运动控制 API
void Car_Stop(void);
void Car_MoveForward(void);
void Car_MoveBackward(void);
void Car_MoveLeft(void);
void Car_MoveRight(void);
void Car_RotateLeft(void);
void Car_RotateRight(void);
void Car_MoveDiagonalLeftForward(void);
void Car_MoveDiagonalRightForward(void);
void Car_MoveDiagonalLeftBackward(void);
void Car_MoveDiagonalRightBackward(void);
void Car_SpinAroundFront_Left(void);
void Car_SpinAroundFront_Right(void);
void Car_SpinAroundRear_Left(void);
void Car_SpinAroundRear_Right(void);

#endif /* __CAR_H__ */
