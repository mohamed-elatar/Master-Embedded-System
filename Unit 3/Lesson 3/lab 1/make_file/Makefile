#@ copyright : mohamed elatar
CC=arm-none-eabi-
CFLAGS=-g -mcpu=arm926ej-s
INCS=-I .
LIBS=
SRC = $(wildcard *.c)
OBJ_SRC= $(SRC:.c=.o)
AS= $(wildcard *.s)
OBJ_AS= $(AS:.s=.o)
PROJECT_NAME=learn-in-depth

all: $(PROJECT_NAME).bin
	@echo "---> Build Is Done <----"

%.o: %.s
	$(CC)as.exe $(CFLAGS) $< -o $@

%.o: %.c
	$(CC)gcc.exe -c $(CFLAGS) $(INCS) $< -o $@

$(PROJECT_NAME).elf: $(OBJ_SRC) $(OBJ_AS)
	$(CC)ld.exe -T linker_script.ld $(OBJ_SRC) $(OBJ_AS) -o $@

$(PROJECT_NAME).bin: $(PROJECT_NAME).elf 
	$(CC)objcopy.exe -O binary $< $@

clean_all:
	rm *.o *.elf *.bin

clean:
	rm -rf *.o *~
	@echo "Everything .o clean"