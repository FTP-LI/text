#include "stm32f10x.h"                  // Device header
#include "delay.h"
#include "OLED.h"
#include "UART.h"
#include "SPI.h"

int main(void) 
{
    char RxData;
    OLED_Init();
    UART_Init();
    
    OLED_ShowString(1,1,"RX:");
    
    while(1)
    {
        if(UART_GetRXFlag() == 1)
        {
            RxData = UART_GetRxData();
            UART_Printf(&RxData);
            OLED_ShowHexNum(1,4,RxData,2);
            OLED_ShowNum(2,4,RxData,2);
        }
    }
}
