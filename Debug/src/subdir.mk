################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/GestorMensajes.cpp \
../src/GestorUsuarios.cpp \
../src/mensaje.cpp \
../src/svr_connect.cpp \
../src/svr_interfaz.cpp \
../src/svr_msg.cpp \
../src/svr_stub.cpp \
../src/svr_user.cpp \
../src/svr_util.cpp \
../src/ui.cpp \
../src/usuario.cpp 

OBJS += \
./src/GestorMensajes.o \
./src/GestorUsuarios.o \
./src/mensaje.o \
./src/svr_connect.o \
./src/svr_interfaz.o \
./src/svr_msg.o \
./src/svr_stub.o \
./src/svr_user.o \
./src/svr_util.o \
./src/ui.o \
./src/usuario.o 

CPP_DEPS += \
./src/GestorMensajes.d \
./src/GestorUsuarios.d \
./src/mensaje.d \
./src/svr_connect.d \
./src/svr_interfaz.d \
./src/svr_msg.d \
./src/svr_stub.d \
./src/svr_user.d \
./src/svr_util.d \
./src/ui.d \
./src/usuario.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


