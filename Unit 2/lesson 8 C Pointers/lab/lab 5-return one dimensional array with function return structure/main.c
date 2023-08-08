/*
 * main.c
 *
 *  Created on: Aug 8, 2023
 *      Author: mohamed elatar
 */
#include <stdio.h>
#define row 3
struct set_array * return_p_array_one_dim();
struct set_array return_array_one_dim();
struct set_array
{
	int arr_struct[row]
};
int main()
{
    int i;
    struct set_array arr_main = return_array_one_dim();
    struct set_array * p_arr_main = &arr_main;
    struct set_array * pp_arr_main = return_p_array_one_dim();
    for(i=0 ; i<row ; i++)
    {
        printf("%u  ," , arr_main.arr_struct[i]);
        printf("%u  ," , p_arr_main->arr_struct[i]);
        printf("%u  \n" , pp_arr_main->arr_struct[i]);
    }
}
struct set_array return_array_one_dim()
{
    static struct set_array arr_fun ={1,2,3};
    return arr_fun; // &arr_fun; incompatible types as function not return pointer
}

struct set_array * return_p_array_one_dim()
{
    static struct set_array arr_fun ={1,2,3};
    return &arr_fun; // arr_fun; incompatible types as function return pointer
}

