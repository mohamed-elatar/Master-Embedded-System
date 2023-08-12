/*
 * main.c
 *
 *  Created on: Aug 12, 2023
 *      Author: mohamed elatar
 */
#include <stdio.h>
#define Size 3
struct SData
{
    char m_name[20];
    int m_roll_number;
    float m_marks;
};
int main()
{
    int i;
    struct SData student[Size];
    /******  info ********/
    printf("Enter information of students : \n");
    printf("**************************************\n");
    for(i=0 ; i<Size ; i++)
    {
        printf("For roll number %i: \n" , i+1);
        printf("Enter name : ");
        fflush(stdin);fflush(stdout);
        gets(student[i].m_name);
        printf("Enter marks : ");
        fflush(stdin);fflush(stdout);
        scanf("%f" , &student[i].m_marks);
        printf("-----------------------------\n");
    }
    /******** print info **************/
    printf("Display information of students \n");
    printf("**************************************\n");
    for(i=0 ; i<Size ; i++)
    {
        printf("information for roll number %i: \n" , i+1);
        printf("name : %s\n" , student[i].m_name);
        printf("marks : %f\n" , student[i].m_marks);
        printf("-----------------------------\n");
    }
    return 0;
}

