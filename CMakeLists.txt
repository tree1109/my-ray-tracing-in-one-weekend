cmake_minimum_required(VERSION 3.10)

project(RayTracingInOneWeekend)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
)

add_executable(main ${SRC_FILES})

target_include_directories(main PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")