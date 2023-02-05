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
    
    -- Precompiled Header -- FIX ERROR WITH INCLUDED VENDOR CPP FILES
    -- pchheader "LKpch.h"
    -- pchsource "LukkelEngine/LKpch.cpp"

    defines {
        "GLEW_STATIC"
       -- "IMGUI_IMPL_OPENGL_LOADER_GLAD"
    }

    includedirs {
        "LukkelEngine/src",
        "LukkelEngine/src/Platform",
        "LukkelEngine/src/LukkelEngine",
        "LukkelEngine/src/LukkelEngine/Renderer",
        "LukkelEngine/src/LukkelEngine/Test",
        "LukkelEngine/src/LukkelEngine/Display",
        "lib",
        "lib/glm",
        "lib/imgui",
        "lib/stb_image",
        "lib/glfw/include",
        "lib/glew/include",
        "lib/spdlog/include"
    }

    files { 
        "LukkelEngine/src/**.cpp",
        "LukkelEngine/src/**.h",
        "LukkelEngine/src/LukkelEngine/**.h",
        "LukkelEngine/src/LukkelEngine/**.cpp",

        "LukkelEngine/src/Platform/**.cpp",
        "LukkelEngine/src/Platform/**.h",

        "lib/stb_image/**.h",
        "lib/stb_image/**.cpp",
		-- "lib/imgui/*.cpp",
		"lib/imgui/imgui.cpp",
		"lib/imgui/imgui.h",
		"lib/imgui/imgui_draw.cpp",
		"lib/imgui/imgui_impl_glfw_gl3.cpp",
		"lib/imgui/imgui_impl_glfw_gl3.h",
		"lib/imgui/imgui_widgets.cpp",
        "lib/glm/glm/**.hpp",
        "lib/glm/glm/**.inl"
        -- "LukkelEngine/LKpch.cpp"
   	}


    -- LINUX    
    filter "system:linux"
        defines {
            "LK_PLATFORM_LINUX",
            "_X11",
            "_IMGUI_X11"
        }
		libdirs {
			"lib/glfw/lib/",
			"lib/glew/lib/"
		}
        links {
            "dl",
            "pthread",
		    "glfw3",
            "opengl32",
            "glew32s"
        }


	filter "system:windows"
		defines { 
        "LK_PLATFORM_WINDOWS",
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
