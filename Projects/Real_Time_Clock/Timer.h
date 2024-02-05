/*
 * Timer.h
 *
 * Created: 5/14/2023 6:09:17 PM
 *  Author: moham
 */ 


#ifndef TIMER_H_
#define TIMER_H_

//////////////// ___timer_0___ /////////////
void TIMER_vinit_overflow_interrupt (void);
void TIMER_vinit_CTC_interrupt (void);
void TIMER_vgeneration_signal_non_PWM (void);
void TIMER_vgeneration_signal_Fast_PWM (void);
void TIMER_vgeneration_signal_Phase_Correct_PWM (void);

//////////////// ___timer_2___ /////////////
void TIMER2_vinit_overflow_interrupt(void);


#endif /* TIMER_H_ */