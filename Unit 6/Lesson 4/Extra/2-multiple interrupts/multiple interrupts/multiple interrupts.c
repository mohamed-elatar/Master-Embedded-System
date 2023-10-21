
#include <avr/interrupt.h>
#include "interrupt.h"

#define F_CPU 8000000UL
#include <util/delay.h>

#include "led.h"
#include "button.h"
#include "standard_macros.h"
int main(void)
{
	LED_vinit_pin('A',0);
	LED_vinit_pin('A',1);
	LED_vinit_pin('A',2);
	
	Enable_Interrupt();
	SET_BIT(MY_GICR , INT_0);  //enable external interrupt 0
	SET_BIT(MY_GICR , INT_1);  //enable external interrupt 1
	SET_BIT(MY_GICR , INT_2);  //enable external interrupt 2
	/*
	 set rising edge option for  external interrupt 0
	*/
	SET_BIT(MY_MCUCR , ISC_00);
	SET_BIT(MY_MCUCR , ISC_01);
	/*
	 set rising edge option for  external interrupt 1
	*/
	SET_BIT(MY_MCUCR , ISC_10);
	SET_BIT(MY_MCUCR , ISC_11);
	/*
	 set rising edge option for  external interrupt 2
	*/
	SET_BIT(MY_MCUCSR , ISC_2);
    while(1)
    {
        LED_vturn_off_pin('A',0);
		LED_vturn_off_pin('A',1);
		LED_vturn_off_pin('A',2);
    }
}


ISR(INT0_vect)
{
	
	LED_vturn_on_pin('A',0);
	_delay_ms(3000);
	
}

ISR(INT1_vect)
{
	
	LED_vturn_on_pin('A',1);
	_delay_ms(3000);
}

ISR(INT2_vect)
{
	
	LED_vturn_on_pin('A',2);
	_delay_ms(3000);
}


