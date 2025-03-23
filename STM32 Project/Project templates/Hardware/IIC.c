#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#define IIC_PROT GPIOB
#define IIC_SCL GPIO_Pin_12
#define IIC_SDA GPIO_Pin_13

void IIC_W_SCL(uint8_t Bit)
{
    GPIO_WriteBit(IIC_PROT, IIC_SCL, (BitAction)(Bit));
    Delay_us(10);
}

void IIC_W_SDA(uint8_t Bit)
{
    GPIO_WriteBit(IIC_PROT, IIC_SDA, (BitAction)(Bit));
    Delay_us(10);
}

uint8_t IIC_R_SDA(void)
{
    uint8_t DATA;
    DATA = GPIO_ReadInputDataBit(IIC_PROT,IIC_SDA);
    Delay_us(10);
    return DATA;
}


void IIC_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    
	GPIO_InitTypeDef GPIO_InitStructure;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = IIC_SCL;
 	GPIO_Init(IIC_PROT, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = IIC_SDA;
 	GPIO_Init(IIC_PROT, &GPIO_InitStructure);
	
	IIC_W_SCL(1);
	IIC_W_SDA(1);
}

void IIC_Start(void)//起始信号
{
    IIC_W_SDA(1);
    IIC_W_SCL(1);
    IIC_W_SDA(0);
    IIC_W_SCL(0);
}

void IIC_Stop(void)//终止信号
{
    IIC_W_SDA(0);
    IIC_W_SCL(1);
    IIC_W_SDA(1);
}

void IIC_SendByte(uint8_t Byte)//发送数据
{
    uint8_t i;
    for (i = 0;i < 8;i ++)
    {
        IIC_W_SDA(Byte & (0x80 >> i ));
        IIC_W_SCL(1);
        IIC_W_SCL(0);
    }
}    

uint8_t IIC_ReceiveByte(void)//接受数据
{
    uint8_t i,Byte = 0x00;
    for (i = 0;i < 8;i ++)
    {
        IIC_W_SDA(1);
        IIC_W_SCL(1);
        if(IIC_R_SDA() == 1)
        {
            Byte |= (0x80 >> i);
        }
        IIC_W_SCL(0);
    }
    IIC_W_SCL(1);
    return Byte;
}

void IIC_SendACK(uint8_t ACKBit)//写应答
{
    IIC_W_SDA(ACKBit);
    IIC_W_SCL(1);
    IIC_W_SCL(0);
}

uint8_t IIC_ReceiveACK(void)//读应答
{
    uint8_t ACKBit;;
    IIC_W_SDA(1);
    IIC_W_SCL(1);
    ACKBit = IIC_R_SDA();
    IIC_W_SCL(0);
    return ACKBit;
}

