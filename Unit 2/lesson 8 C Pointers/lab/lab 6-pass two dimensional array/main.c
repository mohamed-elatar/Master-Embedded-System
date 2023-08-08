/*
 * main.c
 *
 *  Created on: Aug 8, 2023
 *      Author: mohamed elatar
 */
#include <stdio.h>
#define row 3
#define col 3
void pass_array_two_dim(int arr[row][col] , int (*ptr_1)[row][col] , int (*ptr)[row] , int *arr_1 , int arr_2[]);
int main()
{
    int arr[row][col] = { {1,2,3} , {4,5,6} , {7,8,9} };
    pass_array_two_dim(arr , &arr , &arr[0][0] , arr[0] , &arr[0]); //*(arr) == &*(*(arr+0)+0)

}
void pass_array_two_dim(int arr[row][col] , int (*ptr_1)[row][col] , int (*ptr)[row] , int *arr_1 , int arr_2[])
{
    int i , j;
    for(i=0 ; i<row ; i++)
        for(j=0 ; j<col ; j++)
        {
            printf("%u  ,  %u\n" , arr[i][j] , (*ptr_1)[i][j] );
        }
    printf("--------------------------------------------------\n");
    for(i=0 ; i<row*col ; i++)
        printf("%u  ,  %u   , %u\n" , *arr_1++ , (*ptr)[i] , arr_2[i] );
}

