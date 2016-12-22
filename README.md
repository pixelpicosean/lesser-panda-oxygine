# LesserPanda Oxygine (WIP)

Native LesserPanda framework written in C++, powered by Oxygine. This
will very likely to replace the [lesser-panda-native]().

## How to build

This project can be built for several platforms, each with some specific
setups. Follow the steps to make it work properly.

### Windows

Open the `proj.win32/HelloMac.sln` with **Visual Studio** and build

### macOS

Open the `proj.macosx/HelloMac_macosx.xcodeproj` with **XCode** and build

### iOS

Open the `proj.ios/HelloMac_ios.xcodeproj` with **XCode** and build

### Android

1. Install `JDK`, `ant`, `android-sdk` and `android-ndk`
2. Export NDK root folder to `PATH`
3. Open `proj.android` and run scripts

### emscripten

1. Install `emscripten` (can be easily installed with `fips`)
2. Export your `oxygine-framework` and `emscripten` folder to `PATH`
3. Open `proj.cmake` and run scripts
