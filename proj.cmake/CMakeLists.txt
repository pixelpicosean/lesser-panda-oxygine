cmake_minimum_required (VERSION 2.6)
project (HelloMac)

add_subdirectory(../../../../ccApps/oxygine/oxygine-framework/ oxygine-framework)
add_definitions(${OXYGINE_DEFINITIONS})
include_directories(${OXYGINE_INCLUDE_DIRS})
link_directories(${OXYGINE_LIBRARY_DIRS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OXYGINE_CXX_FLAGS}")

add_executable(HelloMac
  ../src/main.cc
  ../src/engine/core.cc
  ../src/engine/core.h
  ../src/engine/Entity.cc
  ../src/engine/Entity.h
  ../src/engine/Game.cc
  ../src/engine/Game.h
  ../src/engine/Gfx.cc
  ../src/engine/Gfx.h
  ../src/engine/NonCopyable.h
  ../src/engine/System.cc
  ../src/engine/System.h
  ../src/engine/Types.h
  ../src/global.cc
  ../src/global.h
  ../src/Loading.cc
  ../src/Loading.h
  ../src/MyGame.cc
  ../src/MyGame.h
)
target_link_libraries(HelloMac ${OXYGINE_CORE_LIBS})



if (WIN32) #disable console mode for VC++
	set_target_properties(HelloMac PROPERTIES WIN32_EXECUTABLE TRUE)
endif(WIN32)



if (EMSCRIPTEN)
	SET(CMAKE_EXECUTABLE_SUFFIX ".html")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s NO_EXIT_RUNTIME=1 -s WARN_ON_UNDEFINED_SYMBOLS=1 --memory-init-file 0 -s TOTAL_MEMORY=50331648")
	em_link_pre_js(HelloMac  ${OXYGINE_JS_LIBRARIES}  ${CMAKE_CURRENT_SOURCE_DIR}/data.js)
endif(EMSCRIPTEN)
