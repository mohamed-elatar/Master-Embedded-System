/*
 * fuunction.c
 *
 *  Created on: Aug 12, 2023
 *      Author: mohamed elatar
 */
#include "function.h"
union_v fun_operation(union_v value_1 , union_v value_2 , enum_ty type, enum_op operation)
{
    union_v result;
    switch(type)
    {
    case INT:
        switch(operation)
        {
        case ADD:
            result.u_int_value = value_1.u_int_value + value_2.u_int_value;
            break;
        case SUB:
            result.u_int_value = value_1.u_int_value - value_2.u_int_value;
            break;
        case MUL:
            result.u_int_value = value_1.u_int_value * value_2.u_int_value;
            break;
        case DiV:
            result.u_int_value = value_1.u_int_value / value_2.u_int_value;
            break;
        }
        break;

    case FLOAT:
        switch(operation)
        {
        case ADD:
            result.u_float_value = value_1.u_float_value + value_2.u_float_value;
            break;
        case SUB:
            result.u_float_value = value_1.u_float_value - value_2.u_float_value;
            break;
        case MUL:
            result.u_float_value = value_1.u_float_value * value_2.u_float_value;
            break;
        case DiV:
            result.u_float_value = value_1.u_float_value / value_2.u_float_value;
            break;
        }
        break;

    case DOUBLE:
        switch(operation)
        {
        case ADD:
            result.u_double_value = value_1.u_double_value + value_2.u_double_value;
            break;
        case SUB:
            result.u_double_value = value_1.u_double_value - value_2.u_double_value;
            break;
        case MUL:
            result.u_double_value = value_1.u_double_value * value_2.u_double_value;
            break;
        case DiV:
            result.u_double_value = value_1.u_double_value / value_2.u_double_value;
            break;
        }
        break;
    }
    return result;
}


