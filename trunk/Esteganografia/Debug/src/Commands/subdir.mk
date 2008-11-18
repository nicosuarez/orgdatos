################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Commands/AddDirectory.cpp \
../src/Commands/AddFile.cpp \
../src/Commands/ChangePassword.cpp \
../src/Commands/Command.cpp \
../src/Commands/CommandFactory.cpp \
../src/Commands/GetFile.cpp \
../src/Commands/Help.cpp \
../src/Commands/RemoveDirectory.cpp \
../src/Commands/RemoveFile.cpp \
../src/Commands/ShowDirectories.cpp \
../src/Commands/ShowFiles.cpp 

OBJS += \
./src/Commands/AddDirectory.o \
./src/Commands/AddFile.o \
./src/Commands/ChangePassword.o \
./src/Commands/Command.o \
./src/Commands/CommandFactory.o \
./src/Commands/GetFile.o \
./src/Commands/Help.o \
./src/Commands/RemoveDirectory.o \
./src/Commands/RemoveFile.o \
./src/Commands/ShowDirectories.o \
./src/Commands/ShowFiles.o 

CPP_DEPS += \
./src/Commands/AddDirectory.d \
./src/Commands/AddFile.d \
./src/Commands/ChangePassword.d \
./src/Commands/Command.d \
./src/Commands/CommandFactory.d \
./src/Commands/GetFile.d \
./src/Commands/Help.d \
./src/Commands/RemoveDirectory.d \
./src/Commands/RemoveFile.d \
./src/Commands/ShowDirectories.d \
./src/Commands/ShowFiles.d 


# Each subdirectory must supply rules for building sources it contributes
src/Commands/%.o: ../src/Commands/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -Wno-deprecated -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


