#include "uart.h"
unsigned char string_1[100] = "learn-in-depth :<Mohamed>";
unsigned char const string_2[100] = "learn-in-depth :<Mohamed>";
int main()
{
	UART_Vsend_string(string_1);
}