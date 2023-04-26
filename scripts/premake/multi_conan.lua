local conanpath = "../../conan"
local conanfile = string.format("%s/conanfile.txt", conanpath)

local function get_conan_configration_folder(configuration)
    return string.format("%s/%s/", conanpath, configuration:lower())
end

local function multi_install()
    local configurations = CrossWorkspace:get_generated_configurations()
    for configuration_index, configuration in pairs(configurations) do
        local command = string.format("conan install %s --build missing -if %s -s build_type=%s",
            conanfile, get_conan_configration_folder(configuration), configuration)
        print(command)
        os.executef(command)
    end
end

local function include_conan(filename)
    include(filename)
    local buildinfo = {}
    local prefix = "conan_"
    for k, v in pairs(_G) do
        if k:sub(1, #prefix) == prefix then
            buildinfo[k:sub(#prefix + 1)] = v
        end
    end
    buildinfo.basic_setup = function()
        configurations{buildinfo.build_type}
        architecture(buildinfo.arch)
        includedirs{buildinfo.includedirs}
        libdirs{buildinfo.libdirs}
        links{buildinfo.libs}
        links{buildinfo.system_libs}
        links{buildinfo.frameworks}
        defines{buildinfo.defines}
        bindirs{buildinfo.bindirs}
    end
    return buildinfo
end

multi_install()
conan_debug = include_conan (string.format("%s/%s", conanpath, "debug/conanbuildinfo.premake.lua"))
conan_release = include_conan (string.format("%s/%s", conanpath, "release/conanbuildinfo.premake.lua"))