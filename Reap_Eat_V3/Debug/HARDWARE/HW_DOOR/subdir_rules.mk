################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
HARDWARE/HW_DOOR/%.obj: ../HARDWARE/HW_DOOR/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"/Applications/ti/ccs1010/ccs/tools/compiler/ti-cgt-arm_20.2.4.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="/Users/juanleyva/Documents/CCStudio/Reap_Eat_V3/HARDWARE/HW_AMBIENT_SENSOR" --include_path="/Users/juanleyva/Documents/CCStudio/Reap_Eat_V3/DRIVERS/DRV_ADC" --include_path="/Users/juanleyva/Documents/CCStudio/Reap_Eat_V3/DRIVERS/DRV_GPIO" --include_path="/Users/juanleyva/Documents/CCStudio/Reap_Eat_V3/DRIVERS/DRV_I2C" --include_path="/Users/juanleyva/Documents/CCStudio/Reap_Eat_V3/DRIVERS/DRV_INITIALIZATION" --include_path="/Users/juanleyva/Documents/CCStudio/Reap_Eat_V3/DRIVERS/DRV_PWM" --include_path="/Users/juanleyva/Documents/CCStudio/Reap_Eat_V3/DRIVERS/DRV_UART" --include_path="/Users/juanleyva/Documents/CCStudio/Reap_Eat_V3/HARDWARE/HW_BUZZER" --include_path="/Users/juanleyva/Documents/CCStudio/Reap_Eat_V3/HARDWARE/HW_COMMUNICATION" --include_path="/Users/juanleyva/Documents/CCStudio/Reap_Eat_V3/HARDWARE/HW_COOLER" --include_path="/Users/juanleyva/Documents/CCStudio/Reap_Eat_V3/HARDWARE/HW_DEBUG_COM" --include_path="/Users/juanleyva/Documents/CCStudio/Reap_Eat_V3/HARDWARE/HW_DOOR" --include_path="/Users/juanleyva/Documents/CCStudio/Reap_Eat_V3/HARDWARE/HW_FAN_EXTERNAL" --include_path="/Users/juanleyva/Documents/CCStudio/Reap_Eat_V3/HARDWARE/HW_FAN_INTERNAL" --include_path="/Users/juanleyva/Documents/CCStudio/Reap_Eat_V3/HARDWARE/HW_HEARTBEAT" --include_path="/Users/juanleyva/Documents/CCStudio/Reap_Eat_V3/HARDWARE/HW_HEATER" --include_path="/Users/juanleyva/Documents/CCStudio/Reap_Eat_V3/HARDWARE/HW_HUMIDIFIER" --include_path="/Users/juanleyva/Documents/CCStudio/Reap_Eat_V3/HARDWARE/HW_IRRIGATION" --include_path="/Users/juanleyva/Documents/CCStudio/Reap_Eat_V3/HARDWARE/HW_LIGHT" --include_path="/Users/juanleyva/Documents/CCStudio/Reap_Eat_V3/HARDWARE/HW_TANK_HUMIDIFIER" --include_path="/Users/juanleyva/Documents/CCStudio/Reap_Eat_V3/HARDWARE/HW_TANK_MAIN" --include_path="/Users/juanleyva/Documents/CCStudio/Reap_Eat_V3/HARDWARE/HW_VENT" --include_path="/Users/juanleyva/Documents/CCStudio/Reap_Eat_V3/TESTING" --include_path="/Users/juanleyva/Documents/CCStudio/Reap_Eat_V3/DRIVERS" --include_path="/Users/juanleyva/Documents/CCStudio/Reap_Eat_V3/HARDWARE" --include_path="/Users/juanleyva/Documents/CCStudio/Reap_Eat_V3" --include_path="/Users/juanleyva/Documents/CCStudio/Reap_Eat_V3" --include_path="/Applications/ti/tirtos_tivac_2_16_00_08/products/bios_6_45_01_29/packages/ti/sysbios/posix" --include_path="/Applications/ti/tirtos_tivac_2_16_00_08/products/TivaWare_C_Series-2.1.1.71b" --include_path="/Applications/ti/ccs1010/ccs/tools/compiler/ti-cgt-arm_20.2.4.LTS/include" --define=ccs="ccs" --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="HARDWARE/HW_DOOR/$(basename $(<F)).d_raw" --obj_directory="HARDWARE/HW_DOOR" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


