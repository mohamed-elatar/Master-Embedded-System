/*
 * main.c
 *
 *  Created on: Jul 26, 2023
 *      Author: mohamed elatar
 */
#include <stdio.h>
void clear_bit(int *ptr_num , int position);
void main()
{
    int num , position;

    /******** input number  **********/
    printf("Enter number :");
    fflush(stdin); fflush(stdout);
    scanf("%d" , &num);

    /******** input number  **********/
    printf("Bit position :");
    fflush(stdin); fflush(stdout);
    scanf("%d" , &position);

    /************ call function **************/
    clear_bit(&num , position);
    printf("Number after clear bit %d:\n" , position);
    printf("result = %d" , num);
}

void clear_bit(int *ptr_num , int position)
{
    *ptr_num &= ~(1<<position);
}

