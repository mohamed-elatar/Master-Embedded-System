/*
 * driver_seven_segment.c
 *
 * Created: 4/29/2023 1:24:18 PM
 *  Author: mohamed elatar
 */ 


#define F_CPU 8000000UL
#include <util/delay.h>
#include "sevensegment.h"

int main(void)
{
	SevenSegment_vinit('c',0x7f);//english
	SevenSegment_vinit('d',0x7f);//arabic
    while(1)
    {
        for (char i=0,j=0 ; i<16 && j<10 ; (i = ++i % 16) ,(j = ++j % 10))
        {
			SevenSegment_vwrite_eg('c',i);
			SevenSegment_vwrite_ar('d',j);
			_delay_ms(500);
        }
    }
}