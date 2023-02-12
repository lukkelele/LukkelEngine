project "LukkeLallish"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"src/**.h",
		"src/**.cpp"
	}

	includedirs {
		"%{wks.location}/LukkelEngine/src",
		"%{wks.location}/lib/spdlog",
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
