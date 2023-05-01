new_project(sandbox CXX 0.1.0)

project_add_executable(sandbox "src/**.cpp;include/**.hpp")
target_include_directories(sandbox PRIVATE "include" PRIVATE "${CMAKE_SOURCE_DIR}/thirdparty/asmjit/src/")
target_compile_options(sandbox PRIVATE "/std:c++17")
target_link_libraries(sandbox PRIVATE box PRIVATE asmjit::asmjit)

# create_ide_filters("src/**.cpp;include/**.hpp")