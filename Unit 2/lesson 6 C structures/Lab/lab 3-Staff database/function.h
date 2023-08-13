/*
 * function.h
 *
 *  Created on: Aug 12, 2023
 *      Author: mohamed elatar
 */

#ifndef FUNCTION_H_
#define FUNCTION_H_

struct SData
{
    int m_day;
    int m_month;
    int year;
};
struct SEmployee
{
    char m_name[20];
    struct SData m_Birth_Data;
    struct SData m_Graduation_Data;
    float m_salary;
};
void read_employee(struct SEmployee *ptr);
struct SData read_data(char *ptr);
void print_employee(struct SEmployee arr[]);
void sort(struct SEmployee arr[]);

int i;
#endif /* FUNCTION_H_ */
