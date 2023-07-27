/*
 * main.c
 *
 *  Created on: Jul 27, 2023
 *      Author: mohamed elatar
 */
#include <stdio.h>
#include <math.h>
float find_root(int num , int root);
void main()
{
	/********** input number ***********/
    int num , root;
    printf("Enter number :");
    fflush(stdout);
    scanf("%d" , &num);
    /********* input root ****************/
    printf("Enter root :");
    fflush(stdout);
    scanf("%d" , &root);
    /********* call function ************/
    printf("square root of %d is %.3f" , num,find_root(num , root));
}
float find_root(int num , int root)
{
    return pow(num , 1.0/root) ;
}


