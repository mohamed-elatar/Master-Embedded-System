 /***********************************************
 * @file           : Pressure_Sensor_Driver.c   *
 * @author         : mohamed elatar             *
 * @Data           : 24/9/2023                  *
 * ARM Cortex M3   : Stm32f103C6                *
 ************************************************/


#include "Pressure_Sensor_Driver.h"

// pointer to function
void (*pf_Pressure_Sensor)();
uint32_t pressure_val;

void_Fun_define(Ps_init)
{
    // state sansor
    Pressure_Sensor_state_id = Ps_init;

    //looping until read pressure signal
    pf_Pressure_Sensor = void_Fun_symbol(Ps_reading);
}

void_Fun_define(Ps_reading)
{
    // state sansor
    Pressure_Sensor_state_id = Ps_reading;

    // get pressure from sensor
    pressure_val = getPressureVal();

    // send to main_algorithm
    set_pressure_val(pressure_val);

    pf_Pressure_Sensor = void_Fun_symbol(Ps_waiting);

}

void_Fun_define(Ps_waiting)
{
    // state sansor
    Pressure_Sensor_state_id = Ps_waiting;

    /******** when timer expires, it will detect pressure again **********/
    pf_Pressure_Sensor = void_Fun_symbol(Ps_reading);
}
