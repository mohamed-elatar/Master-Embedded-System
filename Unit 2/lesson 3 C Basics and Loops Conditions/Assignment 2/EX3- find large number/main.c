/*
 * main.c
 *
 *  Created on: Jul 19, 2023
 *      Author: mohamed elatar
 */
#include "stdio.h"
void main()
{
	float num1 , num2 , num3;
	printf("Enter three number :");
	fflush(stdin);fflush(stdout);
	scanf("%f %f %f" , &num1 , &num2 , &num3);
	switch(((num1>num2)&&(num1>num3)) +2*((num2>num1)&&(num2>num3)) +3*((num3>num2)&&(num3>num1)))
	{
	case 1:
		printf("Largest Number = %f" , num1);
		break;
	case 2:
		printf("Largest Number = %f" , num2);
		break;
	case 3:
		printf("Largest Number = %f" , num3);
		break;
	}
}


