/*
 * relay.c
 *
 * Created: 4/30/2023 4:33:54 PM
 *  Author: moham
 */ 

#define F_CPU 8000000UL
#include <util/delay.h>
#include "relay.h"

int main(void)
{
	Relay_vinit_pin('d',0);
    while(1)
    {
        Relay_vturn_on_pin('d',0);
		_delay_ms(2000);
		Relay_vturn_off_pin('d',0);
		_delay_ms(2000);
    }
}