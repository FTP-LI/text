#include "stm32f10x.h"                  // Device header

#define CLK     GPIO_Pin_5  //时钟先
#define MOIS    GPIO_Pin_7  //主机输出线/从机输入线
#define MISO    GPIO_Pin_6  //从机输出线/主机输入线
#define SS      GPIO_Pin_4  //片选

#define SPI1_W_SS(x)		GPIO_WriteBit(GPIOA, SS, (BitAction)(x))


void SPI1_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,ENABLE);
    
    GPIO_InitTypeDef GPIO_Initstucture; //创建结构体
    GPIO_Initstucture.GPIO_Mode = GPIO_Mode_Out_PP;//推挽输出模式 
    GPIO_Initstucture.GPIO_Pin  = SS;
    GPIO_Initstucture.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_Initstucture);//初始化SS引脚
    
    GPIO_Initstucture.GPIO_Mode = GPIO_Mode_AF_PP;//复用推挽输出
    GPIO_Initstucture.GPIO_Pin  = CLK|MOIS;
    GPIO_Init(GPIOA,&GPIO_Initstucture);//初始化CLK和MOIS引脚
    
    GPIO_Initstucture.GPIO_Mode = GPIO_Mode_IPU;//上拉输入模式
    GPIO_Initstucture.GPIO_Pin  = MISO;
    GPIO_Init(GPIOA,&GPIO_Initstucture);//初始化MISO引脚
    
    SPI_InitTypeDef SPI_Initstucture;
    SPI_Initstucture.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_128;//波特率预分频计数值 选择为128分频
    SPI_Initstucture.SPI_CPHA = SPI_CPHA_1Edge;//指定捕获的时钟边缘 为第一边缘及上
    SPI_Initstucture.SPI_CPOL = SPI_CPOL_Low;//设置空闲情况下SCK引脚状态 设置为低电平
    SPI_Initstucture.SPI_CRCPolynomial = 7;//设置CRC多项式校验
    SPI_Initstucture.SPI_DataSize = SPI_DataSize_8b;//选择数据帧，为8位数据帧
    SPI_Initstucture.SPI_Direction = SPI_Direction_2Lines_FullDuplex;//传输模式选择，选择为全双工模式
    SPI_Initstucture.SPI_FirstBit = SPI_FirstBit_MSB;//选择数据先行位，高位先行
    SPI_Initstucture.SPI_Mode = SPI_Mode_Master;//主从模式选择，设置为主模式
    SPI_Initstucture.SPI_NSS = SPI_NSS_Soft;//NSS触发方式，软件触发
    SPI_Init(SPI1,&SPI_Initstucture);
    
    SPI_Cmd(SPI1,ENABLE);
    
    SPI1_W_SS(1);//不选择模块
}

void SPI1_Start(void)
{
    SPI1_W_SS(0);
}

void SPI1_Stop(void)
{
    SPI1_W_SS(1);
}

uint8_t SPI1_SwapByte(uint8_t ByteSend)//SPI交换一个字节数据
{
    while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE) != SET);//等待上一周期发送完毕
    SPI_I2S_SendData(SPI1,ByteSend);
    while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_RXNE) != SET);//等待上一周期接收完毕
    return SPI_I2S_ReceiveData(SPI1);
}
    
