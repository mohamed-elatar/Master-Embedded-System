/*
 * main.c
 *
 *  Created on: Aug 8, 2023
 *      Author: mohamed elatar
 */
#include <stdio.h>
#define Size 2
typedef struct
{
    char Employee_name[20];
    int Employee_ID;
}Data;

void main()
{
    Data employee[Size]={{"mohamed",1001},{"alex",1002}};
    Data *arr[Size] = {&employee[0] , &employee[1]};
    Data *(*p)[Size] = arr;
    printf("--------use pointer to array of pointer to struct-----------\n\n");
    printf("%*s \n", 20 , "method one");
    printf("%s , %d \n" , (*(*p)[1]).Employee_name , (*(*p)[1]).Employee_ID );
    printf("%s , %d \n" , (*p)[1]->Employee_name , (*p)[1]->Employee_ID );
    printf("%*s \n", 20 , "method two");
    printf("%s , %d \n" , (*(*((*p)+1))).Employee_name , (*(*((*p)+1))).Employee_ID );
    printf("%s , %d \n" , (*((*p)+1))->Employee_name , (*((*p)+1))->Employee_ID );

    printf("\n--------use array of pointer to struct-----------\n\n");
    printf("%*s \n", 20 , "method one");
    printf("%s , %d \n" , (*arr[1]).Employee_name , (*arr[1]).Employee_ID );
    printf("%s , %d \n" , arr[1]->Employee_name , arr[1]->Employee_ID );
    printf("%*s \n", 20 , "method two");
    printf("%s , %d \n" , (**(arr+1)).Employee_name , (**(arr+1)).Employee_ID );
    printf("%s , %d \n" , (*(arr+1))->Employee_name , (*(arr+1))->Employee_ID );

    printf("\n--------use array of struct-----------\n\n");
    printf("%*s \n", 20 , "method one");
    printf("%s , %d \n" , employee[1].Employee_name , employee[1].Employee_ID );
    printf("%*s \n", 20 , "method two");
    printf("%s , %d \n" , (employee+1)->Employee_name , (employee+1)->Employee_ID );
}


