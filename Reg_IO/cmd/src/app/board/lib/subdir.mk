################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/app/board/lib/libregio.c 

OBJS += \
./src/app/board/lib/libregio.o 

C_DEPS += \
./src/app/board/lib/libregio.d 


# Each subdirectory must supply rules for building sources it contributes
src/app/board/lib/%.o: ../src/app/board/lib/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C Compiler'
	$(CC) -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


