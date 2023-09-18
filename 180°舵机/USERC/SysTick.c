#include "SysTick.h"

void Delay_us(uint16_t us)
{
	SysTick->CTRL =  0;// 将SysTick控制寄存器清零，停止SysTick定时器
	SysTick->LOAD =  72*us - 1;// 设置SysTick加载寄存器的值，确定延时的时间
	SysTick->VAL =  0;// 将SysTick当前值寄存器清零
	SysTick->CTRL =  5;// 设置SysTick控制寄存器，使其开始倒数计数，并启用SysTick定时器
	while((SysTick->CTRL & 0x00010000) == 0);// 等待SysTick定时器倒数完成
	SysTick->CTRL =  0;// 再次将SysTick控制寄存器清零，停止SysTick定时器
}

void Delay_ms(uint16_t ms)
{
	while(ms--)
	{
		SysTick->CTRL =  0;
		SysTick->LOAD =  72000 - 1;
		SysTick->VAL =  0;
		SysTick->CTRL =  5;
		while((SysTick->CTRL & 0x00010000) == 0);
		SysTick->CTRL =  0;
	}
}

void Delay_s(uint16_t s)
{
	while(s--)
	{
		Delay_ms(1000);
	}
}
