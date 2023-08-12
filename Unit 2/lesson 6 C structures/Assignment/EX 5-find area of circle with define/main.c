/*
 * main.c
 *
 *  Created on: Aug 12, 2023
 *      Author: mohamed elatar
 */
#include <stdio.h>
#define Area_Circle(R) printf("Area = %0.2f" , (22.0/7)*R*R)
int main()
{
    int radius;
    printf("Enter the radius :");
    fflush(stdin);fflush(stdout);
    scanf("%d" , &radius);
    Area_Circle(radius);
    return 0;
}


