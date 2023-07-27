/*
 * main.c
 *
 *  Created on: Jul 25, 2023
 *      Author: mohamed elatar
 */
#include <stdio.h>
int factorial(int num);// prototype

void main()
{
    int num;
    /************** enter number ***************/
    printf("Enter a positive number :");
    fflush(stdin); fflush(stdout);
    scanf("%u" , &num);

    /************** print factorial number ***************/
    printf("factorial of %u = %u" , num , factorial(num));
}
int factorial(int num)
{
   return (num==0) ? 1 : (num*factorial(num-1)) ;
}
