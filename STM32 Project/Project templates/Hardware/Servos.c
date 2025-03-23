#include "stm32f10x.h"                  // Device header

void Servos_Init(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    
    GPIO_InitTypeDef GPIO_Initstucture; //创建结构体
    GPIO_Initstucture.GPIO_Mode = GPIO_Mode_AF_PP; //复用输出模式
    GPIO_Initstucture.GPIO_Pin  = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;
    GPIO_Initstucture.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_Initstucture);
    
    TIM_InternalClockConfig(TIM2);
    
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitstucture;
    TIM_TimeBaseInitstucture.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitstucture.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitstucture.TIM_Period = 20000 -1;//ARR值设定
    TIM_TimeBaseInitstucture.TIM_Prescaler = 72- 1;//PSC值
    TIM_TimeBaseInitstucture.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitstucture);
    
    TIM_OCInitTypeDef TMO_OCInitstucture;
    TIM_OCStructInit(&TMO_OCInitstucture);
    TMO_OCInitstucture.TIM_OCMode = TIM_OCMode_PWM1;
    TMO_OCInitstucture.TIM_OCPolarity = TIM_OCPolarity_High;
    TMO_OCInitstucture.TIM_OutputState = TIM_OutputState_Enable;
    TMO_OCInitstucture.TIM_Pulse = 0;//初始的ARR值
    TIM_OC1Init(TIM2,&TMO_OCInitstucture);
    TIM_OC2Init(TIM2,&TMO_OCInitstucture);
    TIM_OC3Init(TIM2,&TMO_OCInitstucture);
    
    TIM_Cmd(TIM2,ENABLE);//启动TIM2
}


//ARR 为20000
//0.5 / 20 -> 2.5 / 20
//RCC 500->2500 对应舵机 -90°到90°

//处理完之后 0°-> RCC=500 180°-> RCC=2500

void wind_set(uint8_t time)//动态改变RCC值
{
    TIM_SetCompare1(TIM2,time * 200);
}

void Servos1_set(uint8_t time)//动态改变RCC值
{
    TIM_SetCompare2(TIM2,500+time*(2000/180));
}

void Servos2_set(uint8_t time)//动态改变RCC值
{
    TIM_SetCompare3(TIM2,500+time*(2000/180));
}
