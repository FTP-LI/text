#ifndef _MPU6050_H_
#define _MPU6050_H_

void MPU6050_Init(void);
void MPU6050_GetData(uint16_t *ACCELX,uint16_t *ACCELY,uint16_t *ACCELZ,
                     uint16_t *GYROX ,uint16_t *GYROY ,uint16_t *GYROZ);

#endif
