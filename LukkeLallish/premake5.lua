project "LukkeLallish"
kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"src/**.h",
		"src/**.cpp"
	}

	includedirs {
		"%{wks.location}/LukkelEngine/lib/spdlog/include",
		"%{wks.location}/LukkelEngine/src",
		"%{wks.location}/LukkelEngine/src/LukkelEngine",
		"%{wks.location}/LukkelEngine/src/Platform",
		"%{wks.location}/LukkelEngine/lib",
		"%{wks.location}/LukkelEngine/lib/glm",
		"%{wks.location}/LukkelEngine/src/LukkelEngine/Renderer",
		"%{wks.location}/LukkelEngine/src/LukkelEngine/Test/",
		"%{wks.location}/LukkelEngine/src/LukkelEngine/Display",
		"%{wks.location}/lib",
		"%{wks.location}/lib/glm",
		"%{wks.location}/lib/stb_image",
		"%{wks.location}/lib/glfw/include",
		"%{wks.location}/lib/glew/include",
		"%{wks.location}/lib/spdlog/include"
	}

	links { "LukkelEngine" }

	filter "system:windows"
		systemversion "latest"

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
