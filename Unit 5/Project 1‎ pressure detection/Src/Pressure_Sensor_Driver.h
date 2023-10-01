 /***********************************************
 * @file           : Pressure_Sensor_Driver.h   *
 * @author         : mohamed elatar             *
 * @Data           : 24/9/2023                  *
 * ARM Cortex M3   : Stm32f103C6                *
 ************************************************/


#ifndef _Pressure_Sensor_Driver_H_
#define _Pressure_Sensor_Driver_H_

#include "state.h"


enum
{
    Ps_init,
    Ps_reading,
    Ps_waiting
}Pressure_Sensor_state_id;

void_Fun_define(Ps_init);
void_Fun_define(Ps_reading);
void_Fun_define(Ps_waiting);

extern void (*pf_Pressure_Sensor)();

#endif // _Pressure_Sensor_Driver_H_