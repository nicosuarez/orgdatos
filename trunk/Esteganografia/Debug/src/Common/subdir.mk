################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Common/CompressionManager.cpp \
../src/Common/Console.cpp \
../src/Common/Date.cpp \
../src/Common/EncriptationManager.cpp \
../src/Common/FileSystem.cpp \
../src/Common/FreeSpaceManager.cpp \
../src/Common/ImageManager.cpp \
../src/Common/Message.cpp \
../src/Common/MessageManager.cpp \
../src/Common/PasswordManager.cpp \
../src/Common/Space.cpp \
../src/Common/StrToken.cpp 

OBJS += \
./src/Common/CompressionManager.o \
./src/Common/Console.o \
./src/Common/Date.o \
./src/Common/EncriptationManager.o \
./src/Common/FileSystem.o \
./src/Common/FreeSpaceManager.o \
./src/Common/ImageManager.o \
./src/Common/Message.o \
./src/Common/MessageManager.o \
./src/Common/PasswordManager.o \
./src/Common/Space.o \
./src/Common/StrToken.o 

CPP_DEPS += \
./src/Common/CompressionManager.d \
./src/Common/Console.d \
./src/Common/Date.d \
./src/Common/EncriptationManager.d \
./src/Common/FileSystem.d \
./src/Common/FreeSpaceManager.d \
./src/Common/ImageManager.d \
./src/Common/Message.d \
./src/Common/MessageManager.d \
./src/Common/PasswordManager.d \
./src/Common/Space.d \
./src/Common/StrToken.d 


# Each subdirectory must supply rules for building sources it contributes
src/Common/%.o: ../src/Common/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -Wno-deprecated -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


