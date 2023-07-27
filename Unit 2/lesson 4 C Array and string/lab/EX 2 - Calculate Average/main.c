/*
 * main.c
 *
 *  Created on: Jul 21, 2023
 *      Author: mohamed elatar
 */

#include <stdio.h>
void main()
{
	int n_loop , row ;
	float arr[10] , sum=0.0 , avr=0.0 ;

	/************ input number **********/
	printf("Enter the numbers of data :");
	fflush(stdin);fflush(stdout);
	scanf("%d",&n_loop);

	/************ Constrains **********/
	if( ((n_loop > 9)&&(n_loop < 0)) )
    {
        printf("you must enter number between 0 to 9 \n");
    }
	for(row=0 ; row < n_loop ; row++)
    {
        printf("%d. Enter number: " , row+1);
        fflush(stdin);fflush(stdout);
        scanf("%f",&arr[row]);
        sum += arr[row];
    }
    avr = sum/n_loop ;
    printf("Average = %.2f" , avr);
}
