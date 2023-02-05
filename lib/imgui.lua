	includedirs
	{ 
		"imgui/",
		"lib/imgui/", 
		"imgui/examples/",
	}

	files
	{
		"imgui/*.cpp",
		"lib/imgui/*.cpp",
		"imgui/imgui.h",
		"imgui/imgui_impl_glfw.cpp",
		"imgui/imgui_impl_glfw.h",
		"imgui/imgui_impl_glfw_gl3.cpp",
		"imgui/imgui_impl_glfw_gl3.h",
	}

	defines 
	{
		"IMGUI_IMPL_OPENGL_LOADER_GLAD"
	}
    
	filter "system:linux"
		pic "On"

		systemversion "latest"
		staticruntime "On"

		defines
		{
			"_IMGUI_X11"
		}

	filter "system:windows"
		systemversion "latest"
		staticruntime "On"

		defines 
		{ 
			"_IMGUI_WIN32",
			"_CRT_SECURE_NO_WARNINGS"
		}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"