/*
 * main.c
 *
 *  Created on: Jul 19, 2023
 *      Author: mohamed elatar
 */
#include "stdio.h"
void main()
{
	float num1 , num2 , sum;
	printf("Enter two integers: ");
	fflush(stdin) ; fflush(stdout);
	scanf("%f %f", &num1 , &num2);
	sum = num1 * num2 ;
	printf("sum: %.6f" , sum);
}
/**********  output ************/
/*
 *Enter two integers: 2.4
 *1.1
 *sum: 2.640000
 */
