/**
 ******************************************************************************
 * @file           : main.c
 * @author         : mohamed elatar
 * @brief          : Main program body
 ******************************************************************************/
#include <stdint.h>
typedef volatile unsigned int vuint32_t ;

// register address DIOA
#define GPIOA_BASE 		0x40010800
#define GPIOA_CRH 		*(volatile uint32_t *)(GPIOA_BASE + 0x04)
#define GPIOA_ODR 		*(volatile uint32_t *)(GPIOA_BASE + 0x0C)

// Reset and Clock Control & (Clock & configuration & APB2 peripheral enable) register
#define RCC_BASE 		0X40021000
#define RCC_CFGR		*(volatile uint32_t *)(RCC_BASE + 0x04)
#define RCC_APB2ENR 	*(volatile uint32_t *)(RCC_BASE + 0x18)

int main(void)
{
	// Bits 7:4 HPRE : AHB prescaler --> (0xxx: SYSCLK not divided) 8MHZ
	RCC_CFGR |= (0b0000 << 4);

	// Bits 10:8 PPRE1 : APB1 low-speed prescaler --> (100: HCLK divided by 2) 4MHZ
	RCC_CFGR |= (0b100 << 8);

	// Bits 13:11 PPRE2 : APB2 high-speed prescaler --> (101: HCLK divided by 4) 2MHZ
	RCC_CFGR |= (0b101 << 11);

	// Enable Peripheral Bus to I\O GPIOA
	RCC_APB2ENR |= (1<<2);

	//Initialize GPIOA
	GPIOA_CRH &= 0xFF0FFFFF;
	GPIOA_CRH |= 0x00200000;
	while(1)
	{
		GPIOA_ODR |= 1<<13 ;
		for (int i = 0; i < 5000; i++); // arbitrary delay
		GPIOA_ODR &= ~(1<<13) ;
		for (int i = 0; i < 5000; i++); // arbitrary delay
	}
}
