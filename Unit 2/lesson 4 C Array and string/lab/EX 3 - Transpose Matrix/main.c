/*
 * main.c
 *
 *  Created on: Jul 21, 2023
 *      Author: mohamed elatar
 */

#include <stdio.h>
void main()
{
	int arr_1[3][3] , arr_2[3][3] ;
	int i , j , row , col ;

	/************ input rows and columns **********/
	printf("Enter row and column of matrix :");
	fflush(stdin);fflush(stdout);
	scanf("%d%d", &row , &col);

	/************ input elements **********/
	printf("Enter elements of matrix :\n");
	for(i=0 ; i<row ; i++)
    {
        for(j=0 ; j<col ; j++)
        {
            printf("Enter elements a%d%d :" , i+1 , j+1);
            fflush(stdin);fflush(stdout);
            scanf("%i" , &arr_1[i][j]);
        }
    }

	/************ current matrix entered **********/
	printf("Entered matrix :\n");
	for(i=0 ; i<row ; i++)
    {
        for(j=0 ; j<col ; j++)
        {
            printf("%d \t" , arr_1[i][j]);
        }
        printf("\n");
    }

	/************ Transpose matrix **********/
    for(i=0 ; i<row ; i++)
    {
        for(j=0 ; j<col ; j++)
        {
            arr_2[j][i] = arr_1[i][j] ;
        }
    }

    /************ final matrix **********/
    printf("transpose of matrix :\n");
	for(i=0 ; i<=row  ; i++)
    {
        for(j=0 ; j<col-1 ; j++)
        {
            printf("%d \t" , arr_2[i][j]);
        }
        printf("\n");
    }
}
