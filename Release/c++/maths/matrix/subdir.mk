################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../c++/maths/matrix/matrix.cpp 

OBJS += \
./c++/maths/matrix/matrix.o 

CPP_DEPS += \
./c++/maths/matrix/matrix.d 


# Each subdirectory must supply rules for building sources it contributes
c++/maths/matrix/%.o: ../c++/maths/matrix/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/include -I/usr/include/python2.5 -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


