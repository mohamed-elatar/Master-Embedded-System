/*
 * Platform_Types.h
 *
 *  Created on: Aug 13, 2023
 *      Author: mohamed elatar
 */

#ifndef PLATFORM_TYPES_H_
#define PLATFORM_TYPES_H_

#include <stdbool.h>
#include <stdint.h>

#define CPU_TYPE 			CPU_TYPE_64
#define CPU_BIT_OREDER 		LSB_FIRST
#define CPU_BYTE_ORDER 		HIGH_BYTE_FIRST

#ifndef _Bool
#define _Bool unsigned char
#endif

#ifndef FALSE
#define FALSE 		(_bool)false
#endif /* FALSE */

#ifndef TRUE
#define TRUE 		(_bool)true
#endif /* TRUE */

typedef _Bool 						_bool;
typedef signed char 				int8;
typedef unsigned char				uint8;
typedef signed short 				sint16;
typedef unsigned short 				uint16;
typedef signed int 					sint32;
typedef unsigned int 				uint32;
typedef signed long long 			sint64;
typedef unsigned long long 			uint64;


typedef volatile signed char 		vint8;
typedef volatile unsigned char 		vuint8;
typedef volatile signed short  		vint16;
typedef volatile unsigned short  	vuint16;
typedef volatile signed int  		vint32;
typedef volatile unsigned int  		vuint32;
typedef volatile signed long long 	vint64;
typedef volatile unsigned long long vuint64;

#endif /* PLATFORM_TYPES_H_ */
