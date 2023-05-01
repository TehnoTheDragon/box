cmake_minimum_required(VERSION 3.10.0)
project(BOXLANGUAGE LANGUAGES CXX)

# Settings
set_property(GLOBAL PROPERTY USE_FOLDERS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)

# Variables
set(ASMJIT_PATH "${CMAKE_SOURCE_DIR}/thirdparty/asmjit/")

# Thirdparty
add_subdirectory(${ASMJIT_PATH})

# Modules
include("cmake/array_macros.cmake")
include("cmake/project_module.cmake")

# Projects
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/box/")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/sandbox/")