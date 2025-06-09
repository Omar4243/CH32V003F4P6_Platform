################################################################################
# MRS Version: 2.1.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Debug/debug.c 

C_DEPS += \
./Debug/debug.d 

OBJS += \
./Debug/debug.o 



# Each subdirectory must supply rules for building sources it contributes
Debug/%.o: ../Debug/%.c
	@	riscv-none-embed-gcc -march=rv32ecxw -mabi=ilp32e -msmall-data-limit=0 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -I"c:/Users/Omar Megahed/Desktop/test CH32V003/Repo/CH32V003F4P6_Platform/CH32V003F4P6_Deployment/Debug" -I"c:/Users/Omar Megahed/Desktop/test CH32V003/Repo/CH32V003F4P6_Platform/CH32V003F4P6_Deployment/Core" -I"c:/Users/Omar Megahed/Desktop/test CH32V003/Repo/CH32V003F4P6_Platform/CH32V003F4P6_Deployment/User" -I"c:/Users/Omar Megahed/Desktop/test CH32V003/Repo/CH32V003F4P6_Platform/CH32V003F4P6_Deployment/Peripheral/inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
