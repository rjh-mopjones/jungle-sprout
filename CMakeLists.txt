cmake_minimum_required(VERSION 3.27)
project(jungle-sprout)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

add_executable(untitled main.cpp)

project(jungle-sprout)


set(SOURCE_FILES main.cpp
        noise/math_utils.cpp
        noise/math_utils.h
        noise/perlin.cpp
        noise/perlin.h
        io/bitmap_utils.cpp
        io/bitmap_utils.h
        noise/voronoi.cpp
        noise/voronoi.h
)
add_executable(jungle-sprout ${SOURCE_FILES})
include_directories(/usr/local/include)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(jungle-sprout sfml-system sfml-window sfml-graphics sfml-audio sfml-network)