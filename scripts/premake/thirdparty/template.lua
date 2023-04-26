-- workspace "$WORKSPACE$"

-- local $TEMPLATE_NAME$ = get_thirdparty_folder("$TEMPLATE_NAME$")

-- project "$TEMPLATE_NAME$"
--     kind "StaticLib"
--     language "C"
--     cdialect "C99"

--     targetdir (get_thirdparty_target_direction())
--     objdir (get_thirdparty_object_direction())

--     files {
--         string.format("%s/src/**.m", $TEMPLATE_NAME$),
--         string.format("%s/src/**.h", $TEMPLATE_NAME$),
--         string.format("%s/src/**.c", $TEMPLATE_NAME$),
--         string.format("%s/src/**.in", $TEMPLATE_NAME$),
--         string.format("%s/deps/**", $TEMPLATE_NAME$),
--     }

--     includedirs {
--         string.format("%s/include/", $TEMPLATE_NAME$),
--     }

--     links {}
        
-- workspace "*"
        
-- $TEMPLATE_NAME$Include = string.format("%s/include/", $TEMPLATE_NAME$)