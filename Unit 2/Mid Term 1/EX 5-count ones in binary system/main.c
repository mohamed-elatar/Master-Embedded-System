/*
 * main.c
 *
 *  Created on: Jul 27, 2023
 *      Author: mohamed elatar
 */
#include <stdio.h>
int count_one(int num);
void main()
{
    int num , ones;
    printf("Enter num :");
    fflush(stdin); fflush(stdout);
    scanf("%d" , &num);
    ones = count_one(num);
    printf("count ones in binary system is: %d" , ones);
}
int count_one(int num)
{
    int count=0 , i;
    int size = 8*sizeof(num);
    for(i=0 ; i<size ; i++)
    {
        if( (num&(1<<i))>>i )
            count++;
    }
    return count;
}

