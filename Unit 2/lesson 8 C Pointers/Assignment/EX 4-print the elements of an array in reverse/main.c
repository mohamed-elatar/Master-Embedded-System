/*
 * main.c
 *
 *  Created on: Aug 8, 2023
 *      Author: mohamed elatar
 */
#include <stdio.h>
#define Size 5
int main()
{
    int arr[Size]={1,2,3,4,5} , *ptr;
    int i=0;
    ptr = &arr[Size-1]; //pointer point to last element in array
    for(i=0 ; i<Size ; i++)
    {
        printf("%d " , *ptr--);
    }
    return 0;
}



