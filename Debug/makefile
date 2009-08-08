################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include c++/maths/matrix/subdir.mk
-include c++/maths/iteration/subdir.mk
-include c++/maths/interpolation/subdir.mk
-include c++/maths/basic/subdir.mk
-include c++/finance/instruments/swap/subdir.mk
-include c++/finance/instruments/bond/subdir.mk
-include c++/finance/curve/subdir.mk
-include c++/basic/array/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: libAnalyttlic.dylib

# Tool invocations
libAnalyttlic.dylib: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MacOS X C++ Linker'
	g++ -L/sw/lib/python2.5/config -L/sw/lib -dynamiclib -o "libAnalyttlic.dylib" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C_DEPS)$(CXX_DEPS)$(CPP_DEPS)$(CC_DEPS)$(OBJS)$(C_UPPER_DEPS)$(LIBRARIES)$(C++_DEPS) libAnalyttlic.dylib
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
