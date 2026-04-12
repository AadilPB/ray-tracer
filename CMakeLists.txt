cmake_minimum_required(VERSION 4.3.1)
project(ray-tracer)

set(CMAKE_CXX_STANDARD 17)


add_executable(ray-tracer src/main.cpp)

target_include_directories(ray-tracer PRIVATE
    src/
    external/
    )


