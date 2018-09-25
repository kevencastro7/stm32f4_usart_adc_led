################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../utils/adc.c \
../utils/debug.c \
../utils/led.c \
../utils/port.c 

OBJS += \
./utils/adc.o \
./utils/debug.o \
./utils/led.o \
./utils/port.o 

C_DEPS += \
./utils/adc.d \
./utils/debug.d \
./utils/led.d \
./utils/port.d 


# Each subdirectory must supply rules for building sources it contributes
utils/%.o: ../utils/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32F407VGTx -DSTM32F4 -DSTM32F4DISCOVERY -DSTM32 -DDEBUG -DUSE_STDPERIPH_DRIVER -DSTM32F40XX -DSTM32F40_41xxx -I"/home/kevencastro7/workspace/nighthawk/inc" -I"/home/kevencastro7/workspace/nighthawk/utils" -I"/home/kevencastro7/workspace/nighthawk/StdPeriph_Driver/inc" -I"/home/kevencastro7/workspace/nighthawk/CMSIS/device" -I"/home/kevencastro7/workspace/nighthawk/CMSIS/core" -I"/home/kevencastro7/workspace/nighthawk/Utilities" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


