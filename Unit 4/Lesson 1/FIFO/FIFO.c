/*
 * FIFO.c
 *
 *  Created on: Sep 12, 2023
 *      Author: mohamed elatar
 */

/************* Circular QUEUE *****************/
#include "FIFO.h"

FIFO_STATUS Fiof_Init (FIFO_BUF_t * FIFO_buf , element_type * buf , uint32_t length)
{
    // check null
    if(!FIFO_buf) return FIFO_NULL;

    //initialize
    else
    {
        FIFO_buf->base = buf;
        FIFO_buf->head = buf;
        FIFO_buf->tail = buf;
        FIFO_buf->length = length;
        FIFO_buf->counter = 0;

        return FIFO_NO_ERROR;
    }
}

FIFO_STATUS FIFO_enqueue_Item (FIFO_BUF_t * FIFO_buf , element_type item)
{
    //check null
    if(!FIFO_buf->base || !FIFO_buf->head || !FIFO_buf->tail) return FIFO_NULL;

    //check full
    else if(FIFO_if_full(FIFO_buf) == FIFO_FULL ) return FIFO_FULL;

    //enqueue
    else
    {
        *(FIFO_buf->head) = item;
        FIFO_buf->counter++;
        if(FIFO_buf->head == ( (FIFO_buf->base) + ( (FIFO_buf->length)*sizeof(element_type)))) // counter = length
            FIFO_buf->head = FIFO_buf->base;
        else
            FIFO_buf->head++;

        return FIFO_NO_ERROR;
    }
}

FIFO_STATUS FIFO_dequeue_Item (FIFO_BUF_t * FIFO_buf , element_type * item)
{
    //check null
    if(!FIFO_buf->base || !FIFO_buf->head || !FIFO_buf->tail) return FIFO_NULL;

    //check empty
    else if(FIFO_if_empty (FIFO_buf) == FIFO_EMPTY) return FIFO_EMPTY;

    //dequeue
    else
    {
        *item = *(FIFO_buf->tail);
        FIFO_buf->counter--;
        if(FIFO_buf->tail == ( (FIFO_buf->base) + ( (FIFO_buf->length)*sizeof(element_type))))
            FIFO_buf->tail = FIFO_buf->base;
        else
            FIFO_buf->tail++;

        return FIFO_NO_ERROR;
    }
}

FIFO_STATUS FIFO_dequeue_peek_Item (FIFO_BUF_t * FIFO_buf , element_type * item)
{
    //check null
    if(!FIFO_buf->base || !FIFO_buf->head || !FIFO_buf->tail) return FIFO_NULL;

    //check empty
    else if(FIFO_if_empty (FIFO_buf) == FIFO_EMPTY) return FIFO_EMPTY;

    //peek only
    else
    {
        *item = *(FIFO_buf->tail);
        return FIFO_NO_ERROR;
    }
}

FIFO_STATUS FIFO_if_full (FIFO_BUF_t * FIFO_buf)
{
    //check null
    if(!FIFO_buf->base || !FIFO_buf->head || !FIFO_buf->tail) return FIFO_NULL;

    //check full
    else if(FIFO_buf->counter == FIFO_buf->length) return FIFO_FULL;

    // defualt
    else return FIFO_NO_ERROR;
}

FIFO_STATUS FIFO_if_empty (FIFO_BUF_t * FIFO_buf)
{
    //check null
    if(!FIFO_buf->base || !FIFO_buf->head || !FIFO_buf->tail) return FIFO_NULL;

    //check empty
    else if(FIFO_buf->counter == 0) return FIFO_EMPTY;

    // defualt
    else return FIFO_NO_ERROR;
}

void FIFO_count (FIFO_BUF_t * FIFO_buf)
{
    //check null
    if(!FIFO_buf->base || !FIFO_buf->head || !FIFO_buf->tail) printf("count queue is %d \n\n" , NULL);

    //check empty
    else if(FIFO_buf->counter == 0) printf("count queue is %d \n\n" , NULL);

    //check full
    else if(FIFO_buf->counter == FIFO_buf->length) printf("count queue is %d \n\n" , FIFO_buf->length);

    // defualt
    else printf("count queue is %d \n\n" ,FIFO_buf->counter);
}


void FIFO_print (FIFO_BUF_t * FIFO_buf)
{
    int i ;
    element_type * temp = FIFO_buf->tail;

    ////check empty
    if(FIFO_buf->counter == 0)
        printf("FIFO is empty \n");
    else
    {
        printf("\n========== FIFO print ==============\n");
        for(i=0 ; i<FIFO_buf->counter ; i++)
        {
            printf("\t %x \n" , *temp);
            temp++;
        }
        printf("==================\n");
    }
}

