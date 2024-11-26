-- WalnutExternal-Headless.lua

IncludeDir = {


}
IncludeDir["glm"] = "../vendor/glm"
IncludeDir["spdlog"] = "../vendor/spdlog/include"
IncludeDir["vendor"] = "../vendor/"
IncludeDir["X11"] = "../vendor/X11"
IncludeDir["std_image"] = "../vendor/std_image"
IncludeDir["SOIL"] = "../vendor/SOIL"
 
 
group "Dependencies"
   include "vendor/STDIMAGE"
   include "vendor/SOIL"
   include "vendor/yaml-cpp"
group ""

-- group "Core"
--     include "Walnut/Build-Headless.lua"

     
group ""