/*
 * main.c
 *
 *  Created on: Jul 19, 2023
 *      Author: mohamed elatar
 */
#include "stdio.h"
void main()
{
	signed int num ;
	unsigned fact = 1 ;
	printf("Enter an integer :");
	fflush(stdin);fflush(stdout);
	scanf("%d", &num);

	if(num > 0)
	{
		while(num >= 1)
		{
			fact *= num--;
		}
		printf("factorial = %d" , fact);
	}
	else if (num == 0) printf("factorial = 1");
	else if (num <  0) printf("Error!!! negative number not exist ");

}


