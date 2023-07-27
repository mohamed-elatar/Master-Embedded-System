/*
 * main.c
 *
 *  Created on: Jul 25, 2023
 *      Author: mohamed elatar
 */
#include <stdio.h>
void find_number(int num1 , int num2); //Prototype

void main()
{
    int num1 , num2;
    /********** input start and end numbers**************/
    printf("Enter two numbers(intervals) :");
    fflush(stdin); fflush(stdout);
    scanf("%d%d" , &num1 ,&num2);

    /********** number between two number **************/
    printf("Prime number between %d and %d are : " , num1 , num2);
    find_number(num1 , num2);
}
void find_number(int num1 , int num2)
{
    int arr[20]={} ; // zero array
    int i , j=0 , flag=0;

    /********** loop to get prime number **************/
    for (++num1 ; num1<num2 ; num1++)
    {
        for(i=2 ; i < num1-1 ; i++)
        {
            if(num1 % i == 0)
            {
                flag = 1; // not prime number
                break;
            }
        }
        if(flag == 0) arr[j++] = num1; // this prime number and append in array
        else          flag = 0;
    }
    /********** print array have prime between two number **************/
    for(i=0 ; arr[i] != 0 ; i++)  printf("%d " , arr[i]);
}
