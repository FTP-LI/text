#include "stm32f10x.h"                  // Device header

#define CLK     GPIO_Pin_5  //ʱ����
#define MOIS    GPIO_Pin_7  //���������/�ӻ�������
#define MISO    GPIO_Pin_6  //�ӻ������/����������
#define SS      GPIO_Pin_4  //Ƭѡ

#define SPI1_W_SS(x)		GPIO_WriteBit(GPIOA, SS, (BitAction)(x))


void SPI1_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,ENABLE);
    
    GPIO_InitTypeDef GPIO_Initstucture; //�����ṹ��
    GPIO_Initstucture.GPIO_Mode = GPIO_Mode_Out_PP;//�������ģʽ 
    GPIO_Initstucture.GPIO_Pin  = SS;
    GPIO_Initstucture.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_Initstucture);//��ʼ��SS����
    
    GPIO_Initstucture.GPIO_Mode = GPIO_Mode_AF_PP;//�����������
    GPIO_Initstucture.GPIO_Pin  = CLK|MOIS;
    GPIO_Init(GPIOA,&GPIO_Initstucture);//��ʼ��CLK��MOIS����
    
    GPIO_Initstucture.GPIO_Mode = GPIO_Mode_IPU;//��������ģʽ
    GPIO_Initstucture.GPIO_Pin  = MISO;
    GPIO_Init(GPIOA,&GPIO_Initstucture);//��ʼ��MISO����
    
    SPI_InitTypeDef SPI_Initstucture;
    SPI_Initstucture.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_128;//������Ԥ��Ƶ����ֵ ѡ��Ϊ128��Ƶ
    SPI_Initstucture.SPI_CPHA = SPI_CPHA_1Edge;//ָ�������ʱ�ӱ�Ե Ϊ��һ��Ե����
    SPI_Initstucture.SPI_CPOL = SPI_CPOL_Low;//���ÿ��������SCK����״̬ ����Ϊ�͵�ƽ
    SPI_Initstucture.SPI_CRCPolynomial = 7;//����CRC����ʽУ��
    SPI_Initstucture.SPI_DataSize = SPI_DataSize_8b;//ѡ������֡��Ϊ8λ����֡
    SPI_Initstucture.SPI_Direction = SPI_Direction_2Lines_FullDuplex;//����ģʽѡ��ѡ��Ϊȫ˫��ģʽ
    SPI_Initstucture.SPI_FirstBit = SPI_FirstBit_MSB;//ѡ����������λ����λ����
    SPI_Initstucture.SPI_Mode = SPI_Mode_Master;//����ģʽѡ������Ϊ��ģʽ
    SPI_Initstucture.SPI_NSS = SPI_NSS_Soft;//NSS������ʽ���������
    SPI_Init(SPI1,&SPI_Initstucture);
    
    SPI_Cmd(SPI1,ENABLE);
    
    SPI1_W_SS(1);//��ѡ��ģ��
}

void SPI1_Start(void)
{
    SPI1_W_SS(0);
}

void SPI1_Stop(void)
{
    SPI1_W_SS(1);
}

uint8_t SPI1_SwapByte(uint8_t ByteSend)//SPI����һ���ֽ�����
{
    while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE) != SET);//�ȴ���һ���ڷ������
    SPI_I2S_SendData(SPI1,ByteSend);
    while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_RXNE) != SET);//�ȴ���һ���ڽ������
    return SPI_I2S_ReceiveData(SPI1);
}
    
