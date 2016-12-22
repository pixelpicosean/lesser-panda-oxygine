APP_STL := gnustl_static
APP_CPPFLAGS += -fexceptions
APP_CPPFLAGS += -frtti
APP_CPPFLAGS += -std=c++11
APP_ABI := armeabi-v7a
# Fixes C++11 support, while using NDK-r9d
# NDK_TOOLCHAIN_VERSION := 4.8
