/*
 * main.c
 *
 *  Created on: Jul 27, 2023
 *      Author: mohamed elatar
 */
#include <stdio.h>
int count_max_number_ones(int num);
void main()
{
    int num;
    printf("enter number :");
    fflush(stdout);
    scanf("%d" , &num);
    printf("max number of ones : %d" , count_max_number_ones(num));
}
int count_max_number_ones(int num)
{
    int count=0;
    while(num)
    {
        num = (num&((unsigned)num>>1));
        count++;
    }
    return count;
}


