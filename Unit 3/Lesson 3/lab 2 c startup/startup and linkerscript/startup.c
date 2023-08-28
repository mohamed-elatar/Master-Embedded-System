//learn-in-depth
//mohamed elatar
#include <stdint.h>
extern int main(void);
extern uint32_t _E_text;
extern uint32_t _S_Data;
extern uint32_t _E_Data;
extern uint32_t _S_Bss;
extern uint32_t _E_Bss;
extern uint32_t stack_top;


void Default_Handler();
void Rest_Handler (void);



void NMI_Handler(void) __attribute__((weak , alias("Default_Handler")));
void H_Fault_Handler(void) __attribute__((weak , alias("Default_Handler")));
void MM_Fault_Handler(void) __attribute__((weak , alias("Default_Handler")));
void Bus_Fault(void) __attribute__((weak , alias("Default_Handler")));
void Usage_Fault_Handler(void) __attribute__((weak , alias("Default_Handler")));

uint32_t Vectors[] __attribute__((section(".vectors"))) = {
	(uint32_t) &stack_top,
	(uint32_t) &Rest_Handler,
	(uint32_t) &NMI_Handler,
	(uint32_t) &H_Fault_Handler,
	(uint32_t) &MM_Fault_Handler,
	(uint32_t) &Bus_Fault,
	(uint32_t) &Usage_Fault_Handler,
};

void Default_Handler()
{
	Rest_Handler();
}

void Rest_Handler (void)
{
	uint32_t i;
	//copy data section
	uint32_t data_size = (uint8_t*)&_E_Data - (uint8_t*)&_S_Data ;
	uint8_t *p_src = (uint8_t*)&_E_text ;
	uint8_t *p_des = (uint8_t*)&_S_Data ;
	for (i = 0; i < data_size; ++i)
	{
		*((uint8_t*)p_des++) = *((uint8_t*)p_src++);
	}

	// bss section reversed
	uint32_t bss_size = (uint8_t*)&_E_Bss - (uint8_t*)&_S_Bss ;
	p_des = (uint8_t*)&_S_Bss ;
	for (i = 0; i < bss_size; ++i)
	{
		*((uint8_t*)p_des++) = (uint8_t)0;
	}	

	// jump to main
	main();
}

