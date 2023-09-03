/*linker_script_cortexM3.s 
Eng.Mohamed Elatar*/ 

MEMORY
{
	Flash(RX) : ORIGIN = 0X08000000, LENGTH = 128K
	SRam(RWX) : ORIGIN = 0X20000000, LENGTH = 20K
}
SECTIONS
{
	.text : 
	{
		_S_text = .;
		*(.vectors*)
		*(.text*)
		*(.rodata)
		_E_text = .;
	}>Flash

	.data :
	{
		. = ALIGN(4);
		_S_Data = . ;
		*(.data)
		*(.data.*)
		_E_Data = . ;
	}>SRam AT> Flash

	.bss :
	{
		_S_Bss = . ;
		*(.bss)
		_E_Bss = . ;

		. = ALIGN(4);
		. = . + 0X1000 ;
		max_heap = . ;

		. = ALIGN(4);
		. = . + 0X1000 ;
		stack_top = . ;
	}>SRam
}