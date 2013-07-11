################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../jni/hellocpp/main.cpp 

OBJS += \
./jni/hellocpp/main.o 

CPP_DEPS += \
./jni/hellocpp/main.d 


# Each subdirectory must supply rules for building sources it contributes
jni/hellocpp/%.o: ../jni/hellocpp/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -I"C:\cocos2d-x\cocos2dx" -I"C:\cocos2d-x\cocos2dx\include" -I"C:\cocos2d-x\cocos2dx\platform\android" -I"C:\ADT-Bundle\ndk\platforms\android-8\arch-arm\usr\include\android" -I"C:\cocos2d-x\CocosDenshion" -I"C:\cocos2d-x\CocosDenshion\include" -I"C:\cocos2d-x\CocosDenshion\android" -I"C:\cocos2d-x\extensions" -I"C:\cocos2d-x\extensions\GUI" -I"C:\cocos2d-x\extensions\GUI\CCScrollView" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


