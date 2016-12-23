#!/usr/bin/env sh
adb install -r bin/LesserPanda-debug.apk
adb shell am start -n org.oxygine.LesserPanda/org.oxygine.LesserPanda.MainActivity
