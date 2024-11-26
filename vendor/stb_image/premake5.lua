-- vendor/stb_image/premake5.lua
project "stb_image"
	kind "StaticLib"
	language "C++"
    staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files {
        "rrsprintf.h " ,
        "stb_image_resize.h " ,
        "stb_image.c " ,
        "stb_image.h " ,
        "stb.h " ,
        "stretch_test.c " ,
        "stretchy_buffer.h" ,
		 
	}

	filter "system:windows"
		systemversion "latest"
		cppdialect "C++17"

	filter "system:linux"
		pic "On"
		systemversion "latest"
		cppdialect "C++17"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"

    filter "configurations:Dist"
		runtime "Release"
		optimize "on"
        symbols "off"
