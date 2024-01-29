/***********************************************
 * @file           : STM32_F103X6.h 			*
 * @author         : mohamed elatar             *
 * @Data           : October 30, 2023			*
 ************************************************/

#ifndef INCLUDE_STM32_F103X6_H_
#define INCLUDE_STM32_F103X6_H_


//-----------------------------
//Includes
//-----------------------------

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "standard_macros.h"

//-----------------------------
//Base addresses for Memories
//-----------------------------

#define FLASH_Base								0x08000000ul
#define SRAM_Base								0x20000000ul
#define System_Memory_Base						0x1FFFF000ul
#define Peripheral_Base							0x40000000ul
#define Cortex_M3_Internal_Peripheral_Base		0xE0000000ul
#define NVIC_BASE								0xE000E100UL


//-----------------------------
//Base addresses for NVIC Peripherals
//-----------------------------

//Interrupt set-enable registers
#define NVIC_ISER0								*((volatile uint32_t *)(NVIC_BASE + 0x000))
#define NVIC_ISER1								*((volatile uint32_t *)(NVIC_BASE + 0x004))
#define NVIC_ISER2								*((volatile uint32_t *)(NVIC_BASE + 0x008))
//Interrupt clear-enable registers
#define NVIC_ICER0								*((volatile uint32_t *)(NVIC_BASE + 0x080))
#define NVIC_ICER1								*((volatile uint32_t *)(NVIC_BASE + 0x084))
#define NVIC_ICER2								*((volatile uint32_t *)(NVIC_BASE + 0x088))

//-----------------------------
//Base addresses for AHB Peripherals
//-----------------------------
#define RCC_Base								0x40021000ul

//-----------------------------
//Base addresses for APB1 Peripherals
//-----------------------------

#define USART2_Base								0x40004400ul
#define USART3_Base								0x40004800ul

#define SPI2_Base								0x40003800ul

#define I2C1_Base								0x40005400ul
#define I2C2_Base								0x40005800ul

//-----------------------------
//Base addresses for APB2 Peripherals
//-----------------------------

//GPIO
//A,B Fully Include In LQFP48 Package
#define GPIOA_Base								0x40010800ul
#define GPIOB_Base								0x40010C00ul
//C,D Partial Include In LQFP48 Package
#define GPIOC_Base								0x40011000ul
#define GPIOD_Base								0x40011400ul
//E Not Include In LQFP48 Package
#define GPIOE_Base								0x40011800ul

#define AFIO_Base 								0x40010000ul
#define EXTI_Base								0x40010400ul

#define USART1_Base								0x40013800ul

#define SPI1_Base								0x40013000ul
//----------------------------------------------------------------------------

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: RCC
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct
{
	volatile uint32_t RCC_CR;  			//Clock control register
	volatile uint32_t RCC_CFGR;  		//Clock configuration register
	volatile uint32_t RCC_CIR;  		//Clock interrupt register
	volatile uint32_t RCC_APB2RSTR;  	//APB2 peripheral reset register
	volatile uint32_t RCC_APB1RSTR; 	//APB1 peripheral reset register
	volatile uint32_t RCC_AHBENR;  		//AHB Peripheral Clock enable register
	volatile uint32_t RCC_APB2ENR; 		//APB2 peripheral clock enable register
	volatile uint32_t RCC_APB1ENR;		//APB1 peripheral clock enable register
	volatile uint32_t RCC_BDCR;			//Backup domain control register
	volatile uint32_t RCC_CSR;			//Control/status register
	volatile uint32_t RCC_AHBRSTR;		//AHB peripheral clock reset register
	volatile uint32_t RCC_CFGR2;		//Clock configuration register2
	//
}RCC_TypeDef;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants:RCC
//-*-*-*-*-*-*-*-*-*-*-*
#define RCC						((RCC_TypeDef*) RCC_Base)

//-*-*-*-*-*-*-*-*-*-*-*-
//clock enable Macros:
//-*-*-*-*-*-*-*-*-*-*-*
#define RCC_AFIO_CLK_EN()		( SET_BIT(RCC->RCC_APB2ENR , 0) )

#define RCC_GPIOA_CLK_EN()		( SET_BIT(RCC->RCC_APB2ENR , 2) )
#define RCC_GPIOB_CLK_EN()		( SET_BIT(RCC->RCC_APB2ENR , 3) )
#define RCC_GPIOC_CLK_EN()		( SET_BIT(RCC->RCC_APB2ENR , 4) )
#define RCC_GPIOD_CLK_EN()		( SET_BIT(RCC->RCC_APB2ENR , 5) )
#define RCC_GPIOE_CLK_EN()		( SET_BIT(RCC->RCC_APB2ENR , 6) )

#define RCC_USART1_CLK_EN()		( SET_BIT(RCC->RCC_APB2ENR , 14) )
#define RCC_USART2_CLK_EN()		( SET_BIT(RCC->RCC_APB1ENR , 17) )
#define RCC_USART3_CLK_EN()		( SET_BIT(RCC->RCC_APB1ENR , 18) )

#define RCC_USART1_CLK_Reset()	( SET_BIT(RCC->RCC_APB2RSTR , 14) )
#define RCC_USART2_CLK_Reset()	( SET_BIT(RCC->RCC_APB1RSTR , 17) )
#define RCC_USART3_CLK_Reset()	( SET_BIT(RCC->RCC_APB1RSTR , 18) )

#define RCC_SPI1_CLK_EN()		( SET_BIT(RCC->RCC_APB2ENR , 12) )
#define RCC_SPI2_CLK_EN()		( SET_BIT(RCC->RCC_APB1ENR , 14) )

#define RCC_SPI1_CLK_Reset()	( SET_BIT(RCC->RCC_APB2RSTR , 12) )
#define RCC_SPI2_CLK_Reset()	( SET_BIT(RCC->RCC_APB1RSTR , 14) )

#define RCC_I2C1_CLK_EN()		( SET_BIT(RCC->RCC_APB1ENR , 21) )
#define RCC_I2C2_CLK_EN()		( SET_BIT(RCC->RCC_APB1ENR , 22) )

#define RCC_I2C1_CLK_Reset()	( SET_BIT(RCC->RCC_APB1RSTR , 21) )
#define RCC_I2C2_CLK_Reset()	( SET_BIT(RCC->RCC_APB1RSTR , 22) )

//----------------------------------------------------------------------------//

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: GPIO
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct
{
	volatile uint32_t CRL;  	//configuration register low
	volatile uint32_t CRH;  	//configuration register high
	volatile uint32_t IDR;  	//input data register
	volatile uint32_t ODR;  	//output data register
	volatile uint32_t BSRR; 	//set/reset register
	volatile uint32_t BRR;  	//reset register
	volatile uint32_t LCKR; 	//configuration lock register
}GPIO_TypeDef;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants: GPIO
//-*-*-*-*-*-*-*-*-*-*-*
#define GPIOA					((GPIO_TypeDef*) GPIOA_Base)
#define GPIOB					((GPIO_TypeDef*) GPIOB_Base)
#define GPIOC					((GPIO_TypeDef*) GPIOC_Base)
#define GPIOD					((GPIO_TypeDef*) GPIOD_Base)
#define GPIOE					((GPIO_TypeDef*) GPIOE_Base)

//----------------------------------------------------------------------------//


//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: AFIO
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct
{
	volatile uint32_t EVCR;  	//event control register
	volatile uint32_t MAPR;  	//remap and debug I/O configuration register
	volatile uint32_t EXTICR[4];
	//	volatile uint32_t EXTICR1;  //External interrupt configuration register 1
	//	volatile uint32_t EXTICR2;  //External interrupt configuration register 2
	//	volatile uint32_t EXTICR3; 	//External interrupt configuration register 3
	//	volatile uint32_t EXTICR4;  //External interrupt configuration register 4
	volatile uint32_t Reserved;
	volatile uint32_t MAPR2; 	//remap and debug I/O configuration register2
}AFIO_TypeDef;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants:AFIO
//-*-*-*-*-*-*-*-*-*-*-*
#define AFIO					((AFIO_TypeDef*) AFIO_Base)


//----------------------------------------------------------------------------//

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: USART
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct
{
	volatile uint32_t USART_SR;		//Status register
	volatile uint32_t USART_DR;		//Data register
	volatile uint32_t USART_BRR;	//Baud rate register
	volatile uint32_t USART_CR1;	//Control register 1
	volatile uint32_t USART_CR2;	//Control register 2
	volatile uint32_t USART_CR3;  	//Control register 3
	volatile uint32_t USART_GTPR;  	//Guard time and prescaler register
}USART_TypeDef;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants:USART
//-*-*-*-*-*-*-*-*-*-*-*
#define USART1					((USART_TypeDef*) USART1_Base)
#define USART2					((USART_TypeDef*) USART2_Base)
#define USART3					((USART_TypeDef*) USART3_Base)

//----------------------------------------------------------------------------//

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: SPI
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct
{
	volatile uint32_t SPI_CR1;		//SPI control register 1
	volatile uint32_t SPI_CR2;		//SPI control register 2
	volatile uint32_t SPI_SR;		//SPI status register
	volatile uint32_t SPI_DR;		//SPI data register
	volatile uint32_t SPI_CRCPR;	//SPI CRC polynomial register
	volatile uint32_t SPI_RXCRCR;  	//SPI RX CRC register
	volatile uint32_t SPI_TXCRCR;  	//SPI TX CRC register
	volatile uint32_t SPI_I2SCFGR;  //SPI TX CRC register
	volatile uint32_t SPI_I2SPR;  	//SPI_I2S prescaler register
}SPI_TypeDef;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants:USART
//-*-*-*-*-*-*-*-*-*-*-*
#define SPI1					((SPI_TypeDef*) SPI1_Base)
#define SPI2					((SPI_TypeDef*) SPI2_Base)

//----------------------------------------------------------------------------//

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: I2C
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct
{
	volatile uint32_t I2C_CR1;		//Control register 1
	volatile uint32_t I2C_CR2;		//Control register 2
	volatile uint32_t I2C_OAR1;		//Own address register 1
	volatile uint32_t I2C_OAR2;		//Own address register 2
	volatile uint32_t I2C_DR;		//Data register
	volatile uint32_t I2C_SR1;  	//Status register 1
	volatile uint32_t I2C_SR2;  	//Status register 2
	volatile uint32_t I2C_CCR;  	//Clock control register
	volatile uint32_t I2C_TRISE;  	//TRISE register
}I2C_TypeDef;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants:I2C
//-*-*-*-*-*-*-*-*-*-*-*
#define I2C1					((I2C_TypeDef*) I2C1_Base)
#define I2C2					((I2C_TypeDef*) I2C2_Base)

//----------------------------------------------------------------------------//

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: EXTI
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct
{
	volatile uint32_t IMR;		//Interrupt mask register
	volatile uint32_t EMR;		//Event mask register
	volatile uint32_t RTSR;		//Rising trigger selection register
	volatile uint32_t FTSR;		//Falling trigger selection register
	volatile uint32_t SWIER;	//Software interrupt event register
	volatile uint32_t PR;  		//Pending register
}EXTI_TypeDef;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants:EXTI
//-*-*-*-*-*-*-*-*-*-*-*
#define EXTI					((EXTI_TypeDef*) EXTI_Base)

//-*-*-*-*-*-*-*-*-*-*-*-
//IVT numbers:
//-*-*-*-*-*-*-*-*-*-*-*
#define EXTI0_IRQ									6
#define EXTI1_IRQ									7
#define EXTI2_IRQ									8
#define EXTI3_IRQ									9
#define EXTI4_IRQ									10
/* EXTI9_5 --> 23 */
#define EXTI5_IRQ									23
#define EXTI6_IRQ									23
#define EXTI7_IRQ									23
#define EXTI8_IRQ									23
#define EXTI9_IRQ									23
/* EXTI15_10 --> 40 */
#define EXTI10_IRQ									40
#define EXTI11_IRQ									40
#define EXTI12_IRQ									40
#define EXTI13_IRQ									40
#define EXTI14_IRQ									40
#define EXTI15_IRQ									40

/* EXTI USART --> 37:39 */
#define USART1_IRQ									37
#define USART2_IRQ									38
#define USART3_IRQ									39

/* EXTI SPI --> 35:36 */
#define SPI1_IRQ									35
#define SPI2_IRQ									36

/* EXTI SPI --> 31:34 */
#define I2C1_EV_IRQ									31
#define I2C1_ER_IRQ									32
#define I2C2_EV_IRQ									33
#define I2C2_ER_IRQ									34


//-*-*-*-*-*-*-*-*-*-*-*-
//NVIC enable Macros:
//-*-*-*-*-*-*-*-*-*-*-*

//GPIO
#define NVIC_EXTI0_IRQ_ENABLE()						SET_BIT(NVIC_ISER0,EXTI0_IRQ);
#define NVIC_EXTI1_IRQ_ENABLE()						SET_BIT(NVIC_ISER0,EXTI1_IRQ);
#define NVIC_EXTI2_IRQ_ENABLE()						SET_BIT(NVIC_ISER0,EXTI2_IRQ);
#define NVIC_EXTI3_IRQ_ENABLE()						SET_BIT(NVIC_ISER0,EXTI3_IRQ);
#define NVIC_EXTI4_IRQ_ENABLE()						SET_BIT(NVIC_ISER0,EXTI4_IRQ);
#define NVIC_EXTI9_5_IRQ_ENABLE()					SET_BIT(NVIC_ISER0,EXTI5_IRQ);
#define NVIC_EXTI15_10_IRQ_ENABLE()					SET_BIT(NVIC_ISER1,(EXTI10_IRQ-32)); // NVIC_ISER1 began Interrupts[32 : 63]

//USART
#define NVIC_EXTI37_USART1_ENABLE()					SET_BIT(NVIC_ISER1,(USART1_IRQ-32)); // NVIC_ISER1 began Interrupts[32 : 63]
#define NVIC_EXTI38_USART2_ENABLE()					SET_BIT(NVIC_ISER1,(USART2_IRQ-32));
#define NVIC_EXTI39_USART3_ENABLE()					SET_BIT(NVIC_ISER1,(USART3_IRQ-32));


//SPI
#define NVIC_EXTI35_SPI1_ENABLE()					SET_BIT(NVIC_ISER1,(SPI1_IRQ-32)); // NVIC_ISER1 began Interrupts[32 : 63]
#define NVIC_EXTI36_SPI2_ENABLE()					SET_BIT(NVIC_ISER1,(SPI2_IRQ-32));


//I2C
#define NVIC_EXTI31_I2C1_EV_IRQ_ENABLE()			SET_BIT(NVIC_ISER0,(I2C1_EV_IRQ)); 		// NVIC_ISER0 began Interrupts[0 : 31]
#define NVIC_EXTI32_I2C1_ER_IRQ_ENABLE()			SET_BIT(NVIC_ISER1,(I2C1_ER_IRQ-32)); 	// NVIC_ISER1 began Interrupts[32 : 63]
#define NVIC_EXTI33_I2C2_EV_IRQ_ENABLE()			SET_BIT(NVIC_ISER1,(I2C2_EV_IRQ-32));
#define NVIC_EXTI34_I2C2_ER_IRQ_ENABLE()			SET_BIT(NVIC_ISER1,(I2C2_ER_IRQ-32));
//-*-*-*-*-*-*-*-*-*-*-*-
//NVIC disable Macros:
//-*-*-*-*-*-*-*-*-*-*-*

//GPIO
#define NVIC_EXTI0_IRQ_DISABLE()					SET_BIT(NVIC_ICER0,EXTI0_IRQ);
#define NVIC_EXTI1_IRQ_DISABLE()					SET_BIT(NVIC_ICER0,EXTI1_IRQ);
#define NVIC_EXTI2_IRQ_DISABLE()					SET_BIT(NVIC_ICER0,EXTI2_IRQ);
#define NVIC_EXTI3_IRQ_DISABLE()					SET_BIT(NVIC_ICER0,EXTI3_IRQ);
#define NVIC_EXTI4_IRQ_DISABLE()					SET_BIT(NVIC_ICER0,EXTI4_IRQ);
#define NVIC_EXTI9_5_IRQ_DISABLE()					SET_BIT(NVIC_ICER0,EXTI5_IRQ);
#define NVIC_EXTI15_10_IRQ_DISABLE()				SET_BIT(NVIC_ICER1,(EXTI10_IRQ-32)); // NVIC_ISER1 began Interrupts[32 : 63]

//USART
#define NVIC_EXTI37_USART1_DISABLE()				SET_BIT(NVIC_ICER1,(USART1_IRQ-32)); // NVIC_ISER1 began Interrupts[32 : 63]
#define NVIC_EXTI38_USART2_DISABLE()				SET_BIT(NVIC_ICER1,(USART2_IRQ-32));
#define NVIC_EXTI39_USART3_DISABLE()				SET_BIT(NVIC_ICER1,(USART3_IRQ-32));

//SPI
#define NVIC_EXTI35_SPI1_DISABLE()					SET_BIT(NVIC_ICER1,(SPI1_IRQ-32)); // NVIC_ISER1 began Interrupts[32 : 63]
#define NVIC_EXTI36_SPI2_DISABLE()					SET_BIT(NVIC_ICER1,(SPI2_IRQ-32));

//I2C
#define NVIC_EXTI31_I2C1_EV_IRQ_DISABLE()			SET_BIT(NVIC_ICER0,(I2C1_EV_IRQ)); // NVIC_ICER0 began Interrupts[0 : 31]
#define NVIC_EXTI32_I2C1_ER_IRQ_DISABLE()			SET_BIT(NVIC_ICER1,(I2C1_ER_IRQ-32)); // NVIC_ICER1 began Interrupts[32 : 63]
#define NVIC_EXTI33_I2C2_EV_IRQ_DISABLE()			SET_BIT(NVIC_ICER1,(I2C2_EV_IRQ-32));
#define NVIC_EXTI34_I2C2_ER_IRQ_DISABLE()			SET_BIT(NVIC_ICER1,(I2C2_ER_IRQ-32));


//-*-*-*-*-*-*-*-*-*-*-*-
//Generic Macros: Delay
//-*-*-*-*-*-*-*-*-*-*-*
#define _delay_ms( time )		for(uint32_t i=0 ; i<time ; ++i) \
		{\
	for(uint32_t j=0 ; j<255 ; ++j); \
		}

typedef enum
{
	enable ,
	disable
}Polling_mechism;

#endif /* INCLUDE_STM32_F103X6_H_ */
