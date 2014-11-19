################################################################################
# Automatically-generated file. Do not edit!
################################################################################

#Progress monitor hint: 8
first : all
-include ../makefile.init

# This file contains definitions of environment variables used in the makefiles and .args files if exist.
-include makefile.local

RM := "$(GNU_Make_Install_DirEnv)/rm" -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include Sources/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(SX_DEPS)),)
-include $(SX_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
Lab1.elf \

EXECUTABLES_QUOTED += \
"Lab1.elf" \

EXECUTABLES_OS_FORMAT += \
Lab1.elf \


# All Target
all: warning-messages explicit-dependencies Lab1.elf secondary-outputs

# Tool invocations
Lab1.elf: $(OBJS) $(USER_OBJS) $(FREESCALE)/Freescale_MQX_4_1/lib/twrk60n512.cw10gcc/debug/bsp/intflash.ld
	@echo 'Building target: $@'
	@echo 'Executing target #9 $@'
	@echo 'Invoking: ARM Ltd Windows GCC C Linker'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc"    @"Lab1.args" -o"Lab1.elf"
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(S_DEPS_QUOTED) "./*/*.o"  $(S_UPPER_DEPS_QUOTED) $(ASM_DEPS_QUOTED) $(ASM_UPPER_DEPS_QUOTED) $(SX_DEPS_QUOTED) $(EXECUTABLES_QUOTED) "./*/*.d"  $(ProjDirPath)/twrk60n512_Int_Flash_Debug/Lab1.elf
	-@echo ' '

secondary-outputs:

.PHONY: all clean dependents explicit-dependencies warning-messages
.SECONDARY:

-include ../makefile.targets

explicit-dependencies: $(FREESCALE)/Freescale_MQX_4_1/lib/twrk60n512.cw10gcc/debug/bsp/intflash.ld 

warning-messages: 

