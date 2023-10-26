/*
 * relay.h
 *
 * Created: 4/30/2023 4:35:13 PM
 *  Author: moham
 */ 


#ifndef RELAY_H_
#define RELAY_H_

void Relay_vinit_pin (char portname , char pinnumber);
void Relay_vturn_on_pin (char portname , char pinnumber);
void Relay_vturn_off_pin (char portname , char pinnumber);



#endif /* RELAY_H_ */