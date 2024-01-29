/***********************************************
 * @file           : STM32_F103C6_GPIO_Driver.h *
 * @author         : mohamed elatar             *
 * @Data           : October 30, 2023			*
 ************************************************/


#ifndef INCLUDE_STM32_F103C6_GPIO_DRIVER_H_
#define INCLUDE_STM32_F103C6_GPIO_DRIVER_H_

//-----------------------------
//Includes
//-----------------------------
#include "STM32_F103X6.h"

//-----------------------------
//Macros Configuration References
//-----------------------------
enum
{
	/* GPIO PIN STATUS DEF */
	GPIO_PIN_RESET,
	GPIO_PIN_SET,

	/* GPIO PORT STATUS DEF */
	GPIO_ALL_PORT,  //pin [0:15]
	GPIO_PORT_LOW,  //PIN [0:7]
	GPIO_PORT_HIGH, //PIN [8:15]

	GPIO_PORT_LOW_NIBBLE_LOW, // pin [0:3]
	GPIO_PORT_LOW_NIBBLE_HIGH, // pin [4:7]
	GPIO_PORT_HIGH_NIBBLE_LOW, // pin [8:11]
	GPIO_PORT_HIGH_NIBBLE_HIGH, // pin [12:15]

	/* GPIO PIN LOCK DEF */
	GPIO_PIN_LOCKED,
	GPIO_PIN_ERROR
};

/* Logic */
#define LOGIC_HIGH	1
#define LOGIC_LOW	0

//-----------------------------
//User type definitions (structures)
//-----------------------------

typedef struct
{
	uint16_t GPIO_Pin_Number; 	//Specifies the GPIO Pins to be configured
	// Explain in @ref GPIO_PINS_Numbers

	uint8_t GPIO_Mode; 			//Specifies the GPIO Pins to be configured
	// Explain in @ref GPIO_PINS_Mode

	uint8_t GPIO_Output_Speed; 	//Specifies the GPIO Pins to be configured
	// Explain in @ref GPIO_PINS_Speed
}GPIO_Pin_Configure_t;


typedef struct
{
	uint8_t GPIO_Mode; 			//Specifies the GPIO Pins to be configured
	// Explain in @ref GPIO_PINS_Mode

	uint8_t GPIO_Output_Speed; 	//Specifies the GPIO Pins to be configured
	// Explain in @ref GPIO_PINS_Speed
}GPIO_Port_Configure_t;



/*@ref GPIO_PINS_Numbers*/
#define GPIO_PIN_0 					((uint16_t)0x0000)  /* Pin 0 selected  */
#define GPIO_PIN_1 					((uint16_t)0x0001)  /* Pin 1 selected  */
#define GPIO_PIN_2 					((uint16_t)0x0002)  /* Pin 2 selected  */
#define GPIO_PIN_3 					((uint16_t)0x0003)  /* Pin 3 selected  */
#define GPIO_PIN_4 					((uint16_t)0x0004)  /* Pin 4 selected  */
#define GPIO_PIN_5 					((uint16_t)0x0005)  /* Pin 5 selected  */
#define GPIO_PIN_6 					((uint16_t)0x0006)  /* Pin 6 selected  */
#define GPIO_PIN_7 					((uint16_t)0x0007)  /* Pin 7 selected  */
#define GPIO_PIN_8 					((uint16_t)0x0008)  /* Pin 8 selected  */
#define GPIO_PIN_9 					((uint16_t)0x0009)  /* Pin 9 selected  */
#define GPIO_PIN_10					((uint16_t)0x000A)  /* Pin 10 selected */
#define GPIO_PIN_11					((uint16_t)0x000B)  /* Pin 11 selected */
#define GPIO_PIN_12					((uint16_t)0x000C)  /* Pin 12 selected */
#define GPIO_PIN_13					((uint16_t)0x000D)  /* Pin 13 selected */
#define GPIO_PIN_14					((uint16_t)0x000E)  /* Pin 14 selected */
#define GPIO_PIN_15					((uint16_t)0x000F)  /* Pin 15 selected */

#define GPIO_SHIFT_PIN_0			((uint16_t)0x0001)  /* Pin 0 selected    (1<<0)*/
#define GPIO_SHIFT_PIN_1  			((uint16_t)0x0002)  /* Pin 1 selected    (1<<1)*/
#define GPIO_SHIFT_PIN_2  			((uint16_t)0x0004)  /* Pin 2 selected    (1<<2)*/
#define GPIO_SHIFT_PIN_3  			((uint16_t)0x0008)  /* Pin 3 selected    (1<<3)*/
#define GPIO_SHIFT_PIN_4  			((uint16_t)0x0010)  /* Pin 4 selected    (1<<4)*/
#define GPIO_SHIFT_PIN_5  			((uint16_t)0x0020)  /* Pin 5 selected    (1<<5)*/
#define GPIO_SHIFT_PIN_6  			((uint16_t)0x0040)  /* Pin 6 selected    (1<<6)*/
#define GPIO_SHIFT_PIN_7  			((uint16_t)0x0080)  /* Pin 7 selected    (1<<7)*/
#define GPIO_SHIFT_PIN_8  			((uint16_t)0x0100)  /* Pin 8 selected    (1<<8)*/
#define GPIO_SHIFT_PIN_9  			((uint16_t)0x0200)  /* Pin 9 selected    (1<<9)*/
#define GPIO_SHIFT_PIN_10 			((uint16_t)0x0400)  /* Pin 10 selected   (1<<A)*/
#define GPIO_SHIFT_PIN_11 			((uint16_t)0x0800)  /* Pin 11 selected   (1<<B)*/
#define GPIO_SHIFT_PIN_12 			((uint16_t)0x1000)  /* Pin 12 selected   (1<<C)*/
#define GPIO_SHIFT_PIN_13 			((uint16_t)0x2000)  /* Pin 13 selected   (1<<D)*/
#define GPIO_SHIFT_PIN_14 			((uint16_t)0x4000)  /* Pin 14 selected   (1<<E)*/
#define GPIO_SHIFT_PIN_15 			((uint16_t)0x8000)  /* Pin 15 selected   (1<<F)*/
#define GPIO_SET_ALL_PINS	 		((uint16_t)0xFFFF)  /* Set 15 Pins*/
#define GPIO_CLR_ALL_PINS	 		((uint16_t)0x0000)  /* Set 15 Pins*/


/*@ref GPIO_PINS_Mode*/

// In input mode (MODE[1:0]=00) :
//00: Analog mode
//01: Floating input (reset state)
//10: Input with pull-up / pull-down
//11: Reserved

// In output mode (MODE[1:0] > 00) :
//00: General purpose output push-pull
//01: General purpose output Open-drain
//10: Alternate function output Push-pull
//11: Alternate function output Open-drain

#define GPIO_MODE_INPUT_ANALOG			0x00000000u  // Analog mode
#define GPIO_MODE_AF_INPUT				0x00000000u  // note this mode not exist
#define GPIO_MODE_INPUT_FLOATING		0x00000001u  // Floating input (reset state)
#define GPIO_MODE_INPUT_PULL_UP      	0x00000002u  // Input with pull-up
#define GPIO_MODE_INPUT_PULL_DOWN		0x00000003u  // Input with pull-down
#define GPIO_MODE_OUTPUT_PUSH_PULL		0x00000004u  // General purpose output push-pull
#define GPIO_MODE_OUTPUT_OPEN_DRAIN		0x00000005u  // General purpose output Open-drain
#define GPIO_MODE_AF_PUSH_PULL			0x00000006u  // Alternate function output Push-pull
#define GPIO_MODE_AF_OPEN_DRAIN			0x00000007u  // Alternate function output Open-drain


/*@ref GPIO_PINS_Speed*/
//01: Output mode, max speed 10 MHz.
//10: Output mode, max speed 2 MHz.
//11: Output mode, max speed 50 MHz

#define GPIO_Speed_10 					0x00000001u    // Output mode with maximum speed of 10 MHz
#define GPIO_Speed_2					0x00000002u	   // Output mode with maximum speed of 2 MHz
#define GPIO_Speed_50					0x00000003u    // Output mode with maximum speed of 50 MHz

/*
 * ===============================================
 * 			APIs Supported by "MCAL GPIO DRIVER"
 * ===============================================
 */

void MCAL_GPIO_Pin_Init(GPIO_TypeDef* GPIOx, GPIO_Pin_Configure_t* PinConfig);
void MCAL_GPIO_Port_Init(GPIO_TypeDef* GPIOx, GPIO_Port_Configure_t* PortConfig , uint8_t status);
void MCAL_GPIO_DeInit(GPIO_TypeDef* GPIOx);

uint8_t MCAL_GPIO_Read_Pin(GPIO_TypeDef* GPIOx, uint16_t PinNumber);
uint32_t MCAL_GPIO_Read_Port(GPIO_TypeDef* GPIOx , uint8_t Pins_Select);

void MCAL_GPIO_Write_Pin(GPIO_TypeDef* GPIOx, uint16_t PinNumber, uint8_t value);
void MCAL_GPIO_Write_Port(GPIO_TypeDef* GPIOx, uint32_t value ,uint8_t Pins_Select);

void MCAL_GPIO_Toggle_Pin(GPIO_TypeDef* GPIOx, uint16_t PinNumber);
void MCAL_GPIO_Toggle_Port(GPIO_TypeDef* GPIOx, uint8_t Pins_Select);

uint8_t MCAL_GPIO_Lock_Pin(GPIO_TypeDef* GPIOx, uint16_t PinNumber);

uint8_t Get_Position (uint16_t Pin_Number);

#endif /* INCLUDE_STM32_F103C6_GPIO_DRIVER_H_ */
