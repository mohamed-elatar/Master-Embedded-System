/*
 * main.c
 *
 *  Created on: Sep 12, 2023
 *      Author: mohamed elatar
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "LIFO.h"

uint32_t buffer_1[5]; // global

int main()
{
    clock_t time;
    time = clock();
    int i , temp=0 ;
    LIFO_BUF_t UART_lifo , I2C_lifo; // LIFO Structure

    //static location
    Liof_Init(&UART_lifo , buffer_1 , 5);

    //dynamic location
    uint32_t * buffer_2 = (uint32_t*)malloc(5*sizeof(uint32_t));
    Liof_Init(&I2C_lifo , buffer_2 , 5);

    // push stack
    for(i=0 ; i<5 ; i++)
    {
        if( Lifo_push_Item(&UART_lifo , i) == LIFO_NO_ERROR )
            printf("UART_LIFO push : %d \n" , i);
    }
    Lifo_print(&UART_lifo);
    printf("\n\n");


    // peek
    if(Lifo_Peek_Item(&UART_lifo , &temp) == LIFO_NO_ERROR)
            printf("UART_LIFO peek : %d \n\n" , temp);

    // pop stack
    for(i=0 ; i<5 ; i++)
    {
        if(Lifo_Pop_Item(&UART_lifo , &temp) == LIFO_NO_ERROR)
            printf("UART_LIFO get : %d \n" , temp);
    }
    Lifo_print(&UART_lifo);

    printf("\n\n");
    time = clock() - time ;
    double time_taken = ((double)time)/CLOCKS_PER_SEC;
    printf("fun() main took %lf seconds to execute :\n" , time_taken);
}


