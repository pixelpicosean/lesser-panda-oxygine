LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := main

#SDK_ROOT points to folder with SDL and oxygine-framework
LOCAL_SRC_FILES := ../../../..//SDL/src/main/android/SDL_android_main.c

LOCAL_SRC_FILES += ../../../src/main.cpp \
	../../../src/engine/core.cpp \
	../../../src/engine/Entity.cpp \
	../../../src/engine/Game.cpp \
	../../../src/engine/Gfx.cpp \
	../../../src/engine/Input.cpp \
	../../../src/engine/System.cpp \
	../../../src/game/global.cpp \
	../../../src/game/Loading.cpp \
	../../../src/game/MyGame.cpp


LOCAL_STATIC_LIBRARIES := oxygine-framework_static
LOCAL_SHARED_LIBRARIES := SDL2

include $(BUILD_SHARED_LIBRARY)


#import from NDK_MODULE_PATH defined in build.cmd
$(call import-module, oxygine-framework)
