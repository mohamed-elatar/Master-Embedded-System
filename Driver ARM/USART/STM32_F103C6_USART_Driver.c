/***********************************************
 * @file           : STM32_F103C6_USART_Driver.c *
 * @author         : mohamed elatar             *
 * @Data           : November 11, 2023			*
 ************************************************/

//-----------------------------
//Includes
//-----------------------------
#include "STM32_F103C6_USART_Driver.h"


/* =======================================================================================
 * 							Generic Variables
 * ======================================================================================= */

USART_Config * Global_USART1_Config  = NULL ;
USART_Config * Global_USART2_Config  = NULL ;
USART_Config * Global_USART3_Config  = NULL ;

/*
 * =======================================================================================
 * 							Generic Macros
 * =======================================================================================
 */




/*
 * =======================================================================================
 * 							Generic Functions
 * =======================================================================================
 */



/* ========================================================================
 *                            APIs Function Definitions
 * ========================================================================
 */

/*====================================================================================================
 * @Fn				- MCAL_USART_Init
 * @brief 			- Initializes USART (Supported Asynchrounous now)
 * @param [in] 		- USARTx: where x can be (1..3 depending on device used)
 * @param [in] 		- USART_Config: All USART Configuration EXTI_PinConfig_t
 * @retval 			- none
 * Note				- Support for Now Asynchronous mode & Clock 8 MHZ S
 ====================================================================================================*/
void MCAL_USART_Init (USART_TypeDef * USARTx , USART_Config * USART_Config)
{
	uint32_t pclk , BRR  ;

	// all file can access this UART
	if( USARTx == USART1 )
		Global_USART1_Config = USART_Config ;

	else if( USARTx == USART2 )
		Global_USART2_Config = USART_Config ;

	else if( USARTx == USART3 )
		Global_USART3_Config = USART_Config ;

	//	enable the Clock for given USART peripheral
	if ( USARTx == USART1 )
		RCC_USART1_CLK_EN();

	else if ( USARTx == USART2 )
		RCC_USART2_CLK_EN();

	else if ( USARTx == USART3 )
		RCC_USART3_CLK_EN();

	// USART_CR1  Bit 13 UE: USART enable
	SET_BIT( USARTx->USART_CR1 , 13);

	// enable TX & RX
	// USART_CR1 Bit 3 TE: Transmitter enable & Bit 2 RE: Receiver enable
	USARTx->USART_CR1 |= USART_Config->USART_Mode ;

	// USARTx->CR1  Bit 12 M: Word length (Data)
	USARTx->USART_CR1 |= USART_Config->Data_Length;

	// USARTx->CR1 	Bit 10 PCE: Parity control enable     Bit 9 PS: Parity selection
	USARTx->USART_CR1 |= USART_Config->Parity ;

	// USART_CR2  Bits 13:12 STOP: STOP bits (configure number of stop bits)
	USARTx->USART_CR2 |= USART_Config->StopBits ;

	//USART_CR3  Bit 9 CTSE: CTS enable   Bit 8 RTSE: RTS enable
	USARTx->USART_CR3 |= USART_Config->HW_flow_control ;


	//Configuration of BRR(Baudrate register)
	//PCLK1 for USART [2,3]
	//PCLK2 for USART [1]
	if ( USARTx == USART1 )
	{
		pclk = MCAL_RCC_GET_PCLK2_Freq();
	}
	else
	{
		pclk = MCAL_RCC_GET_PCLK1_Freq();
	}

	BRR = USART_BRR_Register( pclk , USART_Config->USART_BaudRate );
	USARTx->USART_BRR = BRR ;


	// ENABLE / DISABLE Interrupt
	if (USART_Config->IRQ_Enable  != USART_IRQ_Enable_NONE)
	{
		USARTx->USART_CR1 |= (USART_Config->IRQ_Enable);

		// Enable NVIC For USARTx IRQ
		if ( USARTx == USART1 ){
			NVIC_EXTI37_USART1_ENABLE(); }

		else if ( USARTx == USART2 ){
			NVIC_EXTI38_USART2_ENABLE(); }

		else if ( USARTx == USART3 ){
			NVIC_EXTI39_USART3_ENABLE(); }
	}
}


/*====================================================================================================
 * @Fn				- MCAL_USART_DeInit
 * @brief 			- DeInitializes USART
 * @param [in] 		- USARTx: where x can be (1..3 depending on device used)
 * @retval 			- none
 * Note				- Reset the Model By RCC
 ====================================================================================================*/
void MCAL_USART_DeInit (USART_TypeDef *USARTx)
{
	if ( USARTx == USART1 )
	{
		RCC_USART1_CLK_Reset();
		NVIC_EXTI37_USART1_DISABLE();
	}

	else if ( USARTx == USART2 )
	{
		RCC_USART2_CLK_Reset();
		NVIC_EXTI38_USART2_DISABLE();
	}

	else if ( USARTx == USART3 )
	{
		RCC_USART3_CLK_Reset();
		NVIC_EXTI39_USART3_DISABLE();
	}
}

/*====================================================================================================
 * @Fn				- MCAL_USART_Send_Data
 * @brief 			- Send Buffer in USART
 * @param [in] 		- USARTx: where x can be (1..3 depending on device used)
 * @param [in] 		- pTxBuffer Buffer (uint16 as word maybe 9bit)
 * @param [in] 		- PollingEn   Enable pooling or dsable it
 * @retval 			- none
 * Note				- When transmitting with the parity enabled (PCE bit set to 1 in the USART_CR1 register),
						the value written in the MSB (bit 7 or bit 8 depending on the data length) has no effect
						because it is replaced by the parity.
						When receiving with the parity enabled, the value read in the MSB bit is the received parity bit.
 ====================================================================================================*/

void MCAL_USART_Send_Data (USART_TypeDef *USARTx, uint16_t *pTxBuffer, Polling_mechism PollingEn )
{
	//	Bit7 TXE: Transmit data register empty
	//	0: Data is not transferred to the shift register
	//	1: Data is transferred to the shift register
	//	Note: This bit is used during single buffer transmission.
	if (PollingEn == enable)
		while(! READ_BIT( USARTx->USART_SR , 7) ); // wait until transfar all data to shift register

	//Check the USART Data Length [9BIT or 8BIT] on frame
	if (Global_USART1_Config->Data_Length == USART_Data_Length_9B)
	{
		//This is 9bit data transfer ==> 0x1FF For 9B Mask
		USARTx->USART_DR = (*pTxBuffer & (uint16_t)0x01FF);
	}
	else
	{
		//This is 8bit data transfer ==> 0xFF For 8B Mask
		USARTx->USART_DR = (*pTxBuffer  & (uint8_t)0xFF);
	}
}


/*====================================================================================================
 * @Fn				- MCAL_USART_Send_String
 * @brief 			- Send Buffer in USART
 * @param [in] 		- USARTx: where x can be (1..3 depending on device used)
 * @param [in] 		- ptr_str pointer to char
 * @param [in] 		- PollingEn   Enable pooling or dsable it
 * @retval 			- none
 ====================================================================================================*/

void MCAL_USART_Send_String (USART_TypeDef *USARTx, uint8_t * ptr_str , Polling_mechism PollingEn )
{
	while( *ptr_str != NULL)
	{
		MCAL_USART_Send_Data(USARTx, ptr_str , PollingEn);
		ptr_str++;
	}
}

/*====================================================================================================
 * @Fn				- MCAL_USART_WAIT_TC
 * @brief 			- wait until flag TX be set
 * @param [in] 		- USARTx: where x can be (1..3 depending on device used)
 * @param [in] 		- pTxBuffer Buffer (uint16 as word maybe 9bit)
 * @param [in] 		- PollingEn   Enable pooling or dsable it
 * @retval 			- none
 * Note				- if TXE is set
 ====================================================================================================*/
void MCAL_USART_WAIT_TC (USART_TypeDef *USARTx )
{
	//	Bit 6TC: Transmission complete
	//	This bit is set by hardware ifthe transmission of a frame containing data is complete
	//	0: Transmission is not complete
	//	1: Transmission is complete
	while( ! READ_BIT( USARTx->USART_SR , 6 ) );
}



/*====================================================================================================
 * @Fn				- MCAL_USART_Receive_Data
 * @brief 			- Send Buffer in USART
 * @param [in] 		- USARTx: where x can be (1..3 depending on device used)
 * @param [in] 		- pTxBuffer Buffer (uint16 as word maybe 9bit)
 * @param [in] 		- PollingEn   Enable pooling or dsable it
 * @retval 			- none
 * Note				- When transmitting with the parity enabled (PCE bit set to 1 in the USART_CR1 register),
						the value written in the MSB (bit 7 or bit 8 depending on the data length) has no effect
						because it is replaced by the parity.
						When receiving with the parity enabled, the value read in the MSB bit is the received parity bit.
 ====================================================================================================*/
uint16_t MCAL_USART_Receive_Data (USART_TypeDef *USARTx, uint16_t *pRxBuffer , Polling_mechism PollingEn )
{
	//	Bit5 RXNE: Read data register not empty
	//	This bit is set by hardware when the content ofthe RDR shift register has been transferred to
	//	the USART_DR register
	//	0: Data is not received
	//	1: Received data is ready to be read.
	if (PollingEn == enable)
	{
		while( ! READ_BIT( USARTx->USART_SR , 5 ) );
	}


	// Check the USART Data Length item for (9BIT or 8BIT) on frame
	//	USART_Data_Length_9B
	if (Global_USART1_Config->Data_Length == USART_Data_Length_9B)
	{
		if (Global_USART1_Config->Parity == USART_Parity_NONE)
		{
			// no parity So all 9bit are considered data
			*((uint16_t*) pRxBuffer) = USARTx->USART_DR ;
			return (USARTx->USART_DR);
		}
		else
		{
			// Parity is used, so, 8bits will be of user data and 1 bit is parity
			*((uint16_t*) pRxBuffer) = ( USARTx->USART_DR  & (uint8_t)0xFF );
			return (USARTx->USART_DR  & (uint8_t)0xFF);
		}
	}
	//	USART_Data_Length_8B
	else
	{
		//This is 8bit data
		if (Global_USART1_Config->Parity == USART_Parity_NONE)
		{
			// no parity So all 8bit are considered data
			*((uint16_t*) pRxBuffer) = ( USARTx->USART_DR  & (uint8_t)0xFF ) ;
			return (USARTx->USART_DR  & (uint8_t)0xFF);
		}

		else
		{
			// Parity is used, so,7 bits will be of user data and 1 bit is parity
			*((uint16_t*) pRxBuffer) = ( USARTx->USART_DR  & (uint8_t)0X7F );
			return (USARTx->USART_DR  & (uint8_t)0X7F);
		}
	}
}


/*====================================================================================================
 * @Fn				- MCAL_USART_GPIO_Set_Pins
 * @brief 			- intialize GPIO Pins
 * @param [in] 		- USARTx: where x can be (1..3 depending on device used)
 * @retval 			- none
 * Note				- When transmitting with the parity enabled (PCE bit set to 1 in the USART_CR1 register),
						the value written in the MSB (bit 7 or bit 8 depending on the data length) has no effect
						because it is replaced by the parity.
						When receiving with the parity enabled, the value read in the MSB bit is the received parity bit.
 ====================================================================================================*/

void MCAL_USART_GPIO_Set_Pins (USART_TypeDef *USARTx)
{
	GPIO_Pin_Configure_t PinConfig;

	// GPIO configurations for device peripherals
	// From Table 24. USARTs
	if ( USARTx == USART1 )
	{
		//PA9 TX
		//PA10 RX
		//PA11 CTS
		//PA12 RTS

		//PA9 TX
		PinConfig.GPIO_Pin_Number = GPIO_PIN_9;
		PinConfig.GPIO_Mode = GPIO_MODE_AF_PUSH_PULL;
		PinConfig.GPIO_Output_Speed = GPIO_Speed_10;
		MCAL_GPIO_Pin_Init(GPIOA , &PinConfig);

		//PA10 RX
		PinConfig.GPIO_Pin_Number = GPIO_PIN_10;
		PinConfig.GPIO_Mode = GPIO_MODE_INPUT_FLOATING;
		MCAL_GPIO_Pin_Init(GPIOA, &PinConfig);


		if ( Global_USART1_Config->HW_flow_control == USART_HwFlowCtl_CTS || Global_USART1_Config->HW_flow_control == USART_HwFlowCtl_RTS_CTS )
		{
			//PA11 CTS
			PinConfig.GPIO_Pin_Number = GPIO_PIN_11;
			PinConfig.GPIO_Mode = GPIO_MODE_INPUT_FLOATING;
			MCAL_GPIO_Pin_Init(GPIOA, &PinConfig);
		}

		if ( Global_USART1_Config->HW_flow_control == USART_HwFlowCtl_RTS || Global_USART1_Config->HW_flow_control == USART_HwFlowCtl_RTS_CTS )
		{
			//PA12 RTS
			PinConfig.GPIO_Pin_Number = GPIO_PIN_12;
			PinConfig.GPIO_Mode = GPIO_MODE_AF_PUSH_PULL;
			PinConfig.GPIO_Output_Speed = GPIO_Speed_10;
			MCAL_GPIO_Pin_Init(GPIOA , &PinConfig);
		}
	}

	else if ( USARTx == USART2 )
	{
		//PA2 TX
		//PA3 RX
		//PA0 CTS
		//PA1 RTS


		//PA2 TX
		PinConfig.GPIO_Pin_Number = GPIO_PIN_2;
		PinConfig.GPIO_Mode = GPIO_MODE_AF_PUSH_PULL;
		PinConfig.GPIO_Output_Speed = GPIO_Speed_10;
		MCAL_GPIO_Pin_Init(GPIOA , &PinConfig);

		//PA3 RX
		PinConfig.GPIO_Pin_Number = GPIO_PIN_3;
		PinConfig.GPIO_Mode = GPIO_MODE_INPUT_FLOATING;
		MCAL_GPIO_Pin_Init(GPIOA, &PinConfig);
		MCAL_GPIO_Pin_Init(GPIOA, &PinConfig);

		if ( Global_USART2_Config->HW_flow_control == USART_HwFlowCtl_CTS || Global_USART2_Config->HW_flow_control == USART_HwFlowCtl_RTS_CTS )
		{
			//PA0 CTS
			PinConfig.GPIO_Pin_Number = GPIO_PIN_0;
			PinConfig.GPIO_Mode = GPIO_MODE_INPUT_FLOATING;
			MCAL_GPIO_Pin_Init(GPIOA, &PinConfig);
		}

		if ( Global_USART2_Config->HW_flow_control == USART_HwFlowCtl_RTS || Global_USART2_Config->HW_flow_control == USART_HwFlowCtl_RTS_CTS )
		{
			//PA1 RTS
			PinConfig.GPIO_Pin_Number = GPIO_PIN_1;
			PinConfig.GPIO_Mode = GPIO_MODE_AF_PUSH_PULL;
			PinConfig.GPIO_Output_Speed = GPIO_Speed_10;
			MCAL_GPIO_Pin_Init(GPIOA , &PinConfig);
		}
	}

	else if ( USARTx == USART3 )
	{
		//PB10 TX
		//PB11 RX
		//PB13 CTS
		//PA14 RTS

		//PB10 TX
		PinConfig.GPIO_Pin_Number = GPIO_PIN_10;
		PinConfig.GPIO_Mode = GPIO_MODE_AF_PUSH_PULL;
		PinConfig.GPIO_Output_Speed = GPIO_Speed_10;
		MCAL_GPIO_Pin_Init(GPIOB , &PinConfig);

		//PB11 RX
		PinConfig.GPIO_Pin_Number = GPIO_PIN_11;
		PinConfig.GPIO_Mode = GPIO_MODE_INPUT_FLOATING;
		MCAL_GPIO_Pin_Init(GPIOB, &PinConfig);

		if ( Global_USART3_Config->HW_flow_control == USART_HwFlowCtl_CTS || Global_USART3_Config->HW_flow_control == USART_HwFlowCtl_RTS_CTS )
		{
			//PB13 CTS
			PinConfig.GPIO_Pin_Number = GPIO_PIN_13;
			PinConfig.GPIO_Mode = GPIO_MODE_INPUT_FLOATING;
			MCAL_GPIO_Pin_Init(GPIOB, &PinConfig);
		}

		if ( Global_USART3_Config->HW_flow_control == USART_HwFlowCtl_RTS || Global_USART3_Config->HW_flow_control == USART_HwFlowCtl_RTS_CTS )
		{
			//PA14 RTS
			PinConfig.GPIO_Pin_Number = GPIO_PIN_14;
			PinConfig.GPIO_Mode = GPIO_MODE_AF_PUSH_PULL;
			PinConfig.GPIO_Output_Speed = GPIO_Speed_10;
			MCAL_GPIO_Pin_Init(GPIOB , &PinConfig);
		}
	}
}

//////////// Inturrupt //////////////

void USART1_IRQHandler (void)
{
	Global_USART1_Config->PF_IRQ_CallBack();
}

void USART2_IRQHandler (void)
{
	Global_USART2_Config->PF_IRQ_CallBack();
}

void USART3_IRQHandler (void)
{
	Global_USART3_Config->PF_IRQ_CallBack();
}
