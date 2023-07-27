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
	printf("Enter an alphabet: ");
	fflush(stdin) ; fflush(stdout);
	scanf("%c" , &character);

	switch(character)
	{
	case 'A':case 'a':case 'E':case 'e':
	case 'I':case 'i':case 'O':case 'o':
	case 'U':case 'u':
		printf("%c is vowel" ,character);
		break;
	default:
		printf("%c is consonant",character);
	}
}


