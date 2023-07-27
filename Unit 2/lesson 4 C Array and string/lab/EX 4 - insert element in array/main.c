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

    /********* enter element you need insert *********/
    printf("Enter the element to be inserted :");
    fflush(stdin);fflush(stdout);
	scanf("%d" , &num);

	/************ insert index this element **********/
	printf("Enter the location :");
	fflush(stdin);fflush(stdout);
	scanf("%d" , &position);

	/************ shift array before insert **********/
	for(i=n ; i>position-1 ; i--)
    {
        arr[i] = arr[i-1];
    }

	/************ array after insert **********/
    arr[position-1] = num;
    for(i=0 ; i<n+1 ; i++)  //n+1 as exist element add in size
    {
        printf("arr[%d]=%d ," , i+1 , arr[i]);
    }
}
