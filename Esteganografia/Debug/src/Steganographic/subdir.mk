################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Steganographic/Bmp.cpp \
../src/Steganographic/BmpHighColor.cpp \
../src/Steganographic/Gif.cpp \
../src/Steganographic/IStenographic.cpp \
../src/Steganographic/Image.cpp \
../src/Steganographic/ImageFactory.cpp \
../src/Steganographic/Jpg.cpp \
../src/Steganographic/Png.cpp \
../src/Steganographic/StenographicManager.cpp 

OBJS += \
./src/Steganographic/Bmp.o \
./src/Steganographic/BmpHighColor.o \
./src/Steganographic/Gif.o \
./src/Steganographic/IStenographic.o \
./src/Steganographic/Image.o \
./src/Steganographic/ImageFactory.o \
./src/Steganographic/Jpg.o \
./src/Steganographic/Png.o \
./src/Steganographic/StenographicManager.o 

CPP_DEPS += \
./src/Steganographic/Bmp.d \
./src/Steganographic/BmpHighColor.d \
./src/Steganographic/Gif.d \
./src/Steganographic/IStenographic.d \
./src/Steganographic/Image.d \
./src/Steganographic/ImageFactory.d \
./src/Steganographic/Jpg.d \
./src/Steganographic/Png.d \
./src/Steganographic/StenographicManager.d 


# Each subdirectory must supply rules for building sources it contributes
src/Steganographic/%.o: ../src/Steganographic/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -Wno-deprecated -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


