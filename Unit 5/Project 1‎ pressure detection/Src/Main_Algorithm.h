 /***********************************************
 * @file           : Main_Algorithm.h           *
 * @author         : mohamed elatar             *
 * @Data           : 24/9/2023                  *
 * ARM Cortex M3   : Stm32f103C6                *
 ************************************************/

#ifndef _Main_Alogrithm_H_
#define _Main_Alogrithm_H_

#include "state.h"

enum
{
    MA_init,
    MA_waiting,
    MA_detect
}main_algorithm_state_id;

void_Fun_define(MA_init);
void_Fun_define(MA_waiting);
void_Fun_define(MA_detect);

extern void (*pf_main_algorithm)();
#endif // _Main_Alogrithm_H_