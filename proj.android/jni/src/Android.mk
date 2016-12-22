LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := main

#SDK_ROOT points to folder with SDL and oxygine-framework
LOCAL_SRC_FILES := ../../../../../../ccApps/oxygine/SDL/src/main/android/SDL_android_main.c

LOCAL_SRC_FILES += \
	../../../src/engine/core.cc \
	../../../src/engine/Entity.cc \
	../../../src/engine/Game.cc \
	../../../src/engine/Gfx.cc \
	../../../src/engine/System.cc \
	../../../src/global.cc \
	../../../src/Loading.cc \
	../../../src/MyGame.cc \
	../../../src/main.cc


LOCAL_STATIC_LIBRARIES := oxygine-framework_static
LOCAL_SHARED_LIBRARIES := SDL2

include $(BUILD_SHARED_LIBRARY)


#import from NDK_MODULE_PATH defined in build.cmd
$(call import-module, oxygine-framework)
