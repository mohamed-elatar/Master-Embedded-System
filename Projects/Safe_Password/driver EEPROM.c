/*
 * driver_EEPROM.c
 *
 * Created: 5/1/2023 1:15:30 PM
 *  Author: mohamed elatar
 */ 


/*
 *MCAL LAYER
 */

/********************** macros ****************************/
#define offset_add 0x20
#define SFR_IO8(logical_add)    (*(volatile unsigned char *)(logical_add + offset_add))  //Special Function Register Input Output 8_Bit
#define SFR_IO16(logical_add)   (*(volatile unsigned short *)(logical_add + offset_add)) //Special Function Register Input Output 16_Bit

/********************** EEPROM Address ********************/
#define MY_EEAR   SFR_IO16(0x1E)
#define MY_EEARL  SFR_IO8(0x1E)
#define MY_EEARH  SFR_IO8(0x1F)

/********************** EEPROM Data **********************/
#define MY_EEDR  SFR_IO8(0x1D)

/********************** EEPROM Control **********************/
#define MY_EERE  0 // to read from EEPROM 
#define MY_EEWE  1 // to write on EEPROM when enable master write enable EEMWE
#define MY_EEMWE 2 // enable master write enable , HW clear this bit after 4cycle , cycle = 1/freq(mc)
#define MY_EECR  SFR_IO8(0x1C)


/******************************* Driver EEPROM ****************************/

#include "standard_macros.h"
/***************** Write On EEPROM **************/
void EEPROM_vwrite (const unsigned short address , unsigned char val)
{
	/****** load address *********/
	MY_EEARL = (char)address;
	MY_EEARH = (char)(address >> 8);
	/****** load address *********/
	MY_EEDR = val;
	/****** enable write *********/
	SET_BIT(MY_EECR , MY_EEMWE);
	SET_BIT(MY_EECR , MY_EEWE );
	while(READ_BIT(MY_EECR , MY_EEWE) == 1); // looping until finish write
}

/***************** erad from EEPROM **************/
unsigned char EEPROM_u8read (const unsigned short address)
{
	/****** load address *********/
	MY_EEAR = address;
	/****** enable write *********/
	SET_BIT(MY_EECR , MY_EERE);
	/****** return value *********/
	return MY_EEDR;
}


/******************************* end ****************************/