/*
 * driver_EEPROM.h
 *
 * Created: 5/1/2023 1:15:59 PM
 *  Author: mohamed_elatar
 */ 


#ifndef DRIVER EEPROM_H_
#define DRIVER EEPROM_H_


void EEPROM_vwrite (const unsigned short address , unsigned char val);
unsigned char EEPROM_u8read (const unsigned short address);


#endif /* DRIVER EEPROM_H_ */