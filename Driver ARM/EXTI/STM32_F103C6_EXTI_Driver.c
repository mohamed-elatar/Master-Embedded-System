/***********************************************
 * @file           : STM32_F103C6_EXTI_Driver.c *
 * @author         : mohamed elatar             *
 * @Data           : November 11, 2023			*
 ************************************************/

//-----------------------------
//Includes
//-----------------------------
#include "STM32_F103C6_EXTI_Driver.h"


//-----------------------------
//Prototype
//-----------------------------
static void Enable_NVIC(uint8_t input_line_number);
static void Disable_NVIC(uint8_t input_line_number);

//==========================================================================================
// 									Generic Variables
//==========================================================================================

void (*GP_IRQ_CallBack[15])(void);// array of pointers (15) : each pointer is pointer the ISR function

//==========================================================================================
// 									Generic Macros
//==========================================================================================

/*@ref AFIO_GPIO_EXTI_Mapping
0000: PA[x] pin
0001: PB[x] pin
0010: PC[x] pin
0011: PD[x] pin
*/
#define AFIO_GPIO_EXTI_Mapping(x)		((x == GPIOA)? 0 : \
										(x == GPIOB)? 1 : \
										(x == GPIOC)? 2 : \
										(x == GPIOD)? 3 : 0 )



/*=========================================================================================================
 * @Fn			: Updata_EXTI
 * @brief		: update configuration interrupt with specific ( pin_port , num_IQR , callback , enable or not )
 * @param [in]	: Pointers to structure
 * @retval		: none
 *=========================================================================================================*/

void Updata_EXTI(EXTI_Pin_Configure_t * EXTI_CFG)
{
	// (1) :  Configure GPIO PIN as floating input
	GPIO_Pin_Configure_t PIN;
	PIN.GPIO_Pin_Number = EXTI_CFG->EXTI_Pin.GPIO_Pin;
	PIN.GPIO_Mode = GPIO_MODE_INPUT_FLOATING;
	MCAL_GPIO_Pin_Init( EXTI_CFG->EXTI_Pin.GPIO_Port , &PIN);


	// (2) : Choose the pin as AFIO will connect with pin_port (A || B || C || D)
	uint8_t AFIO_EXTICR_index = (EXTI_CFG->EXTI_Pin.EXTI_Input_Line_Number / 4); 			// index 	{ 0, 1, 2, 3 }
	uint8_t AFIO_EXTICR_position = ((EXTI_CFG->EXTI_Pin.EXTI_Input_Line_Number % 4) * 4);	// Position { 0, 4, 8, 12}

	//clear the 4 bits first
	CLR_NIBBLE( AFIO->EXTICR[AFIO_EXTICR_index] , AFIO_EXTICR_position);

	//write the values on the 4 bits according to @ref AFIO_GPIO_EXTI_Mapping to select pin [PA , PB , PC , PD]
	AFIO->EXTICR[AFIO_EXTICR_index] |= ((AFIO_GPIO_EXTI_Mapping(EXTI_CFG->EXTI_Pin.GPIO_Port) & 0xF) << AFIO_EXTICR_position);


	// (3) : Choose the trigger case
	CLR_BIT( EXTI->RTSR , EXTI_CFG->EXTI_Pin.EXTI_Input_Line_Number ); // clear this bit first
	CLR_BIT( EXTI->FTSR , EXTI_CFG->EXTI_Pin.EXTI_Input_Line_Number ); // clear this bit first
	// detect select trigger
	if(EXTI_CFG->Trigger_Case == EXTI_Trigger_Raising)
	{
		SET_BIT( EXTI->RTSR , EXTI_CFG->EXTI_Pin.EXTI_Input_Line_Number);
	}
	else if( EXTI_CFG->Trigger_Case == EXTI_Trigger_Failing)
	{
		SET_BIT( EXTI->FTSR , EXTI_CFG->EXTI_Pin.EXTI_Input_Line_Number );
	}
	else if(EXTI_CFG->Trigger_Case == EXTI_Trigger_Raising_And_Failing )
	{
		SET_BIT( EXTI->RTSR , EXTI_CFG->EXTI_Pin.EXTI_Input_Line_Number);
		SET_BIT( EXTI->FTSR , EXTI_CFG->EXTI_Pin.EXTI_Input_Line_Number);
	}


	// (4) : Update IRQ Handling CALLBACK (pointer to function)
	GP_IRQ_CallBack[EXTI_CFG->EXTI_Pin.EXTI_Input_Line_Number] = EXTI_CFG->PF_IRQ_CallBack;


	// (5) : Enable or Disable IRQ
	if( EXTI_CFG->IRQ_EN == EXTI_IRQ_ENABLE )
	{
		// enable pin in  mask register
		SET_BIT( EXTI->IMR , EXTI_CFG->EXTI_Pin.EXTI_Input_Line_Number );

		// interrupt set enable register (NVIC_ISER) at NVIC
		Enable_NVIC( EXTI_CFG->EXTI_Pin.EXTI_Input_Line_Number );
	}
	else if( EXTI_CFG->IRQ_EN == EXTI_IRQ_DISABLE )
	{
		// mask register
		CLR_BIT( EXTI->IMR , EXTI_CFG->EXTI_Pin.EXTI_Input_Line_Number );

		// interrupt clear enable register (NVIC_ICER) at NVIC
		Disable_NVIC( EXTI_CFG->EXTI_Pin.EXTI_Input_Line_Number );
	}
}

/*=========================================================================================================
 * @Fn			: MCAL_EXTI_GPIO_Init
 * @brief		: to initialize Specific EXTI pin
 * @param [in]	: Pointers to structure
 * @retval		: none
 *=========================================================================================================*/
void MCAL_EXTI_GPIO_Init(EXTI_Pin_Configure_t * EXTI_CFG)
{
	Updata_EXTI(EXTI_CFG);
}

/*=========================================================================================================
 * @Fn			: MCAL_EXTI_GPIO_Update
 * @brief		: to update initialize Specific EXTI pin
 * @param [in]	: Pointers to structure
 * @retval		: none
 *=========================================================================================================*/
void MCAL_EXTI_GPIO_Update(EXTI_Pin_Configure_t *EXTI_CFG)
{
	Updata_EXTI(EXTI_CFG);
}

/*=========================================================================================================
 * @Fn			: MCAL_EXTI_GPIO_DeInit
 * @brief		: reset all EXTI Register
 * @param [in]	: none
 * @retval		: none
 *=========================================================================================================*/
void MCAL_EXTI_GPIO_DeInit(void)
{
	// return register to default value
	CLR_4BYTE( EXTI->IMR   );// Reset value: 0x00000000
	CLR_4BYTE( EXTI->EMR   );// Reset value: 0x00000000
	CLR_4BYTE( EXTI->RTSR  );// Reset value: 0x00000000
	CLR_4BYTE( EXTI->FTSR  );// Reset value: 0x00000000
	CLR_4BYTE( EXTI->SWIER );// Reset value: 0x00000000

	SET_4BYTE( EXTI->PR );// cleared by writing a ‘1’ into the bit

	/* Disable EXTI IRQ from NVIC Registers */
	NVIC_EXTI0_IRQ_DISABLE();
	NVIC_EXTI1_IRQ_DISABLE();
	NVIC_EXTI2_IRQ_DISABLE();
	NVIC_EXTI3_IRQ_DISABLE();
	NVIC_EXTI4_IRQ_DISABLE();
	NVIC_EXTI9_5_IRQ_DISABLE();
	NVIC_EXTI15_10_IRQ_DISABLE();
}

//==========================================================================================
// 									Generic Functions
//==========================================================================================
/* EXTI0 */
void EXTI0_IRQHandler(void)
{
	//clear the Pending Register by writing a ‘1’ into the bit.
	SET_BIT(EXTI->PR,EXTI0);

	//Call IRQ CallBack
	GP_IRQ_CallBack[EXTI0]();
}

/* EXTI1 */
void EXTI1_IRQHandler(void)
{
	//clear the Pending Register by writing a ‘1’ into the bit.
	SET_BIT(EXTI->PR,EXTI1);

	//Call IRQ CallBack
	GP_IRQ_CallBack[EXTI1]();
}

/* EXTI2 */
void EXTI2_IRQHandler(void)
{
	//clear the Pending Register by writing a ‘1’ into the bit.
	SET_BIT(EXTI->PR,EXTI2);

	//Call IRQ CallBack
	GP_IRQ_CallBack[EXTI2]();
}

/* EXTI3 */
void EXTI3_IRQHandler(void)
{
	//clear the Pending Register by writing a ‘1’ into the bit.
	SET_BIT(EXTI->PR,EXTI3);

	//Call IRQ CallBack
	GP_IRQ_CallBack[EXTI3]();
}

/* EXTI4 */
void EXTI4_IRQHandler(void)
{
	//clear the Pending Register by writing a ‘1’ into the bit.
	SET_BIT(EXTI->PR,EXTI4);

	//Call IRQ CallBack
	GP_IRQ_CallBack[EXTI4]();
}

/* EXTI9_5 */
void EXTI9_5_IRQHandler(void)
{
	//clear the Pending Register by writing a ‘1’ into the bit && Call IRQ CallBack
	if( READ_BIT( EXTI->PR , GPIO_PIN_5) ) { SET_BIT(EXTI->PR,EXTI5); GP_IRQ_CallBack[EXTI5](); }
	if( READ_BIT( EXTI->PR , GPIO_PIN_6) ) { SET_BIT(EXTI->PR,EXTI6); GP_IRQ_CallBack[EXTI6](); }
	if( READ_BIT( EXTI->PR , GPIO_PIN_7) ) { SET_BIT(EXTI->PR,EXTI7); GP_IRQ_CallBack[EXTI7](); }
	if( READ_BIT( EXTI->PR , GPIO_PIN_8) ) { SET_BIT(EXTI->PR,EXTI8); GP_IRQ_CallBack[EXTI8](); }
	if( READ_BIT( EXTI->PR , GPIO_PIN_9) ) { SET_BIT(EXTI->PR,EXTI9); GP_IRQ_CallBack[EXTI9](); }
}

/* EXTI15_10 */
void EXTI15_10_IRQHandler(void)
{
	//clear the Pending Register by writing a ‘1’ into the bit && Call IRQ CallBack
	if( READ_BIT( EXTI->PR , GPIO_PIN_10) ) { SET_BIT(EXTI->PR,EXTI10); GP_IRQ_CallBack[EXTI10](); }
	if( READ_BIT( EXTI->PR , GPIO_PIN_11) ) { SET_BIT(EXTI->PR,EXTI11); GP_IRQ_CallBack[EXTI11](); }
	if( READ_BIT( EXTI->PR , GPIO_PIN_12) ) { SET_BIT(EXTI->PR,EXTI12); GP_IRQ_CallBack[EXTI12](); }
	if( READ_BIT( EXTI->PR , GPIO_PIN_13) ) { SET_BIT(EXTI->PR,EXTI13); GP_IRQ_CallBack[EXTI13](); }
	if( READ_BIT( EXTI->PR , GPIO_PIN_14) ) { SET_BIT(EXTI->PR,EXTI14); GP_IRQ_CallBack[EXTI14](); }
	if( READ_BIT( EXTI->PR , GPIO_PIN_15) ) { SET_BIT(EXTI->PR,EXTI15); GP_IRQ_CallBack[EXTI15](); }
}

/*=========================================================================================================
 * @Fn			: Enable_NVIC
 * @brief		: used to enable bit in NVIC to disable IRQ
 * @param [in]	: the input line number to enable the corresponding bit on NVIC
 * @retval		: none
 *=========================================================================================================*/
static void Enable_NVIC(uint8_t input_line_number)
{
	switch(input_line_number)
	{
	case 0:		NVIC_EXTI0_IRQ_ENABLE();		break;
	case 1:		NVIC_EXTI1_IRQ_ENABLE();		break;
	case 2:		NVIC_EXTI2_IRQ_ENABLE();		break;
	case 3:		NVIC_EXTI3_IRQ_ENABLE();		break;
	case 4:		NVIC_EXTI4_IRQ_ENABLE();		break;

	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		NVIC_EXTI9_5_IRQ_ENABLE();
		break;

	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
		NVIC_EXTI15_10_IRQ_ENABLE();
		break;
	}
}

/*=========================================================================================================
 * @Fn			: Disable_NVIC
 * @brief		: used to disable bit in NVIC to disable IRQ
 * @param [in]	: the input line number to disable the corresponding bit on NVIC
 * @retval		: none
 *=========================================================================================================*/
static void Disable_NVIC(uint8_t input_line_number)
{
	switch(input_line_number)
	{
	case 0:		NVIC_EXTI0_IRQ_DISABLE();		break;
	case 1:		NVIC_EXTI1_IRQ_DISABLE();		break;
	case 2:		NVIC_EXTI2_IRQ_DISABLE();		break;
	case 3:		NVIC_EXTI3_IRQ_DISABLE();		break;
	case 4:		NVIC_EXTI4_IRQ_DISABLE();		break;

	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		NVIC_EXTI9_5_IRQ_DISABLE();
		break;

	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
		NVIC_EXTI15_10_IRQ_DISABLE();
		break;
	}
}
