/*
 * bad_ISR.c
 *
 * Created: 5/4/2023 2:00:16 PM
 *  Author: mohamed elatar
 */ 

#define F_CPU 8000000UL
#include <util/delay.h>
#include "interrupt.h"
#include "led.h"
#include "button.h"
char count=0;
int main(void)
{
	BUTTON_vinit_pin('d',2);
	BUTTON_vinit_pin('d',3);
	LED_vinit_pin('a',0);
	LED_vinit_pin('a',1);
	LED_vinit_pin('a',2);
	
	Enable_Interrupt();
	// INT0
	SET_BIT(MY_GICR , INT_0); //enable control INT0
	SET_BIT(MY_MCUCR , ISC_00);  // action when rising edge
	SET_BIT(MY_MCUCR , ISC_01);
	
	// INT1  this is bad interrupt
	SET_BIT(MY_GICR , INT_1); //enable control INT1
	SET_BIT(MY_MCUCR , ISC_10);  // action when rising edge
	SET_BIT(MY_MCUCR , ISC_11);
	
	
    while(1)
    {

		LED_vturn_on_pin('a',2);
		_delay_ms(1000);
		LED_vturn_off_pin('a',2);
		_delay_ms(1000);
    }
}

void INT_0_vect (void) __attribute__((signal,used));
void INT_0_vect (void)
{
	if (count >0)
	{
		LED_vturn_on_pin('a',0);
		_delay_ms(2000);
		LED_vturn_off_pin('a',0);
		_delay_ms(2000);
	}
	count=1;
}

void BADISR__vect (void) __attribute__((signal,used));
void __vector_default (void)
{
	if (count > 0)
	{
		LED_vturn_on_pin('a',1);
		_delay_ms(2000);
		LED_vturn_off_pin('a',1);
		_delay_ms(2000);
	}
	count =1  ;
}