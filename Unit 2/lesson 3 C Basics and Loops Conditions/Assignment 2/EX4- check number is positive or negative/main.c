/*
 * main.c
 *
 *  Created on: Jul 19, 2023
 *      Author: mohamed elatar
 */
#include "stdio.h"
void main()
{
	float num;
	printf("Enter a number :");
	fflush(stdin);fflush(stdout);
	scanf("%f" ,&num);
	if(num > 0) 		printf("%f is positive" , num);
	else if(num < 0)	printf("%f is negative" , num);
	else 				printf("you entered zero");
}


