/*
 * main.c
 *
 *  Created on: Aug 12, 2023
 *      Author: mohamed elatar
 */
#include <stdio.h>
#include <math.h>
struct SCalculate
{
    int m_feet;
    float m_inch;
};
int main()
{
    struct SCalculate dis_1 , dis_2 , sum;
    /****** Enter 1st distance ********/
    printf("Enter information for 1st distance :\n");
    printf("Enter feet : ");
    fflush(stdin);fflush(stdout);
    scanf("%d" , &dis_1.m_feet);
    printf("Enter inch : ");
    fflush(stdin);fflush(stdout);
    scanf("%f" , &dis_1.m_inch);

    /****** Enter 2nd distance ********/
    printf("Enter information for 2nd distance :\n");
    printf("Enter feet : ");
    fflush(stdin);fflush(stdout);
    scanf("%d" , &dis_2.m_feet);
    printf("Enter inch : ");
    fflush(stdin);fflush(stdout);
    scanf("%f" , &dis_2.m_inch);

    sum.m_feet = dis_1.m_feet + dis_2.m_feet;
    sum.m_inch = dis_1.m_inch + dis_2.m_inch;
    if(sum.m_inch >= 12)
    {
        sum.m_inch /= 12;
        sum.m_inch--;
        sum.m_feet++;
    }
    printf("sum of distances : %d\"%0.2f\" \n" , sum.m_feet,sum.m_inch);
    return 0;
}

