workspace "box"

local LLVM_INCLUDE_BUILD = "E:\\LLVM\\llvm-project\\build\\include"
local LLVM_INCLUDE_SOURCE = "E:\\LLVM\\llvm-project\\llvm\\include"
local LLVM_LIBS = "E:\\LLVM\\llvm-project\\build\\Debug\\lib"

project "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"

    targetdir (get_target_direction())
    objdir (get_object_direction())

    files {
        "include/**.h", "include/**.hpp",
        "src/**.c", "src/**.cpp",
        "src/**.ixx", "src/**.cppm"
    }

    includedirs {
        "include/",
        BoxInclude,
    }

    links {
        "BoxLanguage",
    }

    filter { "configurations:Debug" }
        conan_debug.basic_setup()
    filter {}

    filter { "configurations:Release" }
        conan_release.basic_setup()
    filter {}

workspace "*"