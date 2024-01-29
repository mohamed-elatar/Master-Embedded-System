/***********************************************
 * @file           : STM32_F103C6_SPI_Driver.h*
 * @author         : mohamed elatar             *
 * @Data           : November 11, 2023			*
 ************************************************/


#ifndef STM32_F103C6_SPI_Driver_H_
#define STM32_F103C6_SPI_Driver_H_

//-----------------------------
//Includes
//-----------------------------
#include "STM32_F103C6_GPIO_Driver.h"


//-----------------------------
//Structure
//-----------------------------

struct S_IRQ_SRC
{
	uint8_t TXE:1  ; //TX Buffer empty interrupt
	uint8_t RXNE:1 ; //RX Buffer not empty interrupt
	uint8_t ERRI:1 ; //Error interrupt
	uint8_t Reserved:5 ;
};
typedef struct
{
	uint16_t 	Device_Mode;			// Specifics SPI Operation Mode Based on @ref_SPI_Mode_Define

	uint16_t 	Communication_Mode;		// Specifics SPI bidirectional [3\4] wire mode state Based on @ref_Communication_Mode_Define

	uint16_t	Frame_Format;			// Specifics send LSB || MSB Based on @ref_SPI_Frame_Format_Define

	uint16_t	Data_Size;				// Specifics 8\16 bits transmit  Based on @ref_SPI_Data_Size_Define

	uint16_t	Clk_Polarity;			// Specifics idle clock 1 or 0  Based on @ref_SPI_Clk_Polarity_Define

	uint16_t	Clk_Phase;				// Specifics  capture strobe at the first\second edge on the SCK pin Based on @ref_SPI_Clk_Phase_Define

	uint16_t	NSS;					// Specifics  NSS management by hardware or software for both master and slave Based on @ref_SPI_NSS_Define

	uint16_t	BaudRate_Prescaler;		// Specifics  Baud rate control Based on @ref_SPI_BaudRate_Prescaler_Define

	uint16_t	IRQ_Enable;				// enable or disable SPI interrupts Based on @ref_SPI_IRQ_Define

	void(*PF_IRQ_CallBack)(struct S_IRQ_SRC irq_source); // will be called once the irq happen
}SPI_Config;


//-----------------------------
//References Macros
//-----------------------------

//@ref_SPI_Mode_Define
//--------------------------------------
//Bit 2MSTR:Master selection
//0: Slave configuration
//1: Master configuration
#define SPI_Device_Mode_Slave				(0x0 << 2) //(SPI_CR1)
#define SPI_Device_Mode_Master				(0x1 << 2) //(SPI_CR1)



//@ref_Communication_Mode_Define
//--------------------------------------
//Bit 15BIDIMODE:Bidirectional data mode enable
//0: 2-line unidirectional data mode selected
//1: 1-line bidirectional data mode selected
//--------------------------------------
//Bit14 BIDIOE:Output enable in bidirectional mode
//0: Output disabled (receive-only mode)
//1: Output enabled (transmit-only mode)
//--------------------------------------
//Bit 10RXONLY:Receive only
//0: Full duplex (Transmit and receive)
//1: Output disabled (Receive-only mode)
#define SPI_Direction_2Lines				(0x0 << 15) //(SPI_CR1)
#define SPI_Direction_2Lines_RX_Only		(0x1 << 10) //(SPI_CR1)
#define SPI_Direction_1Lines_RX_Only		(0x1 << 15) //(SPI_CR1)
#define SPI_Direction_1Lines_TX_Only		(0x1 << 15) | (0x1 << 14) //(SPI_CR1)




//@ref_SPI_Frame_Format_Define
//--------------------------------------
//Bit 7LSBFIRST:Frame format
//0: MSB transmitted first
//1: LSB transmitted first
#define SPI_Frame_Format_MSB_Send_First		(0x0 << 7) //(SPI_CR1)
#define SPI_Frame_Format_LSB_Send_First		(0x1 << 7) //(SPI_CR1)




// @ref_SPI_Data_Size_Define
//--------------------------------------
//Bit11 DFF:Data frame format
//0: 8-bit data frame format is selected for transmission/reception
//1: 16-bit data frame format is selected for transmission/reception
#define SPI_Data_Size_8B					(0x0 << 11) //(SPI_CR1)
#define SPI_Data_Size_16B					(0x1 << 11) //(SPI_CR1)





//@ref_SPI_Clk_Polarity_Define
//--------------------------------------
//Bit1CPOL:Clock polarity
//0: CK to 0 when idle
//1: CK to 1 when idle
#define SPI_Clk_Polarity_Low_When_Idle		(0x0 << 1) //(SPI_CR1)
#define SPI_Clk_Polarity_High_When_Idle		(0x1 << 1) //(SPI_CR1)




//@ref_SPI_Clk_Phase_Define
//--------------------------------------
//Bit0 CPHA:Clock phase
//0: The first clock transition is the first data capture edge
//1: The second clock transition is the first data capture edge
//Note: This bit should not be changed when communication is
#define SPI_Clk_Phase_1edge_data_capture	(0x0 << 0) //(SPI_CR1)
#define SPI_Clk_Phase_2edge_data_capture	(0x1 << 0) //(SPI_CR1)




//@ref_SPI_NSS_Define
//--------------------------------------
//Bit2 SSOE:SS output enable
//0: SS output is disabled
//1: SS output is enabled
//Hardware
#define SPI_NSS_HardWare_Slave				(0x0)
#define SPI_NSS_HardWare_Master_SS_in		(0x0 << 2) //(SPI_CR2)
#define SPI_NSS_HardWare_Master_SS_out		(0x1 << 2) //(SPI_CR2)

//Bit9 SSM: Software slave management.
//0: Software slave management disabled
//1: Software slave management enabled
//--------------------------------------
//Bit8 SSI:Internal slave select
//This bit has an effect only when the SSM bit is set. The value of this bit is forced onto the
//NSS pin and the IO value of the NSS pin is ignored.
//software
#define SPI_NSS_SoftWare_Internal_reset		(0x0 << 9) //(SPI_CR1)
#define SPI_NSS_SoftWare_Internal_set		(0x1 << 9) | (0x1 << 8) //(SPI_CR1)




//@ref_SPI_BaudRate_Prescaler_Define
//--------------------------------------
//Bits 5:3 BR[2:0]:Baud rate control
//000: fPCLK/2
//001: fPCLK/4
//010: fPCLK/8
//011: fPCLK/16
//100: fPCLK/32
//101: fPCLK/64
//110: fPCLK/128
//111: fPCLK/256
#define SPI_BaudRate_Pre_2					(0x0 << 3) //(SPI_CR1)
#define SPI_BaudRate_Pre_4					(0x1 << 3) //(SPI_CR1)
#define SPI_BaudRate_Pre_8					(0x2 << 3) //(SPI_CR1)
#define SPI_BaudRate_Pre_16					(0x3 << 3) //(SPI_CR1)
#define SPI_BaudRate_Pre_32					(0x4 << 3) //(SPI_CR1)
#define SPI_BaudRate_Pre_64					(0x5 << 3) //(SPI_CR1)
#define SPI_BaudRate_Pre_128				(0x6 << 3) //(SPI_CR1)
#define SPI_BaudRate_Pre_256				(0x7 << 3) //(SPI_CR1)



//@ref_SPI_IRQ_Define
//--------------------------------------
//Bit7 TXEIE:Tx buffer empty interrupt enable
//0: TXE interrupt masked
//1: TXE interrupt not masked
//--------------------------------------
//Bit6 RXNEIE:RX buffer not empty interrupt enable
//0: RXNE interrupt masked
//1: RXNE interrupt not masked
//--------------------------------------
//Bit5 ERRIE:Error interrupt enable
//0: Error interrupt is masked
//1: Error interrupt is enabled
#define SPI_IRQ_Enable_None					(0x0)
#define SPI_IRQ_Enable_TXEIE				(0x1 << 7) //(SPI_CR2)
#define SPI_IRQ_Enable_RXNEIE				(0x1 << 6) //(SPI_CR2)
#define SPI_IRQ_Enable_ERRIOE				(0x1 << 5) //(SPI_CR2)




/* ===============================================
 * 			APIs Supported by "MCAL SPI DRIVER"
 * ===============================================
 */

void MCAL_SPI_Init (SPI_TypeDef * SPIx , SPI_Config * SPI_Config);
void MCAL_SPI_DeInit (SPI_TypeDef *SPIx);

void MCAL_SPI_Send_Data (SPI_TypeDef *SPIx, uint16_t *pTxBuffer, Polling_mechism PollingEn );
void MCAL_SPI_Send_String (SPI_TypeDef *SPIx, uint8_t * ptr_str , Polling_mechism PollingEn );

//void MCAL_SPI_Receive_Data (SPI_TypeDef *SPIx, uint16_t *pRxBuffer , Polling_mechism PollingEn );
uint16_t MCAL_SPI_Receive_Data (SPI_TypeDef *SPIx, uint16_t *pRxBuffer , Polling_mechism PollingEn );
void MCAL_SPI_TX_RX (SPI_TypeDef *SPIx, uint16_t *pBuffer, Polling_mechism PollingEn );

void MCAL_SPI_GPIO_Set_Pins (SPI_TypeDef *SPIx);

#endif /* STM32_F103C6_SPI_Driver_H_ */
