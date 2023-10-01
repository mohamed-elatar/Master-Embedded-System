 /***********************************************
 * @file           : linker_script   			*
 * @author         : mohamed elatar             *
 * @Data           : 24/9/2023                  *
 * ARM Cortex M3   : Stm32f103C6                *
 ************************************************/

ENTRY(Reset)

MEMORY 
{
	Flash(RX) : ORIGIN = 0X08000000, LENGTH = 128K
	SRam(RWX) : ORIGIN = 0X20000000, LENGTH = 20K
}

SECTIONS
{
	.text :
	{
		. = ALIGN(4);
		S_Text = .;
		*(.vectors*)
		*(.text*)
		*(.rodata*)
		E_Text = .;
	}>Flash

	.data :
	{
		. = ALIGN(4);
		S_Data = .;
		*(.data*)
		E_Data = .;
	}>SRam AT>Flash

	.bss :
	{	. = ALIGN(4);
		S_Bss = .;
		*(.bss*) *(.COMMON)
		E_Bss = .;
	}>SRam

}