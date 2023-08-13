/*
 * function.h
 *
 *  Created on: Aug 12, 2023
 *      Author: mohamed elatar
 */

#ifndef FUNCTION_H_
#define FUNCTION_H_

typedef enum NUM_type{INT , FLOAT , DOUBLE}enum_ty;
typedef enum NUM_OPERATION{ADD , SUB , MUL , DiV}enum_op;
typedef union UNUM_number
{
    int u_int_value;
    float u_float_value;
    double u_double_value;
}union_v;

union_v fun_operation(union_v value_1 , union_v value_2 , enum_ty type, enum_op operation);


#endif /* FUNCTION_H_ */
