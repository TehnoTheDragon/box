-- Constants

THIRD_PARTY_DIRECTION = "%{wks.location}/thirdparty"
OUTPUT_DIRECTION = "%{wks.location}/build"

-- Util Functions

function pprint(...)
    local argv = {...}
    local pushes = 0
    local lastColor = nil
    for index, value in pairs(argv) do
        local is_set_color_command = string.sub(tostring(value), 1, 1) .. string.sub(tostring(value), -1, -1) == "$$"
        if is_set_color_command then
            local color = tonumber(string.sub(tostring(value), 2, -2))
            if lastColor ~= color then
                pushes = pushes + 1
                term.pushColor(color)
            elseif color == nil then
                term.popColor()
            end
        else
            print(value)
        end
    end
    for i = 1, pushes do
        term.popColor()
    end
end

function print_table(ttable, offset)
    offset = offset or ""
    for i,v in pairs(ttable) do
        local t = type(v)
        if t == "table" then
            if #v > 0 then
                print(offset .. string.format("%s: {", tostring(i)))
                print_table(v, offset .. "  ")
                print(offset .. "}")
            else
                print(offset .. string.format("%s {}", tostring(i)))
            end
        else
            print(offset .. string.format("%s: %s", tostring(i), tostring(v)))
        end
    end
end

local function get_project_direction()
    local name = "%{prj.name}"
    local configuration = "%{cfg.buildcfg}"
    local architecture = "%{cfg.platform}"
    return string.format("%s/%s/%s/%s", OUTPUT_DIRECTION, name, configuration, architecture)
end

function get_target_direction()
    return string.format("%s/bin/", get_project_direction())
end

function get_object_direction()
    return string.format("%s/", get_project_direction())
end

local function get_thirdparty_project_direction()
    local name = "%{prj.name}"
    local configuration = "%{cfg.buildcfg}"
    local architecture = "%{cfg.architecture}"
    return string.format("%s/thirdparty/%s/%s/%s", OUTPUT_DIRECTION, name, configuration, architecture)
end

function get_thirdparty_target_direction()
    return string.format("%s/bin/", get_thirdparty_project_direction())
end

function get_thirdparty_object_direction()
    return string.format("%s/", get_thirdparty_project_direction())
end

function find_library(libraryName)
    local host = os.host()
    local name = "%{prj.name}"
    local configuration = "%{cfg.buildcfg}"
    local architecture = "%{cfg.architecture}"
    return string.format("%s/thirdparty/%s/%s/%s-%s/bin/%s",
        OUTPUT_DIRECTION, libraryName, host, configuration, architecture, libraryName)
end