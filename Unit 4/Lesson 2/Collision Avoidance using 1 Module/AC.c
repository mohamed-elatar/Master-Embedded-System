/*
 * AC.c
 *
 *  Created on: Sep 13, 2023
 *      Author: mohamed elatar
 */

#include "AC.h"
uint32_t Collision_speed = 0;
uint32_t Collision_new_distance = 0;
uint32_t Collision_old_distance = 0;
uint32_t Collision_threshold = 50;

void (*pfCollision_state)();

/*********************** Functions ****************************/

Fun_define(Collision_waiting)
{
	//state wait
	gCollision_state = Collision_waiting;

	//state action
	Collision_new_distance = fun_random(45 , 55 , 1);
	(Collision_new_distance <= Collision_threshold) ?  (pfCollision_state = Fun_symbol(Collision_waiting)) : (pfCollision_state = Fun_symbol(Collision_driving)) ;

	Collision_speed = 0;
	printf("Collision_waiting state: distance = %d , speed = %d\t" ,Collision_old_distance , Collision_speed);
	printf("--> after detect new_distance : %d \n" , Collision_new_distance);

	Collision_old_distance = Collision_new_distance;


}

Fun_define(Collision_driving)
{
	//state wait
	gCollision_state = Collision_driving;

	//state action
	Collision_new_distance = fun_random(45 , 55 , 1);
	(Collision_new_distance <= Collision_threshold) ?  (pfCollision_state = Fun_symbol(Collision_waiting)) : (pfCollision_state = Fun_symbol(Collision_driving)) ;

	Collision_speed = 30;
	printf("Collision_driving state: distance = %d , speed = %d\t" ,Collision_old_distance , Collision_speed);
	printf("--> after detect new_distance : %d \n" , Collision_new_distance);

	Collision_old_distance = Collision_new_distance;

}

uint32_t fun_random(uint32_t first , uint32_t last , uint32_t count)
{
	uint32_t i , rand_num;
	for(i=0 ; i<count ; i++)
	{
		rand_num = ( (rand() % (last-first+1)) + first );
	}
	return rand_num;
}
