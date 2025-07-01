################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
bsp/src/%.o: ../bsp/src/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"D:/ti/ccs/tools/compiler/ti-cgt-armllvm_4.0.0.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O2 -I"D:/electronic_design_competition/2024H/2024_H/2024h/bsp" -I"D:/electronic_design_competition/2024H/2024_H/2024h" -I"D:/electronic_design_competition/2024H/2024_H/2024h/Board" -I"D:/electronic_design_competition/2024H/2024_H/2024h/bsp/inc" -I"D:/electronic_design_competition/2024H/2024_H/2024h/Debug" -I"D:/ti/mspm0_sdk_2_04_00_06/source/third_party/CMSIS/Core/Include" -I"D:/ti/mspm0_sdk_2_04_00_06/source" -gdwarf-3 -MMD -MP -MF"bsp/src/$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


