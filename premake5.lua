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
    cppdialect "C++17"

    targetdir "bin/%{cfg.buildcfg}"
    objdir    "obj/%{cfg.buildcfg}"

    defines {
        "GLEW_STATIC",
       -- "IMGUI_IMPL_OPENGL_LOADER_GLAD"
    }

    includedirs {
        "LukkelEngine/include/",
        "LukkelEngine/include/Renderer",
        "LukkelEngine/include/Renderer/Test",
        "lib",
        "lib/glm",
        "lib/stb_image"
    }

    files { 
        "LukkelEngine/src/**.cpp",
        "LukkelEngine/include/**.h",
        "lib/stb_image/*",
		"lib/imgui/*.cpp"
   	}


    -- LINUX    
    filter "system:linux"
        links { "dl", "pthread" }
        defines {
            "_X11",
            "_IMGUI_X11"
        }
	
        filter "architecture:x64"
            libdirs {
                "lib/glfw/lib/",
                "lib/glew/lib/"
            }

            links {
                "glfw3",
                "opengl32",
                "glew32s",
            }

    -- WINDOWS
    filter "system:windows"
        defines { 
            "_WINDOWS",
            "_IMGUI_WIN32",
            "_CRT_SECURE_NO_WARNINGS" -- ImGui
        }
        
        filter "architecture:x64"
            libdirs {
                "lib/glfw/lib/",
                "lib/glew/lib/"
            }

            links {
                "glfw3",
                "opengl32",
                "glew32s",
            }


include "lib/glew.lua"
include "lib/glfw.lua"
-- include "lib/imgui.lua"
-- include "lib/glm.lua"
