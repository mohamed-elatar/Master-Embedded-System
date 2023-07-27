/*
 * main.c
 *
 *  Created on: Jul 26, 2023
 *      Author: mohamed elatar
 */
#include <stdio.h>
int ascll_to_decimal(char arr[]);
void main()
{
    char arr[]="1234";
    int num = ascll_to_decimal(arr);
    printf("decimal number is :%d" , num);
}
int ascll_to_decimal(char arr[])
{
    int i=0 , sign=1 , result=0;
    if(arr[i] == '-')
    {
        sign = -1;
        i++;
    }
    switch(arr[i])
    {
    case '1' ... '9':
        while(arr[i]>='0' && arr[i]<='9')
        {
            result = (arr[i++]-'0') + result*10 ;
        }
        break;

    default:
        break;//any character or null
    }
    return sign*result;
}

