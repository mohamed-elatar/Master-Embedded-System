//learn-in-depth
//mohamed elatar
#include <stdint.h>
extern int main(void);
extern uint32_t _E_text;
extern uint32_t _S_Data;
extern uint32_t _E_Data;
extern uint32_t _S_Bss;
extern uint32_t _E_Bss;

void Default_Handler();
void Rest_Handler (void);

void NMI_Handler(void) __attribute__((weak , alias("Default_Handler")));
void H_Fault_Handler(void) __attribute__((weak , alias("Default_Handler")));
void MM_Fault_Handler(void) __attribute__((weak , alias("Default_Handler")));
void Bus_Fault(void) __attribute__((weak , alias("Default_Handler")));
void Usage_Fault_Handler(void) __attribute__((weak , alias("Default_Handler")));

static uint32_t stack_top[256]; // global un_init store in .bss
void (* const vectors_array[])() __attribute__((section(".vectors"))) = {
	(void (*)()) (stack_top + sizeof(stack_top)),
	&Rest_Handler,
	&NMI_Handler,
	&H_Fault_Handler,
	&MM_Fault_Handler,
	&Bus_Fault,
	&Usage_Fault_Handler,
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

