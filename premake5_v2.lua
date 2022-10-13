-- premake5.lua
workspace "LukkelEngine"
    configurations { "Debug", "Release", "Dist" }
    --architecture "x64"

    flags { "MultiProcessorCompile" }

    filter "configurations:Debug"
        defines { "LK_DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "LK_RELEASE" }
        optimize "On"

    filter "configurations:Dist"
        defines { "LK_DIST" }
        optimize "On"


project "LukkelEngine"
    kind "ConsoleApp"
    language "C++"
    location "build/%{prj.name}"
    cppdialect "C++17"
        architecture "x86_64"

    targetdir "bin/%{cfg.buildcfg}"
    objdir    "obj/%{cfg.buildcfg}"

    includedirs
    {
        "LukkelEngine/include/",
        "lib/glad/include/",
        "lib/glfw/include/",
        "lib/glm/",
        "lib/imgui/",
        "lib/imgui/examples",
        "lib/",
    }

    files { "LukkelEngine/src/*.cpp" }

    links { "GLFW", "GLM", "GLAD", "ImGui" }

    -- LINUX
    filter "system:linux"
        links
        {
            "dl",
            "pthread"
        }

        defines
        {
            "_X11"
        }

    -- WINDOWS
    filter "system:windows"
        defines { "_WINDOWS" }


include "lib/glad.lua"
include "lib/glfw.lua"
include "lib/glm.lua"
include "lib/imgui.lua"
