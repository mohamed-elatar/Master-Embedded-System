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
	printf("Enter a integer: ");
	fflush(stdin);fflush(stdout);
	scanf("%d" , &num);
	printf("You entered: %d" , num);
}
/**********  output ************/
/*
 *Enter a integer: 25
 *You entered: 25
 */


