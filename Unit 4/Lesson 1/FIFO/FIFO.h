/*
 * FIFO.h
 *
 *  Created on: Sep 12, 2023
 *      Author: mohamed elatar
 */

#ifndef FIFO_H_
#define FIFO_H_

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

// select data-type
#define element_type uint8_t

// create buffer
#define size_buffer 5


/*
 * length   : size queue
 * counter  : number of element inside queue
 * base     : start queue
 * head     : current position to enqueue
 * tail 	: current position to dequeue
 */

typedef struct
{
    uint32_t length;
    uint32_t counter;
    element_type *base;
    element_type *head;
    element_type *tail;
}FIFO_BUF_t;

/*
 * FIFO_NO_ERROR    : return 0
 * FIFO_FULL        : return 1
 * FIFO_EMPTY       : return 2
 * FIFO_NULL        : return 3
 */

typedef enum
{
    FIFO_NO_ERROR,
    FIFO_FULL,
    FIFO_EMPTY,
    FIFO_NULL
}FIFO_STATUS;

/*
 * initialize queue with parameter  &  with length and
 * queue_buffer : call by references
 * buffer : call by references
 * length : call by value
 * return status [0:3]
 */
FIFO_STATUS Fiof_Init (FIFO_BUF_t * FIFO_buf , element_type * buf , uint32_t length);

/*
 * enqueue with parameter
 * queue_buffer : call by references
 * item : call by value
 * return status [0:3]
 */
FIFO_STATUS FIFO_enqueue_Item (FIFO_BUF_t * FIFO_buf , element_type item);

/*
 * dequeue with parameter
 * queue_buffer : call by references
 * item : call by references
 * return status [0:3]
 */
FIFO_STATUS FIFO_dequeue_Item (FIFO_BUF_t * FIFO_buf , element_type * item);

/*
 * dequeue peek only not remove item from queue with parameter
 * queue_buffer : call by references
 * item : call by references
 * return status [0:3]
 */
FIFO_STATUS FIFO_dequeue_peek_Item (FIFO_BUF_t * FIFO_buf , element_type * item);

/*
 * check queue full with parameter
 * queue_buffer : call by references
 * return status [0:3]
 */
FIFO_STATUS FIFO_if_full (FIFO_BUF_t * FIFO_buf);

/*
 * check queue empty with parameter
 * queue_buffer : call by references
 * return status [0:3]
 */
FIFO_STATUS FIFO_if_empty (FIFO_BUF_t * FIFO_buf);

/*
 * count queue element with parameter
 * queue_buffer : call by references
 * return void
 */
void FIFO_count (FIFO_BUF_t * FIFO_buf);

/*
 * print queue with parameter
 * queue_buffer : call by references
 * return nothing
 */
void FIFO_print (FIFO_BUF_t * FIFO_buf);


#endif /* FIFO_H_ */
