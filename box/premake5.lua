workspace "box"

project "BoxLanguage"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"

    targetdir (get_target_direction())
    objdir (get_object_direction())

    files {
        "include/**.h", "include/**.hpp",
        "src/**.c", "src/**.cpp",
        "src/**.ixx", "src/**.cppm"
    }

    libdirs {}

    includedirs {
        "include/",
    }

    links {}

    filter { "configurations:Debug" }
        conan_debug.basic_setup()
    filter {}

    filter { "configurations:Release" }
        conan_release.basic_setup()
    filter {}

workspace "*"

BoxInclude = "%{wks.location}/box/include/"