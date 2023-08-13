/*
 * function.c
 *
 *  Created on: Aug 12, 2023
 *      Author: mohamed elatar
 */
#include "function.h"
Complex input_complex(double real,double imag)
{
    Complex num = {real , imag};
    return num;
}

Complex sum_complex(P_complex num_1 , P_complex num_2)
{
    Complex sum;
    sum.m_real = num_1->m_real + num_2->m_real;
    sum.m_imag = num_1->m_imag + num_2->m_imag;
    return sum;
}

Complex sub_complex(P_complex num_1 , P_complex num_2)
{
    Complex sub;
    sub.m_real = num_1->m_real - num_2->m_real;
    sub.m_imag = num_1->m_imag - num_2->m_imag;
    return sub;
}

Complex mul_complex(P_complex num_1 , P_complex num_2)
{
    Complex mul;
    mul.m_real = (num_1->m_real * num_2->m_real)-(num_1->m_imag * num_2->m_imag);
    mul.m_imag = (num_1->m_real * num_2->m_imag)+(num_2->m_real * num_1->m_imag);
    return mul;
}

Complex conjugate_complex(P_complex num)
{
    (num->m_imag) *= -1;
    return *num;
}

void remove_complex(P_complex num)
{
    num->m_real=0;
    num->m_imag=0;
}

void print_complex(P_complex ptr)
{
    if(ptr->m_imag >= 0) printf("%.2lf +  %.2lfi\n" , ptr->m_real , ptr->m_imag);
    else printf("%.2lf - j %.2lfi\n" , ptr->m_real , ptr->m_imag*-1);
}

