/***********************************************
 * @file           : LCD_Driver.h				*
 * @author         : mohamed elatar             *
 * @Data           : November 2, 2023			*
 ************************************************/

#ifndef LCD_Driver_H_
#define LCD_Driver_H_

//-----------------------------
//Includes
//-----------------------------
#include "STM32_F103C6_GPIO_Driver.h"

//-----------------------------
//Macros Configuration References
//-----------------------------

//#define F_CPU 1000000UL

#define PortName_Dataline					GPIOA
#define PortName_Control					GPIOB

//#define LCD_2X16
#define LCD_4X16

#define Eight_Bit_Mode
//#define Four_Bit_Mode


#define EN									GPIO_PIN_0
#define RW									GPIO_PIN_1
#define RS									GPIO_PIN_10


//---------------------------
// Commands
//---------------------------
#define Clear_Screen						0x01
#define Return_Home							0x02

/********* display_and_cursor *********/
#define shift_cursor_left_128location		0x10
#define shift_cursor_right_128location		0x14
#define shift_display_left_40location		0x18
#define shift_display_right_40location		0x1C

/******** fuction_set ***********/
#define Eight_Bit							0x38
#define Four_Bit							0x28

/****** display_cursor *******/
#define Disblay_Off_Cursor_Off				0x08
#define Disblay_Off_Cursor_On				0x0A
#define Disblay_On_Cursor_Off				0x0C
#define Disblay_On_Cursor_On				0x0E
#define Disblay_On_Cursor_blink				0x0F

/****** entry_set_mode *******/
#define Entry_Mode_increase_AC_no_shift		0x06
#define Entry_Mode_decrease_AC_no_shift		0x04
#define Entry_Mode_shift_display_left		0x07
#define Entry_Mode_shift_display_right		0x05

/*
 * ===============================================
 * 			APIs Supported by "MCAL GPIO DRIVER"
 * ===============================================
 */

void HAL_LCD_Init();

void HAL_LCD_Send_Char(uint8_t Character);
void HAL_LCD_Send_Cmd(uint8_t Command);

void HAL_LCD_Send_String(uint8_t *ptr);
void HAL_LCD_Send_Number (sint32_t num);
void HAL_LCD_Send_Real_Number (float32_t num);

void HAL_LCD_ClearScreen();
void HAL_LCD_Move_Cursor (uint8_t row , uint8_t column);

void HAL_Enable_bit ();
void LCD_u8read_busy_flag();

#endif /* LCD_Driver_H_ */
