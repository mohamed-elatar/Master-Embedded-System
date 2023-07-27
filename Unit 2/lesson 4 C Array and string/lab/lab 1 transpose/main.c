/*
 * main.c
 *
 *  Created on: Jul 20, 2023
 *      Author: mohamed elatar
 */
#include "stdio.h"
void main()
{
	int arr[3][3] = { {1,2,3} , {4,5,6} , {7,8,9} };
	int arr1[3][3];
	int n = sizeof(arr[0])/sizeof(int);

	for(int row=0 ; row<n ; row++)
	{
		for(int col=0 ; col<n ; col++)
		{
			printf("%d \t" , arr[row][col]);
		}
		printf("\n");
	}

	printf("after transpose matrix \n");

	for(int row=0 ; row<3 ; row++)
	{
		for(int col=0 ; (col<3)&&(row!=col)  ; col++)
		{
			arr[row][col] = arr[row][col] ^ arr[col][row]; // 2 ^ 4
			arr[col][row] = arr[row][col] ^ arr[col][row]; // 2 ^ 4 ^ 4 = 2
			arr[row][col] = arr[row][col] ^	arr[col][row]; // 2 ^ 4 ^ 2 = 4
		}
	}
	for(int row=0 ; row<3 ; row++)
		{
			for(int col=0 ; col<3 ; col++)
			{
				printf("%d \t" , arr[row][col]);
			}
			printf("\n");
		}
}
