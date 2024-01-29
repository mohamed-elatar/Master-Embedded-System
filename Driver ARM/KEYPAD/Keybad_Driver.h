/***********************************************
 * @file           : Keybad_Driver.h		 	*
 * @author         : mohamed elatar             *
 * @Data           : November 5, 2023			*
 ************************************************/


#ifndef Keybad_Driver_H_
#define Keybad_Driver_H_

//-----------------------------
//Includes
//-----------------------------
#include "STM32_F103C6_GPIO_Driver.h"

//-----------------------------
//Macros Configuration References
//-----------------------------
#define ROW_PORT 			GPIOA
#define ROW_Nibble 			GPIO_PORT_LOW_NIBBLE_HIGH

#define R1 					GPIO_PIN_4
#define R2 					GPIO_PIN_5
#define R3 					GPIO_PIN_6
#define R4 					GPIO_PIN_7

#define COL_PORT 			GPIOB
#define COL_Nibble 			GPIO_PORT_HIGH_NIBBLE_HIGH

#define C1 					GPIO_PIN_12
#define C2 					GPIO_PIN_13
#define C3 					GPIO_PIN_14
#define C4 					GPIO_PIN_15

#define NOT_PRESSED 		0xFF





/*
 * ===============================================
 * 			APIs Supported by "MCAL GPIO DRIVER"
 * ===============================================
 */

void HAL_Keybad_Init (void);
uint8_t HAL_Keybad_Read(void);

#endif /* Keybad_Driver_H_ */
