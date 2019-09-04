################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/tela/Opcao.cpp \
../src/tela/Tela.cpp \
../src/tela/TelaInicial.cpp \
../src/tela/TelaLivros.cpp \
../src/tela/TelaPrincipal.cpp \
../src/tela/TelaTransacoes.cpp \
../src/tela/TelaUsuarios.cpp 

OBJS += \
./src/tela/Opcao.o \
./src/tela/Tela.o \
./src/tela/TelaInicial.o \
./src/tela/TelaLivros.o \
./src/tela/TelaPrincipal.o \
./src/tela/TelaTransacoes.o \
./src/tela/TelaUsuarios.o 

CPP_DEPS += \
./src/tela/Opcao.d \
./src/tela/Tela.d \
./src/tela/TelaInicial.d \
./src/tela/TelaLivros.d \
./src/tela/TelaPrincipal.d \
./src/tela/TelaTransacoes.d \
./src/tela/TelaUsuarios.d 


# Each subdirectory must supply rules for building sources it contributes
src/tela/%.o: ../src/tela/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


