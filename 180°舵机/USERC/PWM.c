#include "PWM.h"

void TIM3_PWM_Init(void)//定时器PWM输出初始化(TIM3_CH1)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    /* TIM3 clock enable */
    /* TIM3 时钟使能 */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

    /* GPIOB and AFIO clock enable */
    /* 使能GPIOB端口时钟和AFIO时钟 */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);

    /*GPIOB Configuration: TIM3 channel1 */
    /* PB4配置复用推挽输出模式 */
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    
    /* JTAG-DP Disabled and SW-DP Enabled */
    /* 禁用JTAG 启用SWD */
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
    /* 把TIM3_CH1部分映射到PB4引脚上 */
	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);     

    /* Time base configuration */
    /* 定时计数器配置 50HZ*/
    TIM_TimeBaseStructure.TIM_Period = 20000 - 1;//舵机控制脉冲周期20ms 对应20000us
    TIM_TimeBaseStructure.TIM_Prescaler = 72 - 1;//72MHz / 72 =1MHz 1
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

    /* PWM1 Mode configuration: Channel1 */
    /* PWM1 模式配置：TIM3_CH1 */
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;//PWM模式1
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//PWM输出使能
    TIM_OCInitStructure.TIM_Pulse = 0;//设置比较值 决定占空比
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;//有效电平 高电平
    TIM_OC1Init(TIM3, &TIM_OCInitStructure);
    
    /* 使能预装载寄存器 */
    TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
    
    /* 使能自动重装载寄存器 */
    TIM_ARRPreloadConfig(TIM3, ENABLE);

    /* TIM3 enable counter */
    /* 使能TIM3计数 */
    TIM_Cmd(TIM3, ENABLE);
}

//度数转换
void Degree_Conv_PWM(int Servo_Degree)
{
	float PWM_Time;
	PWM_Time = (2000.0 * (Servo_Degree / 180.0)) + 500;
	TIM_SetCompare1(TIM3, (int)PWM_Time);//定时器设置比较值函数和通道有关 时间参数单位是us
}
