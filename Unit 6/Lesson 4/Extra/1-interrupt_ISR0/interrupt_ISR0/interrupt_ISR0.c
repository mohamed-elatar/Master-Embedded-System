/*
 * interrupt_ISR0.c
 *
 * Created: 5/1/2023 11:14:34 PM
 *  Author: mohamed elatar
 */ 


#define F_CPU 8000000UL
#include <util/delay.h>
#include "led.h"
#include "button.h"
#include "interrupt.h"
#include "standard_macros.h"

char counter=1;
int main(void)
{
	BUTTON_vinit_pin('d',2);//portD 2(INT0)
	LED_vinit_pin('D',7);
	/**** set i_bit ****/
	Enable_Interrupt();
	
	/* select rising edge implement ISR */
	SET_BIT(MY_MCUCR , ISC_00);
	SET_BIT(MY_MCUCR , ISC_01);
	
	/**** enable INT0 ****/
	SET_BIT(MY_GICR , INT_0); // this pin_2 PORTD
	
	/**** clear i_bit ****/
	//DisEnable_Interrupt();
    while(1)
    {
        LED_vturn_off_pin('d',7);
    }
}
ISR(INT0_vect)
{
	if (counter > 0)
	{
		LED_vturn_on_pin('d',7);
		_delay_ms(5000);
	}
	counter = 1;
}
/*
MY_ISR(INT_0_vect)
{
    if (counter > 0)
    {
        LED_vturn_on_pin('d',7);
        _delay_ms(2000);
    }
    counter = 1;
}*/