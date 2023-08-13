/*
 * function.c
 *
 *  Created on: Aug 12, 2023
 *     Author: mohamed elatar
 */
#include <stdio.h>
#include "function.h"
#include <string.h>
#include <conio.h>
void read_employee(struct SEmployee *ptr)
{
	int j=3;
    do
    {
        printf("\n--------------------------------------------------------\n");
        printf("Enter first name and last name of [%i] employee : ",i+1);
        fflush(stdin);fflush(stdout);
        fgets((ptr+i)->m_name , 20 , stdin);

        printf("Enter Birth_Data day/month/year of [%i] employee : ",i+1);
        fflush(stdin);fflush(stdout);
        scanf("%d %d %d" , &(ptr+i)->m_Birth_Data.m_day , &(ptr+i)->m_Birth_Data.m_month ,&(ptr+i)->m_Birth_Data.year );

        (ptr+i)->m_Graduation_Data = read_data("Graduation_Data");

        printf("Enter salary of [%i] employee : ",i+1);
        fflush(stdin);fflush(stdout);
        scanf("%f" , &((ptr+i)->m_salary));

        i++;
        if(i==100) break;
        printf("\nif want add more press Y or N if want exit :");
        fflush(stdin);fflush(stdout);
    }while(getchar() == 'y');
}

struct SData read_data(char *p)
{
    struct SData data;
    printf("Enter %s day/month/year of [%i] employee : ", p ,i+1);
    fflush(stdin);fflush(stdout);
    scanf("%d %d %d" , &data.m_day , &data.m_month , &data.year);
    return data;
}

void print_employee(struct SEmployee arr[])
{
    int j=0;
    while(j<i)
    {
        printf("\n--------------------------------------------------------\n");
        printf("Name [%d] employee : %s" , j+1 , arr[j].m_name);

        printf("Birth Data [%d] employee : %d / %d / %d\n" ,
               j+1 , arr[j].m_Birth_Data.m_day ,
               arr[j].m_Birth_Data.m_month ,
               arr[j].m_Birth_Data.year);

        printf("Graduation Data [%d] employee : %d / %d / %d\n" ,
                j+1 , arr[j].m_Graduation_Data.m_day ,
                arr[j].m_Graduation_Data.m_month ,
                arr[j].m_Graduation_Data.year);

        printf("Salary [%d] employee : %f \n" , j+1 , arr[j].m_salary);
        j++;
    }
}

void sort(struct SEmployee arr[])
{
    struct SEmployee temp;
    int x , y;
    for(x=0 ; x<i-1 ; x++)
    {
        for(y=x+1 ; y<i ; y++)
        {
            if(arr[x].m_Birth_Data.year > arr[y].m_Birth_Data.year
               || (arr[x].m_Birth_Data.year == arr[y].m_Birth_Data.year
                   && arr[x].m_Birth_Data.m_month > arr[y].m_Birth_Data.m_month)
               || (arr[x].m_Birth_Data.year == arr[y].m_Birth_Data.year
                   && arr[x].m_Birth_Data.m_month == arr[y].m_Birth_Data.m_month
                   && arr[x].m_Birth_Data.m_day > arr[y].m_Birth_Data.m_day))
            {
                temp = arr[x];
                arr[x] = arr[y];
                arr[y] = temp;
            }
        }
    }
}

