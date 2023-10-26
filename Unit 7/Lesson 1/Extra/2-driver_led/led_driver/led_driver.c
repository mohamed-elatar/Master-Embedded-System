/*
 * led_driver.c
 *
 * Created: 4/26/2023 6:33:34 PM
 *  Author: moham
 */ 

#define F_CPU 8000000UL
#include <util/delay.h>
#include "led.h"

int main(void)
{
	unsigned char counter;
	LED_vinit_port('A',0xFF);
	LED_vinit_pin('c',0);
    while(1)
    {
		LED_vturn_on_pin('c',0);
        for (counter=0 ; counter <=7 ; counter++)
        {
			LED_vturn_on_pin('A',counter);
			_delay_ms(300);
        }
		
		LED_vturn_off_pin('c',0);
		
		for (counter=7 ; (signed char)counter >=0 ; counter--)
		{
			LED_vturn_off_pin('A',counter);
			_delay_ms(300);
		}
		
		/*
			LED_vturn_on_port('a',0xff);
			_delay_ms(1000);
			LED_vturn_off_port('a',0x00);
			_delay_ms(1000);
		*/
         
    }
}