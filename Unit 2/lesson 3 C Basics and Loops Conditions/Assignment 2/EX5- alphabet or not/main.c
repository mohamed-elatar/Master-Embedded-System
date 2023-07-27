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
	printf("Enter a character :");
	fflush(stdin);fflush(stdout);
	scanf("%c" , &character);
	switch(character)
	{
	case 'A' ... 'Z':
	case 'a' ... 'z':
		printf("%c is an alphabet" , character);
		break;
	default :
		printf("%c is not an alphabet" , character);
	}
}


