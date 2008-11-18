################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Tree/BppTree/bppIterator.cpp \
../src/Tree/BppTree/bpptree.cpp \
../src/Tree/BppTree/leaf_node.cpp \
../src/Tree/BppTree/level_node.cpp \
../src/Tree/BppTree/level_register.cpp \
../src/Tree/BppTree/node.cpp \
../src/Tree/BppTree/node_manager.cpp \
../src/Tree/BppTree/node_register.cpp 

OBJS += \
./src/Tree/BppTree/bppIterator.o \
./src/Tree/BppTree/bpptree.o \
./src/Tree/BppTree/leaf_node.o \
./src/Tree/BppTree/level_node.o \
./src/Tree/BppTree/level_register.o \
./src/Tree/BppTree/node.o \
./src/Tree/BppTree/node_manager.o \
./src/Tree/BppTree/node_register.o 

CPP_DEPS += \
./src/Tree/BppTree/bppIterator.d \
./src/Tree/BppTree/bpptree.d \
./src/Tree/BppTree/leaf_node.d \
./src/Tree/BppTree/level_node.d \
./src/Tree/BppTree/level_register.d \
./src/Tree/BppTree/node.d \
./src/Tree/BppTree/node_manager.d \
./src/Tree/BppTree/node_register.d 


# Each subdirectory must supply rules for building sources it contributes
src/Tree/BppTree/%.o: ../src/Tree/BppTree/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -Wno-deprecated -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


