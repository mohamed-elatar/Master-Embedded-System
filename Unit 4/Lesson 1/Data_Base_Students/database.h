/*
 * database.h
 *
 *  Created on: Sep 12, 2023
 *      Author: mohamed elatar
 */

#ifndef DATABASE_H_
#define DATABASE_H_

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#pragma pack(1)

#define DPRINT(...) fflush(stdin);fflush(stdout); \
                    printf(__VA_ARGS__); \
                    fflush(stdin);fflush(stdout);

//Data type student
struct SData
{
    uint16_t ID;
    uint8_t name[20];
    float years;
    float height;
};

typedef struct SStudent
{
    struct SData data;
    struct SStudent * PNext_Student;
}S_node_student_t;

void student_Add();
void student_delete();
void students_delete_all();
void student_view();
void student_reverse();
void student_index_first_data(uint32_t record);
void student_index_end_data(uint32_t record);
uint32_t students_count();
uint32_t students_middle();
uint32_t students_loop();
uint32_t students_count_recursion(S_node_student_t * p);
#endif /* DATABASE_H_ */
