/*
 * Keybad.c
 *
 * Created: 5/6/2023 3:14:21 PM
 *  Author: mohamed_elatar
 */ 

#include "dio.h"
#define portname 'c'
#define NOT_PRESSED 0xff

void Keybad_vinit (void)
{
	DIO_vset_port_direction(portname , 0x0f);
	DIO_vinternal_pull_up_pin(portname , 4 , 1);//pin_portname default is 1111 
	DIO_vinternal_pull_up_pin(portname , 5 , 1);
	DIO_vinternal_pull_up_pin(portname , 6 , 1);
	DIO_vinternal_pull_up_pin(portname , 7 , 1);	
}

unsigned char Keybad_u8read(void)
{
	char keybad[4][4] = { {'7','8','9','/'} , {'4','5','6','*'} , {'1','2','3','-'} , {'A','0','=','+'} };
	char row , column , x ;
	char retval = NOT_PRESSED;
	for (row=0 ; row<4 ; row++)
	{
		DIO_vwrite_pin_value(portname , 0 , 1);
		DIO_vwrite_pin_value(portname , 1 , 1);
		DIO_vwrite_pin_value(portname , 2 , 1);
		DIO_vwrite_pin_value(portname , 3 , 1);
		DIO_vwrite_pin_value(portname , row , 0);
		for (column=0 ; column<4 ; column++)
		{
			x=DIO_u8read_pin(portname , column+4);
			if (x == 0)
			{
				retval = keybad[row][column];
				while(DIO_u8read_pin(portname , column+4) == 0);//continuous pressed
				break;
			}
		}
		if (x == 0)
		{
			break;
		}
		
	}
	return retval;
}