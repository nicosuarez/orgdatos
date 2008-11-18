################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Tree/RegisterFile/cell.cpp \
../src/Tree/RegisterFile/register_file.cpp 

OBJS += \
./src/Tree/RegisterFile/cell.o \
./src/Tree/RegisterFile/register_file.o 

CPP_DEPS += \
./src/Tree/RegisterFile/cell.d \
./src/Tree/RegisterFile/register_file.d 


# Each subdirectory must supply rules for building sources it contributes
src/Tree/RegisterFile/%.o: ../src/Tree/RegisterFile/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -Wno-deprecated -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


