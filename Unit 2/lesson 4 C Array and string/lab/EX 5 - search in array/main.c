/*
 * main.c
 *
 *  Created on: Jul 21, 2023
 *      Author: mohamed elatar
 */

#include <stdio.h>
void main()
{
	int arr[10] , n , i , num , position ;

	/************ number of elements **********/
	printf("Enter no of elements :");
	fflush(stdin);fflush(stdout);
	scanf("%d" , &n);

	/************ enter array from user **********/
	for(i=0 ; i<n ; i++)
    {
		printf("arr[%d]= " , i+1 );
		fflush(stdin);fflush(stdout);
        scanf("%d" , &arr[i] );

    }
    printf("\n");

    /********* enter element you need search *********/
    printf("Enter the element to be searched :");
    fflush(stdin);fflush(stdout);
	scanf("%d" , &num);
	for(i=0 ; i<n ; i++)
    {
        if(arr[i] == num)
        {
            printf("number found at the location = %d\n" , i+1 );
        }
    }
}
