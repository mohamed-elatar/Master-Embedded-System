/*
 * driver_dio_1_.c
 *
 * Created: 4/25/2023 11:28:01 AM
 *  Author: moham
 */ 


#define F_CPU 8000000UL
#include <util/delay.h>
#include "dio.h"


int main(void)
{
	DIO_vset_pin_direction('A',0,1); //output
	DIO_vset_port_direction('b',0xff);
	DIO_vset_port_direction('D',0XFF);
    while(1)
    {
       DIO_vwrite_pin_value('a',0,1);
	   DIO_vwrite_port_value('b',0xAA);
	   DIO_vtoggle_port('D');
	   
	   _delay_ms(1000);
	   
	   DIO_vwrite_pin_value('a',0,0);
	   DIO_vwrite_port_value('b',0xF0);
	   DIO_vtoggle_port('D');

	   _delay_ms(1000);
    }
}