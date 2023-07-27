/*
 * main.c
 *
 *  Created on: Jul 27, 2023
 *      Author: mohamed elatar
 */
#include <stdio.h>
void find_prime_number(int start , int end);
void main()
{
    int num_1 ,num_2;
    printf("Enter two :");
    fflush(stdout);
    scanf("%d%d" , &num_1 ,&num_2);
    find_prime_number(num_1 , num_2);

}
void find_prime_number(int start , int end)
{
    int i , j , flag=0;

    for(i=start+1 ; i<end ; i++) // hint: 1 not prime number
    {
        for(j=2 ; j<i ; j++)
        {
            if(i % j ==0)
            {
                flag = 1;
                break;
            }
        }
        if(!flag) printf("%d " , i);
        else      flag=0;
    }
}


