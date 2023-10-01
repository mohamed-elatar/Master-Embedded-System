 /***********************************************
 * @file           : Alarm_Actuator_driver.h    *
 * @author         : mohamed elatar             *
 * @Data           : 24/9/2023                  *
 * ARM Cortex M3   : Stm32f103C6                *
 ************************************************/

#ifndef _Alarm_Actuator_driver_H
#define _Alarm_Actuator_driver_H

#include "state.h"

enum
{
    AA_init,
    AA_waiting,
    AA_alarm_turn_on,
    AA_alarm_turn_off
}alarm_actuator_state_id;

void_Fun_define(AA_init);
void_Fun_define(AA_waiting);
void_Fun_define(AA_alarm_turn_on);
void_Fun_define(AA_alarm_turn_off);

extern void (*pf_alarm_actuator)();


#endif // _Alarm_Actuator_driver_H
