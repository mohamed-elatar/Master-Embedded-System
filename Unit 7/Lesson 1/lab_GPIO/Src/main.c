/**
 ******************************************************************************
 * @file           : main.c
 * @author         : mohamed elatar
 * @brief          : Main program body
 ******************************************************************************/
#include <stdint.h>
typedef volatile unsigned int vuint32_t ;

#define SET_BIT(reg , num)	(reg |= (1<<num))
#define CLR_BIT(reg , num)	(reg &= ~(1<<num))
#define TOG_BIT(reg , num)	(reg ^= (1<<num))
#define RED_BIT(reg , num)	( (reg & (1ul<<num))>>num )

// register address DIOA
#define GPIOA_BASE 		0x40010800
#define GPIOA_CRL 		*(volatile uint32_t *)(GPIOA_BASE + 0x00)
#define GPIOA_CRH 		*(volatile uint32_t *)(GPIOA_BASE + 0x04)
#define GPIOA_ODR 		*(volatile uint32_t *)(GPIOA_BASE + 0x0C)
#define GPIOA_IDR 		*(volatile uint32_t *)(GPIOA_BASE + 0x08)

// register address DIOB
#define GPIOB_BASE 		0x40010C00
#define GPIOB_CRL 		*(volatile uint32_t *)(GPIOB_BASE + 0x00)
#define GPIOB_CRH 		*(volatile uint32_t *)(GPIOB_BASE + 0x04)
#define GPIOB_ODR 		*(volatile uint32_t *)(GPIOB_BASE + 0x0C)
#define GPIOB_IDR 		*(volatile uint32_t *)(GPIOA_BASE + 0x08)


// Reset and Clock Control & (APB2 peripheral enable) register
#define RCC_BASE 		0X40021000
#define RCC_APB2ENR 	*(volatile uint32_t *)(RCC_BASE + 0x18)


void init_CLOCK()
{
	//Bit_2 IOPAEN: I/O port A clock enable (1 : I/O port A clock enabled)
	SET_BIT(RCC_APB2ENR , 2);

	//Bit_3 IOPBEN: I/O port B clock enable (1 : I/O port B clock enabled)
	SET_BIT(RCC_APB2ENR , 3);
}


void init_GPIO()
{
	// all input pins A [0:15] configuration is analog mode
	GPIOA_CRL = 0x0;
	GPIOA_CRH = 0x0;

	// PA1 I/P
	GPIOA_CRL &= ~(0b11 << 4); // MODE : 00: Input mode (reset state)
	GPIOA_CRL |= (0b01 << 6);  // CNF  : 01: Floating input (input Mode)

	// PA13 I/P
	GPIOA_CRH &= ~(0b11 << 20); // MODE : 00: Input mode (reset state)
	GPIOA_CRH |= (0b01 << 22);  // CNF  : 01: Floating input (input Mode)


	// all input pins [0:7] configuration is analog mode
	GPIOB_CRL = 0x0;
	GPIOB_CRH = 0x0;

	// PB1 O/P
	GPIOB_CRL |= (0b01 << 4);  // MODE : 01: Output mode, max speed 10 MHz.
	GPIOB_CRL &= ~(0b11 << 6); // CNF : 00: General purpose output push-pull


	// PB13 O/P
	GPIOB_CRH |= (0b01 << 20);  // MODE : 01: Output mode, max speed 10 MHz.
	GPIOB_CRH &= ~(0b01 << 22); // CNF : 00: General purpose output push-pull
}



int main()
{
	init_CLOCK();
	init_GPIO();

	//super loop
	while(1)
	{
		// pull up single press
		if( RED_BIT(GPIOA_IDR , 1) == 0 )
		{
			TOG_BIT(GPIOB_ODR , 1);
			while( RED_BIT(GPIOA_IDR , 1) == 0 );
		}

		// pull down multiple press
		if( RED_BIT(GPIOA_IDR , 13) == 1 )
		{
			TOG_BIT(GPIOB_ODR , 13);
		}

		for (int i = 0 ; i < 10000 ; ++i);
	}
}

