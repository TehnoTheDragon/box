# Includes
include(cmake/file_macros.cmake)

# Module

function(new_project project language version)
    project(${project} LANGUAGES ${language} VERSION ${version})
endfunction(new_project)

function(project_add_executable project files)
    collect_files(out "${files}")
    add_executable(${project} ${out})
endfunction(project_add_executable)

function(project_add_library project files)
    collect_files(out "${files}")
    add_library(${project} ${out})
endfunction(project_add_library)

function(project_property project property value)
    set_property(TARGET ${project} PROPERTY ${property} ${value})
endfunction(project_property)

function(create_ide_filters files)
    collect_files(out "${files}")

    foreach(file ${out})
        file(RELATIVE_PATH rel_file ${CMAKE_CURRENT_SOURCE_DIR} ${file})
        get_filename_component(file_dir ${rel_file} DIRECTORY)
        string(REPLACE "/" "\\" file_dir ${file_dir})
        source_group("${file_dir}" FILES ${file})
    endforeach(file)
endfunction(create_ide_filters)