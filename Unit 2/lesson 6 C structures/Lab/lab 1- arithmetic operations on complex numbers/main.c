/*
 * main.c
 *
 *  Created on: Aug 12, 2023
 *      Author: mohamed elatar
 */
#include <stdio.h>
#include "function.h"
int main()
{
    int  i=0;
    Complex arr[5], result;
    arr[0]=input_complex(5,3);
    arr[1]=input_complex(7,2);
    arr[2]=input_complex(-3,-5);
    arr[3]=input_complex(6,-4);
    arr[4]=input_complex(-10,0);
    while(i<5) print_complex(&arr[i++]);

    printf("\n------------------------------\n");
    printf("sum two complex :\n");
    result = sum_complex(&arr[0],&arr[1]);
    print_complex(&result);

    printf("\n------------------------------\n");
    printf("sub two complex :\n");
    result = sub_complex(&arr[2],&arr[1]);
    print_complex(&result);

    printf("\n------------------------------\n");
    printf("mul two complex :\n");
    result = mul_complex(&arr[2],&arr[3]);
    print_complex(&result);

    printf("\n------------------------------\n");
    printf("conjugate a complex :\n");
    result = conjugate_complex(&arr[0]);
    print_complex(&result);

}


