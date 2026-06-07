cmake_minimum_required(VERSION 4.3.1)
project(ray-tracer)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)


add_executable(ray-tracer src/main.cpp)

target_include_directories(ray-tracer PRIVATE
    ${SDL2_INCLUDE_DIRS}
    src/
    external/
    src/math
    src/geometry
    )


target_link_libraries(ray-tracer PRIVATE SDL2::SDL2)

add_custom_command (TARGET ray-tracer POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/textures
    $<TARGET_FILE_DIR:ray-tracer>/textures
)

add_custom_command (TARGET ray-tracer POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/scenes
    $<TARGET_FILE_DIR:ray-tracer>/scenes
)

