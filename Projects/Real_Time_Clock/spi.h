/*
 * spi.h
 *
 * Created: 6/7/2023 2:52:39 AM
 *  Author: moham
 */ 


#ifndef SPI_H_
#define SPI_H_

void SPI_Master_vinit(void);
void SPI_Slave_vinit(void);
unsigned char SPI_Master_u8transamit (unsigned char data);
unsigned char SPI_Slave_u8receive (unsigned char data);
void SPI_Master_vtransamit_string (unsigned char *ptr);

void SPI_Master_transamit_MAX7221 (unsigned char cmd , unsigned char data);


#endif /* SPI_H_ */