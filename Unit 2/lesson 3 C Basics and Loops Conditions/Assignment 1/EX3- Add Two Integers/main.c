/*
 * main.c
 *
 *  Created on: Jul 19, 2023
 *      Author: mohamed elatar
 */
#include "stdio.h"
void main()
{
	unsigned int num1 , num2 , sum;
	printf("Enter two integers: ");
	fflush(stdin) ; fflush(stdout);
	scanf("%d %d", &num1 , &num2);
	sum = num1 + num2 ;
	printf("sum: %d" , sum);
}
/**********  output ************/
/*
 * Enter two integers: 12
 * 11
 * sum: 23
 */
