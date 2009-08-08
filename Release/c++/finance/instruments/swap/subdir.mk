################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../c++/finance/instruments/swap/irSwap.cpp 

OBJS += \
./c++/finance/instruments/swap/irSwap.o 

CPP_DEPS += \
./c++/finance/instruments/swap/irSwap.d 


# Each subdirectory must supply rules for building sources it contributes
c++/finance/instruments/swap/%.o: ../c++/finance/instruments/swap/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/include -I/usr/include/python2.5 -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


