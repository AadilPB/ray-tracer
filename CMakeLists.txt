cmake_minimum_required(VERSION 4.3.1)
project(ray-tracer)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)


add_executable(ray-tracer src/main.cpp)

target_include_directories(ray-tracer PRIVATE
    ${SDL2_INCLUDE_DIRS}
    src/
    external/
    )


target_link_libraries(ray-tracer PRIVATE SDL2::SDL2)

