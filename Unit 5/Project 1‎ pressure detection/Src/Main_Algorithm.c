 /***********************************************
 * @file           : Main_Algorithm.c           *
 * @author         : mohamed elatar             *
 * @Data           : 24/9/2023                  *
 * ARM Cortex M3   : Stm32f103C6                *
 ************************************************/

#include "Main_Algorithm.h"

// pointer to function
void (*pf_main_algorithm)();

int pressure_detect = 0;
int threshold = 20;

void_Fun_define(MA_init)
{
    // algorithm state
    main_algorithm_state_id = MA_init;

    pf_main_algorithm = void_Fun_symbol(MA_waiting);
}

void_Fun_define(MA_waiting)
{
    // algorithm state
    main_algorithm_state_id = MA_init;

    // looping until get val from sensor
    pf_main_algorithm = void_Fun_symbol(MA_waiting);
}

void_Fun_define(MA_detect)
{
    // algorithm state
    main_algorithm_state_id = MA_detect;

    // check pressure val
    if(pressure_detect > threshold)
        detect_high_pressure();

    pf_main_algorithm = void_Fun_symbol(MA_waiting);
}

void set_pressure_val(int pressure)
{
    // get pressure from sensor
    pressure_detect = pressure;

    pf_main_algorithm = void_Fun_symbol(MA_detect);
}
