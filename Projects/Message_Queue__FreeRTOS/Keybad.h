/*
 * Keybad.h
 *
 * Created: 5/6/2023 3:14:35 PM
 *  Author: moham
 */ 


#ifndef KEYBAD_H_
#define KEYBAD_H_


//-----------------------------
//Macros Configuration References
//-----------------------------
#define ROW_PORT 			'c'

#define R1 					0
#define R2 					1
#define R3 					2
#define R4 					3

#define COL_PORT 			'd'

#define C1 					4
#define C2 					5
#define C3 					6
#define C4 					7

#define NOT_PRESSED 		0xFF

void Keypad_vinit (void);
unsigned char Keypad_u8read(void);

#endif /* KEYBAD_H_ */