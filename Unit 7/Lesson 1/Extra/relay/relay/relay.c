/*
 * relay.c
 *
 * Created: 4/30/2023 4:34:55 PM
 *  Author: moham
 */ 


/*
 *HAL
 */


/*********************** driver relay ****************************/

#include "dio.h"

/***************** init relay ***********************/
void Relay_vinit_pin (char portname , char pinnumber)
{
	DIO_vset_pin_direction(portname , pinnumber , 1); //out pin
}

/***************** relay turn on ***********************/
void Relay_vturn_on_pin (char portname , char pinnumber)
{
	DIO_vwrite_pin_value(portname , pinnumber , 1); //out 5v
}

/***************** relay turn off ***********************/
void Relay_vturn_off_pin (char portname , char pinnumber)
{
	DIO_vwrite_pin_value(portname , pinnumber , 0); //out 0v
}
/*********************** end ****************************/