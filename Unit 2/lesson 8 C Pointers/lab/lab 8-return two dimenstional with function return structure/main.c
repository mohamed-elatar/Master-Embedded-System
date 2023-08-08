/*
 * main.c
 *
 *  Created on: Aug 8, 2023
 *      Author: mohamed elatar
 */
#include <stdio.h>
#define row 3
#define col 3
struct set_array return_array_two_dim();
struct set_array
{
    int arr_struct[row][col];
};
int main()
{
    int i,j;
    struct set_array arr_main = return_array_two_dim();
    struct set_array *p = &arr_main;
    for (i=0 ; i<row ; i++)
    {
        for(j=0 ; j<col ; j++)
        {
            printf("%u  ,  " , arr_main.arr_struct[i][j]);
            printf("%u \n" , p->arr_struct[i][j]);
        }
        printf("\n");
    }
}
struct set_array return_array_two_dim()
{
    struct set_array arr_fun = {
        { {1,2,3},{4,5,6},{7,8,9} }
    };
    return arr_fun;
}

