/***********************************************
 * @file           : STM32_F103C6_EEPROM_Driver.c *
 * @author         : mohamed elatar             *
 * @Data           : November 11, 2023			*
 ************************************************/

//-----------------------------
//Includes
//-----------------------------
#include "STM32_F103C6_EEPROM_Driver.h"

/* ========================================================================
 *                            APIs Function Definitions
 * ========================================================================
 */

/*====================================================================================================
 * @Fn				- MCAL_EEPROM_Init
 * @brief 			- Initializes EEPROM
 * @param [in] 		- EEPROMx: where x can be (1..2 depending on device used)
 * @param [in] 		- EEPROM_Config: All EEPROM Configuration EXTI_PinConfig_t
 * @retval 			- none
 * Note				- Support full I2X Mode and System Management Bus
						- Support EEPROM mode only with standard mode (100Hz)clk
	 ====================================================================================================*/
void EEPROM_init(void)
{
	I2C_Config i2c_config;
	i2c_config.I2C_General_Call = I2C_General_call_Enable;
	i2c_config.I2C_ACK_Control = I2C_ACK_Enable;
	i2c_config.I2C_SCLK = I2C_SCLK_SM_100K;
	i2c_config.I2C_Mode = I2C_Mode_I2C;
	i2c_config.PF_IRQ_Slave_Event_CallBack = NULL;
	i2c_config.I2C_Stretch_Mode = I2C_Clock_stretching_Enable;

	MCAL_I2C_GPIO_Set_Pins(I2C1);
	MCAL_I2C_Init(I2C1, &i2c_config);
}


uint8_t EEPROM_Write (uint32_t memory_address , uint8_t * ptr_buffer_TX , uint8_t data_length)
{
	uint8_t i = 0;
	uint8_t Buffer[9];
	Buffer[0] = (uint8_t)(memory_address>>8);		//upper byte
	Buffer[1] = (uint8_t)memory_address;		//lower byte

	for( i=2 ; i<(data_length + 2) ; i++)
	{
		Buffer[i] = ptr_buffer_TX[i-2];
	}

	MCAL_I2C_Master_TX(I2C1 , EEPROM_Slave_Address , Buffer , data_length+2 , With_Stop , Send_Start);
	return 0;
}


uint8_t EEPROM_Read (uint32_t memory_address , uint8_t * ptr_buffer_RX , uint8_t data_length)
{
	uint8_t Buffer[2];
	Buffer[0] = (uint8_t)(memory_address>>8);		//upper byte
	Buffer[1] = (uint8_t)memory_address;		//lower byte

	MCAL_I2C_Master_TX(I2C1 , EEPROM_Slave_Address , Buffer , 2 , Without_Stop , Send_Start); //write address only
	MCAL_I2C_Master_RX(I2C1 , EEPROM_Slave_Address , ptr_buffer_RX , data_length , With_Stop , Send_Repeated_Start); //read data

	return 0;
}
