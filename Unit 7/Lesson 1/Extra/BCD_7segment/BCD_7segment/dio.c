/*
 * dio.c
 *
 * Created: 4/25/2023 11:28:37 AM
 *  Author: mohamed_elatar
 */ 

/* MCAL */

#include "standard_macros.h"

#define offset 0x20
#define SFR_IO8(logical) (*(volatile unsigned char*)(logical + offset)) //Special Function Register Input Output 8_Bit
/********** PORTA ************/
#define MY_DDRA  SFR_IO8(0x1A)
#define MY_PORTA SFR_IO8(0x1B)
#define MY_PINA  SFR_IO8(0x19)

/********** PORTB ************/
#define MY_DDRB  SFR_IO8(0x17)
#define MY_PORTB SFR_IO8(0x18)
#define MY_PINB  SFR_IO8(0x16)

/********** PORTC ************/
#define MY_DDRC  SFR_IO8(0x14)
#define MY_PORTC SFR_IO8(0x15)
#define MY_PINC  SFR_IO8(0x13)

/********** PORTD ************/
#define MY_DDRD  SFR_IO8(0x11)
#define MY_PORTD SFR_IO8(0x12)
#define MY_PIND  SFR_IO8(0x10)

/********* SFIO_R *************/
#define MY_SFIOR SFR_IO8(0x30) //PUD pull up disable

/************************************** Driver_DIO ****************************************/

/********* dirction_pin **************/
void DIO_vset_pin_direction(char portname , char pinnumber , char dirction)
{
	switch(portname)
	{
		case 'A':
		case 'a':
		if (dirction == 1)
		{
			SET_BIT(MY_DDRA,pinnumber);
		} 
		else
		{
			CLR_BIT(MY_DDRA,pinnumber);
		}
		break;
		
		case 'B':
		case 'b':
		if (dirction == 1)
		{
			SET_BIT(MY_DDRB,pinnumber);
		}
		else
		{
			CLR_BIT(MY_DDRB,pinnumber);
		}
		break;
		
		case 'C':
		case 'c':
		if (dirction == 1)
		{
			SET_BIT(MY_DDRC,pinnumber);
		}
		else
		{
			CLR_BIT(MY_DDRC,pinnumber);
		}
		break;
		
		case 'D':
		case 'd':
		if (dirction == 1)
		{
			SET_BIT(MY_DDRD,pinnumber);
		}
		else
		{
			CLR_BIT(MY_DDRD,pinnumber);
		}
		break;
	}
}


/********* write_pin **************/
void DIO_vwrite_pin_value(char portname , char pinnumber , char val)
{
	switch(portname)
	{
		case 'A':
		case 'a':
		if (val == 1)
		{
			SET_BIT(MY_PORTA,pinnumber);
		}
		else
		{
			CLR_BIT(MY_PORTA,pinnumber);
		}
		break;
		
		case 'B':
		case 'b':
		if (val == 1)
		{
			SET_BIT(MY_PORTB,pinnumber);
		}
		else
		{
			CLR_BIT(MY_PORTB,pinnumber);
		}
		break;
		
		case 'C':
		case 'c':
		if (val == 1)
		{
			SET_BIT(MY_PORTC,pinnumber);
		}
		else
		{
			CLR_BIT(MY_PORTC,pinnumber);
		}
		break;
		
		case 'D':
		case 'd':
		if (val == 1)
		{
			SET_BIT(MY_PORTD,pinnumber);
		}
		else
		{
			CLR_BIT(MY_PORTD,pinnumber);
		}
		break;
	}
}


/********* toggle_pin **************/
void DIO_vtoggle_pin(char portname , char pinnumber)
{
	switch(portname)
	{
		case 'A':
		case 'a':
		TOG_BIT(MY_PORTA,pinnumber);
		break;
		
		case 'B':
		case 'b':
		TOG_BIT(MY_PORTB,pinnumber);
		break;
		
		case 'C':
		case 'c':
		TOG_BIT(MY_PORTC,pinnumber);
		break;
		
		case 'D':
		case 'd':
		TOG_BIT(MY_PORTD,pinnumber);
		break;
	}
}


/********* read_pin **************/
unsigned char DIO_u8read_pin (char portname , char pinnumber)
{
	unsigned char ret_value;
	switch (portname)
	{
		case 'A':
		case 'a':
		ret_value = READ_BIT(MY_PINA,pinnumber);
		break;
		
		case 'B':
		case 'b':
		ret_value = READ_BIT(MY_PINB,pinnumber);
		break;
		
		case 'C':
		case 'c':
		ret_value = READ_BIT(MY_PINC,pinnumber);
		break;
		
		case 'D':
		case 'd':
		ret_value = READ_BIT(MY_PIND,pinnumber);
		break;
	}
	return ret_value;
}


/********* dirction_port **************/
void DIO_vset_port_direction(char portname , char direction)
{
	switch(portname)
	{
		case 'A':
		case 'a':
		MY_DDRA = direction;
		break;
		
		case 'B':
		case 'b':
		MY_DDRB = direction;
		break;
		
		case 'C':
		case 'c':
		MY_DDRC = direction;
		break;
		
		case 'D':
		case 'd':
		MY_DDRD = direction;
		break;
	}
}

/********* write_port **************/
void DIO_vwrite_port_value(char portname , char value)
{
	switch(portname)
	{
		case 'A':
		case 'a':
		MY_PORTA = value;
		break;
		
		case 'B':
		case 'b':
		MY_PORTB = value;
		break;
		
		case 'C':
		case 'c':
		MY_PORTC = value;
		break;
		
		case 'D':
		case 'd':
		MY_PORTD = value;
		break;
	}
}

/********* toggle_port **************/
void DIO_vtoggle_port(char portname)
{
	switch(portname)
	{
		case 'A':
		case 'a':
		MY_PORTA = ~MY_PORTA;
		break;
		
		case 'B':
		case 'b':
		MY_PORTB = ~MY_PORTB;
		break;
		
		case 'C':
		case 'c':
		MY_PORTC = ~MY_PORTC;
		break;
		
		case 'D':
		case 'd':
		MY_PORTD = ~MY_PORTD;
		break;
	}
}

/********* read_port **************/
unsigned char DIO_u8read_port(char portname)
{
	unsigned char read_value;
	switch(portname)
	{
		case 'A':
		case 'a':
		read_value = MY_PINA;
		break;
		
		case 'B':
		case 'b':
		read_value = MY_PINB;
		break;
		
		case 'C':
		case 'c':
		read_value = MY_PINC;
		break;
		
		case 'D':
		case 'd':
		read_value = MY_PINC;
		break;
	}
	return read_value;
}

/********* internal_pull up **************/
void DIO_vinternal_pull_up_pin(char portname , char pinnumber , char pud_enable)
{
	if (BIT_IS_CLR(MY_SFIOR,2))//check PUD(pull up disable pin is 0 (!0 true if)
	{
		switch(portname)
		{
			case 'A':
			case 'a':
			if (pud_enable == 1)
			{
				SET_BIT(MY_PORTA,pinnumber);
			}
			else
			{
				CLR_BIT(MY_PORTA,pinnumber);
			}
			break;
			
			case 'B':
			case 'b':
			if (pud_enable == 1)
			{
				SET_BIT(MY_PORTB,pinnumber);
			}
			else
			{
				CLR_BIT(MY_PORTB,pinnumber);
			}
			break;
			
			case 'C':
			case 'c':
			if (pud_enable == 1)
			{
				SET_BIT(MY_PORTC,pinnumber);
			}
			else
			{
				CLR_BIT(MY_PORTC,pinnumber);
			}
			break;
			
			case 'D':
			case 'd':
			if (pud_enable == 1)
			{
				SET_BIT(MY_PORTD,pinnumber);
			}
			else
			{
				CLR_BIT(MY_PORTD,pinnumber);
			}
			break;
		}
	}
}


/************** low nibble **************/
void DIO_vlow_nibble_write (char portname , char val)
{
	DIO_vwrite_pin_value(portname,0,READ_BIT(val,0));
	DIO_vwrite_pin_value(portname,1,READ_BIT(val,1));
	DIO_vwrite_pin_value(portname,2,READ_BIT(val,2));
	DIO_vwrite_pin_value(portname,3,READ_BIT(val,3));
	/*
	val &= 0x0f;
	switch (portname)
	{
		case 'A':
		case 'a':
		MY_PORTA &= 0xf0;
		MY_PORTA |= val;
		break;
		
		case 'B':
		case 'b':
		MY_PORTB &= 0xf0;
		MY_PORTB |= val;
		break;
		
		case 'C':
		case 'c':
		MY_PORTC &= 0xf0;
		MY_PORTC |= val;
		break;
		
		case 'D':
		case 'd':
		MY_PORTD &= 0xf0;
		MY_PORTD |= val;
		break;
	}
	*/
}

/************** high nibble **************/
void DIO_vhigh_nibble_write (char portname , char val) //val of BCD need least four bit  0x0__
{
	DIO_vwrite_pin_value(portname,4,READ_BIT(val,0));
	DIO_vwrite_pin_value(portname,5,READ_BIT(val,1));
	DIO_vwrite_pin_value(portname,6,READ_BIT(val,2));
	DIO_vwrite_pin_value(portname,7,READ_BIT(val,3));
	/*
	val <<= 4;
	switch (portname)
	{
		case 'A':
		case 'a':
		MY_PORTA &= 0x0f;
		MY_PORTA |= val;
		break;
		
		case 'B':
		case 'b':
		MY_PORTB &= 0xf0;
		MY_PORTB |= val;
		break;
		
		case 'C':
		case 'c':
		MY_PORTC &= 0xf0;
		MY_PORTC |= val;
		break;
		
		case 'D':
		case 'd':
		MY_PORTD &= 0xf0;
		MY_PORTD |= val;
		break;
	}
	*/
}
/*********************** end ************************/