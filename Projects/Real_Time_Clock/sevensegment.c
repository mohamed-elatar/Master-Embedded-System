/*
 * _7segment.c
 *
 * Created: 4/29/2023 1:25:37 PM
 *  Author: mohamed elater
 */ 

/*
 *HAL layer
 */ 

/*************************** driver 7segment ****************************/
#include "dio.h"
#define cc
//#define ca 

/********** init_7seg ************/
void SevenSegment_vinit (char portname , char numberpin)
{
	DIO_vset_port_direction(portname,numberpin);
}

/********** write_english_7seg ************/
void SevenSegment_vwrite_eg (char portname , char number)
{
	#if defined cc
	unsigned char arr[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x47,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
	DIO_vwrite_port_value(portname,arr[number]);
	
	#elif defined ca
	unsigned char arr[]={~0x3f,~0x06,~0x5b,~0x4f,~0x66,~0x6d,~0x7d,~0x47,~0x7f,~0x6f,~0x77,~0x7c,~0x39,~0x5e,~0x79,~0x71};
	DIO_vwrite_port_value(portname,arr[number]);
	
	#endif
}

/********** write_arabic_7seg ************/
void SevenSegment_vwrite_ar (char portname , char number)
{
	#if defined cc
	unsigned char arr[]={0x40,0x06,0x31,0x72,0x79,0x3f,0x07,0x3e,0x37,0x67};
	DIO_vwrite_port_value(portname,arr[number]);
	
	#elif defined ca
	unsigned char arr[]={0x40,0x06,0x31,0x72,0x79,0x3f,0x07,0x3e,0x37,0x67};
	DIO_vwrite_port_value(portname,~arr[number]);
	
	#endif
}

/***************** seven segment BCD *************************/
void SevenSegment_BCD_vinit (char portname , char start_num_pin)
{
	DIO_vset_pin_direction(portname , start_num_pin    , 1);
	DIO_vset_pin_direction(portname , start_num_pin +1 , 1);
	DIO_vset_pin_direction(portname , start_num_pin +2 , 1);
	DIO_vset_pin_direction(portname , start_num_pin +3 , 1);
}

/***************** seven segment low_nibble *************************/
void SevenSegment_BCD_vwrite_lownibble (char portname , char val)
{
	DIO_vlow_nibble_write(portname,val);
}

/***************** seven segment high_nibble *************************/
void SevenSegment_BCD_vwrite_highnibble (char portname , char val)
{
	DIO_vhigh_nibble_write(portname,val);
}

/*************************** end ****************************/