cmake_minimum_required (VERSION 2.6)
project (LesserPanda)

add_subdirectory(../../../../ccApps/oxygine/oxygine-framework/ oxygine-framework)
add_definitions(${OXYGINE_DEFINITIONS})
include_directories(${OXYGINE_INCLUDE_DIRS})
link_directories(${OXYGINE_LIBRARY_DIRS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OXYGINE_CXX_FLAGS}")

add_executable(LesserPanda
  ../src/main.cpp
  ../src/entry.hpp
  ../src/engine/core.cpp
  ../src/engine/core.hpp
  ../src/engine/Entity.cpp
  ../src/engine/Entity.hpp
  ../src/engine/Game.cpp
  ../src/engine/Game.hpp
  ../src/engine/Gfx.cpp
  ../src/engine/Gfx.hpp
  ../src/engine/NonCopyable.hpp
  ../src/engine/System.cpp
  ../src/engine/System.hpp
  ../src/engine/Types.hpp
  ../src/game/global.cpp
  ../src/game/global.hpp
  ../src/game/Loading.cpp
  ../src/game/Loading.hpp
  ../src/game/MyGame.cpp
  ../src/game/MyGame.hpp
)
target_link_libraries(LesserPanda ${OXYGINE_CORE_LIBS})



if (WIN32) #disable console mode for VC++
	set_target_properties(LesserPanda PROPERTIES WIN32_EXECUTABLE TRUE)
endif(WIN32)



if (EMSCRIPTEN)
	SET(CMAKE_EXECUTABLE_SUFFIX ".html")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s NO_EXIT_RUNTIME=1 -s WARN_ON_UNDEFINED_SYMBOLS=1 --memory-init-file 0 -s TOTAL_MEMORY=50331648")
	em_link_pre_js(LesserPanda  ${OXYGINE_JS_LIBRARIES}  ${CMAKE_CURRENT_SOURCE_DIR}/data.js)
endif(EMSCRIPTEN)
