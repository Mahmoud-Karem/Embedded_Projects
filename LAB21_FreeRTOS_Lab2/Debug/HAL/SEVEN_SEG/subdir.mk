################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/SEVEN_SEG/SEVEN_SEG.c \
../HAL/SEVEN_SEG/SEVEN_SEG_Config.c 

OBJS += \
./HAL/SEVEN_SEG/SEVEN_SEG.o \
./HAL/SEVEN_SEG/SEVEN_SEG_Config.o 

C_DEPS += \
./HAL/SEVEN_SEG/SEVEN_SEG.d \
./HAL/SEVEN_SEG/SEVEN_SEG_Config.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/SEVEN_SEG/%.o: ../HAL/SEVEN_SEG/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


