#include "car.h"

// 硬件初始化
void Car_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(MOTOR_GPIO_CLK, ENABLE);

    GPIO_InitStructure.GPIO_Pin = MOTOR_A1_PIN | MOTOR_A2_PIN |
                                  MOTOR_B1_PIN | MOTOR_B2_PIN |
                                  MOTOR_C1_PIN | MOTOR_C2_PIN |
                                  MOTOR_D1_PIN | MOTOR_D2_PIN;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(MOTOR_PORT, &GPIO_InitStructure);

    GPIO_ResetBits(MOTOR_PORT, GPIO_InitStructure.GPIO_Pin);
}

// =================== 底层单轮驱动（极性已校正） ===================

// 左前轮 (C)
void Motor_LF_Forward(void)
{
    GPIO_SetBits(MOTOR_PORT, MOTOR_C1_PIN);
    GPIO_ResetBits(MOTOR_PORT, MOTOR_C2_PIN);
}

void Motor_LF_Backward(void)
{
    GPIO_ResetBits(MOTOR_PORT, MOTOR_C1_PIN);
    GPIO_SetBits(MOTOR_PORT, MOTOR_C2_PIN);
}

void Motor_LF_Stop(void)
{
    GPIO_ResetBits(MOTOR_PORT, MOTOR_C1_PIN | MOTOR_C2_PIN);
}

// 右前轮 (B)
void Motor_RF_Forward(void)
{
    GPIO_ResetBits(MOTOR_PORT, MOTOR_B1_PIN);
    GPIO_SetBits(MOTOR_PORT, MOTOR_B2_PIN);
}

void Motor_RF_Backward(void)
{
    GPIO_SetBits(MOTOR_PORT, MOTOR_B1_PIN);
    GPIO_ResetBits(MOTOR_PORT, MOTOR_B2_PIN);
}

void Motor_RF_Stop(void)
{
    GPIO_ResetBits(MOTOR_PORT, MOTOR_B1_PIN | MOTOR_B2_PIN);
}

// 左后轮 (D)
void Motor_LR_Forward(void)
{
    GPIO_SetBits(MOTOR_PORT, MOTOR_D1_PIN);
    GPIO_ResetBits(MOTOR_PORT, MOTOR_D2_PIN);
}

void Motor_LR_Backward(void)
{
    GPIO_ResetBits(MOTOR_PORT, MOTOR_D1_PIN);
    GPIO_SetBits(MOTOR_PORT, MOTOR_D2_PIN);
}

void Motor_LR_Stop(void)
{
    GPIO_ResetBits(MOTOR_PORT, MOTOR_D1_PIN | MOTOR_D2_PIN);
}

// 右后轮 (A)
void Motor_RR_Forward(void)
{
    GPIO_SetBits(MOTOR_PORT, MOTOR_A1_PIN);
    GPIO_ResetBits(MOTOR_PORT, MOTOR_A2_PIN);
}

void Motor_RR_Backward(void)
{
    GPIO_ResetBits(MOTOR_PORT, MOTOR_A1_PIN);
    GPIO_SetBits(MOTOR_PORT, MOTOR_A2_PIN);
}

void Motor_RR_Stop(void)
{
    GPIO_ResetBits(MOTOR_PORT, MOTOR_A1_PIN | MOTOR_A2_PIN);
}

// 刹车
void Car_Stop(void)
{
    Motor_LF_Stop();
    Motor_RF_Stop();
    Motor_LR_Stop();
    Motor_RR_Stop();
}

// =================== 整车动作控制 ===================

void Car_MoveForward(void)
{
    Motor_LF_Forward();
    Motor_RF_Forward();
    Motor_LR_Forward();
    Motor_RR_Forward();
}

void Car_MoveBackward(void)
{
    Motor_LF_Backward();
    Motor_RF_Backward();
    Motor_LR_Backward();
    Motor_RR_Backward();
}

void Car_MoveLeft(void)
{
    Motor_LF_Backward();
    Motor_RF_Forward();
    Motor_LR_Forward();
    Motor_RR_Backward();
}

void Car_MoveRight(void)
{
    Motor_LF_Forward();
    Motor_RF_Backward();
    Motor_LR_Backward();
    Motor_RR_Forward();
}

void Car_RotateLeft(void)
{
    Motor_LF_Backward();
    Motor_RF_Forward();
    Motor_LR_Backward();
    Motor_RR_Forward();
}

void Car_RotateRight(void)
{
    Motor_LF_Forward();
    Motor_RF_Backward();
    Motor_LR_Forward();
    Motor_RR_Backward();
}

void Car_MoveDiagonalLeftForward(void)
{
    Motor_LF_Forward();
    Motor_RF_Stop();
    Motor_LR_Stop();
    Motor_RR_Forward();
}

void Car_MoveDiagonalRightForward(void)
{
    Motor_LF_Stop();
    Motor_RF_Forward();
    Motor_LR_Forward();
    Motor_RR_Stop();
}

void Car_MoveDiagonalLeftBackward(void)
{
    Motor_LF_Stop();
    Motor_RF_Backward();
    Motor_LR_Backward();
    Motor_RR_Stop();
}

void Car_MoveDiagonalRightBackward(void)
{
    Motor_LF_Backward();
    Motor_RF_Stop();
    Motor_LR_Stop();
    Motor_RR_Backward();
}

void Car_SpinAroundFront_Left(void)
{
    Motor_LF_Stop();
    Motor_RF_Stop();
    Motor_LR_Backward();
    Motor_RR_Backward();
}

void Car_SpinAroundFront_Right(void)
{
    Motor_LF_Stop();
    Motor_RF_Stop();
    Motor_LR_Forward();
    Motor_RR_Forward();
}

void Car_SpinAroundRear_Left(void)
{
    Motor_LF_Backward();
    Motor_RF_Backward();
    Motor_LR_Stop();
    Motor_RR_Stop();
}

void Car_SpinAroundRear_Right(void)
{
    Motor_LF_Forward();
    Motor_RF_Forward();
    Motor_LR_Stop();
    Motor_RR_Stop();
}