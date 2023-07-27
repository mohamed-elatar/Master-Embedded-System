/*
 * main.c
 *
 *  Created on: Jul 19, 2023
 *      Author: mohamed elatar
 */
#include "stdio.h"
void main()
{
	unsigned int a , b ;
	printf("Enter value of a: ");
	fflush(stdin) ; fflush(stdout);
	scanf("%d", &a);

	printf("Enter value of b: ");
	fflush(stdin) ; fflush(stdout);
	scanf("%d", &b);

	a = a^b; //1 ^ 2
	b = a^b; //1 ^ 2 ^ 2 = 1
	a = a^b; //1 ^ 2 ^ 1 = 2

	printf("After swapping, value of a = %d \n", a);
	printf("After swapping, value of b = %d \n", b);
}

/**********  output ************/
/*
 * Enter value of a: 1
 * Enter value of b: 2
 * After swapping, value of a = 2
 * After swapping, value of b = 1
 */
