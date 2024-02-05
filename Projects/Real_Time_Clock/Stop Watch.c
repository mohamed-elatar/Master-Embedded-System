/*
 * Stop_Watch.c
 *
 * Created: 2/1/2024 5:22:36 AM
 *  Author: mohamed elatar
 */ 

#define F_CPU 8000000UL
#include <util/delay.h>
#include "Timer.h"
#include "lcd.h"
#include "led.h"
#include "Keybad.h"
#include "spi.h"
#include "interrupt.h"

void Enter_data();

volatile uint8_t counter_sec_ISR  , counter_hour_ISR  , counter_minute_ISR ;
volatile uint8_t data_sec , data_hour , data_minute ;
volatile uint8_t flag_Alarm , flag_stopwatch , flag_start_count;
volatile uint8_t ISR_0_StopWatch , ISR_0_Alarm , ISR_1 , ISR_2 ;

uint8_t counter_sec , counter_hour , counter_minute ;
uint8_t first_digit , secand_digit ,key ;

int main(void)
{   
    // initialize buzzer for Timer State
    LED_vinit_pin('d' , 0);
    LED_vinit_pin('d' , 1);
    ///// initialize  /////
    LCD_vinit();
    Keybad_vinit();

    LCD_vsend_string("----------------");
    LCD_vmove_cursor(2,1);
    LCD_vsend_string(" Select Option");
    LCD_vmove_cursor(3,1);
    LCD_vsend_string("----------------");

    _delay_ms(1500);
    LCD_vClearScreen();
    LCD_vsend_string("1 : World Clock");
    LCD_vmove_cursor(2,1);
    LCD_vsend_string("2 : StopWatch");
    LCD_vmove_cursor(3,1);
    LCD_vsend_string("3 : Timer");
    LCD_vmove_cursor(4,1);
    // ? 


    ///// configure ISR /////
    Enable_Interrupt();
	SET_BIT(MY_GICR , INT_0);  //enable external interrupt 0
	SET_BIT(MY_GICR , INT_1);  //enable external interrupt 1
	SET_BIT(MY_GICR , INT_2);  //enable external interrupt 2

	//set rising edge option for  external interrupt 0	
	SET_BIT(MY_MCUCR , ISC_00);
	SET_BIT(MY_MCUCR , ISC_01);

	//set rising edge option for  external interrupt 1
	SET_BIT(MY_MCUCR , ISC_10);
	SET_BIT(MY_MCUCR , ISC_11);

	//set rising edge option for  external interrupt 2
	SET_BIT(MY_MCUCSR , ISC_2);

    ISR_0_StopWatch = ISR_1 = ISR_2 = 1;
 

     ///// configure 7-seg max /////
    SPI_Master_vinit();
    //Decode mode || Code B decode for digits 7–0
    SPI_Master_transamit_MAX7221(0x09, 0xFF);
    //Intensity || 15/16(max on)
    SPI_Master_transamit_MAX7221(0x0A, 0xFF);
    //Scan Limit || Display digits 0 1 2 3 4 5 6 7
    SPI_Master_transamit_MAX7221(0x0B, 0xF7);
    //Shutdown || Normal Operation
    SPI_Master_transamit_MAX7221(0x0C, 0x00);

    SPI_Master_transamit_MAX7221( 0x3 , 10);
    SPI_Master_transamit_MAX7221( 0x6 , 10);

    
    // inti real time clock
    TIMER2_vinit_overflow_interrupt();

    while(1)
    {
        key = Keybad_u8read();
        if (key != NOT_PRESSED)
        {
            // option world clock
            if (key == '1')
            {
                flag_Alarm = flag_stopwatch = 0;
                flag_start_count = 1;

                SPI_Master_transamit_MAX7221(0x0C, 0x00);

                LCD_vClearScreen();
                LCD_vmove_cursor(3,1);
                LCD_vsend_string("   World Clock");
                _delay_ms(500);

                Enter_data();
                
                SPI_Master_transamit_MAX7221(0x0C, 0x01);

                LCD_vClearScreen();
                LCD_vmove_cursor(3,1);
                LCD_vsend_string("   World Clock");
            }

            //Stop Watch
            else if ( key == '2')
            {
                flag_stopwatch = 1;
                flag_Alarm = 0;
                flag_start_count = 1;

                counter_hour_ISR = 0;
                counter_minute_ISR = 0;
                counter_sec_ISR = 0;

                SPI_Master_transamit_MAX7221(0x0C, 0x00);

                LCD_vClearScreen();
                LCD_vmove_cursor(3,1);
                LCD_vsend_string("   Stop Watch");
                _delay_ms(500);


                SPI_Master_transamit_MAX7221(0x0C, 0x01);
            }

            //Timer
            else if ( key == '3')
            {
                ISR_0_Alarm = 1;
                flag_start_count = 1;
                SPI_Master_transamit_MAX7221(0x0C, 0x00);

                LCD_vClearScreen();
                LCD_vmove_cursor(3,1);
                LCD_vsend_string("   Timer");
                _delay_ms(500);

                Enter_data();

                flag_Alarm = 1;
                LCD_vClearScreen();
                LCD_vmove_cursor(3,1);
                LCD_vsend_string("   Timer");

                SPI_Master_transamit_MAX7221(0x0C, 0x01);

            }

            // wrong option
            else
            {   
                flag_Alarm = flag_stopwatch = flag_start_count = 0;
                SPI_Master_transamit_MAX7221(0x0C, 0x00);

                LCD_vClearScreen();
                LCD_vmove_cursor(2,1);
                LCD_vsend_string("Wrong Option");
                _delay_ms(1000);
                LCD_vClearScreen();
                LCD_vsend_string("----------------");
                LCD_vmove_cursor(2,1);
                LCD_vsend_string("Select");
                LCD_vmove_cursor(3,1);
                LCD_vsend_string("Valid Option");
                LCD_vmove_cursor(4,1);
                LCD_vsend_string("----------------");
                _delay_ms(1000);
                LCD_vClearScreen();
                LCD_vsend_string("1 : World Clock");
                LCD_vmove_cursor(2,1);
                LCD_vsend_string("2 : Stop Watch");
                LCD_vmove_cursor(3,1);
                LCD_vsend_string("3 : Timer");
                LCD_vmove_cursor(4,1);
            }// end if condition '1 
        }
        else
        {
        }//end if condition not_pressesd
        
    }
}

ISR(TIMER2_OVF_vect)
{
    if (counter_sec_ISR == 60)
    {
        counter_sec_ISR = 0;
        counter_minute_ISR++;
        if (counter_minute_ISR == 60)
        {
            counter_minute_ISR = 0;
            counter_hour_ISR++;
            if (counter_hour_ISR == 24)
            {
                counter_hour_ISR = 0;
            }
        }
    }

    if(flag_start_count && !flag_Alarm)
    {
        SPI_Master_transamit_MAX7221( 0x1 , counter_hour_ISR/10);
        SPI_Master_transamit_MAX7221( 0x2 , counter_hour_ISR%10);
        
        SPI_Master_transamit_MAX7221( 0x4 , counter_minute_ISR/10);
        SPI_Master_transamit_MAX7221( 0x5 , counter_minute_ISR%10);
        
        SPI_Master_transamit_MAX7221( 0x7 , counter_sec_ISR/10);
        SPI_Master_transamit_MAX7221( 0x8 , counter_sec_ISR%10);
    }
    else if (flag_Alarm)
    {
        SPI_Master_transamit_MAX7221( 0x1 , counter_hour/10);
        SPI_Master_transamit_MAX7221( 0x2 , counter_hour%10);
        
        SPI_Master_transamit_MAX7221( 0x4 , counter_minute/10);
        SPI_Master_transamit_MAX7221( 0x5 , counter_minute%10);
        
        SPI_Master_transamit_MAX7221( 0x7 , counter_sec/10);
        SPI_Master_transamit_MAX7221( 0x8 , counter_sec%10);

        // set alarm
         if( !counter_sec && !counter_minute && !counter_hour)
         {
             counter_sec = counter_minute = counter_hour = 0;
             flag_Alarm = flag_start_count = 0;
             LED_vturn_on_pin('d' , 0);
             LED_vturn_on_pin('d' , 1);
         }


         // in progress count down
        else if(counter_sec-- == 0 )
        {
            if( !counter_sec && !counter_minute && !counter_hour) 
            {
                counter_sec = counter_minute = counter_hour = 0;
            }
            else 
            {
                counter_sec = 59;
            }

            // nested if minute
            if (counter_minute-- == 0 )
            {
                if( !counter_minute && !counter_hour ) counter_minute = counter_hour = 0;
                else
                {
                    counter_minute = 59;
                }
                // nested if hour
                if (counter_hour-- == 0)
                {
                    counter_hour = 0;
                }
            }
        } // end alarm counter decrement 
    }

    // global variable
    counter_sec_ISR++;
}


ISR(INT0_vect)
{
    // reset 
    if( ISR_0_StopWatch && flag_stopwatch)
    {
           counter_hour_ISR = 0;
           counter_minute_ISR = 0;
           counter_sec_ISR = 0;
           flag_start_count = 1;
    }

    if( ISR_0_Alarm && !flag_Alarm)
    {
        LED_vturn_off_pin('d' , 0);
        LED_vturn_off_pin('d' , 1);
        flag_start_count = 0;
    }
}

ISR(INT1_vect)
{
    // stop count for stop_warch
    if( ISR_1 && flag_stopwatch)    
    {
        flag_start_count = 0;
        data_hour = counter_hour_ISR;
        data_minute = counter_minute_ISR;
        data_sec = counter_sec_ISR;
    }
}

ISR(INT2_vect)
{   
    // resume
    if( ISR_2 && flag_stopwatch)
    {
        counter_hour_ISR = data_hour ;
        counter_minute_ISR = data_minute ;
        counter_sec_ISR = data_sec ;
        flag_start_count = 1;
    }
}

void Enter_data()
{
    Disable_Interrupt();
    Label :
    LCD_vClearScreen();
    LCD_vsend_string("hours = --");
    LCD_vmove_cursor(1,9);

    do
    {
        first_digit = Keybad_u8read();
    } while (first_digit == NOT_PRESSED);
    LCD_vsend_char(first_digit);

    do
    {
        secand_digit = Keybad_u8read();
    } while (secand_digit == NOT_PRESSED);
    LCD_vsend_char(secand_digit);
    counter_hour = (secand_digit -'0') + ((first_digit - '0')*10);

    /********* minute *************/
    LCD_vmove_cursor(2,1);
    LCD_vsend_string("minute = --");
    LCD_vmove_cursor(2,10);

    do
    {
        first_digit = Keybad_u8read();
    } while (first_digit == NOT_PRESSED);
    LCD_vsend_char(first_digit);

    do
    {
        secand_digit = Keybad_u8read();
    } while (secand_digit == NOT_PRESSED);
    LCD_vsend_char(secand_digit);
    counter_minute = (secand_digit -'0') + ((first_digit - '0')*10);

    /********* sec *************/
    LCD_vmove_cursor(3,1);
    LCD_vsend_string("seconds = --");
    LCD_vmove_cursor(3,11);

    do
    {
        first_digit = Keybad_u8read();
    } while (first_digit == NOT_PRESSED);
    LCD_vsend_char(first_digit);

    do
    {
        secand_digit = Keybad_u8read();
    } while (secand_digit == NOT_PRESSED);

    LCD_vsend_char(secand_digit);
    counter_sec = (secand_digit -'0') + ((first_digit - '0')*10);
    _delay_ms(1000);

    if (counter_hour>=24 || counter_minute>=60 || counter_sec>=60)
    {
        LCD_vClearScreen();
        LCD_vsend_string("  Valid Range");
        LCD_vmove_cursor(2,1);
        LCD_vsend_string("hours [0:23]");
        LCD_vmove_cursor(3,1);
        LCD_vsend_string("minute [0:59]");
        LCD_vmove_cursor(4,1);
        LCD_vsend_string("seconds [0:59]");
        _delay_ms(1500);
        goto Label;
    }

    counter_hour_ISR = counter_hour;
    counter_minute_ISR = counter_minute;
    counter_sec_ISR = counter_sec;
    Enable_Interrupt();
}