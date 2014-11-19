################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/AccelTask.c" \
"../Sources/DisplayTask.c" \
"../Sources/HealthTask.c" \
"../Sources/InputTask.c" \
"../Sources/TempTask.c" \
"../Sources/TheftTask.c" \
"../Sources/UiTask.c" \
"../Sources/main.c" \

C_SRCS += \
../Sources/AccelTask.c \
../Sources/DisplayTask.c \
../Sources/HealthTask.c \
../Sources/InputTask.c \
../Sources/TempTask.c \
../Sources/TheftTask.c \
../Sources/UiTask.c \
../Sources/main.c \

OBJS += \
./Sources/AccelTask.o \
./Sources/DisplayTask.o \
./Sources/HealthTask.o \
./Sources/InputTask.o \
./Sources/TempTask.o \
./Sources/TheftTask.o \
./Sources/UiTask.o \
./Sources/main.o \

C_DEPS += \
./Sources/AccelTask.d \
./Sources/DisplayTask.d \
./Sources/HealthTask.d \
./Sources/InputTask.d \
./Sources/TempTask.d \
./Sources/TheftTask.d \
./Sources/UiTask.d \
./Sources/main.d \

OBJS_QUOTED += \
"./Sources/AccelTask.o" \
"./Sources/DisplayTask.o" \
"./Sources/HealthTask.o" \
"./Sources/InputTask.o" \
"./Sources/TempTask.o" \
"./Sources/TheftTask.o" \
"./Sources/UiTask.o" \
"./Sources/main.o" \

C_DEPS_QUOTED += \
"./Sources/AccelTask.d" \
"./Sources/DisplayTask.d" \
"./Sources/HealthTask.d" \
"./Sources/InputTask.d" \
"./Sources/TempTask.d" \
"./Sources/TheftTask.d" \
"./Sources/UiTask.d" \
"./Sources/main.d" \

OBJS_OS_FORMAT += \
./Sources/AccelTask.o \
./Sources/DisplayTask.o \
./Sources/HealthTask.o \
./Sources/InputTask.o \
./Sources/TempTask.o \
./Sources/TheftTask.o \
./Sources/UiTask.o \
./Sources/main.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/AccelTask.o: ../Sources/AccelTask.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/AccelTask.args" -Wa,-adhlns="$@.lst" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/AccelTask.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/DisplayTask.o: ../Sources/DisplayTask.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/DisplayTask.args" -Wa,-adhlns="$@.lst" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/DisplayTask.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/HealthTask.o: ../Sources/HealthTask.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/HealthTask.args" -Wa,-adhlns="$@.lst" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/HealthTask.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/InputTask.o: ../Sources/InputTask.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/InputTask.args" -Wa,-adhlns="$@.lst" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/InputTask.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/TempTask.o: ../Sources/TempTask.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/TempTask.args" -Wa,-adhlns="$@.lst" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/TempTask.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/TheftTask.o: ../Sources/TheftTask.c
	@echo 'Building file: $<'
	@echo 'Executing target #6 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/TheftTask.args" -Wa,-adhlns="$@.lst" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/TheftTask.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/UiTask.o: ../Sources/UiTask.c
	@echo 'Building file: $<'
	@echo 'Executing target #7 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/UiTask.args" -Wa,-adhlns="$@.lst" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/UiTask.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/main.o: ../Sources/main.c
	@echo 'Building file: $<'
	@echo 'Executing target #8 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/main.args" -Wa,-adhlns="$@.lst" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/main.o"
	@echo 'Finished building: $<'
	@echo ' '


