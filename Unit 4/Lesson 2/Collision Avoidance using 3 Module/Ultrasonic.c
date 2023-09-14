/*
 * Ultrasonic.c
 *
 *  Created on: Sep 13, 2023
 *      Author: mohamed elatar
 */

#include "Ultrasonic.h"

void (*pfUltrasonic_state)();

//module variable
uint32_t Ultrasonic_distance = 0;

/*********************** Functions ****************************/

Fun_define(Ultrasonic_init)
{
	//initialize
	printf("\t ----> Ultrasonic inti <---- \n");
}

Fun_define(Ultrasonic_busy)
{
	//state action
	gUltrasonic_state = Ultrasonic_busy;

	//read from Ultrasonic random
	Ultrasonic_distance = fun_random(45 , 55 , 1);

	printf("Ultrasonic_busy state : detect distance = %d \n" , Ultrasonic_distance);

	Ultrasonic_distance_get(Ultrasonic_distance);
	pfUltrasonic_state = Fun_symbol(Ultrasonic_busy);


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
