################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/app/board/reg_server.c 

OBJS += \
./src/app/board/reg_server.o 

C_DEPS += \
./src/app/board/reg_server.d 


# Each subdirectory must supply rules for building sources it contributes
src/app/board/%.o: ../src/app/board/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C Compiler'
	$(CC) -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


