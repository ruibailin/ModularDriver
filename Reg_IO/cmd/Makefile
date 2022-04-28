################################################################################
# Automatically-generated file. Do not edit!
################################################################################


RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/app/board/skt/subdir.mk
-include src/app/board/lib/subdir.mk
-include src/app/board/subdir.mk
-include src/app/subdir.mk
-include subdir.mk
-include objects.mk


# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: rbl_reg.exe

# Tool invocations
rbl_reg.exe: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GUN C Linker'
	$(CC)  -o "rbl_reg.exe" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

		
# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS) rbl_reg.exe
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

