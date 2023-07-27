/*
 * main.c
 *
 *  Created on: Jul 19, 2023
 *      Author: mohamed elatar
 */
#include "stdio.h"
void main()
{
	unsigned int num , index , sum=0;
	printf("Enter a number :");
	fflush(stdin);fflush(stdout);
	scanf("%d" , &num);
	for(index=0 ; index <= num ; index++)
	{
		sum+= index;
	}
	printf("sum = %d" , sum);
}


