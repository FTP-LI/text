#ifndef _UART_H_
#define _UART_H_

void UART_Init(void);
void UART_Sendbyte(uint16_t Byte);
void UART_SendArray(uint16_t *Array,uint16_t Lenght);
void UART_SendString(char *String);
void UART_SendNumber(uint32_t Number,uint8_t Lenght);
void UART_Printf(char *format,  ...);
uint8_t UART_GetRxData(void);
uint8_t UART_GetRXFlag(void);

#endif
