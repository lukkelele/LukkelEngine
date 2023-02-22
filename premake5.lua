workspace "LukkelEngine"
    architecture "x86_64"
    startproject "LukkeLallish"

    configurations
    {
        "Debug",
		"Release",
        "Dist"
    }

    flags { "MultiProcessorCompile" }

    filter "configurations:Debug"
        defines { "LK_DEBUG" }
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines { "LK_RELEASE" }
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines { "LK_DIST" }
        runtime "Release"
        optimize "On"


outputdir = "%{cfg.buildcfg}-%{cfg.system}"


include "LukkeLallish/premake5.lua"
include "lib/GLFW/glfw.lua"
-- include "lib/glew/glew.lua"
include "lib/imgui/imgui.lua"

project "LukkelEngine"
    location "LukkelEngine"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "off"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    defines
    {
        "GLEW_STATIC",
        "LKLOG_ADVANCED",
		    "_GLM_WIN32",
		    "GLFW_INCLUDE_NONE",
		    "_CRT_SECURE_NO_WARNINGS",

    }

    files
    { 
        "%{prj.name}/**.h",
        "%{prj.name}/**.cpp",

        "%{wks.location}/lib/stb_image/**.h",
        "%{wks.location}/lib/stb_image/**.cpp",

        "%{wks.location}/lib/imgui/imgui.cpp",
		    "%{wks.location}/lib/imgui/imgui.h",
		    "%{wks.location}/lib/imgui/imgui_draw.cpp",
		    "%{wks.location}/lib/imgui/imgui_impl_glfw_gl3.cpp",
		    "%{wks.location}/lib/imgui/imgui_impl_glfw_gl3.h",
		    "%{wks.location}/lib/imgui/imgui_widgets.cpp",

		    "%{wks.location}/lib/entt/entt.hpp",
        "%{wks.location}/glm/glm/**.hpp",

        "%{wks.location}/lib/ImGuizmo/*.cpp",
        "%{wks.location}/lib/ImGuizmo/*.h",

		"%{wks.locaton}/lib/glew/include/GL/glew.h",
   	}

    libdirs
    {
        "%{wks.location}/lib/glew/lib",
        "%{wks.location}/lib/glfw/lib"
    }

    includedirs
    {
        "%{prj.name}/src",
		"%{wks.location}/lib",
		"%{wks.location}/lib/glm",
		"%{wks.location}/lib/imgui",
		"%{wks.location}/lib/ImGuizmo",
		"%{wks.location}/lib/stb_image",
		"%{wks.location}/lib/glfw/include",
		"%{wks.location}/lib/glew/include",
		"%{wks.location}/lib/spdlog/include",
		"%{wks.location}/lib/entt/src"
    }

    links
    {
        "GLFW",
        --"glew",
        "opengl32",
        "glew32s",
        "ImGui",
    }

	filter "system:windows"
		defines 
        { 
			"LK_PLATFORM_WINDOWS",
			"GLEW_STATIC",
			"_IMGUI_WIN32",
			"_CRT_SECURE_NO_WARNINGS"
		}

	filter "configurations:Debug"
		defines "LK_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "LK_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "LK_DIST"
		runtime "Release"
		optimize "on"



	

-- include "lib/glew.lua"
-- include "lib/glfw.lua"
-- include "lib/imgui.lua"
-- include "lib/glm.lua"
