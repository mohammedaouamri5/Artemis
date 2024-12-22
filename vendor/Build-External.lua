-- WalnutExternal.lua

-- VULKAN_SDK = os.getenv("VULKAN_SDK")

IncludeDir = {}

LibraryDir = {}
-- LibraryDir["VulkanSDK"] = "%{VULKAN_SDK}/Lib"

Library = {}
-- Library["Vulkan"] = "%{LibraryDir.VulkanSDK}/vulkan-1.lib"

group "Dependencies"
   include "vendor/imgui"
   include "vendor/GLFW"
   include "vendor/yaml-cpp"
   include "vendor/spdlog"
   include "vendor/stb_image"
   include "vendor/SOIL"
   include "vendor/glad"
   include "vendor/cnpy"

group ""

-- group "Core"
--     include "Walnut/Build-Walnut.lua"

     
group ""
