project "LukkeLallish"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.cpp"
	}

	includedirs
	{
		"%{wks.location}/LukkelEngine",
		"%{wks.location}/LukkelEngine/src",
		"%{wks.location}/lib",
		"%{wks.location}/lib/spdlog",
		"%{wks.location}/lib/glm",
		"%{wks.location}/lib/imgui",
		"%{wks.location}/lib/ImGuizmo",
		"%{wks.location}/lib/stb_image",
		"%{wks.location}/lib/glfw/include",
		"%{wks.location}/lib/glad/include",
		"%{wks.location}/lib/spdlog/include",
		"%{wks.location}/lib/entt/src",
		"%{wks.location}/lib/bullet3/src"
	}

	links
	{ 
		"LukkelEngine"
	}

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

