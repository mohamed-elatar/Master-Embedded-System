/*
 * safe_password.c
 *
 * Created: 5/7/2023 10:03:07 PM
 *  Author: mohamed_elatar
 */ 

#define F_CPU 8000000UL
#include <util/delay.h>
#include "led.h"
#include "lcd.h"
#include "Keybad.h"
#include "driver EEPROM.h"

#define EEPROM_START_addrss		0x60
#define EEPROM_First_Addrss		0x61
#define EEPROM_Secand_Addrss	0x62
#define EEPROM_Thired_Addrss	0x63
#define EEPROM_Four_Addrss		0x64
#define MAX_TRIES 3

int main(void)
{
	uint8_t val = NOT_PRESSED;
	uint8_t i , flag=0;
	uint8_t arr[4] = {NOT_PRESSED , NOT_PRESSED , NOT_PRESSED ,NOT_PRESSED};
	uint8_t tries = MAX_TRIES;

	LCD_vinit();
	Keybad_vinit();
	LED_vinit_pin('a',0);//open
	LED_vinit_pin('a',1);//close
    LCD_vsend_string("    Welcome   ");
    _delay_ms(1000);
    LCD_vClearScreen();
	
    // At First check if set password or has default pass
	if (EEPROM_u8read(EEPROM_START_addrss) == NOT_PRESSED)//0xff default unprogramming EEPROM
	{
		LCD_vsend_string("Set Pass:");
		for (i=0 ; i<4 ; i++)
		{
			do
			{
				val = Keybad_u8read();
				
			} while (val == NOT_PRESSED);
			//LCD_vsend_char(val);
			LCD_vmove_cursor(1,10+i);
			LCD_vsend_char('*');
			EEPROM_vwrite(EEPROM_First_Addrss+i , val);
			//delay_ms(500);
		}
        _delay_ms(500);
		EEPROM_vwrite(EEPROM_START_addrss , 0x00);//programming
        LCD_vClearScreen();
        LCD_vsend_string("Now Set New Pass");
        _delay_ms(1000);
        
	}
	

    // enter the password ( operations check )
	while (!flag)
	{
		//arr[0] = arr[1] = arr[2] = arr[3] = NOT_PRESSED;
		LCD_vClearScreen();
		_delay_ms(1000);
		LCD_vsend_string("Check Pass:");
		for (i=0 ; i<4 ; i++)
		{
			do 
			{
				arr[i] = Keybad_u8read();
			} while (arr[i] == NOT_PRESSED);
			//LCD_vsend_char(arr[i]);
			LCD_vmove_cursor(1,12+i);
			LCD_vsend_char('*');
			//_delay_ms(100);
		}
        _delay_ms(500);

        // check entered password with correct password stored in EEPROM Address 
        // enter correct password
		if (EEPROM_u8read(EEPROM_First_Addrss)  == arr[0] && EEPROM_u8read(EEPROM_Secand_Addrss) == arr[1] 
			&& EEPROM_u8read(EEPROM_Thired_Addrss) == arr[2] && EEPROM_u8read(EEPROM_Four_Addrss) == arr[3])
		{
			_delay_ms(1000);
			LCD_vClearScreen();
			_delay_ms(1000);
			LCD_vsend_string("True Pass");
			_delay_ms(1000);
			LCD_vmove_cursor(2,1);
			LCD_vsend_string("Open Safe");
			_delay_ms(1000);
			LED_vturn_on_pin('a',0);
			flag =1; // exit from while loop
		} 
        // enter fault password
		else
		{
			--tries;
			if (tries > 0)
			{
				LCD_vClearScreen();
				_delay_ms(1000);
				LCD_vsend_string("Wrong Pass");
				LCD_vmove_cursor(2,1);
				LCD_vsend_string("Try Again");
				_delay_ms(1000);
				LCD_vClearScreen();
				LCD_vsend_string("Have Tries: ");
				LCD_vsend_char(tries + 48);
				_delay_ms(1000);
			} 
			else
			{
				_delay_ms(1000);
				LCD_vClearScreen();
				_delay_ms(1000);
				LCD_vsend_string("End Tries");
				_delay_ms(1000);
				LCD_vmove_cursor(2,1);
				LCD_vsend_string("Close Safe");
				_delay_ms(1000);
				LED_vturn_on_pin('a',1);
				flag =1; // exit from while loop
			}
		}
	}
}