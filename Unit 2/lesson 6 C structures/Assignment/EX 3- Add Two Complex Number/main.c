/*
 * main.c
 *
 *  Created on: Aug 12, 2023
 *      Author: mohamed elatar
 */
#include <stdio.h>
typedef struct SComplex
{
    double m_real;
    double m_imag;
}Complex;
void input_complex(Complex *pS_1 , Complex *pS_2);
Complex sum_complex(Complex num_1 , Complex num_2);
void print_complex(Complex result);
int main()
{
    Complex num_1 , num_2 , sum;
    input_complex(&num_1,&num_2);
    sum = sum_complex(num_1,num_2);
    print_complex(sum);
}
void input_complex(Complex *pS_1 , Complex *pS_2)
{
    printf("For 1st complex:\n");
    printf("Enter real and imaginary respectively:");
    fflush(stdin);fflush(stdout);
    scanf("%lf %lf" , &pS_1->m_real , &pS_1->m_imag);

    printf("\n");

    printf("For 2nd complex:\n");
    printf("Enter real and imaginary respectively:");
    fflush(stdin);fflush(stdout);
    scanf("%lf %lf" , &pS_2->m_real , &pS_2->m_imag);
}
Complex sum_complex(Complex num_1 , Complex num_2)
{
    Complex sum;
    sum.m_real = num_1.m_real + num_2.m_real;
    sum.m_imag = num_1.m_imag + num_2.m_imag;
    return sum;
}
void print_complex(Complex result)
{
    if(result.m_imag >= 0) printf("result = %.1lf + %.1lfi" , result.m_real , result.m_imag);
    else printf("result = %.1lf - %.1lfi", result.m_real , result.m_imag*-1);
}


