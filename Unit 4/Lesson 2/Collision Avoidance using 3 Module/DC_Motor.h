/*
 * DC_Motor.h
 *
 *  Created on: Sep 13, 2023
 *      Author: mohamed elatar
 */

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include "State.h"

enum
{
	DC_motor_idle ,
	DC_motor_busy
}gDC_motor_state;
//global variable enumeration


//prototype
Fun_define(DC_motor_init);
Fun_define(DC_motor_idle);
Fun_define(DC_motor_busy);

//pointer to function
extern void (*pfDC_motor_state)();

#endif /* DC_MOTOR_H_ */
