/*
 * main.c
 *
 *  Created on: Aug 8, 2023
 *      Author: mohamed elatar
 */
#include <stdio.h>
void fun_reverse_string(char *ptr , char *ptr_reverse ,int count);
int fun_count_string(char *pointer);
int main()
{
    char string[20] , reverse_string[20];
    int count;
    /******** string ***********/
    printf("input a string :");
    fflush(stdin);fflush(stdout);
    fgets(string,20,stdin);
    /******* call count **************/
    count = fun_count_string(string);
    /******** call reverse function *********/
    fun_reverse_string(string,reverse_string,count);
    /****** print reverse string ***********/
    printf("after reverse with pointer ");
    puts(reverse_string);
}
int fun_count_string(char *pointer)
{
    int count=0;
    while(*pointer != 0)
    {
        count++;
        pointer++;
    }
    return count;
}
void fun_reverse_string(char *ptr , char *ptr_reverse ,int count)
{
    ptr += count-1;
    while(count > 0)
    {
        *ptr_reverse++ = *ptr-- ;
        count--;
    }
    *ptr_reverse = '\0';
}

