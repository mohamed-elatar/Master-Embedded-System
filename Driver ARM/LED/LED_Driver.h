/************************************************
 * @file           : LED_Driver.h				*
 * @author         : mohamed elatar             *
 * @Data           : November 8, 2023			*
 ************************************************/


#ifndef LED_Driver_H_
#define LED_Driver_H_


//-----------------------------
//Includes
//-----------------------------
#include "STM32_F103C6_GPIO_Driver.h"


/*
 * ===============================================
 * 			APIs Supported by "MCAL GPIO DRIVER"
 * ===============================================
 */

void HAL_LED_Init_Pin (GPIO_TypeDef *GPIOx , uint8_t Pin_Number);
void HAL_LED_Init_Port (GPIO_TypeDef *GPIOx , uint8_t Pins_Select);

void HAL_LED_Turn_On_Pin (GPIO_TypeDef *GPIOx , uint8_t Pin_Number);
void HAL_LED_Turn_On_Port (GPIO_TypeDef *GPIOx , uint8_t Pins_Select);

void HAL_LED_Turn_Off_Pin (GPIO_TypeDef *GPIOx , uint8_t Pin_Number);
void HAL_LED_Turn_Off_Port (GPIO_TypeDef *GPIOx , uint8_t Pins_Select);

void HAL_LED_Toggle_Pin (GPIO_TypeDef *GPIOx , uint8_t Pin_Number);
void HAL_LED_Toggle_Port (GPIO_TypeDef *GPIOx , uint8_t Pins_Select);

uint8_t HAL_LED_Read_Status_Pin(GPIO_TypeDef *GPIOx , uint8_t Pin_Number);
uint8_t HAL_LED_Read_Status_Port(GPIO_TypeDef *GPIOx , uint8_t Pins_Select);

#endif /* LED_Driver_H_ */
