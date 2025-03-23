#include "stm32f10x.h"                  // Device header

void GPIOA_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    //����APB2����ʱ�� ����GPIOA��
    GPIO_InitTypeDef GPIO_Initstucture; //�����ṹ��
    GPIO_Initstucture.GPIO_Mode = GPIO_Mode_IPU; //��������ģʽ
    GPIO_Initstucture.GPIO_Pin  = GPIO_Pin_0;
    GPIO_Initstucture.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_Initstucture);
    //��ʼ��GPIOA-PIN13 Ϊ ��©���ģʽ
}

void GPIOB_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
    //����APB2����ʱ�� ����GPIOC��
    GPIO_InitTypeDef GPIO_Initstucture; //�����ṹ��
    GPIO_Initstucture.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Initstucture.GPIO_Pin  = GPIO_Pin_13;
    GPIO_Initstucture.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&GPIO_Initstucture);
    //��ʼ��GPIOB-PIN13 Ϊ ��©���ģʽ
}

void GPIOC_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
    //����APB2����ʱ�� ����GPIOC��
    GPIO_InitTypeDef GPIO_Initstucture; //�����ṹ��
    GPIO_Initstucture.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Initstucture.GPIO_Pin  = GPIO_Pin_13;
    GPIO_Initstucture.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC,&GPIO_Initstucture);
    //��ʼ��GPIOC-PIN13 Ϊ ��©���ģʽ
}

void ALLGPIO_Init(void)
{
    GPIOA_Init();
    GPIOB_Init();
    GPIOC_Init();
}
