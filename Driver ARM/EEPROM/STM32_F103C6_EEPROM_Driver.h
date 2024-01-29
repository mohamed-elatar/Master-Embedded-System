/***********************************************
 * @file           : STM32_F103C6_EEPROM_Driver.h	*
 * @author         : mohamed elatar             *
 * @Data           : November 11, 2023			*
 ************************************************/


#ifndef STM32_F103C6_EEPROM_Driver_H_
#define STM32_F103C6_EEPROM_Driver_H_

//-----------------------------
//Includes
//-----------------------------
#include "STM32_F103C6_I2C_Driver.h"

#define EEPROM_Slave_Address		0x2A

/* ===============================================
 * 			APIs Supported by "MCAL EEPROM DRIVER"
 * ===============================================
 */

void EEPROM_init(void);
uint8_t EEPROM_Write (uint32_t memory_address , uint8_t * ptr_buffer_TX , uint8_t data_length);
uint8_t EEPROM_Read (uint32_t memory_address , uint8_t * ptr_buffer_RX , uint8_t data_length);
#endif /* STM32_F103C6_EEPROM_Driver_H_ */
