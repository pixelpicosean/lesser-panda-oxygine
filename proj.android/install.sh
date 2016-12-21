#!/usr/bin/env sh
adb install -r bin/HelloMac-debug.apk
adb shell am start -n org.oxygine.HelloMac/org.oxygine.HelloMac.MainActivity
