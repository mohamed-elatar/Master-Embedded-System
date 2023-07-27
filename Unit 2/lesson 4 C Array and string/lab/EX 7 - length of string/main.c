/*
 * main.c
 *
 *  Created on: Jul 21, 2023
 *      Author: mohamed elatar
 */

#include <stdio.h>
void main()
{
    int i=0 , counter=0;
	char string[10] ;

	/********* take string from user ***********/
	printf("Enter a string: ");
	fflush(stdin);fflush(stdout);
	gets(string);

	/********* count all char expected null ***********/
	while(string[i++] != 0)
    {
        counter++;
    }
    printf("length of string : %d \n" , counter );


}
