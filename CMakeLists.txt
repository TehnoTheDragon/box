cmake_minimum_required(VERSION 3.10.0)
project(BOXLANGUAGE LANGUAGES NONE)

# Settings
set_property(GLOBAL PROPERTY USE_FOLDERS OFF)

# Modules
include("cmake/array_macros.cmake")
include("cmake/project_module.cmake")

# Projects
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/box/")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/sandbox/")