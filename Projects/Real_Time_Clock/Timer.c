/*
 * Timer.c
 *
 * Created: 5/14/2023 6:09:02 PM
 *  Author: mohamed_elatar
 */ 
#include "interrupt.h"
#include "standard_macros.h"
#define SFR_IO8(logical_address)  *((volatile unsigned char *)(logical_address + 0x20))

/**************** out compare pin ******************/
#define MY_DDRB  SFR_IO8(0x17) // make PB3 output pin


/////////////////////////////////////////////// __Timer_0__ /////////////////////////////////////////////////////////////

/*********************** Timer0_macros **************************/
#define MY_TCNT0	SFR_IO8(0x32) //register Timer
#define MY_OCR0		SFR_IO8(0x3C) //out compare register

/***** control_register ****/
#define MY_CS00			0 //clock select
#define MY_CS01			1 //clock select
#define MY_CS02			2 //clock select
#define MY_WGM01		3 //wave generation mode
#define MY_COM00		4 //compare output mode
#define MY_COM01		5 //compare output mode
#define MY_WGM00		6 //wave generation mode
#define MY_FOC0			7 //Force Output Compare
#define MY_TCCR0	SFR_IO8(0x33)

/********* Flags ***********/
#define MY_TOV0		0 //over flow flag
#define MY_OCF0		1 //out compare match flag
#define MY_TIFR		SFR_IO8(0x38)

/******* Enable_Flags *******/
#define MY_TOIE0		0 //timer overflow interrupt enable
#define MY_OCIE0		1 //timer out compare interrupt enable
#define MY_TIMSK	SFR_IO8(0x39)

/////////////////////////////////////////////// __Timer_2__ /////////////////////////////////////////////////////////////

/*********************** Timer2_macros **************************/
#define MY_TCNT2	SFR_IO8(0x24) //register Timer2
#define MY_OCR2		SFR_IO8(0x23) //out compare register

/***** control_register ****/
#define MY_CS20			0 //clock select
#define MY_CS21			1 //clock select
#define MY_CS22			2 //clock select
#define MY_WGM21		3 //wave generation mode
#define MY_COM20		4 //compare output mode
#define MY_COM21		5 //compare output mode
#define MY_WGM20		6 //wave generation mode
#define MY_FOC2			7 //Force Output Compare
#define MY_TCCR2	SFR_IO8(0x25)

/*** synchronous_state_reg ***/
#define MY_AS2			3 // synchronous timer2
#define MY_ASSR		SFR_IO8(0x22)

/********* Flags ***********/
#define MY_TOV2		6 //over flow flag
#define MY_OCF2		7 //out compare match flag
#define MY_TIFR		SFR_IO8(0x38)

/******* Enable_Flags *******/
#define MY_TOIE2		6 //timer overflow interrupt enable
#define MY_OCIE2		7 //timer out compare interrupt enable
#define MY_TIMSK	SFR_IO8(0x39)


//////////////////////////////////////////// driver timer0 //////////////////////////////////////////////

/************ overflow_mode **********************/
void TIMER_vinit_overflow_interrupt (void)
{
	// generate clock
	SET_BIT(MY_TCCR0 , MY_CS00);//division factor 1024	
	SET_BIT(MY_TCCR0 , MY_CS02);
	
	// generate mode
	CLR_BIT(MY_TCCR0 , MY_WGM00);//default 0 may not need clear
	CLR_BIT(MY_TCCR0 , MY_WGM01);
	
	// enable ISR
	Enable_Interrupt();//enable i_bit SREG
	SET_BIT(MY_TIMSK , MY_TOIE0);
}

/************ compare_match_mode ******************/
void TIMER_vinit_CTC_interrupt (void)
{
	// generate mode
	SET_BIT(MY_TCCR0 , MY_WGM01);
	//load value
	MY_OCR0 = 80;//to control delay ((1/8000)*80) == 10msec
	
	// generate clock
	SET_BIT(MY_TCCR0 , MY_CS00);
	SET_BIT(MY_TCCR0 , MY_CS02);
	
	// enable ISR
	Enable_Interrupt();
	SET_BIT(MY_TIMSK , MY_OCIE0);
}

/************ Signal_nonPWM ******************/
void TIMER_vgeneration_signal_non_PWM (void)
{
	// pin out compare signal PB3
	SET_BIT(MY_DDRB , 3);
	
	// generate mode CTC
	SET_BIT(MY_TCCR0 , MY_WGM01);
	
	//load value
	MY_OCR0 = 64;// Freq(OC0) = 8M / 2*(1+64)*1024 == 60 hz
	
	// generate clock 1024
	SET_BIT(MY_TCCR0 , MY_CS00);
	SET_BIT(MY_TCCR0 , MY_CS02);
	
	// compare match mode Toggle
	SET_BIT(MY_TCCR0 , MY_COM00);
}

/************ Fast_PWM ******************/
void TIMER_vgeneration_signal_Fast_PWM (void)
{
	// pin out compare signal PB3
	SET_BIT(MY_DDRB , 3);
	
	// generate mode Fast PWM
	SET_BIT(MY_TCCR0 , MY_WGM01);
	SET_BIT(MY_TCCR0 , MY_WGM00);
	
	//load value
	//25% duty cycle with non-inverting && 75% duty cycle with inverting mode
	MY_OCR0 = 64;// Freq(OC0) = 8M / 256*1024 == 30.5 hz
	
	// generate clock 1024
	SET_BIT(MY_TCCR0 , MY_CS00);
	SET_BIT(MY_TCCR0 , MY_CS02);
	
	// nin_inverting mode clear(OCR0) set(bottom)
	SET_BIT(MY_TCCR0 , MY_COM01);	
}

/************ Fast_PWM ******************/
void TIMER_vgeneration_signal_Phase_Correct_PWM (void)
{
	// pin out compare signal PB3
	SET_BIT(MY_DDRB , 3);
	
	// generate mode Phase Correct PWM
	SET_BIT(MY_TCCR0 , MY_WGM00);
	
	//load value
	MY_OCR0 = 64;// Freq(OC0) = 8M / 510*1024 == 15.3 hz
	
	// generate clock 1024
	SET_BIT(MY_TCCR0 , MY_CS00);
	SET_BIT(MY_TCCR0 , MY_CS02);
	
	// compare out mode
	SET_BIT(MY_TCCR0 , MY_COM01);// clear OC0 in up_count - set OC0 in down_count 
}

/************************************* end timer 0 ************************************************/

//////////////////////////////////////////// driver timer2 //////////////////////////////////////////////

void TIMER2_vinit_overflow_interrupt(void)
{
	//select clock oscillator
	SET_BIT(MY_ASSR , AS2);//external clock

	//generation overflow_mode
	//CLR_BIT(MY_TCCR2 , MY_WGM20); 
	//CLR_BIT(MY_TCCR2 , MY_WGM21);
	
	//select division factor 128
	SET_BIT(MY_TCCR2 , MY_CS20); 
	SET_BIT(MY_TCCR2 , MY_CS22); 
	
	//enable ISR 
	Enable_Interrupt();
	SET_BIT(MY_TIMSK , MY_TOIE2);
}