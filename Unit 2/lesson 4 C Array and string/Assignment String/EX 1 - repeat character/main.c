/*
 * main.c
 *
 *  Created on: Jul 22, 2023
 *      Author: mohamed elatar
 */

#include <stdio.h>
void main()
{
    int i=0 , counter=0;
	char string[100] , character ;

	/********* take string from user ***********/
	printf("Enter a string: ");
	fflush(stdin);fflush(stdout);
	gets(string);

	/********* take character from user ***********/
	printf("Enter a character find frequency: ");
	fflush(stdin);fflush(stdout);
	character = getchar();

	/********* count character ***********/
	while(string[i] != 0)
    {
        if(string[i++] == character) counter++;
    }

    printf("frequency of %c : %d \n" , character , counter );


}
