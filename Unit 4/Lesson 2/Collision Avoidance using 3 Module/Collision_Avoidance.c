/*
 * Collision_Avoidance.c
 *
 *  Created on: Sep 13, 2023
 *      Author: mohamed elatar
 */

#include "Collision_Avoidance.h"
uint32_t Collision_speed = 0;
uint32_t Collision_new_distance = 0;
uint32_t Collision_old_distance = 0;
uint32_t Collision_threshold = 50;

void (*pfCollision_state)();

/*********************** Functions ****************************/

void Ultrasonic_distance_get(int distance)
{
	Collision_new_distance = distance; // random distance
	(Collision_new_distance <= Collision_threshold) ?  (pfCollision_state = Fun_symbol(Collision_waiting)) : (pfCollision_state = Fun_symbol(Collision_driving)) ;

	printf("Ultrasonic ------- distance = %d --------> Collision_Avoidance \n" , Collision_new_distance);
}

Fun_define(Collision_waiting)
{
	//state wait
	gCollision_state = Collision_waiting;
	printf("Collision_waiting state before updata ultrasonic: distance = %d , speed = %d \n" , \
			Collision_old_distance , Collision_speed);

	//state action
	printf("after updata ultrasonic\n");
	Collision_old_distance = Collision_new_distance;
	Collision_speed = 0;
	Dc_motor(Collision_speed);
}

Fun_define(Collision_driving)
{
	//state wait
	gCollision_state = Collision_driving;
	printf("Collision_driving state before updata ultrasonic: distance = %d , speed = %d \n" , \
			Collision_old_distance , Collision_speed);

	//state action
	printf("after updata ultrasonic\n");
	Collision_old_distance = Collision_new_distance;
	Collision_speed = 30;
	Dc_motor(Collision_speed);
}















