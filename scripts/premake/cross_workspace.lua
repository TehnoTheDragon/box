CrossWorkspace = {
    CACHE = {
        GENERATED_PLATFORMS = {},
        GENERATED_FILTERS = {},
        GENERATED_CONFIGURATIONS = {},
    },

    SYSTEMS = {},
    ARCHITECTURES = {},
    CONFIGURATIONS = {},

    add_architecture = function(self, architecture, name)
        local newarch = {}
        newarch.name = name
        self.ARCHITECTURES[architecture] = newarch
    end,

    add_system = function(self, system, name, architectures)
        local newsys = {}
        newsys.name = name
        newsys.archs = architectures
        self.SYSTEMS[system] = newsys
    end,

    add_configuration = function(self, configuration)
        table.insert(self.CONFIGURATIONS, configuration)
    end,

    init = function(self)
        term.pushColor(0x06)
        print("CrossWorkspace: Initialization Begin")
        term.popColor()

        local GP = self.CACHE.GENERATED_PLATFORMS
        local GF = self.CACHE.GENERATED_FILTERS
        local GC = self.CACHE.GENERATED_CONFIGURATIONS

        term.pushColor(0x0A)
        
        print("Systems:")
        for system, systemObject in pairs(self.SYSTEMS) do
            print(" - ".. system .. ":")
            for arch_index, architecture in pairs(systemObject.archs) do
                table.insert(GP, string.format("%s_%s", systemObject.name, architecture))

                local SYSTEM = string.format("SYSTEM_%s", system:upper())
                local ARCH = string.format("ARCH_%s", architecture)
                local OS = string.format("OS_%s", systemObject.name:upper())
                local PLATFORM = string.format("PLATFORM_%s_%s", systemObject.name:upper(), architecture)
                
                for configuration_index, configuration in pairs(self.CONFIGURATIONS) do
                    table.insert(GF, {
                        defines = { SYSTEM, ARCH, OS, PLATFORM },
                        system = system,
                        architecture = architecture,
                        platform = string.format("%s_%s", systemObject.name, architecture),
                    })
                end
                

                print("   - " .. architecture)
                print("     : ", SYSTEM, ARCH, OS, PLATFORM)
            end
        end

        print("Configurations:")
        for configuration_index, configuration in pairs(self.CONFIGURATIONS) do
            table.insert(GC, configuration)
            print(" - " .. configuration)
        end

        term.popColor()

        term.pushColor(0x06)
        print("CrossWorkspace: Initialization Finish")
        term.popColor()
    end,

    get_generated_platforms = function(self)
        return self.CACHE.GENERATED_PLATFORMS
    end,

    get_generated_configurations = function(self)
        return self.CACHE.GENERATED_CONFIGURATIONS
    end,

    apply_filters = function(self)
        term.pushColor(0x06)
        print("CrossWorkspace: Apply Filters Begin")
        term.popColor()
        
        term.pushColor(0x0A)

        for configuration_index, configuration in pairs(self.CONFIGURATIONS) do
            for filter_index, filterObject in pairs(self.CACHE.GENERATED_FILTERS) do
                filter (string.format("platforms:%s", filterObject.platform))
                    defines (filterObject.defines)
                    system (filterObject.system)
                    architecture (filterObject.architecture)
                filter {}
                print(
                    "(" .. string.format("platforms:%s", filterObject.platform) .. "):",
                    string.format("\n  - defines: {%s}", table.concat(filterObject.defines, ", ")),
                    string.format("\n  - system: %s", filterObject.system),
                    string.format("\n  - architecture: %s", filterObject.architecture)
                )
                    
                filter (string.format("configurations:%s", configuration))
                    defines (configuration:upper())
                    if configuration == "Debug" then
                        symbols "On"
                    elseif configuration == "Release" then
                        optimize "On"
                    end
                filter {}
                print(
                    "(" .. string.format("configurations:%s", configuration) .. "):",
                    string.format("\n  - defines: {%s}", configuration),
                    string.format("\n  - symbols: %s", configuration == "Release" and "Off" or "On"),
                    string.format("\n  - optimize: %s", configuration == "Debug" and "Off" or "On")
                )
            end
        end

        term.popColor()

        term.pushColor(0x06)
        print("CrossWorkspace: Apply Filters End")
        term.popColor()
    end,
}

CrossWorkspace:add_architecture("x32", "32")
CrossWorkspace:add_architecture("x64", "64")

CrossWorkspace:add_system("windows", "Windows", {"x32", "x64"})
CrossWorkspace:add_system("linux", "Unix", {"x32", "x64"})
CrossWorkspace:add_system("macosx", "Mac", {"x32", "x64"})

CrossWorkspace:add_configuration("Debug")
CrossWorkspace:add_configuration("Release")

CrossWorkspace:init()

function create_cross_workspace(workspace_name)
    print(string.format("New Workspace: %s", workspace_name))

    workspace (workspace_name)
    configurations (CrossWorkspace:get_generated_configurations())
    platforms (CrossWorkspace:get_generated_platforms())
    CrossWorkspace:apply_filters()
end