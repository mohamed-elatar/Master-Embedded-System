/*
 * button.c
 *
 * Created: 4/26/2023 10:43:30 PM
 *  Author: mohamed elatar
 */

/* HAL */

/*********************** driver_BUTTON ***********************************/

#include "dio.h"

/*************** initi BUTTON *****************/
void BUTTON_vinit_pin (char portname , char pinnumber)
{
	DIO_vset_pin_direction(portname , pinnumber , 0);//input pin
}

/*************** initi BUTTON port *****************/
void BUTTON_vinit_port (char portname , char numberpin)
{
	DIO_vset_port_direction(portname , numberpin);//0x0000 input pins
}

/*************** read BUTTON *****************/
unsigned char BUTTON_u8read_pin(char portname , char pinnumber)
{
	return DIO_u8read_pin(portname,pinnumber);
}

/*************** read BUTTON port *****************/
unsigned char BUTTON_u8read_port(char portname)
{
	return DIO_u8read_port(portname);
}

/*************** internal pull up *****************/
void BUTTON_vinternal_pull_up_pin (char portname , char pinnumber , char pud_enable)
{
	DIO_vinternal_pull_up_pin(portname,pinnumber,pud_enable);// pud=0 , ddr=0 , port=1 --> enable internal pullup
}


/*********************** driver_end *******************************/
