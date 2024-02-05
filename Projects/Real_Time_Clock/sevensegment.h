/*
 * _7segment.h
 *
 * Created: 4/29/2023 1:25:53 PM
 *  Author: mohamed elatar
 */ 


#ifndef SevenSegmentSEGMENT_H_
#define SevenSegmentSEGMENT_H_


void SevenSegment_vinit (char portname , char numberpin);
void SevenSegment_vwrite_eg (char portname , char number);
void SevenSegment_vwrite_ar (char portname , char number);

void SevenSegment_BCD_vinit (char portname , char start_num_pin);
void SevenSegment_BCD_vwrite_lownibble (char portname , char val);
void SevenSegment_BCD_vwrite_highnibble (char portname , char val);

#endif /* 7SEGMENT_H_ */