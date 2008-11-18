################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/DataAccess/Files/ExtensibleRelativeFile.cpp \
../src/DataAccess/Files/Serializable.cpp 

OBJS += \
./src/DataAccess/Files/ExtensibleRelativeFile.o \
./src/DataAccess/Files/Serializable.o 

CPP_DEPS += \
./src/DataAccess/Files/ExtensibleRelativeFile.d \
./src/DataAccess/Files/Serializable.d 


# Each subdirectory must supply rules for building sources it contributes
src/DataAccess/Files/%.o: ../src/DataAccess/Files/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -Wno-deprecated -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


