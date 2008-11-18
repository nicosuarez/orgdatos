################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/DataAccess/Registries/ExtensibleRelativeRegistry.cpp \
../src/DataAccess/Registries/FreeSpaceRegistry.cpp \
../src/DataAccess/Registries/ImgRegistry.cpp \
../src/DataAccess/Registries/ListImgRegistry.cpp \
../src/DataAccess/Registries/ListMsgRegistry.cpp \
../src/DataAccess/Registries/ListRegistry.cpp \
../src/DataAccess/Registries/MsgRegistry.cpp \
../src/DataAccess/Registries/TextRegistry.cpp 

OBJS += \
./src/DataAccess/Registries/ExtensibleRelativeRegistry.o \
./src/DataAccess/Registries/FreeSpaceRegistry.o \
./src/DataAccess/Registries/ImgRegistry.o \
./src/DataAccess/Registries/ListImgRegistry.o \
./src/DataAccess/Registries/ListMsgRegistry.o \
./src/DataAccess/Registries/ListRegistry.o \
./src/DataAccess/Registries/MsgRegistry.o \
./src/DataAccess/Registries/TextRegistry.o 

CPP_DEPS += \
./src/DataAccess/Registries/ExtensibleRelativeRegistry.d \
./src/DataAccess/Registries/FreeSpaceRegistry.d \
./src/DataAccess/Registries/ImgRegistry.d \
./src/DataAccess/Registries/ListImgRegistry.d \
./src/DataAccess/Registries/ListMsgRegistry.d \
./src/DataAccess/Registries/ListRegistry.d \
./src/DataAccess/Registries/MsgRegistry.d \
./src/DataAccess/Registries/TextRegistry.d 


# Each subdirectory must supply rules for building sources it contributes
src/DataAccess/Registries/%.o: ../src/DataAccess/Registries/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -Wno-deprecated -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


