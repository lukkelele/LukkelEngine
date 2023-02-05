includedirs { "glad/include/" }

files 
{
	"glad/include/glad/glad.h",
	"glad/src/glad.c"
} 
 
links { "glad" }

filter "system:linux"
	pic "On"

	systemversion "latest"
	staticruntime "On"

	defines
	{
		"_GLAD_X11"
	}

filter "system:windows"
	systemversion "latest"
	staticruntime "On"

	defines 
	{ 
		"_GLAD_WIN32",
		"_CRT_SECURE_NO_WARNINGS"
	}

filter "configurations:Debug"
	runtime "Debug"
	symbols "on"

filter "configurations:Release"
	runtime "Release"
	optimize "on"