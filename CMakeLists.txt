cmake_minimum_required(VERSION 3.14)

project (ev)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

if (${CMAKE_SYSTEM_NAME} STREQUAL "Emscripten")
  set(CMAKE_EXECUTABLE_SUFFIX ".html")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s USE_SDL=2 -s USE_SDL_IMAGE=2")
  set(SDL2_LIBRARIES "-s USE_SDL=2")
  set(SDL2_IMAGE_LIBRARIES "-s USE_SDL_IMAGE=2")
else ()
  find_package(SDL2 REQUIRED)
endif ()

set(CATCH2_INCLUDES deps/Catch2/single_include/)
set(EIGEN_INCLUDES deps/eigen/)

# objs target

set(INCLUDES include/)
file(GLOB SOURCES "src/*.cpp")

add_library(objs OBJECT ${SOURCES})
target_include_directories(objs PUBLIC
  ${INCLUDES}
  ${EIGEN_INCLUDES}
  ${SDL2_INCLUDE_DIRS})
target_link_libraries(objs ${SDL2_LIBRARIES})

# test target

file(GLOB TEST_SOURCES "test/*.cpp")

add_executable(test ${TEST_SOURCES})
target_include_directories(test PRIVATE ${CATCH2_INCLUDES})
target_link_libraries(test objs)

# main target

add_executable(main cmd/main.cpp)
target_link_libraries(main objs)

add_executable(demo_seek cmd/demo_seek.cpp)
target_link_libraries(demo_seek objs)

add_executable(demo_arrive cmd/demo_arrive.cpp)
target_link_libraries(demo_arrive objs)
