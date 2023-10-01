 /***********************************************
 * @file           : state.h 					*
 * @author         : mohamed elatar             *
 * @Data           : 24/9/2023                  *
 * ARM Cortex M3   : Stm32f103C6                *
 ************************************************/

#ifndef _state_H
#define _state_H

#include <stdint.h>
#include "driver.h"

#define low  0
#define high 1

#define void_Fun_define(name) void Fun_##name()
#define void_Fun_symbol(name) Fun_##name


//connection between Modules
void set_pressure_val(int pressure);
void detect_high_pressure();
void Start_Alarm();
void Stop_Alarm();

#endif // _state_H