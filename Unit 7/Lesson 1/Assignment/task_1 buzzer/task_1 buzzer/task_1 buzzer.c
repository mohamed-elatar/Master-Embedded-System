/*
 * task_1_buzzer.c
 *
 * Created: 10/26/2023 3:07:25 AM
 *  Author: mohamed elatar
 */ 


#define F_CPU 8000000ul
#include "dio.h"

int main(void)
{
    DIO_vset_pin_direction('d' , 0 , 0); //input pin
    DIO_vset_pin_direction('d' , 4 , 1); //output pin

    while(1)
    {
        //TODO:: Please write your application code 
        if (DIO_u8read_pin('d' , 0) == 1) // pull down
        {
            // enable buzzer
            DIO_vwrite_pin_value('d' , 4 , 1);
        }
    }
}