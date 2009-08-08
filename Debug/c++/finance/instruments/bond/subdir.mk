################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../c++/finance/instruments/bond/bond.cpp \
../c++/finance/instruments/bond/coupon.cpp 

CPP_DEPS += \
./c++/finance/instruments/bond/bond.d \
./c++/finance/instruments/bond/coupon.d 

OBJS += \
./c++/finance/instruments/bond/bond.o \
./c++/finance/instruments/bond/coupon.o 


# Each subdirectory must supply rules for building sources it contributes
c++/finance/instruments/bond/%.o: ../c++/finance/instruments/bond/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/sw/include/python2.5 -I/sw/include/boost-1_34_1 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


