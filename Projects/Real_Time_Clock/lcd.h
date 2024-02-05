/*
 * lcd.h
 *
 * Created: 5/4/2023 9:05:42 PM
 *  Author: mohamed elatar
 */ 


#ifndef LCD_H_
#define LCD_H_

void LCD_vinit();
void LCD_vsend_char(char char_send);
void LCD_vsend_cmd(char cmd_send);
static void Enable_bit (void);
void LCD_vsend_string(char *ptr);
void LCD_vsend_number (int num);
void LCD_vsend_real_number (float num);
void LCD_vClearScreen(void);
void LCD_vmove_cursor (char row , char column);
unsigned char LCD_u8read_busy_flag(void);

#endif /* LCD_H_ */