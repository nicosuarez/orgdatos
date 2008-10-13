################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Common/Commands.cpp \
../src/Common/CompressionManager.cpp \
../src/Common/EncriptationManager.cpp \
../src/Common/FreeSpaceManager.cpp \
../src/Common/ImageManager.cpp \
../src/Common/Message.cpp \
../src/Common/MessageManager.cpp \
../src/Common/Space.cpp 

OBJS += \
./src/Common/Commands.o \
./src/Common/CompressionManager.o \
./src/Common/EncriptationManager.o \
./src/Common/FreeSpaceManager.o \
./src/Common/ImageManager.o \
./src/Common/Message.o \
./src/Common/MessageManager.o \
./src/Common/Space.o 

CPP_DEPS += \
./src/Common/Commands.d \
./src/Common/CompressionManager.d \
./src/Common/EncriptationManager.d \
./src/Common/FreeSpaceManager.d \
./src/Common/ImageManager.d \
./src/Common/Message.d \
./src/Common/MessageManager.d \
./src/Common/Space.d 


# Each subdirectory must supply rules for building sources it contributes
src/Common/%.o: ../src/Common/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


