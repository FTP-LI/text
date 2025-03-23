#include "stm32f10x.h"                  // Device header
#include <stdio.h>
#include <stdarg.h>

uint8_t UART_RXFlag;
uint8_t UART_RXData;

void UART_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
    
    GPIO_InitTypeDef GPIO_Initstucture; //�����ṹ��
    GPIO_Initstucture.GPIO_Mode = GPIO_Mode_AF_PP; //�������ģʽ
    GPIO_Initstucture.GPIO_Pin  = GPIO_Pin_9;
    GPIO_Initstucture.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_Initstucture);//��ʼ��PA9 TX
    
    GPIO_Initstucture.GPIO_Mode = GPIO_Mode_IPU; //��������ģʽ
    GPIO_Initstucture.GPIO_Pin  = GPIO_Pin_10 ;
    GPIO_Initstucture.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_Initstucture);//��ʼ��PA10 RX
    
    USART_InitTypeDef USART_Initstucture;
    USART_Initstucture.USART_BaudRate = 9600;//���ò�����
    USART_Initstucture.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��ʹ����������
    USART_Initstucture.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //ͬʱ���ý��պͷ���
    USART_Initstucture.USART_Parity = USART_Parity_No;//��ʹ��У��λ
    USART_Initstucture.USART_StopBits = USART_StopBits_1;//����Ϊһλֹͣλ
    USART_Initstucture.USART_WordLength = USART_WordLength_8b;//�����ֳ�Ϊ8λ
    USART_Init(USART1,&USART_Initstucture);
    
    USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);//����USART1 �����ж�
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);//�����ж����ȼ�
    
    NVIC_InitTypeDef NVIC_Initstucture;
    NVIC_Initstucture.NVIC_IRQChannel = USART1_IRQn;//�����ж�ͨ��ΪUSART1
    NVIC_Initstucture.NVIC_IRQChannelCmd = ENABLE;//�ж��Ƿ�Ϊ�ڲ��ж�ͨ��
    NVIC_Initstucture.NVIC_IRQChannelPreemptionPriority = 1;//������ռ���ȼ�
    NVIC_Initstucture.NVIC_IRQChannelSubPriority = 1;//���ô����ȼ�
    NVIC_Init(&NVIC_Initstucture);
    
    USART_Cmd(USART1,ENABLE);//����USART1
}

    void UART_Sendbyte(uint16_t Byte)//���͵�һ�ֽ�
{
    USART_SendData(USART1,Byte);//��������
    while (USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);//�ȴ��������
}

void UART_SendArray(uint16_t *Array,uint16_t Lenght)//��������
{
    uint16_t i;
    for(i = 0;i < Lenght;i++)
    {
        UART_Sendbyte(Array[i]);
    }
}

void UART_SendString(char *String)//�����ַ���
{
    uint8_t i;
    for(i = 0;String[i] != '\0';i++)
    {       
        UART_Sendbyte(String[i]);
    }
}

uint32_t Uart_Pow(uint16_t x,uint16_t y)//x�ǻ��� y�Ǵ���
{
    uint32_t Result = 1;
    while(y--)
    {
        Result *= x;
    }
    return Result;
}

void UART_SendNumber(uint32_t Number,uint8_t Lenght)//��������
{
    uint8_t i;
    for(i = 0;i < Lenght;i++)
    {
        UART_Sendbyte((Number / Uart_Pow(10,Lenght -i-1))%10 + '0' );
    }
}

void UART_Printf(char *format,  ...)//��дprintf����
{
    char Sting[100];
    va_list arg;
    va_start ( arg, format);
    vsprintf( Sting, format, arg);
    va_end(arg);
    UART_SendString(Sting);
}

uint8_t UART_GetRXFlag(void)//��ȡ���ܱ�־λ������װ
{
    if(UART_RXFlag == 1)
    {
        UART_RXFlag = 0;//��װ
        return 1;
    }
    return 0;
}

uint8_t UART_GetRxData(void)//��ȡ���ܵ�������
{
    return UART_RXData;
}    

void USART1_IRQHandler(void)
{
    if(USART_GetFlagStatus(USART1,USART_FLAG_RXNE) == SET)
    {
        UART_RXData = USART_ReceiveData(USART1);
        UART_RXFlag = 1;
        USART_ClearITPendingBit(USART1,USART_FLAG_RXNE);
    }
}





    







