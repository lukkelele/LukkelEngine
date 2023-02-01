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
--    location "build/%{prj.name}"
--   location "%{prj.name}/"

    cppdialect "C++17"

    targetdir "bin/%{cfg.buildcfg}"
    objdir    "obj/%{cfg.buildcfg}"

    includedirs
    {
        "LukkelEngine/include/",
        "LukkelEngine/include/Renderer",
        "LukkelEngine/include/Renderer/Test",
        "lib/glad/include/",
        "lib/glfw/include/",
        "lib/glew/include/",
        "lib/glm/",
        "lib/imgui/",
        "lib/imgui/examples",
        "lib/",
    }

    files
	{ 
	"LukkelEngine/src/**.cpp",
	"LukkelEngine/include/**.h"
   	}
    -- lib links
    links 
    {
        "glfw3",
	    -- "glfw",
        -- "GLM",
        "opengl32",
        "glew32",
        -- "GLAD", 
        -- "ImGui"
    }

    filter "system:linux"
        links { "dl", "pthread" }
        defines { "_X11" }
	
	filter "architecture:x64"
	  libdirs
	  {
	  "lib/glfw/lib/",
	  "lib/glew/lib/"
	  }

    filter "system:windows"
        defines { "_WINDOWS" }
        
	filter "architecture:x64"
	  libdirs
	  {
	  "lib/glfw/lib/",
	  "lib/glew/lib/"
	  }


include "lib/glad.lua"
include "lib/glfw.lua"
include "lib/glm.lua"
include "lib/imgui.lua"
include "lib/stb_image.lua"
