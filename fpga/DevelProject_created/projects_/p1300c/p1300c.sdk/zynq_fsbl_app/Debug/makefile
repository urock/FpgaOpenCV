################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
ELFSIZE += \
zynq_fsbl_app.elf.size \


# All Target
all: zynq_fsbl_app.elf secondary-outputs

# Tool invocations
zynq_fsbl_app.elf: $(OBJS) ../src/lscript.ld $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM gcc linker'
	arm-xilinx-eabi-gcc -L"E:\users\tasha\git_dirs\refactor\FpgaOpenCV\fpga\DevelProject\projects_\p1300c\p1300c.sdk\zynq_fsbl_app\src" -Wl,-T -Wl,../src/lscript.ld -L../../zynq_fsbl_bsp/ps7_cortexa9_0/lib -o "zynq_fsbl_app.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

zynq_fsbl_app.elf.size: zynq_fsbl_app.elf
	@echo 'Invoking: ARM Print Size'
	arm-xilinx-eabi-size zynq_fsbl_app.elf  |tee "zynq_fsbl_app.elf.size"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(S_UPPER_DEPS)$(C_DEPS)$(ELFSIZE) zynq_fsbl_app.elf
	-@echo ' '

secondary-outputs: $(ELFSIZE)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
