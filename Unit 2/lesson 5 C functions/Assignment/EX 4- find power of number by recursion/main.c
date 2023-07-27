/*
 * main.c
 *
 *  Created on: Jul 25, 2023
 *      Author: mohamed elatar
 */
#include <stdio.h>
int power(int base_num , int power_num); //prototype
void main()
{
    int base_num , power_num;
    /************** enter base of number ******************/
    printf("Enter base number :");
    fflush(stdin); fflush(stdout);
    scanf("%d" , &base_num);

    /************** enter power of number ******************/
    printf("Enter power number(positive integer) :");
    fflush(stdin); fflush(stdout);
    scanf("%d" , &power_num);

    /************** print calculate ******************/
    printf("%d ^ %d = %d", base_num , power_num , power(base_num,power_num));
}
int power(int base_num , int power_num)
{
    return (power_num==1) ? (base_num) : (base_num*power(base_num , power_num-1));
}
