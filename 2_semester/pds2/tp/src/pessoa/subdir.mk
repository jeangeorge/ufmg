################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/pessoa/Bibliotecario.cpp \
../src/pessoa/Pessoa.cpp \
../src/pessoa/Usuario.cpp 

OBJS += \
./src/pessoa/Bibliotecario.o \
./src/pessoa/Pessoa.o \
./src/pessoa/Usuario.o 

CPP_DEPS += \
./src/pessoa/Bibliotecario.d \
./src/pessoa/Pessoa.d \
./src/pessoa/Usuario.d 


# Each subdirectory must supply rules for building sources it contributes
src/pessoa/%.o: ../src/pessoa/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


