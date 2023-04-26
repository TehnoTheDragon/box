function get_thirdparty_folder(ThirdPartyName)
    return string.format("%s/thirdparty/%s", "%{wks.location}", ThirdPartyName)
end