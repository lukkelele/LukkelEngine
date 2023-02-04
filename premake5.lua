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
    
    -- Precompiled Headers
    -- pchheader "LKpch.h"
    -- pchsource "./LukkelEngine/LKpch.cpp"

    defines {
        "GLEW_STATIC"
       -- "IMGUI_IMPL_OPENGL_LOADER_GLAD"
    }

    includedirs {
        "LukkelEngine/",
        "LukkelEngine/src/",
        "LukkelEngine/src/Renderer",
        "LukkelEngine/src/Test",
        "LukkelEngine/src/Platform",
        "LukkelEngine/src/Display",
        "LukkelEngine/src/Displ",
        "lib",
        "lib/glm",
        "lib/stb_image",
        "lib/glfw/include",
        "lib/glew/include"
    }

    files { 
        "LukkelEngine/src/**.cpp",
        "LukkelEngine/src/**.h",
        "lib/stb_image/*",
		"lib/imgui/*.cpp"
        -- "LukkelEngine/LKpch.cpp"
   	}


    -- LINUX    
    filter "system:linux"
        links {
          "dl",
          "pthread"
        }
        defines {
            "_X11",
            "_IMGUI_X11"
        }

	filter "system:windows"
		defines { 
        "GLEW_STATIC",
		"_IMGUI_WIN32",
		"_CRT_SECURE_NO_WARNINGS" -- ImGui
		}
		libdirs {
			"lib/glfw/lib/",
			"lib/glew/lib/"
		}
		links { "glfw3", "opengl32", "glew32s" }


	
--        -- LINUX 64 bit
--        filter "architecture:x64"
--            defines { 
--                "PLATFORM_LINUX_64",
--				"GLEW_STATIC"
--            }
--            libdirs {
--                "lib/glfw/lib/",
--                "lib/glew/lib/"
--            }
--            links { "glfw3", "opengl32", "glew32s" }
--
--        -- LINUX 32 bit  FIXME
--        filter "architecture:x86"
--            defines {
--                "PLATFORM_LINUX_32",
--				"GLEW_STATIC"
--            }
--            libdirs {
--                "lib/glfw/lib/",
--                "lib/glew/lib/"
--            }
--            links { "glfw3", "opengl32", "glew32s" }
--
--    -- WINDOWS
--    filter "system:windows"
--        defines { 
--            "_IMGUI_WIN32",
--            "_CRT_SECURE_NO_WARNINGS" -- ImGui
--        }
--       -- WINDOWS 64 bit 
--        filter "architecture:x64"
--            defines { 
--                "PLATFORM_WINDOWS_64",
--				"GLEW_STATIC"
--            }
--            libdirs {
--                "lib/glfw/lib/",
--                "lib/glew/lib/"
--            }
--            links { "glfw3", "opengl32", "glew32s" }
--        -- WINDOWS 32 bit
--        filter "architecture:x86"
--            defines { "PLATFORM_WINDOWS_32" }
--            libdirs {
--                "lib/glfw/lib/",
--                "lib/glew/lib/"
--            }
--            links { "glfw3", "opengl32", "glew32s" }




include "lib/glew.lua"
include "lib/glfw.lua"
-- include "lib/imgui.lua"
-- include "lib/glm.lua"
