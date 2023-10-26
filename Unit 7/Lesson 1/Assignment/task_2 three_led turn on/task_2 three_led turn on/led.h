/*
 * led.h
 *
 * Created: 4/26/2023 6:34:52 PM
 *  Author: mohamed_elatar
 */ 


#ifndef LED_H_
#define LED_H_

void LED_vinit_pin (char portname , char pinnumber);
void LED_vinit_port (char portname , char numberpin);

void LED_vturn_on_pin (char portname , char pinnumber);
void LED_vturn_on_port (char portname , char numberpin);

void LED_vturn_off_pin (char portname , char pinnumber);
void LED_vturn_off_port (char portname , char numberpin);

void LED_vtoggle_pin (char portname , char pinnumber);
void LED_vtoggle_port (char portname );

unsigned char LED_u8read_pin(char portname , char pinnumber);
unsigned char LED_u8read_port(char portname);

#endif /* LED_H_ */