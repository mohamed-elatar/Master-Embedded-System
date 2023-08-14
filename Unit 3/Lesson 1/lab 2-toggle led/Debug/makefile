################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
lab\ 2-toggle\ led.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
lab\ 2-toggle\ led.list \

OBJCOPY_HEX += \
lab\ 2-toggle\ led.hex \

OBJCOPY_BIN += \
lab\ 2-toggle\ led.bin \


# All Target
all: lab\ 2-toggle\ led.elf secondary-outputs

# Tool invocations
lab\ 2-toggle\ led.elf: $(OBJS) $(USER_OBJS) D:\ES\ -\ Keroles\Unit\ 3\lesson\ 1\stm\lab\ 2-toggle\ led\STM32F103C6TX_FLASH.ld
	arm-none-eabi-gcc -o "lab 2-toggle led.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"D:\ES - Keroles\Unit 3\lesson 1\stm\lab 2-toggle led\STM32F103C6TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="lab 2-toggle led.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

lab\ 2-toggle\ led.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "lab 2-toggle led.list"
	@echo 'Finished building: $@'
	@echo ' '

lab\ 2-toggle\ led.hex: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "lab 2-toggle led.hex"
	@echo 'Finished building: $@'
	@echo ' '

lab\ 2-toggle\ led.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "lab 2-toggle led.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
