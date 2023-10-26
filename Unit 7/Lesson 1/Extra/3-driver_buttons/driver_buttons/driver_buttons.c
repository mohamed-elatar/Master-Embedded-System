/*
 * driver_buttons.c
 *
 * Created: 4/26/2023 10:42:54 PM
 *  Author: mohamed elatar
 */ 

//#define pull_down
#define pull_up

#define F_CPU 8000000UL
#include <util/delay.h>

#include "led.h"
#include "button.h"

int main(void)
{
	BUTTON_vinit_pin('d',0);
	LED_vinit_pin('A',0);
    while(1)
    {
        #if defined pull_down
			if (BUTTON_u8read_pin('d',0) == 1)
			{
				LED_vturn_on_pin('a',0);
			} 
			else
			{
				LED_vturn_off_pin('a',0);
			}
			
		#elif defined pull_up
			if (BUTTON_u8read_pin('d',0) == 0)
			{
				LED_vturn_on_pin('a',0);
			}
			else
			{
				LED_vturn_off_pin('a',0);
			}
		#endif
    }
}