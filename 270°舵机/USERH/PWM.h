#ifndef __PWM_H__
#define __PWM_H__

#include "stm32f10x.h"

void TIM3_PWM_Init(void);//定时器PWM输出初始化(TIM3_CH1)
void Degree_Conv_PWM(int Servo_Degree);//度数转换成PWM

#endif
