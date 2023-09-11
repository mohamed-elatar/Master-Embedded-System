/*
 * LIFO.c
 *
 *  Created on: Sep 12, 2023
 *      Author: mohamed elatar
 */
#include "LIFO.h"

LIFO_STATUS Liof_Init (LIFO_BUF_t * lifo_buf , uint32_t * buf , uint32_t length)
{
    if(buf == 0) return LIFO_NULL;
    else
    {
        lifo_buf->base = buf;
        lifo_buf->head = buf;
        lifo_buf->length = length;
        lifo_buf->counter = 0;
        return LIFO_NO_ERROR;
    }
}

LIFO_STATUS Lifo_push_Item (LIFO_BUF_t * lifo_buf , uint32_t item)
{
    // check lifo is valid
    if(!lifo_buf->base || !lifo_buf->head) return LIFO_NULL;

    // check lifo if full
    else if(lifo_buf->head >= (lifo_buf->base + lifo_buf->length * sizeof(uint32_t)) )
        return LIFO_FULL;

    // push value
	else
	{
    	*(lifo_buf->head) = item;
    	lifo_buf->head++;
    	lifo_buf->counter++;
		return LIFO_NO_ERROR;
	}

}

LIFO_STATUS Lifo_Pop_Item (LIFO_BUF_t * lifo_buf , uint32_t * item)
{
    // check lifo is valid
    if(!lifo_buf->base || !lifo_buf->head) return LIFO_NULL;

    // check lifo if empty
    else if (lifo_buf->counter == 0) return LIFO_EMPTY;

    // pop value
    else
    {
    	lifo_buf->head--;
    	*item = *(lifo_buf->head);
    	lifo_buf->counter--;
    	return LIFO_NO_ERROR;
    }
}

LIFO_STATUS Lifo_Peek_Item (LIFO_BUF_t * lifo_buf , uint32_t * item)
{
    // check lifo is valid
    if(!lifo_buf->base || !lifo_buf->head) return LIFO_NULL;

    // check lifo if empty
    else if (lifo_buf->counter == 0) return LIFO_EMPTY;

    // peek value
    else
    {
        /*lifo_buf->head--;
        *item = *(lifo_buf->head);
        lifo_buf->head++;*/

        Lifo_Pop_Item(lifo_buf,item);
        *item = *(lifo_buf->head);
        Lifo_push_Item(lifo_buf,*item);
        return LIFO_NO_ERROR;
    }
}

void Lifo_print(LIFO_BUF_t * lifo_buf)
{
    uint32_t * temp = lifo_buf->head , i;
    if(lifo_buf->counter == 0)
    {
        printf("\n\nprint element stack\n");
        printf("===================================\n");
        printf("stack is empty ");
        printf("\n===================================\n");
    }
    else
    {
        printf("\n\nprint element stack\n");
        printf("===================================\n");
        for (i = 0; i < lifo_buf->counter  ; ++i) printf("%d \t" , *(--temp) );
        printf("\n===================================\n");
    }


}


