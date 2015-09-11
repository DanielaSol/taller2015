################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Game.cpp \
../GameObject.cpp \
../InputHandler.cpp \
../Map.cpp \
../TextureManager.cpp \
../Unit.cpp \
../main.cpp 

OBJS += \
./Game.o \
./GameObject.o \
./InputHandler.o \
./Map.o \
./TextureManager.o \
./Unit.o \
./main.o 

CPP_DEPS += \
./Game.d \
./GameObject.d \
./InputHandler.d \
./Map.d \
./TextureManager.d \
./Unit.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


