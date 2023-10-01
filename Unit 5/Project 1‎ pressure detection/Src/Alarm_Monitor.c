 /***********************************************
 * @file           : Alarm_Monitor.c            *
 * @author         : mohamed elatar             *
 * @Data           : 24/9/2023                  *
 * ARM Cortex M3   : Stm32f103C6                *
 ************************************************/

#include "Alarm_Monitor.h"

// pointer to function
void (*pf_alarm_monitor)();


void_Fun_define(AM_init)
{
    // state monitor
    alarm_monitor_state_id = AM_init;

    pf_alarm_monitor = void_Fun_symbol(AM_monitor);
}

void_Fun_define(AM_monitor)
{
    // state monitor
    alarm_monitor_state_id = AM_init;

    // looping until detect high pressure
    pf_alarm_monitor = void_Fun_symbol(AM_monitor);
}

void_Fun_define(AM_alarm_on)
{
    // state monitor
    alarm_monitor_state_id = AM_init;

    // alarm turn on for specific delay(Timer)
    Start_Alarm();
    Delay(1250000);
    Stop_Alarm();

    pf_alarm_monitor = void_Fun_symbol(AM_monitor);
}

void detect_high_pressure()
{
    // get high pressure so must turn alarm
    pf_alarm_monitor = void_Fun_symbol(AM_alarm_on);
}
