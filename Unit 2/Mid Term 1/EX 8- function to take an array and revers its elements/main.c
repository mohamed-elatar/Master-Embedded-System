/*
 * main.c
 *
 *  Created on: Jul 27, 2023
 *      Author: mohamed elatar
 */
#include <stdio.h>
#define size 5
void reverse_array(int arr[]);
void main()
{
    int arr[size]={1,2,3,4,5};
    int i;
    printf("after call function reverse:\n");
    reverse_array(arr);
    for(i=0 ; i<size ; i++) printf("%d ", arr[i]);
}
void reverse_array(int arr[])
{
    int i=0 , j=size-1;
    while(i < j)
    {
        arr[i] = arr[i]^arr[j]; //1^5
        arr[j] = arr[i]^arr[j]; //1^5^5 = 1
        arr[i] = arr[i]^arr[j]; //1^5^1 = 5
        i++;
        j--;
    }
}


