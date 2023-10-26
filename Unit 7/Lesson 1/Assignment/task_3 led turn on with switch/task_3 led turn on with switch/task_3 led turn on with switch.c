/*
 * task_3_led_turn_on_with_switch.c
 *
 * Created: 10/26/2023 3:28:31 AM
 *  Author: mohamed elatar
 */ 


#include <util/delay.h>
#include "led.h"
#include "button.h"

int main(void)
{
    BUTTON_vinit_pin('d' , 0); //input pin
    LED_vinit_pin('d' , 5);
    LED_vinit_pin('d' , 6);
    LED_vinit_pin('d' , 7);

    int i=5;
    while(1)
    {
        //TODO:: Please write your application code 
        if (BUTTON_u8read_pin('d' , 0) == 1) //pull down
        {
            LED_vturn_on_pin('d' , i);
            while(BUTTON_u8read_pin('d' , 0) == 1);
            if(++i == 8) break;   
        }
    }
}