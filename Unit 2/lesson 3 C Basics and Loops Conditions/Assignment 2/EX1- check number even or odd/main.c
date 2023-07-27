/*
 * main.c
 *
 *  Created on: Jul 19, 2023
 *      Author: mohamed elatar
 */
#include "stdio.h"
void main()
{
	unsigned int num;
	printf("Enter an integer you want to check: ");
	fflush(stdin) ; fflush(stdout);
	scanf("%d" , &num);

	if(num%2 == 0) printf("%d is even\n" , num);
	else printf("%d is odd\n" , num);

}

/**********  output ************/
/*
 * Enter an integer you want to check: 25
 * 25 is odd
 */


