/*
 * AC.h
 *
 *  Created on: Sep 13, 2023
 *      Author: mohamed elatar
 */

#ifndef AC_H_
#define AC_H_

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
uint32_t fun_random(uint32_t first , uint32_t last , uint32_t count);
#endif /* AC_H_ */
