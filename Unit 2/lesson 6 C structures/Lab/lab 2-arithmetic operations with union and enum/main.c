/*
 * main.c
 *
 *  Created on: Aug 12, 2023
 *      Author: mohamed elatar
 */
#include <stdio.h>
#include "function.h"
int main()
{
    union_v x , y , result;
    x.u_int_value = 20;
    y.u_int_value = 10;
    /*--------------------------------- mul integer -------------------------------------*/
    result = fun_operation(x,y,INT,MUL);
    printf("INT : %d * %d = %d\n\n" , x.u_int_value , y.u_int_value , result.u_int_value);
    /*--------------------------------- sub integer ----------------------------------------------*/
    result = fun_operation(x,y,INT,SUB);
    printf("INT : %d - %d = %d\n\n" , x.u_int_value , y.u_int_value , result.u_int_value);
    /*--------------------------------- div float --------------------------------------------*/
    x.u_float_value = 20.5;
    y.u_float_value = 10;
    result = fun_operation(x,y,FLOAT,DiV);
    printf("FLOAT : %f / %f = %f\n\n" , x.u_float_value , y.u_float_value , result.u_float_value);
    /*--------------------------------- sub double --------------------------------------------*/
    x.u_double_value = 35.6;
    y.u_double_value = 10.1;
    result = fun_operation(x,y,DOUBLE,SUB);
    printf("DOUBLE : %lf - %lf = %lf\n\n" , x.u_double_value , y.u_double_value , result.u_double_value);
    return 0;
}

