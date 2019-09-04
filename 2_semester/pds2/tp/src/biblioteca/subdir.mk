################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/biblioteca/Biblioteca.cpp 

OBJS += \
./src/biblioteca/Biblioteca.o 

CPP_DEPS += \
./src/biblioteca/Biblioteca.d 


# Each subdirectory must supply rules for building sources it contributes
src/biblioteca/%.o: ../src/biblioteca/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


