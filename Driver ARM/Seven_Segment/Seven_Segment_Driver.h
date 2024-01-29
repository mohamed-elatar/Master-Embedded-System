/***********************************************
 * @file           : Seven_Segment_Driver.h 	*
 * @author         : mohamed elatar             *
 * @Data           : November 5, 2023			*
 ************************************************/

#ifndef Seven_Segment_Driver_H_
#define Seven_Segment_Driver_H_

//-----------------------------
//Includes
//-----------------------------
#include "STM32_F103C6_GPIO_Driver.h"

//-----------------------------
//Macros Configuration References
//-----------------------------
#define Pins_Select_7Segment 		GPIO_PORT_HIGH
#define Pins_Select_7Segment_BCD 	GPIO_PORT_LOW_NIBBLE_LOW
#define Port_7Segment 				GPIOA

//#define Common_Cathod
#define Common_Anode



/*
 * ===============================================
 * 			APIs Supported by "MCAL GPIO DRIVER"
 * ===============================================
 */
void HAL_SevenSegment_Init ();
void HAL_SevenSegment_Write_ENG (uint8_t Number);
void HAL_SevenSegment_Write_ARB (uint8_t Number);

void HAL_SevenSegment_BCD_Init ();
void HAL_SevenSegment_BCD_Write (uint8_t value);

#endif /* Seven_Segment_Driver_H_ */
