new_project(box CXX 0.1.0)
project_add_library(box "src/**.cpp;include/**.hpp")
target_include_directories(box PUBLIC "include")
target_compile_options(box PRIVATE "/std:c++17")

# create_ide_filters("src/**.cpp;include/**.hpp")