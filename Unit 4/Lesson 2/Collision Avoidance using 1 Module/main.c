/*
 * main.c
 *
 *  Created on: Sep 13, 2023
 *      Author: mohamed elatar
 */


#include "AC.h"

int temp = 25;
void setup()
{
	//set pointer to function
	pfCollision_state = Fun_symbol(Collision_waiting);
}

void main()
{
	volatile uint32_t delay;

	setup();

	while(temp--)
	{
		//call state
		pfCollision_state();

		//delay
		for(delay = 0 ; delay <= 100000000 ; delay++);
	}
}
