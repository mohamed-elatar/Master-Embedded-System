/*
 * main.c
 *
 *  Created on: Jul 27, 2023
 *      Author: mohamed elatar
 */
#include <stdio.h>
#include <string.h>
#define size 20
void reverse_string(char arr[] , int length);
void main()
{
    int i;
    char arr[size]="mohamed gamal";
    int length = strlen(arr);
    printf("string after reverse:\n");
    reverse_string(arr , length);
    puts(arr);
}
void reverse_string(char arr[] , int length)
{
    int i=0 , j=0;
    char temp_first[size] , temp_secand[size];
    while(arr[i] != ' ')
    {
        temp_secand[i] = arr[i];
        i++;
    }
    temp_secand[i] = '\0';
    while(arr[i++] != '\0')
    {
        temp_first[j++] = arr[i];
    }
    strcpy(arr , temp_first);
    strcat(arr , " ");
    strcat(arr , temp_secand);
}


