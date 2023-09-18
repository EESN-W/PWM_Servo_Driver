#include "Usart.h"

uint8_t Rx_Buffer[BUFFER_SIZE];
char Data_Buffer[BUFFER_SIZE];

volatile uint8_t Rx_Index = 0;
volatile uint8_t Data_Flag = 0;

void USART1_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;

    // 使能USART1和GPIOA时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);

    // 配置USART1引脚
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;    // USART1_TX
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;    // 复用推挽输出
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;    // USART1_RX
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;    // 浮空输入
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // 配置USART1
    USART_InitStructure.USART_BaudRate = 115200;    // 波特率为115200
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;    // 数据位长度为8位
    USART_InitStructure.USART_StopBits = USART_StopBits_1;    // 停止位为1位
    USART_InitStructure.USART_Parity = USART_Parity_No;    // 无奇偶校验
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;    // 无硬件流控制
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;    // 同时启用接收和发送模式
    USART_Init(USART1, &USART_InitStructure);

    // 使能USART1接收中断
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

    // 使能USART1
    USART_Cmd(USART1, ENABLE);
}

void NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    // 配置USART1中断向量
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

int fputc(int ch, FILE *f)
{
    // 发送一个字符到USART1
    USART_SendData(USART1, (uint16_t)ch);

    // 等待发送完成
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);

    return ch;
}

void USART1_IRQHandler(void)
{
    if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{
        // 从串口接收数据到缓冲区
        Rx_Buffer[Rx_Index] = USART_ReceiveData(USART1);
		
		// 如果数据是以$开头则开始存储数据
		if(Rx_Buffer[Rx_Index] == '$')
		{
			// 清空接收缓冲区
            memset(Rx_Buffer, 0, sizeof(Rx_Buffer));
			Rx_Buffer[0] = '$';
			Rx_Index = 1;
		}
		// 如果数据是以#结尾则结束数据存储并打印数据信息
		else if(Rx_Buffer[Rx_Index] == '#' && Rx_Buffer[0] == '$')
		{
			// 打印接收到的数据
            printf("Received: %s\n", Rx_Buffer);
			
			// 使用memcpy函数进行数组内容复制
			memcpy(Data_Buffer, Rx_Buffer + 1, 3);
			
            // 清空接收缓冲区
            memset(Rx_Buffer, 0, sizeof(Rx_Buffer));
			
            // 重置索引
            Rx_Index = 0;
			Data_Flag = 1;
		}
		else
		{
			// 增加索引，准备接收下一个字符
            Rx_Index++;
		}
    }
}
