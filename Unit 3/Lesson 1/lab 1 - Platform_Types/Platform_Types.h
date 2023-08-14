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

typedef _Bool 		_bool;
typedef int8_t 		sint8;
typedef uint8_t 	uint8;
typedef int16_t 	sint16;
typedef uint16_t 	uint16;
typedef int32_t 	sint32;
typedef uint32_t 	uint32;
typedef int64_t 	sint64;
typedef uint64_t 	uint64;


typedef volatile int8_t 	vint8;
typedef volatile uint8_t 	vuint8;
typedef volatile int16_t 	vint16;
typedef volatile uint16_t 	vuint16;
typedef volatile int32_t 	vint32;
typedef volatile uint32_t 	vuint32;
typedef volatile int64_t 	vint64;
typedef volatile uint64_t 	vuint64;


#endif /* PLATFORM_TYPES_H_ */
