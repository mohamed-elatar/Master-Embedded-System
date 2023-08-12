/*
 * main.c
 *
 *  Created on: Aug 12, 2023
 *      Author: mohamed elatar
 */
#include <stdio.h>
struct SData
{
    char m_name[20];
    int m_roll_number;
    float m_marks;
};
int main()
{
    struct SData student;
    /****** Enter name of student ********/
    printf("Enter name : ");
    fflush(stdin);fflush(stdout);
    gets(student.m_name);
    /****** Enter number of student ********/
    printf("Enter roll number : ");
    fflush(stdin);fflush(stdout);
    scanf("%d" , &student.m_roll_number);
    /****** Enter marks of student ********/
    printf("Enter markes : ");
    fflush(stdin);fflush(stdout);
    scanf("%f" , &student.m_marks);

    /******** print data **************/
    printf("\nDisplay Information\n");
    printf("\nname:%s \nroll:%d \nmarks:%.3f" , student.m_name ,
                                              student.m_roll_number ,
                                              student.m_marks);
    return 0;
}

