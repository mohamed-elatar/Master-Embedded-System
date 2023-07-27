/*
 * main.c
 *
 *  Created on: Jul 27, 2023
 *      Author: mohamed elatar
 */
#include <stdio.h>
int reverse_digit(int number);
void main()
{
	int num;;
	printf("Enter number :");
	fflush(stdout);
	scanf("%d" , &num);
	printf("reverse number is :%d" , reverse_digit(num));
}
int reverse_digit(int number)
{
	int temp , sum=0;
	if(number>=10 && number<100)
	{
		int i=10;
		while(number)
		{
			temp = number%10;
			sum += temp*i;
			number /= 10;
			i /= 10;
		}
	}
	else if(number>=100 && number<1000)
	{
		int i=100;
		while(number)
		{
			temp = number%10;
			sum += temp*i;
			number /= 10;
			i /= 10;
		}
	}
	else if(number>=1000 && number<10000)
	{
		int i=1000;
		while(number)
		{
			temp = number%10;
			sum  += (temp*i);
			number /= 10;
			i /= 10;
		}
	}
	return sum;
}


