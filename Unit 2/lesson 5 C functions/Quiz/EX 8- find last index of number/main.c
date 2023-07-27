/*
 * main.c
 *
 *  Created on: Jul 26, 2023
 *      Author: mohamed elatar
 */
#include <stdio.h>
#define size 7
void main()
{
    int arr[size] = {1,2,3,4,5,6,4};
    int index , num , flag=0;
    printf("enter number :");
    fflush(stdin); fflush(stdout);
    scanf("%d" , &num);

    /****** loop from reverse *********/
    for(index = size-1 ; index >=0 ; index--)
    {
        if(arr[index] == num)
        {
            flag = 1;
            break;
        }
    }
    if(flag == 1) printf("index number %d is %d" , num , index);
    else          printf("-1");

}

