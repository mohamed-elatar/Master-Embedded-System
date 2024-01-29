/************************************************
 * @file           : BUTTON_Driver.c			*
 * @author         : mohamed elatar             *
 * @Data           : November 8, 2023			*
 ************************************************/

//-----------------------------
//Includes
//-----------------------------
#include "BUTTON_Driver.h"

/*=========================================================================================================
 * @Fn			: HAL_BUTTON_Init_Pin
 * @brief		: to initialize pin button sw (input pin)
 * @param [in]	: pinnumber [0:15] and mode pin (floating , push pull/down , analog) and pointer to structure
 * @retval		: none
 *=========================================================================================================*/

void HAL_BUTTON_Init_Pin (GPIO_TypeDef *GPIOx , uint8_t Pin_Number , uint8_t Pin_Mode)
{
	GPIO_Pin_Configure_t PinConfig;
	PinConfig.GPIO_Pin_Number = Pin_Number;
	PinConfig.GPIO_Mode = Pin_Mode;
	MCAL_GPIO_Pin_Init(GPIOx, &PinConfig);
}

/*=========================================================================================================
 * @Fn			: HAL_BUTTON_Init_EXTI_Pin
 * @brief		: to initialize Specific EXTI pin (input pin)
 * @param [in]	: Mapping include (EXTI_Input_Line_Number , GPIO_Port , GPIO_Pin , IVT_IRQ_Number) && trigger (raising || failing) && (enable || disable) IQR
 * @param [in]	: trigger (raising || failing) && (enable || disable) IQR
 * @param [in]	: pointer to function EXTI in application layer
 * @retval		: none
 *=========================================================================================================*/

void HAL_BUTTON_Init_EXTI_Pin (EXTI_GPIO_Mapping_t * Mapping , uint8_t select_trigger , uint8_t Enable_Or_Disable , void (*PF)() )
{
	EXTI_Pin_Configure_t pin;
	pin.EXTI_Pin = *Mapping;
	pin.Trigger_Case = select_trigger;
	pin.IRQ_EN = Enable_Or_Disable;
	pin.PF_IRQ_CallBack = PF;

	MCAL_EXTI_GPIO_Init(&pin);
}


/*=========================================================================================================
 * @Fn			: HAL_BUTTON_Init_Port
 * @brief		: to initialize pins button sw (input pins)
 * @param [in]	: pins_port and mode pin (floating , push pull/down , analog) and pointer to structure
 * @retval		: none
 *=========================================================================================================*/
void HAL_BUTTON_Init_Port (GPIO_TypeDef *GPIOx , uint8_t Pins_Select , uint8_t Pins_Mode)
{
	GPIO_Port_Configure_t PortConfig;
	PortConfig.GPIO_Mode = Pins_Mode;
	MCAL_GPIO_Port_Init(GPIOx, &PortConfig , Pins_Select);
}


/*=========================================================================================================
 * @Fn			: HAL_BUTTON_Read_Status_Pin
 * @brief		: read status sw (ON / OFF)
 * @param [in]	: pinnumber [0:15] and pointer to structure
 * @retval		: ON / OFF
 *=========================================================================================================*/
uint8_t HAL_BUTTON_Read_Status_Pin(GPIO_TypeDef *GPIOx , uint8_t Pin_Number)
{
	return MCAL_GPIO_Read_Pin(GPIOx, Pin_Number);
}

/*=========================================================================================================
 * @Fn			: HAL_BUTTON_Read_Status_Port
 * @brief		: read status sw (ON / OFF)
 * @param [in]	: pins_port and pointer to structure
 * @retval		: ON / OFF
 *=========================================================================================================*/
uint8_t HAL_BUTTON_Read_Status_Port(GPIO_TypeDef *GPIOx , uint8_t Pins_Select)
{
	return MCAL_GPIO_Read_Port(GPIOx, Pins_Select);
}
