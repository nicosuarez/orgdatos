################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Images/Link\ to\ CompressionManager.cpp \
../Images/Link\ to\ EncriptationManager.cpp 

OBJS += \
./Images/Link\ to\ CompressionManager.o \
./Images/Link\ to\ EncriptationManager.o 

CPP_DEPS += \
./Images/Link\ to\ CompressionManager.d \
./Images/Link\ to\ EncriptationManager.d 


# Each subdirectory must supply rules for building sources it contributes
Images/Link\ to\ CompressionManager.o: ../Images/Link\ to\ CompressionManager.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"Images/Link\ to\ CompressionManager.d" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Images/Link\ to\ EncriptationManager.o: ../Images/Link\ to\ EncriptationManager.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"Images/Link\ to\ EncriptationManager.d" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


