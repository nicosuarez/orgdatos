################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Lzss/lzss.cpp 

OBJS += \
./src/Lzss/lzss.o 

CPP_DEPS += \
./src/Lzss/lzss.d 


# Each subdirectory must supply rules for building sources it contributes
src/Lzss/%.o: ../src/Lzss/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -Wno-deprecated -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


