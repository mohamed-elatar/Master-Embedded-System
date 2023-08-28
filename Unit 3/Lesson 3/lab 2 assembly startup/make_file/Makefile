#@ copyright : mohamed elatar
CC=arm-none-eabi-
CFLAGS=-mthumb -mcpu=cortex-m3 -gdwarf-2
INCS=-I .
LIBS=
SRC = $(wildcard *.c)
OBJ_SRC= $(SRC:.c=.o)
AS= $(wildcard *.s)
OBJ_AS= $(AS:.s=.o)
PROJECT_NAME=learn-in-depth-cortex-m3

all: $(PROJECT_NAME).bin
	@echo "---> Build Is Done <----"

%.o: %.s
	$(CC)as.exe $(CFLAGS) $< -o $@

%.o: %.c
	$(CC)gcc.exe -c $(CFLAGS) $(INCS) $< -o $@

$(PROJECT_NAME).elf: $(OBJ_SRC) $(OBJ_AS)
	$(CC)ld.exe -T Linker_Script.ld $(OBJ_SRC) $(OBJ_AS) -o $@ -Map=Map_file.map

$(PROJECT_NAME).bin: $(PROJECT_NAME).elf 
	$(CC)objcopy.exe -O binary $< $@

clean_all:
	rm *.o *.elf *.bin

clean:
	rm -rf *.o *~
	@echo "Everything .o clean"