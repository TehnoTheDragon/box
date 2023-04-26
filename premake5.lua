-- Pre Includes
include "scripts/premake/predefines.lua"
include "scripts/premake/cross_workspace.lua"
include "scripts/premake/multi_conan.lua"

-- Main Workspace
create_cross_workspace "box"
workspace "*"

-- Post Includes
include "scripts/premake/thirdparty/thirdparty.lua"
include "box"
include "sandbox"

-- Clean Action
newaction {
    trigger = "clean",
    description = "delete build folder",
    execute = function()
        os.rmdir("./build")
    end
}