-- vendor/stb_image/premake5.lua
project "SOIL"
	kind "StaticLib"
	language "C++"
    staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files {
        "image_DXT.c" ,
        "image_DXT.h" ,
        "image_helper.c " ,
        "image_helper.h " ,
        "premake5.lua " ,
        "SOIL.c " ,
        "SOIL.h " ,
        "stb_image_aug.c " ,
        "stb_image_aug.h " ,
        "stbi_DDS_aug_c.h" ,
        "stbi_DDS_aug.h" , 
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
