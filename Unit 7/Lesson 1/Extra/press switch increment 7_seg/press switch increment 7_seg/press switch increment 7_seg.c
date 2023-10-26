/*
 * press_switch_increment_7_seg.c
 *
 * Created: 4/29/2023 3:52:59 PM
 *  Author: moham
 */ 

#define F_CPU 8000000UL
#include <util/delay.h>
#include "button.h"
#include "7segment.h"

int main(void)
{
	BUTTON_vinternal_pull_up_pin('a',7,1);//pull up
	SevenSegment_vinit('d',0x7f);
	BUTTON_vinit_pin('a',7);
	char number=0;
    while(1)
    {
        if (BUTTON_u8read_pin('a',7) == 0)
        {
			_delay_ms(20);//avoid bouncing
			if (BUTTON_u8read_pin('a',7) == 0)
			{
				SevenSegment_vwrite_eg('d',number);
				number = ++number %16;
				while(BUTTON_u8read_pin('a',7) == 0);//avoid continuous press
			}
			_delay_ms(250);//avoid delay 200ms mechanical switch	
        }
    }
}