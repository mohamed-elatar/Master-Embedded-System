/*
 * Ultrasonic.h
 *
 *  Created on: Sep 13, 2023
 *      Author: mohamed elatar
 */

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#include "State.h"

enum
{
	Ultrasonic_busy
}gUltrasonic_state;
//global variable enumeration


//prototype
Fun_define(Ultrasonic_busy);
uint32_t fun_random(uint32_t first , uint32_t last , uint32_t count);

//pointer to function
extern void (*pfUltrasonic_state)();


#endif /* ULTRASONIC_H_ */
