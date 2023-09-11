#include "gd32f4xx.h"
#include "stdio.h"
#include "delay.h"
#include "led.h"
#include "usart.h"

int main(void)
{
        delay_init(200);
        LED_Init();
        USART_Init(115200);

        unsigned int temp = 0;
        while (1) {
                printf("%s %d\n", "test", temp++);
                LED_ON;
                USART_Send_String((uint8_t *) "off\n");
                //delay_1ms(500);
                delay_ms(1000);
                LED_OFF;
                USART_Send_String((uint8_t *) "no\n");
                //delay_1ms(500);
                delay_ms(1000);
        }
}
