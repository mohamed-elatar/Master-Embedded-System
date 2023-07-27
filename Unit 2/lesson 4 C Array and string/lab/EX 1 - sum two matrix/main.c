/*
 * main.c
 *
 *  Created on: Jul 21, 2023
 *      Author: mohamed elatar
 */

#include <stdio.h>
void main()
{
	float matrix_1 [2][2] , matrix_2 [2][2] , matrix[2][2];
	int row , col , n = sizeof(matrix_1[0])/sizeof(float);

	/************ input first matrix **********/
	printf("Enter elements of 1st matrix: \n");
	for(row=0 ; row < n ; row++)
	{
		for(col=0 ; col < n ; col++)
		{
			printf("Enter a%d%d : " , row+1 , col+1);
			fflush(stdin);fflush(stdout);
			scanf("%f",&matrix_1[row][col]);
		}
	}

	/************ input second matrix **********/
	printf("Enter elements of 2nd matrix: \n");
	for(row=0 ; row < n ; row++)
	{
		for(col=0 ; col < n ; col++)
		{
			printf("Enter b%d%d : " , row+1 , col+1);
			fflush(stdin);fflush(stdout);
			scanf("%f",&matrix_2[row][col]);
		}
	}

	/************ sum two matrix **********/
	printf("sum matrix: \n");
	for(row=0 ; row < n ; row++)
	{
		for(col=0 ; col < n ; col++)
		{
			matrix[row][col] = matrix_1[row][col] + matrix_2[row][col] ;
		}
	}

	/************ display final matrix **********/
	for(row=0 ; row < n ; row++)
	{
		for(col=0 ; col < n ; col++)
		{
			printf("%.1f\t" , matrix[row][col]);
		}
		printf("\n");
	}
}
