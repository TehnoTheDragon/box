workspace "box"

local LLVM_INCLUDE_BUILD = "E:\\LLVM\\llvm-project\\build\\include"
local LLVM_INCLUDE_SOURCE = "E:\\LLVM\\llvm-project\\llvm\\include"
local LLVM_LIBS = "E:\\LLVM\\llvm-project\\build\\Debug\\lib"

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

    libdirs {
        LLVM_LIBS
    }

    includedirs {
        "include/",
        LLVM_INCLUDE_BUILD,
        LLVM_INCLUDE_SOURCE
    }

    links {
        "LLVMCore",
        "LLVMSupport",
        "LLVMIRReader",
        "LLVMIRPrinter",
        "LLVMX86CodeGen",
        "LLVMX86AsmParser",
        -- "LLVMCFGuard",
        -- "LLVMGlobalISel",
        "LLVMX86Desc",
        "LLVMX86Info",
        -- "LLVMMCDisassembler",
        -- "LLVMSelectionDAG",
        -- "LLVMInstrumentation",
        "LLVMAsmPrinter",
        "LLVMCodeGen",
        "LLVMTarget",
        -- "LLVMScalarOpts",
        -- "LLVMInstCombine",
        -- "LLVMAggressiveInstCombine",
        -- "LLVMObjCARCOpts",
        -- "LLVMTransformUtils",
        "LLVMBitWriter",
        "LLVMAnalysis",
        -- "LLVMProfileData",
        -- "LLVMSymbolize",
        "LLVMDebugInfoPDB",
        "LLVMDebugInfoMSF",
        "LLVMDebugInfoDWARF",
        -- "LLVMObject",
        -- "LLVMTextAPI",
        -- "LLVMMCParser",
        -- "LLVMIRReader",
        "LLVMAsmParser",
        -- "LLVMMC",
        "LLVMDebugInfoCodeView",
        -- "LLVMBitReader",
        -- "LLVMCore",
        "LLVMRemarks",
        -- "LLVMBitstreamReader",
        -- "LLVMBinaryFormat",
        -- "LLVMTargetParser",
        -- "LLVMSupport",
        -- "LLVMDemangle",
    }

    filter { "configurations:Debug" }
        conan_debug.basic_setup()
    filter {}

    filter { "configurations:Release" }
        conan_release.basic_setup()
    filter {}

workspace "*"

BoxInclude = "%{wks.location}/box/include/"