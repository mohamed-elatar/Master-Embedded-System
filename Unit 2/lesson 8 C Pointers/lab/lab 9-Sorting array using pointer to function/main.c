/*
 * main.c
 *
 *  Created on: Aug 9, 2023
 *      Author: mohamed elatar
 */
#include <stdio.h>
#define Size 5
void swap(int *num_1 , int *num_2);
int compare(int num_1 , int num_2);
void sort(int *arr , int size , int (*ptr)(int , int));
int main()
{
    int arr[Size]={4,2,1,10,3};
    sort(arr,Size,compare);
    for(int i =0 ; i<Size ; i++)
    {
        printf("%u , " , arr[i]);
    }
}
void swap(int *num_1 , int *num_2)
{
    *num_1 = *num_1 ^ *num_2 ;
    *num_2 = *num_1 ^ *num_2 ;
    *num_1 = *num_1 ^ *num_2 ;
}
int compare(int num_1 , int num_2)
{
    if(num_1>num_2) return 1;
    return -1;
}
void sort(int *arr , int size , int (*ptr)(int , int))
{
    int i , j;
    for(i=0 ; i<Size-1 ; i++)
    {
        for(j=i+1 ; j<Size ; j++)
        {
            if((*ptr)(arr[i],arr[j]) > 0) // < sort ascending order and > sort descending order
            {
                swap(&arr[i],&arr[j]);
            }
        }
    }
}

