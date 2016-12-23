call emsdk activate

python ${OXYGINE}/tools/others/embed_folder_js.py -s ../data

mkdir build_emsc
cd build_emsc
cmake -DCMAKE_TOOLCHAIN_FILE="%EMSCRIPTEN%/emscripten/incoming/cmake/Modules/Platform/Emscripten.cmake" -G"Unix Makefiles" ..
make
cd ..
