 /***********************************************
 * @file           : Alarm_Monitor.h            *
 * @author         : mohamed elatar             *
 * @Data           : 24/9/2023                  *
 * ARM Cortex M3   : Stm32f103C6                *
 ************************************************/

#ifndef _Alarm_Monitor_H
#define _Alarm_Monitor_H

#include "state.h"

enum
{
    AM_init,
    AM_monitor,
    AM_alarm_on
}alarm_monitor_state_id;

void_Fun_define(AM_init);
void_Fun_define(AM_monitor);
void_Fun_define(AM_alarm_on);

extern void (*pf_alarm_monitor)();

#endif // _Alarm_Monitor_H
