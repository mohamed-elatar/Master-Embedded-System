/*
 * State.h
 *
 *  Created on: Sep 13, 2023
 *      Author: mohamed elatar
 */

#ifndef STATE_H_
#define STATE_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

//function define
#define Fun_define(state_fun)	void Fun_##state_fun()
#define Fun_symbol(state_fun)	Fun_##state_fun

//connection prototype
void Ultrasonic_distance_get(int distance);
void Dc_motor(int speed);

#endif /* STATE_H_ */
