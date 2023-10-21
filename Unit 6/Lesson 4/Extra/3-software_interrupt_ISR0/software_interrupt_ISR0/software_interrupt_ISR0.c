/*
 * software_interrupt_ISR0.c
 *
 * Created: 5/2/2023 4:57:05 PM
 *  Author: mohamed elatar
 */ 
#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/interrupt.h>
#include "interrupt.h"
#include "led.h"

char count=0;
int main(void)
{
	LED_vinit_pin('d',2); //INT0
	LED_vinit_pin('a',0);
	
	Enable_Interrupt();
	SET_BIT(MY_GICR  , INT_0);
	SET_BIT(MY_MCUCR , ISC_00);
	SET_BIT(MY_MCUCR , ISC_01);
	
	_delay_ms(5000);
    while(1)
    {
		LED_vturn_on_pin('d',2);
		_delay_ms(50);
		LED_vturn_off_pin('d',2);
		_delay_ms(2000);
    }
}
ISR(INT0_vect)
{
	if (count > 0)
	{
		LED_vtoggle_pin('A',0);
	}
	count =1 ;
}