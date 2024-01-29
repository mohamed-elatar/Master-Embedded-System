/***********************************************
 * @file           : LCD_Driver.c				*
 * @author         : mohamed elatar             *
 * @Data           : November 2, 2023			*
 ************************************************/

//-----------------------------
//Includes
//-----------------------------
#include "LCD_Driver.h"


/*=========================================================================================================
 * @Fn			: HAL_LCD_Init
 * @brief		: to initialize LCD by Send Commands
 * @param [in]	: none
 * @retval		: none
 * Note			: may be 4-bit mode or 8-bit mode
 *=========================================================================================================*/
void HAL_LCD_Init()
{
	_delay_ms(30);
	GPIO_Port_Configure_t port_configure ;
	GPIO_Pin_Configure_t pin_configure ;

	/******* 8-bit mode ********/
#if defined Eight_Bit_Mode
	// send data
	port_configure.GPIO_Mode = GPIO_MODE_OUTPUT_PUSH_PULL;
	port_configure.GPIO_Output_Speed = GPIO_Speed_10;
	MCAL_GPIO_Port_Init( PortName_Dataline , &port_configure , GPIO_PORT_LOW);

	// send control
	pin_configure.GPIO_Pin_Number = EN;
	pin_configure.GPIO_Mode = GPIO_MODE_OUTPUT_PUSH_PULL;
	pin_configure.GPIO_Output_Speed = GPIO_Speed_10;
	MCAL_GPIO_Pin_Init( PortName_Control , &pin_configure );

	pin_configure.GPIO_Pin_Number = RW;
	pin_configure.GPIO_Mode = GPIO_MODE_OUTPUT_PUSH_PULL;
	pin_configure.GPIO_Output_Speed = GPIO_Speed_10;
	MCAL_GPIO_Pin_Init( PortName_Control , &pin_configure );

	pin_configure.GPIO_Pin_Number = RS;
	pin_configure.GPIO_Mode = GPIO_MODE_OUTPUT_PUSH_PULL;
	pin_configure.GPIO_Output_Speed = GPIO_Speed_10;
	MCAL_GPIO_Pin_Init( PortName_Control , &pin_configure );


	// enable write on lcd
	MCAL_GPIO_Write_Pin( PortName_Control , RW , LOGIC_LOW);

	// command instructions
	HAL_LCD_Send_Cmd(Eight_Bit);//8bit-mode
	_delay_ms(1);
	HAL_LCD_Send_Cmd(Disblay_On_Cursor_On);//appear cursor and display
	_delay_ms(1);
	HAL_LCD_Send_Cmd(Clear_Screen);//clear lcd
	_delay_ms(1);
	HAL_LCD_Send_Cmd(Entry_Mode_increase_AC_no_shift);//increase cursor step
	_delay_ms(1);

	/******* 4-bit mode ********/
#elif defined Four_Bit_Mode
	port_configure.GPIO_Mode = GPIO_MODE_OUTPUT_PUSH_PULL;
	port_configure.GPIO_Output_Speed = GPIO_Speed_10;
	MCAL_GPIO_Port_Init( PortName_Dataline , &port_configure , GPIO_PORT_LOW_NIBBLE_LOW );

	pin_configure.GPIO_Pin_Number = EN;
	pin_configure.GPIO_Mode = GPIO_MODE_OUTPUT_PUSH_PULL;
	pin_configure.GPIO_Output_Speed = GPIO_Speed_10;
	MCAL_GPIO_Pin_Init( PortName_Control , &pin_configure );

	pin_configure.GPIO_Pin_Number = RW;
	pin_configure.GPIO_Mode = GPIO_MODE_OUTPUT_PUSH_PULL;
	pin_configure.GPIO_Output_Speed = GPIO_Speed_10;
	MCAL_GPIO_Pin_Init( PortName_Control , &pin_configure );

	pin_configure.GPIO_Pin_Number = RS;
	pin_configure.GPIO_Mode = GPIO_MODE_OUTPUT_PUSH_PULL;
	pin_configure.GPIO_Output_Speed = GPIO_Speed_10;
	MCAL_GPIO_Pin_Init( PortName_Control , &pin_configure );

	// enable write on lcd
	MCAL_GPIO_Write_Pin( PortName_Control , RW , LOGIC_LOW);

	// command instructions
	HAL_LCD_Send_Cmd(Return_Home); //return home
	_delay_ms(1);
	HAL_LCD_Send_Cmd(Four_Bit);//4bit-mode
	_delay_ms(1);
	HAL_LCD_Send_Cmd(Disblay_On_Cursor_On);//appear cursor and display
	_delay_ms(1);
	HAL_LCD_Send_Cmd(Clear_Screen);//clear lcd
	_delay_ms(1);
	HAL_LCD_Send_Cmd(Entry_Mode_increase_AC_no_shift);//increase cursor step
	_delay_ms(1);
#endif

}

/*=========================================================================================================
 * @Fn			: HAL_LCD_ClearScreen
 * @brief		: delete lcd screen
 * @param [in]	: none
 * @retval		: none
 *=========================================================================================================*/
void HAL_LCD_ClearScreen()
{
	HAL_LCD_Send_Cmd(Clear_Screen);
	_delay_ms(1);
}

/*=========================================================================================================
 * @Fn			: HAL_Enable_bit
 * @brief		: to output trigger to pin enable lcd
 * @param [in]	: none
 * @retval		: none
 *=========================================================================================================*/
void HAL_Enable_bit ()
{
	MCAL_GPIO_Write_Pin( PortName_Control , EN , LOGIC_HIGH);
	_delay_ms(25);
	MCAL_GPIO_Write_Pin( PortName_Control , EN , LOGIC_LOW);
}


/*=========================================================================================================
 * @Fn			: LCD_u8read_busy_flag
 * @brief		: read busy flag lcd to show lcd finished send data or command yet?
 * @param [in]	: none
 * @retval		: none
 *=========================================================================================================*/
void LCD_u8read_busy_flag()
{
	GPIO_Pin_Configure_t pin_configure ;
	pin_configure.GPIO_Pin_Number = GPIO_PIN_7;
	pin_configure.GPIO_Mode = GPIO_MODE_INPUT_FLOATING;
	MCAL_GPIO_Pin_Init(PortName_Dataline, &pin_configure);

	MCAL_GPIO_Write_Pin(PortName_Control, RW , LOGIC_HIGH);
	MCAL_GPIO_Write_Pin(PortName_Control, RS , LOGIC_LOW);

	while( MCAL_GPIO_Read_Pin(GPIOA, GPIO_PIN_7) );

	pin_configure.GPIO_Pin_Number = GPIO_PIN_7;
	pin_configure.GPIO_Mode = GPIO_MODE_OUTPUT_PUSH_PULL;
	pin_configure.GPIO_Output_Speed = GPIO_Speed_10;
	MCAL_GPIO_Pin_Init(PortName_Dataline, &pin_configure);

	MCAL_GPIO_Write_Pin(PortName_Control, RW , LOGIC_LOW);
}


/*=========================================================================================================
 * @Fn			: HAL_LCD_Send_Char
 * @brief		: write data on data-line lcd
 * @param [in]	: Character
 * @retval		: none
 * Note			: may be 4-bit mode or 8-bit mode
 *=========================================================================================================*/
void HAL_LCD_Send_Char(uint8_t Character)
{
	/******* 8-bit mode ********/
#if defined Eight_Bit_Mode
	MCAL_GPIO_Write_Port(PortName_Dataline , Character , GPIO_PORT_LOW);
	MCAL_GPIO_Write_Pin(PortName_Control, RW , LOGIC_LOW);
	MCAL_GPIO_Write_Pin(PortName_Control, RS , LOGIC_HIGH);
	HAL_Enable_bit();

	/******* 4-bit mode ********/
#elif defined Four_Bit_Mode
	//send MSB
	MCAL_GPIO_Write_Port(PortName_Dataline , Character >> 4 , GPIO_PORT_LOW_NIBBLE_LOW);
	MCAL_GPIO_Write_Pin(PortName_Control, RS , LOGIC_HIGH);
	HAL_Enable_bit();

	//send LSB
	MCAL_GPIO_Write_Port(PortName_Dataline , Character , GPIO_PORT_LOW_NIBBLE_LOW);
	MCAL_GPIO_Write_Pin(PortName_Control, RS , LOGIC_HIGH);
	HAL_Enable_bit();
#endif
	_delay_ms(1);
}

/*=========================================================================================================
 * @Fn			: HAL_LCD_Send_Cmd
 * @brief		: write data on data-line lcd
 * @param [in]	: Command
 * @retval		: none
 * Note			: may be 4-bit mode or 8-bit mode
 *=========================================================================================================*/
void HAL_LCD_Send_Cmd(uint8_t Command)
{
	/******* 8-bit mode ********/
#if defined Eight_Bit_Mode
	MCAL_GPIO_Write_Port(PortName_Dataline , Command , GPIO_PORT_LOW);
	MCAL_GPIO_Write_Pin(PortName_Control, RW , LOGIC_LOW);
	MCAL_GPIO_Write_Pin(PortName_Control, RS , LOGIC_LOW);
	HAL_Enable_bit();

	/******* 4-bit mode ********/
#elif defined Four_Bit_Mode
	//send MSB
	MCAL_GPIO_Write_Port(PortName_Dataline , Command >> 4 , GPIO_PORT_LOW_NIBBLE_LOW);
	MCAL_GPIO_Write_Pin(PortName_Control, RS , LOGIC_LOW);
	HAL_Enable_bit();
	//send LSB
	MCAL_GPIO_Write_Port(PortName_Dataline , Command , GPIO_PORT_LOW_NIBBLE_LOW);
	MCAL_GPIO_Write_Pin(PortName_Control, RS , LOGIC_LOW);
	HAL_Enable_bit();
#endif
	_delay_ms(1);
}


/*=========================================================================================================
 * @Fn			: HAL_LCD_Send_String
 * @brief		: write string on dataline lcd
 * @param [in]	: pointer to char point to address string
 * @retval		: none
 * Note			: may be lcd 2x16 or lcd 4x16
 *=========================================================================================================*/
void HAL_LCD_Send_String(uint8_t *ptr)
{
	uint32_t count=0;
	while(*ptr != 0)
	{
		count++;
		HAL_LCD_Send_Char(*ptr++);
#if defined LCD_2X16
		if (count == 16) 		HAL_LCD_Move_Cursor(2,1);
		else if (count == 32)
		{
			HAL_LCD_ClearScreen();
			HAL_LCD_Move_Cursor(1,1);
			count = 0;
		}
#elif defined LCD_4X16
		if (count == 16) 		HAL_LCD_Move_Cursor(2,1);
		else if (count == 32) 	HAL_LCD_Move_Cursor(3,1);
		else if (count == 48) 	HAL_LCD_Move_Cursor(4,1);
		else if (count == 64)
		{
			HAL_LCD_ClearScreen();
			HAL_LCD_Move_Cursor(1,1);
			count = 0;
		}
#endif
	}
	_delay_ms(1);
}

/*=========================================================================================================
 * @Fn			: HAL_LCD_Send_Number
 * @brief		: write number on dataline lcd
 * @param [in]	: interger number
 * @retval		: none
 *=========================================================================================================*/

void HAL_LCD_Send_Number (sint32_t num)
{
	sint8_t str[10];
	sint8_t * sign = (num < 0) ? "-" : "" ;
	sint32_t val = (num < 0) ? -1*num : num ;

	sprintf(str , "%s%d" , sign , val);
	HAL_LCD_Send_String(str);
	_delay_ms(1);
}


/*=========================================================================================================
 * @Fn			: HAL_LCD_Send_Real_Number
 * @brief		: write number on dataline lcd
 * @param [in]	: float number
 * @retval		: none
 *=========================================================================================================*/
void HAL_LCD_Send_Real_Number (float32_t num)
{
	uint8_t str[10];

	sint8_t *sign = (num < 0) ? "-" : "" ;
	sint32_t real_val = (num < 0) ? -1*num : num ;
	sint32_t float_val = (num < 0) ? ((-num - real_val )*100) : ((num - real_val )*100);

	sprintf(str , "%s%d.%.2d" , sign , real_val , float_val);
	HAL_LCD_Send_String(str);
	_delay_ms(1);
}

/*=========================================================================================================
 * @Fn			: HAL_LCD_Move_Cursor
 * @brief		: control move cursor on screen
 * @param [in]	: row and column
 * @retval		: none
 * Note			: may be lcd 2x16 or lcd 4x16
 *=========================================================================================================*/
void HAL_LCD_Move_Cursor (uint8_t row , uint8_t column)
{
	uint8_t cmd;
#if defined LCD_2X16
	if (row>2 || row<0  ||  column>16 || column<1)
	{
		cmd = 0x80;
	}
	else if(row == 1)
	{
		cmd = (0x80 + column -1);
	}
	else if (row == 2)
	{
		cmd = (0xC0 + column -1);
	}
#elif defined LCD_4X16
	if (row>4 || row<1  ||  column>16 || column<1)
	{
		cmd = 0x80;
	}
	else if(row == 1)
	{
		cmd = (0x80 + column -1);
	}
	else if (row == 2)
	{
		cmd = (0xC0 + column -1);
	}
	else if (row == 3)
	{
		cmd = (0x90 + column -1);
	}
	else if (row == 4)
	{
		cmd = (0xD0 + column -1);
	}
#endif
	HAL_LCD_Send_Cmd(cmd);
	_delay_ms(1);
}

