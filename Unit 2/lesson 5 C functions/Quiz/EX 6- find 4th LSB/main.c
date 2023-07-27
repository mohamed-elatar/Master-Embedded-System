/*
 * main.c
 *
 *  Created on: Jul 26, 2023
 *      Author: mohamed elatar
 */
#include <stdio.h>
void main()
{
    int num , four_LSB , size ;
    printf("Enter num :");
    fflush(stdin); fflush(stdout);
    scanf("%d" , &num);

    printf("%d in binary number system :" , num);
    size = 8*sizeof(num);
    for (size-- ; size>=0 ; size-- )
    {
    	printf("%d" , ((num>>(unsigned int)size)&1) );
    }
    printf("\n");
    four_LSB = ((num&(1u<<3))>>3) ; // read specific bit
    printf("4th least significant is %d" , four_LSB);
}
