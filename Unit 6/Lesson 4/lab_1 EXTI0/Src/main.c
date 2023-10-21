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
#define GPIOA_CRL 		*(volatile uint32_t *)(GPIOA_BASE + 0x00)
#define GPIOA_CRH 		*(volatile uint32_t *)(GPIOA_BASE + 0x04)
#define GPIOA_ODR 		*(volatile uint32_t *)(GPIOA_BASE + 0x0C)

// Alternate function I/O
#define AFIO_BASE		0x40010000
#define AFIO_EXTICR1	*(volatile uint32_t *)(AFIO_BASE + 0x08)

// Reset and Clock Control & (APB2 peripheral enable) register
#define RCC_BASE 		0X40021000
#define RCC_APB2ENR 	*(volatile uint32_t *)(RCC_BASE + 0x18)


#define EXTI_BASE 		0x40010400 										//External interrupt/event controller
#define EXTI_IMR		*(volatile uint32_t *)(EXTI_BASE + 0x00) 		//Interrupt mask register
#define EXTI_RTSR		*(volatile uint32_t *)(EXTI_BASE + 0x08) 		//Rising trigger selection
#define EXTI_PR 		*(volatile uint32_t *)(EXTI_BASE + 0x14) 		//Pending register

#define EXTIE0_NVIC		*(volatile uint32_t *)(0xE000E100)				//enable NVIC line 0

#define SET_BIT(reg , num)	(reg |= (1<<num))
#define CLR_BIT(reg , num)	(reg &= ~(1<<num))
#define TOG_BIT(reg , num)	(reg ^= (1<<num))

void init_GPIO()
{
	//Initialize GPIOA
	GPIOA_CRH &= 0xFF0FFFFF;
	GPIOA_CRH |= 0x00200000;

	//pin A0: Floating input (reset state)
	SET_BIT(GPIOA_CRL , 2);

}

void init_CLOCK()
{
	//Bit_0 AFIOEN: Alternate function I/O clock enable (1)
	SET_BIT(RCC_APB2ENR , 0);

	//Bit_2 IOPAEN: I/O port A clock enable (1)
	SET_BIT(RCC_APB2ENR , 2);
}

int main()
{
	init_CLOCK();
	init_GPIO();

	//select the source input for EXTI0 external --> interrupt 0000: PA[0] pin --> default is zero
	CLR_BIT(AFIO_EXTICR1 , 0);

	//selected trigger rising request occurred (1)
	SET_BIT(EXTI_RTSR , 0);

	//Interrupt Mask on line 0
	SET_BIT(EXTI_IMR , 0);

	//enable IRQ NVIC EXTI0
	SET_BIT(EXTIE0_NVIC , 6);

	//super loop
	while(1);
}

void EXTI0_IRQHandler(void)
{
	// toggle led pin 13 port_a rising edge
	TOG_BIT(GPIOA_ODR , 13);

	// clear pending for line 0 to avoid overhead IRQ
	SET_BIT(EXTI_PR , 0);
}
