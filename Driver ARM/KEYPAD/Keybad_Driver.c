/***********************************************
 * @file           : Keybad_Driver.c		 	*
 * @author         : mohamed elatar             *
 * @Data           : November 5, 2023			*
 ************************************************/

//-----------------------------
//Includes
//-----------------------------
#include "Keybad_Driver.h"


/*=========================================================================================================
 * @Fn			: HAL_Keybad_Init
 * @brief		: to initialize Specific pin (I/P OR O/P) for ROW & COLUMN
 * @param [in]	: none
 * @retval		: none
 * Note			: (pull_up) default IDR & ODR = 0valF
 *=========================================================================================================*/

void HAL_Keybad_Init ()
{
	// output pins
	GPIO_Port_Configure_t PortConfig;
	PortConfig.GPIO_Mode = GPIO_MODE_OUTPUT_PUSH_PULL;
	PortConfig.GPIO_Output_Speed = GPIO_Speed_10;
	MCAL_GPIO_Port_Init(ROW_PORT, &PortConfig, ROW_Nibble);

	// input pins
	PortConfig.GPIO_Mode = GPIO_MODE_INPUT_PULL_UP;
	MCAL_GPIO_Port_Init(COL_PORT, &PortConfig, COL_Nibble);
}

/*=========================================================================================================
 * @Fn			: HAL_Keybad_Read
 * @brief		: to read input from keypad
 * @param [in]	: none
 * @retval		: value keypad
 *=========================================================================================================*/
uint8_t HAL_Keybad_Read()
{
	uint8_t keybad[4][4] = { { 7 , 8 , 9 , '/'} , { 4 , 5 , 6 , '*'} , { 1 , 2 , 3 , '-'} , { 'A' , 0 , '=' , '+'} };
	uint8_t Keypad_Row[] = { R1, R2, R3, R4 }; //rows
	uint8_t Keypad_Col[] = { C1, C2, C3, C4 }; //columns
	uint32_t row , column , val , retval = NOT_PRESSED;
	for (row=0 ; row<4 ; row++)
	{
		MCAL_GPIO_Write_Pin(ROW_PORT , Keypad_Row[0] , LOGIC_LOW);
		MCAL_GPIO_Write_Pin(ROW_PORT , Keypad_Row[1] , LOGIC_LOW);
		MCAL_GPIO_Write_Pin(ROW_PORT , Keypad_Row[2] , LOGIC_LOW);
		MCAL_GPIO_Write_Pin(ROW_PORT , Keypad_Row[3] , LOGIC_LOW);
		MCAL_GPIO_Write_Pin(ROW_PORT , Keypad_Row[row] , LOGIC_HIGH);
		for (column=0 ; column<4 ; column++)
		{
			val=MCAL_GPIO_Read_Pin(COL_PORT , Keypad_Col[column]);
			if (val == LOGIC_HIGH)
			{
				retval = keybad[row][column];
				while(MCAL_GPIO_Read_Pin(COL_PORT , Keypad_Col[column]) == LOGIC_HIGH);//continuous pressed
				break;
			}
		}
		if (val == LOGIC_HIGH)
		{
			break;
		}
	}
	return retval;
}
