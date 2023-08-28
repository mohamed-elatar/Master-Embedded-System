/*startup_cortexM3.s 
Eng.Mohamed Elatar*/ 

ENTRY(_reset)
MEMORY
{
	Flash(RX) : ORIGIN = 0X08000000, LENGTH = 128K
	SRam(RWX) : ORIGIN = 0X20000000, LENGTH = 20K
}
SECTIONS
{
	.text : 
	{
		*(.vectors*)
		*(.text*)
		*(.rodata)
	}>Flash

	.data :
	{
		*(.data)
	}>Flash

	.bss :
	{
		*(.bss)
	}>SRam
}