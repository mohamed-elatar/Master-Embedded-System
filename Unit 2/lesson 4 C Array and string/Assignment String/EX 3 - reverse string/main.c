/*
 * main.c
 *
 *  Created on: Jul 22, 2023
 *      Author: mohamed elatar
 */

#include <stdio.h>
#include <string.h>
void main()
{
    int i=0 , counter=0 , len;
	char string[10] , string_reverse[10];

	/********* take string from user ***********/
	printf("Enter a string: ");
	fflush(stdin);fflush(stdout);
	gets(string);
	len = strlen(string);

	/********* reverse ***********/
    string_reverse[len--] = '\0';
	while(string[i] != 0)
    {
        string_reverse[i++] = string[len--] ;
    }
    printf("reverse string is: ");
	puts(string_reverse);
}
