project "Bullet3"
	kind "StaticLib"
	language "C"
	staticruntime "On"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.cpp",
		"src/**.hpp",
		"src/**.c",
		"src/**.h",
	}

	includedirs
	{
		"src",
		"test"
	}

	links
	{
		-- "Bullet3Collision",
		-- "Bullet3Common",
		-- "Bullet3Dynamics",
		-- "Bullet3Geometry",
		-- "Bullet3Serialize",
		-- "BulletSoftBody",
		-- "LinearMath"
	}


	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		runtime "Release"
		optimize "on"
