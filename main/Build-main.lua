project "Artemis"
kind "ConsoleApp"
language "C++"
cppdialect "C++17"
targetdir "bin/%{cfg.buildcfg}"
staticruntime "off"

files { "src/**.h", "src/**.cpp", "src/**.c", "src/**.hpp", "src/**.tpp" }







includedirs {
   "str/src",
   "src",
   "src/core",
   "../vendor/imgui",
   "../vendor/imgui/backends/",
   "../vendor/GLFW/include",
   "../vendor/GL",
   "../vendor/stb_image",
   "../vendor/cnpy",
   "../vendor/SOIL",
   "../vendor/glm",
   "../vendor/spdlog/include",
   "../vendor/",
   "../vendor",
   "../vendor/glad",
   "%{IncludeDir.glm}",
   "%{IncludeDir.X11}"
}



links {
   "ImGui", "stb_image", "SOIL", "assimp",
   "GLFW", "GL", "glad", "fmt", "spdlog", 
   "cnpy" , "z"
}

targetdir("../build/" .. outputdir .. "/%{prj.name}")
objdir("../bin-int/" .. outputdir .. "/%{prj.name}")

filter "system:linux"
includedirs {
   "../vendor/X11"
}
links {
   "X11", "Xrandr", "Xi"
}



filter "system:windows"
systemversion "latest"
defines { "WL_PLATFORM_WINDOWS" }

filter "configurations:Debug"
defines { "WL_DEBUG" }
runtime "Debug"
symbols "On"

filter "configurations:Release"
defines { "WL_RELEASE" }
runtime "Release"
optimize "On"
symbols "On"

filter "configurations:Dist"
kind "WindowedApp"
defines { "WL_DIST" }
runtime "Release"
optimize "On"
symbols "Off"
