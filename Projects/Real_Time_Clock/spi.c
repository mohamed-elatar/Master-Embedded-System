/*
 * spi.c
 *
 * Created: 6/7/2023 2:52:07 AM
 *  Author: mohamed_elatar
 */ 

/*
 * MCAL
 */
#define F_CPU 8000000ul
#include <util/delay.h>
#include "standard_macros.h"
#define SFR_IO8(logical_address)  *((volatile unsigned char *) (0x20 + logical_address))

/************** macros ******************/

/**** SPI Data Register ****/
#define MY_SPDR		SFR_IO8(0x0F)

/**** SPI control Register ****/
#define MY_SPIE		7 //spi interrupt enable
#define MY_SPE 		6 //spi enable
#define MY_DORD 	5 //data order (LSB , MSB)
#define MY_MSTR 	4 //master slave select
#define MY_CPOL 	3 //clock parity
#define MY_CPHA 	2 //clock phase
#define MY_SPR1 	1 //spi clock rate select 1
#define MY_SPR0		0 //spi clock rate select 0
#define MY_SPCR		SFR_IO8(0x0D)

/**** SPI status Register ****/
#define MY_SPIF  	7 //spi interrupt flag
#define MY_WCOL		6 //Write COLlision Flag(over write)
#define MY_SPI2X	0 //spi double speed
#define MY_SPSR		SFR_IO8(0x0E)

/***************************************** Driver *************************************/

/********* initi master **********/
void SPI_Master_vinit(void)
{
	//direction pins
	DIO_vset_pin_direction('b' , 4 , 1);//slave select SS
	DIO_vset_pin_direction('b' , 5 , 1);//MOSI
	DIO_vset_pin_direction('b' , 6 , 0);//MISO (optional)
	DIO_vset_pin_direction('b' , 7 , 1);//SCK
	
	//not select any slave now(not active)
	DIO_vwrite_pin_value('b' , 4 , 1);
	
	//enable spi
	SET_BIT(MY_SPCR , MY_SPE);
	
	//send LSB first(optional)
	CLR_BIT(MY_SPCR , MY_DORD);
	
	//enable master
	SET_BIT(MY_SPCR , MY_MSTR);
	
	//clock rate select freq(mc)/16
	SET_BIT(MY_SPCR , MY_SPR0);
}

/********* initi slave **********/
void SPI_Slave_vinit(void)
{
	//enable slave(optional)
	CLR_BIT(MY_SPCR , MY_MSTR);
	
	//enable spi
	SET_BIT(MY_SPCR , MY_SPE); 
	
	//direction pin
	DIO_vset_pin_direction('b' , 6 , 1);//MISO
	DIO_vset_pin_direction('b' , 4 , 0);//SS	(optional)
	DIO_vset_pin_direction('b' , 5 , 0);//MOSI	(optional)
	DIO_vset_pin_direction('b' , 7 , 0);//SCK	(optional)
}

/*********** SPI_master_transamit ****************/
void SPI_Master_transamit_MAX7221 (unsigned char cmd , unsigned char data)
{
    //active slave select SS pin
    DIO_vwrite_pin_value('b' , 4 , 0);
    //load cmd
    MY_SPDR = cmd;
    //transmit cmd
    while (READ_BIT(MY_SPSR , MY_SPIF) == 0);

    //load data
    MY_SPDR = data;
    //transmit data
    while (READ_BIT(MY_SPSR , MY_SPIF) == 0);

    //de_active slave select SS pin
    DIO_vwrite_pin_value('b' , 4 , 1);
}

unsigned char SPI_Master_u8transamit (unsigned char data)
{
	//active slave select SS pin
	DIO_vwrite_pin_value('b' , 4 , 0);
	
	//load data 
	MY_SPDR = data;
	
	//transmit data
	while (READ_BIT(MY_SPSR , MY_SPIF) == 0);
	//(if == 0)not yet transmit to slave
	//must exist data SPDR before loop flag in order clear

    //active slave select SS pin
	_delay_ms(1000);
	return MY_SPDR ; //master receive data from slave exchange
} 

/*********** SPI_slave_receive ****************/
unsigned char SPI_Slave_u8receive (unsigned char data)
{
	//load data
	MY_SPDR = data;
	
	//receive data from master
	while (READ_BIT(MY_SPSR , MY_SPIF) == 0);
	//(if == 0)not yet rececive to master
	//must exist data SPDR before loop flag in order clear
	//so flag not clear if slave not receive any data
	_delay_ms(1000);
	return MY_SPDR ; //slave receive data from master exchange
}

/********* master send string ***************/
void SPI_Master_vtransamit_string (unsigned char *ptr)
{
	while(*ptr != 0)
	{
		SPI_Master_u8transamit(*ptr);
		_delay_ms(300);
		ptr++;
	}
}

/************************************ end *********************************************/