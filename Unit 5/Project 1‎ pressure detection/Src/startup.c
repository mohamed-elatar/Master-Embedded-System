 /***********************************************
 * @file           : startup.c   				*
 * @author         : mohamed elatar             *
 * @Data           : 24/9/2023                  *
 * ARM Cortex M3   : Stm32f103C6                *
 ************************************************/

extern int main();
extern unsigned int S_Text;
extern unsigned int E_Text;
extern unsigned int S_Data;
extern unsigned int E_Data;
extern unsigned int S_Bss;
extern unsigned int E_Bss;

//prototype functions
void Default_Handler();
void Reset();

void NMI_Handler(void) __attribute__((weak , alias("Default_Handler")));
void H_Fault_Handler(void) __attribute__((weak , alias("Default_Handler")));
void MM_Fault_Handler(void) __attribute__((weak , alias("Default_Handler")));
void Bus_Fault(void) __attribute__((weak , alias("Default_Handler")));
void Usage_Fault_Handler(void) __attribute__((weak , alias("Default_Handler")));


unsigned int stack_top[256]; //store in .bss elf (block start by symbol)

void (* const vector_arr[])() __attribute__((section(".vectors"))) = {
	(void(*)()) (stack_top + sizeof(stack_top)),
	&Reset,
	&NMI_Handler,
	&H_Fault_Handler,
	&MM_Fault_Handler,
	&Bus_Fault,
	&Usage_Fault_Handler
};

void Default_Handler()
{
	Reset();
}

void Reset()
{
	int i;
	
	unsigned int size_data = ((unsigned int)&E_Data - (unsigned int)&S_Data);
	unsigned int size_bss = ((unsigned int)&E_Bss - (unsigned int)&S_Bss);

	unsigned char * p_src = (unsigned char*)&E_Text;
	unsigned char * p_des = (unsigned char*)&S_Data;

	for (i = 0; i < size_data; ++i)
	{
		*((unsigned char*)p_des++) = *((unsigned char*)p_src++);
	}

	p_des = (unsigned char*)&S_Bss;
	for (i = 0; i < size_bss; ++i)
	{
		*((unsigned char*)p_des++) = (unsigned char)0;
	}

	//call main() fun
	main();
}