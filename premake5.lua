-- premake5.lua
workspace "LukkelEngine"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }


project "LukkelEngine"
    --location "LukkelEngine"
    kind "SharedLib"
    language "C++"
    targetdir "bin/%{cfg.buildcfg}/%{prj.name}"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
    }

    includedirs
    {
        "%{prj.name}/include/**.h",
        "%{prj.name}/include/**.cpp",
        "%{prj.name}/include/vendor/**.h",
        "%{prj.name}/include/vendor/**.cpp",
    }

    links
    {
        "LukkelEngine"
    }

    filter "configurations:Debug"
        defines { "LK_DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "LK_RELEASE" }
        optimize "On"

    filter "configurations:Dist"
        defines { "LK_DIST" }
        optimize "On"


