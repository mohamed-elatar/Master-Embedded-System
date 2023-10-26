/*
 * button.h
 *
 * Created: 4/26/2023 10:43:52 PM
 *  Author: moham
 */ 


#ifndef BUTTON_H_
#define BUTTON_H_

void BUTTON_vinit_pin (char portname , char pinnumber);
void BUTTON_vinit_port (char portname , char numberpin);
unsigned char BUTTON_u8read_pin(char portname , char pinnumber);
unsigned char BUTTON_u8read_port(char portname);
void BUTTON_vinternal_pull_up_pin (char portname , char pinnumber , char pud_enable);



#endif /* BUTTON_H_ */