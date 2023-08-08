/*
 * main.c
 *
 *  Created on: Aug 8, 2023
 *      Author: mohamed elatar
 */
#include <stdio.h>
#define row 3
#define col 3
int * return_array_two_dim();
int main()
{
    int i,j;
    int *ptr = return_array_two_dim();
    int *ptr_1 = return_array_two_dim();
    for (i=0 ; i<row*col ; i++ )
    {
        printf("%u  ,  %u\n" , ptr[i] , *ptr_1++);

    }
}
int * return_array_two_dim()
{
    static int arr[row][col] = {{1,2,3} , {4,5,6} , {7,8,9}};
    return arr; // &arr[0][0] , &arr , arr[0] , *arr
}
