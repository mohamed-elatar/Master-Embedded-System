/*
 * main.c
 *
 *  Created on: Jul 27, 2023
 *      Author: mohamed elatar
 */
#include <stdio.h>
#define SIZE 7
int find_unique_num(int arr[]);
void main()
{
    int arr[SIZE] = {4,2,5,2,5,7,4};
    printf("unique number in array is %d" , find_unique_num(arr));
}
int find_unique_num(int arr[])
{
    int i , unique_num=0;
    for(i=0 ; i<SIZE ; i++)
    {
        unique_num ^= arr[i];
    }
    return unique_num;
}

