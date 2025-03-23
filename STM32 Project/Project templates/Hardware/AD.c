#include "stm32f10x.h"                  // Device header

void AD_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
    
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);//���ò������� 72Mhz / 6 = 12Mhz
    
    GPIO_InitTypeDef GPIO_Initstucture; //�����ṹ��
    GPIO_Initstucture.GPIO_Mode = GPIO_Mode_AIN; //ģ������ģʽ
    GPIO_Initstucture.GPIO_Pin  = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
    GPIO_Initstucture.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_Initstucture);
    
    ADC_InitTypeDef ADC_Initstucture;
    ADC_Initstucture.ADC_ContinuousConvMode = DISABLE;//��ʹ������ת��ģʽ
    ADC_Initstucture.ADC_DataAlign = ADC_DataAlign_Right;//�����Ҷ���
    ADC_Initstucture.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//��ʹ���ⲿʱ��
    ADC_Initstucture.ADC_Mode = ADC_Mode_Independent;//��������ģʽ
    ADC_Initstucture.ADC_NbrOfChannel = 1;//����ͨ����Ŀ
    ADC_Initstucture.ADC_ScanConvMode = DISABLE;//������ɨ��ģʽ
    ADC_Init(ADC1,&ADC_Initstucture);
    
    ADC_Cmd(ADC1,ENABLE);
    
    ADC_ResetCalibration(ADC1);//����ADC��λУ׼
    while(ADC_GetResetCalibrationStatus(ADC1) == SET);//�ȴ�У׼���
    ADC_StartCalibration(ADC1);//��ʼ����У׼
    while(ADC_GetCalibrationStatus(ADC1) == SET);//�ȴ�У׼���
}


uint16_t AD_Getvalue(uint8_t ADC_Channel_x)
{
    ADC_RegularChannelConfig(ADC1,ADC_Channel_x,1,ADC_SampleTime_55Cycles5);//����ADC�Ĺ����� ʹ��ADC1 ʹ�õ�xͨ�� �趨Ϊ��һ���� ��������Ϊ55.5��ADCCLK
    ADC_SoftwareStartConvCmd(ADC1,ENABLE);//�������ת��
    while (ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC) == RESET);//�ȴ�ת�����
    return ADC_GetConversionValue(ADC1);//����ת��ֵ
}






