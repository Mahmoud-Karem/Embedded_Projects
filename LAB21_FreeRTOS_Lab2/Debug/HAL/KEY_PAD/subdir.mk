################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/KEY_PAD/KEY_PAD.c \
../HAL/KEY_PAD/KEY_PAD_config.c 

OBJS += \
./HAL/KEY_PAD/KEY_PAD.o \
./HAL/KEY_PAD/KEY_PAD_config.o 

C_DEPS += \
./HAL/KEY_PAD/KEY_PAD.d \
./HAL/KEY_PAD/KEY_PAD_config.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/KEY_PAD/%.o: ../HAL/KEY_PAD/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


