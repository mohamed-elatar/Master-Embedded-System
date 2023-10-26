/*
 * dio.h
 *
 * Created: 4/25/2023 11:28:59 AM
 *  Author: moham
 */ 


#ifndef DIO_H_
#define DIO_H_

void DIO_vset_pin_direction(char portname , char pinnumber , char dirction);
void DIO_vwrite_pin_value(char portname , char pinnumber , char val);
void DIO_vtoggle_pin(char portname , char pinnumber);
unsigned char DIO_u8read_pin (char portname , char pinnumber);
void DIO_vset_port_direction(char portname , char direction);
void DIO_vwrite_port_value(char portname , char value);
void DIO_vtoggle_port(char portname);
unsigned char DIO_u8read_port(char portname);


#endif /* DIO_H_ */