/*
 * standard_macros.h
 *
 * Created: 4/25/2023 11:43:54 AM
 *  Author: moham
 */ 


#ifndef STANDARD_MACROS_H_
#define STANDARD_MACROS_H_


#define size_register 8
#define SET_BIT(REG,BIT)        REG |= (1<<BIT) 
#define CLR_BIT(REG,BIT)        REG &= (~(1<<BIT))
#define TOG_BIT(REG,BIT)        REG ^= (1<<BIT) 
#define READ_BIT(REG,BIT)       ( (REG & (1<<BIT)) >> BIT )            
#define BIT_IS_SET(REG,BIT)     ( (REG & (1<<BIT)) >> BIT ) 
#define BIT_IS_CLR(REG,BIT)     !( (REG & (1<<BIT)) >> BIT ) 
#define ROL(REG,NUM)            REG = ( (REG<<NUM) | (REG>>(size_register-NUM)) )
#define ROR(REG,NUM)            REG = ( (REG>>NUM) | (REG<<(size_register-NUM)) )
#endif /* STANDARD_MACROS_H_ */