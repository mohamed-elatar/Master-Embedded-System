/***********************************************
 * @file           : Seven_Segment_Driver.c 	*
 * @author         : mohamed elatar             *
 * @Data           : November 5, 2023			*
 ************************************************/

//-----------------------------
//Includes
//-----------------------------
#include "Seven_Segment_Driver.h"

/*=========================================================================================================
 * @Fn			: HAL_SevenSegment_Init
 * @brief		: to initialize Specific Pins in Port as output pins need 7 pins
 * @param [in]	: none
 * @retval		: none
 *=========================================================================================================*/
void HAL_SevenSegment_Init ()
{
	// output pins
	GPIO_Port_Configure_t PortConfig;
	PortConfig.GPIO_Mode = GPIO_MODE_OUTPUT_PUSH_PULL;
	PortConfig.GPIO_Output_Speed = GPIO_Speed_10;
	MCAL_GPIO_Port_Init(Port_7Segment, &PortConfig, Pins_Select_7Segment);

	// return default configuration
	GPIO_Pin_Configure_t PinConfig;
	PinConfig.GPIO_Mode = GPIO_MODE_INPUT_FLOATING;
	if( Pins_Select_7Segment == GPIO_PORT_LOW) PinConfig.GPIO_Pin_Number = GPIO_PIN_7;
	else PinConfig.GPIO_Pin_Number = GPIO_PIN_15;
	MCAL_GPIO_Pin_Init(Port_7Segment, &PinConfig);

}

/*=========================================================================================================
 * @Fn			: HAL_SevenSegment_Write_ENG
 * @brief		: to write on segment
 * @param [in]	: the write number
 * @retval		: none
 *=========================================================================================================*/
void HAL_SevenSegment_Write_ENG (uint8_t Number)
{
	#if defined Common_Cathod
	uint8_t arr[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x47,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
	MCAL_GPIO_Write_Port(Port_7Segment , arr[Number] , Pins_Select_7Segment);
	
	#elif defined Common_Anode
	uint8_t arr[]={~0x3f,~0x06,~0x5b,~0x4f,~0x66,~0x6d,~0x7d,~0x47,~0x7f,~0x6f,~0x77,~0x7c,~0x39,~0x5e,~0x79,~0x71};
	MCAL_GPIO_Write_Port(Port_7Segment , arr[Number] , Pins_Select_7Segment);
	
	#endif
}

/*=========================================================================================================
 * @Fn			: HAL_SevenSegment_Write_ARB
 * @brief		: to write on segment
 * @param [in]	: the write number
 * @retval		: none
 *=========================================================================================================*/
void HAL_SevenSegment_Write_ARB (uint8_t Number)
{
	#if defined Common_Cathod
	uint8_t arr[]={0x40,0x06,0x31,0x72,0x79,0x3f,0x07,0x3e,0x37,0x67};
	MCAL_GPIO_Write_Port(Port_7Segment , arr[Number] , Pins_Select_7Segment);
	
	#elif defined Common_Anode
	uint8_t arr[]={0x40,0x06,0x31,0x72,0x79,0x3f,0x07,0x3e,0x37,0x67};
	MCAL_GPIO_Write_Port(Port_7Segment , ~arr[Number] , Pins_Select_7Segment);
	#endif
}

/*=========================================================================================================
 * @Fn			: HAL_SevenSegmHAL_SevenSegment_BCD_Initent_Init
 * @brief		: to initialize Specific Pins in Port as output pins need 4 pins only
 * @param [in]	: none
 * @retval		: none
 * @Note		: BCD -> binary to decimal converter
 *=========================================================================================================*/
void HAL_SevenSegment_BCD_Init ()
{
	GPIO_Port_Configure_t PortConfig;
	PortConfig.GPIO_Mode = GPIO_MODE_OUTPUT_PUSH_PULL;
	PortConfig.GPIO_Output_Speed = GPIO_Speed_10;
	MCAL_GPIO_Port_Init(Port_7Segment , &PortConfig , Pins_Select_7Segment_BCD);
}

/*=========================================================================================================
 * @Fn			: HAL_SevenSegment_BCD_Write
 * @brief		: to write on BCD
 * @param [in]	: the write number
 * @retval		: none
 *=========================================================================================================*/
void HAL_SevenSegment_BCD_Write (uint8_t value)
{
	MCAL_GPIO_Write_Port(Port_7Segment , value , Pins_Select_7Segment_BCD);
}