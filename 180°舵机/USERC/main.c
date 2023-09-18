#include "stm32f10x.h"
#include <stdio.h>
#include <stdlib.h>
#include "SysTick.h"
#include "Usart.h"
#include "PWM.h"

#pragma  diag_suppress 870 //禁止编译出现870警告 这个警告是因为我的printf()函数有中文

int main(void)
{
    USART1_Config();//串口初始化
	NVIC_Configuration();//串口中断初始化
	TIM3_PWM_Init();//定时器PWM输出初始化(TIM3_CH1)  舵机信号线接PB4
	
	printf("***************Hardware Wiring***************\n");
	printf("舵机(180°)	<------->	STM32F103C8T6\n");
	printf("VCC(红色)	<------->	5V\n");
	printf("SIG(黄色)	<------->	PB4\n");
	printf("GND(褐色)	<------->	GND\n");
	printf("*****************Servo  Test*****************\n");
	printf("波特率默认设置：115200\n");
	printf("数据格式参考:$120#\n");
	printf("数据头:$\n");
	printf("数据(舵机转动角度):120\n");
	printf("数据尾:#\n");
	printf("注意:请务必按照格式发送数据测试！！！\n");
	printf("*********************************************\n");

	while(1)
	{
		if(Data_Flag == 1)
		{
			int Servo_Degree = strtol(Data_Buffer, NULL, 10);//将数组中的数据转换成整数
//			printf("%s\n",Data_Buffer);//打印数组中的字符串
			printf("舵机目前角度 = %d°\n",Servo_Degree);//打印转化后的数据
			Degree_Conv_PWM(Servo_Degree);//控制舵机旋转角度
			Data_Flag = 0;//标志位重置
			memset(Data_Buffer, 0, sizeof(Data_Buffer));//清除数组中的数据
		}
	}
}
