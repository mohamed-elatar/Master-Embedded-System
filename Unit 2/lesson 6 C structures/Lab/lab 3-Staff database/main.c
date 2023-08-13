/*
 * main.c
 *
 *  Created on: Aug 12, 2023
 *      Author: mohamed elatar
 */
#include <stdio.h>
#include "function.h"
void main()
{
	struct SEmployee arr[100];
	read_employee(arr);

	printf("\n********************************\n");
	printf("%*s \n",20,"display data");
	printf("********************************");
	print_employee(arr);

	printf("\n********************************\n");
	printf("%20s \n","after sort");
	printf("********************************");

	sort(arr);
	print_employee(arr);
}

