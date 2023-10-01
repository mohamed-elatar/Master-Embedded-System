 #***********************************************
 # @file           : makefile	  				*
 # @author         : mohamed elatar             *
 # @Data           : 24/9/2023                  *
 # ARM Cortex M3   : Stm32f103C6                *
 #***********************************************

CC= arm-none-eabi-
CPU= -mthumb -mcpu=cortex-m3 -gdwarf-2 -g
INC= -I .
LIB= 
SRC= $(wildcard *.c)
OBJ_SRC = $(SRC:.c=.o) 
AS= $(wildcard *.s)
OBJ_AS = $(AS:.s=.o)

PATH_DUMP = "C:\Program Files\Cppcheck\addons\misra.py"
SCR_DUMP = $(wildcard *.c)
DUMP = $(SCR_DUMP:.c=.c.dump)

PROJECT_NAME= pressure_project

All : $(PROJECT_NAME).bin
	@echo "-----> Build is Done <-----"
	
%.o : %.c 
	$(CC)gcc.exe -c $(CPU) $(INC) $< -o $@

%.o : %.s 
	$(CC)as.exe -s $(CPU)  $< -o $@ 

$(PROJECT_NAME).elf : $(OBJ_AS) $(OBJ_SRC)
	$(CC)ld.exe -T linker_script.ld $(OBJ_AS) $(OBJ_SRC) -o $@ -Map=map_file.map
	cp $(PROJECT_NAME).elf $(PROJECT_NAME).axf

$(PROJECT_NAME).bin : $(PROJECT_NAME).elf
	$(CC)objcopy.exe -O binary $< $@

clean :
	rm *.o *.bin *.elf
	@echo "-----> Remove Executable is Done <-----" 

clean_all :
	rm *.o *.bin *.elf *.asm *.axf *.map *.txt *.dump
	@echo "-----> Remove All is Done <-----" 

clean_object :
	rm -f $(OBJ_SRC)
	@echo "-----> Remove object is Done <-----" 

misra : 
	cppcheck --dump $(SCR_DUMP)
	python $(PATH_DUMP) $(DUMP)

symbol : 
	$(CC)nm.exe *.o > All_Object_symbols.txt
	$(CC)nm.exe *.elf > executable.txt

size :
	$(CC)size.exe *.o *.elf |tee size.txt

section :
	$(CC)objdump -h  *.o *.elf > section_table.txt