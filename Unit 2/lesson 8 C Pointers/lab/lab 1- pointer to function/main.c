/*
 * main.c
 *
 *  Created on: Aug 2, 2023
 *      Author: mohamed elatar
 */
#include <stdio.h>
#include <string.h>
void check(char *str_1 , char str_2[] ,int (*comp)(const char *,const char *));
int main()
{
    char str_1[10] , str_2[10];
    /********** pointer to fun string compare *************/
    int (*pointer)(const char * , const char *) = strcmp ;
    /********** input 1st string *****************/
    printf("enter first string :");
    fflush(stdin);fflush(stdout);
    fgets(str_1,10,stdin);
    /********** input 2nd string *****************/
    printf("enter second string :");
    fflush(stdin);fflush(stdout);
    fgets(str_2,10,stdin);
    /********** call check *****************/
    check(str_1,str_2,pointer);
    return 0;
}
void check(char *str_1 , char str_2[] ,int (*comp)(const char *,const char *))
{
    if(!(*comp)(str_1,str_2)) printf("strings are equal");
    else printf("strings are not equal");
}


