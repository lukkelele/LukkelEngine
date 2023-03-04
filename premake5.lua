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
include "lib/imgui/imgui.lua"
include "lib/bullet3/bullet3.lua"
include "lib/glad/glad.lua"

project "LukkelEngine"
    location "LukkelEngine"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "off"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "LKpch.h"
    pchsource "LukkelEngine/src/LKpch.cpp"

    defines
    {
        -- "GLEW_STATIC",
        "LKLOG_ADVANCED",
		"_GLM_WIN32",
		"GLFW_INCLUDE_NONE",
		"_CRT_SECURE_NO_WARNINGS",
        "BT_USE_SSE_IN_API",
        "IMGUI_IMPL_OPENGL_LOADER_GLAD"
    }

    files
    { 
        "%{prj.name}/**.h",
        "%{prj.name}/**.cpp",

        "%{wks.location}/lib/stb_image/**.h",
        "%{wks.location}/lib/stb_image/**.cpp",
   	}

    libdirs
    {
        -- "%{wks.location}/lib/glew/lib",
        "%{wks.location}/lib/GLFW/lib",
        "%{wks.location}/lib/bullet3/lib"
    }

    includedirs
    {
		"%{wks.location}/LukkelEngine/src",
        "%{prj.name}",
        "%{prj.name}/src",
		"%{wks.location}/lib",
		"%{wks.location}/lib/glm",
		"%{wks.location}/lib/imgui",
		"%{wks.location}/lib/imgui/examples",
		"%{wks.location}/lib/glad",
		"%{wks.location}/lib/glad/include",
		"%{wks.location}/lib/ImGuizmo",
		"%{wks.location}/lib/stb_image",
		"%{wks.location}/lib/GLFW/include",
		-- "%{wks.location}/lib/glew/include",
		"%{wks.location}/lib/spdlog/include",
		"%{wks.location}/lib/entt/src",

		"%{wks.location}/lib/bullet3/src",
    }

    links
    {
        "GLFW",
        "glad",
        "opengl32",
        -- "glew32s",
        "ImGui",
        "Bullet3",
    }

	filter "system:windows"
		defines 
        { 
			"LK_PLATFORM_WINDOWS",
			-- "GLEW_STATIC",
			"_IMGUI_WIN32",
			"_CRT_SECURE_NO_WARNINGS",
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
