/*
 * main.c
 *
 *  Created on: Sep 13, 2023
 *      Author: mohamed elatar
 */

#include "DC_Motor.h"
#include "Ultrasonic.h"
#include "Collision_Avoidance.h"

int temp = 15;
void setup()
{
	//initialize
	Fun_Ultrasonic_init();
	Fun_DC_motor_init();

	//set pointer to function
	pfCollision_state = Fun_symbol(Collision_waiting);
	pfDC_motor_state = Fun_symbol(DC_motor_idle);
	pfUltrasonic_state = Fun_symbol(Ultrasonic_busy);
}

void main()
{
	volatile uint32_t delay;

	setup();

	while(temp--)
	{
		//call state
		pfUltrasonic_state();
		pfCollision_state();
		pfDC_motor_state();
		//delay
		for(delay = 0 ; delay <= 100000000 ; delay++);
	}
}
