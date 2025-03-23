#include "stm32f10x.h"                  // Device header

void GPIOA_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    //启动APB2总线时钟 激活GPIOA区
    GPIO_InitTypeDef GPIO_Initstucture; //创建结构体
    GPIO_Initstucture.GPIO_Mode = GPIO_Mode_IPU; //上拉输入模式
    GPIO_Initstucture.GPIO_Pin  = GPIO_Pin_0;
    GPIO_Initstucture.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_Initstucture);
    //初始化GPIOA-PIN13 为 开漏输出模式
}

void GPIOB_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
    //启动APB2总线时钟 激活GPIOC区
    GPIO_InitTypeDef GPIO_Initstucture; //创建结构体
    GPIO_Initstucture.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Initstucture.GPIO_Pin  = GPIO_Pin_13;
    GPIO_Initstucture.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&GPIO_Initstucture);
    //初始化GPIOB-PIN13 为 开漏输出模式
}

void GPIOC_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
    //启动APB2总线时钟 激活GPIOC区
    GPIO_InitTypeDef GPIO_Initstucture; //创建结构体
    GPIO_Initstucture.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Initstucture.GPIO_Pin  = GPIO_Pin_13;
    GPIO_Initstucture.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC,&GPIO_Initstucture);
    //初始化GPIOC-PIN13 为 开漏输出模式
}

void ALLGPIO_Init(void)
{
    GPIOA_Init();
    GPIOB_Init();
    GPIOC_Init();
}
