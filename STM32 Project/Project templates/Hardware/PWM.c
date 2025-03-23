#include "stm32f10x.h"                  // Device header

//#define LED_PROT GPIOC
//#define LED_PIN GPIO_Pin_13
//#define LED_CON(x) GPIO_WriteBit(LED_PROT, LED_PIN, (BitAction)(x))

//void LED_LIGHT(int8_t TIME_PROT) // TIME_PROT -> 0~100
//{
//    uint8_t i;
//    TIME_PROT = TIME_PROT/5;
//    for(i=0; i< 20 ;i++)//单格1ms
//    {
//        if(i<TIME_PROT)
//        {
//            LED_CON(1);
//        }
//        else if(i>=TIME_PROT)
//        {
//            LED_CON(0);
//        }
//    }
//    
//}//实现对高低电平的占比控制




void PWM_Init(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    
    GPIO_InitTypeDef GPIO_Initstucture; //创建结构体
    GPIO_Initstucture.GPIO_Mode = GPIO_Mode_AF_PP; //复用输出模式
    GPIO_Initstucture.GPIO_Pin  = GPIO_Pin_0;
    GPIO_Initstucture.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_Initstucture);
    
    TIM_InternalClockConfig(TIM2);
    
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitstucture;
    TIM_TimeBaseInitstucture.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitstucture.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitstucture.TIM_Period = 100 -1;//ARR值设定
    TIM_TimeBaseInitstucture.TIM_Prescaler = 720 - 1;//PSC值
    TIM_TimeBaseInitstucture.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitstucture);
    
    TIM_OCInitTypeDef TMO_OCInitstucture;
    TIM_OCStructInit(&TMO_OCInitstucture);
    TMO_OCInitstucture.TIM_OCMode = TIM_OCMode_PWM1;
    TMO_OCInitstucture.TIM_OCPolarity = TIM_OCPolarity_High;
    TMO_OCInitstucture.TIM_OutputState = TIM_OutputState_Enable;
    TMO_OCInitstucture.TIM_Pulse = 0;
    TIM_OC1Init(TIM2,&TMO_OCInitstucture);
    
    TIM_Cmd(TIM2,ENABLE);//启动TIM2
}

void PWM1_set(uint8_t time)//动态改变RCC值
{
    TIM_SetCompare1(TIM2,time);
}

