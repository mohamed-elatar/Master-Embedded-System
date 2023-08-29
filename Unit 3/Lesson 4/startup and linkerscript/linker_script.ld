/*linker_script_cortexM4.s 
Eng.Mohamed Elatar*/ 

MEMORY
{
	Flash(RX) : ORIGIN = 0X00000000, LENGTH = 512K
	SRam(RWX) : ORIGIN = 0X20000000, LENGTH = 512K
}
SECTIONS
{
	.text : 
	{
		. = ALIGN(4);
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
		_E_Data = . ;
	}>SRam AT> Flash

	.bss :
	{
		. = ALIGN(4);
		_S_Bss = . ;
		*(.bss)
		_E_Bss = . ;
	}>SRam
}