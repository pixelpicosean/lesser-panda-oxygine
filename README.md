# LesserPanda Oxygine (WIP)

Native LesserPanda framework written in C++, powered by Oxygine. This
will very likely to replace the [lesser-panda-native]().

## Setup

This project can be built for several platforms, each with some specific
setups. Follow the steps to make it work properly.

First of all, setup oxygine so you have a folder that contains
`oxygine-framework` and `SDL` repos. Clone this project to that folder.

Then follow the steps to be able to build for any supported platforms.

### Windows

Open the `proj.win32/LesserPanda.sln` with **Visual Studio** and build

### macOS

Open the `proj.macosx/LesserPanda_macosx.xcodeproj` with **XCode** and build

### iOS

Open the `proj.ios/LesserPanda_ios.xcodeproj` with **XCode** and build

### Android

1. Install `JDK`, `ant`, `android-sdk` and `android-ndk`
2. Export NDK root folder to `PATH`
3. Open `proj.android` and run scripts

### emscripten

To make this step simplier, I've modified the cmake file to work with
the portable version from [fips](https://floooh.github.io/fips/index.html).
Simply use `fips` to install `emscripten` and follow the rest steps,
you'll get a working setup.

1. Install `fips` and `emscripten`
2. Export your `oxygine-framework` and `emscripten` folder to `PATH`
3. Open `proj.cmake` and run scripts

## Getting start

I'll try my best to keep the same API as the JavaScript version, but slightly
adjusted to be better to use in C++.


Add a new system:

```cpp
this
  ->addSystem<lp::Gfx>()
  ->addSystem<lp::Input>();
```


Spawn an `Entity`:

```cpp
auto player = this->spawnEntity<MyMarioEntity>(100, 100, "actors");
```
