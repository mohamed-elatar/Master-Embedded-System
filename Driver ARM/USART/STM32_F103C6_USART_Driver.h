/***********************************************
 * @file           : STM32_F103C6_USART_Driver.h*
 * @author         : mohamed elatar             *
 * @Data           : November 11, 2023			*
 ************************************************/


#ifndef STM32_F103C6_USART_Driver_H_
#define STM32_F103C6_USART_Driver_H_

//-----------------------------
//Includes
//-----------------------------
#include "STM32_F103C6_GPIO_Driver.h"
#include "STM32_F103C6_RCC_Driver.h"


//-----------------------------
//Structure
//-----------------------------
typedef struct
{
	uint8_t 						USART_Mode;			// RX/TX Enable or Disable
														// Based on @ref_USART_Mode_Define

	uint32_t 						USART_BaudRate;		// Fractional baud rate generation
														// Based on @ref_USART_BaudRate_Define

	uint8_t							Data_Length;		// determines the word length
														// Based on @ref_USART_Data_Lenght_Define

	uint8_t							Parity;				// This bit selects the odd or even parity
														// Based on @ref_USART_Parity_Define

	uint8_t							StopBits;			// These bits are used for programming the stop bits
														// Based on @ref_USART_StopBits_Define

	uint8_t							HW_flow_control;	// hardware flow control mode is enabled or disabled [cts / rts]
														// Based on @ref_USART_FlowControl_Define

	uint8_t							IRQ_Enable;			// enable or disable USART interrupts Based on
														// @ref_USART_IRQ_Define

	void(*PF_IRQ_CallBack)(void);
}USART_Config;


//-----------------------------
//References Macros
//-----------------------------

// @ref_USART_Mode_Define
#define USART_MODE_RX				(uint32_t)(1<<2) // Bit2 RE: Receiver enable
#define USART_MODE_TX				(uint32_t)(1<<3) // Bit3 TE: Transmitter enable
#define USART_MODE_RX_TX			(uint32_t)(1<<2 | 1<<3)

//@ref_USART_BaudRate_Define
#define USART_BaudRate_2400                   2400
#define USART_BaudRate_9600                   9600
#define USART_BaudRate_19200                  19200
#define USART_BaudRate_57600                  57600
#define USART_BaudRate_115200                 115200
#define USART_BaudRate_230400                 230400
#define USART_BaudRate_460800                 460800
#define USART_BaudRate_921600                 921600
#define USART_BaudRate_2250000                2250000
#define USART_BaudRate_4500000                4500000

//@ref_USART_Data_Lenght_Define
#define USART_Data_Length_8B               (uint32_t)(0) // 0 at bit 12
#define USART_Data_Length_9B               (uint32_t)(1<<12) //Bit12 M Word length


//@ref_USART_Parity_Define
//Bit 10PCE: Parity control enable ==> 1: Parity control enabled
//Bit 9PS: Parity selection ==> 0: Even parity && 1: Odd parity
#define USART_Parity_NONE                    (uint32_t)(0)    // 0 at bit 9
#define USART_Parity_EVEN                    (uint32_t)(1<<10)
#define USART_Parity_ODD                     (uint32_t)(1<<10 | 1<<9)

//@ref_USART_StopBits_Define
//Bits 13:12STOP: STOP bits
//00: 1 Stop bit
//01: 0.5 Stop bit
//10: 2 Stop bits
//11: 1.5 Stop bit
//The 0.5 Stop bit and 1.5 Stop bit are not available for USART4 & USART5.
#define USART_StopBits_half                  (uint32_t)(1<<12)
#define USART_StopBits_1                     (uint32_t)(0)// 0 at bit 13:12
#define USART_StopBits_1_half                (uint32_t)(3<<12)
#define USART_StopBits_2                     (uint32_t)(2<<12)

//@ref_USART_FlowControl_Define
//Control register 3 (USART_CR3)
//Bit 9CTSE: CTS enable
//0: CTS hardware flow control disabled
//1: CTS mode enabled, data is only transmitted when the CTS input is asserted (tied to 0).
//Bit 8RTSE: RTS enable
//0: RTS hardware flow control disabled
//1: RTS interrupt enabled, data is only requested when there is space in the receive buffer.
#define USART_HwFlowCtl_NONE                  (uint32_t)(0)
#define USART_HwFlowCtl_RTS                   (uint32_t)(1<<8)
#define USART_HwFlowCtl_CTS                   (uint32_t)(1<<9)
#define USART_HwFlowCtl_RTS_CTS               ((uint32_t)(1<<8 | 1<<9))


//@ref_USART_IRQ_Define
#define USART_IRQ_Enable_NONE                 (uint32_t)(0)
#define USART_IRQ_Enable_TXE                  (uint32_t)(1<<7)  // Bit7 TXE : Transmit data register empty
#define USART_IRQ_Enable_TC                   (uint32_t)(1<<6)  // Bit6 TC  : Transmission complete
#define USART_IRQ_Enable_RXNEIE               (uint32_t)(1<<5)  // Bit5 RXNEIE: RXNE interrupt enable || Bit5 RXNE: Read data register not empty
#define USART_IRQ_Enable_PE                   (uint32_t)(1<<8)  // Bit8 PEIE: PE interrupt enable



// BaudRate Calculation
//USARTDIV = fclk / (16 * Baudrate)
//DIV_Mantissa = Integer Part (USARTDIV)
//DIV_Mantissa_MUL100 = Integer Part (USARTDIV ) * 100
//USARTDIV_MUL100 = ( (100 * fclk ) / (16 * Baudrate) ) ==> ( (25 * fclk ) / (4 * Baudrate) )
//DIV_Fraction = (( USARTDIV_MUL100 - DIV_Mantissa_MUL100 ) * 16 ) / 100

#define USARTDIV(_FCLK_, _BAUD_)							(uint32_t) (_FCLK_/(16 * _BAUD_ ))
#define Mantissa(_FCLK_, _BAUD_)							(uint32_t) (USARTDIV(_FCLK_, _BAUD_) )
#define USARTDIV_MUL100(_FCLK_, _BAUD_)						(uint32_t) ( (25 * _FCLK_ ) / (4  * _BAUD_ ))
#define Mantissa_MUL100(_FCLK_, _BAUD_)						(uint32_t) (Mantissa(_FCLK_, _BAUD_) * 100)
#define DIV_Fraction(_FCLK_, _BAUD_)						(uint32_t) (((USARTDIV_MUL100(_FCLK_, _BAUD_) -  Mantissa_MUL100(_FCLK_, _BAUD_) ) * 16 ) / 100 )

//Bits 15:4DIV_Mantissa[11:0]: mantissa of USARTDIV || Bits 3:0DIV_Fraction[3:0]: fraction of USARTDIV
#define USART_BRR_Register(_FCLK_, _BAUD_)					(( Mantissa (_FCLK_, _BAUD_) ) << 4 )|( (DIV_Fraction(_FCLK_, _BAUD_)) & 0xF )




/* ===============================================
 * 			APIs Supported by "MCAL USART DRIVER"
 * ===============================================
 */

void MCAL_USART_Init (USART_TypeDef * USARTx , USART_Config * USART_Config);
void MCAL_USART_DeInit (USART_TypeDef *USARTx);

void MCAL_USART_Send_Data (USART_TypeDef *USARTx, uint16_t *pTxBuffer, Polling_mechism PollingEn );
void MCAL_USART_Send_String (USART_TypeDef *USARTx, uint8_t * ptr_str , Polling_mechism PollingEn );
void MCAL_USART_WAIT_TC (USART_TypeDef *USARTx );

//void MCAL_USART_Receive_Data (USART_TypeDef *USARTx, uint16_t *pRxBuffer , Polling_mechism PollingEn );
uint16_t MCAL_USART_Receive_Data (USART_TypeDef *USARTx, uint16_t *pRxBuffer , Polling_mechism PollingEn );

void MCAL_USART_GPIO_Set_Pins (USART_TypeDef *USARTx);

#endif /* STM32_F103C6_USART_Driver_H_ */
