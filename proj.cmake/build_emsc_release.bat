call emsdk activate

python ${OXYGINE}/tools/others/embed_folder_js.py -s ../data

mkdir build_emsc_release
cd build_emsc_release
cmake -DCMAKE_TOOLCHAIN_FILE="%EMSCRIPTEN%/emscripten/incoming/cmake/Modules/Platform/Emscripten.cmake" -G"Unix Makefiles" ..
make
cd ..
