################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Inc/vl53lx_api.c \
../Core/Inc/vl53lx_api_calibration.c \
../Core/Inc/vl53lx_api_core.c \
../Core/Inc/vl53lx_api_debug.c \
../Core/Inc/vl53lx_api_preset_modes.c \
../Core/Inc/vl53lx_core.c \
../Core/Inc/vl53lx_core_support.c \
../Core/Inc/vl53lx_dmax.c \
../Core/Inc/vl53lx_hist_algos_gen3.c \
../Core/Inc/vl53lx_hist_algos_gen4.c \
../Core/Inc/vl53lx_hist_char.c \
../Core/Inc/vl53lx_hist_core.c \
../Core/Inc/vl53lx_hist_funcs.c \
../Core/Inc/vl53lx_nvm.c \
../Core/Inc/vl53lx_nvm_debug.c \
../Core/Inc/vl53lx_register_funcs.c \
../Core/Inc/vl53lx_sigma_estimate.c \
../Core/Inc/vl53lx_silicon_core.c \
../Core/Inc/vl53lx_wait.c \
../Core/Inc/vl53lx_xtalk.c 

OBJS += \
./Core/Inc/vl53lx_api.o \
./Core/Inc/vl53lx_api_calibration.o \
./Core/Inc/vl53lx_api_core.o \
./Core/Inc/vl53lx_api_debug.o \
./Core/Inc/vl53lx_api_preset_modes.o \
./Core/Inc/vl53lx_core.o \
./Core/Inc/vl53lx_core_support.o \
./Core/Inc/vl53lx_dmax.o \
./Core/Inc/vl53lx_hist_algos_gen3.o \
./Core/Inc/vl53lx_hist_algos_gen4.o \
./Core/Inc/vl53lx_hist_char.o \
./Core/Inc/vl53lx_hist_core.o \
./Core/Inc/vl53lx_hist_funcs.o \
./Core/Inc/vl53lx_nvm.o \
./Core/Inc/vl53lx_nvm_debug.o \
./Core/Inc/vl53lx_register_funcs.o \
./Core/Inc/vl53lx_sigma_estimate.o \
./Core/Inc/vl53lx_silicon_core.o \
./Core/Inc/vl53lx_wait.o \
./Core/Inc/vl53lx_xtalk.o 

C_DEPS += \
./Core/Inc/vl53lx_api.d \
./Core/Inc/vl53lx_api_calibration.d \
./Core/Inc/vl53lx_api_core.d \
./Core/Inc/vl53lx_api_debug.d \
./Core/Inc/vl53lx_api_preset_modes.d \
./Core/Inc/vl53lx_core.d \
./Core/Inc/vl53lx_core_support.d \
./Core/Inc/vl53lx_dmax.d \
./Core/Inc/vl53lx_hist_algos_gen3.d \
./Core/Inc/vl53lx_hist_algos_gen4.d \
./Core/Inc/vl53lx_hist_char.d \
./Core/Inc/vl53lx_hist_core.d \
./Core/Inc/vl53lx_hist_funcs.d \
./Core/Inc/vl53lx_nvm.d \
./Core/Inc/vl53lx_nvm_debug.d \
./Core/Inc/vl53lx_register_funcs.d \
./Core/Inc/vl53lx_sigma_estimate.d \
./Core/Inc/vl53lx_silicon_core.d \
./Core/Inc/vl53lx_wait.d \
./Core/Inc/vl53lx_xtalk.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Inc/%.o Core/Inc/%.su Core/Inc/%.cyclo: ../Core/Inc/%.c Core/Inc/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U575xx -c -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/coryc/STM32CubeIDE/FINAL/FINAL_NUCLEO/Drivers/BSP/Components/VL53L4CX" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Inc

clean-Core-2f-Inc:
	-$(RM) ./Core/Inc/vl53lx_api.cyclo ./Core/Inc/vl53lx_api.d ./Core/Inc/vl53lx_api.o ./Core/Inc/vl53lx_api.su ./Core/Inc/vl53lx_api_calibration.cyclo ./Core/Inc/vl53lx_api_calibration.d ./Core/Inc/vl53lx_api_calibration.o ./Core/Inc/vl53lx_api_calibration.su ./Core/Inc/vl53lx_api_core.cyclo ./Core/Inc/vl53lx_api_core.d ./Core/Inc/vl53lx_api_core.o ./Core/Inc/vl53lx_api_core.su ./Core/Inc/vl53lx_api_debug.cyclo ./Core/Inc/vl53lx_api_debug.d ./Core/Inc/vl53lx_api_debug.o ./Core/Inc/vl53lx_api_debug.su ./Core/Inc/vl53lx_api_preset_modes.cyclo ./Core/Inc/vl53lx_api_preset_modes.d ./Core/Inc/vl53lx_api_preset_modes.o ./Core/Inc/vl53lx_api_preset_modes.su ./Core/Inc/vl53lx_core.cyclo ./Core/Inc/vl53lx_core.d ./Core/Inc/vl53lx_core.o ./Core/Inc/vl53lx_core.su ./Core/Inc/vl53lx_core_support.cyclo ./Core/Inc/vl53lx_core_support.d ./Core/Inc/vl53lx_core_support.o ./Core/Inc/vl53lx_core_support.su ./Core/Inc/vl53lx_dmax.cyclo ./Core/Inc/vl53lx_dmax.d ./Core/Inc/vl53lx_dmax.o ./Core/Inc/vl53lx_dmax.su ./Core/Inc/vl53lx_hist_algos_gen3.cyclo ./Core/Inc/vl53lx_hist_algos_gen3.d ./Core/Inc/vl53lx_hist_algos_gen3.o ./Core/Inc/vl53lx_hist_algos_gen3.su ./Core/Inc/vl53lx_hist_algos_gen4.cyclo ./Core/Inc/vl53lx_hist_algos_gen4.d ./Core/Inc/vl53lx_hist_algos_gen4.o ./Core/Inc/vl53lx_hist_algos_gen4.su ./Core/Inc/vl53lx_hist_char.cyclo ./Core/Inc/vl53lx_hist_char.d ./Core/Inc/vl53lx_hist_char.o ./Core/Inc/vl53lx_hist_char.su ./Core/Inc/vl53lx_hist_core.cyclo ./Core/Inc/vl53lx_hist_core.d ./Core/Inc/vl53lx_hist_core.o ./Core/Inc/vl53lx_hist_core.su ./Core/Inc/vl53lx_hist_funcs.cyclo ./Core/Inc/vl53lx_hist_funcs.d ./Core/Inc/vl53lx_hist_funcs.o ./Core/Inc/vl53lx_hist_funcs.su ./Core/Inc/vl53lx_nvm.cyclo ./Core/Inc/vl53lx_nvm.d ./Core/Inc/vl53lx_nvm.o ./Core/Inc/vl53lx_nvm.su ./Core/Inc/vl53lx_nvm_debug.cyclo ./Core/Inc/vl53lx_nvm_debug.d ./Core/Inc/vl53lx_nvm_debug.o ./Core/Inc/vl53lx_nvm_debug.su ./Core/Inc/vl53lx_register_funcs.cyclo ./Core/Inc/vl53lx_register_funcs.d ./Core/Inc/vl53lx_register_funcs.o ./Core/Inc/vl53lx_register_funcs.su ./Core/Inc/vl53lx_sigma_estimate.cyclo ./Core/Inc/vl53lx_sigma_estimate.d ./Core/Inc/vl53lx_sigma_estimate.o ./Core/Inc/vl53lx_sigma_estimate.su ./Core/Inc/vl53lx_silicon_core.cyclo ./Core/Inc/vl53lx_silicon_core.d ./Core/Inc/vl53lx_silicon_core.o ./Core/Inc/vl53lx_silicon_core.su ./Core/Inc/vl53lx_wait.cyclo ./Core/Inc/vl53lx_wait.d ./Core/Inc/vl53lx_wait.o ./Core/Inc/vl53lx_wait.su ./Core/Inc/vl53lx_xtalk.cyclo ./Core/Inc/vl53lx_xtalk.d ./Core/Inc/vl53lx_xtalk.o ./Core/Inc/vl53lx_xtalk.su

.PHONY: clean-Core-2f-Inc

