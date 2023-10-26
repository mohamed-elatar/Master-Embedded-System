/*
 * BCD_7segment.c
 *
 * Created: 4/29/2023 6:06:25 PM
 *  Author: moham
 */ 

#define F_CPU 8000000UL
#include <util/delay.h>
#include "sevensegment.h"

int main(void)
{
	SevenSegment_BCD_vinit('d',0);
	SevenSegment_BCD_vinit('c',4);
	char count=0;
    while(1)
    {
        SevenSegment_BCD_vwrite_lownibble ('d',9);
		do 
		{
			SevenSegment_BCD_vwrite_highnibble('c',count)
			;_delay_ms(250);
			
		} while (count = ++count % 16);
		
    }
}