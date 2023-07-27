/*
 * main.c
 *
 *  Created on: Jul 19, 2023
 *      Author: mohamed elatar
 */
#include "stdio.h"
void main()
{
	float num1 , num2 , result;
	char operator ;
	printf("Enter operator either + or - or * or divide :");
	fflush(stdin);fflush(stdout);
	scanf("%c", &operator);

	printf("Enter two operands :");
	fflush(stdin);fflush(stdout);
	scanf("%f %f", &num1 , &num2);

	switch(operator)
	{
	case '+':
		result = num1 + num2 ;
		printf("%.1f %c %.1f = %.1f" , num1 , operator , num2 , result);
		break;
	case '-':
		result = num1 - num2 ;
		printf("%.1f %c %.1f = %.1f" , num1 , operator , num2 , result);
		break;
	case '*':
		result = num1 * num2 ;
		printf("%.1f %c %.1f = %.1f" , num1 , operator , num2 , result);
		break;
	case '/':
		result = num1 / num2 ;
		printf("%.1f %c %.1f = %.1f" , num1 , operator , num2 , result);
		break;
	}

}


