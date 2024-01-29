/***********************************************
 * @file           : STM32_F103C6_I2C_Driver.c *
 * @author         : mohamed elatar             *
 * @Data           : November 11, 2023			*
 ************************************************/

//-----------------------------
//Includes
//-----------------------------
#include "STM32_F103C6_I2C_Driver.h"


/* =======================================================================================
 * 							Generic Variables
 * ======================================================================================= */

I2C_Config  Global_I2C_Config[2]  = {0} ;
uint32_t dummy_read ;
/*
 * =======================================================================================
 * 							Generic Macros
 * =======================================================================================
 */
#define I2C1_Index	0
#define I2C2_Index	1
#define One_MHz		1000000



/* ========================================================================
 *                            APIs Function Definitions
 * ========================================================================
 */

/*====================================================================================================
 * @Fn				- MCAL_I2C_Init
 * @brief 			- Initializes I2C
 * @param [in] 		- I2Cx: where x can be (1..2 depending on device used)
 * @param [in] 		- I2C_Config: All I2C Configuration EXTI_PinConfig_t
 * @retval 			- none
 * Note				- Support full I2X Mode and System Management Bus
						- Support I2C mode only with standard mode (100Hz)clk
	 ====================================================================================================*/
void MCAL_I2C_Init (I2C_TypeDef * I2Cx , I2C_Config * I2C_Config)
{
	uint16_t temp_register = 0 ,  freqency = 0 , result = 0;
	uint32_t Freq_Pclk1 = 8000000 ; // 8MHz in range interger not short
	// Enable Rcc
	if (I2Cx == I2C1)
	{
		Global_I2C_Config[I2C1_Index] = *I2C_Config;
		RCC_I2C1_CLK_EN();
	}
	else if( I2Cx == I2C2)
	{
		Global_I2C_Config[I2C2_Index] = *I2C_Config;
		RCC_I2C2_CLK_EN();
	}

	if(I2C_Config->I2C_Mode == I2C_Mode_I2C)
	{
		///////////// ------ [1] Timing initialize ------ /////////////
		//Program the peripheral input clock in I2C_CR2 Register in order to generate correct timings
		//FREQ[5:0]: Peripheral clock frequency
		temp_register = I2Cx->I2C_CR2;
		//clear frequency
		temp_register &= ~(I2C_CR2_FREQ); //0x3F
		//get Freq Pclk1
		Freq_Pclk1 = MCAL_RCC_GET_PCLK1_Freq();
		//Put frequency based on Pclk1 Value
		freqency = (uint16_t)(Freq_Pclk1 / One_MHz);

		//set on temp_register
		temp_register |= freqency;
		//set on CR2 register
		I2Cx->I2C_CR2 = temp_register;

		///////////// ------ [2] Configure Clock ------ /////////////
		//at first disable i2c peripheral
		I2Cx->I2C_CR1 &= ~(I2C_CR1_PE); // (0x1 << 0) position PE bit in I2C_CR1
		//clear temp_register
		temp_register = 0;

		//Clock control register in Fm/Sm mode (Master mode) I2C_CCR
		if ( (I2C_Config->I2C_SCLK == I2C_SCLK_SM_50K) || (I2C_Config->I2C_SCLK == I2C_SCLK_SM_100K))
		{
			//configure standard speed mode
			//		Thigh = CCR  * TPCLK1
			//		Thigh = TCLK / 2
			//		CCR   = TCLK / (2 * TPCLK1)
			//		CCR   = F-TPCLK1 / (2 * F-TCLK)

			result = (uint16_t)( Freq_Pclk1 / (I2C_Config->I2C_SCLK << 1) ); // <<1 equivalent 2^1 --> * 2
			//set on temp_register
			temp_register |= result;
			//set on CCR register
			I2Cx->I2C_CCR = temp_register;

			///////////// ------ [3] Configure rise time ------ /////////////
			//the maximum allowed SCL rise time is 1000 ns
			//FREQ[5:0] bits is equal to 0x08 --> TPCLK1= 125 ns
			//therefore the TRISE[5:0] bits must be programmed with 09h.
			//(1000 ns / 125 ns = 8 + 1) --> (I2C_TRISE)
			I2Cx->I2C_TRISE = freqency + 1;
		}
		else
		{
			//this configure fast mode (400khz)
		}


		///////////// ------ I2C CR1 Configuration ------ /////////////
		//get val register in temp_register
		temp_register = I2Cx->I2C_CR1;

		temp_register |= (I2C_Config->I2C_ACK_Control | I2C_Config->I2C_General_Call | \
				I2C_Config->I2C_Stretch_Mode | I2C_Config->I2C_Mode) ;

		//write in register CR1
		I2Cx->I2C_CR1 = temp_register;

		///////////// ------ I2C OAR1 & OAR2 Configuration ------ /////////////
		if(I2C_Config->I2C_Slave_Address.Enable_Dual_ADD == I2C_Dual_ADD_Enable)
		{
			//Secondary_Slave_ADD
			temp_register = I2C_OAR2_ENDUAL; // (0x1 << 0)
			temp_register |= I2C_Config->I2C_Slave_Address.Secondary_Slave_ADD_OAR2 << I2C_OAR2_ADD2_Pos; // position 1

			//write in register OAR2
			I2Cx->I2C_OAR2 = temp_register;
		}
		//Primary_Slave_ADD
		temp_register = 0;
		temp_register |= I2C_Config->I2C_Slave_Address.Primary_Slave_ADD_OAR1 << 1;
		temp_register |= I2C_Config->I2C_Slave_Address.I2C_Addressing_Slave_Mode ;

		//write in register OAR1
		I2Cx->I2C_OAR1 = temp_register;
	}
	else
	{
		//Specific SMBus But Not Support Now
	}

	///////////// ------ Enble IRQ ------ /////////////
	if(I2C_Config->PF_IRQ_Slave_Event_CallBack != NULL)
	{
		//Enable IRQ
		I2Cx->I2C_CR2 |= ( I2C_CR2_ITERREN ); // Error interrupt enable
		I2Cx->I2C_CR2 |= ( I2C_CR2_ITBUFEN ); // ptr_Buffer interrupt enable
		I2Cx->I2C_CR2 |= ( I2C_CR2_ITEVTEN ); // Event interrupt enable
		if(I2Cx == I2C1)
		{
			NVIC_EXTI31_I2C1_EV_IRQ_ENABLE();
			NVIC_EXTI32_I2C1_ER_IRQ_ENABLE();
		}
		else
		{
			NVIC_EXTI33_I2C2_EV_IRQ_ENABLE();
			NVIC_EXTI34_I2C2_ER_IRQ_ENABLE();
		}
	}
	//Flags
	I2Cx->I2C_SR1 = 0; // Reset value: 0x0000
	I2Cx->I2C_SR2 = 0; // Reset value: 0x0000

	//	Bit 0 PE: Peripheral enable
	//	0: Peripheral disable
	//	1: Peripheral enable
	SET_BIT( I2Cx->I2C_CR1 , 0);
	//I2Cx->I2C_CR1 |= (I2C_CR1_PE); The same
}


/*====================================================================================================
 * @Fn				- MCAL_I2C_DeInit
 * @brief 			- DeInitializes I2C
 * @param [in] 		- I2Cx: where x can be (1..2 depending on device used)
 * @retval 			- none
 * Note				- Reset the Model By RCC
	 ====================================================================================================*/
void MCAL_I2C_DeInit (I2C_TypeDef *I2Cx)
{
	if (I2Cx == I2C1)
	{
		RCC_I2C1_CLK_Reset();
		NVIC_EXTI31_I2C1_EV_IRQ_DISABLE();
		NVIC_EXTI32_I2C1_ER_IRQ_DISABLE();
	}
	else if( I2Cx == I2C2)
	{
		RCC_I2C2_CLK_Reset();
		NVIC_EXTI33_I2C2_EV_IRQ_DISABLE();
		NVIC_EXTI34_I2C2_ER_IRQ_DISABLE();
	}
}

/*====================================================================================================
 * @Fn				- MCAL_I2C_GPIO_Set_Pins
 * @brief 			- intialize GPIO Pins
 * @param [in] 		- I2Cx: where x can be (1..2 depending on device used)
 * @retval 			- none
 * Note				- GPIO configurations for device peripherals (Recommanded)
	 ====================================================================================================*/

void MCAL_I2C_GPIO_Set_Pins (I2C_TypeDef *I2Cx)
{
	GPIO_Pin_Configure_t pin;

	if(I2Cx == I2C1)
	{
		//		PB6 : SCL
		//		PB7 : SDA

		pin.GPIO_Pin_Number = GPIO_PIN_6;
		pin.GPIO_Output_Speed = GPIO_Speed_10;
		pin.GPIO_Mode = GPIO_MODE_AF_OPEN_DRAIN;
		MCAL_GPIO_Pin_Init(GPIOB, &pin);

		pin.GPIO_Pin_Number = GPIO_PIN_7;
		pin.GPIO_Output_Speed = GPIO_Speed_10;
		pin.GPIO_Mode = GPIO_MODE_AF_OPEN_DRAIN;
		MCAL_GPIO_Pin_Init(GPIOB, &pin);
	}
	else if (I2Cx == I2C2)
	{
		//		PB10 : SCL
		//		PB11 : SDA

		pin.GPIO_Pin_Number = GPIO_PIN_10;
		pin.GPIO_Output_Speed = GPIO_Speed_10;
		pin.GPIO_Mode = GPIO_MODE_AF_OPEN_DRAIN;
		MCAL_GPIO_Pin_Init(GPIOB, &pin);

		pin.GPIO_Pin_Number = GPIO_PIN_11;
		pin.GPIO_Output_Speed = GPIO_Speed_10;
		pin.GPIO_Mode = GPIO_MODE_AF_OPEN_DRAIN;
		MCAL_GPIO_Pin_Init(GPIOB, &pin);
	}
}

/*====================================================================================================
 * @Fn				- MCAL_I2C_Master_TX
 * @brief 			- Send ptr_Buffer in I2C from Master
 * @param [in] 		- I2Cx: where x can be (1..2 depending on device used)
 * @param [in] 		- devive_address to detect slave
 * @param [in] 		- ptr_Buffer (uint8 as word must be 8bit)
 * @param [in] 		- Data_Length 8 or 16
 * @param [in] 		- Stop ( send stop or not)
 * @param [in] 		- Start ( send start or repeat_start )
 * @retval 			- none
 * Note				- Legend: S= Start, Sr = Repeated Start, P= Stop, A= Acknowledge,
						EVx= Event (with interrupt if ITEVFEN = 1)
						EV5: SB=1, cleared by reading SR1 register followed by writing DR register with Address.
						EV6:ADDR=1, cleared by reading SR1 register followed by reading SR2.
						EV8_1:TxE=1, shift register empty, dataregister empty, write Data1 in DR.
						EV8:TxE=1, shift register not empty, dataregister empty, cleared by writing DR register .
						EV8_2:TxE=1, BTF = 1, Program Stop request. TxE and BTF are cleared by hardware by the Stop condition
						EV9:ADD10=1, cleared by reading SR1 register followed by writing DR register.
====================================================================================================*/

void MCAL_I2C_Master_TX (I2C_TypeDef * I2Cx , uint16_t devive_address , uint8_t *ptr_Buffer , uint32_t Data_Length , E_Stop_Condition Stop , E_Repeated_Start Start)
{
	uint32_t i;
	///////////// ------ (1) send start bit on SDA Bus ------ /////////////
	I2C_Generate_Start( I2Cx , Enable_Send_Start , Start);

	///////////// ------  EV5: raise flag as SB=1   ------ /////////////
	//followed by writing DR register with Address
	while( ! I2c_Get_Flag_Status(I2Cx, EV5) );

	///////////// ------ (2) writing DR register with Address   ------ /////////////
	I2C_Send_Address(I2Cx, devive_address, Direction_TX_W);

	///////////// ------ EV6: rise flag as ADDR=1 load address in data register ------ /////////////
	//For 7-bit addressing, the bit is set after the ACK of the byte
	//cleared by reading SR1 register followed by reading SR2
	while( ! I2c_Get_Flag_Status(I2Cx, EV6) );

	///////////// ------ EV8_1: rise flag as shift register empty, dataregister empty ------ /////////////
	// Data register empty & Master Mode & Bus busy &  Data bytes transmitted
	while( ! I2c_Get_Flag_Status(I2Cx, Master_Byte_Transmitting) );


	///////////// ------ (3) writing DR register with data   ------ /////////////
	for ( i=0 ; i<Data_Length ; i++)
	{
		I2Cx->I2C_DR = ptr_Buffer[i];
		// EV8:TxE=1, shift register not empty, dataregister empty, cleared by writing DR register
		while ( ! I2c_Get_Flag_Status(I2Cx, EV8) );
	}

	///////////// ------ EV8_2: rise flag as EV8_2:TxE=1, BTF = 1, Program Stop request  ------ /////////////
	// Byte transfer finished
	while ( ! I2c_Get_Flag_Status(I2Cx, EV8_2) );

	///////////// ------ (4) send stop bit on SDA Bus ------ /////////////
	if( Stop == With_Stop )
	{
		I2C_Generate_Stop( I2Cx , Enable_Send_Stop );
	}
}



/*====================================================================================================
 * @Fn				- MCAL_I2C_Master_RX
 * @brief 			- receive ptr_Buffer in I2C from Slave
 * @param [in] 		- I2Cx: where x can be (1..2 depending on device used)
 * @param [in] 		- devive_address to detect slave
 * @param [in] 		- ptr_Buffer (uint8 as word must be 8bit)
 * @param [in] 		- Data_Length 8 or 16
 * @param [in] 		- Stop ( send stop or not)
 * @param [in] 		- Start ( send start or repeat_start )
 * @retval 			- none
 * Note				- Legend: S= Start, S₁ = Repeated Start, P= Stop, A= Acknowledge, NA= Non-acknowledge,
						EVX= Event (with interrupt if ITEVFEN=1)
						EV5: SB=1, cleared by reading SR1 register followed by writing DR register.
						EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2. In 10-bit master receiver mode, this se-
						quence should be followed by writing CR2 with START = 1.
						EV6_1: no associated flag event, used for 1 byte reception only. The Acknowledge disable and Stop condition
						generation are made just after EV6, that is after ADDR is cleared.
						EV7: RXNE=1 cleared by reading DR register.
						EV7_1: RxNE=1 cleared by reading DR register, program ACK=0 and STOP request
						EV9: ADD10=1, cleared by reading SR1 register followed by writing DR register.
====================================================================================================*/

void MCAL_I2C_Master_RX (I2C_TypeDef * I2Cx , uint16_t devive_address , uint8_t *ptr_Buffer , uint32_t Data_Length , E_Stop_Condition Stop , E_Repeated_Start Start)
{
	uint32_t i;
	uint8_t index = ((I2Cx==I2C1) ? I2C1_Index : I2C2_Index);


	///////////// ------ (1) send start bit on SDA Bus ------ /////////////
	I2C_Generate_Start( I2Cx , Enable_Send_Start , Start);

	///////////// ------  EV5: raise flag as SB=1   ------ /////////////
	//followed by writing DR register with Address
	while( ! I2c_Get_Flag_Status(I2Cx, EV5) );

	///////////// ------ (2) writing DR register with Address   ------ /////////////
	I2C_Send_Address(I2Cx, devive_address, Direction_RX_R);

	///////////// ------ EV6: rise flag as ADDR=1 load address in data register ------ /////////////
	//For 7-bit addressing, the bit is set after the ACK of the byte
	//cleared by reading SR1 register followed by reading SR2
	while( ! I2c_Get_Flag_Status(I2Cx, EV6) );



	// Acknowledge enable send by master
	if( Global_I2C_Config[index].I2C_ACK_Control == I2C_ACK_Enable )
	{
		I2C_ACKnowledge_Config(I2Cx, Enable_Send_ACK);
	}
	///////////// ------ (3) Reading DR register  ------ /////////////
	if( Data_Length )
	{
		for( i = 0 ; i<Data_Length-1 ; ++i )
		{
			// RxNE=1 cleared by reading DR register
			while( ! I2c_Get_Flag_Status(I2Cx, EV7) );

			*ptr_Buffer = I2Cx->I2C_DR;
			ptr_Buffer++;
		}
		// PROGRAM ACK=0 AND STOP REQUEST
		I2C_ACKnowledge_Config(I2Cx , Disable_Send_ACK);
	}

	// STOP REQUEST
	while( ! I2c_Get_Flag_Status(I2Cx, EV7_1) );

	///////////// ------ (4) send stop bit on SDA Bus ------ /////////////
	if( Stop == With_Stop )
	{
		I2C_Generate_Stop(I2Cx , Enable_Send_Stop );
	}

}


/*====================================================================================================
 * @Fn				- I2C_Generate_Start
 * @brief 			- send start bit
 * @param [in] 		- I2Cx: where x can be (1..2 depending on device used)
 * @param [in] 		- New_State to detect enable send start or disable send
 * @param [in] 		- Start (send start or repeated start)
 * @retval 			- none
====================================================================================================*/

void I2C_Generate_Start (I2C_TypeDef * I2Cx , E_Function_State New_State , E_Repeated_Start Start)
{
	//check if bus is idle or idle
	//if send repeated start not check as this currnet master hold bus
	if(Start == Send_Start)
	{
		//check until bus be idle as i sent start bit so bus must be idle
		while( I2c_Get_Flag_Status( I2Cx , I2C_Flag_Busy ) );
	}
	//	Bit 8 START: Start generation (I2C_CR1)
	//	This bit is set and cleared by software and cleared by hardware when start is sent or PE=0.

	//	In Master Mode:
	//	0: No Start generation
	//	1: Repeated start generation

	//	In Slave mode:
	//	0: No Start generation
	//	1: Start generation when the bus is free
	if( New_State == Enable_Send_Start)
	{
		//send start
		SET_BIT( I2Cx->I2C_CR1 , I2C_CR1_START_Pos );
	}
	else
	{
		//not send start
		CLR_BIT( I2Cx->I2C_CR1 , I2C_CR1_START_Pos );
	}
}



/*====================================================================================================
 * @Fn				- I2C_Generate_Stop
 * @brief 			- send stop bit
 * @param [in] 		- I2Cx: where x can be (1..2 depending on device used)
 * @param [in] 		- New_State to detect enable send stop or disable send
 * @retval 			- none
====================================================================================================*/

void I2C_Generate_Stop (I2C_TypeDef * I2Cx , E_Function_State New_State)
{
	//	Bit 9 STOP: Stop generation (I2C_CR1)
	//	The bit is set and cleared by software, cleared by hardware when a Stop condition is
	//	detected, set by hardware when a timeout error is detected.

	//	In Master Mode:
	//	0: No Stop generation.
	//	1: Stop generation after the current byte transfer or after the current Start condition is sent.

	//	In Slave mode:
	//	0: No Stop generation.
	//	1: Release the SCL and SDA lines after the current byte transfer.
	if( New_State == Enable_Send_Stop)
	{
		//Stop generation
		SET_BIT( I2Cx->I2C_CR1 , I2C_CR1_STOP_Pos);
	}
	else
	{
		//no Stop generation
		CLR_BIT( I2Cx->I2C_CR1 , I2C_CR1_STOP_Pos);
	}
}

/*====================================================================================================
 * @Fn				- I2C_ACKnowledge_Config
 * @brief 			- configration acknowledge
 * @param [in] 		- I2Cx: where x can be (1..2 depending on device used)
 * @param [in] 		- New_State to detect Enable_Send_ACK or disable
 * @retval 			- none
====================================================================================================*/

void I2C_ACKnowledge_Config (I2C_TypeDef * I2Cx , E_Function_State New_State)
{
	//	Bit 10 ACK: Acknowledge enable (I2C_CR1)
	//	This bit is set and cleared by software and cleared by hardware when PE=0.
	//	0: No acknowledge returned
	//	1: Acknowledge returned after a byte is received (matched address or data)
	if( New_State == Enable_Send_ACK)
	{
		// Acknowledge returned after a byte is received
		SET_BIT( I2Cx->I2C_CR1 , I2C_CR1_ACK_Pos);
	}
	else
	{
		// No acknowledge returned
		CLR_BIT( I2Cx->I2C_CR1 , I2C_CR1_ACK_Pos);
	}

}

/*====================================================================================================
 * @Fn				- I2C_Send_Address
 * @brief 			- send address slave
 * @param [in] 		- I2Cx: where x can be (1..2 depending on device used)
 * @param [in] 		- address slave
 * @param [in] 		- Direction detect master write or read this address
 * @retval 			- none
 * note				- slave address 7B - 10B here support 7B
====================================================================================================*/

void I2C_Send_Address(I2C_TypeDef * I2Cx , uint16_t address , E_I2C_Direction Direction)
{
	//	Bits 7:1ADD[7:1]: Interface address
	//	bits 7:1 of address
	//	Bit 0ADD0: Interface address
	//	7-bit addressing mode: don’t care
	//	10-bit addressing mode: bit 0 of address

	// lsb BIT consider (R/W)  [0-->W , 1-->R]
	address = (address << 1);
	if ( Direction == Direction_TX_W)
	{
		//Write
		address &= ~(1 << 0);
	}
	else
	{
		//Read
		address |= (1 << 0);
	}
	//Load Addrss and R/W in data register
	I2Cx->I2C_DR = address;
}


/*====================================================================================================
 * @Fn				- I2c_Get_Flag_Status
 * @brief 			- check stauts flags set or reset
 * @param [in] 		- I2Cx: where x can be (1..2 depending on device used)
 * @param [in] 		- Flag require check
 * @retval 			- Reset_flag or Set_flag
====================================================================================================*/

E_Flag_Status I2c_Get_Flag_Status (I2C_TypeDef * I2Cx , E_Status Flag)
{
	uint32_t flag1 = 0 , flag2 = 0 , last_event = 0;

	//check flag is set ? || by default reset
	E_Flag_Status flag_status = Reset_flag;

	switch(Flag)
	{

	case I2C_Flag_Busy:
	{
		//		Bit 1 BUSY: Bus busy (I2C_SR2)
		//		0: No communication on the bus
		//		1: Communication ongoing on the bus
		//		– Set by hardware on detection of SDA or SCL low
		//		– cleared by hardware on detection of a Stop condition.
		if( READ_BIT( I2Cx->I2C_SR2 , I2C_SR2_BUSY_Pos ) )
		{
			//Communication ongoing on the bus
			flag_status = Set_flag;
		}
		else
		{
			//No communication on the bus
			flag_status = Reset_flag;
		}
		break;
	}

	case EV5:
	{
		//		EV5: SB=1, cleared by reading SR1 register followed by writing DR register with Address

		//		Bit 0 SB: Start bit (Master mode) (I2C_SR1)
		//		0: No Start condition
		//		1: Start condition generated.
		//		– Set when a Start condition generated.
		//		– Cleared by software by reading the SR1 register followed by writing the DR register, or by
		//		hardware when PE=0
		if( READ_BIT( I2Cx->I2C_SR1 , I2C_SR1_SB_Pos ) )
		{
			//Start condition generated.
			flag_status = Set_flag;
		}
		else
		{
			//No Start condition
			flag_status = Reset_flag;
		}
		break;
	}

	case EV6:
	{
		//		EV6:ADDR=1, cleared by reading SR1 register followed by reading SR2

		//		ADDR: Address sent (master mode)/matched (slave mode) (I2C_SR1)
		//		This bit is cleared by software reading SR1 register followed reading SR2, or by hardware
		//		when PE=0.
		//
		//		Address matched (Slave)
		//		0: Address mismatched or not received.
		//		1: Received address matched.
		//
		//		Address sent (Master)
		//		0: No end of address transmission
		//		1: End of address transmission
		//		– For 10-bit addressing, the bit is set after the ACK of the 2nd byte.
		//		– For 7-bit addressing, the bit is set after the ACK of the byte.
		if( READ_BIT( I2Cx->I2C_SR1 , I2C_SR1_ADDR_Pos ) )
		{
			//End of address transmission
			flag_status = Set_flag;
		}
		else
		{
			//No end of address transmission
			flag_status = Reset_flag;
		}
		// cleared by software reading SR1 register followed reading SR2
		dummy_read = I2Cx->I2C_SR1;
		dummy_read = I2Cx->I2C_SR2;
		break;
	}

	case Master_Byte_Transmitting:
	{
		//		Data register empty & Master Mode & Bus busy &  Data bytes transmitted

		//		Bit 7 TxE: Data register empty (transmitters) (I2C_SR1)
		//		0: Data register not empty
		//		1: Data register empty
		//		– Set when DR is empty in transmission. TxE is not set during address phase.
		//		– Cleared by software writing to the DR register or by hardware after a start or a stop condition

		//		Bit 0 MSL: Master/slave (I2C_SR2)
		//		0: Slave Mode
		//		1: Master Mode
		//		– Set by hardware as soon as the interface is in Master mode (SB=1).
		//		– Cleared by hardware after detecting a Stop condition on the bus or a loss of arbitration
		//		flag2 = flag2 << 16;
		//
		//		Bit 1 BUSY: Bus busy (I2C_SR2)
		//		0: No communication on the bus
		//		1: Communication ongoing on the bus
		//		– Set by hardware on detection of SDA or SCL low
		//		– cleared by hardware on detection of a Stop condition.
		//
		//		Bit 2 TRA: Transmitter/receiver (I2C_SR2)
		//		0: Data bytes received
		//		1: Data bytes transmitted
		//		This bit is set depending on the R/W bit of the address byte, at the end of total address
		//		phase.
		//		It is also cleared by hardware after detectionof Stop condition (STOPF=1), repeated Start
		//		condition, loss of bus arbitration (ARLO=1), or when PE=0.
		flag1 = I2Cx->I2C_SR1;
		flag2 = I2Cx->I2C_SR2;
		flag2 = flag2 << 16;

		last_event = ( (flag1 | flag2) & ((uint32_t)0XFFFFFFFF) ); //AS SR1 4Byte && SR2 4Byte

		if( (last_event & Flag) == Flag)
		{
			flag_status = Set_flag;
		}
		else
		{
			flag_status = Reset_flag;
		}
		break;
	}

	case EV7:
	case EV7_1:
	{
		//		EV 7 : RxNE=1 cleared by reading DR register

		//		Bit 6 RxNE: Data register not empty (receivers)
		//		0: Data register empty
		//		1: Data register not empty
		//		– Set when data register is not empty in receiver mode. RxNE is not set during address phase.
		//		– Cleared by software reading or writing the DR register or by hardware when PE=0.
		if( READ_BIT( I2Cx->I2C_SR1 , I2C_SR1_RXNE_Pos ) )
		{
			// Data register not empty
			flag_status = Set_flag;
		}
		else
		{
			// Data register empty not receive yet
			flag_status = Reset_flag;
		}
		break;
	}

	case EV8_1:
	case EV8:
	{
		//		EV8_1: TxE=1 , shift register empty, dataregister empty, write Data1 in DR --> (First) <--
		//		EV8:   TxE=1 , shift register not empty, dataregister empty, cleared by writing DR register

		//		Bit 7 TxE: Data register empty (transmitters) (I2C_SR1)
		//		0: Data register not empty
		//		1: Data register empty
		//		– Set when DR is empty in transmission. TxE is not set during address phase.
		//		– Cleared by software writing to the DR register or by hardware after a start or a stop condition
		if( READ_BIT( I2Cx->I2C_SR1 , I2C_SR1_TXE_Pos ) )
		{
			//Data register empty
			flag_status = Set_flag;
		}
		else
		{
			//Data register not empty
			flag_status = Reset_flag;
		}
		break;
	}

	case EV8_2:
	{
		//	EV8_2:TxE=1, BTF = 1, Program Stop request. TxE and BTF are cleared by hardware by the Stop condition
		//		Bit 2 BTF: Byte transfer finished
		//		0: Data byte transfer not done
		//		1: Data byte transfer succeeded
		//		– In transmission when a new byte should be sent and DR has not been written yet (TxE=1).
		//		– Cleared by software reading SR1 followed by either a read or write in the DR register or by
		//		hardware after a start or a stop condition in transmission or when PE=0
		if( READ_BIT( I2Cx->I2C_SR1 , I2C_SR1_BTF_Pos ) )
		{
			//Data byte transfer succeeded
			flag_status = Set_flag;
		}
		else
		{
			//Data byte transfer not done
			flag_status = Reset_flag;
		}
		break;
	}
	}
	return flag_status;
}



void MCAL_I2C_Slave_TX (I2C_TypeDef * I2Cx , uint8_t data)
{
	I2Cx->I2C_DR = data;
}

uint8_t MCAL_I2C_Slave_RX (I2C_TypeDef * I2Cx )
{
	return (uint8_t)I2Cx->I2C_DR;
}

void I2C1_EV_IRQHandler()
{
	volatile uint32_t dummy_read_irq = 0;
	I2C_TypeDef * I2Cx = I2C1;

	uint32_t temp1 , temp2 , temp3 ;

	temp1 = READ_BIT( I2Cx->I2C_CR2 , I2C_CR2_ITEVTEN_Pos); // Event interrupt enable
	temp2 = READ_BIT( I2Cx->I2C_CR2 , I2C_CR2_ITBUFEN_Pos); // Buffer interrupt enable

	//	Bit 4 STOPF: Stop detection (slave mode) (I2C_SR1)
	//	0: No Stop condition detected
	//	1: Stop condition detected
	temp3 = READ_BIT( I2Cx->I2C_SR1 , I2C_SR1_STOPF_Pos);

	if(temp1 && temp3)
	{
		I2Cx->I2C_CR1 |= 0x0000;
		Slave_States(I2Cx , I2C_EV_STOP);
	}

	temp3 = READ_BIT( I2Cx->I2C_SR1 , I2C_SR1_ADDR_Pos);
	// handle irq generate by ADDR event
	// master mode : address is sent
	// slave mode  : adress matched with own address
	if( temp1 && temp3)
	{
		// irq is generate by ADDR event
		if ( READ_BIT( I2Cx->I2C_SR2 , I2C_SR2_MSL_Pos ) )
		{
			//master mode
		}
		else
		{
			//salve mode
			// In slave mode, it is recommended to perform the complete clearing sequence (READ
			// SR1 then READ SR2) after ADDR is set
			dummy_read_irq = I2Cx->I2C_SR1;
			dummy_read_irq = I2Cx->I2C_SR1;
			Slave_States(I2Cx , I2C_EV_ADDR_MATCH);
		}
	}

	temp3 = READ_BIT( I2Cx->I2C_SR1 , I2C_SR1_TXE_Pos);
	// handle for irq generate by TXE event
	if( temp1 && temp2 && temp3)
	{
		//check device mode
		if( READ_BIT( I2Cx->I2C_SR2 , I2C_SR2_MSL_Pos) )
		{
			//master mode

		}
		else
		{
			//slave mode
			Slave_States(I2Cx, I2C_EV_DATA_REQ);
		}
	}
}

void I2C1_ER_IRQHandler()
{

}

void I2C2_EV_IRQHandler()
{

}

void I2C2_ER_IRQHandler()
{

}

void Slave_States (I2C_TypeDef * I2Cx , E_Slave_State_Irq Flag)
{
	uint8_t index = ((I2Cx==I2C1) ? I2C1_Index : I2C2_Index);

	switch(Flag)
	{

	case I2C_ERROR_AF:
	{
		// make sure that slave is really in transmitter mode
		if( READ_BIT(I2Cx->I2C_SR2 , I2C_SR2_TRA_Pos) )
		{
			//slave shouldn't send anything else
		}
		break;
	}

	case I2C_EV_STOP:
	{
		// make sure that slave is really in transmitter mode
		if( READ_BIT(I2Cx->I2C_SR2 , I2C_SR2_TRA_Pos) )
		{
			Global_I2C_Config[index].PF_IRQ_Slave_Event_CallBack(I2C_EV_STOP);
		}
		break;
	}

	case I2C_EV_ADDR_MATCH:
	{
		Global_I2C_Config[index].PF_IRQ_Slave_Event_CallBack(I2C_EV_ADDR_MATCH);
		break;
	}

	case I2C_EV_DATA_REQ:
	{
		if( READ_BIT( I2Cx->I2C_SR2 , I2C_SR2_TRA_Pos) )
		{
			Global_I2C_Config[index].PF_IRQ_Slave_Event_CallBack(I2C_EV_DATA_REQ);
		}
		break;
	}

	case I2C_EV_DATA_RCV:
	{
		if( ! READ_BIT( I2Cx->I2C_SR2 , I2C_SR2_TRA_Pos) )
		{
			Global_I2C_Config[index].PF_IRQ_Slave_Event_CallBack(I2C_EV_DATA_RCV);
		}
		break;
	}
	}
}
/*
 * =======================================================================================
 * 							Generic Interrupt
 * =======================================================================================
 */
