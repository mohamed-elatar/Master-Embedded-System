/***********************************************
 * @file           : STM32_F103C6_RCC_Driver.h *
 * @author         : mohamed elatar             *
 * @Data           : November 11, 2023			*
 ************************************************/


#ifndef STM32_F103C6_RCC_Driver_H_
#define STM32_F103C6_RCC_Driver_H_

//-----------------------------
//Includes
//-----------------------------
#include "STM32_F103C6_GPIO_Driver.h"


//-----------------------------
//Macros
//-----------------------------
#define HSI_RC_CLK			(uint32_t)8000000
#define HSE_CLK 			(uint32_t)16000000
#define PLL_CLK				(uint32_t)16000000

/* ===============================================
 * 			APIs Supported by "MCAL RCC DRIVER"
 * ===============================================
 */
uint32_t MCAL_RCC_GET_SYS_CLK_Freq(void);
uint32_t MCAL_RCC_GET_HCLK_Freq(void);
uint32_t MCAL_RCC_GET_PCLK1_Freq(void);
uint32_t MCAL_RCC_GET_PCLK2_Freq(void);

#endif /* STM32_F103C6_RCC_Driver_H_ */
