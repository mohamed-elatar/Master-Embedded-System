/*
 * main.c
 *
 *  Created on: Jul 19, 2023
 *      Author: mohamed elatar
 */
#include "stdio.h"
void main()
{
	char character;
	printf("Enter a character: ");
	fflush(stdin) ; fflush(stdout);
	scanf("%c", &character);
	printf("ASCII value of G = %i" , character);
}


/**********  output ************/
/*
 * Enter a character: G
 * ASCII value of G = 71
 */
