project "Bullet3"
	kind "StaticLib"
	language "C++"
	--staticruntime "On"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	defines { "BT_USE_SSE_IN_API" }

	files
	{
		"src/**.cpp",
		"src/**.h",
		"src/BulletCollision/**.cpp",
		"src/BulletCollision/**.h",
		"src/BulletDynamics/**.cpp",
		"src/BulletDynamics/**.h",
		"src/BulletInverseDynamics/**.cpp",
		"src/BulletInverseDynamics/**.h",
		"src/BulletSoftBody/**.cpp",
		"src/BulletSoftBody/**.h",
		"src/LinearMath/**.cpp",
		"src/LinearMath/**.h",
	}

	includedirs
	{
		"src"
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
