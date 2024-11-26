-- WalnutExternal.lua

-- VULKAN_SDK = os.getenv("VULKAN_SDK")
OpenGL_SDK = "../vendor/GL" -- Adjust the path accordingly

IncludeDir = {}

LibraryDir = {}
-- LibraryDir["VulkanSDK"] = "%{VULKAN_SDK}/Lib"

Library = {}
-- Library["Vulkan"] = "%{LibraryDir.VulkanSDK}/vulkan-1.lib"

group "Dependencies"
   include "vendor/imgui"
   include "vendor/GLFW"
   include "vendor/yaml-cpp"
   include "vendor/stb_image"
   include "vendor/SOIL"
group ""

-- group "Core"
--     include "Walnut/Build-Walnut.lua"

     
group ""