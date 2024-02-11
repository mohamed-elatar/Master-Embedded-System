################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL := cmd.exe
RM := rm -rf

USER_OBJS :=

LIBS := 
PROJ := 

O_SRCS := 
C_SRCS := 
S_SRCS := 
S_UPPER_SRCS := 
OBJ_SRCS := 
ASM_SRCS := 
PREPROCESSING_SRCS := 
OBJS := 
OBJS_AS_ARGS := 
C_DEPS := 
C_DEPS_AS_ARGS := 
EXECUTABLES := 
OUTPUT_FILE_PATH :=
OUTPUT_FILE_PATH_AS_ARGS :=
AVR_APP_PATH :=$$$AVR_APP_PATH$$$
QUOTE := "
ADDITIONAL_DEPENDENCIES:=
OUTPUT_FILE_DEP:=

# Every subdirectory with source files must be described here
SUBDIRS :=  \
../FreeRTOS


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../dio.c \
../FreeRTOS/event_groups.c \
../FreeRTOS/heap_2.c \
../FreeRTOS/list.c \
../FreeRTOS/port.c \
../FreeRTOS/queue.c \
../FreeRTOS/tasks.c \
../Keybad.c \
../lcd.c \
../Message_Queue_FreeRTOS.c


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
dio.o \
FreeRTOS/event_groups.o \
FreeRTOS/heap_2.o \
FreeRTOS/list.o \
FreeRTOS/port.o \
FreeRTOS/queue.o \
FreeRTOS/tasks.o \
Keybad.o \
lcd.o \
Message_Queue_FreeRTOS.o


OBJS_AS_ARGS +=  \
dio.o \
FreeRTOS/event_groups.o \
FreeRTOS/heap_2.o \
FreeRTOS/list.o \
FreeRTOS/port.o \
FreeRTOS/queue.o \
FreeRTOS/tasks.o \
Keybad.o \
lcd.o \
Message_Queue_FreeRTOS.o


C_DEPS +=  \
dio.d \
FreeRTOS/event_groups.d \
FreeRTOS/heap_2.d \
FreeRTOS/list.d \
FreeRTOS/port.d \
FreeRTOS/queue.d \
FreeRTOS/tasks.d \
Keybad.d \
lcd.d \
Message_Queue_FreeRTOS.d


C_DEPS_AS_ARGS +=  \
dio.d \
FreeRTOS/event_groups.d \
FreeRTOS/heap_2.d \
FreeRTOS/list.d \
FreeRTOS/port.d \
FreeRTOS/queue.d \
FreeRTOS/tasks.d \
Keybad.d \
lcd.d \
Message_Queue_FreeRTOS.d


OUTPUT_FILE_PATH +=Message_Queue_FreeRTOS.elf

OUTPUT_FILE_PATH_AS_ARGS +=Message_Queue_FreeRTOS.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

# AVR32/GNU C Compiler





















./%.o: .././%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : (AVR_8_bit_GNU_Toolchain_3.4.1_830) 4.6.2
	$(QUOTE)C:\Program Files (x86)\Atmel\Atmel Studio 6.0\extensions\Atmel\AVRGCC\3.4.1.95\AVRToolchain\bin\avr-gcc.exe$(QUOTE) -funsigned-char -funsigned-bitfields -O1 -fpack-struct -fshort-enums -g2 -gdwarf-2 -Wall -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"  -mmcu=atmega32   -o"$@" "$<" 
	@echo Finished building: $<

FreeRTOS/%.o: ../FreeRTOS/%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : (AVR_8_bit_GNU_Toolchain_3.4.1_830) 4.6.2
	$(QUOTE)C:\Program Files (x86)\Atmel\Atmel Studio 6.0\extensions\Atmel\AVRGCC\3.4.1.95\AVRToolchain\bin\avr-gcc.exe$(QUOTE) -funsigned-char -funsigned-bitfields -O1 -fpack-struct -fshort-enums -g2 -gdwarf-2 -Wall -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"  -mmcu=atmega32   -o"$@" "$<" 
	@echo Finished building: $<



# AVR32/GNU Preprocessing Assembler



# AVR32/GNU Assembler




ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: $(OUTPUT_FILE_PATH) $(ADDITIONAL_DEPENDENCIES)

$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP)
	@echo Building target: $@
	@echo Invoking: AVR/GNU Linker : (AVR_8_bit_GNU_Toolchain_3.4.1_830) 4.6.2
	$(QUOTE)C:\Program Files (x86)\Atmel\Atmel Studio 6.0\extensions\Atmel\AVRGCC\3.4.1.95\AVRToolchain\bin\avr-gcc.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -Wl,-Map="Message_Queue_FreeRTOS.map" -Wl,--start-group -Wl,-lm  -Wl,--end-group  -mmcu=atmega32  
	@echo Finished building target: $@
	"C:\Program Files (x86)\Atmel\Atmel Studio 6.0\extensions\Atmel\AVRGCC\3.4.1.95\AVRToolchain\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature  "Message_Queue_FreeRTOS.elf" "Message_Queue_FreeRTOS.hex"
	"C:\Program Files (x86)\Atmel\Atmel Studio 6.0\extensions\Atmel\AVRGCC\3.4.1.95\AVRToolchain\bin\avr-objcopy.exe" -j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings -O ihex "Message_Queue_FreeRTOS.elf" "Message_Queue_FreeRTOS.eep" || exit 0
	"C:\Program Files (x86)\Atmel\Atmel Studio 6.0\extensions\Atmel\AVRGCC\3.4.1.95\AVRToolchain\bin\avr-objdump.exe" -h -S "Message_Queue_FreeRTOS.elf" > "Message_Queue_FreeRTOS.lss"
	"C:\Program Files (x86)\Atmel\Atmel Studio 6.0\extensions\Atmel\AVRGCC\3.4.1.95\AVRToolchain\bin\avr-objcopy.exe" -O srec -R .eeprom -R .fuse -R .lock -R .signature  "Message_Queue_FreeRTOS.elf" "Message_Queue_FreeRTOS.srec"
	"C:\Program Files (x86)\Atmel\Atmel Studio 6.0\extensions\Atmel\AVRGCC\3.4.1.95\AVRToolchain\bin\avr-size.exe" "Message_Queue_FreeRTOS.elf"
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS)$(C_DEPS_AS_ARGS) $(EXECUTABLES) 
	rm -rf "Message_Queue_FreeRTOS.elf" "Message_Queue_FreeRTOS.a" "Message_Queue_FreeRTOS.hex" "Message_Queue_FreeRTOS.lss" "Message_Queue_FreeRTOS.eep" "Message_Queue_FreeRTOS.map" "Message_Queue_FreeRTOS.srec"
	