/*
 * task_2_three_led_turn_on.c
 *
 * Created: 10/26/2023 3:18:29 AM
 *  Author: mohamed elatar
 */ 


#define F_CPU 8000000ul
#include "led.h"
#include <util/delay.h>

int main(void)
{
    LED_vinit_pin('d' , 5);
    LED_vinit_pin('d' , 6);
    LED_vinit_pin('d' , 7);
    while(1)
    {
        //TODO:: Please write your application code 
        for (int i=5 ; i<8 ; ++i)
        {
            LED_vturn_on_pin('d',i);
            _delay_ms(1000);
        }
        for (int i=7 ; i>4 ; --i)
        {
            LED_vturn_off_pin('d',i);
            _delay_ms(1000);
        }
    }
}