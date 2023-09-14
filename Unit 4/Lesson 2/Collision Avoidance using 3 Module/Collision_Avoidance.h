/*
 * Collision_Avoidance.h
 *
 *  Created on: Sep 13, 2023
 *      Author: mohamed elatar
 */

#ifndef COLLISION_AVOIDANCE_H_
#define COLLISION_AVOIDANCE_H_

#include "State.h"

enum
{
	Collision_waiting ,
	Collision_driving
}gCollision_state;
//global variable enumeration


//prototype
//Fun_define(Collision_init);
Fun_define(Collision_waiting);
Fun_define(Collision_driving);

//pointer to function
extern void (*pfCollision_state)();

#endif /* COLLISION_AVOIDANCE_H_ */
