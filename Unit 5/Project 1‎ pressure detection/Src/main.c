 /***********************************************
 * @file           : main.c                     *
 * @author         : mohamed elatar             *
 * @Data           : 24/9/2023                  *
 * ARM Cortex M3   : Stm32f103C6                *
 ************************************************/

#include "Pressure_Sensor_Driver.h"
#include "Main_Algorithm.h"
#include "Alarm_Monitor.h"
#include "Alarm_Actuator_driver.h"


void setup(void)
{
    pf_Pressure_Sensor  = void_Fun_symbol(Ps_init);
    pf_main_algorithm   = void_Fun_symbol(MA_init);
    pf_alarm_monitor    = void_Fun_symbol(AM_init);
    pf_alarm_actuator   = void_Fun_symbol(AA_init);
}


int main (){
	GPIO_INITIALIZATION();
    setup();

	while (1)
	{
        pf_Pressure_Sensor();
        pf_main_algorithm();
        pf_alarm_monitor();
        pf_alarm_actuator();
	}
}


