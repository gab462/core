cmake_minimum_required(VERSION 3.25)
project(examples LANGUAGES CXX)

option(BUILD_EXAMPLES "Build example executables" ON)
if(NOT BUILD_EXAMPLES)
  return()
endif()

set(EXAMPLE_SRCS
  primer.cpp
  client.cpp
  server.cpp
)

foreach(src IN LISTS EXAMPLE_SRCS)
  get_filename_component(name ${src} NAME_WE)
  add_executable(${name} ${src})
  target_link_libraries(${name} PRIVATE core::core)
endforeach()
