#include "stm32f10x.h"                  // Device header
#include "MPU6050_Reg.h"
#include "IIC.h"

//需要主函数存在uint16_t AX,AY,AZ,GX,GY,GZ;

#define MPU6050_ADDRESS 0xD0

void MPU6050_W_REG(uint8_t REG_ADDRESS,uint8_t DATA)//MP6050写数据
{
    IIC_Start();
    IIC_SendByte(MPU6050_ADDRESS);
    IIC_ReceiveACK();
    IIC_SendByte(REG_ADDRESS);
    IIC_ReceiveACK();
    IIC_SendByte(DATA);
    IIC_ReceiveACK();
    IIC_Stop();
}

uint8_t MPU6050_R_REG(uint8_t REG_ADDRESS)//MPU6050读数据
{
    uint8_t DATA;
    IIC_Start();
    IIC_SendByte(MPU6050_ADDRESS);
    IIC_ReceiveACK();
    IIC_SendByte(REG_ADDRESS);
    IIC_ReceiveACK();
    
    IIC_Start();
    IIC_SendByte(MPU6050_ADDRESS | 0x01);
    IIC_ReceiveACK();
    DATA = IIC_ReceiveByte();
    IIC_SendACK(0);
    IIC_Stop();
    return DATA;
}

void MPU6050_Init(void)
{
    IIC_Init();
    MPU6050_W_REG(MPU6050_PWR_MGMT_1,0x01);
    MPU6050_W_REG(MPU6050_PWR_MGMT_2,0x00);
    MPU6050_W_REG(MPU6050_SMPLRT_DIV,0x09);
    MPU6050_W_REG(MPU6050_CONFIG,0x06);
    MPU6050_W_REG(MPU6050_GYRO_CONFIG,0x18);
    MPU6050_W_REG(MPU6050_ACCEL_CONFIG,0x18);
}

void MPU6050_GetData(uint16_t *ACCELX,uint16_t *ACCELY,uint16_t *ACCELZ,
                     uint16_t *GYROX ,uint16_t *GYROY ,uint16_t *GYROZ)
{
    uint8_t DATAH,DATAL;
    
    DATAH = MPU6050_R_REG(MPU6050_ACCEL_XOUT_H);
    DATAL = MPU6050_R_REG(MPU6050_ACCEL_XOUT_L);
    *ACCELX = (DATAH << 8) | DATAL;
    
    DATAH = MPU6050_R_REG(MPU6050_ACCEL_YOUT_H);
    DATAL = MPU6050_R_REG(MPU6050_ACCEL_YOUT_L);
    *ACCELY = (DATAH << 8) | DATAL;
    
    DATAH = MPU6050_R_REG(MPU6050_ACCEL_ZOUT_H);
    DATAL = MPU6050_R_REG(MPU6050_ACCEL_ZOUT_L);
    *ACCELZ = (DATAH << 8) | DATAL;
    
    DATAH = MPU6050_R_REG(MPU6050_GYRO_XOUT_H);
    DATAL = MPU6050_R_REG(MPU6050_GYRO_XOUT_L);
    *GYROX = (DATAH << 8) | DATAL;
    
    DATAH = MPU6050_R_REG(MPU6050_GYRO_YOUT_H);
    DATAL = MPU6050_R_REG(MPU6050_GYRO_YOUT_L);
    *GYROY = (DATAH << 8) | DATAL;
    
    DATAH = MPU6050_R_REG(MPU6050_GYRO_ZOUT_H);
    DATAL = MPU6050_R_REG(MPU6050_GYRO_ZOUT_L);
    *GYROZ = (DATAH << 8) | DATAL;
}

