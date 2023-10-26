/*
 * led.c
 *
 * Created: 4/26/2023 6:34:33 PM
 *  Author: mohamed_elatar
 */

/* HAL */

/*********************** driver_led ***********************************/

#include "dio.h"

/*************** initi led *****************/
void LED_vinit_pin (char portname , char pinnumber)
{
	DIO_vset_pin_direction(portname , pinnumber , 1);
}

/*************** initi led port *****************/
void LED_vinit_port (char portname , char numberpin)
{
	DIO_vset_port_direction(portname , numberpin);
}

/*************** turn on led *****************/
void LED_vturn_on_pin (char portname , char pinnumber)
{
	DIO_vwrite_pin_value(portname,pinnumber,1);
}

/*************** turn on port *****************/
void LED_vturn_on_port (char portname , char numberpin)
{
	DIO_vwrite_port_value(portname,numberpin);
}

/*************** turn off led *****************/
void LED_vturn_off_pin (char portname , char pinnumber)
{
	DIO_vwrite_pin_value(portname,pinnumber,0);
}

/*************** turn off port *****************/
void LED_vturn_off_port (char portname , char numberpin)
{
	DIO_vwrite_port_value(portname,numberpin);
}

/*************** toggle led *****************/
void LED_vtoggle_pin (char portname , char pinnumber)
{
	DIO_vtoggle_pin(portname,pinnumber);
}

/*************** toggle port *****************/
void LED_vtoggle_port (char portname )
{
	DIO_vtoggle_port(portname);
}

/*************** read led *****************/
unsigned char LED_u8read_pin(char portname , char pinnumber)
{
	return DIO_u8read_pin(portname,pinnumber);
}

/*************** read port *****************/
unsigned char LED_u8read_port(char portname)
{
	return DIO_u8read_port(portname);
}


/*********************** driver_end ***********************************/
