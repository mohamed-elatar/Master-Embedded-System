/*
 * main.c
 *
 *  Created on: Jul 27, 2023
 *      Author: mohamed elatar
 */
#include <stdio.h>
void main()
{
    int num;
    /********* input number **************/
    printf("Enter number :");
    fflush(stdout);
    scanf("%d" , &num);
    /********** call function *************/
    printf("sum digits number = %d" , sum_digit(num));
}
int sum_digit(int num)
{
    int digit , sum=0;
    while(num)
    {
        digit = num%10;
        sum  += digit;
        num  /= 10;
    }
    return sum;
}



