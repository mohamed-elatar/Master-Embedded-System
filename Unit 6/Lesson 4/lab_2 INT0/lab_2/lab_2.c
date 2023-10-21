/*
 * lab_2.c
 *
 * Created: 10/21/2023 1:21:46 AM
 *  Author: mohamed elatar
 */ 


#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#define F_CPU 8000000ul

#include "led.h"
#include "button.h"
#include "standard_macros.h"

volatile int delay_1 , delay_2 , delay_3 ;
int main(void)
{
    LED_vinit_pin('d',5);
    LED_vinit_pin('d',6);
    LED_vinit_pin('d',7);
    BUTTON_vinit_pin('d',2); //INT0
    BUTTON_vinit_pin('d',3); //INT1
    BUTTON_vinit_pin('b',2); //INT2

    sei(); // global interrupt i-bit

    // INT0
    SET_BIT(GICR  , INT0);  //enable INT0
    CLR_BIT(MCUCR , ISC01); //any logic
    SET_BIT(MCUCR , ISC00); //any logic
    

    // INT1
    SET_BIT(GICR  , INT1);  //enable INT1
    SET_BIT(MCUCR , ISC10); //rising
    SET_BIT(MCUCR , ISC11); //rising

    // INT2
    SET_BIT(GICR  , INT2);  //enable INT2
    CLR_BIT(MCUCSR , ISC2); //failing


    while(1)
    {
        //TODO:: Please write your application code 
        LED_vturn_off_pin('d',5);
        LED_vturn_off_pin('d',6);
        LED_vturn_off_pin('d',7);
    }
}

ISR(INT0_vect)
{
    if (delay_1 == 1)
    {
        LED_vturn_on_pin('d',5);
        _delay_ms(3000);
    }
    delay_1 = 1;
}

ISR(INT1_vect)
{
    if (delay_2 == 1)
    {
        LED_vturn_on_pin('d',6);
        _delay_ms(3000);
    }
    delay_2 = 1;
}

ISR(INT2_vect)
{
    if (delay_3 == 1)
    {
        LED_vturn_on_pin('d',7);
        _delay_ms(3000);
    }
    delay_3 = 1;
}