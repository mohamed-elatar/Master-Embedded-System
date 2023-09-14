/*
 * DC_Motor.c
 *
 *  Created on: Sep 13, 2023
 *      Author: mohamed elatar
 */

#include "DC_Motor.h"

uint32_t DC_speed;

void (*pfDC_motor_state)();

/*********************** Functions ****************************/

Fun_define(DC_motor_init)
{
	//initialize
	printf("\t ----> DC_motor init <---- \n");
}

// in order change pointer from idle to busy
void Dc_motor(int speed)
{
	DC_speed = speed;
	pfDC_motor_state = Fun_symbol(DC_motor_busy);
	printf("Collision ------ speed = %d ------> DC_motor \n" , DC_speed);
}

Fun_define(DC_motor_idle)
{
	gDC_motor_state = DC_motor_idle ;
	//pDC_motor_state = Fun_symbol(DC_motor_idle) ;

	printf("DC_Idle state : speed = %d \n\n" , DC_speed);
}

Fun_define(DC_motor_busy)
{
	//state action
	gDC_motor_state = DC_motor_busy;

	//call dc driver
	// not exist condition to change busy to idle
	pfDC_motor_state = Fun_symbol(DC_motor_idle);

	printf("DC_busy state : speed = %d \n\n\n" , DC_speed);
}

