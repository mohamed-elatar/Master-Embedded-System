/***********************************************
 * @file           : STM32_F103C6_RCC_Driver.c 	*
 * @author         : mohamed elatar             *
 * @Data           : November 11, 2023			*
 ************************************************/

//-----------------------------
//Includes
//-----------------------------
#include "STM32_F103C6_RCC_Driver.h"


//Bits 10:8PPRE1[2:0]: APB Low-speed prescaler (APB1) (APB2)
//Set and cleared by software to control the division factor of the APB Low speed clock (PCLK1).
//0xx: HCLK not divided
//100: HCLK divided by 2
//101: HCLK divided by 4
//110: HCLK divided by 8
//111: HCLK divided by 16
const uint8_t APBPrescaler_Table[8] = {0 , 0 , 0 , 0 , 1 , 2 , 3 , 4}; // for shift right == multiply by 2^num = [2,4,8,16]


//Bits 7:4HPRE[3:0]: AHB prescaler
//Set and cleared by software to control AHB clock division factor.
//0xxx: SYSCLK not divided
//1000: SYSCLK divided by 2
//1001: SYSCLK divided by 4
//1010: SYSCLK divided by 8
//1011: SYSCLK divided by 16
//1100: SYSCLK divided by 64
//1101: SYSCLK divided by 128
//1110: SYSCLK divided by 256
//1111: SYSCLK divided by 512
const uint8_t AHBPrescaler_Table[16] = {0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 2 , 3 , 4  , 6 , 7 , 8 , 9}; // for shift right == multiply by 2^num = [2,4,8,16,64,128,265,512]



uint32_t MCAL_RCC_GET_SYS_CLK_Freq(void)
{
	uint32_t ret_val;
	//	Bits 3:2SWS[1:0]: System clock switch status
	//	Set and cleared by hardware toindicate which clock source is used as system clock.
	//	00: HSI oscillator used as system clock
	//	01: HSE oscillator used as system clock
	//	10: PLL used as system clock
	//	11: Not applicable
	switch( (RCC->RCC_CFGR >> 2) & 0x3 ) // 0x3 is mask
	{
	case 0:
		ret_val = HSI_RC_CLK;
		break;

	case 1:
		ret_val = HSE_CLK;
		break;

	case 2:
		ret_val = PLL_CLK;
		break;
	}
	return ret_val;
}
uint32_t MCAL_RCC_GET_HCLK_Freq(void)
{
	// Bits 7:4HPRE[3:0]: AHB prescaler
	return ( MCAL_RCC_GET_SYS_CLK_Freq() >> AHBPrescaler_Table[ (RCC->RCC_CFGR >> 4) & 0xF ] ); // 0xF is mask
}
uint32_t MCAL_RCC_GET_PCLK1_Freq(void)
{
	// Bits 10:8PPRE1[2:0]: APB Low-speed prescaler (APB1
	return ( MCAL_RCC_GET_HCLK_Freq() >> APBPrescaler_Table[ (RCC->RCC_CFGR >> 8) & 0x7 ] ); // 0x7 is mask
}
uint32_t MCAL_RCC_GET_PCLK2_Freq(void)
{
	// Bits 13:11PPRE2[2:0]: APB high-speed prescaler (APB2)
	return ( MCAL_RCC_GET_HCLK_Freq() >> APBPrescaler_Table[ (RCC->RCC_CFGR >> 11) & 0x7 ] ); // 0x7 is mask
}

