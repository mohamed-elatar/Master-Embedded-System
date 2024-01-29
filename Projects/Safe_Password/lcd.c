/*
 * lcd.c
 *
 * Created: 5/4/2023 9:05:22 PM
 *  Author: mohamed_elatar
 */ 

#define F_CPU 8000000UL
#include <util/delay.h>
#include "configure_lcd.h"
#include "dio.h"
#include "standard_macros.h"

/****** Some_Macro *******/
#define EN						0
#define RW						1
#define RS						2

#define Clear_Screen			0x01
#define Return_Home				0x02

/********* display_and_cursor *********/
#define shift_cursor_left_128location		0x10
#define shift_cursor_right_128location		0x14
#define shift_display_left_40location		0x18
#define shift_display_right_40location		0x1C

/******** fuction_set ***********/
#define Eight_Bit	0x38
#define Four_Bit	0x28

/****** display_cursor *******/
#define Disblay_Off_Cursor_Off	0x08
#define Disblay_Off_Cursor_On	0x0A
#define Disblay_On_Cursor_Off	0x0C
#define Disblay_On_Cursor_On	0x0E
#define Disblay_On_Cursor_blink	0x0F

/****** entry_set_mode *******/
#define Entry_Mode_increase_AC_no_shift		0x06
#define Entry_Mode_decrease_AC_no_shift		0x04
#define Entry_Mode_shift_display_left		0x07
#define Entry_Mode_shift_display_right		0x05


/********************************* driver_LCD **************************************/

/********* initialization_lcd ********/
void LCD_vinit()
{
	_delay_ms(100);
	/******* 8-bit mode ********/
	#if defined Eight_Bit_Mode
	DIO_vset_port_direction(portname_dataline , 0xff  );
	DIO_vset_pin_direction(portname_control   , EN , 1);
	DIO_vset_pin_direction(portname_control   , RW , 1);
	DIO_vset_pin_direction(portname_control   , RS , 1);
	// enable write on lcd
	DIO_vwrite_pin_value(portname_control , RW , 0);
	// command instructions
	LCD_vsend_cmd(Eight_Bit);//8bit-mode
	_delay_ms(10);
	LCD_vsend_cmd(Disblay_On_Cursor_Off);//appear cursor and display
	_delay_ms(10);
	LCD_vsend_cmd(Clear_Screen);//clear lcd
	_delay_ms(10);
	LCD_vsend_cmd(Entry_Mode_increase_AC_no_shift);//increase cursor step
	_delay_ms(10);
	
	/******* 4-bit mode ********/
	#elif defined Four_Bit_Mode
	DIO_vset_pin_direction(portname_dataline , pin_nibble   , 1);
	DIO_vset_pin_direction(portname_dataline , pin_nibble+1 , 1);
	DIO_vset_pin_direction(portname_dataline , pin_nibble+2 , 1);
	DIO_vset_pin_direction(portname_dataline , pin_nibble+2 , 1);
	DIO_vset_pin_direction(portname_control   , EN , 1);
	DIO_vset_pin_direction(portname_control   , RW , 1);
	DIO_vset_pin_direction(portname_control   , RS , 1);
	// enable write on lcd
	DIO_vwrite_pin_value(portname_control , RW , 0);
	// command instructions
	LCD_vsend_cmd(Return_Home); //return home
	_delay_ms(10);
	LCD_vsend_cmd(Four_Bit);//4bit-mode
	_delay_ms(10);
	LCD_vsend_cmd(Disblay_On_Cursor_Off);//appear cursor and display
	_delay_ms(10);
	LCD_vsend_cmd(Clear_Screen);//clear lcd
	_delay_ms(10);
	LCD_vsend_cmd(Entry_Mode_increase_AC_no_shift);//increase cursor step
	_delay_ms(10);
	#endif
	
}
/********* pulse_enable_lcd ********/
static void Enable_bit (void)
{
	DIO_vwrite_pin_value(portname_control , EN , 1);
	_delay_ms(2);
	DIO_vwrite_pin_value(portname_control , EN , 0);
	_delay_ms(2);
}

/********* send_char_lcd ********/
void LCD_vsend_char(char char_send)
{
	/******* 8-bit mode ********/
	#if defined Eight_Bit_Mode
	DIO_vwrite_port_value(portname_dataline , char_send);
	DIO_vwrite_pin_value(portname_control , RS , 1);
	Enable_bit();
	
	/******* 4-bit mode ********/
	#elif defined Four_Bit_Mode
	//send MSB
	DIO_vhigh_nibble_write(portname_dataline , char_send >> 4);
	DIO_vwrite_pin_value(portname_control , RS , 1);
	Enable_bit();
	//send LSB
	DIO_vhigh_nibble_write(portname_dataline , char_send);
	DIO_vwrite_pin_value(portname_control , RS , 1);
	Enable_bit();
	#endif
	_delay_ms(10);
}

/************** busy_flag ******************/
unsigned char LCD_u8read_busy_flag(void)
{
	DIO_vwrite_pin_value(portname_control , RW , 1);
	DIO_vwrite_pin_value(portname_control , RS , 0);
	while(BIT_IS_SET(portname_dataline , 7));
	DIO_vwrite_pin_value(portname_control , RW , 0);
}

/********* send_command_lcd ********/
void LCD_vsend_cmd(char cmd_send)
{
	/******* 8-bit mode ********/
	#if defined Eight_Bit_Mode
	DIO_vwrite_port_value(portname_dataline , cmd_send);
	DIO_vwrite_pin_value(portname_control , RS , 0);
	Enable_bit();
	
	/******* 4-bit mode ********/
	#elif defined Four_Bit_Mode
	//send MSB
	DIO_vhigh_nibble_write(portname_dataline , cmd_send >> 4);
	DIO_vwrite_pin_value(portname_control , RS , 0);
	Enable_bit();
	//send LSB
	DIO_vhigh_nibble_write(portname_dataline , cmd_send);
	DIO_vwrite_pin_value(portname_control , RS , 0);
	Enable_bit();
	#endif
	LCD_u8read_busy_flag();
	//_delay_ms(10);
}


/********* send_string_lcd ********/
void LCD_vsend_string(char *ptr)
{
	while(*ptr != 0)
	{
		LCD_vsend_char(*ptr);
		ptr++;
	}
	_delay_ms(10);
}

/*********** clear_lcd **********/
void LCD_vClearScreen(void)
{
	LCD_vsend_cmd(Clear_Screen);
	_delay_ms(10);
}


/********* move_cursor_lcd ********/
void LCD_vmove_cursor (char row , char column)
{
	char cmd;
	if (row>2 || row<1  ||  column>16 || column<1)
	{
		cmd = 0x80;
	} 
	else if(row == 1)
	{
		cmd = (0x80 + column -1);
	}
	else if (row == 2)
	{
		cmd = (0xC0 + column -1);
	}
	LCD_vsend_cmd(cmd);
	_delay_ms(10);
}


/************** end driver ****************/