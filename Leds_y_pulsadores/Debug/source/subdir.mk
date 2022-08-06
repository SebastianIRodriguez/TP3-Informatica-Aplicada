################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/MKL46Z4_Project.c \
../source/mtb.c \
../source/semihost_hardfault.c 

OBJS += \
./source/MKL46Z4_Project.o \
./source/mtb.o \
./source/semihost_hardfault.o 

C_DEPS += \
./source/MKL46Z4_Project.d \
./source/mtb.d \
./source/semihost_hardfault.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKL46Z256VLL4_cm0plus -DCPU_MKL46Z256VLL4 -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\lraff\Documents\MCUXpressoIDE_11.5.1_7266\workspace\TP3\board" -I"C:\Users\lraff\Documents\MCUXpressoIDE_11.5.1_7266\workspace\TP3\source" -I"C:\Users\lraff\Documents\MCUXpressoIDE_11.5.1_7266\workspace\TP3" -I"C:\Users\lraff\Documents\MCUXpressoIDE_11.5.1_7266\workspace\TP3\drivers" -I"C:\Users\lraff\Documents\MCUXpressoIDE_11.5.1_7266\workspace\TP3\utilities" -I"C:\Users\lraff\Documents\MCUXpressoIDE_11.5.1_7266\workspace\TP3\startup" -I"C:\Users\lraff\Documents\MCUXpressoIDE_11.5.1_7266\workspace\TP3\CMSIS" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


