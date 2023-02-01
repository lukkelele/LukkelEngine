-- premake5.lua
workspace "LukkelEngine"
    configurations { "Debug", "Release", "Dist" }
    architecture "x64"

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
    architecture "x64"
--   location "build/%{prj.name}"
--   location "%{prj.name}/"

    cppdialect "C++17"

    targetdir "bin/%{cfg.buildcfg}"
    objdir    "obj/%{cfg.buildcfg}"

    defines { "GLEW_STATIC" }

    libdirs -- REMOVE ME
    {
        "lib/glfw/lib/",
        "lib/glew/lib/"
    }


    includedirs
    {
        "LukkelEngine/include/",
        "LukkelEngine/include/Renderer",
        "LukkelEngine/include/Renderer/Test",
        "lib",
        "lib/glm",
        "lib/stb_image"
    }

    files
	{ 
        "LukkelEngine/src/**.cpp",
        "LukkelEngine/include/**.h",
        "lib/stb_image/**",

        -- ImGui
		"lib/imgui/*.cpp",
		-- "lib/imgui/imgui.h",
		-- "lib/imgui/imgui_impl_glfw.cpp",
		-- "lib/imgui/imgui_impl_glfw.h",
		-- "lib/imgui/imgui_impl_glfw_gl3.cpp",
		-- "lib/imgui/imgui_impl_glfw_gl3.h",

   	}

    links 
    {
        "glfw3",
        "opengl32",
        "glew32s",
    }

    -- LINUX    
    filter "system:linux"
        links { "dl", "pthread" }
        defines { "_X11" }
	
        filter "architecture:x64"
        libdirs
        {
            "lib/glfw/lib/",
            "lib/glew/lib/"
        }

    -- WINDOWS
    filter "system:windows"
        defines { "_WINDOWS", }
        
        filter "architecture:x64"
        libdirs
        {
            "lib/glfw/lib/",
            "lib/glew/lib/"
        }


include "lib/glew.lua"
include "lib/glfw.lua"
-- include "lib/glad.lua"
include "lib/imgui.lua"
-- include "lib/stb_image.lua"
include "lib/glm.lua"
