 /***********************************************
 * @file           : Alarm_Actuator_driver.c    *
 * @author         : mohamed elatar             *
 * @Data           : 24/9/2023                  *
 * ARM Cortex M3   : Stm32f103C6                *
 ************************************************/

#include "Alarm_Actuator_driver.h"

// pointer to function
void (*pf_alarm_actuator)();


void_Fun_define(AA_init)
{
    // state actuator
    alarm_actuator_state_id = AA_init;

    //when initialize turn off alarm
    Set_Alarm_actuator(high);

    pf_alarm_actuator = void_Fun_symbol(AA_waiting);
}

void_Fun_define(AA_waiting)
{
    // state actuator
    alarm_actuator_state_id = AA_waiting;

    pf_alarm_actuator = void_Fun_symbol(AA_waiting);
}

void_Fun_define(AA_alarm_turn_on)
{
    // state actuator
    alarm_actuator_state_id = AA_alarm_turn_on;

    pf_alarm_actuator = void_Fun_symbol(AA_alarm_turn_on);
}

void_Fun_define(AA_alarm_turn_off)
{
    // state actuator
    alarm_actuator_state_id = AA_alarm_turn_off;
    
    pf_alarm_actuator = void_Fun_symbol(AA_waiting);
}

void Start_Alarm()
{
    Set_Alarm_actuator(low);
    pf_alarm_actuator = void_Fun_symbol(AA_alarm_turn_on);
}

void Stop_Alarm()
{
    Set_Alarm_actuator(high);
    pf_alarm_actuator = void_Fun_symbol(AA_alarm_turn_off);
}
