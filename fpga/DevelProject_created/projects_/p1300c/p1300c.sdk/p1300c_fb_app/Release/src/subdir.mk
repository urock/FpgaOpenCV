################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
LD_SRCS += \
../src/lscript.ld 

C_SRCS += \
../src/adv7511.c \
../src/cat9554.c \
../src/main.c \
../src/pca9534.c \
../src/tca9548.c \
../src/xaxivdma_ext.c \
../src/xiicps_ext.c 

OBJS += \
./src/adv7511.o \
./src/cat9554.o \
./src/main.o \
./src/pca9534.o \
./src/tca9548.o \
./src/xaxivdma_ext.o \
./src/xiicps_ext.o 

C_DEPS += \
./src/adv7511.d \
./src/cat9554.d \
./src/main.d \
./src/pca9534.d \
./src/tca9548.d \
./src/xaxivdma_ext.d \
./src/xiicps_ext.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM gcc compiler'
	arm-xilinx-eabi-gcc -Wall -O2 -c -fmessage-length=0 -MT"$@" -I../../p1300c_fb_bsp/ps7_cortexa9_0/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


