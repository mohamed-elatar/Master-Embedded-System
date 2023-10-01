/***********************************************
 * @file           : FIFO.h						*
 * @author         : mohamed elatar             *
 * @Data           : 26/9/2023                  *
 ************************************************/

#ifndef FIFO_H_
#define FIFO_H_

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define DPRINT(...)  fflush(stdin);fflush(stdout); \
		printf(__VA_ARGS__); \
		fflush(stdin);fflush(stdout);


#define element_type Student_t
#define size_buffer 50
#define max_courses 5

typedef struct
{
	uint8_t first_name[20];
	uint8_t last_name[20];
	uint32_t roll;
	float gpa;
	uint32_t course_id[max_courses];
}Student_t;

typedef struct
{
	uint32_t length;
	uint32_t counter;
	element_type *base;
	element_type *head;
	element_type *tail;
}FIFO_BUF_t;

typedef enum
{
	FIFO_NO_ERROR,
	FIFO_FULL,
	FIFO_EMPTY,
	FIFO_NULL
}FIFO_STATUS;

enum
{
	enqueue_success ,
	dequeue_success ,
	exist_roll ,
	not_exist_roll ,
	total_students
};

FIFO_STATUS FiFO_Init (FIFO_BUF_t * FIFO_buf , element_type * buf , uint32_t length);
void FIFO_enqueue_student(FIFO_BUF_t * FIFO_buf);
void FIFO_dequeue_student(FIFO_BUF_t * FIFO_buf);


void add_student_by_manually(FIFO_BUF_t * FIFO_buf);
void add_student_from_file(FIFO_BUF_t * FIFO_buf);
void find_student_by_roll_num(FIFO_BUF_t * FIFO_buf);
void find_student_by_first_name(FIFO_BUF_t * FIFO_buf);
void find_course_enroll(FIFO_BUF_t * FIFO_buf);
void find_total_number_students(FIFO_BUF_t * FIFO_buf);
void delete_student(FIFO_BUF_t * FIFO_buf);
void update_student(FIFO_BUF_t * FIFO_buf);
void display_all_student(FIFO_BUF_t * FIFO_buf);

element_type* return_student_roll (FIFO_BUF_t * FIFO_buf , uint32_t roll);
void print_message(FIFO_BUF_t * FIFO_buf , uint32_t val);
void move_tail(FIFO_BUF_t * FIFO_buf , Student_t * student);
uint32_t check_roll (uint32_t roll);
uint32_t check_buffer_counter(FIFO_BUF_t * FIFO_buf);

#endif /* FIFO_H_ */
