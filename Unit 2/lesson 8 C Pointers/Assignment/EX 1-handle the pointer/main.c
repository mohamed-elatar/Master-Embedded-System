/*
 * main.c
 *
 *  Created on: Aug 8, 2023
 *      Author: mohamed elatar
 */
#include <stdio.h>
int main()
{
	int m_variable = 29;
	printf("address of m_variable : %#x \n" , &m_variable);
	printf("value of m_variable : %d \n\n" , m_variable);

	printf("Now ptr is assigned with the address of m_variable: \n");
	int * ptr = &m_variable;
	printf("address of pointer : %#x \n" , ptr);
	printf("content of pointer : %d \n\n" , *ptr);

	printf("The value of m_variable assigned to 34 now: \n");
	m_variable = 34;
	printf("address of pointer : %#x \n" , ptr);
	printf("content of pointer : %d \n\n" , *ptr);

	printf("The pointer variable ptr is assigned with the value 7 now: \n");
	*ptr = 7;
	printf("address of m_variable : %#x \n" , &m_variable);
	printf("value of m_variable : %d \n\n" , m_variable);
	return 0;
}


