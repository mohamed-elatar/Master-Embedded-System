/*
 * LIFO.h
 *
 *  Created on: Sep 12, 2023
 *      Author: mohamed elatar
 */

#ifndef LIFO_H_
#define LIFO_H_

#include <stdint.h>

/*
 * length   : size stack
 * counter  : number of element inside stack
 * base     : start stack
 * head     : current position to push
 */

typedef struct
{
    uint32_t length;
    uint32_t counter;
    uint32_t *base;
    uint32_t *head;
}LIFO_BUF_t;

/*
 * LIFO_NO_ERROR    : return 0
 * LIFO_FULL        : return 1
 * LIFO_EMPTY       : return 2
 * LIFO_NULL        : return 3
 */

typedef enum
{
    LIFO_NO_ERROR,
    LIFO_FULL,
    LIFO_EMPTY,
    LIFO_NULL
}LIFO_STATUS;

/*
 * initialize stack with parameter  &  with length and
 * stack_buffer : call by references
 * buffer : call by references
 * length : call by value
 * return status [0:3]
 */
LIFO_STATUS Liof_Init       (LIFO_BUF_t * lifo_buf , uint32_t * buf , uint32_t length);

/*
 * push stack with parameter
 * stack_buffer : call by references
 * item : call by value
 * return status [0:3]
 */
LIFO_STATUS Lifo_push_Item   (LIFO_BUF_t * lifo_buf , uint32_t item);

/*
 * pop stack with parameter
 * stack_buffer : call by references
 * item : call by references
 * return status [0:3]
 */
LIFO_STATUS Lifo_Pop_Item   (LIFO_BUF_t * lifo_buf , uint32_t * item);

/*
 * peek stack with parameter
 * stack_buffer : call by references
 * item : call by references
 * return status [0:3]
 */
LIFO_STATUS Lifo_Peek_Item (LIFO_BUF_t * lifo_buf , uint32_t * item);

/*
 * print stack with parameter
 * stack_buffer : call by references
 * return void */
void Lifo_print(LIFO_BUF_t * lifo_buf);


#endif /* LIFO_H_ */
