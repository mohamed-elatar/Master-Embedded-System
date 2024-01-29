/***********************************************
 * @file           : STM32_F103C6_GPIO_Driver.c *
 * @author         : mohamed elatar             *
 * @Data           : October 30, 2023			*
 ************************************************/

//-----------------------------
//Includes
//-----------------------------
#include "STM32_F103C6_GPIO_Driver.h"


/*=========================================================================================================
 * @Fn			: MCAL_GPIO_INIT
 * @brief		: to initialize Specific pin (I/P OR O/P)
 * @param [in]	: Two Pointers to structure
 * @retval		: none
 * Note			: LQFP48 Package has Fully port A,B and Partial C,D
 *=========================================================================================================*/

void MCAL_GPIO_Pin_Init(GPIO_TypeDef* GPIOx, GPIO_Pin_Configure_t* PinConfig)
{
	//Port configuration register low (GPOIx_CRL) configure pins from 0:7
	//Port configuration register high (GPOIx_CRH) configure pins from 8:15

	uint32_t pin_configure = 0;
	volatile uint32_t * configure_register = NULL;
	configure_register = (PinConfig->GPIO_Pin_Number < GPIO_PIN_8) ? &GPIOx->CRL : &GPIOx->CRH ;

	//clear CNFy[1:0] 00 , MODEy[1:0] 00   --> 4BIT
	(*configure_register) &= ~( (0xF)<<Get_Position(PinConfig->GPIO_Pin_Number) );

	//if output mode
	if( (PinConfig->GPIO_Mode == GPIO_MODE_OUTPUT_PUSH_PULL) || (PinConfig->GPIO_Mode == GPIO_MODE_OUTPUT_OPEN_DRAIN) ||
			(PinConfig->GPIO_Mode == GPIO_MODE_AF_PUSH_PULL) || (PinConfig->GPIO_Mode == GPIO_MODE_AF_OPEN_DRAIN)   )
	{
		//set CNFy[1:0] ? , MODEy[1:0] ?   --> 4BIT
		pin_configure = ( ((( (PinConfig->GPIO_Mode) - 4) << 2 ) | (PinConfig->GPIO_Output_Speed)) & 0x0F ); // 0x0F as need only first 4bit 
	}
	// input mode
	else
	{
		if( (PinConfig->GPIO_Mode == GPIO_MODE_INPUT_ANALOG) || (PinConfig->GPIO_Mode == GPIO_MODE_INPUT_FLOATING))
		{
			//set  CNFy[1:0] ? , MODEy[1:0] 00  -> 2BIT
			pin_configure = ( ((PinConfig->GPIO_Mode << 2 ) | (0x0)) & 0x0F );
		}
		else if ( PinConfig->GPIO_Mode == GPIO_MODE_AF_INPUT ) // deal with it as i/p analog
		{
			//set CNFy[1:0] ? , MODEy[1:0] 00   -> 2BIT
			pin_configure = ( ((PinConfig->GPIO_Mode << 2 ) | (0x0)) & 0x0F );
		}
		else
		{
			// pull up
			if( PinConfig->GPIO_Mode == GPIO_MODE_INPUT_PULL_UP )
			{
				// from table 20 : PX-ODR = 1 For Pull Up
				SET_BIT( GPIOx->ODR , PinConfig->GPIO_Pin_Number );
				pin_configure =  ( ((PinConfig->GPIO_Mode << 2) | (0x0)) & 0x0F);
			}
			// pull down
			else
			{
				// from table 20 : PX-ODR = 0 For Pull Down
				CLR_BIT( GPIOx->ODR , PinConfig->GPIO_Pin_Number );
				pin_configure =  ( (((PinConfig->GPIO_Mode << 2) - 1) | (0x0)) & 0x0F);
			}
		}
	}
	(*configure_register) |= ( (pin_configure) << Get_Position(PinConfig->GPIO_Pin_Number) );
}



/*=========================================================================================================
 * @Fn			: MCAL_GPIO_PORT_INIT
 * @brief		: to initialize Specific Port (I/P OR O/P)
 * @param [in]	: Two Pointers to structure and status to select 8bit low or high
 * @param [in]	: status to select 8bit low pin[0:7] or 8bit high pin[8:15]
 * @retval		: none
 * Note			: LQFP48 Package has Fully port A,B and Partial C,D
 *=========================================================================================================*/

void MCAL_GPIO_Port_Init(GPIO_TypeDef* GPIOx, GPIO_Port_Configure_t* PortConfig , uint8_t Pins_Select)
{
	//Port configuration register low (GPOIx_CRL) configure pins from 0:7
	//Port configuration register high (GPOIx_CRH) configure pins from 8:15

	uint32_t pin_configure = 0;
	//clear CNFy[1:0] 00 , MODEy[1:0] 00   --> 4BIT
	switch (Pins_Select)
	{
	case GPIO_PORT_LOW:					CLR_4BYTE(GPIOx->CRL);		break;
	case GPIO_PORT_HIGH:				CLR_4BYTE(GPIOx->CRH);		break;
	case GPIO_PORT_LOW_NIBBLE_LOW: 		CLR_2BYTE(GPIOx->CRL , 0);	break;
	case GPIO_PORT_LOW_NIBBLE_HIGH: 	CLR_2BYTE(GPIOx->CRL , 16);	break;
	case GPIO_PORT_HIGH_NIBBLE_LOW: 	CLR_2BYTE(GPIOx->CRH , 0);	break;
	case GPIO_PORT_HIGH_NIBBLE_HIGH: 	CLR_2BYTE(GPIOx->CRH , 16);	break;
	default:
		CLR_4BYTE(GPIOx->CRL);
		CLR_4BYTE(GPIOx->CRH);
	}

	//if output mode
	if( (PortConfig->GPIO_Mode == GPIO_MODE_OUTPUT_PUSH_PULL) || (PortConfig->GPIO_Mode == GPIO_MODE_OUTPUT_OPEN_DRAIN) ||
			(PortConfig->GPIO_Mode == GPIO_MODE_AF_PUSH_PULL)     || (PortConfig->GPIO_Mode == GPIO_MODE_AF_OPEN_DRAIN)   )
	{
		//set MODEy[1:0] ? , CNFy[1:0] ? -> 4BIT
		pin_configure = ( ((( (PortConfig->GPIO_Mode) - 4) << 2 ) | (PortConfig->GPIO_Output_Speed)) & 0x0F );
	}
	// input mode
	else
	{
		if( (PortConfig->GPIO_Mode == GPIO_MODE_INPUT_ANALOG) || (PortConfig->GPIO_Mode == GPIO_MODE_INPUT_FLOATING))
		{
			//set CNFy[1:0] ? , MODEy[1:0] ?   --> 4BIT
			pin_configure = ( ((PortConfig->GPIO_Mode << 2 ) | (0x0)) & 0x0F );
		}
		else if ( PortConfig->GPIO_Mode == GPIO_MODE_AF_INPUT ) // deal with it as i/p analog
		{
			//set CNFy[1:0] ? , MODEy[1:0] 00 -> 2BIT
			pin_configure = ( ((PortConfig->GPIO_Mode << 2 ) | (0x0)) & 0x0F );
		}
		else
		{
			// pull up
			if( PortConfig->GPIO_Mode == GPIO_MODE_INPUT_PULL_UP )
			{
				// from table 20 : PX-ODR = 1 For Pull Up
				switch (Pins_Select) {
				case GPIO_PORT_LOW:
					for (uint32_t i = GPIO_PIN_0 ; i <= GPIO_PIN_7 ; ++i) SET_BIT( GPIOx->ODR , i );
					break;
				case GPIO_PORT_HIGH:
					for (uint32_t i = GPIO_PIN_8 ; i <= GPIO_PIN_15 ; ++i) SET_BIT( GPIOx->ODR , i );
					break;
				case GPIO_PORT_LOW_NIBBLE_LOW:
					for (uint32_t i = GPIO_PIN_0 ; i <= GPIO_PIN_3 ; ++i) SET_BIT( GPIOx->ODR , i );
					break;
				case GPIO_PORT_LOW_NIBBLE_HIGH:
					for (uint32_t i = GPIO_PIN_4 ; i <= GPIO_PIN_7 ; ++i) SET_BIT( GPIOx->ODR , i );
					break;
				case GPIO_PORT_HIGH_NIBBLE_LOW:
					for (uint32_t i = GPIO_PIN_8 ; i <= GPIO_PIN_11 ; ++i) SET_BIT( GPIOx->ODR , i );
					break;
				case GPIO_PORT_HIGH_NIBBLE_HIGH:
					for (uint32_t i = GPIO_PIN_12 ; i <= GPIO_PIN_15 ; ++i) SET_BIT( GPIOx->ODR , i );
					break;
				default:
					SET_4BYTE(GPIOx->ODR);
				}
				pin_configure = ( ((PortConfig->GPIO_Mode << 2 ) | (0x0)) & 0x0F );
			}
			// pull down
			else
			{
				// from table 20 : PX-ODR = 0 For Pull Down
				switch (Pins_Select) {
				case GPIO_PORT_LOW:
					for (uint32_t i = GPIO_PIN_0 ; i <= GPIO_PIN_7 ; ++i) CLR_BIT( GPIOx->ODR , i );
					break;
				case GPIO_PORT_HIGH:
					for (uint32_t i = GPIO_PIN_8 ; i <= GPIO_PIN_15 ; ++i) CLR_BIT( GPIOx->ODR , i );
					break;
				case GPIO_PORT_LOW_NIBBLE_LOW:
					for (uint32_t i = GPIO_PIN_0 ; i <= GPIO_PIN_3 ; ++i) CLR_BIT( GPIOx->ODR , i );
					break;
				case GPIO_PORT_LOW_NIBBLE_HIGH:
					for (uint32_t i = GPIO_PIN_4 ; i <= GPIO_PIN_7 ; ++i) CLR_BIT( GPIOx->ODR , i );
					break;
				case GPIO_PORT_HIGH_NIBBLE_LOW:
					for (uint32_t i = GPIO_PIN_8 ; i <= GPIO_PIN_11 ; ++i) CLR_BIT( GPIOx->ODR , i );
					break;
				case GPIO_PORT_HIGH_NIBBLE_HIGH:
					for (uint32_t i = GPIO_PIN_12 ; i <= GPIO_PIN_15 ; ++i) CLR_BIT( GPIOx->ODR , i );
					break;
				default:
					CLR_4BYTE(GPIOx->ODR);
				}
				pin_configure = ( (((PortConfig->GPIO_Mode << 2 ) - 1) | (0x0)) & 0x0F );
			}
		}
	}
	//configuration register LOW OR HIGH
	switch (Pins_Select) {
	case GPIO_PORT_LOW:
		for (uint32_t i = GPIO_PIN_0 ; i <= GPIO_PIN_7 ; ++i) GPIOx->CRL |= ( (pin_configure) << Get_Position(i) );
		break;
	case GPIO_PORT_HIGH:
		for (int i = GPIO_PIN_8 ; i <= GPIO_PIN_15 ; ++i) GPIOx->CRH |= ( (pin_configure) << Get_Position(i) );
		break;
	case GPIO_PORT_LOW_NIBBLE_LOW:
		for (uint32_t i = GPIO_PIN_0 ; i <= GPIO_PIN_3 ; ++i) GPIOx->CRL |= ( (pin_configure) << Get_Position(i) );
		break;
	case GPIO_PORT_LOW_NIBBLE_HIGH:
		for (uint32_t i = GPIO_PIN_4 ; i <= GPIO_PIN_7 ; ++i) GPIOx->CRL |= ( (pin_configure) << Get_Position(i) );
		break;
	case GPIO_PORT_HIGH_NIBBLE_LOW:
		for (int i = GPIO_PIN_8 ; i <= GPIO_PIN_11 ; ++i) GPIOx->CRH |= ( (pin_configure) << Get_Position(i) );
		break;
	case GPIO_PORT_HIGH_NIBBLE_HIGH:
		for (int i = GPIO_PIN_12 ; i <= GPIO_PIN_15 ; ++i) GPIOx->CRH |= ( (pin_configure) << Get_Position(i) );
		break;
	default:
		for (uint32_t i = GPIO_PIN_0 ; i <= GPIO_PIN_7 ; ++i) GPIOx->CRL |= ( (pin_configure) << Get_Position(i) );
		for (uint32_t i = GPIO_PIN_8 ; i <= GPIO_PIN_15 ; ++i) GPIOx->CRH |= ( (pin_configure) << Get_Position(i) );
	}
}


/*=========================================================================================================
 * @Fn			: MCAL_GPIO_DEINIT
 * @brief		: reset peripheral bus
 * @param [in]	: one pointer to structure
 * @retval		: none
 *=========================================================================================================*/

void MCAL_GPIO_DeInit(GPIO_TypeDef* GPIOx)
{
	/* // put reset value
	GPIOx->CRL = 0x44444444;
	GPIOx->CRH = 0x44444444;
	//GPIOx->IDR = ; read only
	GPIOx->ODR = 0x0000 0000;
	GPIOx->BRR = 0x0000 0000;
	GPIOx->BSRR= 0x0000 0000;
	GPIOx->LCKR= 0x0000 0000; */
	if(GPIOx == GPIOA)
	{
		// Bit 2IOPAEN:IO port A clock enable
		// Set and cleared by software.
		// 0: IO port A clock disabled
		// 1: IO port A clock enabled
		SET_BIT( RCC->RCC_APB2RSTR , 2 ); // Bit 2 IOPARST: I/O port A reset
		CLR_BIT( RCC->RCC_APB2RSTR , 2 );
	}
	else if (GPIOx == GPIOB)
	{
		SET_BIT( RCC->RCC_APB2RSTR , 3 ); // Bit 3 IOPBRST: IO port B reset
		CLR_BIT( RCC->RCC_APB2RSTR , 3 );

	}
	else if (GPIOx == GPIOC)
	{
		SET_BIT( RCC->RCC_APB2RSTR , 4 ); // Bit 4 IOPCRST: IO port C reset
		CLR_BIT( RCC->RCC_APB2RSTR , 4 );
	}
	else if (GPIOx == GPIOD)
	{
		SET_BIT( RCC->RCC_APB2RSTR , 5 ); // Bit 5 IOPDRST: I/O port D reset
		CLR_BIT( RCC->RCC_APB2RSTR , 5 );
	}
	else if (GPIOx == GPIOE)
	{
		SET_BIT( RCC->RCC_APB2RSTR , 6 ); // Bit 6 IOPERST: I/O port E reset
		CLR_BIT( RCC->RCC_APB2RSTR , 6 );
	}
}


/*=========================================================================================================
 * @Fn			: MCAL_GPIO_Read_Pin
 * @brief		: receive data on specific pin
 * @param [in]	: GPIOx pointer to structure , PinNumber according to specific pin
 * @retval		: data [0,1]
 *=========================================================================================================*/

uint8_t MCAL_GPIO_Read_Pin(GPIO_TypeDef* GPIOx, uint16_t PinNumber)
{
	uint8_t Data = ( READ_BIT(GPIOx->IDR , PinNumber) ? (uint8_t)GPIO_PIN_SET : (uint8_t)GPIO_PIN_RESET );
	return Data;
}


/*=========================================================================================================
 * @Fn			: MCAL_GPIO_Read_Port
 * @brief		: data on specific Port
 * @param [in]	: GPIOx pointer to structure
 * @retval		: data [0,1]
 *=========================================================================================================*/

uint32_t MCAL_GPIO_Read_Port(GPIO_TypeDef* GPIOx , uint8_t Pins_Select)
{
	uint32_t Data;
	switch (Pins_Select)
	{
	case GPIO_PORT_LOW:					Data = READ_BYTE(GPIOx->IDR , GPIO_PIN_0);		break;
	case GPIO_PORT_HIGH:				Data = READ_BYTE(GPIOx->IDR , GPIO_PIN_8);		break;
	case GPIO_PORT_LOW_NIBBLE_LOW:		Data = READ_NIBBLE(GPIOx->IDR , GPIO_PIN_0);	break;
	case GPIO_PORT_LOW_NIBBLE_HIGH:		Data = READ_NIBBLE(GPIOx->IDR , GPIO_PIN_4);	break;
	case GPIO_PORT_HIGH_NIBBLE_LOW:		Data = READ_NIBBLE(GPIOx->IDR , GPIO_PIN_8);	break;
	case GPIO_PORT_HIGH_NIBBLE_HIGH:	Data = READ_NIBBLE(GPIOx->IDR , GPIO_PIN_12);	break;
	default:
		Data = (GPIOx->IDR);
		break;
	}
	return Data;
}

/*=========================================================================================================
 * @Fn			: MCAL_GPIO_Write_Pin
 * @brief		: write data on specific pin
 * @param [in]	: GPIOx pointer to structure , PinNumber according to specific pin
 * @param [in]	: value is data [0,1]
 * @retval		: none
 *==================================================================================================================================================*/

void MCAL_GPIO_Write_Pin(GPIO_TypeDef* GPIOx, uint16_t PinNumber, uint8_t value)
{
	if(value) // true
	{
		// -----> GPIOx->ODR |= PinNumber <-----
		//Bits 15:0 BSy:Port x Set bit y (y= 0 .. 15)
		//These bits are write-only and can be accessed in Word mode only.
		//0: No action on the corresponding ODRx bit
		//1: Set the corresponding ODRx bit
		//		SET_BIT( GPIOx->BSRR , PinNumber);
		SET_BIT( GPIOx->ODR , PinNumber);
	}
	else
	{
		//Bits 15:0 BRy:Port x Reset bit y (y= 0 .. 15)
		//These bits are write-only and can be accessed in Word mode only.
		//0: No action on the corresponding ODRx bit
		//1: Reset the corresponding ODRx bit
		//		SET_BIT( GPIOx->BRR , PinNumber);
		CLR_BIT( GPIOx->ODR , PinNumber);
	}
}


/*=========================================================================================================
 * @Fn			: MCAL_GPIO_Write_Pin
 * @brief		: write data on specific Port
 * @param [in]	: GPIOx pointer to structure
 * @param [in]	: value is data [0,1]
 * @retval		: none
 *=========================================================================================================*/

void MCAL_GPIO_Write_Port(GPIO_TypeDef* GPIOx, uint32_t value ,uint8_t Pins_Select)
{
	switch (Pins_Select)
	{
	case GPIO_PORT_LOW:
		for (uint32_t i = GPIO_PIN_0 , j = 0 ; i <= GPIO_PIN_7 ; ++i , ++j)
		{
			MCAL_GPIO_Write_Pin(GPIOx , i , READ_BIT(value,j) );
		}
		break;

	case GPIO_PORT_HIGH:
		for (uint32_t i = GPIO_PIN_8 , j = 0 ; i <= GPIO_PIN_15 ; ++i , ++j)
		{
			MCAL_GPIO_Write_Pin(GPIOx , i , READ_BIT(value,j) );
		}
		break;

	case GPIO_PORT_LOW_NIBBLE_LOW:
		for (uint32_t i = GPIO_PIN_0 , j = 0 ; i <= GPIO_PIN_4 ; ++i , ++j)
		{
			MCAL_GPIO_Write_Pin(GPIOx , i , READ_BIT(value,j) );
		}
		break;

	case GPIO_PORT_LOW_NIBBLE_HIGH:
		for (uint32_t i = GPIO_PIN_4 , j = 0 ; i <= GPIO_PIN_7 ; ++i , ++j)
		{
			MCAL_GPIO_Write_Pin(GPIOx , i , READ_BIT(value,j) );
		}
		break;

	case GPIO_PORT_HIGH_NIBBLE_LOW:
		for (uint32_t i = GPIO_PIN_8 , j = 0 ; i <= GPIO_PIN_11 ; ++i , ++j)
		{
			MCAL_GPIO_Write_Pin(GPIOx , i , READ_BIT(value,j) );
		}
		break;

	case GPIO_PORT_HIGH_NIBBLE_HIGH:
		for (uint32_t i = GPIO_PIN_12 , j = 0 ; i <= GPIO_PIN_15 ; ++i , ++j)
		{
			MCAL_GPIO_Write_Pin(GPIOx , i , READ_BIT(value,j) );
		}
		break;
	case GPIO_ALL_PORT:
		GPIOx->ODR = (uint32_t)value ;
		break;
	default:
		GPIOx->ODR = value;
		break;
	}
}


/*=========================================================================================================
 * @Fn			: MCAL_GPIO_Toggle_Pin
 * @brief		: toggle specific pin
 * @param [in]	: GPIOx pointer to structure , PinNumber according to specific pin
 * @retval		: none
 *=========================================================================================================*/

void MCAL_GPIO_Toggle_Pin(GPIO_TypeDef* GPIOx, uint16_t PinNumber)
{
	TOG_BIT( GPIOx->ODR , PinNumber);
}

/*=========================================================================================================
 * @Fn			: MCAL_GPIO_Toggle_Port
 * @brief		: toggle specific port
 * @param [in]	: GPIOx pointer to structure , Pins_Select according to specific port
 * @retval		: none
 *=========================================================================================================*/

void MCAL_GPIO_Toggle_Port(GPIO_TypeDef* GPIOx, uint8_t Pins_Select)
{
	switch (Pins_Select)
	{
	case GPIO_PORT_LOW:
		for (uint32_t i = GPIO_PIN_0 , j = 0 ; i <= GPIO_PIN_7 ; ++i , ++j)
		{
			TOG_BIT( GPIOx->ODR , i);
		}
		break;

	case GPIO_PORT_HIGH:
		for (uint32_t i = GPIO_PIN_8 , j = 0 ; i <= GPIO_PIN_15 ; ++i , ++j)
		{
			TOG_BIT( GPIOx->ODR , i);
		}
		break;

	case GPIO_PORT_LOW_NIBBLE_LOW:
		for (uint32_t i = GPIO_PIN_0 , j = 0 ; i <= GPIO_PIN_4 ; ++i , ++j)
		{
			TOG_BIT( GPIOx->ODR , i);
		}
		break;

	case GPIO_PORT_LOW_NIBBLE_HIGH:
		for (uint32_t i = GPIO_PIN_4 , j = 0 ; i <= GPIO_PIN_7 ; ++i , ++j)
		{
			TOG_BIT( GPIOx->ODR , i);
		}
		break;

	case GPIO_PORT_HIGH_NIBBLE_LOW:
		for (uint32_t i = GPIO_PIN_8 , j = 0 ; i <= GPIO_PIN_11 ; ++i , ++j)
		{
			TOG_BIT( GPIOx->ODR , i);
		}
		break;

	case GPIO_PORT_HIGH_NIBBLE_HIGH:
		for (uint32_t i = GPIO_PIN_12 , j = 0 ; i <= GPIO_PIN_15 ; ++i , ++j)
		{
			TOG_BIT( GPIOx->ODR , i);
		}
		break;
	case GPIO_ALL_PORT:
		TOG_2BYTE(GPIOx->ODR , GPIO_PIN_0);
		break;
	}
}


/*=========================================================================================================
 * @Fn			: MCAL_GPIO_Lock_Pin
 * @brief		: locked specific pin until the next reset.
 * @param [in]	: GPIOx pointer to structure , PinNumber according to specific pin
 * @retval		: lock is enable to disable
 * Note			: When the LOCK sequence has been applied on a port bit
 * 					it is no longer possible to modify the value of the port bit until the next reset.
 *=========================================================================================================*/

uint8_t MCAL_GPIO_Lock_Pin(GPIO_TypeDef* GPIOx, uint16_t PinNumber)
{
	//Bit 16 LCKK[16]:Lock key
	//This bit can be read anytime. It can only be modified using the Lock Key Writing Sequence.
	//0: Port configuration lock key not active
	//1: Port configuration lock key active. GPIOx_LCKR register is locked until the next reset.
	//LOCK key writing sequence:
	//Write 1
	//Write 0
	//Write 1
	//Read 0
	//Read 1 (this read is optional but confirms that the lock is active)

	//Bits 15:0LCKy:Port x Lock bit y (y= 0 .. 15)
	//These bits are read write but can only be written when the LCKK bit is 0.
	//0: Port configuration not locked
	//1: Port configuration locked.

	volatile uint32_t seq = 1<<16;
	seq |= (PinNumber);

	// writing sequence
	//Write 1
	GPIOx->LCKR = seq;
	//Write 0
	GPIOx->LCKR = PinNumber;
	//Write 1
	GPIOx->LCKR = seq;
	//Read 0
	seq = GPIOx->LCKR;
	//Read 1
	if( (GPIOx->LCKR) & (1<<16) ) return GPIO_PIN_LOCKED;
	else return GPIO_PIN_ERROR;
}


/*=========================================================================================================
 * @Fn			: Get_Position
 * @brief		: get position pin in-order-to use to shift in CNFx In CRL , CRH
 * @param [in]	: specific pin
 * @retval		: position
 *=========================================================================================================*/
uint8_t Get_Position (uint16_t Pin_Number)
{
	uint8_t position;
	switch(Pin_Number)
	{
	case GPIO_PIN_0:
	case GPIO_PIN_8:
		position = 0 ;
		break;

	case GPIO_PIN_1:
	case GPIO_PIN_9:
		position = 4 ;
		break;

	case GPIO_PIN_2:
	case GPIO_PIN_10:
		position = 8 ;
		break;

	case GPIO_PIN_3:
	case GPIO_PIN_11:
		position = 12 ;
		break;

	case GPIO_PIN_4:
	case GPIO_PIN_12:
		position = 16 ;
		break;

	case GPIO_PIN_5:
	case GPIO_PIN_13:
		position = 20 ;
		break;

	case GPIO_PIN_6:
	case GPIO_PIN_14:
		position = 24 ;
		break;

	case GPIO_PIN_7:
	case GPIO_PIN_15:
		position = 28 ;
		break;
	}
	return position;
}
