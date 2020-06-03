################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Config/PB_cfg.c \
../Config/SSD_cfg.c \
../Config/dio_cfg.c \
../Config/tmr0_cfg.c 

OBJS += \
./Config/PB_cfg.o \
./Config/SSD_cfg.o \
./Config/dio_cfg.o \
./Config/tmr0_cfg.o 

C_DEPS += \
./Config/PB_cfg.d \
./Config/SSD_cfg.d \
./Config/dio_cfg.d \
./Config/tmr0_cfg.d 


# Each subdirectory must supply rules for building sources it contributes
Config/%.o: ../Config/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


