/*
 * function.h
 *
 *  Created on: Aug 12, 2023
 *      Author: mohamed elatar
 */

#ifndef FUNCTION_H_
#define FUNCTION_H_

struct SComplex
{
    double m_real;
    double m_imag;
};
typedef struct SComplex Complex, * P_complex;
Complex input_complex(double real,double imag);
Complex sum_complex(P_complex num_1 , P_complex num_2);
Complex sub_complex(P_complex num_1 , P_complex num_2);
Complex mul_complex(P_complex num_1 , P_complex num_2);
Complex conjugate_complex(P_complex num);
void remove_complex(P_complex num);
void print_complex(P_complex ptr);

#endif /* FUNCTION_H_ */
