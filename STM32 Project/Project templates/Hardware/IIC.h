#ifndef _IIC_H_
#define _IIC_H_

void IIC_Init(void);                //引脚初始化
void IIC_Start(void);               //起始信号
void IIC_Stop(void);                //停止信号
void IIC_SendByte(uint8_t Byte);    //发送数据
uint8_t IIC_ReceiveByte(void);      //接受数据
void IIC_SendACK(uint8_t ACKBit);   //写应答
uint8_t IIC_ReceiveACK(void);       //读应答

#endif
