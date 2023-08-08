/*
 * main.c
 *
 *  Created on: Aug 8, 2023
 *      Author: mohamed elatar
 */
#include <stdio.h>
#include <time.h>
#define row 3
#define col 3
int * return_array_one_dim();
int main()
{
    //int arr[row]=return_array_one_dim(); error: invalid initializer
    int i;
    int *ptr = return_array_one_dim() ;
    for(i=0 ; i<row ; i++)
    {
        printf("%u\n" , *ptr++);
    }
}
int * return_array_one_dim()
{
    int i ;
    static int arr[row];
    srand(time(NULL));
    for(i=0 ; i<row  ; i++)
    {
        arr[i] = (rand()%(20-10))+10 ;//[10:19]
    }
    return arr; // or &arr
}

