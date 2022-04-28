################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/test/subdir.mk
-include src/sw_cve/5cve/subdir.mk
-include src/sw_cve/4reg/subdir.mk
-include src/sw_cve/3opr/subdir.mk
-include src/sw_cve/2blk/subdir.mk
-include src/sw_cve/subdir.mk
-include src/hw_cve/3opr/subdir.mk
-include src/hw_cve/3cve/subdir.mk
-include src/hw_cve/2reg/subdir.mk
-include src/hw_cve/1ram/subdir.mk
-include src/hw_cve/subdir.mk
-include src/app/2sdl/subdir.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: 6805_ive_app

# Tool invocations
6805_ive_app: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C++ Linker'
	g++ -L/usr/local/lib -o "6805_ive_app" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(CC_DEPS)$(C++_DEPS)$(EXECUTABLES)$(C_UPPER_DEPS)$(CXX_DEPS)$(OBJS)$(CPP_DEPS)$(C_DEPS) 6805_ive_app
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
