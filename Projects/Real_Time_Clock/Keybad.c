/*
 * Keybad.c
 *
 * Created: 5/6/2023 3:14:21 PM
 *  Author: mohamed_elatar
 */ 

#include "dio.h"
#include "Keybad.h"

void Keybad_vinit (void)
{
    DIO_vset_pin_direction(ROW_PORT , R1 , 1);
    DIO_vset_pin_direction(ROW_PORT , R2 , 1);
    DIO_vset_pin_direction(ROW_PORT , R3 , 1);
    DIO_vset_pin_direction(ROW_PORT , R4 , 1);

    DIO_vset_pin_direction(COL_PORT , C1 , 0);
    DIO_vset_pin_direction(COL_PORT , C2 , 0);
    DIO_vset_pin_direction(COL_PORT , C3 , 0);
    DIO_vset_pin_direction(COL_PORT , C4 , 0);

	DIO_vinternal_pull_up_pin(COL_PORT , C1 , 1);//pin_portname default is 1111 
	DIO_vinternal_pull_up_pin(COL_PORT , C2 , 1);
	DIO_vinternal_pull_up_pin(COL_PORT , C3 , 1);
	DIO_vinternal_pull_up_pin(COL_PORT , C4 , 1);	
}

unsigned char Keybad_u8read(void)
{
	char keybad[4][4] = { {'7','8','9','/'} , {'4','5','6','*'} , {'1','2','3','-'} , {'A','0','=','+'} };
    char Keypad_Row[] = { R1, R2, R3, R4 }; //rows
	char Keypad_Col[] = { C1, C2, C3, C4 }; //columns

	char row , column , x ;
	char retval = NOT_PRESSED;
	for (row=0 ; row<4 ; row++)
	{
		DIO_vwrite_pin_value(ROW_PORT , Keypad_Row[0] , 1);
		DIO_vwrite_pin_value(ROW_PORT , Keypad_Row[1] , 1);
		DIO_vwrite_pin_value(ROW_PORT , Keypad_Row[2] , 1);
		DIO_vwrite_pin_value(ROW_PORT , Keypad_Row[3] , 1);
		DIO_vwrite_pin_value(ROW_PORT , Keypad_Row[row] , 0);
		for (column=0 ; column<4 ; column++)
		{
			x=DIO_u8read_pin(COL_PORT , Keypad_Col[column]);
			if (x == 0)
			{
				retval = keybad[row][column];
				while(DIO_u8read_pin(COL_PORT , Keypad_Col[column]) == 0);//continuous pressed
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