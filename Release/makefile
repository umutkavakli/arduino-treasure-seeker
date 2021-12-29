################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -f

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include libraries/LiquidCrystal/src/subdir.mk
-include hd44780/subdir.mk
-include core/core/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
AR += \
/home/ginger/Documents/sloeber-workspace/treasure_seeker/Release/arduino.ar \

ELF += \
treasure_seeker.elf \

HEX += \
treasure_seeker.hex \


# All Target
all: treasure_seeker

# Tool invocations
treasure_seeker: $(HEX)
	@echo 'Building target: $@'
	@echo 'Printing size:'
	"/home/ginger/Sloeber/arduinoPlugin/packages/arduino/tools/avr-gcc/7.3.0-atmel3.6.1-arduino7/bin/avr-size" -A "/home/ginger/Documents/sloeber-workspace/treasure_seeker/Release/treasure_seeker.elf"
	@echo 'Finished building target: $@'
	@echo ' '

/home/ginger/Documents/sloeber-workspace/treasure_seeker/Release/arduino.ar: $(AR_OBJ)
	@echo 'Starting archiver'
	"/home/ginger/Sloeber/arduinoPlugin/packages/arduino/tools/avr-gcc/7.3.0-atmel3.6.1-arduino7/bin/avr-gcc-ar" rcs     /home/ginger/Documents/sloeber-workspace/treasure_seeker/Release/arduino.ar $(AR_OBJ)
	@echo 'Finished building: $@'
	@echo ' '

treasure_seeker.elf: $(LINK_OBJ) $(AR)
	@echo 'Starting combiner'
	"/home/ginger/Sloeber/arduinoPlugin/packages/arduino/tools/avr-gcc/7.3.0-atmel3.6.1-arduino7/bin/avr-gcc" -w -Os -g -flto -fuse-linker-plugin -Wl,--gc-sections -mmcu=atmega328p   -o "/home/ginger/Documents/sloeber-workspace/treasure_seeker/Release/treasure_seeker.elf"   $(LINK_OBJ)    /home/ginger/Documents/sloeber-workspace/treasure_seeker/Release/arduino.ar  "-L/home/ginger/Documents/sloeber-workspace/treasure_seeker/Release" -lm
	@echo 'Finished building: $@'
	@echo ' '

treasure_seeker.hex: $(ELF)
	@echo 'Do all objcopy commands'
	${recipe.objcopy.eep.pattern}
	${recipe.objcopy.hex.pattern}
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C_UPPER_DEPS)$(PDE_DEPS)$(C_DEPS)$(AR)$(CC_DEPS)$(AR_OBJ)$(C++_DEPS)$(LINK_OBJ)$(CXX_DEPS)$(ASM_DEPS)$(HEX)$(INO_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(ELF)$(CPP_DEPS)
	-@echo ' '

.PHONY: all clean dependents

-include ../makefile.targets
