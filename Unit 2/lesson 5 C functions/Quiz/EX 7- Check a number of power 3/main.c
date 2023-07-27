/*
 * main.c
 *
 *  Created on: Jul 26, 2023
 *      Author: mohamed elatar
 */
#include <stdio.h>
#include <math.h>
int function_power_3(int num); //prototype
int check_power_of3(int num);  //prototype
void main()
{
	int num;
	/******** input number want to check **********/
	printf("Enter number :");
	fflush(stdin); fflush(stdout);
	scanf("%d" , &num);

	/************ call function **************/
	if(check_power_of3(num)) printf("%d is a power of 3" , num);
	else                     printf("%d is not a power of 3" , num);
}
int function_power_3(int num)
{
	int return_val = 1 ;
	int arr[20]= {} ;
	arr[0] = 3 ;
	for(int i=1 ; i<20 ; i++)
	{
		arr[i] = arr[i-1] * 3 ;//append elements of power 3
	}

	for(int i=0 ; i<20 ; i++)
	{
		if(num == arr[i]) return_val=0;// this a power num of 3
	}
	return return_val;
}

int check_power_of3(int num)
{
	double i = log(num) / log(3) ;
	return i == trunc(i);//if integer return n
}
