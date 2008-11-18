################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/DataAccess/Organizations/OrgExtensibleRelative.cpp \
../src/DataAccess/Organizations/OrgList.cpp \
../src/DataAccess/Organizations/OrgText.cpp 

OBJS += \
./src/DataAccess/Organizations/OrgExtensibleRelative.o \
./src/DataAccess/Organizations/OrgList.o \
./src/DataAccess/Organizations/OrgText.o 

CPP_DEPS += \
./src/DataAccess/Organizations/OrgExtensibleRelative.d \
./src/DataAccess/Organizations/OrgList.d \
./src/DataAccess/Organizations/OrgText.d 


# Each subdirectory must supply rules for building sources it contributes
src/DataAccess/Organizations/%.o: ../src/DataAccess/Organizations/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -Wno-deprecated -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


