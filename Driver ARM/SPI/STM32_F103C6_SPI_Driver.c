/***********************************************
 * @file           : STM32_F103C6_SPI_Driver.c *
 * @author         : mohamed elatar             *
 * @Data           : November 11, 2023			*
 ************************************************/

//-----------------------------
//Includes
//-----------------------------
#include "STM32_F103C6_SPI_Driver.h"


/* =======================================================================================
 * 							Generic Variables
 * ======================================================================================= */

SPI_Config * Global_SPI_Config[2]  = {NULL , NULL} ;

/*
 * =======================================================================================
 * 							Generic Macros
 * =======================================================================================
 */
#define SPI1_Index	0
#define SPI2_Index	1



/* ========================================================================
 *                            APIs Function Definitions
 * ========================================================================
 */

/*====================================================================================================
 * @Fn				- MCAL_SPI_Init
 * @brief 			- Initializes SPI
 * @param [in] 		- SPIx: where x can be (1..3 depending on device used)
 * @param [in] 		- SPI_Config: All SPI Configuration EXTI_PinConfig_t
 * @retval 			- none
 * Note				- Support full duplex master/slave only & NSS HW/SW
 	 	 	 	 	- in case master you have to configure pin and drive it
 ====================================================================================================*/
void MCAL_SPI_Init (SPI_TypeDef * SPIx , SPI_Config * SPI_Config)
{
	//safety register
	uint16_t temp_reg_CR1 = 0;
	uint16_t temp_reg_CR2 = 0;

	if(SPIx == SPI1)
	{
		Global_SPI_Config[SPI1_Index] = SPI_Config;
		RCC_SPI1_CLK_EN();
	}else if(SPIx == SPI2)
	{
		Global_SPI_Config[SPI2_Index] = SPI_Config;
		RCC_SPI2_CLK_EN();
	}

	//enable spi  (SPI_CR1) Bit6 SPE: SPI enable
	SET_BIT( temp_reg_CR1 , 6);

	//master or slave
	temp_reg_CR1 |= SPI_Config->Device_Mode;

	//communication mode
	temp_reg_CR1 |= SPI_Config->Communication_Mode;

	//frame_format
	temp_reg_CR1 |= SPI_Config->Frame_Format;

	//data size
	temp_reg_CR1 |= SPI_Config->Data_Size;

	//clock_polarity
	temp_reg_CR1 |= SPI_Config->Clk_Polarity;

	//clock_phase
	temp_reg_CR1 |= SPI_Config->Clk_Phase;

	//------------- NSS -----------------//
	if (SPI_Config->NSS == SPI_NSS_HardWare_Master_SS_out)
	{
		//		The NSS pin may also be used as an output if enabled (SSOE bit)
		//		and driven low if the SPI is in master configuration
		//		all NSS pins from devices connected to the Master NSS pin see a low level and become slaves
		temp_reg_CR2 |= SPI_Config->NSS;
	}
	else if(SPI_Config->NSS == SPI_NSS_HardWare_Master_SS_in)
	{
		//		This configuration allows multimaster capability for devices operating in master mode
		temp_reg_CR2 |= SPI_Config->NSS;
	}
	else
	{
		//		The slave select information is driven internally by the value of the SSI bit in the SPI_CR1 register
		temp_reg_CR1 |= SPI_Config->NSS;
	}

	//set prescaler baudrate
	temp_reg_CR1 |= SPI_Config->BaudRate_Prescaler;

	//enable interrupt
	if( SPI_Config->IRQ_Enable != SPI_IRQ_Enable_None )
	{
		// SPI Enable IRQ
		temp_reg_CR2 |= SPI_Config->IRQ_Enable;

		if( SPIx == SPI1 )
		{
			NVIC_EXTI35_SPI1_ENABLE();
		}
		else if( SPIx == SPI2 )
		{
			NVIC_EXTI36_SPI2_ENABLE();
		}
	}

	SPIx->SPI_CR1 = temp_reg_CR1;
	SPIx->SPI_CR2 = temp_reg_CR2;
	//SPIx->SPI_CRCPR = 0x0;
}


/*====================================================================================================
 * @Fn				- MCAL_SPI_DeInit
 * @brief 			- DeInitializes SPI
 * @param [in] 		- SPIx: where x can be (1..3 depending on device used)
 * @retval 			- none
 * Note				- Reset the Model By RCC
 ====================================================================================================*/
void MCAL_SPI_DeInit (SPI_TypeDef *SPIx)
{
	if( SPIx == SPI1 )
	{
		RCC_SPI1_CLK_Reset();
		NVIC_EXTI35_SPI1_DISABLE();
	}
	else if( SPIx == SPI2 )
	{
		RCC_SPI2_CLK_Reset();
		NVIC_EXTI36_SPI2_DISABLE();
	}
}

/*====================================================================================================
 * @Fn				- MCAL_SPI_Send_Data
 * @brief 			- Send Buffer in SPI
 * @param [in] 		- SPIx: where x can be (1..3 depending on device used)
 * @param [in] 		- pTxBuffer Buffer (uint16 as word maybe 9bit)
 * @param [in] 		- PollingEn   Enable pooling or disable it
 * @retval 			- none
 * Note				- The data byte is parallel-loaded into the Tx buffer during a write cycle.
						The transmit sequence begins when the slave device receives the clock signal and the most
						significant bit of the data on its MOSI pin. The remaining bits (the 7 bits in 8-bit data frame
						format, and the 15 bits in 16-bit data frame format) are loaded into the shift-register. The
						TXE flag in the SPI_SR register is set on the transfer of data from the Tx Buffer to the shift
						register and an interrupt is generated if the TXEIE bit in the SPI_CR2 register is set.
 ====================================================================================================*/

void MCAL_SPI_Send_Data (SPI_TypeDef *SPIx, uint16_t *pTxBuffer, Polling_mechism PollingEn )
{
	//	Bit1 TXE:Transmit buffer empty
	//	0: Tx buffer not empty
	//	1: Tx buffer empty

	//	Bit 7BSY: Busy flag
	//	0: SPI (or I2S) not busy
	//	1: SPI (or I2S) is busy in communication or Tx buffer is not empty
	//	This flag is set and cleared by hardware.
	if(PollingEn == enable)
		while( !READ_BIT( SPIx->SPI_SR , 1) && !READ_BIT( SPIx->SPI_SR , 7));

	SPIx->SPI_DR = *pTxBuffer;
}


/*====================================================================================================
 * @Fn				- MCAL_SPI_Send_String
 * @brief 			- Send Buffer in SPI
 * @param [in] 		- SPIx: where x can be (1..3 depending on device used)
 * @param [in] 		- ptr_str pointer to char
 * @param [in] 		- PollingEn   Enable pooling or dsable it
 * @retval 			- none
 ====================================================================================================*/

void MCAL_SPI_Send_String (SPI_TypeDef *SPIx, uint8_t * ptr_str , Polling_mechism PollingEn )
{
	while( *ptr_str != NULL && *ptr_str != '\r')
	{
		MCAL_SPI_Send_Data(SPIx, *ptr_str , PollingEn);
		ptr_str++;
	}
}

/*====================================================================================================
 * @Fn				- MCAL_SPI_Receive_Data
 * @brief 			- Send Buffer in SPI
 * @param [in] 		- SPIx: where x can be (1..3 depending on device used)
 * @param [in] 		- pTxBuffer Buffer (uint16 as word maybe 9bit)
 * @param [in] 		- PollingEn   Enable pooling or disable it
 * @retval 			- data register
 * Note				- The Data in shift register is transferred to Rx Buffer and the RXNE flag (SPI_SR register) is set
						An Interrupt is generated if the RXNEIEbit is set in the SPI_CR2 register.
 	 	 	 	 	 	After the last sampling clock edge the RXNE bit is set, a copy of the data byte received in
						the shift register is moved to the Rx buffer. When the SPI_DR register is read, the SPI
						peripheral returns this buffered value. Clearing of the RXNE bit is performed by reading the SPI_DR register.
 ====================================================================================================*/
uint16_t MCAL_SPI_Receive_Data (SPI_TypeDef *SPIx, uint16_t *pRxBuffer , Polling_mechism PollingEn )
{
	//	Bit0 RXNE :Receive buffer not empty
	//	0: Rx buffer empty
	//	1: Rx buffer not empty
	if(PollingEn == enable)
		while( ! READ_BIT( SPIx->SPI_SR , 0) );

	*pRxBuffer = SPIx->SPI_DR;

	return SPIx->SPI_DR;
}

/*====================================================================================================
 * @Fn				- MCAL_SPI_TX_RX
 * @brief 			- Send Buffer in SPI
 * @param [in] 		- SPIx: where x can be (1..3 depending on device used)
 * @param [in] 		- ptr_str pointer to char
 * @param [in] 		- PollingEn   Enable pooling or dsable it
 * @retval 			- none
 ====================================================================================================*/
void MCAL_SPI_TX_RX (SPI_TypeDef *SPIx, uint16_t *pBuffer, Polling_mechism PollingEn )
{
	// TX
	if(PollingEn == enable)
		while( !READ_BIT( SPIx->SPI_SR , 1) && !READ_BIT( SPIx->SPI_SR , 7));

	SPIx->SPI_DR = *pBuffer;

	// RX
	if(PollingEn == enable)
		while( ! READ_BIT( SPIx->SPI_SR , 0));

	*pBuffer = SPIx->SPI_DR;
}


/*====================================================================================================
 * @Fn				- MCAL_SPI_GPIO_Set_Pins
 * @brief 			- intialize GPIO Pins
 * @param [in] 		- SPIx: where x can be (1..3 depending on device used)
 * @retval 			- none
 * Note				- When transmitting with the parity enabled (PCE bit set to 1 in the SPI_CR1 register),
						the value written in the MSB (bit 7 or bit 8 depending on the data length) has no effect
						because it is replaced by the parity.
						When receiving with the parity enabled, the value read in the MSB bit is the received parity bit.
 ====================================================================================================*/

void MCAL_SPI_GPIO_Set_Pins (SPI_TypeDef *SPIx)
{
	GPIO_Pin_Configure_t PinConfig;
	// 	PA4 : SPI1_NSS
	//	PA5 : SPI1_SCK
	//	PA6 : SPI1_MISO
	//	PA7 : SPI1_MOSI
	if(SPIx == SPI1)
	{
		//Master SPI
		if(Global_SPI_Config[SPI1_Index]->Device_Mode == SPI_Device_Mode_Master)
		{
			//PA4 : SPI1_NSS
			switch( Global_SPI_Config[SPI1_Index]->NSS)
			{
			case SPI_NSS_HardWare_Master_SS_in:
				//Hardware master /slave Input floating
				PinConfig.GPIO_Pin_Number = GPIO_PIN_4;
				PinConfig.GPIO_Mode = GPIO_MODE_INPUT_FLOATING;
				MCAL_GPIO_Pin_Init(GPIOA , &PinConfig);
				break;

			case SPI_NSS_HardWare_Master_SS_out:
				//Hardware master/ NSS output enabled Alternate function push-pull
				PinConfig.GPIO_Pin_Number = GPIO_PIN_4;
				PinConfig.GPIO_Output_Speed = GPIO_Speed_10;
				PinConfig.GPIO_Mode = GPIO_MODE_AF_PUSH_PULL;
				MCAL_GPIO_Pin_Init(GPIOA , &PinConfig);
				break;

			case SPI_NSS_SoftWare_Internal_set:
				//Software Not used. Can be used as a GPIO
				PinConfig.GPIO_Pin_Number = GPIO_PIN_4;
				PinConfig.GPIO_Output_Speed = GPIO_Speed_10;
				PinConfig.GPIO_Mode = GPIO_MODE_OUTPUT_PUSH_PULL;
				MCAL_GPIO_Pin_Init(GPIOA , &PinConfig);
				MCAL_GPIO_Write_Pin( GPIOA , GPIO_PIN_4 , LOGIC_HIGH);
			}

			//PA5 : SPI SCK
			//Master Alternate function push-pull
			PinConfig.GPIO_Pin_Number = GPIO_PIN_5;
			PinConfig.GPIO_Output_Speed = GPIO_Speed_10;
			PinConfig.GPIO_Mode = GPIO_MODE_AF_PUSH_PULL;
			MCAL_GPIO_Pin_Init(GPIOA , &PinConfig);

			//PA6 : SPI_MISO
			//Full duplex / master Alternate function push-pull
			PinConfig.GPIO_Pin_Number = GPIO_PIN_6;
			PinConfig.GPIO_Mode = GPIO_MODE_INPUT_FLOATING;
			MCAL_GPIO_Pin_Init(GPIOA , &PinConfig);

			//PA7 : SPI_MOSI
			//Full duplex / master Input floating
			PinConfig.GPIO_Pin_Number = GPIO_PIN_7;
			PinConfig.GPIO_Output_Speed = GPIO_Speed_10;
			PinConfig.GPIO_Mode = GPIO_MODE_AF_PUSH_PULL;
			MCAL_GPIO_Pin_Init(GPIOA , &PinConfig);
		}

		//Slave SPI
		else if(Global_SPI_Config[SPI1_Index]->Device_Mode == SPI_Device_Mode_Slave)
		{
			//PA4 : SPI1_NSS
			if( Global_SPI_Config[SPI1_Index]->NSS == SPI_NSS_HardWare_Slave)
			{
				//Hardware master /slave Input floating
				PinConfig.GPIO_Pin_Number = GPIO_PIN_4;
				PinConfig.GPIO_Mode = GPIO_MODE_INPUT_FLOATING;
				MCAL_GPIO_Pin_Init(GPIOA , &PinConfig);
			}

			//PA5 : SPI SCK
			//Master Alternate function push-pull
			PinConfig.GPIO_Pin_Number = GPIO_PIN_5;
			PinConfig.GPIO_Mode = GPIO_MODE_INPUT_FLOATING;
			MCAL_GPIO_Pin_Init(GPIOA , &PinConfig);

			//PA6 : SPI_MISO
			//Full duplex / slave (point to point) Alternate function push-pull
			PinConfig.GPIO_Pin_Number = GPIO_PIN_6;
			PinConfig.GPIO_Mode = GPIO_MODE_AF_PUSH_PULL;
			PinConfig.GPIO_Output_Speed = GPIO_Speed_10;
			MCAL_GPIO_Pin_Init(GPIOA , &PinConfig);

			//PA7 : SPI_MOSI
			//Full duplex / slave Input floating
			PinConfig.GPIO_Pin_Number = GPIO_PIN_7;
			PinConfig.GPIO_Mode = GPIO_MODE_INPUT_FLOATING;
			MCAL_GPIO_Pin_Init(GPIOA , &PinConfig);
		}

	}

	// 	PB12 : SPI2_NSS
	//	PB13 : SPI2_SCK
	//	PB14 : SPI2_MISO
	//	PB15 : SPI2_MOSI
	else if(SPIx == SPI2)
	{
		//Master SPI
		if(Global_SPI_Config[SPI2_Index]->Device_Mode == SPI_Device_Mode_Master)
		{
			//PA4 : SPI1_NSS
			switch( Global_SPI_Config[SPI2_Index]->NSS)
			{
			case SPI_NSS_HardWare_Master_SS_in:
				//Hardware master /slave Input floating
				PinConfig.GPIO_Pin_Number = GPIO_PIN_12;
				PinConfig.GPIO_Mode = GPIO_MODE_INPUT_FLOATING;
				MCAL_GPIO_Pin_Init(GPIOB , &PinConfig);
				break;

			case SPI_NSS_HardWare_Master_SS_out:
				//Hardware master/ NSS output enabled Alternate function push-pull
				PinConfig.GPIO_Pin_Number = GPIO_PIN_12;
				PinConfig.GPIO_Output_Speed = GPIO_Speed_10;
				PinConfig.GPIO_Mode = GPIO_MODE_AF_PUSH_PULL;
				MCAL_GPIO_Pin_Init(GPIOB , &PinConfig);
				break;
			}

			//PA5 : SPI SCK
			//Master Alternate function push-pull
			PinConfig.GPIO_Pin_Number = GPIO_PIN_13;
			PinConfig.GPIO_Output_Speed = GPIO_Speed_10;
			PinConfig.GPIO_Mode = GPIO_MODE_AF_PUSH_PULL;
			MCAL_GPIO_Pin_Init(GPIOB , &PinConfig);

			//PA6 : SPI_MISO
			//Full duplex / master Alternate function push-pull
			PinConfig.GPIO_Pin_Number = GPIO_PIN_14;
			PinConfig.GPIO_Mode = GPIO_MODE_INPUT_FLOATING;
			MCAL_GPIO_Pin_Init(GPIOB , &PinConfig);

			//PA7 : SPI_MOSI
			//Full duplex / master Input floating
			PinConfig.GPIO_Pin_Number = GPIO_PIN_15;
			PinConfig.GPIO_Output_Speed = GPIO_Speed_10;
			PinConfig.GPIO_Mode = GPIO_MODE_AF_PUSH_PULL;
			MCAL_GPIO_Pin_Init(GPIOB , &PinConfig);
		}

		//Slave SPI
		else if(Global_SPI_Config[SPI1_Index]->Device_Mode == SPI_Device_Mode_Slave)
		{
			//PA4 : SPI1_NSS
			if( Global_SPI_Config[SPI1_Index]->NSS == SPI_NSS_HardWare_Slave)
			{
				//Hardware master /slave Input floating
				PinConfig.GPIO_Pin_Number = GPIO_PIN_12;
				PinConfig.GPIO_Mode = GPIO_MODE_INPUT_FLOATING;
				MCAL_GPIO_Pin_Init(GPIOB , &PinConfig);
			}

			//PA5 : SPI SCK
			//Master Alternate function push-pull
			PinConfig.GPIO_Pin_Number = GPIO_PIN_13;
			PinConfig.GPIO_Mode = GPIO_MODE_INPUT_FLOATING;
			MCAL_GPIO_Pin_Init(GPIOB , &PinConfig);

			//PA6 : SPI_MISO
			//Full duplex / slave (point to point) Alternate function push-pull
			PinConfig.GPIO_Pin_Number = GPIO_PIN_14;
			PinConfig.GPIO_Mode = GPIO_MODE_AF_PUSH_PULL;
			PinConfig.GPIO_Output_Speed = GPIO_Speed_10;
			MCAL_GPIO_Pin_Init(GPIOB , &PinConfig);

			//PA7 : SPI_MOSI
			//Full duplex / slave Input floating
			PinConfig.GPIO_Pin_Number = GPIO_PIN_15;
			PinConfig.GPIO_Mode = GPIO_MODE_INPUT_FLOATING;
			MCAL_GPIO_Pin_Init(GPIOB , &PinConfig);
		}
	}
}

/*
 * =======================================================================================
 * 							Generic Interrupt
 * =======================================================================================
 */
//	Bit1 TXE:Transmit buffer empty
//	0: Tx buffer not empty
//	1: Tx buffer empty

//	Bit0 RXNE:Receive buffer not empty
//	0: Rx buffer empty
//	1: Rx buffer not empty

//	Bit4 CRCERR:CRC error flag
//	0: CRC value received matches the SPI_RXCRCR value
//	1: CRC value received does not match the SPI_RXCRCR value
void SPI1_IRQHandler (void)
{
	struct S_IRQ_SRC irq_scr;

	irq_scr.TXE  = READ_BIT( SPI1->SPI_SR , 1);
	irq_scr.RXNE = READ_BIT( SPI1->SPI_SR , 0);
	irq_scr.ERRI = READ_BIT( SPI1->SPI_SR , 4);

	Global_SPI_Config[SPI1_Index]->PF_IRQ_CallBack(irq_scr);
}

void SPI2_IRQHandler (void)
{
	struct S_IRQ_SRC irq_scr;

	irq_scr.TXE  = READ_BIT( SPI2->SPI_SR , 1);
	irq_scr.RXNE = READ_BIT( SPI2->SPI_SR , 0);
	irq_scr.ERRI = READ_BIT( SPI2->SPI_SR , 4);

	Global_SPI_Config[SPI2_Index]->PF_IRQ_CallBack(irq_scr);
}
