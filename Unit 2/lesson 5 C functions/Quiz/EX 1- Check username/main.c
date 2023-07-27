/*
 * main.c
 *
 *  Created on: Jul 26, 2023
 *      Author: mohamed elatar
 */
#include <stdio.h>
#include <string.h>
void main()
{
    char str[10];
    char username[20]= "mohamed elatar";
    printf("Enter string :");
    fflush(stdin); fflush(stdout);
    gets(str);

    /********** check username ***************/
    if(stricmp(str , username) == 0) printf("same user name open door\n");
    else                             printf("not same user name\n");

}

