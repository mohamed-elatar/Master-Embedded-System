 /***********************************************
 * @file           : standard_macros.h			*
 * @author         : mohamed elatar             *
 * @Data           : Oct 30, 2023				*
 ************************************************/


#ifndef STANDARD_MACROS_H_
#define STANDARD_MACROS_H_


#define size_register 8
#define CLR_BIT(REG,BIT)        			REG &= ~(1<<BIT)
#define CLR_NIBBLE(REG,START_NIBBLE)        REG &= ~(0XF  << START_NIBBLE)
#define CLR_BYTE(REG,START_BYTE)        	REG &= ~(0XFF << START_BYTE)
#define CLR_2BYTE(REG,START_2BYTE)        	REG &= ~(0XFFFF << START_2BYTE)
#define CLR_4BYTE(REG)			        	REG &= ~(0XFFFFFFFF)


#define SET_BIT(REG,BIT)        			REG |= (1<<BIT)
#define SET_NIBBLE(REG,START_NIBBLE)        REG |= (0XF  << START_NIBBLE)
#define SET_BYTE(REG,START_BYTE)        	REG |= (0XFF << START_BYTE)
#define SET_2BYTE(REG,START_2BYTE)        	REG |= (0XFFFF << START_2BYTE)
#define SET_4BYTE(REG)			        	REG |= (0XFFFFFFFF)


#define READ_BIT(REG,BIT)       			( (REG & (1<<BIT)) >> BIT )
#define READ_NIBBLE(REG , START_NIBBLE)		( (REG & (0XF << START_NIBBLE)) >> START_NIBBLE )
#define READ_BYTE(REG , START_BYTE)			( (REG & (0XFF << START_BYTE)) >> START_BYTE )

#define TOG_BIT(REG,BIT)        			REG ^= (1 << BIT)
#define TOG_NIBBLE(REG,START_NIBBLE)        REG ^= (0XF << START_NIBBLE)
#define TOG_BYTE(REG,START_BYTE)        	REG ^= (0XFF << START_BYTE)
#define TOG_2BYTE(REG,START_2BYTE)        	REG ^= (0XFFFF << START_2BYTE)
#define TOG_4BYTE(REG,BIT)        			REG ^= (0XFFFFFFFF)

#define BIT_IS_SET(REG,BIT)     			( (REG & (1<<BIT)) >> BIT )
#define BIT_IS_CLR(REG,BIT)     			!( (REG & (1<<BIT)) >> BIT )
#define ROL(REG,NUM)            			REG = ( (REG<<NUM) | (REG>>(size_register-NUM)) )
#define ROR(REG,NUM)            			REG = ( (REG>>NUM) | (REG<<(size_register-NUM)) )

typedef unsigned char         uint8_t;          /*           0 .. 255              */
typedef signed char           sint8_t;          /*        -128 .. +127             */
typedef unsigned short        uint16_t;         /*           0 .. 65535            */
typedef signed short          sint16_t;         /*      -32768 .. +32767           */
typedef unsigned long         uint32_t;         /*           0 .. 4294967295       */
typedef signed long           sint32_t;         /* -2147483648 .. +2147483647      */
typedef unsigned long long    uint64_t;         /*       0 .. 18446744073709551615  */
typedef signed long long      sint64_t;         /* -9223372036854775808 .. 9223372036854775807 */
typedef float                 float32_t;
typedef double                float64_t;

#endif /* STANDARD_MACROS_H_ */
