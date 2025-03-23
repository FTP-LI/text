#include "stm32f10x.h"                  // Device header
#include <stdio.h>
#include <stdarg.h>

uint8_t UART_RXFlag;
uint8_t UART_RXData;

void UART_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
    
    GPIO_InitTypeDef GPIO_Initstucture; //创建结构体
    GPIO_Initstucture.GPIO_Mode = GPIO_Mode_AF_PP; //复用输出模式
    GPIO_Initstucture.GPIO_Pin  = GPIO_Pin_9;
    GPIO_Initstucture.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_Initstucture);//初始化PA9 TX
    
    GPIO_Initstucture.GPIO_Mode = GPIO_Mode_IPU; //上拉输入模式
    GPIO_Initstucture.GPIO_Pin  = GPIO_Pin_10 ;
    GPIO_Initstucture.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_Initstucture);//初始化PA10 RX
    
    USART_InitTypeDef USART_Initstucture;
    USART_Initstucture.USART_BaudRate = 9600;//设置波特率
    USART_Initstucture.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//不使用流控制器
    USART_Initstucture.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //同时启用接收和发送
    USART_Initstucture.USART_Parity = USART_Parity_No;//不使用校验位
    USART_Initstucture.USART_StopBits = USART_StopBits_1;//设置为一位停止位
    USART_Initstucture.USART_WordLength = USART_WordLength_8b;//设置字长为8位
    USART_Init(USART1,&USART_Initstucture);
    
    USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);//启用USART1 接收中断
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);//设置中断优先级
    
    NVIC_InitTypeDef NVIC_Initstucture;
    NVIC_Initstucture.NVIC_IRQChannel = USART1_IRQn;//设置中断通道为USART1
    NVIC_Initstucture.NVIC_IRQChannelCmd = ENABLE;//判断是否为内部中断通道
    NVIC_Initstucture.NVIC_IRQChannelPreemptionPriority = 1;//设置抢占优先级
    NVIC_Initstucture.NVIC_IRQChannelSubPriority = 1;//设置次优先级
    NVIC_Init(&NVIC_Initstucture);
    
    USART_Cmd(USART1,ENABLE);//启用USART1
}

    void UART_Sendbyte(uint16_t Byte)//发送单一字节
{
    USART_SendData(USART1,Byte);//发送数据
    while (USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);//等待发送完成
}

void UART_SendArray(uint16_t *Array,uint16_t Lenght)//发送数组
{
    uint16_t i;
    for(i = 0;i < Lenght;i++)
    {
        UART_Sendbyte(Array[i]);
    }
}

void UART_SendString(char *String)//发送字符串
{
    uint8_t i;
    for(i = 0;String[i] != '\0';i++)
    {       
        UART_Sendbyte(String[i]);
    }
}

uint32_t Uart_Pow(uint16_t x,uint16_t y)//x是基数 y是次数
{
    uint32_t Result = 1;
    while(y--)
    {
        Result *= x;
    }
    return Result;
}

void UART_SendNumber(uint32_t Number,uint8_t Lenght)//发送数字
{
    uint8_t i;
    for(i = 0;i < Lenght;i++)
    {
        UART_Sendbyte((Number / Uart_Pow(10,Lenght -i-1))%10 + '0' );
    }
}

void UART_Printf(char *format,  ...)//覆写printf函数
{
    char Sting[100];
    va_list arg;
    va_start ( arg, format);
    vsprintf( Sting, format, arg);
    va_end(arg);
    UART_SendString(Sting);
}

uint8_t UART_GetRXFlag(void)//获取接受标志位，并重装
{
    if(UART_RXFlag == 1)
    {
        UART_RXFlag = 0;//重装
        return 1;
    }
    return 0;
}

uint8_t UART_GetRxData(void)//获取接受到的数据
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





    







