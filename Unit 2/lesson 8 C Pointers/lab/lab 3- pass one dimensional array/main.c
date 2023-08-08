/*
 * main.c
 *
 *  Created on: Aug 8, 2023
 *      Author: mohamed elatar
 */
#include <stdio.h>
#define row 3
#define col 3
void pass_array_one_dim(int arr[] , int * ptr , int (*ptr_1)[row]);
int main()
{
    int arr[row] = {1,2,3};
    pass_array_one_dim(arr , arr , arr); // or &arr
    return 0;
}
void pass_array_one_dim(int arr[] , int * ptr , int (*ptr_1)[row])
{
    int i=0;
    while(i<row)
    {
        printf("%u\n" , arr[i]); // *(arr+i)
        printf("%u\n" , *ptr);
        printf("%u\n\n" , (*ptr_1)[i]); // *((*ptr_1)+i)
        ptr++;
        i++;
    }
}

