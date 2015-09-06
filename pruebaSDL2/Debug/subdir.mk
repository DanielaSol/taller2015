################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Game.cpp \
../GameObject.cpp \
../Player.cpp \
../TextureManager.cpp \
../main.cpp 

OBJS += \
./Game.o \
./GameObject.o \
./Player.o \
./TextureManager.o \
./main.o 

CPP_DEPS += \
./Game.d \
./GameObject.d \
./Player.d \
./TextureManager.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


