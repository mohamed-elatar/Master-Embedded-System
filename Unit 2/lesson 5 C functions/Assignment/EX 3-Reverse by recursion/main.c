/*
 * main.c
 *
 *  Created on: Jul 25, 2023
 *      Author: mohamed elatar
 */
#include <stdio.h>
#include <string.h>
void reverse (char arr[] , int num1 , int num2);//prototype
void main()
{
    char string[20];
    /************** enter sentence want reverse ******************/
    printf("Enter a sentence :");
    fflush(stdin); fflush(stdout);
    gets(string);

    /************** call function reverse ******************/
    reverse( string , 0 , (strlen(string)-1) );

    /************** print reverse sentence ******************/
    puts(string);
}
void reverse (char arr[] , int num1 , int num2)
{
    if(num1 < num2)
    {
        arr[num1] = arr[num1] ^ arr[num2] ; // swap with xor
        arr[num2] = arr[num1] ^ arr[num2] ;
        arr[num1] = arr[num1] ^ arr[num2] ;
        reverse(arr , num1+1 , num2-1);
    }
}
