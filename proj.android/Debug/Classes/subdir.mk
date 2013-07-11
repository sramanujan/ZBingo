################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
C:/cocos2d-x/ZBingo/Classes/AppDelegate.cpp \
C:/cocos2d-x/ZBingo/Classes/HelloWorldScene.cpp \
C:/cocos2d-x/ZBingo/Classes/XTLayer.cpp 

OBJS += \
./Classes/AppDelegate.o \
./Classes/HelloWorldScene.o \
./Classes/XTLayer.o 

CPP_DEPS += \
./Classes/AppDelegate.d \
./Classes/HelloWorldScene.d \
./Classes/XTLayer.d 


# Each subdirectory must supply rules for building sources it contributes
Classes/AppDelegate.o: C:/cocos2d-x/ZBingo/Classes/AppDelegate.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -I"C:\cocos2d-x\cocos2dx" -I"C:\cocos2d-x\cocos2dx\include" -I"C:\cocos2d-x\cocos2dx\platform\android" -I"C:\ADT-Bundle\ndk\platforms\android-8\arch-arm\usr\include\android" -I"C:\cocos2d-x\CocosDenshion" -I"C:\cocos2d-x\CocosDenshion\include" -I"C:\cocos2d-x\CocosDenshion\android" -I"C:\cocos2d-x\extensions" -I"C:\cocos2d-x\extensions\GUI" -I"C:\cocos2d-x\extensions\GUI\CCScrollView" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Classes/HelloWorldScene.o: C:/cocos2d-x/ZBingo/Classes/HelloWorldScene.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -I"C:\cocos2d-x\cocos2dx" -I"C:\cocos2d-x\cocos2dx\include" -I"C:\cocos2d-x\cocos2dx\platform\android" -I"C:\ADT-Bundle\ndk\platforms\android-8\arch-arm\usr\include\android" -I"C:\cocos2d-x\CocosDenshion" -I"C:\cocos2d-x\CocosDenshion\include" -I"C:\cocos2d-x\CocosDenshion\android" -I"C:\cocos2d-x\extensions" -I"C:\cocos2d-x\extensions\GUI" -I"C:\cocos2d-x\extensions\GUI\CCScrollView" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Classes/XTLayer.o: C:/cocos2d-x/ZBingo/Classes/XTLayer.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -I"C:\cocos2d-x\cocos2dx" -I"C:\cocos2d-x\cocos2dx\include" -I"C:\cocos2d-x\cocos2dx\platform\android" -I"C:\ADT-Bundle\ndk\platforms\android-8\arch-arm\usr\include\android" -I"C:\cocos2d-x\CocosDenshion" -I"C:\cocos2d-x\CocosDenshion\include" -I"C:\cocos2d-x\CocosDenshion\android" -I"C:\cocos2d-x\extensions" -I"C:\cocos2d-x\extensions\GUI" -I"C:\cocos2d-x\extensions\GUI\CCScrollView" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


