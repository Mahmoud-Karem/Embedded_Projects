################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CLCD_program.c \
../DIO_program.c \
../SSD_program.c \
../SW_program.c \
../main.c \
../mode_prg.c 

OBJS += \
./CLCD_program.o \
./DIO_program.o \
./SSD_program.o \
./SW_program.o \
./main.o \
./mode_prg.o 

C_DEPS += \
./CLCD_program.d \
./DIO_program.d \
./SSD_program.d \
./SW_program.d \
./main.d \
./mode_prg.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


