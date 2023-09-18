#ifndef __USART_H__
#define __USART_H__

#include <stm32f10x.h>
#include <stdio.h>
#include <string.h>

// 定义缓冲区大小
#define BUFFER_SIZE 128

// 用于存储接收到的数据的缓冲区
extern uint8_t Rx_Buffer[BUFFER_SIZE];
extern char Data_Buffer[BUFFER_SIZE];

// 当前接收到的数据的索引
extern volatile uint8_t Rx_Index;
extern volatile uint8_t Data_Flag;

// 函数原型
void USART1_Config(void);
void NVIC_Configuration(void);
int fputc(int ch, FILE *f);

#endif
