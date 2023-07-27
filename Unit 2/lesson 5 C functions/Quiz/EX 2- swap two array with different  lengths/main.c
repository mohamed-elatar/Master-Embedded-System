/*
 * main.c
 *
 *  Created on: Jul 26, 2023
 *      Author: mohamed elatar
 */
#include <stdio.h>
#define size    10
void scan_array(int arr[] , int n);
void print_array(int arr[] , int n);
void swap(int arr[] , int arr_1[]);

void main()
{
    int n1 , n2;
    int arr_1[size] , arr_2[size];
    /******** first array *************/
    printf("enter number of element 1st array :");
    fflush(stdin); fflush(stdout);
    scanf("%d" , &n1);
    printf("enter elements 1st array :");
    scan_array(arr_1,n1);

    /******** Second array *************/
    printf("enter number of element 2nd array :");
    fflush(stdin); fflush(stdout);
    scanf("%d" , &n2);
    printf("enter elements 1st array :");
    scan_array(arr_2,n2);

    /********* call swap function **********/
    swap(arr_1 , arr_2);

    printf("after swap:\r\n");
    printf("1st array :");

    print_array(arr_1 , n2);
    printf("2nd array :");
    print_array(arr_2 , n1);

}
void scan_array(int arr[] , int n)
{
    int i;
    fflush(stdin); fflush(stdout);
    for(i=0 ; i<n ; i++)
    {
        scanf("%d",&arr[i]);
    }
}

void print_array(int arr[] , int n)
{
    int i;
    for(i=0 ; i<n ; i++)
    {
        printf("%d ",arr[i]);
    }
    printf("\n");
}
void swap(int arr[] , int arr_1[])
{
    for (int i=0 ; i<size ; i++)
    {
        arr[i]   = arr[i] + arr_1[i];
        arr_1[i] = arr[i] - arr_1[i];
        arr[i]   = arr[i] - arr_1[i];
    }
    printf("\n");
}
