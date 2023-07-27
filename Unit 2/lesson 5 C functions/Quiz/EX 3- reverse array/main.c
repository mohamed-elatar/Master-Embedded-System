/*
 * main.c
 *
 *  Created on: Jul 26, 2023
 *      Author: mohamed elatar
 */
#include <stdio.h>
void function_reverse(int arr[]);
#define SIZE 6
void main()
{
    int arr[SIZE];

    /******* enter element ********/
    printf("input elements of array :");
    fflush(stdin); fflush(stdout);
    for(int i=0 ; i<SIZE ; i++)
    {
        scanf("%d" , &arr[i]);
    }
    /******* call function **********/
    function_reverse(arr);

    /******* print reverse array ***********/
    for(int i=0 ; i<SIZE ; i++)
    {
        printf("%d " , arr[i]);
    }
}
void function_reverse(int arr[])
{
    int temp[SIZE] , i , j;
    for(i=0 , j=SIZE-1 ; i < SIZE ; i++ , j--)
    {
        temp[i] = arr[j]; // swap
    }
    for(i=0 ; i < SIZE ; i++)
    {
        arr[i] = temp[i]; // reverse
    }
}

