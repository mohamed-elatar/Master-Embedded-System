/*
 * main.c
 *
 *  Created on: Aug 8, 2023
 *      Author: mohamed elatar
 */
#include <stdio.h>
int main()
{
	char arr_alph[26] , *ptr=arr_alph;
	int i=0 , n ;
	n = sizeof(arr_alph)/sizeof(char) ;
	while(i<n)
	{
		*ptr= 'A'+i ;
		printf("%c  " , *ptr);
		ptr++;
		i++;
	}
	return 0;
}


