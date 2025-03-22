################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/fonts.c \
../Core/Src/main.c \
../Core/Src/platform.c \
../Core/Src/ssd1351.c \
../Core/Src/stm32u5xx_hal_msp.c \
../Core/Src/stm32u5xx_hal_timebase_tim.c \
../Core/Src/stm32u5xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32u5xx.c \
../Core/Src/vl53lx_platform.c \
../Core/Src/vl53lx_platform_init.c \
../Core/Src/vl53lx_platform_ipp.c \
../Core/Src/vl53lx_platform_log.c 

OBJS += \
./Core/Src/fonts.o \
./Core/Src/main.o \
./Core/Src/platform.o \
./Core/Src/ssd1351.o \
./Core/Src/stm32u5xx_hal_msp.o \
./Core/Src/stm32u5xx_hal_timebase_tim.o \
./Core/Src/stm32u5xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32u5xx.o \
./Core/Src/vl53lx_platform.o \
./Core/Src/vl53lx_platform_init.o \
./Core/Src/vl53lx_platform_ipp.o \
./Core/Src/vl53lx_platform_log.o 

C_DEPS += \
./Core/Src/fonts.d \
./Core/Src/main.d \
./Core/Src/platform.d \
./Core/Src/ssd1351.d \
./Core/Src/stm32u5xx_hal_msp.d \
./Core/Src/stm32u5xx_hal_timebase_tim.d \
./Core/Src/stm32u5xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32u5xx.d \
./Core/Src/vl53lx_platform.d \
./Core/Src/vl53lx_platform_init.d \
./Core/Src/vl53lx_platform_ipp.d \
./Core/Src/vl53lx_platform_log.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U575xx -c -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/coryc/STM32CubeIDE/FINAL/FINAL_NUCLEO/Drivers/BSP/Components/VL53L4CX" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/fonts.cyclo ./Core/Src/fonts.d ./Core/Src/fonts.o ./Core/Src/fonts.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/platform.cyclo ./Core/Src/platform.d ./Core/Src/platform.o ./Core/Src/platform.su ./Core/Src/ssd1351.cyclo ./Core/Src/ssd1351.d ./Core/Src/ssd1351.o ./Core/Src/ssd1351.su ./Core/Src/stm32u5xx_hal_msp.cyclo ./Core/Src/stm32u5xx_hal_msp.d ./Core/Src/stm32u5xx_hal_msp.o ./Core/Src/stm32u5xx_hal_msp.su ./Core/Src/stm32u5xx_hal_timebase_tim.cyclo ./Core/Src/stm32u5xx_hal_timebase_tim.d ./Core/Src/stm32u5xx_hal_timebase_tim.o ./Core/Src/stm32u5xx_hal_timebase_tim.su ./Core/Src/stm32u5xx_it.cyclo ./Core/Src/stm32u5xx_it.d ./Core/Src/stm32u5xx_it.o ./Core/Src/stm32u5xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32u5xx.cyclo ./Core/Src/system_stm32u5xx.d ./Core/Src/system_stm32u5xx.o ./Core/Src/system_stm32u5xx.su ./Core/Src/vl53lx_platform.cyclo ./Core/Src/vl53lx_platform.d ./Core/Src/vl53lx_platform.o ./Core/Src/vl53lx_platform.su ./Core/Src/vl53lx_platform_init.cyclo ./Core/Src/vl53lx_platform_init.d ./Core/Src/vl53lx_platform_init.o ./Core/Src/vl53lx_platform_init.su ./Core/Src/vl53lx_platform_ipp.cyclo ./Core/Src/vl53lx_platform_ipp.d ./Core/Src/vl53lx_platform_ipp.o ./Core/Src/vl53lx_platform_ipp.su ./Core/Src/vl53lx_platform_log.cyclo ./Core/Src/vl53lx_platform_log.d ./Core/Src/vl53lx_platform_log.o ./Core/Src/vl53lx_platform_log.su

.PHONY: clean-Core-2f-Src

