#include "uart.h"
#define UART0DR *((volatile unsigned int* const)((unsigned int*)0x101f1000))
void UART_Vsend_string(unsigned char * P_TX)
{
	while(*P_TX != 0)
	{
		UART0DR = (unsigned char)(*P_TX);
		P_TX++;
	}
}