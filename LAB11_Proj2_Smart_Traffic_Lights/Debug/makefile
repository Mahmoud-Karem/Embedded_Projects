################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include MCAL/TIMER0/subdir.mk
-include MCAL/PORT/subdir.mk
-include MCAL/GIE/subdir.mk
-include MCAL/EXTI/subdir.mk
-include MCAL/DIO/subdir.mk
-include HAL/SWITCH/subdir.mk
-include HAL/SSD/subdir.mk
-include HAL/LED/subdir.mk
-include HAL/CLCD/subdir.mk
-include APP/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
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
LSS += \
On_Demand_Traffic_Light_Control.lss \

FLASH_IMAGE += \
On_Demand_Traffic_Light_Control.hex \

SIZEDUMMY += \
sizedummy \


# All Target
all: On_Demand_Traffic_Light_Control.elf secondary-outputs

# Tool invocations
On_Demand_Traffic_Light_Control.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,On_Demand_Traffic_Light_Control.map -mmcu=atmega32 -o "On_Demand_Traffic_Light_Control.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

On_Demand_Traffic_Light_Control.lss: On_Demand_Traffic_Light_Control.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S On_Demand_Traffic_Light_Control.elf  >"On_Demand_Traffic_Light_Control.lss"
	@echo 'Finished building: $@'
	@echo ' '

On_Demand_Traffic_Light_Control.hex: On_Demand_Traffic_Light_Control.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex On_Demand_Traffic_Light_Control.elf  "On_Demand_Traffic_Light_Control.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: On_Demand_Traffic_Light_Control.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 On_Demand_Traffic_Light_Control.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) On_Demand_Traffic_Light_Control.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
