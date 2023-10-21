/*
 * interrupt.h
 *
 * Created: 5/1/2023 11:15:24 PM
 *  Author: moham
 */ 


#ifndef INTERRUPT_H_
#define INTERRUPT_H_
//#include <avr/interrupt.h>
#include "standard_macros.h"
/******************* SFR_IO8 ********************/
#define offset_add 0x20
#define SFR_IO8(logical_add) (*(volatile unsigned char*)(logical_add+offset_add))

/******* SREG states_register ***********/
#define I_BIT				  7
#define MY_SREG				  SFR_IO8(0x3F)
#define Enable_Interrupt()    SET_BIT(MY_SREG,I_BIT)
#define DisEnable_Interrupt() CLR_BIT(MY_SREG,I_BIT)

/******* GICR general_interrupt_control_register ***********/

#define INT_1    7
#define INT_0    6
#define INT_2    5
#define MY_GICR SFR_IO8(0x3B) //enable interrupt

/******* GIFR general_interrupt_flag_register ***********/

#define INTF_2 5
#define INTF_0 6
#define INTF_1 7
#define MY_GIFR SFR_IO8(0x3A) //flag interrupt 1 when implement ISR
 
/******* MCUCR Microcontroller_control_register ***********/

#define ISC_00 0  //interrupt sense control ISC
#define ISC_01 1
#define ISC_10 2
#define ISC_11 3
#define MY_MCUCR SFR_IO8(0x35) //to control when happen interrupt (low , high)level || (rising , falling)edge

/******* MCUCSR Microcontroller_control_state_register ***********/

#define ISC_2 6               //interrupt sense control ISC
#define MY_MCUCSR SFR_IO8(0x34) //to control when happen interrupt (low , high)level || (rising , falling)edge


/*************** ISR_interrupt_service_routine *************/

#define INT_0_vect				__vector_1
#define INT_1_vect				__vector_2
#define INT_2_vect				__vector_3
#define BADISR__vect			__vector_default
#define NOT_OPTIMIZE_CODE		used
#define ISR__NOBLOCK				__attribute__((interrupt)) //enable nested interrupt
#define ISR__NAKED				    __attribute__((naked))    //masked code assembly

#define MY_ISR(vecto_r , ...)      \
								void vecto_r (void) __attribute__((signal,NOT_OPTIMIZE_CODE)) __VA_ARGS__ ;   \
								void vecto_r (void)
																
#endif /* INTERRUPT_H_ */