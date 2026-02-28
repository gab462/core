cmake_minimum_required(VERSION 3.25)
project(core LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CXX_EXTENSIONS OFF)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)

file(GLOB CORE_MODULES src/*.cppm)

add_library(core)
target_sources(core PUBLIC
    FILE_SET CXX_MODULES FILES
    ${CORE_MODULES}
)

target_compile_options(core PUBLIC
    -nostdlib
    -fno-builtin
    -fno-unwind-tables
    -fno-asynchronous-unwind-tables
    -fno-stack-protector
    -fno-exceptions
    -fno-rtti
    -Wa,--noexecstack
)

target_link_options(core PUBLIC -nostdlib)

add_library(core::core ALIAS core)

add_subdirectory(example)
