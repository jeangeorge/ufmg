################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/transacao/Emprestimo.cpp \
../src/transacao/Reserva.cpp 

OBJS += \
./src/transacao/Emprestimo.o \
./src/transacao/Reserva.o 

CPP_DEPS += \
./src/transacao/Emprestimo.d \
./src/transacao/Reserva.d 


# Each subdirectory must supply rules for building sources it contributes
src/transacao/%.o: ../src/transacao/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


