################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../hd44780/HD44780.cpp 

LINK_OBJ += \
./hd44780/HD44780.cpp.o 

CPP_DEPS += \
./hd44780/HD44780.cpp.d 


# Each subdirectory must supply rules for building sources it contributes
hd44780/HD44780.cpp.o: ../hd44780/HD44780.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/ginger/Sloeber/arduinoPlugin/packages/arduino/tools/avr-gcc/7.3.0-atmel3.6.1-arduino7/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10812 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR     -I"/home/ginger/Sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.8.3/variants/standard" -I"/home/ginger/Sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.8.3/cores/arduino" -I"/home/ginger/Sloeber/arduinoPlugin/libraries/LiquidCrystal/1.0.7/src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"   -o "$@"
	@echo 'Finished building: $<'
	@echo ' '


