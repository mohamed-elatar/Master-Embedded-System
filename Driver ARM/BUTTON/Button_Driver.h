/************************************************
 * @file           : Button_Driver.h			*
 * @author         : mohamed elatar             *
 * @Data           : November 8, 2023			*
 ************************************************/


#ifndef Button_Driver_H_
#define Button_Driver_H_


//-----------------------------
//Includes
//-----------------------------
#include "STM32_F103C6_GPIO_Driver.h"
#include "STM32_F103C6_EXTI_Driver.h"

/*
 * ===============================================
 * 			APIs Supported by "MCAL GPIO DRIVER"
 * ===============================================
 */

void HAL_BUTTON_Init_Pin (GPIO_TypeDef *GPIOx , uint8_t Pin_Number , uint8_t Pin_Mode);
void HAL_BUTTON_Init_Port (GPIO_TypeDef *GPIOx , uint8_t Pins_Select , uint8_t Pins_Mode);

void HAL_BUTTON_Init_EXTI_Pin (EXTI_GPIO_Mapping_t * Mapping , uint8_t select_trigger , uint8_t Enable_Or_Disable , void (*PF)() );

uint8_t HAL_BUTTON_Read_Status_Pin(GPIO_TypeDef *GPIOx , uint8_t Pin_Number);
uint8_t HAL_BUTTON_Read_Status_Port(GPIO_TypeDef *GPIOx , uint8_t Pins_Select);


#endif /* Button_Driver_H_ */
