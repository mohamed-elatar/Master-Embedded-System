/*
 * main.c
 *
 *  Created on: Sep 12, 2023
 *      Author: mohamed elatar
 */
#include "FIFO.h"
element_type UART_buf[size_buffer]; // global
int main()
{
    clock_t time;
    time = clock();
    FIFO_BUF_t FIFO_UART;
    element_type i , temp;
    if(Fiof_Init(&FIFO_UART , UART_buf , 5) == FIFO_NO_ERROR)
        printf("FIFO init done \n\n");

    for(i=0 ; i<7 ; i++)
    {
        printf("FIFO Enqueue (%x) \n" , i);
        if(FIFO_enqueue_Item(&FIFO_UART , i) == FIFO_NO_ERROR)
            printf("\t FIFO Enqueue Done \n");
        else
            printf("\t FIFO Enqueue failed as queue is full\n");
    }

    FIFO_print(&FIFO_UART);
    FIFO_count(&FIFO_UART);

    if(FIFO_dequeue_Item(&FIFO_UART , &temp) == FIFO_NO_ERROR)
        printf("FIFO dequeue (%x) done \n" , temp);

    if(FIFO_dequeue_Item(&FIFO_UART , &temp) == FIFO_NO_ERROR)
        printf("FIFO dequeue (%x) done \n" , temp);

    if(FIFO_dequeue_peek_Item(&FIFO_UART , &temp) == FIFO_NO_ERROR)
        printf("FIFO dequeue peek (%x) done \n" , temp);

    FIFO_print(&FIFO_UART);
    FIFO_count(&FIFO_UART);

    time = clock() - time;
    double time_taken = ((double)time)/CLOCKS_PER_SEC;
    printf("fun() main took %lf seconds to execute :\n" , time_taken);
    return 0;
}


