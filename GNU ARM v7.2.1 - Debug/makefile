################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include emlib/subdir.mk
-include CMSIS/EFM32GG/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: battleShip.axf

# Tool invocations
battleShip.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU ARM C Linker'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m3 -mthumb -T "battleShip.ld" -Xlinker --gc-sections -Xlinker -Map="battleShip.map" --specs=nano.specs -o battleShip.axf "./CMSIS/EFM32GG/startup_efm32gg.o" "./CMSIS/EFM32GG/system_efm32gg.o" "./emlib/em_cmu.o" "./emlib/em_gpio.o" "./emlib/em_lcd.o" "./emlib/em_system.o" "./emlib/em_usart.o" "./emlib/segmentlcd.o" "./src/control.o" "./src/display.o" "./src/main.o" "./src/segmentlcd_individual.o" "./src/uart.o" -Wl,--start-group -lgcc -lc -lnosys -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

	@echo 'Building hex file: battleShip.hex'
	arm-none-eabi-objcopy -O ihex "battleShip.axf" "battleShip.hex"
	@echo ' '

	@echo 'Building bin file: battleShip.bin'
	arm-none-eabi-objcopy -O binary "battleShip.axf" "battleShip.bin"
	@echo ' '

	@echo 'Building s37 file: battleShip.s37'
	arm-none-eabi-objcopy -O srec "battleShip.axf" "battleShip.s37"
	@echo ' '

	@echo 'Running size tool'
	arm-none-eabi-size "battleShip.axf"
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) battleShip.axf
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
