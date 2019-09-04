################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/livro/Livro.cpp 

OBJS += \
./src/livro/Livro.o 

CPP_DEPS += \
./src/livro/Livro.d 


# Each subdirectory must supply rules for building sources it contributes
src/livro/%.o: ../src/livro/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


