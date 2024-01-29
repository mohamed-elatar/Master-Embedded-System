/************************************************
 * @file           : LED_Driver.c				*
 * @author         : mohamed elatar             *
 * @Data           : November 8, 2023			*
 ************************************************/

//-----------------------------
//Includes
//-----------------------------
#include "LED_Driver.h"

/*=========================================================================================================
 * @Fn			: HAL_LED_Init_Pin
 * @brief		: to initialize pin led (output pin)
 * @param [in]	: pinnumber [0:15] and pointer to structure
 * @retval		: none
 *=========================================================================================================*/
void HAL_LED_Init_Pin (GPIO_TypeDef *GPIOx , uint8_t Pin_Number)
{
	GPIO_Pin_Configure_t PinConfig;
	PinConfig.GPIO_Pin_Number = Pin_Number;
	PinConfig.GPIO_Mode = GPIO_MODE_OUTPUT_PUSH_PULL;
	PinConfig.GPIO_Output_Speed = GPIO_Speed_10;
	MCAL_GPIO_Pin_Init(GPIOx, &PinConfig);
}


/*=========================================================================================================
 * @Fn			: HAL_LED_Init_Port
 * @brief		: to initialize pins led (output pins)
 * @param [in]	: pins_port and pointer to structure
 * @retval		: none
 *=========================================================================================================*/
void HAL_LED_Init_Port (GPIO_TypeDef *GPIOx , uint8_t Pins_Select)
{
	GPIO_Port_Configure_t PortConfig;
	PortConfig.GPIO_Mode = GPIO_MODE_OUTPUT_PUSH_PULL;
	PortConfig.GPIO_Output_Speed = GPIO_Speed_10;
	MCAL_GPIO_Port_Init(GPIOx, &PortConfig , Pins_Select);
}


/*=========================================================================================================
 * @Fn			: HAL_LED_Turn_On_Pin
 * @brief		: make led turn on
 * @param [in]	: pinnumber [0:15] and pointer to structure
 * @retval		: none
 *=========================================================================================================*/
void HAL_LED_Turn_On_Pin (GPIO_TypeDef *GPIOx , uint8_t Pin_Number)
{
	MCAL_GPIO_Write_Pin(GPIOx, Pin_Number , LOGIC_HIGH);
}

/*=========================================================================================================
 * @Fn			: HAL_LED_Turn_On_Port
 * @brief		: make led port turn on
 * @param [in]	: pins_port and pointer to structure
 * @retval		: none
 *=========================================================================================================*/
void HAL_LED_Turn_On_Port (GPIO_TypeDef *GPIOx , uint8_t Pins_Select)
{
	switch (Pins_Select)
	{
	case GPIO_PORT_LOW:
		MCAL_GPIO_Write_Port(GPIOx, 0XFF , Pins_Select);
		break;

	case GPIO_PORT_HIGH:
		MCAL_GPIO_Write_Port(GPIOx, 0XFF , Pins_Select);
		break;

	case GPIO_PORT_LOW_NIBBLE_LOW:
		MCAL_GPIO_Write_Port(GPIOx, 0XF , Pins_Select);
		break;

	case GPIO_PORT_LOW_NIBBLE_HIGH:
		MCAL_GPIO_Write_Port(GPIOx, 0XF , Pins_Select);
		break;

	case GPIO_PORT_HIGH_NIBBLE_LOW:
		MCAL_GPIO_Write_Port(GPIOx, 0XF , Pins_Select);
		break;

	case GPIO_PORT_HIGH_NIBBLE_HIGH:
		MCAL_GPIO_Write_Port(GPIOx, 0XF , Pins_Select);
		break;
	case GPIO_ALL_PORT:
		MCAL_GPIO_Write_Port(GPIOx, 0XFFFF , Pins_Select);
		break;
	}
}


/*=========================================================================================================
 * @Fn			: HAL_LED_Turn_Off_Pin
 * @brief		: make led turn off
 * @param [in]	: pinnumber [0:15] and pointer to structure
 * @retval		: none
 *=========================================================================================================*/
void HAL_LED_Turn_Off_Pin (GPIO_TypeDef *GPIOx , uint8_t Pin_Number)
{
	MCAL_GPIO_Write_Pin(GPIOx, Pin_Number , LOGIC_LOW);
}

/*=========================================================================================================
 * @Fn			: HAL_LED_Turn_Off_Port
 * @brief		: make led port turn off
 * @param [in]	: pins_port and pointer to structure
 * @retval		: none
 *=========================================================================================================*/
void HAL_LED_Turn_Off_Port (GPIO_TypeDef *GPIOx , uint8_t Pins_Select)
{
	MCAL_GPIO_Write_Port(GPIOx , LOGIC_LOW , Pins_Select);
}


/*=========================================================================================================
 * @Fn			: HAL_LED_Toggle_Pin
 * @brief		: make led toggle
 * @param [in]	: pinnumber [0:15] and pointer to structure
 * @retval		: none
 *=========================================================================================================*/
void HAL_LED_Toggle_Pin (GPIO_TypeDef *GPIOx , uint8_t Pin_Number)
{
	MCAL_GPIO_Toggle_Pin(GPIOx , Pin_Number);
}


/*=========================================================================================================
 * @Fn			: HAL_LED_Toggle_Port
 * @brief		: make led port toggle
 * @param [in]	: pins_port and pointer to structure
 * @retval		: none
 *=========================================================================================================*/
void HAL_LED_Toggle_Port (GPIO_TypeDef *GPIOx , uint8_t Pins_Select)
{
	MCAL_GPIO_Toggle_Port(GPIOx, Pins_Select);
}

/*=========================================================================================================
 * @Fn			: HAL_LED_Read_Status_Pin
 * @brief		: read status pin (ON / OFF)
 * @param [in]	: pinnumber [0:15] and pointer to structure
 * @retval		: ON / OFF
 *=========================================================================================================*/
uint8_t HAL_LED_Read_Status_Pin(GPIO_TypeDef *GPIOx , uint8_t Pin_Number)
{
	return MCAL_GPIO_Read_Pin(GPIOx, Pin_Number);
}

/*=========================================================================================================
 * @Fn			: HAL_LED_Read_Status_Port
 * @brief		: read status pin (ON / OFF)
 * @param [in]	: pins_port and pointer to structure
 * @retval		: ON / OFF
 *=========================================================================================================*/
uint8_t HAL_LED_Read_Status_Port(GPIO_TypeDef *GPIOx , uint8_t Pins_Select)
{
	return MCAL_GPIO_Read_Port(GPIOx, Pins_Select);
}
